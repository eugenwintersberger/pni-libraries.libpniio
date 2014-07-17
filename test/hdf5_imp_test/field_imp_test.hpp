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
// ============================================================================
//
// Created on: Jul 17, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

extern "C"{
#include <hdf5.h>
}

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/io/nx/h5/file_imp.hpp>
#include <pni/io/nx/h5/group_imp.hpp>
#include <pni/io/nx/h5/field_imp.hpp>
#include <pni/io/nx/h5/field_factory.hpp>

#include "../EqualityCheck.hpp"

using namespace pni::core;
using namespace pni::io::nx::h5;

class field_imp_test:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(field_imp_test);
        CPPUNIT_TEST(test_create_default);
        CPPUNIT_TEST(test_create_no_filter); 
        CPPUNIT_TEST(test_create_with_filter);
        CPPUNIT_TEST(test_create_copy);
        CPPUNIT_TEST(test_create_move);
        CPPUNIT_TEST(test_create_errors);
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_inquery);
        CPPUNIT_TEST(test_resize);
        CPPUNIT_TEST(test_parent);
        /*
        CPPUNIT_TEST(test_scalar_data<uint8>);
        CPPUNIT_TEST(test_scalar_data<int8>);
        CPPUNIT_TEST(test_scalar_data<uint16>);
        CPPUNIT_TEST(test_scalar_data<int16>);
        CPPUNIT_TEST(test_scalar_data<uint32>);
        CPPUNIT_TEST(test_scalar_data<int32>);
        CPPUNIT_TEST(test_scalar_data<uint64>);
        CPPUNIT_TEST(test_scalar_data<int64>);
        CPPUNIT_TEST(test_scalar_data<float32>);
        CPPUNIT_TEST(test_scalar_data<float64>);
        CPPUNIT_TEST(test_scalar_data<float128>);
        CPPUNIT_TEST(test_scalar_data<complex32>);
        CPPUNIT_TEST(test_scalar_data<complex64>);
        CPPUNIT_TEST(test_scalar_data<complex128>);
        CPPUNIT_TEST(test_scalar_data<binary>);
        CPPUNIT_TEST(test_string_scalar_data);
        CPPUNIT_TEST(test_bool_scalar_data);

        CPPUNIT_TEST(test_array_data<uint8>);
        CPPUNIT_TEST(test_array_data<int8>);
        CPPUNIT_TEST(test_array_data<uint16>);
        CPPUNIT_TEST(test_array_data<int16>);
        CPPUNIT_TEST(test_array_data<uint32>);
        CPPUNIT_TEST(test_array_data<int32>);
        CPPUNIT_TEST(test_array_data<uint64>);
        CPPUNIT_TEST(test_array_data<int64>);
        CPPUNIT_TEST(test_array_data<float32>);
        CPPUNIT_TEST(test_array_data<float64>);
        CPPUNIT_TEST(test_array_data<float128>);
        CPPUNIT_TEST(test_array_data<complex32>);
        CPPUNIT_TEST(test_array_data<complex64>);
        CPPUNIT_TEST(test_array_data<complex128>);
        CPPUNIT_TEST(test_array_data<binary>);
        CPPUNIT_TEST(test_string_array_data);

        CPPUNIT_TEST(test_selection<uint8>);
        CPPUNIT_TEST(test_selection<int8>);
        CPPUNIT_TEST(test_selection<uint16>);
        CPPUNIT_TEST(test_selection<int16>);
        CPPUNIT_TEST(test_selection<uint32>);
        CPPUNIT_TEST(test_selection<int32>);
        CPPUNIT_TEST(test_selection<uint64>);
        CPPUNIT_TEST(test_selection<int64>);
        CPPUNIT_TEST(test_selection<float32>);
        CPPUNIT_TEST(test_selection<float64>);
        CPPUNIT_TEST(test_selection<float128>);
        CPPUNIT_TEST(test_selection<complex32>);
        CPPUNIT_TEST(test_selection<complex64>);
        CPPUNIT_TEST(test_selection<complex128>);
        CPPUNIT_TEST(test_selection<binary>);
        CPPUNIT_TEST(test_string_selection);
        */
        CPPUNIT_TEST_SUITE_END();
    private:
        file_imp _file;
        group_imp _group;
    public:
        void setUp();
        void tearDown();
        void test_create_default();
        void test_create_no_filter(); 
        void test_create_with_filter();
        void test_create_errors();
        void test_create_copy();
        void test_create_move();
        void test_assignment();
        void test_inquery();
        void test_resize();
        template<typename T> void test_scalar_data();
        template<typename T> void test_array_data();
        void test_string_array_data();
        void test_string_scalar_data();
        void test_bool_scalar_data();
        void test_bool_array_data();
        template<typename T> void test_selection();
        void test_string_selection();
        void test_bool_selection();
        void test_parent();
};

//-----------------------------------------------------------------------------
template<typename T> void field_imp_test::test_scalar_data()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    //start with a scalar dataset
    field_imp scalar_ds = field_factory::create(_group,
                                                "scalar_dataset",
                                                type_id_map<T>::type_id,
                                                {1},
                                                {1});

    T write = T(1);
    CPPUNIT_ASSERT_NO_THROW(scalar_ds.write(&write));
    T read;
    CPPUNIT_ASSERT_NO_THROW(scalar_ds.read(&read));
    check_equality(read,write);
}

//-----------------------------------------------------------------------------
template<typename T> void field_imp_test::test_array_data()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t s{3,3};
    shape_t cs{1,3}; 
    field_imp ds = field_factory::create(_group,"array_dataset",
                                         type_id_map<T>::type_id,{3,3},{1,3});
    auto write = dynamic_array<T>::create(s);
    auto read  = dynamic_array<T>::create(s);
    std::fill(write.begin(),write.end(),T(1));

    CPPUNIT_ASSERT_NO_THROW(ds.write(write.data()));
    CPPUNIT_ASSERT_NO_THROW(ds.read(read.data()));
    
    //check equality
    for(size_t i=0;i<write.size();i++) check_equality(write[i],read[i]);
}

//-----------------------------------------------------------------------------
template<typename T> void field_imp_test::test_selection() 
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t shape({10,20});
    field_imp dset = field_factory::create(_group,"flags",
                                           type_id_map<T>::type_id,{10,20},{1,20});

    shape_t s;
    s = dset.shape<shape_t>();
    CPPUNIT_ASSERT(dset.size()==10*20);

    std::vector<T> writebuf(10);
    std::vector<T> readbuf(10);

    //check single value selection
    std::vector<slice> selection({slice(1),slice(2)});
    dset.apply_selection(selection);
    CPPUNIT_ASSERT(dset.size() == 1);

    for(size_t i=0;i<10;i++)
    {
        //select regtion in the dataset
        std::vector<slice> selection({slice(i),slice(10,20)});
        //set buffer value
        std::fill(writebuf.begin(),writebuf.end(),T(i));
        
        //apply selection
        dset.apply_selection(selection);

        //check new properties of the dataset with selection
        CPPUNIT_ASSERT(dset.size()==10);
        CPPUNIT_ASSERT(dset.rank()==1);
        auto sel_s = dset.shape<shape_t>();
        CPPUNIT_ASSERT(sel_s.size() == 1);
        CPPUNIT_ASSERT(sel_s[0] == 10);

        //write data
        dset.write(writebuf.data());

        //read data back
        dset.read(readbuf.data());

        //compare data
        CPPUNIT_ASSERT(std::equal(writebuf.begin(),writebuf.end(),readbuf.begin()));
        dset.clear_selections();
    }

}
