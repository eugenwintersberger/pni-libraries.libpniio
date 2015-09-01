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
#pragma once

#include <pni/io/nx/xml/dimensions.hpp>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class read_fixture : public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(read_fixture);
        CPPUNIT_TEST(test_read_1);
        CPPUNIT_TEST(test_read_2);
        CPPUNIT_TEST(test_read_3);
        CPPUNIT_TEST(test_read_4);
        CPPUNIT_TEST(test_read_5);
        CPPUNIT_TEST(test_read_6);
        CPPUNIT_TEST_SUITE_END();

        pni::io::nx::xml::node root;
        pni::io::nx::xml::node child;

        void setup_xml(const pni::core::string &fname);

    public:
        void setUp();
        void tearDown();
        
        void test_read_1();
        void test_read_2();
        void test_read_3();
        void test_read_4();
        void test_read_5();
        void test_read_6();
};
