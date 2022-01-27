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
//  Created on: Oct 29, 2015 
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/arrays.hpp>
#include <pni/types.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/joint_view.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>
#include <cstddef>

typedef boost::mpl::list<pni::dynamic_array<pni::uint8>,
                         pni::dynamic_array<pni::uint16>,
                         pni::dynamic_array<pni::uint32>,
                         pni::dynamic_array<pni::uint64>,
                         pni::dynamic_array<pni::int8>,
                         pni::dynamic_array<pni::int16>,
                         pni::dynamic_array<pni::int32>,
                         pni::dynamic_array<pni::int64>,
                         pni::dynamic_array<pni::float32>,
                         pni::dynamic_array<pni::float64>,
                         pni::dynamic_array<pni::float128>,
                         pni::dynamic_array<pni::complex32>,
                         pni::dynamic_array<pni::complex64>,
                         pni::dynamic_array<pni::complex128>>
                         numeric_dynamic_arrays;

typedef boost::mpl::list<pni::dynamic_array<pni::string>,
                         pni::dynamic_array<pni::bool_t>,
                         pni::dynamic_array<hdf5::datatype::EBool>>
                         nonnumeric_dynamic_arrays;

typedef boost::mpl::joint_view<numeric_dynamic_arrays,
                               nonnumeric_dynamic_arrays>
                               all_dynamic_arrays;

template<size_t NDIMS>
using numeric_fixed_dim_arrays = 
        boost::mpl::list<pni::fixed_dim_array<pni::uint8,NDIMS>,
                         pni::fixed_dim_array<pni::uint16,NDIMS>,
                         pni::fixed_dim_array<pni::uint32,NDIMS>,
                         pni::fixed_dim_array<pni::uint64,NDIMS>,
                         pni::fixed_dim_array<pni::int8,NDIMS>,
                         pni::fixed_dim_array<pni::int16,NDIMS>,
                         pni::fixed_dim_array<pni::int32,NDIMS>,
                         pni::fixed_dim_array<pni::int64,NDIMS>,
                         pni::fixed_dim_array<pni::float32,NDIMS>,
                         pni::fixed_dim_array<pni::float64,NDIMS>,
                         pni::fixed_dim_array<pni::float128,NDIMS>,
                         pni::fixed_dim_array<pni::complex32,NDIMS>,
                         pni::fixed_dim_array<pni::complex64,NDIMS>,
                         pni::fixed_dim_array<pni::complex128,NDIMS>>;
                         

template<size_t NDIMS>
using nonnumeric_fixed_dim_arrays = 
        boost::mpl::list<pni::fixed_dim_array<pni::string,NDIMS>,
                         pni::fixed_dim_array<pni::bool_t,NDIMS>,
                         pni::fixed_dim_array<hdf5::datatype::EBool,NDIMS>>;

template<size_t NDIMS>
using all_fixed_dim_arrays = 
        boost::mpl::joint_view<numeric_fixed_dim_arrays<NDIMS>,
                               nonnumeric_fixed_dim_arrays<NDIMS>>;

template<size_t... DIMS>
using numeric_static_arrays = 
        boost::mpl::list<pni::static_array<pni::uint8,DIMS... >,
                         pni::static_array<pni::uint16,DIMS... >,
                         pni::static_array<pni::uint32,DIMS... >,
                         pni::static_array<pni::uint64,DIMS... >,
                         pni::static_array<pni::int8,DIMS... >,
                         pni::static_array<pni::int16,DIMS... >,
                         pni::static_array<pni::int32,DIMS... >,
                         pni::static_array<pni::int64,DIMS... >,
                         pni::static_array<pni::float32,DIMS... >,
                         pni::static_array<pni::float64,DIMS... >,
                         pni::static_array<pni::float128,DIMS... >,
                         pni::static_array<pni::complex32,DIMS... >,
                         pni::static_array<pni::complex64,DIMS... >,
                         pni::static_array<pni::complex128,DIMS...>>;

template<size_t... DIMS>
using nonnumeric_static_arrays = 
        boost::mpl::list<pni::static_array<pni::string,DIMS... >,
                         pni::static_array<pni::bool_t,DIMS... >,
                         pni::static_array<hdf5::datatype::EBool,DIMS... >>;

template<size_t... DIMS>
using all_static_arrays = 
        boost::mpl::joint_view<numeric_static_arrays<DIMS...>,
                               nonnumeric_static_arrays<DIMS...>>;
                         
