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
 *  Created on: Jun 26, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <sstream>
#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "nxpath_utils_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(nxpath_utils_test);

//-----------------------------------------------------------------------------
void nxpath_utils_test::setUp() 
{ 
    p1 = "/home/wintersb/file.nx2:///entry/instrument/detector/data";
    p2 = "../../instrument/detector/data@time";
    p3 = "file.nx2:///:NXentry/:NXinstrument/:NXdetector/data";
}

//-----------------------------------------------------------------------------
void nxpath_utils_test::tearDown() { }


//-----------------------------------------------------------------------------
void nxpath_utils_test::test_path_input()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    nxpath p;
    std::stringstream is(p1);
    is>>p;
    CPPUNIT_ASSERT(p.size()==4);
    CPPUNIT_ASSERT(p.filename() == "/home/wintersb/file.nx2");
    CPPUNIT_ASSERT(p.attribute() == "");
    CPPUNIT_ASSERT(p.is_absolute());

    std::stringstream is2(p2);
    is2>>p;
    CPPUNIT_ASSERT(p.size()==5);
    CPPUNIT_ASSERT(p.filename() == "");
    CPPUNIT_ASSERT(p.attribute() == "time");
    CPPUNIT_ASSERT(!p.is_absolute());

    std::stringstream is3(p3);
    is3>>p;
    CPPUNIT_ASSERT(p.size()==4);
    CPPUNIT_ASSERT(p.filename() == "file.nx2");
    CPPUNIT_ASSERT(p.attribute() == "");
    CPPUNIT_ASSERT(p.is_absolute());

}

//-----------------------------------------------------------------------------
void nxpath_utils_test::test_path_output()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    nxpath path1 = path_from_string(p1);
    nxpath path2 = path_from_string(p2);
    nxpath path3 = path_from_string(p3);

    std::stringstream s1,s2,s3;
    s1<<path1;
    CPPUNIT_ASSERT(s1.str() == p1);
    s2<<path2;
    CPPUNIT_ASSERT(s2.str() == p2);
    s3<<path3;
    CPPUNIT_ASSERT(s3.str() == p3);
}

//-----------------------------------------------------------------------------
void nxpath_utils_test::test_path_strrep()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    nxpath path1 = path_from_string(p1);
    nxpath path2 = path_from_string(p2);
    nxpath path3 = path_from_string(p3);

    std::cout<<p1<<std::endl;
    std::cout<<string_from_path(path1)<<std::endl;
    CPPUNIT_ASSERT(string_from_path(path1) == p1);
    CPPUNIT_ASSERT(string_from_path(path2) == p2);
    CPPUNIT_ASSERT(string_from_path(path3) == p3);

}

//-----------------------------------------------------------------------------
void nxpath_utils_test::test_path_comparison()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    nxpath path1 = path_from_string(p1);
    nxpath path2 = path_from_string(p2);
    nxpath path3 = path_from_string(p1);

    CPPUNIT_ASSERT(path1 != path2);
    CPPUNIT_ASSERT(path1 == path3);
}

//-----------------------------------------------------------------------------
void nxpath_utils_test::test_path_split()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    nxpath path1 = path_from_string(p1);
    nxpath p1_1,p1_2;

    split_path(path1,path1.size()-1,p1_1,p1_2);

    CPPUNIT_ASSERT(path1.filename() == p1_1.filename());
    CPPUNIT_ASSERT(p1_2.filename() == "");
    CPPUNIT_ASSERT(p1_1.is_absolute());
    CPPUNIT_ASSERT(!p1_2.is_absolute());

    std::cout<<p1_1<<std::endl;
    std::cout<<p1_2<<std::endl;

    nxpath p;
    CPPUNIT_ASSERT_THROW(split_last(p,p1_1,p1_2),index_error);
    CPPUNIT_ASSERT_THROW(split_path(path1,10,p1_1,p1_2),index_error);
    CPPUNIT_ASSERT(p1_1.is_absolute());
    CPPUNIT_ASSERT(!p1_2.is_absolute());


}
