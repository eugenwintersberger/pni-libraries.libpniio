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
 *  Created on: May 06, 2013
 *      Author: Eugen Wintersberger
 */

#pragma once

#include <boost/current_function.hpp>
#include <boost/variant.hpp>
#include <pni/io/parsers/record_parser.hpp>
#include <pni/core/types.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "../TestHelpers.hpp"

using namespace pni::core;
using namespace pni::io;

//need a few visitors to do the job
class get_type_id : public boost::static_visitor<type_id_t>
{
    public:
        type_id_t operator()(const value &v) const
        {
            return v.type_id();
        }

        type_id_t operator()(const array &a) const
        {
            return a.type_id();
        }
};

template<typename T,size_t i=0> 
class get_value : public boost::static_visitor<T>
{
    public:
        T operator()(const value &v) const
        {
            return v.template as<T>();
        }

        T operator()(const array &v) const
        {
            return v[i].template as<T>();
        }
};


class record_parser_test:public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(record_parser_test);
    CPPUNIT_TEST(test_pure_scalar);
    CPPUNIT_TEST(test_array_value);
	CPPUNIT_TEST_SUITE_END();

    typedef string::const_iterator iterator_t;
    typedef record_parser<iterator_t> record_parser_t;
    record_parser_t parser;
public:
	void setUp();
	void tearDown();
	void test_pure_scalar();
    void test_array_value();
};


