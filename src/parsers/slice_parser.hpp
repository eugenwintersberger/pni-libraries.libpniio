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

#include <pni/core/types.hpp>
#include <pni/core/slice.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace pni{
namespace io{

    /*!
    \ingroup parser_classes
    \brief slice parser

    This parser reads slice objects from a string. 
    
    \tparam ITERT iterator type for the parser
    */
    template<typename ITERT>
    struct slice_parser: boost::spirit::qi::grammar<ITERT,
                                                    boost::spirit::qi::locals<size_t,size_t,size_t>,
                                                    pni::core::slice()>
    {
        boost::spirit::qi::rule<ITERT,boost::spirit::qi::locals<size_t,size_t,size_t>,
                                pni::core::slice()
                                > slice_rule;

        slice_parser() : slice_parser::base_type(slice_rule)
        {
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;
            slice_rule = eps[_a=0,_b=0,_c=1]>>(
                (int_[_a = _1,_b=_1+1]>> -(':' >>int_[_b = _1]>> -(':' >>
                                                                 int_[_c=_1]))) 
                |
                ( ':' >> int_[_b = _1]>> -(':'>>int_[_c = _1]))
              )[_val = construct<pni::core::slice>(_a,_b,_c)];
        }
    };
//end of namespace
}
}
