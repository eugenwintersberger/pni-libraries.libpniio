//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Dec 4, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nx/xml/decoder.hpp>

namespace pni{
namespace io{
namespace nx{
namespace xml{

    //-------------------------------------------------------------------------
    string decoder<string>::decode(const string &data) const
    {
        return data;
    }

    //-------------------------------------------------------------------------
    bool decoder<bool>::decode(const string &data) const
    {
        try
        {
            return bool_string_map.at(data);
        }
        catch(std::out_of_range &error)
        {
            throw pni::core::value_error(EXCEPTION_RECORD,
                    "The attribute value does not represent a boolean value!");
        }
        catch(...)
        {
            throw pni::io::parser_error(EXCEPTION_RECORD,
                    "Unknown error parsing boolean attribute!");
        }
    }

    //------------------------------------------------------------------------
    bool_t decoder<bool_t>::decode(const string &data) const
    {
        return decoder<bool>().decode(data);
    }
    

    //-------------------------------------------------------------------------
    decoder<array>::decoder(char sep):
        _parser(sep)
    {}

    //-------------------------------------------------------------------------
    decoder<array>::decoder(char start,char stop,char sep):
        _parser(start,stop,sep)
    {}

    //-------------------------------------------------------------------------
    array decoder<array>::decode(const string &data) const
    {
        using boost::spirit::qi::parse;
        
        array a;
        try
        {
            a= array_from_string(data,_parser);
        }
        catch(...)
        {
            throw parser_error(EXCEPTION_RECORD,
                    "Error parsing string \""+data+"\" to an array!");
        }

        try
        {
            a.size();
        }
        catch(...)
        {
            throw parser_error(EXCEPTION_RECORD,
                    "Error parsing array data!");
        }

        return a;
    }

//end of namespace
}
}
}
}

