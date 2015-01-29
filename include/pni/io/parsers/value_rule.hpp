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

#include<pni/core/types.hpp>
#include<pni/core/type_erasures.hpp>
#include<vector>
#include "spirit_rules.hpp"
#include "complex_rule.hpp"

#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace pni{
namespace io{

    class value_constructor_visitor 
        : public boost::static_visitor<pni::core::value>
    {
        public:
            pni::core::value operator()(const pni::core::int64 &v) const
            {
                return value(v);
            }

            pni::core::value operator()(const pni::core::complex64 &v) const
            {
                return value(v);
            }

            pni::core::value operator()(const pni::core::float64 &v) const
            {
                return value(v);
            }
    };

    //!
    //! \ingroup parser_classes
    //! \brief array construction lazy function
    //! 
    //! This is the implementation of a lazy function for phoenix which can 
    //! be used to create an array from a container. 
    //!
    struct value_constructor
    {
        //! determine the return type of the function
        template<typename Sig> struct result
        {
            //! the return type
            typedef pni::core::value type;
        };

        //---------------------------------------------------------------------
        /*!
        \brief lazy function implementation

        This operator finally implements the lazy function. 
        \tparam Arg argument type
        \param n container with input data
        \return instance of pni::core::array
        */
        template<typename Arg> pni::core::value operator()(Arg const &n) const
        {
            return boost::apply_visitor(value_constructor_visitor(),n);
        }

    };
   
    //!
    //! \ingroup parser_classes
    //! \brief value rule
    //!
    //! This rule parses an input string and automatically selects the proper 
    //! parser for the input value. From its ASCII representation the particular 
    //! type a value belongs to is not entirely visible. For instance it is 
    //! not possible to distinguish the different integer types from a single 
    //! ASCII representation. Neither is this possible for floating point types 
    //! and complex types. Thus, the number of different parsers used 
    //! in this  rule are limitted. As a fallback the string parser is 
    //! the last resort tho get the data parsed. 
    //! The following parsers will be used internally 
    //! 
    //! \li int64   -- for all integer types
    //! \li float64 -- for all floating point types
    //! \li complex64 -- for complex numbers
    //!
    //! A typical application would be to parse the value part of key-value
    //! pairs in an ASCII file where the data type of the attribute is not known 
    //! in advance. The rule will make a best guess to automatically find the 
    //! appropriate type or uses a string representation in the worst case. 
    //!
    //! The input string is assumed to be stripped from all leading and trailing
    //! blank and newline symbols.
    //! 
    //! \tparam ITERT iterator type
    //!
    template<typename ITERT>
    struct value_rule : boost::spirit::qi::grammar<ITERT,pni::core::value()>
    {
        typename boost::mpl::at<spirit_rules,int64>::type   integer_rule_;
        typename boost::mpl::at<spirit_rules,float64>::type float_rule_;
        complex_rule<ITERT,float64>                         complex_rule_;
        //!value reading rule
        boost::spirit::qi::rule<ITERT,pni::core::value()> value_;
        boost::spirit::qi::rule<ITERT> sign_rule;
        boost::spirit::qi::rule<ITERT> float_signs;
        boost::phoenix::function<value_constructor> construct_value;

        //!default constructor
        value_rule() : value_rule::base_type(value_)
        {
            using namespace pni::core;
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;
            using boost::spirit::qi::_1;

            sign_rule = char_('+')|char_('-');
            float_signs = char_('.')|char_('e');

            value_ = ((integer_rule_ >> !(float_signs|sign_rule))
                      | 
                      (float_rule_ >> !(sign_rule))
                      | 
                      complex_rule_)[_val = construct_value(_1)];
        }
    };

//end of namespace
}
}
