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
 *  Created on: Jul 9, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include <vector>
#include <list>
#include "check_size_test.hpp"

typedef dynamic_array<uint32> darray_t;
typedef dynamic_array<uint16> narray_t;
typedef std::vector<complex128> vector_t;
typedef std::list<string> list_t;

typedef check_size_test<darray_t,vector_t> test1_t;
typedef check_size_test<darray_t,list_t> test2_t;
typedef check_size_test<narray_t,vector_t> test3_t;
typedef check_size_test<narray_t,list_t> test4_t;

CPPUNIT_TEST_SUITE_REGISTRATION(test1_t);
CPPUNIT_TEST_SUITE_REGISTRATION(test2_t);
CPPUNIT_TEST_SUITE_REGISTRATION(test3_t);
CPPUNIT_TEST_SUITE_REGISTRATION(test4_t);

