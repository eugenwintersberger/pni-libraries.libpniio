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
class nxfield_io_test: public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(nxfield_io_test);
	CPPUNIT_TEST(test_mdarray);
    CPPUNIT_TEST(test_mdarray_error);
    CPPUNIT_TEST(test_array);
    CPPUNIT_TEST(test_array_error);
    CPPUNIT_TEST(test_pointer);
    CPPUNIT_TEST(test_pointer_error);
    CPPUNIT_TEST(test_scalar);
    CPPUNIT_TEST(test_scalar_error);
	CPPUNIT_TEST_SUITE_END();
    static const string filename;
    static const shape_t shape;
    static const size_t size = 12;

    typedef std::vector<T> buffer_type;
    typedef dynamic_array<T> mdarray_type;
    typedef uniform_distribution<T> distribution_type;
    
    h5::nxfile f;
    h5::nxgroup root;
    h5::nxfield field;
    buffer_type buffer;
    distribution_type rand_dist;
public:
	void setUp();
	void tearDown();

	//testing basic file functionality
    void test_mdarray();
    void test_mdarray_error();
    void test_array();
    void test_array_error();
    void test_pointer();
    void test_pointer_error();
    void test_scalar();
    void test_scalar_error();
};

template<typename T>
const string nxfield_io_test<T>::filename="nxfield_io_test.nxs";

template<typename T>
const shape_t nxfield_io_test<T>::shape=shape_t{3,4};

//------------------------------------------------------------------------------
template<typename T>
void nxfield_io_test<T>::setUp() 
{ 
    //create a new file
    f = h5::nxfile::create_file(filename,true);
    root = f.root();
    field = root.create_field<T>("test",shape);

    //setup random number generator
    rand_dist = distribution_type();

    //generate random data
    buffer = buffer_type(size);
    std::generate(buffer.begin(),buffer.end(),rand_dist);
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_io_test<T>::tearDown() 
{ 
    field.close();
    root.close();
    f.close();
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_io_test<T>::test_mdarray()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    auto write_data = mdarray_type::create(shape,buffer);
    auto read_data  = mdarray_type::create(shape);

    //write data
    CPPUNIT_ASSERT_NO_THROW(field.write(write_data));
    //read data
    CPPUNIT_ASSERT_NO_THROW(field.read(read_data));

    //compare data
    auto buffer_iter = buffer.begin();
    auto read_iter   = read_data.begin();
    for(;read_iter!=read_data.end();++read_iter,++buffer_iter)
        check_equality(*read_iter,*buffer_iter);
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_io_test<T>::test_mdarray_error()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    T scalar_value;
    CPPUNIT_ASSERT_THROW(field.write(scalar_value),size_mismatch_error);
    CPPUNIT_ASSERT_THROW(field.read(scalar_value),size_mismatch_error);

    auto wrong_size = mdarray_type::create(shape_t{10});
    CPPUNIT_ASSERT_THROW(field.write(wrong_size),size_mismatch_error);
    CPPUNIT_ASSERT_THROW(field.read(wrong_size),size_mismatch_error);

    wrong_size = mdarray_type::create(shape_t{10,100});
    CPPUNIT_ASSERT_THROW(field.write(wrong_size),size_mismatch_error);
    CPPUNIT_ASSERT_THROW(field.read(wrong_size),size_mismatch_error);
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_io_test<T>::test_array()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    array write_data(mdarray_type::create(shape,buffer));
    array read_data(mdarray_type::create(shape));

    //write data
    CPPUNIT_ASSERT_NO_THROW(field.write(write_data));
    //read data
    CPPUNIT_ASSERT_NO_THROW(field.read(read_data));

    //compare data
    auto buffer_iter = buffer.begin();
    auto read_iter   = read_data.begin();
    for(;read_iter!=read_data.end();++read_iter,++buffer_iter)
        check_equality((*read_iter).template as<T>(),*buffer_iter);
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_io_test<T>::test_array_error()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    array a(mdarray_type::create(shape_t{4}));
    CPPUNIT_ASSERT_THROW(field.write(a),size_mismatch_error);

    a = array(mdarray_type::create(shape_t{10,20}));
    CPPUNIT_ASSERT_THROW(field.write(a),size_mismatch_error);
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_io_test<T>::test_pointer()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    buffer_type write_data(buffer);
    buffer_type read_data(buffer.size());

    //write data
    CPPUNIT_ASSERT_NO_THROW(field.write(write_data.size(),write_data.data()));
    //read data
    CPPUNIT_ASSERT_NO_THROW(field.read(read_data.size(),read_data.data()));

    //compare data
    auto buffer_iter = buffer.begin();
    auto read_iter   = read_data.begin();
    for(;read_iter!=read_data.end();++read_iter,++buffer_iter)
        check_equality(*read_iter,*buffer_iter);

}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_io_test<T>::test_pointer_error()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT_THROW(field.write(size+3,buffer.data()),size_mismatch_error);
    CPPUNIT_ASSERT_THROW(field.write(size-1,buffer.data()),size_mismatch_error);

    CPPUNIT_ASSERT_THROW(field.read(size+3,buffer.data()),size_mismatch_error);
    CPPUNIT_ASSERT_THROW(field.read(size-1,buffer.data()),size_mismatch_error);
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_io_test<T>::test_scalar()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxfield sfield = root.create_field<T>("test2");;
    
    T write_data = buffer[0];
    T read_data;

    CPPUNIT_ASSERT_NO_THROW(sfield.write(write_data));
    CPPUNIT_ASSERT_NO_THROW(sfield.read(read_data));
    check_equality(write_data,read_data);
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_io_test<T>::test_scalar_error()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    T data;
    CPPUNIT_ASSERT_THROW(field.read(data),size_mismatch_error);
    CPPUNIT_ASSERT_THROW(field.write(data),size_mismatch_error);
}

