//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: May 4, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/io/nexus/path.hpp>

using namespace pni::core;
using namespace pni::io::nexus;

namespace std{
    
    ostream &operator<<(ostream &stream,const Path::Element &e)
    {
        stream<<e.first<<":"<<e.second;
        return stream;
    }
}

BOOST_AUTO_TEST_SUITE(PathTest)
BOOST_AUTO_TEST_SUITE(ElementEqualityTest)
    
using Element = Path::Element;

BOOST_AUTO_TEST_CASE(test_equality)
{
  BOOST_CHECK_EQUAL(Element("entry","NXentry") ,
                    Element("entry","NXentry"));

  BOOST_CHECK_EQUAL(Element("","NXentry") ,
                    Element("","NXentry"));

  BOOST_CHECK_EQUAL(Element("entry","") ,
                    Element("entry",""));
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_inequality)
{
  BOOST_CHECK_NE(Element("entry","NXentry") ,
                 Element("scan_1","NXentry"));
  BOOST_CHECK_NE(Element("entry","NXinstrument") ,
                 Element("entry","NXentry"));

  BOOST_CHECK_NE(Element("","NXentry"),
                 Element("entry","NXentry"));
  BOOST_CHECK_NE(Element("entry","NXentry"),
                 Element("entry",""));

  BOOST_CHECK_NE(Element("entry","NXentry") ,
                 Element("","NXentry"));
  BOOST_CHECK_NE(Element("","NXentry") ,
                 Element("entry","NXentry"));

  BOOST_CHECK_NE(Element("","NXentry") ,
                 Element("","NXinstrument"));
  BOOST_CHECK_NE(Element("entry","") ,
                 Element("scan1",""));

}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

