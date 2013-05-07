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
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: May 7, 2013
 *      Author: Eugen Wintersberger
 */

#include "nxpath_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(nxpath_test);

//-----------------------------------------------------------------------------
void nxpath_test::setUp()
{
    path_1 = "/home/data/file.h5:///entry:NXentry/:NXinstrument/:NXdetector/data";
    path_2 = "/entry:NXentry/:NXinstrument/:NXdetector/data";
    path_3 = "/:NXentry/:NXinstrument/:NXdetector/data@time";
}

//-----------------------------------------------------------------------------
void nxpath_test::tearDown()
{

}

//-----------------------------------------------------------------------------
void nxpath_test::test_split_string()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    string file,group,attribute;

    split_path(path_1,file,group,attribute);
    CPPUNIT_ASSERT(file=="/home/data/file.h5");
    CPPUNIT_ASSERT(group=="/entry:NXentry/:NXinstrument/:NXdetector/data");
    CPPUNIT_ASSERT(attribute=="");

    split_path(path_2,file,group,attribute);
    CPPUNIT_ASSERT(file=="");
    CPPUNIT_ASSERT(group=="/entry:NXentry/:NXinstrument/:NXdetector/data");
    CPPUNIT_ASSERT(attribute=="");
    
    split_path(path_3,file,group,attribute);
    CPPUNIT_ASSERT(file=="");
    CPPUNIT_ASSERT(group=="/:NXentry/:NXinstrument/:NXdetector/data");
    CPPUNIT_ASSERT(attribute=="time");

}

//-----------------------------------------------------------------------------
void nxpath_test::test_parse()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxpath path = path_from_string(path_1);
    CPPUNIT_ASSERT(path.filename() == "/home/data/file.h5");
    CPPUNIT_ASSERT(path.attribute() == "");
    CPPUNIT_ASSERT(path.size() == 4);
    auto iter = path.begin();
    CPPUNIT_ASSERT(iter->first == "entry");
    CPPUNIT_ASSERT(iter->second == "NXentry");
    ++iter;
    CPPUNIT_ASSERT(iter->first == "");
    CPPUNIT_ASSERT(iter->second == "NXinstrument");
    ++iter;
    CPPUNIT_ASSERT(iter->first == "");
    CPPUNIT_ASSERT(iter->second == "NXdetector");
    ++iter;
    CPPUNIT_ASSERT(iter->first == "data");
    CPPUNIT_ASSERT(iter->second == "");

    path = path_from_string(path_3);
    iter = path.begin();
    CPPUNIT_ASSERT(iter->first == "");
    CPPUNIT_ASSERT(iter->second == "NXentry");
    ++iter;
    CPPUNIT_ASSERT(iter->first == "");
    CPPUNIT_ASSERT(iter->second == "NXinstrument");
    ++iter;
    CPPUNIT_ASSERT(iter->first == "");
    CPPUNIT_ASSERT(iter->second == "NXdetector");
    ++iter;
    CPPUNIT_ASSERT(iter->first == "data");
    CPPUNIT_ASSERT(iter->second == "");
    

}
