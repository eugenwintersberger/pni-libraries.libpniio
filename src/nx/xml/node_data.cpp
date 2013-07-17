/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Jul 15, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#include "../../parsers/array_parser.hpp"
#include "node_data.hpp"
#include <boost/algorithm/string.hpp>

namespace pni{
namespace io{
namespace nx{
namespace xml{


    //-------------------------------------------------------------------------
    array node_data<array>::read(const xml::node &node,char sep)
    {
        return read(node,array_parser_t(sep));
    }
   
    //--------------------------------------------------------------------------
    array node_data<array>::read(const xml::node &node,char start,char stop,
                                 char sep)
    {
        return read(node,array_parser_t(start,stop,sep));
    }

    //-------------------------------------------------------------------------
    array node_data<array>::read(const xml::node &node,const array_parser_t &p)
    {
        using boost::spirit::qi::parse;
        using boost::algorithm::trim;
        //read the node data as a string
        auto text = node_data<string>::read(node);
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
    bool has_data(const node &n)
    {
        using boost::algorithm::trim;
        auto value = node_data<string>::read(n);
        trim(value);
        
        return !value.empty();
    }


//end of namespace
}
}
}
}
