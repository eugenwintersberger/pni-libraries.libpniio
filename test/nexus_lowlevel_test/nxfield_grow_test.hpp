//
// Declaration of Nexus object template.
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
// along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================

//testing class for ArrayShape objects

#pragma once

#include <vector>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include "../uniform_distribution.hpp"
#include "../EqualityCheck.hpp"

#include <pni/io/nx/nx.hpp>

using namespace pni::core;
using namespace pni::io::nx;

template<typename T>
class nxfield_grow_test: public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(nxfield_grow_test);
	CPPUNIT_TEST(test_grow_1d);
    CPPUNIT_TEST(test_grow_2d);
	CPPUNIT_TEST_SUITE_END();
    static const string filename;
    static const shape_t shape;
    static const size_t size = 12;
    
    h5::nxfile f;
    h5::nxgroup root;
public:
	void setUp();
	void tearDown();

	//testing basic file functionality
    void test_grow_1d();
    void test_grow_2d();
};

template<typename T>
const string nxfield_grow_test<T>::filename="nxfield_grow_test.nxs";

template<typename T>
const shape_t nxfield_grow_test<T>::shape=shape_t{3,4};

//------------------------------------------------------------------------------
template<typename T>
void nxfield_grow_test<T>::setUp() 
{ 
    //create a new file
    f     = h5::nxfile::create_file(filename,true);
    root  = f.root();
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_grow_test<T>::tearDown() 
{ 
    root.close();
    f.close();
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_grow_test<T>::test_grow_1d()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxfield field = root.create_field<T>("test",shape_t{0});
    CPPUNIT_ASSERT(field.is_valid());
    CPPUNIT_ASSERT(field.size() == 0);
    CPPUNIT_ASSERT(field.rank() == 1);

    CPPUNIT_ASSERT_NO_THROW(field.grow(0,1));
    CPPUNIT_ASSERT(field.size() == 1);

    CPPUNIT_ASSERT_NO_THROW(field.grow(0,10));
    CPPUNIT_ASSERT(field.size()==11);
   
    CPPUNIT_ASSERT_THROW(field.grow(1,3),index_error);
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_grow_test<T>::test_grow_2d()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5::nxfield f = root.create_field<T>("test",shape_t{3,4});
    CPPUNIT_ASSERT(f.rank() == 2);
    CPPUNIT_ASSERT(f.size() == 12);

    CPPUNIT_ASSERT_NO_THROW(f.grow(0,2));
    CPPUNIT_ASSERT(f.size() == 20);

    CPPUNIT_ASSERT_NO_THROW(f.grow(1,4));
    CPPUNIT_ASSERT(f.size() == 40);
}

