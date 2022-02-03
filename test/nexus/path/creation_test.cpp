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
// Created on: Dec 15, 2017
//

#include "../../boost_unit_test.hpp"
#include <pni/nexus/path.hpp>

using namespace pni::nexus;

BOOST_AUTO_TEST_SUITE(PathTest)
BOOST_AUTO_TEST_SUITE(CreationTest)

BOOST_AUTO_TEST_CASE(test_abs_no_file)
{
  Path p = Path::from_string("/");
  BOOST_CHECK(p.size() == 1);
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.front().first == "/");
  BOOST_CHECK(p.front().second == "NXroot");

  p = Path::from_string("/./:NXentry/:NXinstrument/");
  BOOST_CHECK(p.size() == 4);
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.front().first == "/");
  BOOST_CHECK(p.front().second == "NXroot");

  p = Path::from_string("/../:NXentry/:NXinstrument");
  BOOST_CHECK(p.size() == 4);
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.front().first == "/");
  BOOST_CHECK(p.front().second == "NXroot");

  p = Path::from_string("/.");
  BOOST_CHECK(p.size() == 2);
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.front().first == "/");
  BOOST_CHECK(p.front().second == "NXroot");

  p = Path::from_string("/:NXroot");
  BOOST_CHECK(p.size() == 1);
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.front().first == "/");
  BOOST_CHECK(p.front().second == "NXroot");
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_abs_no_file_with_attribute)
{
  Path p = Path::from_string("/@date");
  BOOST_CHECK(p.size() == 1);
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.front().first == "/");
  BOOST_CHECK(p.front().second == "NXroot");
  BOOST_CHECK(p.attribute() == "date");

  p = Path::from_string("/./:NXentry/:NXinstrument/@date");
  BOOST_CHECK(p.size() == 4);
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.front().first == "/");
  BOOST_CHECK(p.front().second == "NXroot");
  BOOST_CHECK(p.attribute() == "date");

  p = Path::from_string("/../:NXentry/:NXinstrument@date");
  BOOST_CHECK(p.size() == 4);
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.front().first == "/");
  BOOST_CHECK(p.front().second == "NXroot");
  BOOST_CHECK(p.attribute() == "date");

  p = Path::from_string("/.@date");
  p = Path::from_string("/.");
  BOOST_CHECK(p.size() == 2);
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.front().first == "/");
  BOOST_CHECK(p.front().second == "NXroot");
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_abs_with_file)
{
  Path p = Path::from_string("test.nxs://");
  BOOST_CHECK(p.size() == 1);
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.filename() == "test.nxs");

  p = Path::from_string("/data/run/test.nxs://");
  BOOST_CHECK(p.size() == 1);
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.filename() == "/data/run/test.nxs");

  p= Path::from_string("test.nxs://:NXentry/:NXinstrument/pilatus:NXdetector");
  BOOST_CHECK(p.size() == 4);
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.filename() == "test.nxs");
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_abs_with_file_with_attribute)
{
  Path p = Path::from_string("test.nxs://@date");
  BOOST_CHECK(p.size() == 1);
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.filename() == "test.nxs");
  BOOST_CHECK(p.attribute() == "date");

  p= Path::from_string("/data/run/test.nxs://.@date");
  BOOST_CHECK(p.size() == 2);
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.filename() == "/data/run/test.nxs");
  BOOST_CHECK(p.attribute() == "date");

  p= Path::from_string("test.nxs://:NXentry/:NXinstrument/pilatus:NXdetector@date");
  BOOST_CHECK(p.size() == 4);
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.filename() == "test.nxs");
  BOOST_CHECK(p.attribute() == "date");
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_rel_no_attribute)
{
  //get an attribute
  Path p = Path::from_string("scan_1/:NXinstrument/value");
  BOOST_CHECK(!is_absolute(p));
  BOOST_CHECK(p.size() == 3);

  //get an attribute from the root group
  p = Path::from_string(".");
  BOOST_CHECK(!is_absolute(p));
  BOOST_CHECK(p.size() == 1);

  //get an attribute from the current group
  p = Path::from_string("..");
  BOOST_CHECK(!is_absolute(p));
  BOOST_CHECK(p.size() == 1);

  //get an attribute from the parent group
  p = Path::from_string("./:NXdetector");
  BOOST_CHECK(!is_absolute(p));
  BOOST_CHECK(p.size() == 2);
}

