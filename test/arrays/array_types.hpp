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

template<size_t NDimsT>
using numeric_fixed_dim_arrays = 
        boost::mpl::list<pni::fixed_dim_array<pni::uint8,NDimsT>,
                         pni::fixed_dim_array<pni::uint16,NDimsT>,
                         pni::fixed_dim_array<pni::uint32,NDimsT>,
                         pni::fixed_dim_array<pni::uint64,NDimsT>,
                         pni::fixed_dim_array<pni::int8,NDimsT>,
                         pni::fixed_dim_array<pni::int16,NDimsT>,
                         pni::fixed_dim_array<pni::int32,NDimsT>,
                         pni::fixed_dim_array<pni::int64,NDimsT>,
                         pni::fixed_dim_array<pni::float32,NDimsT>,
                         pni::fixed_dim_array<pni::float64,NDimsT>,
                         pni::fixed_dim_array<pni::float128,NDimsT>,
                         pni::fixed_dim_array<pni::complex32,NDimsT>,
                         pni::fixed_dim_array<pni::complex64,NDimsT>,
                         pni::fixed_dim_array<pni::complex128,NDimsT>>;
                         

template<size_t NDimsT>
using nonnumeric_fixed_dim_arrays = 
        boost::mpl::list<pni::fixed_dim_array<pni::string,NDimsT>,
                         pni::fixed_dim_array<pni::bool_t,NDimsT>,
                         pni::fixed_dim_array<hdf5::datatype::EBool,NDimsT>>;

template<size_t NDimsT>
using all_fixed_dim_arrays = 
        boost::mpl::joint_view<numeric_fixed_dim_arrays<NDimsT>,
                               nonnumeric_fixed_dim_arrays<NDimsT>>;

template<size_t... DimsT>
using numeric_static_arrays = 
        boost::mpl::list<pni::static_array<pni::uint8,DimsT... >,
                         pni::static_array<pni::uint16,DimsT... >,
                         pni::static_array<pni::uint32,DimsT... >,
                         pni::static_array<pni::uint64,DimsT... >,
                         pni::static_array<pni::int8,DimsT... >,
                         pni::static_array<pni::int16,DimsT... >,
                         pni::static_array<pni::int32,DimsT... >,
                         pni::static_array<pni::int64,DimsT... >,
                         pni::static_array<pni::float32,DimsT... >,
                         pni::static_array<pni::float64,DimsT... >,
                         pni::static_array<pni::float128,DimsT... >,
                         pni::static_array<pni::complex32,DimsT... >,
                         pni::static_array<pni::complex64,DimsT... >,
                         pni::static_array<pni::complex128,DimsT...>>;

template<size_t... DimsT>
using nonnumeric_static_arrays = 
        boost::mpl::list<pni::static_array<pni::string,DimsT... >,
                         pni::static_array<pni::bool_t,DimsT... >,
                         pni::static_array<hdf5::datatype::EBool,DimsT... >>;

template<size_t... DimsT>
using all_static_arrays = 
        boost::mpl::joint_view<numeric_static_arrays<DimsT...>,
                               nonnumeric_static_arrays<DimsT...>>;
                         
