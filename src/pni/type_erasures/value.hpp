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
// ============================================================================
//
// Created on: Jan 11, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include<iostream>
#include<memory>

#include <pni/error/exceptions.hpp>
#include <pni/types/types.hpp>
#include <pni/type_erasures/value_holder.hpp>
#include <pni/type_erasures/utils.hpp>
#include <pni/types/traits.hpp>
#include <pni/windows.hpp>

namespace pni{
namespace core{


    //forward declaration
    class value_ref;

    //!
    //! \ingroup type_erasure_classes
    //!\brief type erasure for POD data
    //!
    class PNIIO_EXPORT value
    {
        private:
            //! internal pointer type 
            using pointer_type = std::unique_ptr<value_holder_interface>;

            template<typename T>
            using enable_primitive = std::enable_if<is_primitive_type<T>::value>;
            
            //----------------------------------------------------------------
            //! 
            //! \brief return value
            //!
            //! Return the value of the variable the reference refers to. 
            //! T denotes the data type requested by the  user. S denotes 
            //! the type of the variable the reference points to.
            //! 
            //! \throws type_error if the conversion is not possible
            //! \throws range_error if the value 
            //! \tparam T target type
            //! \tparam S source type
            //! \return value as T
            //!
            template<
                     typename T,
                     typename S 
                    > 
            T _get() const
            {
                return get_value<T,S>(get_holder_ptr<S>(_ptr));
            }

            //----------------------------------------------------------------
            //!
            //! \brief set value
            //! 
            //! Sets the value of the variable the reference points to. 
            //!
            //! \throws type_error if the conversion is not possible
            //! \throws range_error if the passed value does not fit in the
            //! target type
            //! \tparam S type of the variable
            //! \tparam T type of the value the user passed
            //! \param v value to set  
            template<
                     typename S,
                     typename T
                    > 
            void _set(const T& v) const
            {
                return set_value<S,T>(get_holder_ptr<S>(_ptr),v);
            }

            //! pointer holding the value stored
#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif
            pointer_type _ptr;
#ifdef _MSC_VER
#pragma warning(default:4251)
#endif
        public:
            //================constructors and destructor======================
            //! default constructor
            value();
          
            //-----------------------------------------------------------------
            //! 
            //! \brief  template constructor from value
            //!
            //! This constructor accepts all primitive types from libpnicore.
            //!
            //! \tparam T primitive type
            //! \param v value to store in the type erasure
            //! 
            template<
                     typename T,
                     typename = typename enable_primitive<T>::type 
                    > 
            explicit value(T v):_ptr(new value_holder<T>(v)){}

            //-----------------------------------------------------------------
            //!
            //! \brief copy constructor
            //!
            value(const value &o);

            //-----------------------------------------------------------------
            //! 
            //! \brief move constructor
            //!
            value(value &&o);

            //==================assignment operators===========================
            //! 
            //! \brief copy assignment from value
            //!
            //! \param v reference to the new value
            //! \return instance of value
            //!
            template<typename VT> value &operator=(const VT &v);

            //-----------------------------------------------------------------
            //! copy assignment
            value &operator=(const value &o);

            //-----------------------------------------------------------------
            //! move assignment operator
            value &operator=(value &&o);

            //----------------------------------------------------------------
            //! copy construction from a value reference
            value &operator=(const value_ref &v);

            //-----------------------------------------------------------------
            //!
            //! \brief get the stored value
            //!
            //! Return the stored value as type T. If the value instance has 
            //! not been initialized before an exception is thrown. In 
            //! addition, if the data type passed as a template parameter 
            //! does not fit the type used to store the data an exception 
            //! will be thrown.
            //!
            //! \throws memory_not_allocate_error if value is uninitialized
            //! \throws type_error if T does not match the original data type
            //! \throws range_error if the value stored does not fit into the 
            //! requested type.
            //! \return value of type T 
            //!
            template<typename T> T as() const;

