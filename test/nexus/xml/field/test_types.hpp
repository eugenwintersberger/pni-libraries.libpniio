//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Jan 15, 2016
//      Author: Eugen Wintersberger
//
#pragma once

#include <pni/types.hpp>
#include <boost/mpl/list.hpp>

typedef boost::mpl::list<pni::uint8,
                         pni::int8,
                         pni::uint16,
                         pni::int16,
                         pni::uint32,
                         pni::int32,
                         pni::uint64,
                         pni::int64,
                         pni::float32,
                         pni::float64,
#ifndef _MSC_VER
                         pni::float128,
#endif
                         pni::complex32,
                         pni::complex64,
#ifndef _MSC_VER
                         pni::complex128,
#endif
                         pni::bool_t> mdim_test_types;

typedef boost::mpl::list<pni::uint8,
                         pni::int8,
                         pni::uint16,
                         pni::int16,
                         pni::uint32,
                         pni::int32,
                         pni::uint64,
                         pni::int64,
                         pni::float32,
                         pni::float64,
#ifndef _MSC_VER
                         pni::float128,
#endif
                         pni::complex32,
                         pni::complex64,
#ifndef _MSC_VER
                         pni::complex128,
#endif
                         pni::string,
                         pni::bool_t> scalar_test_types;
