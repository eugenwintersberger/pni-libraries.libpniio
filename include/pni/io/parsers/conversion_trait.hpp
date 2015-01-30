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
    //! \ingroup parser_classes
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
        typedef T result_type;
        typedef T read_type;

        static result_type convert(read_type &&v) 
        { 
            return v; 
        }

        static result_type convert(const read_type &v)
        {
            return v;
        }
    };

    //------------------------------------------------------------------------
    //! 
    //! \ingroup parser_classes
    //! \brief uint8 conversion trait
    //! 
    //! Specialization of the conversion_trait template for the uint8 type. 
    //! In this special case uint16 is used for parsing the data.
    //!
    template<>
    struct conversion_trait<uint8>
    {
        typedef uint8  result_type;
        typedef uint16 read_type;

        static result_type convert(read_type &&v) 
        { 
            return pni::core::convert<result_type>(v); 
        }

        static result_type convert(const read_type &v)
        {
            return pni::core::convert<result_type>(v);
        }
    };

    //------------------------------------------------------------------------
    //! 
    //! \ingroup parser_classes
    //! \brief int8 conversion trait
    //! 
    //! Specialization of the conversion_trait template for the int8 type. 
    //! In this special case int16 is used for parsing the data.
    //!
    template<>
    struct conversion_trait<int8>
    {
        typedef int8  result_type;
        typedef int16 read_type;

        static result_type convert(read_type &&v) 
        { 
            return pni::core::convert<result_type>(v); 
        }

        static result_type convert(const read_type &v)
        {
            return pni::core::convert<result_type>(v);
        }
    };

//end of namespace
}
}
