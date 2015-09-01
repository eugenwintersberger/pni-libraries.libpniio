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

#include <boost/current_function.hpp>
#include "inquery_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

CPPUNIT_TEST_SUITE_REGISTRATION(inquery_fixture);

void inquery_fixture::setUp()
{}

//----------------------------------------------------------------------------
void inquery_fixture::tearDown()
{}

//----------------------------------------------------------------------------
void inquery_fixture::setup_xml(const string &fname)
{
    root = xml::create_from_file(fname);
    child = root.get_child("dimensions");
}

//-----------------------------------------------------------------------------
void inquery_fixture::test_rank()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    setup_xml("dim1.xml");

    CPPUNIT_ASSERT(xml::dimensions::rank(child)==2);

    setup_xml("dim6.xml");
    CPPUNIT_ASSERT(xml::dimensions::rank(child)==0);
}

//-----------------------------------------------------------------------------
void inquery_fixture::test_size()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    setup_xml("dim1.xml");

    CPPUNIT_ASSERT(xml::dimensions::size(child)==100*55);

    setup_xml("dim6.xml");
    CPPUNIT_ASSERT(xml::dimensions::size(child)==1);

}


