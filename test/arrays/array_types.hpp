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
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
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

template<size_t TDimN>
using numeric_fixed_dim_arrays = 
        boost::mpl::list<pni::fixed_dim_array<pni::uint8,TDimN>,
                         pni::fixed_dim_array<pni::uint16,TDimN>,
                         pni::fixed_dim_array<pni::uint32,TDimN>,
                         pni::fixed_dim_array<pni::uint64,TDimN>,
                         pni::fixed_dim_array<pni::int8,TDimN>,
                         pni::fixed_dim_array<pni::int16,TDimN>,
                         pni::fixed_dim_array<pni::int32,TDimN>,
                         pni::fixed_dim_array<pni::int64,TDimN>,
                         pni::fixed_dim_array<pni::float32,TDimN>,
                         pni::fixed_dim_array<pni::float64,TDimN>,
                         pni::fixed_dim_array<pni::float128,TDimN>,
                         pni::fixed_dim_array<pni::complex32,TDimN>,
                         pni::fixed_dim_array<pni::complex64,TDimN>,
                         pni::fixed_dim_array<pni::complex128,TDimN>>;
                         

template<size_t TDimN>
using nonnumeric_fixed_dim_arrays = 
        boost::mpl::list<pni::fixed_dim_array<pni::string,TDimN>,
                         pni::fixed_dim_array<pni::bool_t,TDimN>,
                         pni::fixed_dim_array<hdf5::datatype::EBool,TDimN>>;

template<size_t TDimN>
using all_fixed_dim_arrays = 
        boost::mpl::joint_view<numeric_fixed_dim_arrays<TDimN>,
                               nonnumeric_fixed_dim_arrays<TDimN>>;

template<size_t... TDimsN>
using numeric_static_arrays = 
        boost::mpl::list<pni::static_array<pni::uint8,TDimsN... >,
                         pni::static_array<pni::uint16,TDimsN... >,
                         pni::static_array<pni::uint32,TDimsN... >,
                         pni::static_array<pni::uint64,TDimsN... >,
                         pni::static_array<pni::int8,TDimsN... >,
                         pni::static_array<pni::int16,TDimsN... >,
                         pni::static_array<pni::int32,TDimsN... >,
                         pni::static_array<pni::int64,TDimsN... >,
                         pni::static_array<pni::float32,TDimsN... >,
                         pni::static_array<pni::float64,TDimsN... >,
                         pni::static_array<pni::float128,TDimsN... >,
                         pni::static_array<pni::complex32,TDimsN... >,
                         pni::static_array<pni::complex64,TDimsN... >,
                         pni::static_array<pni::complex128,TDimsN...>>;

template<size_t... TDimsN>
using nonnumeric_static_arrays = 
        boost::mpl::list<pni::static_array<pni::string,TDimsN... >,
                         pni::static_array<pni::bool_t,TDimsN... >,
                         pni::static_array<hdf5::datatype::EBool,TDimsN... >>;

template<size_t... TDimsN>
using all_static_arrays = 
        boost::mpl::joint_view<numeric_static_arrays<TDimsN...>,
                               nonnumeric_static_arrays<TDimsN...>>;
                         
