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
         _dtype(),
         _selection(),
         _apply_selection(false)
    {}
    
    //-------------------------------------------------------------------------
    attribute_imp::attribute_imp(object_imp &&object)
        :_object(std::move(object)),
         _dspace(),
         _dtype(),
         _selection(),
         _apply_selection(false)
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
        if(!is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Cannot obtain shape from an invalid object!");

        if(_apply_selection)
            return effective_shape(_selection);
        else
            return _dspace.shape();
    }
    
    //-------------------------------------------------------------------------
    size_t attribute_imp::size() const 
    { 
        if(!is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Cannot obtain size from an invalid attribute!");

        if(_apply_selection)
            return pni::io::nx::h5::size(_selection);
        else
            return _dspace.size(); 
    }

    //-------------------------------------------------------------------------
    size_t attribute_imp::rank() const 
    { 
        if(!is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Cannot obtain rank from an invalid attribute!");
        
        if(_apply_selection)
            return effective_rank(_selection);
        else
            return _dspace.rank(); 
    }
    //-------------------------------------------------------------------------
    // Implementation of IO related methods
    //-------------------------------------------------------------------------
    void attribute_imp::_to_disk(const h5datatype &memtype,
                                 const void *ptr) const
    {
        if(H5Awrite(_object.id(),memtype.object().id(),ptr)<0)
            throw io_error(EXCEPTION_RECORD,
                    "Error writing attribute ["+name()+"]!\n\n"
                    +get_h5_error_string());

    }

    //------------------------------------------------------------------------
    void attribute_imp::_write_all(type_id_t tid,const void *ptr) const
    {

        if(tid==type_id_t::STRING)
        {
            auto s = static_cast<const string*>(ptr);
            std::vector<const char*> ptrs(_dspace.size());
            for(size_t i=0;i<_dspace.size();i++) ptrs[i] = s[i].data();
            _to_disk(_dtype,static_cast<const void*>(ptrs.data()));
        }
        else
        {
            const h5datatype &mem_type = get_type(tid);
            _to_disk(mem_type,ptr);
        }
    }
    
    //-------------------------------------------------------------------------
    void attribute_imp::_from_disk(const h5datatype &memtype,void *ptr) const
    {
        if(H5Aread(_object.id(),memtype.object().id(),ptr)<0)
            throw io_error(EXCEPTION_RECORD,"Error reading attribute ["
                    +name()+"]!\n\n"+get_h5_error_string());
    }
    
    //-------------------------------------------------------------------------
    void attribute_imp::write(type_id_t tid,const void *ptr) const
    {
        if(!is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Cannot write data to invalid attribut!");

        if(_apply_selection)
            _write_selection(tid,ptr);
        else 
            _write_all(tid,ptr);
    }


    //-------------------------------------------------------------------------
    void attribute_imp::_write_selection(type_id_t tid,const void *ptr) const
    {
        //first we have to readback data
        if(tid == type_id_t::UINT8)
            _write_selection_typed<uint8>(tid,(uint8*)ptr);
        else if(tid == type_id_t::INT8)
            _write_selection_typed<int8>(tid,(int8*)ptr);
        else if(tid == type_id_t::UINT16)
            _write_selection_typed<uint16>(tid,(uint16*)ptr);
        else if(tid == type_id_t::INT16)
            _write_selection_typed<int16>(tid,(int16*)ptr);
        else if(tid == type_id_t::UINT32)
            _write_selection_typed<uint32>(tid,(uint32*)ptr);
        else if(tid == type_id_t::INT32)
            _write_selection_typed<int32>(tid,(int32*)ptr);
        else if(tid == type_id_t::UINT64)
            _write_selection_typed<uint64>(tid,(uint64*)ptr);
        else if(tid == type_id_t::INT64)
            _write_selection_typed<int64>(tid,(int64*)ptr);
        else if(tid == type_id_t::FLOAT32)
            _write_selection_typed<float32>(tid,(float32*)ptr);
        else if(tid == type_id_t::FLOAT64)
            _write_selection_typed<float64>(tid,(float64*)ptr);
        else if(tid == type_id_t::FLOAT128)
            _write_selection_typed<float128>(tid,(float128*)ptr);
        else if(tid == type_id_t::COMPLEX32)
            _write_selection_typed<complex32>(tid,(complex32*)ptr);
        else if(tid == type_id_t::COMPLEX64)
            _write_selection_typed<complex64>(tid,(complex64*)ptr);
        else if(tid == type_id_t::COMPLEX128)
            _write_selection_typed<complex128>(tid,(complex128*)ptr);
        else if(tid == type_id_t::BOOL)
            _write_selection_typed<bool_t>(tid,(bool_t*)ptr);
        else if(tid == type_id_t::STRING)
            _write_selection_typed<string>(tid,(string*)ptr);
        else if(tid == type_id_t::BINARY)
            _write_selection_typed<binary>(tid,(binary*)ptr);
        else 
            type_error(EXCEPTION_RECORD,"");

    }


    //-------------------------------------------------------------------------
    //implementation to read to string
    void attribute_imp::read(type_id_t tid,void *ptr) const
    {
        if(!is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Cannot read data from invalid attribute!");

        if(_apply_selection)
            _read_selection(tid,ptr);
        else
            _read_all(tid,ptr);
    }

    //------------------------------------------------------------------------
    void attribute_imp::_read_all(type_id_t tid,void *ptr) const
    {
        //if the type is not a variable length string memory must be allocated
        //for each string in the attribute
        const h5datatype &mem_type = get_type(tid);

        if(is_static_string(_dtype))
        {
            char_vector_type str_data(_dspace.size()*static_string_size(_dtype));
            _from_disk(_dtype,static_cast<void *>(str_data.data()));
            copy_from_vector(str_data,
                             _dspace.size(),
                             static_string_size(_dtype),
                             static_cast<string*>(ptr));
        }
        else if(is_vl_string(_dtype))
        {
            char_ptr_vector_type str_pointers(_dspace.size());
            _from_disk(_dtype,static_cast<void *>(str_pointers.data()));
            copy_from_vector(str_pointers,_dspace.size(),static_cast<string*>(ptr));
        }
        else
        {
            _from_disk(mem_type,ptr);
        }

    }


    //------------------------------------------------------------------------
    void attribute_imp::_read_selection(type_id_t tid,void *ptr) const
    {
        //first we have to readback data
        if(tid == type_id_t::UINT8)
            _read_selection_typed<uint8>(tid,(uint8*)ptr);
        else if(tid == type_id_t::INT8)
            _read_selection_typed<int8>(tid,(int8*)ptr);
        else if(tid == type_id_t::UINT16)
            _read_selection_typed<uint16>(tid,(uint16*)ptr);
        else if(tid == type_id_t::INT16)
            _read_selection_typed<int16>(tid,(int16*)ptr);
        else if(tid == type_id_t::UINT32)
            _read_selection_typed<uint32>(tid,(uint32*)ptr);
        else if(tid == type_id_t::INT32)
            _read_selection_typed<int32>(tid,(int32*)ptr);
        else if(tid == type_id_t::UINT64)
            _read_selection_typed<uint64>(tid,(uint64*)ptr);
        else if(tid == type_id_t::INT64)
            _read_selection_typed<int64>(tid,(int64*)ptr);
        else if(tid == type_id_t::FLOAT32)
            _read_selection_typed<float32>(tid,(float32*)ptr);
        else if(tid == type_id_t::FLOAT64)
            _read_selection_typed<float64>(tid,(float64*)ptr);
        else if(tid == type_id_t::FLOAT128)
            _read_selection_typed<float128>(tid,(float128*)ptr);
        else if(tid == type_id_t::COMPLEX32)
            _read_selection_typed<complex32>(tid,(complex32*)ptr);
        else if(tid == type_id_t::COMPLEX64)
            _read_selection_typed<complex64>(tid,(complex64*)ptr);
        else if(tid == type_id_t::COMPLEX128)
            _read_selection_typed<complex128>(tid,(complex128*)ptr);
        else if(tid == type_id_t::BOOL)
            _read_selection_typed<bool_t>(tid,(bool_t*)ptr);
        else if(tid == type_id_t::STRING)
            _read_selection_typed<string>(tid,(string*)ptr);
        else if(tid == type_id_t::BINARY)
            _read_selection_typed<binary>(tid,(binary*)ptr);
        else 
            type_error(EXCEPTION_RECORD,"");


    } 

    //-------------------------------------------------------------------------
    void attribute_imp::close()
    {
        _object.close();
    }

    //------------------------------------------------------------------------
    void attribute_imp::apply_selection(const type_imp::selection_vector_type &s)
    {
        _selection = create_selection(s);
        _apply_selection = true;
    }

    //------------------------------------------------------------------------
    void attribute_imp::clear_selection()
    {
        _selection = selection();
        _apply_selection = false;
    }
           

//end of namespace
}
}
}
}
