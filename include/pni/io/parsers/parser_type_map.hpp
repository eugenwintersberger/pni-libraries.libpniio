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

#include <boost/spirit/include/qi_real.hpp>
#include <boost/spirit/include/qi_uint.hpp>
#include <boost/spirit/include/qi_int.hpp>

#include <boost/spirit/home/qi/numeric/uint.hpp>


namespace pni{
namespace io{

    using namespace pni::core;
    using namespace boost;

    /*
    typedef mpl::map<
        mpl::pair<uint16,spirit::qi::ushort_parser>,
        mpl::pair<uint32,spirit::uint_>,
        mpl::pair<uint64,spirit::ulong_>,
        mpl::pair<int16,spirit::short_>,
        mpl::pair<int32,spirit::int_>,
        mpl::pair<int64,spirit::long_>,
        mpl::pair<float32,spirit::float_>,
        mpl::pair<float64,spirit::double_>,
        mpl::pair<float128,spirit::long_double_>
        > parser_type_map;
        */

//end of namespace
}
}
