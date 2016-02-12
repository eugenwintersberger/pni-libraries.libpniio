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
#include <pni/core/arrays/slice.hpp>

#ifdef _MSC_VER
#pragma warning(disable:4348)
#endif
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#ifdef _MSC_VER
#pragma warning(default:4348)
#endif

namespace pni{
namespace io{

    //!
    //! \ingroup parser_internal_classes
    //! \brief slice parser
    //!
    //! This parser reads slice objects from a string. A slice is represented 
    //! by three numbers: the start index, the last index, and a stride. 
    //! In string representation these three values are written as
    /*!
    \code
    start:stop:stride
    \endcode
    */
    //! where a \c : is used as separator between the numbers. There are 
    //! several flavors of strings that can be used to denote a slice 
    //! \li \c start - here stop is assumed to be start+1 and stride=1.
    //! \li \c start:stop - where stride is assumed to be 1
    //! \li \c :stop - where start=0 and stride = 1
    //! \li \c :stop:stride - where start is assumed to be 0
    //!
    //! This parser is capable of managing all these variations. It can be 
    //! used like this
    /*!
    \code 
    typedef string::iterator iterator_t;
    typedef slice_parser<iterator_t> parser_t;

    string slice_str = "1:100:2";
    slice s;
    parser_t parser; //generate a parser instance
    parse(slice_str.begin(),slice_str.end(),parser,s);

    \endcode
    */
    //!
    //! \tparam ITERT iterator type for the parser
    //!
    template<typename ITERT>
    struct slice_rule: boost::spirit::qi::grammar<ITERT,
                                   boost::spirit::qi::locals<size_t,size_t,size_t>,
                                   pni::core::slice()>
    {
        //! rule to parse a slice string
        boost::spirit::qi::rule<ITERT,
                 boost::spirit::qi::locals<size_t,size_t,size_t>,
                 pni::core::slice() > slice_;

        //! default constructor
        slice_rule() : slice_rule::base_type(slice_)
        {
            using namespace boost::spirit;
            using namespace boost::spirit::qi;
            using namespace boost::phoenix;
            using qi::_1;

            slice_= eps[_a=0,_b=0,_c=1]>>(
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
