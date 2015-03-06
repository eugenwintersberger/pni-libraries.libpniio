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
class nxfield_creation_test: public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(nxfield_creation_test);
	CPPUNIT_TEST(test_scalar);
    CPPUNIT_TEST(test_multidim_default_chunk);
    CPPUNIT_TEST(test_multidim_custom_chunk);
    CPPUNIT_TEST(test_multidim_default_chunk_filter);
    CPPUNIT_TEST(test_multidim_custom_chunk_filter);
	CPPUNIT_TEST_SUITE_END();
    h5::nxfile f;
    h5::nxgroup root;
    static const string filename;

    template<typename ST> 
    static void check_shape(const ST &a,const ST &b)
    {
        std::equal(a.begin(),a.end(),b.begin()); 
    }
public:
	void setUp();
	void tearDown();

	//testing basic file functionality
    void test_scalar();
    void test_multidim_default_chunk();
    void test_multidim_custom_chunk();
    void test_multidim_default_chunk_filter();
    void test_multidim_custom_chunk_filter();
};

template<typename T>
const string nxfield_creation_test<T>::filename="nxfield_creation_test.nxs";

//------------------------------------------------------------------------------
template<typename T>
void nxfield_creation_test<T>::setUp() 
{ 
    f = h5::nxfile::create_file(filename,true);
    root = f.root();
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_creation_test<T>::tearDown() 
{   
    root.close();
    f.close();
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_creation_test<T>::test_scalar()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxfield field;

    CPPUNIT_ASSERT_NO_THROW(field = root.create_field<T>("test"));
    CPPUNIT_ASSERT(field.size()==1);
    CPPUNIT_ASSERT(field.rank()==1);
    check_shape(field.shape<shape_t>(),shape_t{1});

    //should throw - the field already exists
    CPPUNIT_ASSERT_THROW(root.create_field<T>("test"),object_error);
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_creation_test<T>::test_multidim_default_chunk()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxfield field;

    CPPUNIT_ASSERT_NO_THROW(field = root.create_field<T>("test",shape_t{3,4}));
    CPPUNIT_ASSERT(field.size()==12);
    CPPUNIT_ASSERT(field.rank()==2);
    check_shape(field.shape<shape_t>(),shape_t{3,4});
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_creation_test<T>::test_multidim_custom_chunk()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxfield field;
    shape_t s{3,4},c{1,4};

    CPPUNIT_ASSERT_NO_THROW(field = root.create_field<T>("test",s,c));
    CPPUNIT_ASSERT(field.size()==12);
    CPPUNIT_ASSERT(field.rank()==2);
    check_shape(field.shape<shape_t>(),shape_t{3,4});

    //check error cases
    CPPUNIT_ASSERT_THROW(root.create_field<T>("error1",s,shape_t{4}),
                         size_mismatch_error);
    CPPUNIT_ASSERT_THROW(root.create_field<T>("test",s,c),object_error);

}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_creation_test<T>::test_multidim_default_chunk_filter()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxdeflate_filter filter(9,true);
    h5::nxfield field;
    shape_t s{3,4};

    CPPUNIT_ASSERT_NO_THROW(field = root.create_field<T>("test",s,filter));
    CPPUNIT_ASSERT(field.size()==12);
    CPPUNIT_ASSERT(field.rank()==2);
    check_shape(field.shape<shape_t>(),s);
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_creation_test<T>::test_multidim_custom_chunk_filter()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxdeflate_filter filter(9,true);
    h5::nxfield field;
    shape_t s{3,4},c{1,4};

    CPPUNIT_ASSERT_NO_THROW(field = root.create_field<T>("test",s,c,filter));
    CPPUNIT_ASSERT(field.size()==12);
    CPPUNIT_ASSERT(field.rank()==2);
    check_shape(field.shape<shape_t>(),shape_t{3,4});

    //check error cases
    CPPUNIT_ASSERT_THROW(root.create_field<T>("error1",s,shape_t{4},filter),
                         size_mismatch_error);
    CPPUNIT_ASSERT_THROW(root.create_field<T>("test",s,c,filter),object_error);
}
