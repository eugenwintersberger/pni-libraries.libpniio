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
// Created on: May 6, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once


#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace pni{
namespace io{

    using namespace pni;
    using namespace boost::spirit;

    //!
    //! \ingroup parser_classes
    //! \brief delimiter parser
    //!
    //! This parser is used for delimiters which for instance separate 
    //! columns in a CSV file. By default the separator is at least one blank 
    //! symbol.  Alternatively one can define a special single character as 
    //! a delimiter.  This character can be preceded and followed by an 
    //! arbitrary number of blanks. 
    //!
    //! This parser itself is hardly usefull. However, it is a quite handy 
    //! component in connection with other parser.
    //!
    //! \tparam ITERT iterator type for the parser
    //!
    template<typename ITERT >
    struct delimiter_rule : boost::spirit::qi::grammar<ITERT,pni::core::string()>
    {
        //! main parser rule
        boost::spirit::qi::rule<ITERT,pni::core::string()> delimiter;

        //--------------------------------------------------------------------
        //!default constructor
        delimiter_rule() : 
            delimiter_rule::base_type(delimiter)
        {
            using namespace pni::core;
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;
            //default behavior - at least one whitespace is a valid delimiter
            delimiter = +boost::spirit::qi::blank;
        }

        //--------------------------------------------------------------------
        //! constructor
        delimiter_rule(char symbol):
            delimiter_rule::base_type(delimiter)
        {
            using namespace pni::core;
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;
            if(symbol == ' ')
                delimiter = +qi::blank;
            else
                delimiter = *qi::blank>>char_(symbol)>>*qi::blank;
        }

    };

//end of namespace
}
}
