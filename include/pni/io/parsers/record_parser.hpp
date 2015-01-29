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
#include<iostream>
#include<pni/core/types.hpp>
#include<pni/core/type_erasures.hpp>
#include<pni/core/arrays.hpp>
#include<vector>

#include <boost/variant.hpp>

#include "value_parser.hpp"
#include "delimiter_rule.hpp"
#include "array_parser.hpp"


namespace pni{
namespace io{

    typedef boost::variant<pni::core::value,pni::core::array> record_element_t;
    typedef std::vector<record_element_t> record_t;

    //!
    //! \ingroup parser_classes
    //! \brief parser for numeric data records
    //!
    //! This is a parser for numeric data records that is based on the value-,
    //! array-, and delimiter-parser. A typical record would look like this
    /*! \code
    1. 2 3.4 [1,2,3,4] 5.6 1.3e-4
    2. 3 3.8 [6,8,9,10] 10.9 2.3e-3
    ....
    \endcode */
    //! Every column (the array is treated as a column for its own). 
    //! It must be mentioned that due to current limitations of the array 
    //! parser only 1D arrays can be read. 
    //! Each element of the record is an instance of boost::variant<value,array>
    //! as each element can be either a single scalar value (value) or an 
    //! array.  See the documentation for boost::variant to learn how to 
    //! manage such a data structure. 
    //!
    //! \tparam ITERT iterator type for the parser
    //! \sa array_parser, delimiter_parser, value_parser
    //!
    template<typename ITERT>
    struct record_parser : boost::spirit::qi::grammar<ITERT,record_t()>
    {
        //! grammar rule for the entire record
        boost::spirit::qi::rule<ITERT,record_t()> record_rule;
        //! grammar rule for a single element
        boost::spirit::qi::rule<ITERT,record_element_t()> entry_rule;
       
        //! the value parser 
        value_parser<ITERT> value_;
        //! the delimiter parser
        delimiter_rule<ITERT> delimiter_;
        //! the array parser
        array_parser<ITERT> array_;
    
        //---------------------------------------------------------------------
        //!
        //! \brief default constructor
        //!
        //! In this case blanks are used as column delimiters, [ and ] as 
        //! array start and stop symbols, and a ',' as the array element 
        //! delimiter. 
        //!
        record_parser() : 
            record_parser::base_type(record_rule),
            delimiter_(),
            array_()
        {
            init();
        }

        //---------------------------------------------------------------------
        //! 
        //! \brief constructor
        //!
        //! \param column_separator the character separating the individual 
        //! columns
        //! \param array_start character staring an array
        //! \param array_stop character finishing an array
        //! \param array_separator character separating array elements
        //!
        record_parser(char column_separator,
                      char array_start,char array_stop,
                      char array_separator) :
            record_parser::base_type(record_rule),
            delimiter_(column_separator),
            array_(array_start,array_stop,array_separator)
        {
            init();
        }

        //---------------------------------------------------------------------
        //!
        //! initialization method called by each constructor
        //!
        void init() 
        {
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;
            using boost::phoenix::push_back;

            entry_rule = (value_|array_);
            record_rule = (*blank>>(entry_rule % delimiter_))[_val = _2];    
        }
    };

//end of namespace
}
}

