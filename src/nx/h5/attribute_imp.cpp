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

#include <pni/io/nx/h5/attribute_imp.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/h5/hdf5_utilities.hpp>


namespace pni{
namespace io{
namespace nx{
namespace h5{

    using pni::io::io_error;
    using pni::io::invalid_object_error;
    using pni::io::object_error;

    //===============private methods===========================================
    void attribute_imp::__update()
    {
        _dspace = h5dataspace();
        _dtype  = h5datatype();

        if(_object.is_valid())
        {
            //we can use this Ids to create new H5Objects from which 
            //the datatype and the dataspace can be constructed.
            _dspace = h5dataspace(object_imp(H5Aget_space(_object.id())));
            _dtype  = h5datatype(object_imp(H5Aget_type(_object.id())));
        }
    }

    //===========constructors and destructors==================================
    //! implementation of the default constructor
    attribute_imp::attribute_imp() noexcept 
        :_object(),
         _dspace(),
         _dtype()
    {}
    
    //-------------------------------------------------------------------------
    attribute_imp::attribute_imp(object_imp &&object)
        :_object(std::move(object)),
         _dspace(),
         _dtype()
    {
        if(get_hdf5_type(_object) != h5object_type::ATTRIBUTE)
            throw type_error(EXCEPTION_RECORD,
                    "Object is not an attribute instance!");

        //update dataspace and datatype
        __update();
    }

    //-------------------------------------------------------------------------
    //implementation of the copy constructor
    attribute_imp::attribute_imp(const attribute_imp &o)
        :_object(o._object),
         _dspace(o._dspace),
         _dtype(o._dtype)
    { }

    //--------------------------------------------------------------------------
    //implementation of the move constructor
    attribute_imp::attribute_imp(attribute_imp &&o) noexcept
        :_object(std::move(o._object)),
         _dspace(std::move(o._dspace)),
         _dtype(std::move(o._dtype))
    { }

    //===============implementation of assignment operators====================
    // implementation of copy assignment operator
    attribute_imp &attribute_imp::operator=(const attribute_imp &a)
    {
       if(this == &a) return *this;
    
       _object = a._object;
       _dspace = a._dspace;
       _dtype  = a._dtype;

       return *this;
    }
    
    //-------------------------------------------------------------------------
    //implementation of move assignment operator
    attribute_imp &attribute_imp::operator=(attribute_imp &&o) noexcept
    {
        if(this == &o) return *this;

        _object = std::move(o._object);
        _dspace = std::move(o._dspace);
        _dtype  = std::move(o._dtype);

        return *this;
    }

    //=========implementation of inquery methods===============================
    type_id_t attribute_imp::type_id() const
    {
        return pni::io::nx::h5::type_id(_dtype);
    }

    //-------------------------------------------------------------------------
    string attribute_imp::name() const
    {
        return get_name(_object);
    }

    //-------------------------------------------------------------------------
    object_imp attribute_imp::parent() const
    {
        return get_parent(_object);
    }

    //-------------------------------------------------------------------------
    bool attribute_imp::is_valid() const
    {
        return _object.is_valid();
    }

    //-------------------------------------------------------------------------
    string attribute_imp::filename() const
    {
        return get_filename(_object);
    }
    
    //-------------------------------------------------------------------------
    //implementation of write from String
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
    void attribute_imp::write(type_id_t tid,const string *s) const
    {
        std::vector<const char*> ptrs(size());

        for(size_t i=0;i<size();i++) ptrs[i] = s[i].data();

        herr_t err = H5Awrite(_object.id(),
                              _dtype.object().id(),
                              (void *)ptrs.data());
        if(err < 0)
            throw io_error(EXCEPTION_RECORD, 
                  "Error writing attribute ["+name()+"]!\n\n"
                  +get_h5_error_string());
    }
#pragma GCC diagnostic pop

    //-------------------------------------------------------------------------
    void attribute_imp::write(type_id_t tid,const void *ptr) const
    {
        const h5datatype &mem_type = get_type(tid);
        herr_t err = H5Awrite(_object.id(),
                              mem_type.object().id(),
                              ptr);
        if(err<0)
            throw io_error(EXCEPTION_RECORD, 
                           "Error writing attribute ["+this->name()+"]!\n\n"
                           +get_h5_error_string());
    }
    
    //-------------------------------------------------------------------------
    void attribute_imp::read(type_id_t tid,void *ptr) const
    {
        const h5datatype &mem_type = get_type(tid);
        herr_t err = H5Aread(_object.id(),
                              mem_type.object().id(),
                              ptr);
        if(err<0)
            throw io_error(EXCEPTION_RECORD, 
                           "Error reading attribute ["+this->name()+"]!\n\n"
                           +get_h5_error_string());
    }

    //-------------------------------------------------------------------------
    type_imp::index_vector_type attribute_imp::shape() const
    {
        type_imp::index_vector_type s(_dspace.rank());
        std::copy(_dspace.current_begin(),
                  _dspace.current_end(),
                  s.begin());
        return s;
    }
    
    //-------------------------------------------------------------------------
    size_t attribute_imp::size() const 
    { 
        return this->_dspace.size(); 
    }

    //-------------------------------------------------------------------------
    size_t attribute_imp::rank() const 
    { 
        return this->_dspace.rank(); 
    }

    //-------------------------------------------------------------------------
    void attribute_imp::write(type_id_t tid,const char *s) const 
    {
        string str(s);
        write(tid,&str);
    }
    //-------------------------------------------------------------------------
    //implementation to read to string
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
    void attribute_imp::read(type_id_t tid,string *s) const
    {
        //if the type is not a variable length string memory must be allocated
        //for each string in the attribute
        if(!H5Tis_variable_str(_dtype.object().id()))
            _read_static_strings(s);
        else
            _read_vl_strings(s);

    }
#pragma GCC diagnostic pop

    //-------------------------------------------------------------------------
    void attribute_imp::_read_vl_strings(string *s) const
    {
        size_t nstrings = size();

        //allocate a vector of pointers each holding an individual string
        std::vector<char*> str_pointers(nstrings);
            
        herr_t err = H5Aread(_object.id(),
                             _dtype.object().id(),
                             (void *)str_pointers.data());
        if(err<0)
            throw io_error(EXCEPTION_RECORD, 
                    "Error reading attribute ["+name()+"]!\n\n"+
                    get_h5_error_string());

        //copy the strings
        for(size_t i = 0;i<nstrings;i++)
            s[i] = string(str_pointers[i]);

    }

    //-------------------------------------------------------------------------
    void attribute_imp::_read_static_strings(string *s) const
    {
        //total number of strings stored
        size_t nstrings = size(); 
        //determine the length of the strings
        size_t ssize    = H5Tget_size(_dtype.object().id());

        //allocate memory
        std::vector<char> str_data(nstrings*ssize);

        herr_t err = H5Aread(_object.id(),
                             _dtype.object().id(),
                             (void *)str_data.data());
        if(err<0)
            throw io_error(EXCEPTION_RECORD, 
                    "Error reading attribute ["+name()+"]!\n\n"+
                    get_h5_error_string());

        //copy the strings
        for(size_t i = 0;i<nstrings;++i)
            s[i] = string(str_data.data()+i*ssize,ssize);

    }

    //-------------------------------------------------------------------------
    void attribute_imp::close()
    {
        _object.close();
    }
           

//end of namespace
}
}
}
}
