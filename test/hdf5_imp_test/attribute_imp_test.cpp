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
//

#include <boost/test/unit_test.hpp>
#include <pni/io/nx/nxdate_time.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/h5/file_imp.hpp>
#include <pni/io/nx/h5/group_imp.hpp>
#include <pni/io/nx/h5/h5datatype.hpp>
#include <pni/io/nx/h5/h5dataspace.hpp>
#include <pni/io/nx/h5/attribute_imp.hpp>
#include <pni/io/nx/h5/attribute_utils.hpp>
#include <boost/mpl/list.hpp>
#include "../uniform_distribution.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct attribute_imp_test_fixture
{
    h5::file_imp file;   //!< file object
    h5::group_imp root_group;


    attribute_imp_test_fixture():
        file(h5::file_imp::create("attribute_imp_test.h5",true,0)),
        root_group(file.root())
    {}

    ~attribute_imp_test_fixture()
    {
        root_group.close();
        file.close();
    }
};

typedef boost::mpl::list<uint8,int8,uint16,int16,uint32,int32,uint64,int64,
                         float32,float64,float128,
                         complex32,complex64,complex128,string,bool_t>
                         test_types;

BOOST_FIXTURE_TEST_SUITE(attribute_imp_test,attribute_imp_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_creation)
    {
        using pni::io::invalid_object_error;
        using pni::io::nx::nxdate_time;

        //default constructor
        h5::attribute_imp a;
        BOOST_CHECK(!a.is_valid());
        BOOST_CHECK_THROW(a.filename(),invalid_object_error);
        BOOST_CHECK_THROW(a.size(),invalid_object_error);
        BOOST_CHECK_THROW(a.type_id(),invalid_object_error);
        BOOST_CHECK_THROW(a.shape(),invalid_object_error);
        BOOST_CHECK_THROW(a.rank(),invalid_object_error);
        BOOST_CHECK_THROW(a.name(),invalid_object_error);
        BOOST_CHECK_THROW(a.parent(),invalid_object_error);
      
        //test constructor from new object
        h5::attribute_imp a1(h5::create_attribute(root_group.object(),
                                         "a1",
                                         h5::get_type(type_id_t::STRING),
                                         h5::h5dataspace(),
                                         false));
        BOOST_CHECK(a1.is_valid());
        BOOST_CHECK_EQUAL(a1.name(),"a1");

        
        //test construction from copy constructor
        h5::attribute_imp a2(a1);
        BOOST_CHECK(a2.is_valid());
        BOOST_CHECK_EQUAL(a2.name(),a1.name());
        
        //test move construction
        h5::attribute_imp a3(std::move(a2));
        BOOST_CHECK(a3.is_valid());
        BOOST_CHECK(!a2.is_valid());

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_assignment)
    {
        h5::attribute_imp a1(h5::create_attribute(root_group.object(),
                                          "a1",
                                          h5::get_type(type_id_t::STRING),
                                          h5::h5dataspace(),
                                          false));
        BOOST_CHECK(a1.is_valid());

        h5::attribute_imp a2;
        a2 = a1;
        BOOST_CHECK(a1.is_valid());
        BOOST_CHECK(a2.is_valid());

        h5::attribute_imp a3;
        a3= std::move(a2);
        BOOST_CHECK(!a2.is_valid());
        BOOST_CHECK(a1.is_valid());
        BOOST_CHECK(a3.is_valid());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_inquery)
    {
        h5::attribute_imp a1(h5::create_attribute(root_group.object(),
                                          "a1",
                                          h5::get_type(type_id_t::FLOAT32),
                                          h5::h5dataspace(),
                                          false));
        shape_t shape{10,2};
        h5::attribute_imp a2(create_attribute(root_group.object(),
                                          "a2",
                                          h5::get_type(type_id_t::FLOAT32),
                                          h5::h5dataspace{h5::type_imp::index_vector_type{10,2}},
                                          false));

        BOOST_CHECK(a1.is_valid());
        BOOST_CHECK_EQUAL(a1.name(),"a1");
        BOOST_CHECK_EQUAL(a1.filename(),"attribute_imp_test.h5");
        BOOST_CHECK_EQUAL(a1.size(),1);
        BOOST_CHECK_EQUAL(a1.rank(),1);
        BOOST_CHECK_EQUAL(a1.type_id(),type_id_t::FLOAT32);
        BOOST_CHECK_EQUAL(a1.shape().size(),1);


        BOOST_CHECK(a2.is_valid());
        BOOST_CHECK_EQUAL(a2.name(),"a2");
        BOOST_CHECK_EQUAL(a2.filename(),"attribute_imp_test.h5");
        BOOST_CHECK_EQUAL(a2.size(),20);
        BOOST_CHECK_EQUAL(a2.rank(),2);
        BOOST_CHECK_EQUAL(a2.type_id(),type_id_t::FLOAT32);
        auto ashape = a2.shape();
        BOOST_CHECK_EQUAL_COLLECTIONS(shape.begin(),shape.end(),
                                      ashape.begin(),ashape.end());

        h5::group_imp parent(a1.parent());
        BOOST_CHECK(parent.is_valid());
        BOOST_CHECK_EQUAL(parent.name(),"/");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_scalar_attribute,T,test_types)
    {
        typedef uniform_distribution<T> dist_type;
        dist_type generator;

        type_id_t tid = type_id_map<T>::type_id;
        h5::attribute_imp a(h5::create_attribute(root_group.object(),
                                         "a1",
                                         h5::get_type(tid),
                                         h5::h5dataspace(),
                                         false));

        //write data
        auto write = generator();
        a.write(tid,&write);
        //read data back and check equality
        T read;
        a.read(tid,&read);
        BOOST_CHECK_EQUAL(write,read);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_array_attribute,T,test_types)
    {
        typedef uniform_distribution<T> dist_type;

        dist_type generator;
        h5::type_imp::index_vector_type s{10,20};
        type_id_t tid = type_id_map<T>::type_id;

        //create the attribute
        h5::attribute_imp a(h5::create_attribute(root_group.object(),
                                         "a1",
                                         h5::get_type(tid), 
                                         h5::h5dataspace(s),
                                         false));

        //generate data for writing
        auto write = dynamic_array<T>::create(s);
        std::generate(write.begin(),write.end(),generator);
        
        //write data
        a.write(tid,write.data());

        //read data back
        static_array<T,10,20> read;
        a.read(tid,read.data());

        //compare data
        BOOST_CHECK_EQUAL_COLLECTIONS(write.begin(),write.end(),
                                      read.begin(),read.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_array_attribute_partial,T,test_types)
    {
        typedef uniform_distribution<T> dist_type;

        dist_type generator;
        h5::type_imp::index_vector_type s{10,20};
        type_id_t tid = type_id_map<T>::type_id;

        //create the attribute
        h5::attribute_imp a(h5::create_attribute(root_group.object(),
                                         "a1",
                                         h5::get_type(tid), 
                                         h5::h5dataspace(s),
                                         false));

        auto write = dynamic_array<T>::create(shape_t{10});
        static_array<T,10> read;

        for(size_t i=0;i<s[1];++i)
        {
            h5::type_imp::selection_vector_type selection{slice(0,10),slice(i)};

            std::generate(write.begin(),write.end(),generator);
        
            a.apply_selection(selection);
            //write data
            a.write(tid,write.data());
            //read data back
            a.read(tid,read.data());
            //release selection
            a.clear_selection();
           
            BOOST_CHECK_EQUAL_COLLECTIONS(write.begin(),write.end(),
                                          read.begin(),read.end());
        }
    }

BOOST_AUTO_TEST_SUITE_END()
