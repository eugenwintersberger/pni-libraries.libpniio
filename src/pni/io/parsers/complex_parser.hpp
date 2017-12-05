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

#include <pni/io/parsers/parser.hpp>

namespace pni{
namespace io{

    template<typename T>
    class parser<std::complex<T>>
    {
    private:
        using base_type = T;
        parser<base_type> _base_parser;
    public:
        using result_type = std::complex<T>;

        result_type operator()(const pni::core::string &input) const
        {
            using namespace pni::core;

            boost::regex cmplx_regex(default_complex_regexp);

            result_type value;
            boost::smatch results;
            if(boost::regex_match(input,results,cmplx_regex))
            {
                base_type real_part  = 0.0,
                          imag_part  = 0.0,
                          image_sign = 1.0;
                string part = results.str("REALPART");
                if(!part.empty()) real_part = _base_parser(part);

                part = results.str("IMAGSIGN");
                if(!part.empty())
                {
                    if(part[0]=='-') image_sign = -1.0;
                }

                part = results.str("IMAGPART");
                if(!part.empty()) imag_part = _base_parser(part);

                return result_type(real_part,image_sign*imag_part);

            }
            else
            {
                std::stringstream ss;
                ss<<"Cannot convert ["<<input<<"] to "<<type_id(value)<<"!";
                throw parser_error(EXCEPTION_RECORD,ss.str());
            }
        }
    };
}
}