BOOST_AUTO_TEST_CASE(from_string_without_file)
{
  //test for a relative path without attribute
  std::string str = "../:NXdata/data";
  Path p = Path::from_string(str);
  BOOST_CHECK(p.filename().empty());
  BOOST_CHECK(p.attribute().empty());
  BOOST_CHECK(p.size() == 3);
  BOOST_CHECK(!is_absolute(p));
  BOOST_CHECK(Path::to_string(p) == str);

  //test for an absolute path without attribute
  str = "/scan_1/:NXinstrument/:NXdetector/";
  p = Path::from_string(str);
  BOOST_CHECK(p.filename().empty() && p.attribute().empty());
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.size() == 4);
  BOOST_CHECK(Path::to_string(p) == std::string(str,0,str.size()-1));

  //test for an absolute path without attribute
  str = "/scan_1/:NXinstrument/:NXdetector";
  p = Path::from_string(str);
  BOOST_CHECK(p.filename().empty() && p.attribute().empty());
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.size() == 4);
  BOOST_CHECK(Path::to_string(p) == str);

  str = "/";
  p = Path::from_string(str);
  BOOST_CHECK(p.filename().empty() && p.attribute().empty());
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.size() == 1);
  BOOST_CHECK(Path::to_string(p) == str);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(from_string_no_file_attr)
{
  //get an attribute
  std::string str = "/scan_1/:NXinstrument/value@test";
  Path p = Path::from_string(str);
  BOOST_CHECK(p.filename().empty());
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.size() == 4);
  BOOST_CHECK(p.attribute() == "test");
  BOOST_CHECK(Path::to_string(p) == str);

  //get an attribute from the root group
  str = "/@date";
  p = Path::from_string(str);
  BOOST_CHECK(p.filename().empty());
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.size() == 1);
  BOOST_CHECK(p.attribute() == "date");
  BOOST_CHECK(Path::to_string(p) == str);

  //get an attribute from the current group
  str = ".@date";
  p = Path::from_string(str);
  BOOST_CHECK(p.filename().empty());
  BOOST_CHECK(!is_absolute(p));
  BOOST_CHECK(p.size() == 1);
  BOOST_CHECK(p.attribute() == "date");
  BOOST_CHECK(Path::to_string(p) == str);

  //get an attribute from the parent group
  str = "..@date";
  p = Path::from_string(str);
  BOOST_CHECK(p.filename().empty());
  BOOST_CHECK(!is_absolute(p));
  BOOST_CHECK(p.size() == 1);
  BOOST_CHECK(p.attribute() == "date");
  BOOST_CHECK(Path::to_string(p) == str);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(from_string_with_file_attr)
{
  //get an attribute
  std::string str = "data/test/test.nx://scan_1/:NXinstrument/value@test";
  Path p = Path::from_string(str);
  BOOST_CHECK(p.filename() == "data/test/test.nx");
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.size() == 4);
  BOOST_CHECK(p.attribute() == "test");
  BOOST_CHECK(Path::to_string(p) == str);

  //get an attribute from the root group
  str = "test.nx://@date";
  p = Path::from_string(str);
  BOOST_CHECK(p.filename() == "test.nx");
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.size() == 1);
  BOOST_CHECK(p.attribute() == "date");
  BOOST_CHECK(Path::to_string(p) == str);

  //get an attribute from the current group
  str = "test.nx://:NXentry/:NXinstrument/.@date";
  p = Path::from_string(str);
  BOOST_CHECK(p.filename() == "test.nx");
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.size() == 4);
  BOOST_CHECK(p.attribute() == "date");
  BOOST_CHECK(Path::to_string(p) == str);

  //get an attribute from the parent group
  str = "test.nx://scan_1:NXentry/..@date";
  p = Path::from_string(str);
  BOOST_CHECK(p.filename() == "test.nx");
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.size() == 3);
  BOOST_CHECK(p.attribute() == "date");
  BOOST_CHECK(Path::to_string(p) == str);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_from_string_with_file)
{
  //test for an absolute path without attribute
  std::string str = "test.nx://";
  Path p = Path::from_string(str);
  BOOST_CHECK(p.filename() == "test.nx");
  BOOST_CHECK(p.attribute().empty());
  BOOST_CHECK(p.size() == 1);
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(p.front().first == "/");
  BOOST_CHECK(p.front().second == "NXroot");
  BOOST_CHECK(Path::to_string(p) == str);

  //test for an absolute path without attribute
  str = "test.nx://../:NXdata/data";
  p = Path::from_string(str);
  BOOST_CHECK(p.filename() == "test.nx");
  BOOST_CHECK(p.size() == 4);
  BOOST_CHECK(is_absolute(p));
  BOOST_CHECK(Path::to_string(p) == str);

}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
