//
// Declaration of Nexus object template.
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
//  Created on: Sep 10, 2014
//      Author: Eugen Wintersberger
//

#include <boost/current_function.hpp>
#include "flat_group_test.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxobject_type.hpp>
#include <pni/io/nx/algorithms.hpp>
#include <pni/io/exceptions.hpp>

using pni::io::invalid_object_error;

CPPUNIT_TEST_SUITE_REGISTRATION(flat_group_test);

//------------------------------------------------------------------------------
void flat_group_test::setUp()
{
    _f = h5::nxfile::create_file("flat_group_test.nxs",true);
    h5::nxgroup g=_f.root();
    g = g.create_group("entry","NXentry");
    g.create_group("sample","NXsample");
    g.create_group("control","NXmonitor");
    g = g.create_group("instrument","NXinstrument");
    g.create_group("detector","NXdetector");
    g.create_group("machine","NXsource");
    g.create_group("unudlator","NXinsertion_device");
    g.create_group("monochromator","NXmonochromator");

}

//------------------------------------------------------------------------------
void flat_group_test::tearDown()
{
	_f.close();
}


//------------------------------------------------------------------------------
void flat_group_test::test_creation()
{
	std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    //construct from a group type
    auto fgroup = make_flat(_f.root());
    CPPUNIT_ASSERT(fgroup.size() == 8);
    CPPUNIT_ASSERT_THROW(make_flat(h5::nxgroup()),invalid_object_error);

    //construct from an object 
    fgroup = make_flat(get_object(_f.root(),nxpath::from_string("entry:NXentry")));
    CPPUNIT_ASSERT(fgroup.size()==7);

    
    CPPUNIT_ASSERT_THROW(make_flat(h5::nxobject(h5::nxgroup())),
                         invalid_object_error);
                         
}

