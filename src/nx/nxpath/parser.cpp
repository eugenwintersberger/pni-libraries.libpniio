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
// Created on: Jun 25, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nx/nxpath/parser.hpp>
#include <pni/io/exceptions.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace pni{
namespace io{
namespace nx{
namespace parsers{

    using namespace boost::spirit;
    using namespace boost::phoenix;

    namespace algo = boost::algorithm; 

    nxpath parse_path(const pni::core::string &input)
    {
        using namespace pni::core;
        typedef string::iterator iterator_type;
        typedef nxpath_parser<iterator_type> parser_type;

        string file_part,parser_input;

        string::size_type n = input.find("://");
        if(n == string::npos)
        {
            //if we do not have :// in the path we can assume that the path is
            //an object path
            parser_input = input;
            file_part = "";
        }
        else 
        {
            file_part = input.substr(0,n);
            parser_input = input.substr(n+3);

            //if we have a file section we eventually add a leading / to the
            //object path in order to make it absolute - a path with a file
            //section must be absolute.
            if(parser_input[0]!='/') 
                parser_input = "/"+parser_input;
        }

        //generate parser
        nxpath path;
        try
        {
            parser_type parser(file_part); 
            qi::parse(parser_input.begin(),parser_input.end(),parser,path);
        }
        catch(...)
        {
            throw pni::io::parser_error(EXCEPTION_RECORD,
                    "Error parsing string ["+input+"] to nxpath!\n"
                    "File section was:   ["+file_part+"]\n"
                    "Object section was: ["+parser_input+"]");
        }

        return path;
    }

//end of namespace
}
}
}
}

