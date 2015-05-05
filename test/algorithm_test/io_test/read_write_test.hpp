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
//  Created on: Sep 16, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <boost/current_function.hpp>

#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/algorithms/read.hpp>
#include <pni/io/nx/algorithms/write.hpp>
#include <pni/io/nx/nxobject_traits.hpp>

#include "../../uniform_distribution.hpp"
#include "../../EqualityCheck.hpp"

using namespace pni::core;
using namespace pni::io::nx;

template<typename T>
class read_write_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(read_write_test);
        CPPUNIT_TEST(test_field_full);
        CPPUNIT_TEST(test_field_object_full);
        CPPUNIT_TEST(test_field_partial);
        CPPUNIT_TEST(test_field_object_partial);
        CPPUNIT_TEST(test_group);
        CPPUNIT_TEST(test_attribute_full);
        CPPUNIT_TEST(test_attribute_partial);
        CPPUNIT_TEST(test_attribute_object_full);
        CPPUNIT_TEST(test_attribute_object_partial);
        CPPUNIT_TEST_SUITE_END();

        typedef T value_type;
        typedef uniform_distribution<value_type> distribution_type;
        typedef std::vector<value_type> container_type;
        typedef dynamic_array<value_type> array_type;
        typedef nxobject_trait<nximp_code::HDF5>::object_type object_type;

        container_type buffer;
        distribution_type random_generator;

        h5::nxfile  file;
        h5::nxfield field;
        h5::nxgroup root;
        h5::nxattribute attribute;

        shape_t shape;
        array_type wbuffer;
        array_type rbuffer;
        slice sl1,sl2;

        template<typename CTYPE> void is_equal(const CTYPE &a,const CTYPE &b)
        {
            for(auto aiter = a.begin(),biter=b.begin();
                     aiter!=a.end();
                     ++aiter,++biter)
                check_equality(*aiter,*biter);
        }
        
    public:
        void setUp();
        void tearDown();
        
        void test_field_object_full();
        void test_field_full();
        void test_field_partial();
        void test_field_object_partial();
        void test_group();
        void test_attribute_full();
        void test_attribute_partial();
        void test_attribute_object_full();
        void test_attribute_object_partial();
};

//-----------------------------------------------------------------------------
template<typename T>
void read_write_test<T>::setUp()
{
    shape = shape_t{2,3,5};

    file = h5::nxfile::create_file("read_write_test.nxs",true);
    root = file.root();
    field     = root.create_field<value_type>("data",shape);
    attribute = field.attributes.create<value_type>("temp",shape);

    random_generator = distribution_type();
    buffer = container_type(field.size());
    std::generate(buffer.begin(),buffer.end(),random_generator);

    wbuffer = array_type::create(shape,buffer);
    rbuffer = array_type::create(shape);
    sl1 = slice(0,3);
    sl2 = slice(0,5);
}

//-----------------------------------------------------------------------------
template<typename T>
void read_write_test<T>::tearDown() 
{ 
    attribute.close();
    field.close();
    root.close();
    file.close();
}

//-----------------------------------------------------------------------------
template<typename T>
void read_write_test<T>::test_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    object_type object = root;
    CPPUNIT_ASSERT_THROW(write(object,array_type()),type_error);

}

//-----------------------------------------------------------------------------
template<typename T>
void read_write_test<T>::test_field_full()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    CPPUNIT_ASSERT_NO_THROW(write(field,wbuffer));
    CPPUNIT_ASSERT_NO_THROW(read(field,rbuffer));

    is_equal(wbuffer,rbuffer);
}

//-----------------------------------------------------------------------------
template<typename T>
void read_write_test<T>::test_field_object_full()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    object_type object = field;
   
    CPPUNIT_ASSERT_NO_THROW(write(object,wbuffer));
    CPPUNIT_ASSERT_NO_THROW(read(object,rbuffer));

    is_equal(wbuffer,rbuffer);
}

//-----------------------------------------------------------------------------
template<typename T>
void read_write_test<T>::test_field_partial()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    wbuffer = array_type::create(shape_t{3,5});
    rbuffer = array_type::create(shape_t{3,5});

    //write data
    for(size_t i=0;i<2;++i)
    {
        std::generate(wbuffer.begin(),wbuffer.end(),random_generator);
        CPPUNIT_ASSERT_NO_THROW(write(field,wbuffer,i,sl1,sl2));
        CPPUNIT_ASSERT_NO_THROW(read(field,rbuffer,i,sl1,sl2));

        is_equal(wbuffer,rbuffer);
    }
}

//-----------------------------------------------------------------------------
template<typename T>
void read_write_test<T>::test_field_object_partial()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    object_type object = field;
    wbuffer = array_type::create(shape_t{3,5});
    rbuffer = array_type::create(shape_t{3,5});

    //write data
    for(size_t i=0;i<2;++i)
    {
        std::generate(wbuffer.begin(),wbuffer.end(),random_generator);
        CPPUNIT_ASSERT_NO_THROW(write(object,wbuffer,i,sl1,sl2));
        CPPUNIT_ASSERT_NO_THROW(read(object,rbuffer,i,sl1,sl2));
        is_equal(wbuffer,rbuffer);
    }
}

//-----------------------------------------------------------------------------
template<typename T>
void read_write_test<T>::test_attribute_full()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT_NO_THROW(write(attribute,wbuffer));
    CPPUNIT_ASSERT_NO_THROW(read(attribute,rbuffer));

    is_equal(wbuffer,rbuffer);
}

//-----------------------------------------------------------------------------
template<typename T>
void read_write_test<T>::test_attribute_object_full()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject object = attribute;
    
    CPPUNIT_ASSERT_NO_THROW(write(object,wbuffer));
    CPPUNIT_ASSERT_NO_THROW(read(object,rbuffer));

    is_equal(wbuffer,rbuffer);
}
//-----------------------------------------------------------------------------
template<typename T>
void read_write_test<T>::test_attribute_partial()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    wbuffer = array_type::create(shape_t{3,5});
    rbuffer = array_type::create(shape_t{3,5});

    //write data
    for(size_t i=0;i<2;++i)
    {
        std::generate(wbuffer.begin(),wbuffer.end(),random_generator);
        CPPUNIT_ASSERT_NO_THROW(write(attribute,wbuffer,i,sl1,sl2));
        CPPUNIT_ASSERT_NO_THROW(read(attribute,rbuffer,i,sl1,sl2));
        is_equal(wbuffer,rbuffer);
    }
}
//-----------------------------------------------------------------------------
template<typename T>
void read_write_test<T>::test_attribute_object_partial()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject object = attribute;

    wbuffer = array_type::create(shape_t{3,5});
    rbuffer = array_type::create(shape_t{3,5});

    //write data
    for(size_t i=0;i<2;++i)
    {
        std::generate(wbuffer.begin(),wbuffer.end(),random_generator);
        write(object,wbuffer,i,sl1,sl2);
        CPPUNIT_ASSERT_NO_THROW(write(object,wbuffer,i,sl1,sl2));
        CPPUNIT_ASSERT_NO_THROW(read(object,rbuffer,i,sl1,sl2));
        is_equal(wbuffer,rbuffer);
    }
}
