//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
// Created on: Jan 11, 2013
// Authors:
//         Eugen Wintersberger <eugen.wintersberger@desy.de>
//         Jan Kotanski <jan.kotanski@desy.de>
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
#include <h5cpp/contrib/nexus/ebool.hpp>

namespace pni{


    //forward declaration
    class value_ref;

    //!
    //! \ingroup type_erasure_classes
    //!\brief type erasure for POD data
    //!
    class PNINEXUS_EXPORT value
    {
        private:
            //! internal pointer type 
            using pointer_type = std::unique_ptr<value_holder_interface>;

            template<typename GeneralT>
            using enable_primitive = std::enable_if<is_primitive_type<GeneralT>::value>;
            
            //----------------------------------------------------------------
            //! 
            //! \brief return value
            //!
            //! Return the value of the variable the reference refers to. 
            //! TargetT denotes the data type requested by the  user. SourceT denotes 
            //! the type of the variable the reference points to.
            //! 
            //! \throws type_error if the conversion is not possible
            //! \throws range_error if the value 
            //! \tparam TargetT target type
            //! \tparam SourceT source type
            //! \return value as TargetT
            //!
            template<
                     typename TargetT,
                     typename SourceT 
                    > 
            TargetT _get() const
            {
                return get_value<TargetT,SourceT>(get_holder_ptr<SourceT>(_ptr));
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
            //! \tparam VariableT type of the variable
            //! \tparam UserValueT type of the value the user passed
            //! \param v value to set  
            template<
                     typename VariableT,
                     typename UserValueT
                    > 
            void _set(const UserValueT& v) const
            {
                return set_value<VariableT,UserValueT>(get_holder_ptr<VariableT>(_ptr),v);
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
            //! This constructor accepts all primitive types from libpninexus.
            //!
            //! \tparam PrimitiveT primitive type
            //! \param v value to store in the type erasure
            //! 
            template<
                     typename PrimitiveT,
                     typename = typename enable_primitive<PrimitiveT>::type 
                    > 
            explicit value(PrimitiveT v):_ptr(new value_holder<PrimitiveT>(v)){}

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
            template<typename ValueT> value &operator=(const ValueT &v);

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
            //! Return the stored value as type TargetT. If the value instance has 
            //! not been initialized before an exception is thrown. In 
            //! addition, if the data type passed as a template parameter 
            //! does not fit the type used to store the data an exception 
            //! will be thrown.
            //!
            //! \throws memory_not_allocate_error if value is uninitialized
            //! \throws type_error if TargetT does not match the original data type
            //! \throws range_error if the value stored does not fit into the 
            //! requested type.
            //! \return value of type TargetT 
            //!
            template<typename TargetT> TargetT as() const;

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
    template<typename TargetT> TargetT value::as() const
    {
        type_id_t tid = type_id();
        switch(tid)
        {
            case type_id_t::UInt8:      return _get<TargetT,uint8>();
            case type_id_t::Int8:       return _get<TargetT,int8>();
            case type_id_t::UInt16:     return _get<TargetT,uint16>();
            case type_id_t::Int16:      return _get<TargetT,int16>();
            case type_id_t::UInt32:     return _get<TargetT,uint32>();
            case type_id_t::Int32:      return _get<TargetT,int32>();
            case type_id_t::UInt64:     return _get<TargetT,uint64>();
            case type_id_t::Int64:      return _get<TargetT,int64>();
            case type_id_t::Float32:    return _get<TargetT,float32>();
            case type_id_t::Float64:    return _get<TargetT,float64>();
            case type_id_t::Float128:   return _get<TargetT,float128>();
            case type_id_t::Complex32:  return _get<TargetT,complex32>();
            case type_id_t::Complex64:  return _get<TargetT,complex64>();
            case type_id_t::Complex128: return _get<TargetT,complex128>(); 
            case type_id_t::String:     return _get<TargetT,string>();
            case type_id_t::Binary:     return _get<TargetT,binary>();
            case type_id_t::Bool:       return _get<TargetT,bool_t>();
            case type_id_t::EBool:      return _get<TargetT,hdf5::datatype::EBool>();
            default:
                throw type_error(EXCEPTION_RECORD,"Uknown type!");
        }

    }

    //-------------------------------------------------------------------------
    template<typename ValueT> value &value::operator=(const ValueT &v)
    {
        type_id_t tid = type_id();

        switch(tid)
        {
            case type_id_t::UInt8:      _set<uint8>(v);      break;
            case type_id_t::Int8:       _set<int8>(v);       break;
            case type_id_t::UInt16:     _set<uint16>(v);     break;
            case type_id_t::Int16:      _set<int16>(v);      break;
            case type_id_t::UInt32:     _set<uint32>(v);     break;
            case type_id_t::Int32:      _set<int32>(v);      break;
            case type_id_t::UInt64:     _set<uint64>(v);     break;
            case type_id_t::Int64:      _set<int64>(v);      break;
            case type_id_t::Float32:    _set<float32>(v);    break;
            case type_id_t::Float64:    _set<float64>(v);    break;
            case type_id_t::Float128:   _set<float128>(v);   break;
            case type_id_t::Complex32:  _set<complex32>(v);  break;
            case type_id_t::Complex64:  _set<complex64>(v);  break;
            case type_id_t::Complex128: _set<complex128>(v); break;
            case type_id_t::Binary:     _set<binary>(v);     break;
            case type_id_t::Bool:       _set<bool_t>(v);     break;
            case type_id_t::EBool:      _set<hdf5::datatype::EBool>(v);     break;
            case type_id_t::String:     _set<string>(v);     break;
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
    PNINEXUS_EXPORT type_id_t type_id(const value &rv);

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes
    //! \brief create value
    //! 
    //! Create a value instance for a particular type. 
    //!
    //! \tparam RequestedT requested type
    //! \return instance of value holding a value of RequestedT
    //!
    template<typename RequestedT> value make_value()
    {
        return value(RequestedT{});
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
    PNINEXUS_EXPORT value make_value(type_id_t tid);

//end of namespace
}

