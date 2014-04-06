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
 *
 * Created on: May 6, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#pragma once

#include<pni/core/types.hpp>
#include<pni/core/type_erasures.hpp>
#include<vector>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace pni{
namespace io{
   
    /*!
    \ingroup parser_classes
    \brief value parser

    Parser reading an integer or floating point number from a string and stores
    it into an instance of pni::core::value. The parser is able of infering the
    appropriate data type from its string representation. 
    Currently all integers are interpreted as INT32 and all floating point
    numbers as FLOAT64 types.
    \tparam ITERT iterator type
    */
    template<typename ITERT>
    struct value_parser: public boost::spirit::qi::grammar<ITERT,pni::core::value()>
    {
        //!value reading rule
        boost::spirit::qi::rule<ITERT,pni::core::value()> value_rule;

        //!default constructor
        value_parser() : value_parser::base_type(value_rule)
        {
            using namespace pni::core;
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;
            using boost::spirit::qi::_1;
            value_rule = (*blank>>(
                         (int_>>!(char_('.')|char_('e')))[_val = _1] 
                          || 
                          double_[_val = _1]
                        ));
        }
    };

//end of namespace
}
}
