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
//  Created on: Oct 17, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include <pni/types.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>
#include <boost/mpl/list.hpp>

typedef boost::mpl::list<
	                     //pni::uint8,
                         pni::int8,
                         pni::uint16,
                         pni::int16,
                         pni::uint32,
                         pni::int32,
                         pni::uint64,
                         pni::int64,
                         pni::float32,
                         pni::float64,
                         pni::float128,
                         pni::complex32,
                         pni::complex64,
                         pni::complex128,
                         pni::string,
                         hdf5::datatype::EBool,
                         pni::bool_t
                        > all_types;
