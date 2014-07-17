//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Jul 16, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/current_function.hpp>

#include <pni/io/nx/h5/field_imp.hpp>

namespace pni{
namespace io{
namespace nx{
namespace h5{

    //============implementation of private methods====================
    void field_imp::_update()
    {
        _file_space = h5dataspace(object_imp(H5Dget_space(_object.id())));
        _type       = h5datatype(object_imp(H5Dget_type(_object.id())));
        _memory_space = _file_space;
    }

    //===implementation of constructors and destructors================
    //implementation of the default constructor
    field_imp::field_imp() noexcept
        :_object(),
         _file_space(),
         _memory_space(),
         _type()
    { } 
    
    //-----------------------------------------------------------------
    //implementation of the copy conversion constructor
    field_imp::field_imp(object_imp &&o):
        _object(std::move(o)),
        _file_space(),
        _memory_space(),
        _type()
    {
        if(get_hdf5_type(_object) != h5object_type::DATASET)
            throw type_error(EXCEPTION_RECORD,
                    "Object is not an HDF5 dataset!");
        _update();
    }
    
    //-----------------------------------------------------------------
    //implementation of the copy constructor
    field_imp::field_imp(const field_imp &o)
        :_object(o._object),
         _file_space(o._file_space), 
         _memory_space(o._memory_space),
         _type(o._type)
    { }


    //-----------------------------------------------------------------
    //implementation of the move constrcutor
    field_imp::field_imp(field_imp &&o) noexcept
        :_object(o._object),
         _file_space(std::move(o._file_space)),
         _memory_space(std::move(o._memory_space)),
         _type(std::move(o._type))
    { }

    //=========implementation of the assignment operators==============
    //implementation of the  copy assignment operator
    field_imp &field_imp::operator=(const field_imp &o)
    {
        if(this == &o) return *this;

        _object       = o._object;
        _file_space   = o._file_space;
        _memory_space = o._memory_space;
        _type         = o._type;

        return *this;
    }

    //-----------------------------------------------------------------
    //implementation of the  move assignment operator
    field_imp &field_imp::operator=(field_imp &&o) noexcept
    {
        if(this == &o) return *this;

        _object       = std::move(o._object);
        _file_space   = std::move(o._file_space);
        _memory_space = std::move(o._memory_space);
        _type         = std::move(o._type);

        return *this;
    }


    //=========implementation of inquery methods========================
    void field_imp::grow(const size_t &e,const size_t &n)
    {
        if(e>=rank())
        {
            std::stringstream ss;
            ss<<"Dimension index ("<<e<<") exceeds rank of ";
            ss<<"dataspace ["<<get_object_path(_object.id())
              <<"] which is ("<<rank()<<")!";
            throw index_error(EXCEPTION_RECORD,ss.str());
        }

        size_vector_t b(_file_space.rank());
        std::copy(_file_space.current_begin(),
                  _file_space.current_end(),
                  b.begin());
        b[e] += n;

        herr_t err = H5Dset_extent(_object.id(),b.data());
        if(err < 0)
            throw pni::io::nx::nxfield_error(EXCEPTION_RECORD, 
                  "Grow of dataset ["+get_object_path(_object.id())
                  +"] failed!\n\n"+get_h5_error_string());

        //re-fetch the new dataspace
        _file_space.grow(e,n);
        _memory_space = _file_space;
    }

    //------------------------------------------------------------------
    void field_imp::write(const string *sptr) const
    {
        typedef const char * char_ptr_t;
        //select the proper memory data type
        
        h5datatype mem_type(object_imp(H5Dget_type(_object.id())));
        char_ptr_t *ptr = new char_ptr_t[size()];
        for(size_t i=0;i<size();i++)
            ptr[i] = sptr[i].c_str();

        //write data to disk
        herr_t err = H5Dwrite(_object.id(),
                              mem_type.object().id(),
                              _memory_space.object().id(),
                              _file_space.object().id(),
                              H5P_DEFAULT,
                              (const void *)ptr);

        delete [] ptr; //free memory
        if(err<0)
            throw pni::io::nx::nxfield_error(EXCEPTION_RECORD, 
                    "Error writing data to dataset!\n\n"+
                    get_h5_error_string());
    }

    //------------------------------------------------------------------------
    size_t field_imp::dim(const size_t &i) const 
    { 
        return _memory_space.current_dim(i); 
    }
    
    //------------------------------------------------------------------------
    type_id_t field_imp::type_id() const 
    { 
        return pni::io::nx::h5::type_id(_type); 
    }

    //------------------------------------------------------------------------
    size_t field_imp::size() const 
    { 
        return _memory_space.size(); 
    }
    
    //------------------------------------------------------------------------
    size_t field_imp::rank() const 
    { 
        return _memory_space.rank(); 
    }
    //-----------------------------------------------------------------
    void field_imp::read(string *sptr) const
    {
        //select the proper memory data type
        h5datatype mem_type(object_imp(H5Dget_type(_object.id())));
        
        if(H5Tis_variable_str(mem_type.object().id()))
            _read_vl_strings(sptr,mem_type);
        else
            _read_static_strings(sptr,mem_type);
    }

    //-------------------------------------------------------------------------
    void field_imp::_read_vl_strings(string *s,h5datatype &stype) const
    {
        std::vector<char *> ptrs(size());

        //need here a more general guard for HDF5 objects
        hid_t xfer_plist = H5Pcreate(H5P_DATASET_XFER);

        //read data from disk
        herr_t err = H5Dread(_object.id(),
                             stype.object().id(),
                             _memory_space.object().id(),
                             _file_space.object().id(),
                             xfer_plist,
                             (void *)ptrs.data());
        if(err<0)
        {
            H5Pclose(xfer_plist); //close the transfer property list
            pni::io::nx::nxfield_error error(EXCEPTION_RECORD, 
                    "Error reading data to dataset ["
                    +get_object_path(_object.id())+"]!\n\n"+
                    get_h5_error_string());
            throw error;
        }

        for(size_t i=0;i<size();i++)
        {
            try
            {
                s[i] = string(ptrs[i]);
            }
            catch(...)
            {
                s[i] = "";
            }
        }

        H5Dvlen_reclaim(stype.object().id(),
                        _memory_space.object().id(),
                        xfer_plist,
                        ptrs.data());
        H5Pclose(xfer_plist); //close the transfer property list
    }

    //-------------------------------------------------------------------------
    void field_imp::_read_static_strings(string *s,h5datatype &stype) const
    {
        size_t strsize = H5Tget_size(stype.object().id());

        std::vector<char> ptrs(strsize*size());

        //read data from disk
        herr_t err = H5Dread(_object.id(),
                             stype.object().id(),
                             _memory_space.object().id(),
                             _file_space.object().id(),
                              H5P_DEFAULT,
                              (void *)ptrs.data());
        if(err<0)
        {
            pni::io::nx::nxfield_error error(EXCEPTION_RECORD, 
                    "Error reading data to dataset ["
                    +get_object_path(_object.id())+"]!\n\n"+
                    get_h5_error_string());
            throw error;
        }

        for(size_t i=0;i<size();i++)
            s[i] = string(ptrs.data()+i*strsize,strsize);
    }


    //-------------------------------------------------------------------------
    void field_imp::close() 
    {
        _file_space = h5dataspace();
        _memory_space = h5dataspace();
        _type = h5datatype();
        _object.close();
    }



//end of namespace
}
}
}
}