            //-----------------------------------------------------------------
            //!
            //! \brief get type id
            //!
            //! Returns the ID of the stored data type. 
            //! 
            //! \throws memory_not_allocated_error if value is not initialized
            //! \return type ID.
            //!
            type_id_t type_id() const;
    };

    //=====================implementation of template member functions=========
    template<typename T> T value::as() const
    {
        type_id_t tid = type_id();

        switch(tid)
        {
            case type_id_t::UINT8:      return _get<T,uint8>();
            case type_id_t::INT8:       return _get<T,int8>();
            case type_id_t::UINT16:     return _get<T,uint16>();
            case type_id_t::INT16:      return _get<T,int16>();
            case type_id_t::UINT32:     return _get<T,uint32>();
            case type_id_t::INT32:      return _get<T,int32>();
            case type_id_t::UINT64:     return _get<T,uint64>();
            case type_id_t::INT64:      return _get<T,int64>();
            case type_id_t::FLOAT32:    return _get<T,float32>();
            case type_id_t::FLOAT64:    return _get<T,float64>();
            case type_id_t::FLOAT128:   return _get<T,float128>();
            case type_id_t::COMPLEX32:  return _get<T,complex32>();
            case type_id_t::COMPLEX64:  return _get<T,complex64>();
            case type_id_t::COMPLEX128: return _get<T,complex128>(); 
            case type_id_t::STRING:     return _get<T,string>();
            case type_id_t::BINARY:     return _get<T,binary>();
            case type_id_t::BOOL:       return _get<T,bool_t>();
            default:
                throw type_error(EXCEPTION_RECORD,"Uknown type!");
        }

    }

    //-------------------------------------------------------------------------
    template<typename VT> value &value::operator=(const VT &v)
    {
        type_id_t tid = type_id();

        switch(tid)
        {
            case type_id_t::UINT8:      _set<uint8>(v);      break;
            case type_id_t::INT8:       _set<int8>(v);       break;
            case type_id_t::UINT16:     _set<uint16>(v);     break;
            case type_id_t::INT16:      _set<int16>(v);      break;
            case type_id_t::UINT32:     _set<uint32>(v);     break;
            case type_id_t::INT32:      _set<int32>(v);      break;
            case type_id_t::UINT64:     _set<uint64>(v);     break;
            case type_id_t::INT64:      _set<int64>(v);      break;
            case type_id_t::FLOAT32:    _set<float32>(v);    break;
            case type_id_t::FLOAT64:    _set<float64>(v);    break;
            case type_id_t::FLOAT128:   _set<float128>(v);   break;
            case type_id_t::COMPLEX32:  _set<complex32>(v);  break;
            case type_id_t::COMPLEX64:  _set<complex64>(v);  break;
            case type_id_t::COMPLEX128: _set<complex128>(v); break;
            case type_id_t::BINARY:     _set<binary>(v);     break;
            case type_id_t::BOOL:       _set<bool_t>(v);     break;
            case type_id_t::STRING:     _set<string>(v);     break;
            default:
                throw type_error(EXCEPTION_RECORD,
                        "Value is of unkonw type!");
        }

        return *this;
    }

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup type_erasure_classes
    //! \brief get type ID
    //! 
    //! Overload of type_id to obtain the type ID of the element stored in the 
    //! type erasure.
    //! 
    //! \param rv reference to value 
    //! \return type ID of the erased type
    //!
    PNIIO_EXPORT type_id_t type_id(const value &rv);

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes
    //! \brief create value
    //! 
    //! Create a value instance for a particular type. 
    //!
    //! \tparam T requested type
    //! \return instance of value holding a value of T
    //!
    template<typename T> value make_value()
    {
        return value(T{});
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes
    //! \brief create value
    //! 
    //! Create a value instance for a particular type. Here the type is entirely
    //! determined by its type ID. 
    //!
    //! \throws type_error if the type ID is now known
    //! \param tid type ID of the requested type
    //! \return instance of value holding data of type tid  
    //!
    PNIIO_EXPORT value make_value(type_id_t tid);

//end of namespace
}
}

