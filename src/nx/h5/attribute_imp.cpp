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
#include <pni/io/nx/h5/h5_error_stack.hpp>
#include <pni/io/nx/h5/string_utils.hpp>


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

        //we do not throw invalid_object_error as this member function is used
        //during construction where the object would definitely be invalid
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
        //as attribute_imp is a composite object we have to check all its
        //components to determine the validity status
        return _object.is_valid() && 
               _dspace.is_valid() && 
               _dtype.object().is_valid();
    }

    //-------------------------------------------------------------------------
    string attribute_imp::filename() const
    {
        return get_filename(_object);
    }
    
    //-------------------------------------------------------------------------
    type_imp::index_vector_type attribute_imp::shape() const
    {
        type_imp::index_vector_type s(_dspace.rank());
        std::copy(_dspace.shape().begin(),
                  _dspace.shape().end(),
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
    void attribute_imp::write(type_id_t tid,const void *ptr) const
    {
        if(!is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Cannot write data to invalid attribut!");

        if(tid==type_id_t::STRING)
        {
            auto s = static_cast<const string*>(ptr);
            std::vector<const char*> ptrs(size());
            for(size_t i=0;i<size();i++) ptrs[i] = s[i].data();
            _write_data(_dtype,static_cast<const void*>(ptrs.data()));
        }
        else
        {
            const h5datatype &mem_type = get_type(tid);
            _write_data(mem_type,ptr);
        }
    }

    //-------------------------------------------------------------------------
    void attribute_imp::_write_data(const h5datatype &memtype,const void *ptr)
        const
    {
        if(H5Awrite(_object.id(),memtype.object().id(),ptr)<0)
            throw io_error(EXCEPTION_RECORD,
                    "Error writing attribute ["+name()+"]!\n\n"
                    +get_h5_error_string());

    }


    //-------------------------------------------------------------------------
    //implementation to read to string
    void attribute_imp::read(type_id_t tid,void *ptr) const
    {
        if(!is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Cannot read data from invalid attribute!");

        //if the type is not a variable length string memory must be allocated
        //for each string in the attribute
        if(is_static_string(_dtype))
        {
            char_vector_type str_data(size()*static_string_size(_dtype));
            _read_data(_dtype,static_cast<void *>(str_data.data()));
            copy_from_vector(str_data,
                             size(),
                             static_string_size(_dtype),
                             static_cast<string*>(ptr));
        }
        else if(is_vl_string(_dtype))
        {
            char_ptr_vector_type str_pointers(size());
            _read_data(_dtype,static_cast<void *>(str_pointers.data()));
            copy_from_vector(str_pointers,size(),static_cast<string*>(ptr));
        }
        else
        {
            const h5datatype &mem_type = get_type(tid);
            _read_data(mem_type,ptr);
        }

    }

    //-------------------------------------------------------------------------
    void attribute_imp::_read_data(const h5datatype &memtype,void *ptr) const
    {
        if(H5Aread(_object.id(),memtype.object().id(),ptr)<0)
            throw io_error(EXCEPTION_RECORD,"Error reading attribute ["
                    +name()+"]!\n\n"+get_h5_error_string());
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
