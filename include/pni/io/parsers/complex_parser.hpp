//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jan 20, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//

#pragma once

#include<pni/core/types.hpp>
#include<vector>
#include<map>
#include<complex>

#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/at.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include "spirit_parsers.hpp"

namespace pni{
namespace io{


    template<
             typename ITERT,
             typename BASET
            >
    using complex_grammar = boost::spirit::qi::grammar<ITERT,std::complex<BASET>()>;
   
    //!
    //! \ingroup parser_classes
    //! \brief value parser
    //!
    //! Parser reading an integer or floating point number from a string and 
    //! stores it into an instance of pni::core::value. The parser is able 
    //! of infering the appropriate data type from its string representation. 
    //! Currently all integers are interpreted as INT32 and all floating 
    //! point numbers as FLOAT64 types.
    //! 
    //! \tparam ITERT iterator type
    //!
    template<typename ITERT,typename BASET>
    struct complex_parser: public complex_grammar<ITERT,BASET>
    {
        typedef std::complex<BASET> result_type;
        typename boost::mpl::at<spirit_parsers,BASET>::type base_parser;
        //!rule matching a single numeric value
        boost::spirit::qi::rule<ITERT,BASET()> number_rule;
        //! rule obtaining the sign
        boost::spirit::qi::rule<ITERT,BASET()> sign_rule;
        //! rule matching the separator i,j,I 
        boost::spirit::qi::rule<ITERT>       i_rule;
        //! rule determining the imaginary part
        boost::spirit::qi::rule<ITERT,BASET()> imag_rule;
        //! rule defining the entire complex number
        boost::spirit::qi::rule<ITERT,result_type()> complex_rule;

        //!default constructor
        complex_parser() : complex_parser::base_type(complex_rule)
        {
            using namespace pni::core;
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;
            using boost::spirit::qi::_1;

            number_rule = base_parser[_val = _1];
            sign_rule   = char_('+')[_val=1] | char_('-')[_val=-1.];
            i_rule      = (char_('i') | char_('j') | char_('I'))>!sign_rule;
            imag_rule   = sign_rule[_val = _1]>i_rule>number_rule[_val *= _1];

            complex_rule = number_rule[_val = construct<result_type>(_1,0)] || 
                           imag_rule[_val += construct<result_type>(0,_1)];
                         
                         
        }
    };

//end of namespace
}
}
