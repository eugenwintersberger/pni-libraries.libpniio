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
 * Created on: Jul 12, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "xml_lowlevel.hpp"

namespace pni{
namespace io{
namespace nx{
namespace xml{

    array read_xml_array_data(const node &n)
    {
        using boost::spirit::qi::parse;
        typedef string::const_iterator iterator_t;
        typedef pni::io::array_parser<iterator_t> array_parser_t;;

        //define iterators
        iterator_t start_iter,stop_iter;

        //first we need to read the data as plain text
        string text = read_xml_data<string>(n);
        start_iter = text.begin();
        stop_iter  = text.end();

        array a;

        //now we need to try vor several delimiters
        try
        {
            //here we try an array separated by whitespaces
            parse(start_iter,stop_iter,array_parser_t(' '),a);
            return a;
        }
        catch(...)
        {}

        try
        {
            //try a comma as a separator
            parse(start_iter,stop_iter,array_parser_t(','),a);
            return a;
        }
        catch(...)
        { }

        try
        {
            //try with a semi-colon
            parse(start_iter,stop_iter,array_parser_t(';'),a);
            return a;
        }
        catch(...)
        {
            //ok this was the last try - throw an exception here.
            throw pni::io::parser_error(EXCEPTION_RECORD,
                    "Could not parse array data!");
        }

        //just to make the compiler happy
        return a;
    }

//end of namespace
}
}
}
}

