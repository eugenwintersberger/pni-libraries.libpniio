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
//
// Created on: Jul 15, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//


#include <pni/io/parsers/array_parser.hpp>
#include <pni/io/nx/xml/node_data.hpp>
#include <boost/algorithm/string.hpp>

namespace pni{
namespace io{
namespace nx{
namespace xml{


    //-------------------------------------------------------------------------
    array node_data<array>::read(const node &dnode,char sep)
    {
        return read(dnode,array_parser_t(sep));
    }
   
    //--------------------------------------------------------------------------
    array node_data<array>::read(const node &dnode,char start,char stop,
                                 char sep)
    {
        return read(dnode,array_parser_t(start,stop,sep));
    }

    //-------------------------------------------------------------------------
    array node_data<array>::read(const node &dnode,const array_parser_t &p)
    {
        using boost::spirit::qi::parse;
        using boost::algorithm::trim;
        //read the node data as a string
        auto text = node_data<string>::read(dnode);
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

    //-------------------------------------------------------------------------
    string node_data<string>::read(const node &dnode)
    {
        try
        {
            return dnode.get_value<string>();
        }
        catch(boost::property_tree::ptree_bad_data &error)
        {
            throw parser_error(EXCEPTION_RECORD,
                    "Bad string data in tag!");
        }
        catch(...)
        {
            throw parser_error(EXCEPTION_RECORD,
                    "Unknown error when reading string data from tag!");
        }

    }

    //-------------------------------------------------------------------------
    bool node_data<bool>::read(const node &dnode)
    {
        auto str_rep = node_data<string>::read(dnode);

        try
        {
            return bool_string_map.at(str_rep);
        }
        catch(std::out_of_range &error)
        {
            throw pni::core::value_error(EXCEPTION_RECORD,
                    "Node data is not a valid bool representation!");
        }
        catch(...)
        {
            throw pni::io::parser_error(EXCEPTION_RECORD,
                    "Unkonwn error when converting string to bool!");
        }
    }

    //------------------------------------------------------------------------
    bool_t node_data<bool_t>::read(const node &dnode)
    {
        return node_data<bool>::read(dnode);
    }

    //------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
    binary node_data<binary>::read(const node &dnode)
    {
        throw pni::core::not_implemented_error(EXCEPTION_RECORD,
                "Reading binary data from XML is currently not supported!");
    }
#pragma GCC diagnostic pop

    //-------------------------------------------------------------------------
    bool has_data(const node &n)
    {
        using boost::algorithm::trim;
        auto value = node_data<string>::read(n);
        trim(value);
        
        return !value.empty();
    }
    
    //------------------------------------------------------------------------
    value read_node(type_id_t tid,const node &n)
    {
        if(tid == type_id_t::UINT8)
            return value(node_data<uint8>::read(n));
        else if(tid == type_id_t::INT8)
            return value(node_data<int8>::read(n));
        else if(tid == type_id_t::UINT16)
            return value(node_data<uint16>::read(n));
        else if(tid == type_id_t::INT16)
            return value(node_data<int16>::read(n));
        else if(tid == type_id_t::UINT32)
            return value(node_data<uint32>::read(n));
        else if(tid == type_id_t::INT32)
            return value(node_data<int32>::read(n));
        else if(tid == type_id_t::UINT64)
            return value(node_data<uint64>::read(n));
        else if(tid == type_id_t::INT64)
            return value(node_data<int16>::read(n));
        else if(tid == type_id_t::FLOAT32)
            return value(node_data<float32>::read(n));
        else if(tid == type_id_t::FLOAT64)
            return value(node_data<float64>::read(n));
        else if(tid == type_id_t::FLOAT128)
            return value(node_data<float128>::read(n));
        else if(tid == type_id_t::COMPLEX32)
            return value(node_data<complex32>::read(n));
        else if(tid == type_id_t::COMPLEX64)
            return value(node_data<complex64>::read(n));
        else if(tid == type_id_t::COMPLEX128)
            return value(node_data<complex128>::read(n));
        else if(tid == type_id_t::BINARY)
            return value(node_data<binary>::read(n));
        else if(tid == type_id_t::STRING)
            return value(node_data<string>::read(n));
        else if(tid == type_id_t::BOOL)
            return value(node_data<bool_t>::read(n));
        else 
            throw type_error(EXCEPTION_RECORD,
                    "Unsupported data type!");
    }


//end of namespace
}
}
}
}
