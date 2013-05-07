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

#pragma once

#include <boost/current_function.hpp>
#include <functional>
#include <random>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nx_utils.hpp>
#include <pni/core/arrays.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "TestHelpers.hpp"

using namespace pni::core;
using namespace pni::io::nx;
class nxutils_test : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(nxutils_test);
    CPPUNIT_TEST(test_find_by_name);
    CPPUNIT_TEST(test_find_by_class);
    CPPUNIT_TEST(test_find_by_name_and_class);
    CPPUNIT_TEST_SUITE_END();

    private:
        h5::nxfile file;
        h5::nxgroup group;

    public:
        void setUp();
        void tearDown();

        void test_find_by_name();
        void test_find_by_class();
        void test_find_by_name_and_class();
};

