//
// (c) Copyright 2017 DESY
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Dec 8, 2017
//
#include <boost/test/unit_test.hpp>
#include <pni/io/nexus/predicates.hpp>
#include <pni/io/nexus/base_class.hpp>
#include <pni/io/nexus/file.hpp>

using namespace pni::io;
using namespace hdf5;

struct PredicateTestFixture
{
    file::File nexus_file;
    node::Group root_group;
    node::Dataset dataset;

    PredicateTestFixture()
    {
      nexus_file = nexus::create_file("PredicateTest.nxs",
                                 file::AccessFlags::TRUNCATE);
      root_group = nexus_file.root();
      dataset = node::Dataset(root_group,"data",
                              datatype::create<int>(),
                              dataspace::Scalar());
    }
};


BOOST_FIXTURE_TEST_SUITE(PredicateTest,PredicateTestFixture)

// ===========================================================================
// testing the base class predicate
// ===========================================================================

BOOST_AUTO_TEST_SUITE(IsBaseClassTest)

BOOST_AUTO_TEST_CASE(success)
{
  BOOST_CHECK(nexus::IsBaseClass()(root_group));
  nexus::BaseClass entry(root_group,"entry","NXentry");
  BOOST_CHECK(nexus::IsBaseClass("NXentry")(entry));
}

BOOST_AUTO_TEST_CASE(fail)
{
  BOOST_CHECK(!nexus::IsBaseClass()(dataset));
  BOOST_CHECK(!nexus::IsBaseClass("NXmonochromator")(root_group));
}

BOOST_AUTO_TEST_SUITE_END()

// ===========================================================================
// testing the specialized base class predicates
// ===========================================================================

BOOST_AUTO_TEST_SUITE(BaseClassPredicateTests)

BOOST_AUTO_TEST_CASE(IsTransformation)
{
  nexus::BaseClass t(root_group,"transformations","NXtransformations");
  BOOST_CHECK(nexus::IsTransformation()(t));
  BOOST_CHECK(!nexus::IsTransformation()(root_group));
}

BOOST_AUTO_TEST_CASE(IsEntry)
{
  nexus::BaseClass entry(root_group,"entry","NXentry");
  BOOST_CHECK(nexus::IsEntry()(entry));
  BOOST_CHECK(!nexus::IsEntry()(root_group));
}

BOOST_AUTO_TEST_CASE(IsSubentry)
{
  nexus::BaseClass subentry(root_group,"subentry","NXsubentry");
  BOOST_CHECK(nexus::IsSubentry()(subentry));
  BOOST_CHECK(!nexus::IsSubentry()(root_group));
}

BOOST_AUTO_TEST_CASE(IsDetector)
{
  nexus::BaseClass detector(root_group,"detector","NXdetector");
  BOOST_CHECK(nexus::IsDetector()(detector));
  BOOST_CHECK(!nexus::IsDetector()(root_group));
}

BOOST_AUTO_TEST_CASE(IsInstrument)
{
  nexus::BaseClass instrument(root_group,"instrument","NXinstrument");
  BOOST_CHECK(nexus::IsInstrument()(instrument));
  BOOST_CHECK(!nexus::IsInstrument()(root_group));
}

BOOST_AUTO_TEST_CASE(IsSample)
{
  nexus::BaseClass sample(root_group,"sample","NXsample");
  BOOST_CHECK(nexus::IsSample()(sample));
  BOOST_CHECK(!nexus::IsSample()(root_group));
}

BOOST_AUTO_TEST_CASE(IsData)
{
  nexus::BaseClass data(root_group,"plot","NXdata");
  BOOST_CHECK(nexus::IsData()(data));
  BOOST_CHECK(!nexus::IsData()(root_group));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(NeXusNameConventionCheck)

BOOST_AUTO_TEST_CASE(test_valid_names)
{
  nexus::IsValidNeXusName check;
  BOOST_CHECK(check("temperature"));
  BOOST_CHECK(check("log"));
  BOOST_CHECK(check("sample_temperature"));
}

BOOST_AUTO_TEST_CASE(test_invalid_names)
{
  nexus::IsValidNeXusName check;
  BOOST_CHECK(!check("sample temperature"));
  BOOST_CHECK(!check("Sample"));
  BOOST_CHECK(!check(" Hello"));
  BOOST_CHECK(!check("sample$temperature"));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
