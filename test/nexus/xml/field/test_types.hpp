//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jan 15, 2016
//      Author: Eugen Wintersberger
//
#pragma once

#include <pni/core/types.hpp>
#include <boost/mpl/list.hpp>

typedef boost::mpl::list<pni::core::uint8,
                         pni::core::int8,
                         pni::core::uint16,
                         pni::core::int16,
                         pni::core::uint32,
                         pni::core::int32,
                         pni::core::uint64,
                         pni::core::int64,
                         pni::core::float32,
                         pni::core::float64,
#ifndef _MSC_VER
                         pni::core::float128,
#endif
                         pni::core::complex32,
                         pni::core::complex64,
#ifndef _MSC_VER
                         pni::core::complex128,
#endif
                         pni::core::bool_t> mdim_test_types;

typedef boost::mpl::list<pni::core::uint8,
                         pni::core::int8,
                         pni::core::uint16,
                         pni::core::int16,
                         pni::core::uint32,
                         pni::core::int32,
                         pni::core::uint64,
                         pni::core::int64,
                         pni::core::float32,
                         pni::core::float64,
#ifndef _MSC_VER
                         pni::core::float128,
#endif
                         pni::core::complex32,
                         pni::core::complex64,
#ifndef _MSC_VER
                         pni::core::complex128,
#endif
                         pni::core::string,
                         pni::core::bool_t> scalar_test_types;
