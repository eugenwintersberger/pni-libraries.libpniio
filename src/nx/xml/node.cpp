//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 11, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <sstream>
#include <fstream>
#include <locale>
#include <boost/property_tree/xml_parser.hpp>

#include <pni/io/exceptions.hpp>
#include <pni/io/nx/xml/node.hpp>

namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace boost::property_tree;

    node create_from_string(const string &s)
    {
        std::stringstream stream(s.c_str());
        node t;
        try
        {
            read_xml(stream,t);
        }
        catch(ptree_bad_data &error)
        {
            throw pni::io::parser_error(EXCEPTION_RECORD,
                    "A parser error occured due to invalid input data!");
        }
        catch(ptree_bad_path &error)
        {
            throw pni::io::parser_error(EXCEPTION_RECORD,
                    "A parser error occured as the requested object could not"
                    " be resolved!");
        }
        catch(ptree_error &error)
        {
            throw pni::io::parser_error(EXCEPTION_RECORD,
                    "A general parser error has occured!");
        }
        catch(...)
        {
            //whatever exception is thrown here is related to parsing
            throw pni::io::parser_error(EXCEPTION_RECORD,
                    "A unkown fatal error parsing XML string has occured!");
        }

        return t;
    }

    //-------------------------------------------------------------------------
    node create_from_file(const string &s)
    {
        std::ifstream stream(s.c_str());
        if(!stream.is_open())
            throw file_error(EXCEPTION_RECORD,
                    "Error opening "+s+" for reading!");

        node t;
        try
        {
            read_xml(stream,t);
        }
        catch(...)
        {
            throw pni::io::parser_error(EXCEPTION_RECORD,
                    "Error parsing XML file "+s+"!");
        }

        return t;
    }
    //------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const node &n)
    {
        boost::property_tree::xml_writer_settings<char> settings('\t',1);

        boost::property_tree::write_xml(o,n,settings);
        return o;
    }


//end of namespace
}
}
}
}
