/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
    group.create_group("sample","NXsample");
    group.create_group("monitor","NXcontrol");
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: May 7, 2013
 *      Author: Eugen Wintersberger
 */

#include "nxutils_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(nxutils_test);

//-----------------------------------------------------------------------------
void nxutils_test::setUp()
{
    file = h5::nxfile::create_file("nxutils_test.h5",true);
    //need to create some groups
    group = file.create_group("entry","NXentry");
    group.create_group("sample","NXsample");
    group.create_group("monitor","NXcontrol");
    group = group.create_group("instrument","NXinstrument");

    group.create_group("detector","NXdetector");
    group.create_group("undulator","NXinsertion_device");
    group.create_group("synchrotron","NXsource");
    

}

//-----------------------------------------------------------------------------
void nxutils_test::tearDown()
{
    group.close();
    file.close();
}

//-----------------------------------------------------------------------------
void nxutils_test::test_find_by_name()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    group = file["/entry/instrument"];
    h5::nxgroup g;
    CPPUNIT_ASSERT(find_group_by_name(group,"detector",g));
    CPPUNIT_ASSERT(g.name() == "detector");
    CPPUNIT_ASSERT(!find_group_by_name(group,"blabla",g));
}

//-----------------------------------------------------------------------------
void nxutils_test::test_find_by_class()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    group = file["/entry/instrument"];
    h5::nxgroup g;
    CPPUNIT_ASSERT(find_group_by_class(group,"NXdetector",g));
    CPPUNIT_ASSERT(g.name() == "detector");
    CPPUNIT_ASSERT(!find_group_by_class(group,"blabla",g));

}

//-----------------------------------------------------------------------------
void nxutils_test::test_find_by_name_and_class()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    group = file["/entry/instrument"];
    h5::nxgroup g;
    CPPUNIT_ASSERT(find_group_by_name_and_class(group,"detector","NXdetector",g));
    CPPUNIT_ASSERT(g.name() == "detector");
    CPPUNIT_ASSERT(!find_group_by_name_and_class(group,"blabla","NXblub",g));

}
