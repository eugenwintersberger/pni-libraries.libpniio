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

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>

#include <pni/io/nx/nx.hpp>

using namespace pni::core;
using namespace pni::io::nx;

template<typename T>
class nxfield_inquiry_test: public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(nxfield_inquiry_test);
	CPPUNIT_TEST(test_filename);
    CPPUNIT_TEST(test_name);
    CPPUNIT_TEST(test_is_valid);
    CPPUNIT_TEST(test_size);
    CPPUNIT_TEST(test_rank);
    CPPUNIT_TEST(test_shape);
    CPPUNIT_TEST(test_type_id);
	CPPUNIT_TEST_SUITE_END();
    h5::nxfile f;
    h5::nxgroup root;
    h5::nxfield field;
    static const string filename;
    static const string fieldname;
    static const shape_t shape;
    static const size = 12;

    template<typename ST> 
    static void check_shape(const ST &a,const ST &b)
    {
        std::equal(a.begin(),a.end(),b.begin()); 
    }
public:
	void setUp();
	void tearDown();

	//testing basic file functionality
    void test_filename();
    void test_name();
    void test_is_valid();
    void test_size();
    void test_rank();
    void test_shape();
    void test_type_id();
};

template<typename T>
const string nxfield_inquiry_test<T>::filename="nxfield_inquiry_test.nxs";

template<typename T>
const string nxfield_inquiry_test<T>::fieldname = "test";

template<typename T>
const shape_t nxfield_inquiry_test<T>::shape = shape_t{3,4};

//------------------------------------------------------------------------------
template<typename T>
void nxfield_inquiry_test<T>::setUp() 
{ 
    f = h5::nxfile::create_file(filename,true);
    root = f.root();
    field = root.create_field<T>(fieldname,shape);
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_inquiry_test<T>::tearDown() 
{   
    root.close();
    field.close();
    f.close();
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_inquiry_test<T>::test_name()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(field.name() == fieldname);
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_inquiry_test<T>::test_filename()
{
    std::cerr<<BOOST_CURRENT_FUNCION<<std::endl;
    CPPUNIT_ASSERT(field.filename() == filename);
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_inquiry_test<T>::test_is_valid()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxfield f2; 
    CPPUNIT_ASSERT(!f2.is_valid());

    CPPUNIT_ASSERT(field.is_valid());
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_inquiry_test<T>::test_size()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(field.size() == size);
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_inquiry_test<T>::test_rank()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(field.rank() == 2);
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_inquiry_test<T>::test_shape()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    check_shape(field.shape<shape_t>(),shape);
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_inquiry_test<T>::test_type_id()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(field.type_id() == type_id_map<T>::type_id);
}


