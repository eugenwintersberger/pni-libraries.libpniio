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
class nxattribute_view_io_test: public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(nxattribute_view_io_test);
	CPPUNIT_TEST(test_rvalue_cont_view);
    CPPUNIT_TEST(test_rvalue_discont_view);
    CPPUNIT_TEST(test_lvalue_cont_view);
    CPPUNIT_TEST(test_lvalue_discont_view);
	CPPUNIT_TEST_SUITE_END();

    //static members
    static const string  filename;
    static const shape_t attr_shape;
    static const shape_t array_shape;
    static const size_t size = 12;

    //some types
    typedef std::vector<T>          buffer_type;
    typedef dynamic_array<T>        mdarray_type;
    typedef uniform_distribution<T> distribution_type;
   
    //member variables
    h5::nxfile        f;
    h5::nxgroup       root;
    h5::nxattribute   attr;
    buffer_type       buffer;
    distribution_type rand_dist;
    mdarray_type      array;
public:
	void setUp();
	void tearDown();

	//testing basic file functionality
    void test_rvalue_cont_view();
    void test_rvalue_discont_view();
    void test_lvalue_cont_view();
    void test_lvalue_discont_view();
};

template<typename T>
const string nxattribute_view_io_test<T>::filename="nxattribute_view_io_test.nxs";

template<typename T>
const shape_t nxattribute_view_io_test<T>::attr_shape=shape_t{3,4};

template<typename T>
const shape_t nxattribute_view_io_test<T>::array_shape = shape_t{10,20};

//------------------------------------------------------------------------------
template<typename T>
void nxattribute_view_io_test<T>::setUp() 
{ 
    //create a new file
    f = h5::nxfile::create_file(filename,true);
    root = f.root();
    attr = root.attributes.create<T>("test",attr_shape);

    //setup random number generator
    rand_dist = distribution_type();

    //generate random data
    buffer = buffer_type(size);
    std::generate(buffer.begin(),buffer.end(),rand_dist);

    array= mdarray_type::create(array_shape);
    std::generate(array.begin(),array.end(),rand_dist);
}

//----------------------------------------------------------------------------
template<typename T>
void nxattribute_view_io_test<T>::tearDown() 
{ 
    attr.close();
    root.close();
    f.close();
}

//----------------------------------------------------------------------------
template<typename T>
void nxattribute_view_io_test<T>::test_rvalue_cont_view()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    //write data
    CPPUNIT_ASSERT_NO_THROW(attr.write(array(0,slice(0,12))));
    //read data
    CPPUNIT_ASSERT_NO_THROW(attr.read(array(1,slice(0,12))));

    for(size_t i=0;i<12;++i)
        check_equality(array[i],array[i]);

}

//----------------------------------------------------------------------------
template<typename T>
void nxattribute_view_io_test<T>::test_rvalue_discont_view()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    //write data
    CPPUNIT_ASSERT_NO_THROW(attr.write(array(slice(0,3),slice(0,4))));
    //read data
    CPPUNIT_ASSERT_NO_THROW(attr.read(array(slice(3,6),slice(0,4))));

    for(size_t i=0;i<attr_shape[0];++i)
    {
        for(size_t j=0;j<attr_shape[1];++j)
        {
            check_equality(array(i,j),array(i+3,j));
        }
    }
}

//----------------------------------------------------------------------------
template<typename T>
void nxattribute_view_io_test<T>::test_lvalue_discont_view()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    auto write = array(slice(0,3),slice(0,4));
    auto read  = array(slice(3,6),slice(0,4));

    //write data
    CPPUNIT_ASSERT_NO_THROW(attr.write(write));
    //read data
    CPPUNIT_ASSERT_NO_THROW(attr.read(read));

    for(size_t i=0;i<attr_shape[0];++i)
    {
        for(size_t j=0;j<attr_shape[1];++j)
        {
            check_equality(read(i,j),write(i,j));
        }
    }
}

//---------------------------------------------------------------------------
template<typename T>
void nxattribute_view_io_test<T>::test_lvalue_cont_view()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    auto write = array(0,slice(0,12));
    auto read  = array(1,slice(0,12));

    //write data
    CPPUNIT_ASSERT_NO_THROW(attr.write(write));
    //read data
    CPPUNIT_ASSERT_NO_THROW(attr.read(read));

    for(size_t i=0;i<write.size();++i)
        check_equality(write[i],read[i]);
}

