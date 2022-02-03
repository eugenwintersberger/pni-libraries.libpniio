//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Dec 2, 2014
//      Author: Eugen Wintersberger
//

#include "../../boost_unit_test.hpp"
#include <boost/current_function.hpp>
#include <pni/types.hpp>
#include <pni/nexus/xml/dimensions.hpp>
#include "dimensions_fixture.hpp"

using namespace pni;
using namespace pni::nexus;


BOOST_AUTO_TEST_SUITE(NexusXMLTest)

BOOST_FIXTURE_TEST_SUITE(inquery_test,DimensionsFixture)

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_rank)
{
  read_file("dimensions/dim1.xml");

  BOOST_CHECK(xml::Dimensions::rank(child_node) == 2);

  read_file("dimensions/dim6.xml");
  BOOST_CHECK(xml::Dimensions::rank(child_node) == 0);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_size)
{
  read_file("dimensions/dim1.xml");

  BOOST_CHECK(xml::Dimensions::size(child_node) == 100*55);

  read_file("dimensions/dim6.xml");
  BOOST_CHECK(xml::Dimensions::size(child_node) == 1);

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

