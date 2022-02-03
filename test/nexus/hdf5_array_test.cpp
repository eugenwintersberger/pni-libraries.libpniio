//
// (c) Copyright 2017 DESY
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Dec 12, 2017
//
#include <boost/test/included/unit_test.hpp>
#include <pni/nexus.hpp>
#include <pni/arrays.hpp>
#include <pni/type_erasures/array.hpp>
#include "hdf5_support_fixture.hpp"

using namespace pni;

BOOST_FIXTURE_TEST_SUITE(HDF5SupportTest,HDF5SupportFixture)

BOOST_AUTO_TEST_CASE(test_array_integers)
{
  using pni::shape_t;
  using array_type = pni::dynamic_array<int>;
  using storage_type = array_type::storage_type;
  storage_type     write_payload{1,2,3,4,5};
  pni::array write(array_type::create(shape_t{5},write_payload));

  hdf5::dataspace::Simple space = hdf5::dataspace::create(write);
  hdf5::datatype::Datatype type = hdf5::datatype::create(write);
  dataset = hdf5::node::Dataset(root_group,"data",type,space);
  dataset.write(write);

  pni::array read(array_type::create(shape_t{5}));
  dataset.read(read);
  storage_type read_payload;
  std::transform(read.begin(),read.end(),std::back_inserter(read_payload),
                 [](pni::value v) { return v.as<int>();});

  BOOST_CHECK_EQUAL_COLLECTIONS(write_payload.begin(),write_payload.end(),
                                read_payload.begin(),read_payload.end());

}


BOOST_AUTO_TEST_CASE(test_mdarray_integers)
{
  using pni::shape_t;
  using array_type = pni::dynamic_array<int>;
  using storage_type = array_type::storage_type;
  shape_t shape{5};
  auto write = array_type::create(shape,storage_type{1,2,3,4,5});

  hdf5::dataspace::Simple space = hdf5::dataspace::create(write);
  hdf5::datatype::Datatype type = hdf5::datatype::create(write);
  dataset = hdf5::node::Dataset(root_group,"data",type,space);
  dataset.write(write);

  auto read = array_type::create(shape);
  dataset.read(read);

  BOOST_CHECK_EQUAL_COLLECTIONS(write.begin(),write.end(),
                                read.begin(),read.end());

}

BOOST_AUTO_TEST_CASE(test_mdarray_strings)
{
  using pni::shape_t;
  using array_type = pni::dynamic_array<std::string>;
  using storage_type = array_type::storage_type;
  shape_t shape{5};
  auto write = array_type::create(shape,storage_type{"hello","world","a stupid","test","with arrays"});

  hdf5::dataspace::Simple space = hdf5::dataspace::create(write);
  hdf5::datatype::Datatype type = hdf5::datatype::create(write);
  dataset = hdf5::node::Dataset(root_group,"data",type,space);
  dataset.write(write);

  auto read = array_type::create(shape);
  dataset.read(read);

  BOOST_CHECK_EQUAL_COLLECTIONS(write.begin(),write.end(),
                                read.begin(),read.end());
}


BOOST_AUTO_TEST_SUITE_END()
