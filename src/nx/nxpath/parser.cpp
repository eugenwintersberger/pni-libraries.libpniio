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
#include <boost/algorithm/string/predicate.hpp>

namespace pni{
namespace io{
namespace nx{
namespace parsers{


    namespace algo = boost::algorithm; 

    nxpath parse_path(const string &input)
    {
        typedef string::iterator iterator_type;
        typedef nxpath_parser<iterator_type> parser_type;

        //a file path must contain at least one '.' - the extension of the 
        //file
        bool file_path = algo::contains(input,".");
        //a full path consists of a file path separated from the object path
        //by :// 
        bool full_path = algo::contains(input,"://");
        
        string parser_input;
        if(full_path)
            //need to parse a full nexus path
            parser_input = input;
        else if(file_path)
            //if the input is not a full path but satisifies the requirements
            //for a file path => it can only be a file path.
            parser_input = input + "://";
        else
            //if the input is neither a full path nor a file path it must be 
            //an object path and needs a prefix to be successfully parsed
            parser_input = "://"+input;

        
        //generate parser
        parser_type parser; 
        nxpath path;
        qi::parse(parser_input.begin(),parser_input.end(),parser,path);

        return path;
    }

//end of namespace
}
}
}
}

