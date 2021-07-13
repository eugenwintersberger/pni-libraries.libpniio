//
// (c) Copyright 2017 DESY
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
// Created on: Jun 8, 2017
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/parsers/complex_parser.hpp>
#include <pni/parsers/parser.hpp>

namespace pni{
namespace io{

    //!
    //! \ingroup parser_classes
    //! \brief parser for general values
    //!
    //! This is a specialization of the parser class for the value type erasure.
    //! The parser tries to identify the value provided by the data string
    //! and converts it to the appropriate type which will then be wrapped
    //! in an instance of pni::core::value.
    //!
    //! The class currently supports the following types
    //! * 64Bit integer
    //! * 64Bit floating point
    //! * 64Bit complex floats
    //! * and strings
    //!
    template<>
    class PNIIO_EXPORT parser<pni::core::value>
    {
    private:
        //!
        //! parser for integer values
        //!
        parser<pni::core::int64>     _int_parser;

        //!
        //! parser for float values (doubles)
        //!
        parser<pni::core::float64>   _float_parser;

        //!
        //! parser for complex values
        //!
        parser<pni::core::complex64> _complex_parser;
    public:
        using result_type = pni::core::value;

        result_type operator()(const pni::core::string &data) const;
    };

}
}
