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
#include <pni/parsers/slice_parser.hpp>

namespace pni {

    parser<pni::slice>::parser():
        _regexpr("^(?<START>\\d+)?(:(?<STOP>\\d*)(:(?<STRIDE>\\d+))?)?$")
    {
    }

    //=========================================================================
    parser<pni::slice>::result_type
    parser<pni::slice>::operator()(const pni::string &input) const
    {
        using namespace pni;

        boost::smatch results;
        if(boost::regex_match(input,results,_regexpr))
        {
            size_t start = 0, stop = 0, stride = 1;
            string value = results.str("START");
            if(!value.empty())
                start = boost::lexical_cast<size_t>(value);

            value = results.str("STOP");
            if(!value.empty())
                stop = boost::lexical_cast<size_t>(value);
            else
                stop = start+1;

            value = results.str("STRIDE");
            if(!value.empty())
                stride = boost::lexical_cast<size_t>(value);

            return slice(start,stop,stride);
        }
        else
        {
            std::stringstream ss;
            ss<<"Input ["<<input<<"] cannot be converted to a slice!";
            throw parser_error(EXCEPTION_RECORD,ss.str());
        }
        return pni::slice();
    }

}
