//
// Declaration of Nexus object template.
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
// along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================

#include <pni/core/types.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/back.hpp>
#include <pni/io/nx/nx.hpp>


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
                         pni::core::binary,
                         pni::core::bool_t,
                         pni::core::string> field_test_types;

typedef field_test_types attribute_test_types;

typedef boost::mpl::list<
        boost::mpl::vector<pni::io::nx::h5::nxgroup,pni::core::uint8>,
        boost::mpl::vector<pni::io::nx::h5::nxgroup,pni::core::int8>,
        boost::mpl::vector<pni::io::nx::h5::nxgroup,pni::core::uint16>,
        boost::mpl::vector<pni::io::nx::h5::nxgroup,pni::core::int16>,
        boost::mpl::vector<pni::io::nx::h5::nxgroup,pni::core::uint32>,
        boost::mpl::vector<pni::io::nx::h5::nxgroup,pni::core::int32>,
        boost::mpl::vector<pni::io::nx::h5::nxgroup,pni::core::uint64>,
        boost::mpl::vector<pni::io::nx::h5::nxgroup,pni::core::int64>,
        boost::mpl::vector<pni::io::nx::h5::nxgroup,pni::core::float32>,
        boost::mpl::vector<pni::io::nx::h5::nxgroup,pni::core::float64>,
#ifndef _MSC_VER
        boost::mpl::vector<pni::io::nx::h5::nxgroup,pni::core::float128>,
#endif
        boost::mpl::vector<pni::io::nx::h5::nxgroup,pni::core::complex32>,
        boost::mpl::vector<pni::io::nx::h5::nxgroup,pni::core::complex64>,
#ifndef _MSC_VER
        boost::mpl::vector<pni::io::nx::h5::nxgroup,pni::core::complex128>,
#endif
        boost::mpl::vector<pni::io::nx::h5::nxgroup,pni::core::binary>,
        boost::mpl::vector<pni::io::nx::h5::nxgroup,pni::core::string>,
        boost::mpl::vector<pni::io::nx::h5::nxgroup,pni::core::bool_t>
        > group_attr_types;

typedef boost::mpl::list<
        boost::mpl::vector<pni::io::nx::h5::nxfield,pni::core::uint8>,
        boost::mpl::vector<pni::io::nx::h5::nxfield,pni::core::int8>,
        boost::mpl::vector<pni::io::nx::h5::nxfield,pni::core::uint16>,
        boost::mpl::vector<pni::io::nx::h5::nxfield,pni::core::int16>,
        boost::mpl::vector<pni::io::nx::h5::nxfield,pni::core::uint32>,
        boost::mpl::vector<pni::io::nx::h5::nxfield,pni::core::int32>,
        boost::mpl::vector<pni::io::nx::h5::nxfield,pni::core::uint64>,
        boost::mpl::vector<pni::io::nx::h5::nxfield,pni::core::int64>,
        boost::mpl::vector<pni::io::nx::h5::nxfield,pni::core::float32>,
        boost::mpl::vector<pni::io::nx::h5::nxfield,pni::core::float64>,
#ifndef _MSC_VER
        boost::mpl::vector<pni::io::nx::h5::nxfield,pni::core::float128>,
#endif
        boost::mpl::vector<pni::io::nx::h5::nxfield,pni::core::complex32>,
        boost::mpl::vector<pni::io::nx::h5::nxfield,pni::core::complex64>,
#ifndef _MSC_VER
        boost::mpl::vector<pni::io::nx::h5::nxfield,pni::core::complex128>,
#endif
        boost::mpl::vector<pni::io::nx::h5::nxfield,pni::core::binary>,
        boost::mpl::vector<pni::io::nx::h5::nxfield,pni::core::string>,
        boost::mpl::vector<pni::io::nx::h5::nxfield,pni::core::bool_t>
        > field_attr_types;


typedef boost::mpl::joint_view<group_attr_types,
                               field_attr_types> parent_attr_types;                

typedef boost::mpl::list<pni::io::nx::h5::nxfield,
                         pni::io::nx::h5::nxgroup> attr_parent_types;
