//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Dec 3, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <pni/core/types.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/joint_view.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_real.hpp>
#include <boost/spirit/include/qi_uint.hpp>
#include <boost/spirit/include/qi_int.hpp>

namespace pni{
namespace io{

    using namespace pni;
    using namespace boost;

#define PARSER_TYPE(p)\
    std::remove_const<decltype(p)>::type

    //!
    //! \ingroup parser_classes
    //! \brief spirit rule map
    //!
    //! This MPL map provides a mapping from data types to their appropriate
    //! parsing rules provided by the boost::spirit library.
    //!
    typedef mpl::map<
        mpl::pair<core::uint8 ,spirit::qi::uint_parser<core::uint8,10,1,4> >,
        mpl::pair<core::uint16,PARSER_TYPE(spirit::qi::ushort_)>,
        mpl::pair<core::uint32,PARSER_TYPE(spirit::qi::uint_)  >,
        mpl::pair<core::uint64,PARSER_TYPE(spirit::qi::ulong_) >,
        mpl::pair<core::int8 ,spirit::qi::uint_parser<core::int8,10,1,4> >,
        mpl::pair<core::int16, PARSER_TYPE(spirit::qi::short_) >,
        mpl::pair<core::int32, PARSER_TYPE(spirit::qi::int_)   >,
        mpl::pair<core::int64, PARSER_TYPE(spirit::long_)      >,
        mpl::pair<core::float32, PARSER_TYPE(spirit::float_)      >,
        mpl::pair<core::float64, PARSER_TYPE(spirit::double_)     >,
        mpl::pair<core::float128,PARSER_TYPE(spirit::long_double) >,
        mpl::pair<core::bool_t,  PARSER_TYPE(spirit::bool_)       >
        > spirit_rules;

//end of namespace
}
}
