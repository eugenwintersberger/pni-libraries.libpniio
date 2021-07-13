//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Dec 2, 2014
//      Author: Eugen Wintersberger
//
#include <boost/test/unit_test.hpp>
#include <pni/nexus/xml/dimensions.hpp>
#include <pni/types.hpp>
#include <pni/error.hpp>
#include <pni/exceptions.hpp>

#include "dimensions_fixture.hpp"

using namespace pni::io::nexus;
using namespace pni::core;


BOOST_FIXTURE_TEST_SUITE(read_test,DimensionsFixture)


//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_read_1)
{
  read_file("dimensions/dim1.xml");

  hdf5::Dimensions shape = xml::Dimensions::object_from_xml(child_node);
  BOOST_CHECK(shape.size() == 2);
  BOOST_CHECK(shape.front() == 55);
  BOOST_CHECK(shape.back() == 100);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_read_2)
{
  read_file("dimensions/dim2.xml");

  BOOST_CHECK_THROW(xml::Dimensions::object_from_xml(child_node),
                    shape_mismatch_error);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_read_3)
{
  read_file("dimensions/dim3.xml");

  BOOST_CHECK_THROW(xml::Dimensions::object_from_xml(child_node),
                    key_error);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_read_4)
{
  read_file("dimensions/dim4.xml");

  BOOST_CHECK_THROW(xml::Dimensions::object_from_xml(child_node),
                    key_error);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_read_5)
{
  read_file("dimensions/dim5.xml");

  BOOST_CHECK_THROW(xml::Dimensions::object_from_xml(child_node),
                    key_error);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_read_6)
{
  read_file("dimensions/dim6.xml");
  auto s = xml::Dimensions::object_from_xml(child_node);
  BOOST_CHECK(s.size() == 0);
}

BOOST_AUTO_TEST_SUITE_END()
