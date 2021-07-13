//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
// Created on: Jan 11, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/type_erasures/array.hpp>

namespace pni{
namespace core{

    //copy constructor
    array::array(const array &e):_ptr(e._ptr ? e._ptr->clone():nullptr)
    {
        //std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    }

    //-------------------------------------------------------------------------
    //move constructor
    array::array(array &&e):_ptr(std::move(e._ptr))
    {
        //std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    }

    //-------------------------------------------------------------------------
    //copy assignment operator
    array &array::operator=(const array &a)
    {
        if(&a == this) return *this;

        this->_ptr = std::unique_ptr<array_holder_interface>(a._ptr->clone());
        return *this;
    }

    //-------------------------------------------------------------------------
    //move assignment operator
    array &array::operator=(array &&a)
    {
        if(&a == this) return *this;

        this->_ptr = std::move(a._ptr);
        return *this;
    }

    //-------------------------------------------------------------------------
    type_id_t array::type_id() const
    { 
        _check_pointer(_ptr,EXCEPTION_RECORD);
        return _ptr->type_id(); 
    }

    //-------------------------------------------------------------------------
    size_t array::rank() const 
    {
        _check_pointer(_ptr,EXCEPTION_RECORD);
        return _ptr->rank(); 
    }
        
    //-------------------------------------------------------------------------
    shape_t array::shape() const 
    {
        _check_pointer(_ptr,EXCEPTION_RECORD);
        return _ptr->shape(); 
    }

    //-------------------------------------------------------------------------
    size_t array::size() const 
    {
        _check_pointer(_ptr,EXCEPTION_RECORD);
        return _ptr->size(); 
    }

    //-------------------------------------------------------------------------
    value array::operator[](size_t i) const
    {
        _check_pointer(_ptr,EXCEPTION_RECORD);
        return ((const array_holder_interface&)(*_ptr))[i];
    }

    //-------------------------------------------------------------------------
    value array::at(size_t i) const
    {
        _check_pointer(_ptr,EXCEPTION_RECORD);
        return value(_ptr->at(i));
    }

    //-------------------------------------------------------------------------
    value_ref array::operator[](size_t i) 
    {
        _check_pointer(_ptr,EXCEPTION_RECORD);
        return (*_ptr)[i];
    }

    //-------------------------------------------------------------------------
    value_ref array::at(size_t i)
    {
        _check_pointer(_ptr,EXCEPTION_RECORD);
        return _ptr->at(i);
    }

    //-------------------------------------------------------------------------
    value_ref array::operator()(const element_index &index)
    {
        _check_pointer(_ptr,EXCEPTION_RECORD);
        return (*_ptr)(index);
    }

    //-------------------------------------------------------------------------
    value array::operator()(const element_index &index) const
    {
        _check_pointer(_ptr,EXCEPTION_RECORD);
        return const_cast<const array_holder_interface &>((*_ptr))(index);
    }

    //-------------------------------------------------------------------------
    string array::type_name() const
    {
        _check_pointer(_ptr,EXCEPTION_RECORD);
        return _ptr->type_name();
    }

    //-------------------------------------------------------------------------
    const void *array::data() const
    {
        _check_pointer(_ptr,EXCEPTION_RECORD);
        return _ptr->ptr();
    }
    
    //-------------------------------------------------------------------------
    void *array::data() 
    {
        _check_pointer(_ptr,EXCEPTION_RECORD);
        return const_cast<void*>(_ptr->ptr());
    }
   
    //-------------------------------------------------------------------------
    type_id_t type_id(const array &a)
    {
        return a.type_id();
    }


//end of namespace
}
}
