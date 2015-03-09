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
class nxfield_partial_io_test: public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(nxfield_partial_io_test);
	CPPUNIT_TEST(test_scalar_selection);
    CPPUNIT_TEST(test_strip_selection);
    CPPUNIT_TEST(test_view_to_selection);
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
    void test_scalar_selection();
    void test_strip_selection();
    void test_view_to_selection();
};

template<typename T>
const string nxfield_partial_io_test<T>::filename="nxfield_partial_io_test.nxs";

template<typename T>
const shape_t nxfield_partial_io_test<T>::shape=shape_t{3,4};

//------------------------------------------------------------------------------
template<typename T>
void nxfield_partial_io_test<T>::setUp() 
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
void nxfield_partial_io_test<T>::tearDown() 
{ 
    field.close();
    root.close();
    f.close();
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_partial_io_test<T>::test_scalar_selection()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    //writing data to disk
    size_t index = 0;
    for(size_t i=0;i<shape[0];++i)
    {
        for(size_t j=0;j<shape[1];++j)
        {
            CPPUNIT_ASSERT_NO_THROW(field(i,j).write(buffer[index++]));
        }
    }

    index = 0;
    T read;
    for(size_t i=0;i<shape[0];++i)
    {
        for(size_t j=0;j<shape[1];++j)
        {
            CPPUNIT_ASSERT_NO_THROW(field(i,j).read(read));
            check_equality(read,buffer[index++]);
        }
    }
}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_partial_io_test<T>::test_strip_selection()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    //writing data to disk
    auto write = mdarray_type::create(shape_t{4});
    auto read  = mdarray_type::create(shape_t{4});
    for(size_t i=0;i<shape[0];++i)
    {
        std::generate(write.begin(),write.end(),rand_dist);

        //write data
        CPPUNIT_ASSERT_NO_THROW(field(i,slice(0,4)).write(write));
        //read back data
        CPPUNIT_ASSERT_NO_THROW(field(i,slice(0,4)).read(read));

        for(size_t j=0;j<write.size();++j) check_equality(write(j),read(j));
    }

}

//----------------------------------------------------------------------------
template<typename T>
void nxfield_partial_io_test<T>::test_view_to_selection()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    //writing data to disk
    auto write = mdarray_type::create(shape);
    auto read  = mdarray_type::create(shape);

    std::generate(write.begin(),write.end(),rand_dist);
    slice s(0,4);
    for(size_t i=0;i<shape[0];++i)
    {
        //write data
        field(i,s).write(write(i,s));
        //read back data
        //auto r = read(i,s);
        //field(i,s).read(r);
        field(i,s).read(read(i,s));
    }
    
    for(size_t i=0;i<write.size();++i) check_equality(write[i],read[i]);

}
