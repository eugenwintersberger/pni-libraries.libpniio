//
// (c) Copyright 2017 DESY
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
// ===========================================================================
//
// Created on: Jun 7, 2017
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//

#include <pni/parsers/utils.hpp>
#include <pni/parsers/parser.hpp>
#include <boost/regex.hpp>

namespace pni{

    bool is_integer(const pni::string &input)
    {
        //boost::regex expr(default_int_regexp);

        return boost::regex_match(input,default_int_regexp);
    }

    //=========================================================================
    bool is_float(const pni::string &input)
    {
        //boost::regex expr(default_float_regexp);

        return boost::regex_match(input,default_float_regexp);
    }

    //=========================================================================
    bool is_boolean(const pni::string &input)
    {
        boost::regex expr("^T(rue|RUE)|true|1|F(alse|ALSE)|false|0$");

        return boost::regex_match(input,expr);
    }

    //=========================================================================
    bool is_complex(const pni::string &)
    {
        return false;
    }

    //=========================================================================
    bool is_slice(const pni::string &input)
    {
        boost::regex expr("^\\d+:(\\d*(:\\d+)?)?$");

        return boost::regex_match(input,expr);
    }

}
