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
// Created on: Jul 16, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nx/xml/attribute_data.hpp>
#include <boost/algorithm/string.hpp>

namespace pni{
namespace io{
namespace nx{
namespace xml{


    //-------------------------------------------------------------------------
    bool has_attribute(const node &n,const string &name) 
    {
        try
        {
            n.get<string>("<xmlattr>."+name);
        }
        catch(...)
        {
            //as we catch all exceptions here we do not have a problem
            return false;
        }
        return true;
    }
   
    //-------------------------------------------------------------------------
    bool has_data(const node &n,const string &name)
    {
        using boost::algorithm::trim;
        auto value = attribute_data<string>::read(n,name);
        trim(value);
         
        return !value.empty();

    }

    //-------------------------------------------------------------------------
    string attribute_data<string>::read(const node &n,const string &a)
    {
        string value;
        try
        {
            value = n.get<string>("<xmlattr>."+a);
            boost::algorithm::trim(value);
        }
        catch(boost::property_tree::ptree_bad_path &error)
        {
            throw pni::io::parser_error(EXCEPTION_RECORD,
                    "Attribute \""+a+"\" does not exist!");
        }
        catch(boost::property_tree::ptree_bad_data &error)
        {
            throw pni::io::parser_error(EXCEPTION_RECORD,
                    "Error parsing attribute \""+a+"\"!");
        }
        catch(...)
        {
            throw pni::io::parser_error(EXCEPTION_RECORD,
                    "Unknown error during parsing of attribute \""+a+"\"!");
        }

        return value;
    }

    //-------------------------------------------------------------------------
    bool attribute_data<bool>::read(const node &n,const string &a)
    {
        auto s = attribute_data<string>::read(n,a);
        bool value;

        try
        {
            value = bool_string_map.at(s);
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

        return value;
    }

    //------------------------------------------------------------------------
    bool_t attribute_data<bool_t>::read(const node &n,const string &a)
    {
        return attribute_data<bool>::read(n,a);
    }
    
    //-------------------------------------------------------------------------
    array attribute_data<array>::read(const node &dnode,const string &name,
                                      char sep)
    {
        return read(dnode,name,array_parser_t(sep));
    }
   
    //--------------------------------------------------------------------------
    array attribute_data<array>::read(const node &dnode,const string &name,
                                      char start,char stop, char sep)
    {
        return read(dnode,name,array_parser_t(start,stop,sep));
    }

    //-------------------------------------------------------------------------
    array attribute_data<array>::read(const node &dnode,const string &name,
                                      const array_parser_t &p)
    {
        using boost::spirit::qi::parse;
        using boost::algorithm::trim;
        
        //read the node data as a string
        auto text = attribute_data<string>::read(dnode,name);
        trim(text);

        array a;
        try
        {
            a= array_from_string(text,p);
        }
        catch(...)
        {
            throw parser_error(EXCEPTION_RECORD,
                    "Error parsing string \""+text+"\" to an array!");
        }

        try
        {
            a.size();
        }
        catch(...)
        {
            throw parser_error(EXCEPTION_RECORD,
                    "Error parsing string \""+text+"\" to an array!");
        }

        return a;
    }
//end of namespace
}
}
}
}
