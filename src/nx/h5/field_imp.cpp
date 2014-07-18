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
#include <pni/io/nx/h5/field_factory.hpp>

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
        :_object(std::move(o._object)),
         _file_space(std::move(o._file_space)),
         _memory_space(std::move(o._memory_space)),
         _type(std::move(o._type))
    { }

    //-----------------------------------------------------------------
    field_imp::field_imp(const group_imp &parent,
                         const string &name,
                         type_id_t tid,
                         const type_imp::index_vector_type &shape,
                         const type_imp::index_vector_type &chunk,
                         const h5filter &filter)
    {
        *this = field_factory::create(parent,name,tid,shape,chunk,
                                      filter);
    }



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

        type_imp::index_vector_type b(_file_space.rank());
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
    void field_imp::resize(const type_imp::index_vector_type &s)
    {
        if(s.size() != _file_space.rank())
            throw shape_mismatch_error(EXCEPTION_RECORD,
                  "New shape does not have the same rank!");

        herr_t err = H5Dset_extent(_object.id(),s.data());
        if(err < 0)
            throw pni::io::nx::nxfield_error(EXCEPTION_RECORD, 
                 "Resizing of dataset ["+get_object_path(_object.id())
                 +"] failed!\n\n"+ get_h5_error_string());

        _update();
    }


    //------------------------------------------------------------------------
    type_imp::index_vector_type field_imp::shape() const
    {
        type_imp::index_vector_type s(_memory_space.rank());
        std::copy(_memory_space.current_begin(),
                  _memory_space.current_end(),
                  s.begin());
        return s;
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

    //------------------------------------------------------------------------
    string field_imp::name() const
    {
        return get_name(_object);
    }

    //------------------------------------------------------------------------
    object_imp field_imp::parent() const
    {
        return get_parent(_object);
    }

    //------------------------------------------------------------------------
    string field_imp::filename() const 
    {
        return get_filename(_object.id());
    }

    //------------------------------------------------------------------------
    bool field_imp::is_valid() const
    {
        return _object.is_valid();
    }

    //------------------------------------------------------------------------
    attribute_imp field_imp::attr(const string &name) const 
    {
        return attribute_imp(get_attribute_by_name(_object,name));
    }

    //------------------------------------------------------------------------
    attribute_imp field_imp::attr(size_t i) const
    {
        return attribute_imp(get_attribute_by_index(_object,i));
    }

    //-----------------------------------------------------------------------
    size_t field_imp::nattr() const noexcept
    {
        return get_number_of_attributes(_object);
    }

    //-----------------------------------------------------------------------
    bool field_imp::has_attr(const string &name) const
    {
        return has_attribute(_object,name);
    }
     
    //------------------------------------------------------------------------
    void field_imp::del_attr(const string &name) const
    {
        delete_attribute(_object,name);
    }

    
    void field_imp::apply_selection(const type_imp::selection_vector_type &s)
        const
    {
        //create an array selection
        array_selection asel = array_selection::create(s);
        
        //create buffers
        auto offset = asel.offset<type_imp::index_vector_type>();
        auto stride = asel.stride<type_imp::index_vector_type>();
        auto count = asel.full_shape<type_imp::index_vector_type>();

        //need to throw an exception if the rank of the selection and
        //that of the 
        if(offset.size() != _file_space.rank())
            throw shape_mismatch_error(EXCEPTION_RECORD,
                    "Selection and field rank do not match!");

        //apply the selection
        herr_t err = H5Sselect_hyperslab(_file_space.object().id(),
                H5S_SELECT_SET,offset.data(),stride.data(),count.data(),
                nullptr);
        if(err<0)
            throw pni::io::nx::nxfield_error(EXCEPTION_RECORD,
                    "Error applying selection to dataset!\n\n"+
                    get_h5_error_string());

        //need to set the memory dataspace to the effective shape of the
        //selection
        _memory_space = h5dataspace(asel.shape<std::vector<size_t>>());

    }

    //------------------------------------------------------------------------
    void field_imp::clear_selections() const
    {
        //this should be quite easy - there is nothing special we have
        ///to do.
        if(_file_space.object().is_valid())
        {
            H5Sselect_all(_file_space.object().id());
            _memory_space = _file_space;
        }
    }

    //------------------------------------------------------------------------
    attribute_imp field_imp::attr(const string &name,type_id_t tid,
                                  bool overwrite) const
    {
        return attribute_imp(create_attribute(_object,
                                              name,
                                              get_type(tid),
                                              h5dataspace(),
                                              overwrite));
    }

    //------------------------------------------------------------------------
    attribute_imp field_imp::attr(const string &name,type_id_t tid,
                                  const type_imp::index_vector_type &shape,
                                  bool overwrite) const
    {
        return attribute_imp(create_attribute(_object,
                                              name,
                                              get_type(tid),
                                              h5dataspace(shape),
                                              overwrite));
    }

//end of namespace
}
}
}
}
