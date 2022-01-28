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
//  Created on: Oct 16, 2015
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
//
#pragma once
#include <pni/types.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/joint_view.hpp>
#include <pni/arrays.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>


template<typename T> using sarray = pni::static_array<T,3,2>;
template<typename T> using farray = pni::fixed_dim_array<T,2>;

typedef boost::mpl::list<pni::dynamic_array<pni::uint8>,
                         pni::dynamic_array<pni::int8>,
                         pni::dynamic_array<pni::uint16>,
                         pni::dynamic_array<pni::int16>,
                         pni::dynamic_array<pni::uint32>,
                         pni::dynamic_array<pni::int32>,
                         pni::dynamic_array<pni::uint64>,
                         pni::dynamic_array<pni::int64>,
                         pni::dynamic_array<pni::float32>,
                         pni::dynamic_array<pni::float64>,
                         pni::dynamic_array<pni::float128>,
                         pni::dynamic_array<pni::complex32>,
                         pni::dynamic_array<pni::complex64>,
                         pni::dynamic_array<pni::complex128>,
                         pni::dynamic_array<pni::string>,
                         pni::dynamic_array<pni::bool_t>,
                         pni::dynamic_array<hdf5::datatype::EBool>
                         > dyn_array_types; 

typedef boost::mpl::list<sarray<pni::uint8>,
                         sarray<pni::int8>,
                         sarray<pni::uint16>,
                         sarray<pni::int16>,
                         sarray<pni::uint32>,
                         sarray<pni::int32>,
                         sarray<pni::uint64>,
                         sarray<pni::int64>,
                         sarray<pni::float32>,
                         sarray<pni::float64>,
                         sarray<pni::float128>,
                         sarray<pni::complex32>,
                         sarray<pni::complex64>,
                         sarray<pni::complex128>,
                         sarray<pni::string>,
                         sarray<pni::bool_t>,
                         sarray<hdf5::datatype::EBool>
                        > stat_array_types;

typedef boost::mpl::list<farray<pni::uint8>,
                         farray<pni::int8>,
                         farray<pni::uint16>,
                         farray<pni::int16>,
                         farray<pni::uint32>,
                         farray<pni::int32>,
                         farray<pni::uint64>,
                         farray<pni::int64>,
                         farray<pni::float32>,
                         farray<pni::float64>,
                         farray<pni::float128>,
                         farray<pni::complex32>,
                         farray<pni::complex64>,
                         farray<pni::complex128>,
                         farray<pni::string>,
                         farray<pni::bool_t>,
                         farray<hdf5::datatype::EBool>
                        > fix_array_types;

typedef boost::mpl::joint_view<
                              boost::mpl::joint_view<dyn_array_types,
                                                     stat_array_types>,
                              fix_array_types> all_array_types;
