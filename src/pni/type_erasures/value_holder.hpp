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
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/types/type_id_map.hpp>
#include <pni/type_erasures/value_holder_interface.hpp>

namespace pni{

    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief return reference
    //!
    //! Return the reference to its argument. This function template produces 
    //! no code. It just passes the reference through.
    //! 
    //! \tparam T type of the reference
    //! \param v input reference
    //! \return reference to the argument
    //!
    template<typename T> 
    T& get_ref(T &v) noexcept
    { 
        return v;
    } 

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief return const reference
    //!
    //! Return a const reference from a primitive type. 
    //!
    //! \tparam T primitive type
    //! \param v const reference to the primitive type
    //! \return const reference to T
    //!
    template<typename T> 
    const T& get_const_ref(const T &v) noexcept
    { 
        return v; 
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief return reference
    //!
    //! Return the reference stored in a std::reference_wrapper. 
    //! 
    //! \tparam T type wrapped by std::reference_wrapper
    //! \param v input reference
    //! \return reference to the argument
    //!
    template<typename T> 
    T& get_ref(std::reference_wrapper<T> &v) noexcept
    {
        return v.get();
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief return const reference
    //!
    //! Return a const reference stored in a std::reference_wrapper. 
    //! 
    //! \tparam T type wrapped by std::reference_wrapper
    //! \param v const reference 
    //! \return reference to the argument
    //!
    template<typename T> 
    const T& get_const_ref(const std::reference_wrapper<T> &v) noexcept
    {
        return v.get();
    }


    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_clases_internal
    //! \brief check if type is reference
    //!
    //! Value is true if T is a reference type (an instance f the
    //! std::reference_wrapper<T> template). In this default case the value 
    //! member is set to false.
    //!
    template<typename T> struct is_reference_holder
    {
        //! value set to false
        static const bool value = false;
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief chef if type is reference
    //!
    //! Specialization of the is_reference_holder template. In this case the 
    //! value member is set to true.
    //!
    template<typename T> struct is_reference_holder<std::reference_wrapper<T> >
    {
        //! value set to true
        static const bool value = true;
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief get original type of reference
    //!
    //! In this case T is just pushed through.
    //!
    template<typename T> struct get_reference_type
    {
        //! original reference type
        typedef T value_type;
        //! reference type
        typedef T &reference_type;
        //! const reference type
        typedef const T &const_reference_type;
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief get the original type of reference
    //!
    //! In this case value_type is T which is the template parameter of the 
    //! original std::reference_wrapper<> template.
    //!
    template<typename T> struct get_reference_type<std::reference_wrapper<T> >
    {
        //! original reference type
        typedef T value_type;
        //! reference type
        typedef T &reference_type;
        //! const reference type
        typedef const  T &const_reference_type;
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief implementation of the holder interface
    //! 
    //! This template implements the holder interface for the value class.
    //! \tparam T type of the data wrapped
    //!
    template<typename T> 
    class value_holder : public value_holder_interface
    {
        private:
            T _value; //!< the data value

        public:
            //----------------------------------------------------------------
            //!
            //! default constructor
            //!
            value_holder():_value(T(0)) {}

            //----------------------------------------------------------------
            //!
            //! \brief constructor 
            //! 
            //! Construct a value_holder instance from a concrete value of 
            //! type T. 
            //! 
            //! \param v value from which to construct the holder
            //!
            value_holder(T v):_value(v) {}


            //====================public inerface implementation==============
            //!
            //! \brief get type id of data
            //!
            //! \return type ID of the value stored in this holder instance 
            //! 
            virtual type_id_t type_id() const noexcept
            {
                typedef typename get_reference_type<T>::value_type value_type;
                return type_id_map<value_type >::type_id;
            }

            //----------------------------------------------------------------
            //!
            //! \brief clone holder instance
            //!
            //! \return pointer to a new instance of value holder 
            //! 
            virtual value_holder_interface *clone() const
            {
                return new value_holder<T>(_value);
            }

            //----------------------------------------------------------------
            //!
            //! \brief return value
            //!
            //! Return the value stored.
            //!
            //! \return value of type T
            //!
            typename get_reference_type<T>::value_type as() const 
            { 
                return get_const_ref(_value);
            } 

            //----------------------------------------------------------------
            //! 
            //! \brief get reference 
            //! 
            //! \return reference to the stored value
            //! 
            typename get_reference_type<T>::reference_type as()
            {
                return get_ref(_value);
            }

            //----------------------------------------------------------------
            //!
            //! \brief check if holder stores a reference
            //!
            //! \return true if a reference is stored, false otherwise 
            //! 
            virtual bool holds_reference() const
            {
                return is_reference_holder<T>::value;
            }
    };


//end of namespace
}
