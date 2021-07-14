//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pninexus.
//
// pninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
//  Created on: Nov 27, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/types.hpp>
#include <pni/arrays.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/joint_view.hpp>


typedef boost::mpl::list<
                         pni::dynamic_array<pni::int8>,
                         pni::dynamic_array<pni::int16>,
                         pni::dynamic_array<pni::int32>,
                         pni::dynamic_array<pni::int64>,
                         pni::dynamic_array<pni::uint8>,
                         pni::dynamic_array<pni::uint16>,
                         pni::dynamic_array<pni::uint32>,
                         pni::dynamic_array<pni::uint64>,
                         pni::dynamic_array<pni::float32>,
                         pni::dynamic_array<pni::float64>,
                         pni::dynamic_array<pni::float128>,
                         pni::dynamic_array<pni::complex32>,
                         pni::dynamic_array<pni::complex64>,
                         pni::dynamic_array<pni::complex128>
                        > dyn_array_types;

typedef boost::mpl::list<
                         pni::fixed_dim_array<pni::int8,3>,
                         pni::fixed_dim_array<pni::int16,3>,
                         pni::fixed_dim_array<pni::int32,3>,
                         pni::fixed_dim_array<pni::int64,3>,
                         pni::fixed_dim_array<pni::uint8,3>,
                         pni::fixed_dim_array<pni::uint16,3>,
                         pni::fixed_dim_array<pni::uint32,3>,
                         pni::fixed_dim_array<pni::uint64,3>,
                         pni::fixed_dim_array<pni::float32,3>,
                         pni::fixed_dim_array<pni::float64,3>,
                         pni::fixed_dim_array<pni::float128,3>,
                         pni::fixed_dim_array<pni::complex32,3>,
                         pni::fixed_dim_array<pni::complex64,3>,
                         pni::fixed_dim_array<pni::complex128,3>
                        > fixed_dim_array_types;

typedef boost::mpl::list<
                         pni::static_array<pni::int8,2,3,4>,
                         pni::static_array<pni::int16,2,3,4>,
                         pni::static_array<pni::int32,2,3,4>,
                         pni::static_array<pni::int64,2,3,4>,
                         pni::static_array<pni::uint8,2,3,4>,
                         pni::static_array<pni::uint16,2,3,4>,
                         pni::static_array<pni::uint32,2,3,4>,
                         pni::static_array<pni::uint64,2,3,4>,
                         pni::static_array<pni::float32,2,3,4>,
                         pni::static_array<pni::float64,2,3,4>,
                         pni::static_array<pni::float128,2,3,4>,
                         pni::static_array<pni::complex32,2,3,4>,
                         pni::static_array<pni::complex64,2,3,4>,
                         pni::static_array<pni::complex128,2,3,4>
                        > static_array_types;

typedef boost::mpl::joint_view<
                               boost::mpl::joint_view<dyn_array_types,
                                                      fixed_dim_array_types>,
                               static_array_types> all_array_types;

