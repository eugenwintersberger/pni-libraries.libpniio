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

#include <pni/core/types.hpp>
#include <pni/core/type_erasures.hpp>
#include <boost/variant.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include "spirit_rules.hpp"
#include "complex_rule.hpp"

namespace pni{
namespace io{

   
    //!
    //! \ingroup parser_internal_classes
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
    //! The rule is only default constructible. No additional options have to 
    //! be applied.
    //! 
    //! \tparam ITERT iterator type
    //!
    template<typename ITERT>
    struct value_rule : boost::spirit::qi::grammar<ITERT,pni::core::value()>
    {
        //--------------------------------------------------------------------
        // definition of internal classes used by the value_rule
        //--------------------------------------------------------------------
        //!
        //! \brief visitor for value construction
        //!
        //! This visitor is used to construct a value instance from a 
        //! boost::variant<int64,float64,complex64> instance. This visitor is
        //! used by the value_constructor which is by again called by 
        //! value_rule to construct a value instance. Most of the member 
        //! functions plainly pass through their input arguments.
        //! 
        //! \sa value_rule
        //! \sa value_constructor
        class value_constructor_visitor : 
            public boost::static_visitor<pni::core::value>
        {
            public:
                //!
                //! \brief int64 value construction
                //! 
                pni::core::value operator()(const pni::core::int64 &v) const
                {
                    return pni::core::value(v);
                }
                
                //!
                //! \brief complex64 value construction
                //! 
                pni::core::value operator()(const pni::core::complex64 &v) const
                {
                    return pni::core::value(v);
                }

                //!
                //! \brief float64 value construction
                //! 
                pni::core::value operator()(const pni::core::float64 &v) const
                {
                    return pni::core::value(v);
                }
        };

        //--------------------------------------------------------------------
        //!
        //! \brief value construction lazy function
        //! 
        //! This is the implementation of a lazy function for phoenix which 
        //! can be used to create a value instance from the parsed data item.
        //!
        struct value_constructor
        {
            //! determine the return type of the function
            template<typename Sig> struct result
            {
                //! the return type
                typedef pni::core::value type;
            };

            //-----------------------------------------------------------------
            //!
            //! \brief lazy function implementation
            //!
            //! This operator finally implements the lazy function. 
            //!
            //! \tparam Arg argument type
            //! \param n container with input data
            //! \return instance of pni::core::array
            //!
            template<typename Arg> 
            pni::core::value operator()(Arg const &n) const
            {
                return boost::apply_visitor(value_constructor_visitor(),n);
            }

        };

        //--------------------------------------------------------------------
        // here starts the implementation of the rule
        //--------------------------------------------------------------------
        //! rule for parsing an integer
        typename boost::mpl::at<
                                spirit_rules,
                                pni::core::int64
                               >::type   integer_rule_;

        //! rule for parsing a floating point number
        typename boost::mpl::at<
                                spirit_rules,
                                pni::core::float64
                               >::type float_rule_;

        //! rule for parsing a complex number
        complex_rule<ITERT,pni::core::complex64> complex_rule_;
        //!value reading rule
        boost::spirit::qi::rule<ITERT,pni::core::value()> value_;
        //! rule to match the + or - sign
        boost::spirit::qi::rule<ITERT>               sign_rule;
        //! rule to match . or e used to denote a floating point number
        boost::spirit::qi::rule<ITERT>               float_signs;
        //! lazy function to assemble a value instance
        boost::phoenix::function<value_constructor> construct_value;

        //--------------------------------------------------------------------
        //!default constructor
        value_rule() : value_rule::base_type(value_)
        {
            //using namespace pni::core;
            using namespace boost::spirit::qi;
            //using namespace boost::fusion;
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
