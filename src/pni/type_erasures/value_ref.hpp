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
#include <h5cpp/contrib/nexus/ebool.hpp>
#include <pni/windows.hpp>

namespace pni{

    class value;

    //!
    //! \ingroup type_erasure_classes
    //! \brief type erasure for references to POD data
    //!
    //!
    class PNINEXUS_EXPORT value_ref
    {
        private:
            //! internal pointer type used to hold the reference instance
            typedef std::unique_ptr<value_holder_interface> pointer_type;

            //----------------------------------------------------------------
            //!
            //! \brief throw exception
            //!
            //! Static helper method that throws a memory_not_allocated_error 
            //! if the type erasure holds no data and data access is 
            //! requested by the user.
            //! 
            //! \throw memory_not_allocated_error
            //! \param r exception record where the error occurred.
            //!
            void _check_pointer(const exception_record &r) const;

            //----------------------------------------------------------------
            //!
            //! \brief check type
            //!
            //! Throws type_error exception if the passed type id does not match
            //! the references original type. 
            //!
            //! \throw type_error 
            //! \param tid type id to check
            //! \param r exception record of the code position 
            //!
            void _check_type(type_id_t tid,const exception_record &r) const;

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
            //! \tparam TargetT target type
            //! \tparam SourceT source type
            //! \return value as T
            //!
            template<
                     typename TargetT,
                     typename SourceT 
                    > 
            TargetT _get() const
            {
                return get_value<TargetT,SourceT>(get_holder_ptr<ref_type<SourceT>>(_ptr));
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
            //! 
            template<
                     typename VariableT,
                     typename UserValueT
                    > 
            void _set(const UserValueT& v) const
            {
                return set_value<VariableT,UserValueT>(get_holder_ptr<ref_type<VariableT>>(_ptr),v);
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
            //!
            //! \brief default constructor
            //! 
            value_ref();
          
            //-----------------------------------------------------------------
            //! 
            //! \brief template constructor from value
            //!
            //! Constructs a reference to a variable of type ValueT. 
            /*!
            \code
            float32 x = 100.;
            value_ref v(std::ref(x));
            \endcode
            !*/
            //! \tparam ValueT type of the value to which the reference shall be created
            //! \param v reference to the value
            //!
            template<typename ValueT>
            explicit value_ref(std::reference_wrapper<ValueT> v):
                _ptr(new value_holder<std::reference_wrapper<ValueT> >(v))
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief copy constructor
            //!
            value_ref(const value_ref &o);

            //==================assignment operators===========================
            //! 
            //! \brief assign value to the variable
            //!
            //! Assign a value of type ValueT to the target of the reference. 
            //! If ValueT differs from the original type of the target the data will 
            //! be converted. 
            //! 
            //! \throws memory_not_allocated_error if the reference is not 
            //! initialized 
            //! \throws type_error if conversion is not possible 
            //! \throws range_error if the value does not fit into the target
            //! type.
            //!
            //! \param v reference to the new value
            //! \return instance of value
            //!
            template<typename ValueT> value_ref &operator=(const ValueT &v);

            //----------------------------------------------------------------
            //!
            //! \brief assignment from a value
            //!
            //! In this case the value stored in v will be assigned to the
            //! variable refered to by this instance of value_ref.
            //! If the data types do not match a type conversion takes place 
            //! if necessary.
            //!
            //! \throws memory_not_allocated if the reference is not initialized
            //! \throws type_error if the type of v and the reference to not
            //!                    match
            //! \throws range_error if the value of v does not fit in the type 
            //!                     of the variable referenced by this 
            //!                     instance of value_ref.
            //! 
            //! \param v value instance
            //! \return reference to this instance
            //!
            value_ref &operator=(const value &v);

            //-----------------------------------------------------------------
            //! copy assignment
            // we should remove this - makes not really sense. We can 
            // always destroy the reference and create a new one (could we?)
            value_ref &operator=(const value_ref &o);

            //-----------------------------------------------------------------
            //!
            //! \brief conversion operator
            //! 
            //! This operator is used to convert a reference to a value 
            //! type erasure. 
            //! 
            operator value () const;

            //-----------------------------------------------------------------
            //!
            //! \brief get the referenced value
            //!
            //! Returns the value of the variable the value_ref instance 
            //! points to. If the type requested by the user via the template
            //! parameter ReturnT is different from the type of the variable value_ref
            //! points to the data will be converted if possible. 
            //! If the conversion fails or is not possible an exception will 
            //! be thrown. 
            //! 
            //! \throws memory_not_allocated_error if value is uninitialized
            //! \throws type_error if data cannot be converted to ReturnT
            //! \throws range_error if data does not fit into the range of ReturnT 
            //! \return value of type ReturnT 
            //!
            template<typename ReturnT> ReturnT as() const;

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

    //======================implementation of template members=================
    template<typename ReturnT> ReturnT value_ref::as() const
    {
        //check if the reference points to something
        _check_pointer(EXCEPTION_RECORD);

        type_id_t tid = type_id();
        switch(tid)
        {
            case type_id_t::UInt8:      return _get<ReturnT,uint8>();
            case type_id_t::Int8:       return _get<ReturnT,int8>();
            case type_id_t::UInt16:     return _get<ReturnT,uint16>();
            case type_id_t::Int16:      return _get<ReturnT,int16>();
            case type_id_t::UInt32:     return _get<ReturnT,uint32>();
            case type_id_t::Int32:      return _get<ReturnT,int32>();
            case type_id_t::UInt64:     return _get<ReturnT,uint64>();
            case type_id_t::Int64:      return _get<ReturnT,int64>();
            case type_id_t::Float32:    return _get<ReturnT,float32>();
            case type_id_t::Float64:    return _get<ReturnT,float64>();
            case type_id_t::Float128:   return _get<ReturnT,float128>();
            case type_id_t::Complex32:  return _get<ReturnT,complex32>();
            case type_id_t::Complex64:  return _get<ReturnT,complex64>();
            case type_id_t::Complex128: return _get<ReturnT,complex128>();
            case type_id_t::Binary:     return _get<ReturnT,binary>();
            case type_id_t::String:     return _get<ReturnT,string>();
            case type_id_t::Bool:       return _get<ReturnT,bool_t>();
            case type_id_t::EBool:       return _get<ReturnT,hdf5::datatype::EBool>();
            default:
                throw type_error(EXCEPTION_RECORD,
                        "The reference points to an object of unkown type!");
        }
        
    }
           
    //-------------------------------------------------------------------------
    template<typename ReturnT> value_ref &value_ref::operator=(const ReturnT &v)
    {
        _check_pointer(EXCEPTION_RECORD);
        
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
            case type_id_t::String:     _set<string>(v);     break;
            case type_id_t::Bool:       _set<bool_t>(v);     break;
            case type_id_t::EBool:      _set<hdf5::datatype::EBool>(v);     break;
            default:
                throw type_error(EXCEPTION_RECORD,
                        "The reference points to an object of unknown type!");
        }

        return *this;
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes
    //! \brief conversion function to value
    //!
    //! This function extracts the value stored in the variable referenced by 
    //! value_ref and stores it in a new instance of value. 
    //!
    //! \throws memory_not_allocated_error if the reference is not set
    //! \throws type_error if the type of the variable referenced by value_ref 
    //! is unknown
    //!
    //! \param v reference to value_ref
    //! \return instance of value with the content of value_ref
    //!
    PNINEXUS_EXPORT value to_value(const value_ref &v);

//end of namespace
}

