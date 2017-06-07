//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jan 30, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <sstream>

#include<pni/core/types.hpp>


namespace pni{
namespace io{

    //!
    //! \ingroup parser_internal_classes
    //! \brief default conversion trait
    //!
    //! Conversion trait used to convert parsed data to the requested
    //! type. In this default version nothing has to be done as the
    //! type read from the string is the same as the type requested by
    //! the user.
    //!
    //! \tparam T result type
    //!
    template<typename T>
    struct conversion_trait
    {
        //! the type requested by the user
        typedef T result_type;
        //! the type to read
        typedef T read_type;

        //!
        //! \brief conversion function
        //!
        //! Conversion function taking an rvalue reference.
        //!
        //! \param v rvalue reference for type to convert
        //! \return new value of type result_type
        //!
        static result_type convert(read_type &&v)
        {
            return v;
        }

        //--------------------------------------------------------------------
        //!
        //! \brief conversion function
        //!
        //! Conversion function taking an lvalue reference to the source
        //! value.
        //!
        //! \param v lvalue reference to the value to convert
        //! \return new value of type result_type
        //!
        static result_type convert(const read_type &v)
        {
            return v;
        }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup parser_internal_classes
    //! \brief uint8 conversion trait
    //!
    //! Specialization of the conversion_trait template for the uint8 type.
    //! In this special case uint16 is used for parsing the data.
    //!
    template<>
    struct conversion_trait<pni::core::uint8>
    {
        //! the type requested by the user
        typedef pni::core::uint8  result_type;
        //! the type to read
        typedef pni::core::uint16 read_type;

        //------------------------------------------------------------------
        //!
        //! \brief convert uint16 to uint8
        //!
        //! Takes an rvalue reference to an uint16 value and converts it to
        //! uint8. If the value of the input exceeds the numeric range of
        //! uint8 a range_error exception is thrown.
        //!
        //! \throws range_error if input value exceeds range of output type
        //!
        //! \param v rvalue reference to input
        //! \return new value of type uint8
        //!
        static result_type convert(read_type &&v)
        {
            return pni::core::convert<result_type>(v);
        }

        //------------------------------------------------------------------
        //!
        //! \brief convert uint16 to uint8
        //!
        //! Takes an lvalue reference to an uint16 value and converts it to
        //! uint8. If the value of the input exceeds the numeric range of
        //! uint8 a range_error exception is thrown.
        //!
        //! \throws range_error if input value exceeds range of output type
        //!
        //! \param v lvalue reference to input
        //! \return new value of type uint8
        //!
        static result_type convert(const read_type &v)
        {
            return pni::core::convert<result_type>(v);
        }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup parser_internal_classes
    //! \brief int8 conversion trait
    //!
    //! Specialization of the conversion_trait template for the int8 type.
    //! In this special case int16 is used for parsing the data.
    //!
    template<>
    struct conversion_trait<pni::core::int8>
    {
        //! the type requested by the user
        typedef pni::core::int8  result_type;
        //! the type used for reading
        typedef pni::core::int16 read_type;

        //------------------------------------------------------------------
        //!
        //! \brief convert int16 to int8
        //!
        //! Takes an rvalue reference to an int16 value and converts it to
        //! int8. If the value of the input exceeds the numeric range of
        //! int8 a range_error exception is thrown.
        //!
        //! \throws range_error if input value exceeds range of output type
        //!
        //! \param v rvalue reference to input
        //! \return new value of type int8
        //!
        static result_type convert(read_type &&v)
        {
            return pni::core::convert<result_type>(v);
        }

        //------------------------------------------------------------------
        //!
        //! \brief convert int16 to int8
        //!
        //! Takes an lvalue reference to an int16 value and converts it to
        //! int8. If the value of the input exceeds the numeric range of
        //! int8 a range_error exception is thrown.
        //!
        //! \throws range_error if input value exceeds range of output type
        //!
        //! \param v lvalue reference to input
        //! \return new value of type int8
        //!
        static result_type convert(const read_type &v)
        {
            return pni::core::convert<result_type>(v);
        }
    };

//end of namespace
}
}
