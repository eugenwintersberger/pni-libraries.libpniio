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
// Created on: Jun 8, 2017
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//

#include <pni/parsers/value_parser.hpp>

namespace pni{
namespace io{

    parser<pni::value>::result_type
    parser<pni::value>::operator()(const pni::string &input) const
    {
        using namespace pni;

        if(boost::regex_match(input,default_int_regexp))
            return result_type(_int_parser(input));
        else if(boost::regex_match(input,default_float_regexp))
            return result_type(_float_parser(input));
        else if(boost::regex_match(input,default_complex_regexp))
            return result_type(_complex_parser(input));
        else
        {
            std::stringstream ss;
            ss<<"Input ["<<input<<"]cannot be converted to pni::value!";
            throw parser_error(EXCEPTION_RECORD,ss.str());
        }
    }
}
}
