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
// Created on: Jul 16, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
///
#pragma once

extern "C" {
#include <hdf5.h>
}

#include "../common.hpp"
#include "../data.hpp"

#include <pni/io/nx/h5/file_imp.hpp>
#include <pni/io/nx/h5/group_imp.hpp>
#include <pni/io/nx/h5/h5datatype.hpp>
#include <pni/io/nx/h5/h5dataspace.hpp>
#include <pni/io/nx/h5/attribute_imp.hpp>
#include <pni/io/nx/h5/attribute_utils.hpp>

using namespace pni::io::nx::h5;

/*!
\ingroup test_suites
\brief test H5Attribute objects

Testing instances of H5Attribute.
*/
class attribute_imp_test:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(attribute_imp_test);
        CPPUNIT_TEST(test_creation); 
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_inquery);

        CPPUNIT_TEST(test_scalar_attribute<uint8>);
        CPPUNIT_TEST(test_scalar_attribute<int8>);
        CPPUNIT_TEST(test_scalar_attribute<uint16>);
        CPPUNIT_TEST(test_scalar_attribute<int16>);
        CPPUNIT_TEST(test_scalar_attribute<uint32>);
        CPPUNIT_TEST(test_scalar_attribute<int32>);
        CPPUNIT_TEST(test_scalar_attribute<uint64>);
        CPPUNIT_TEST(test_scalar_attribute<int64>);
        CPPUNIT_TEST(test_scalar_attribute<float32>);
        CPPUNIT_TEST(test_scalar_attribute<float64>);
        CPPUNIT_TEST(test_scalar_attribute<float128>);
        CPPUNIT_TEST(test_scalar_attribute<complex32>);
        CPPUNIT_TEST(test_scalar_attribute<complex64>);
        CPPUNIT_TEST(test_scalar_attribute<complex128>);
        CPPUNIT_TEST(test_scalar_attribute<string>);
        CPPUNIT_TEST(test_scalar_attribute<bool_t>);

        CPPUNIT_TEST(test_array_attribute<uint8>);
        CPPUNIT_TEST(test_array_attribute<int8>);
        CPPUNIT_TEST(test_array_attribute<uint16>);
        CPPUNIT_TEST(test_array_attribute<int16>);
        CPPUNIT_TEST(test_array_attribute<uint32>);
        CPPUNIT_TEST(test_array_attribute<int32>);
        CPPUNIT_TEST(test_array_attribute<uint64>);
        CPPUNIT_TEST(test_array_attribute<int64>);
        CPPUNIT_TEST(test_array_attribute<float32>);
        CPPUNIT_TEST(test_array_attribute<float64>);
        CPPUNIT_TEST(test_array_attribute<float128>);
        CPPUNIT_TEST(test_array_attribute<complex32>);
        CPPUNIT_TEST(test_array_attribute<complex64>);
        CPPUNIT_TEST(test_array_attribute<complex128>);
        CPPUNIT_TEST(test_array_attribute<string>);
        
        CPPUNIT_TEST(test_array_attribute_partial<uint8>);
        CPPUNIT_TEST(test_array_attribute_partial<int8>);
        CPPUNIT_TEST(test_array_attribute_partial<uint16>);
        CPPUNIT_TEST(test_array_attribute_partial<int16>);
        CPPUNIT_TEST(test_array_attribute_partial<uint32>);
        CPPUNIT_TEST(test_array_attribute_partial<int32>);
        CPPUNIT_TEST(test_array_attribute_partial<uint64>);
        CPPUNIT_TEST(test_array_attribute_partial<int64>);
        CPPUNIT_TEST(test_array_attribute_partial<float32>);
        CPPUNIT_TEST(test_array_attribute_partial<float64>);
        CPPUNIT_TEST(test_array_attribute_partial<float128>);
        CPPUNIT_TEST(test_array_attribute_partial<complex32>);
        CPPUNIT_TEST(test_array_attribute_partial<complex64>);
        CPPUNIT_TEST(test_array_attribute_partial<complex128>);
        CPPUNIT_TEST(test_array_attribute_partial<string>);
        CPPUNIT_TEST_SUITE_END();
    private:
        file_imp file;   //!< file object
        group_imp root_group;

    public:
        //---------------------------------------------------------------------
        /*!
        \brief setting up the test

        Run before each test.
        */
        void setUp();

        //---------------------------------------------------------------------
        /*!
        \brief tear down the test

        Run after each test.
        */
        void tearDown();

        //---------------------------------------------------------------------
        //! test attribute constructors
        void test_creation();

        //---------------------------------------------------------------------
        //! testing assignment operators
        void test_assignment();

        //---------------------------------------------------------------------
        //! testing comparision operators
        void test_comparison();

        //---------------------------------------------------------------------
        //! testing types inquery methods
        void test_inquery();

        template<typename T> void test_scalar_attribute();
        template<typename T> void test_array_attribute();
        template<typename T> void test_array_attribute_partial();
};

//-----------------------------------------------------------------------------
template<typename T> void attribute_imp_test::test_scalar_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    type_id_t tid = type_id_map<T>::type_id;
    attribute_imp a(create_attribute(root_group.object(),
                                     "a1",
                                     get_type(tid),
                                     h5dataspace(),
                                     false));

    //write data
    auto write = create_scalar_data<T>();
    a.write(tid,&write);
    //read data back and check equality
    T read;
    a.read(tid,&read);
    check_equality(write,read);
}

//-----------------------------------------------------------------------------
template<typename T> void attribute_imp_test::test_array_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    type_imp::index_vector_type s{10,20};
    auto write = dynamic_array<T>::create(s);
    static_array<T,10,20> read;
    type_id_t tid = type_id_map<T>::type_id;

    std::vector<T> b = create_array_data<T>(write.size());
    std::copy(b.begin(),b.end(),write.begin());
    
    attribute_imp a(create_attribute(root_group.object(),
                                     "a1",
                                     get_type(tid), 
                                     h5dataspace(s),
                                     false));
    //write data
    a.write(tid,write.data());
    //read data back
    a.read(tid,read.data());

    //compare data
    for(size_t i=0;i<a.size();i++) check_equality(read[i],write[i]);
}

//-----------------------------------------------------------------------------
template<typename T> void attribute_imp_test::test_array_attribute_partial()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    type_imp::index_vector_type s{10,20};
    type_imp::selection_vector_type selection{slice(0,10),slice(1)};
    auto write = dynamic_array<T>::create(shape_t{10});
    static_array<T,10,20> read;
    type_id_t tid = type_id_map<T>::type_id;

    std::vector<T> b = create_array_data<T>(write.size());
    std::copy(b.begin(),b.end(),write.begin());
    
    attribute_imp a(create_attribute(root_group.object(),
                                     "a1",
                                     get_type(tid), 
                                     h5dataspace(s),
                                     false));
    a.apply_selection(selection);
    //write data
    a.write(tid,write.data());
    a.clear_selection();
    //read data back
    a.read(tid,read.data());

    //compare data
    for(size_t i=0;i<a.size();i++) check_equality(read[i],write[i]);
}
