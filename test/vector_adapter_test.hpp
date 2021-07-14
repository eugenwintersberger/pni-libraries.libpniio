/*
 * (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pninexus.
 *
 * pninexus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pninexus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pninexus.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Feb 18, 2014
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <boost/current_function.hpp>
#include <algorithm>
#include <vector>

#include <pni/vector_adapter.hpp>

#include "compare.hpp"
#include "data_generator.hpp"

using namespace pni;

template<typename T> class vector_adapter_test : public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(vector_adapter_test<T>);
        CPPUNIT_TEST(test_create);
        CPPUNIT_TEST(test_assign);
        CPPUNIT_TEST(test_copy_data);
        CPPUNIT_TEST(test_reverse_iterator);
        CPPUNIT_TEST_SUITE_END();
    
        typedef vector_adapter<T> adapter_type;
        typedef std::vector<T>    vector_type;
        typedef random_generator<T> random_type;
        T *test_data;
        size_t n = 1000;
    public:
        void setUp();
        void tearDown();
        
        void test_create();
        void test_assign();
        void test_copy_data();
        void test_reverse_iterator();
};

//-----------------------------------------------------------------------------
template<typename T> void vector_adapter_test<T>::setUp()
{
    test_data = new T[n];
}

//-----------------------------------------------------------------------------
template<typename T> void vector_adapter_test<T>::tearDown()
{
    if(test_data) delete [] test_data;
}

//-----------------------------------------------------------------------------
template<typename T> void vector_adapter_test<T>::test_create()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    //testing the default constructor
    adapter_type a1;
    CPPUNIT_ASSERT(a1.size()==0);
    CPPUNIT_ASSERT(a1.empty());

    //testing the standard constructor
    adapter_type a(test_data,n);
    CPPUNIT_ASSERT(a.size()==n);
    CPPUNIT_ASSERT(!a.empty());

    //testing the copy constructor
    adapter_type a2(a);
    CPPUNIT_ASSERT(a.size() == a2.size());
    CPPUNIT_ASSERT(a.empty() == a2.empty());
    CPPUNIT_ASSERT(a.data() == a2.data());

    //testing the move constructor
    adapter_type a3(std::move(a2));
    CPPUNIT_ASSERT(a2.size() == 0);
    CPPUNIT_ASSERT(a2.empty());
    CPPUNIT_ASSERT(a3.size() == a.size());
    CPPUNIT_ASSERT(!a3.empty());
}

//-----------------------------------------------------------------------------
template<typename T> void vector_adapter_test<T>::test_assign()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    adapter_type a1,a3;

    adapter_type a2(test_data,n);

    //copy assignment
    a1 = a2;
    CPPUNIT_ASSERT(a1.size() == a2.size());
    CPPUNIT_ASSERT(!a1.empty());
    CPPUNIT_ASSERT(!a2.empty());
    CPPUNIT_ASSERT(a2.data() == a1.data());

    //move assignment
    a3 = std::move(a2);
    CPPUNIT_ASSERT(a2.empty());
    CPPUNIT_ASSERT(a2.size() == 0);
    CPPUNIT_ASSERT(a2.data() == nullptr);

    CPPUNIT_ASSERT(a3.data() == a1.data());
    CPPUNIT_ASSERT(a3.size() == a1.size());
    CPPUNIT_ASSERT(a3.empty() == a1.empty());
}

//------------------------------------------------------------------------------
template<typename T> void vector_adapter_test<T>::test_copy_data()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    adapter_type a1(test_data,n);
    vector_type  v1(n);
    std::generate(v1.begin(),v1.end(),random_type());

    //copy the data
    std::copy(v1.begin(),v1.end(),a1.begin());

    auto viter = v1.begin();
    auto vend  = v1.end();
    auto aiter = a1.begin();
    for(;viter!=vend;++viter,++aiter) compare(*viter,*aiter);
        
}

//-----------------------------------------------------------------------------
template<typename T> void vector_adapter_test<T>::test_reverse_iterator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    adapter_type a1(test_data,n);
    vector_type  v1(n);
    std::generate(v1.begin(),v1.end(),random_type());

    //copy the data
    std::copy(v1.begin(),v1.end(),a1.begin());

    auto viter = v1.rbegin();
    auto vend  = v1.rend();
    auto aiter = a1.rbegin();
    for(;viter!=vend;++viter,++aiter) compare(*viter,*aiter);

}
