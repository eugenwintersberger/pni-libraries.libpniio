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
    //! \tparam GeneralT type of the reference
    //! \param v input reference
    //! \return reference to the argument
    //!
    template<typename GeneralT> 
    GeneralT& get_ref(GeneralT &v) noexcept
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
    //! \tparam PrimitiveT primitive type
    //! \param v const reference to the primitive type
    //! \return const reference to PrimitiveT
    //!
    template<typename PrimitiveT> 
    const PrimitiveT& get_const_ref(const PrimitiveT &v) noexcept
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
    //! \tparam GeneralT type wrapped by std::reference_wrapper
    //! \param v input reference
    //! \return reference to the argument
    //!
    template<typename GeneralT> 
    GeneralT& get_ref(std::reference_wrapper<GeneralT> &v) noexcept
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
    template<typename GeneralT> 
    const GeneralT& get_const_ref(const std::reference_wrapper<GeneralT> &v) noexcept
    {
        return v.get();
    }


    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_clases_internal
    //! \brief check if type is reference
    //!
    //! Value is true if GeneralT is a reference type (an instance f the
    //! std::reference_wrapper<GeneralT> template). In this default case the value 
    //! member is set to false.
    //!
    template<typename GeneralT> struct is_reference_holder
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
    template<typename GeneralT> struct is_reference_holder<std::reference_wrapper<GeneralT> >
    {
        //! value set to true
        static const bool value = true;
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief get original type of reference
    //!
    //! In this case GeneralT is just pushed through.
    //!
    template<typename GeneralT> struct get_reference_type
    {
        //! original reference type
        typedef GeneralT value_type;
        //! reference type
        typedef GeneralT &reference_type;
        //! const reference type
        typedef const GeneralT &const_reference_type;
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief get the original type of reference
    //!
    //! In this case value_type is GeneralT which is the template parameter of the 
    //! original std::reference_wrapper<> template.
    //!
    template<typename GeneralT> struct get_reference_type<std::reference_wrapper<GeneralT> >
    {
        //! original reference type
        typedef GeneralT value_type;
        //! reference type
        typedef GeneralT &reference_type;
        //! const reference type
        typedef const  GeneralT &const_reference_type;
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief implementation of the holder interface
    //! 
    //! This template implements the holder interface for the value class.
    //! \tparam GeneralT type of the data wrapped
    //!
    template<typename GeneralT> 
    class value_holder : public value_holder_interface
    {
        private:
            GeneralT _value; //!< the data value

        public:
            //----------------------------------------------------------------
            //!
            //! default constructor
            //!
            value_holder():_value(GeneralT(0)) {}

            //----------------------------------------------------------------
            //!
            //! \brief constructor 
            //! 
            //! Construct a value_holder instance from a concrete value of 
            //! type GeneralT. 
            //! 
            //! \param v value from which to construct the holder
            //!
            value_holder(GeneralT v):_value(v) {}


            //====================public inerface implementation==============
            //!
            //! \brief get type id of data
            //!
            //! \return type ID of the value stored in this holder instance 
            //! 
            virtual type_id_t type_id() const noexcept
            {
                typedef typename get_reference_type<GeneralT>::value_type value_type;
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
                return new value_holder<GeneralT>(_value);
            }

            //----------------------------------------------------------------
            //!
            //! \brief return value
            //!
            //! Return the value stored.
            //!
            //! \return value of type GeneralT
            //!
            typename get_reference_type<GeneralT>::value_type as() const 
            { 
                return get_const_ref(_value);
            } 

            //----------------------------------------------------------------
            //! 
            //! \brief get reference 
            //! 
            //! \return reference to the stored value
            //! 
            typename get_reference_type<GeneralT>::reference_type as()
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
                return is_reference_holder<GeneralT>::value;
            }
    };


//end of namespace
}
