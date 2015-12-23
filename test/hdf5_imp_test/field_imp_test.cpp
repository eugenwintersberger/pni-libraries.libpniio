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
// Created on: Jul 17, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <boost/test/unit_test.hpp>
#include <boost/current_function.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/h5/h5deflate_filter.hpp>
#include <pni/io/nx/h5/type_imp.hpp>
#include <pni/io/nx/h5/file_imp.hpp>
#include <pni/io/nx/h5/group_imp.hpp>
#include <pni/io/nx/h5/field_imp.hpp>
#include <pni/io/nx/h5/field_factory.hpp>
#include <boost/mpl/list.hpp>
#include "../uniform_distribution.hpp"

using namespace pni::core;
using namespace pni::io::nx;
using pni::io::object_error;


typedef boost::mpl::list<uint8,int8,uint16,int16,uint32,int32,uint64,int64,
                         float32,float64,float128,
                         complex32,complex64,complex128,binary> test_types;

struct field_imp_test_fixture
{
    h5::file_imp file;
    h5::group_imp group;

    field_imp_test_fixture():
        file(h5::file_imp::create("field_imp_test.h5",true,0)),
        group(h5::group_imp(file.root(),"data"))
    {}

    //-------------------------------------------------------------------------
    ~field_imp_test_fixture()
    {
        group.close();
        file.close();
    }
};

BOOST_FIXTURE_TEST_SUITE(field_imp_test,field_imp_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_create_default)
    {
        h5::field_imp field;
        BOOST_CHECK(!field.is_valid());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_create_no_filter)
    {
        h5::field_imp field(group,"data",type_id_t::FLOAT32,{1},{1});
        field.rank();
        BOOST_CHECK(field.is_valid());
        BOOST_CHECK_EQUAL(field.rank(),1);
        BOOST_CHECK_EQUAL(field.size(),1);

        h5::field_imp field1(group,"data2",type_id_t::FLOAT32,{10,200},{1,200});
        BOOST_CHECK(field1.is_valid());
        BOOST_CHECK_EQUAL(field1.rank(),2);
        BOOST_CHECK_EQUAL(field1.size(),2000);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_create_errors)
    {
        type_id_t tid = type_id_t::FLOAT32;
        
        BOOST_CHECK_NO_THROW(h5::field_imp(group,"data",tid,{1},{1}));

        //should throw as field does already exist
        BOOST_CHECK_THROW(h5::field_imp(group,"data",tid,{1},{2}),object_error);
        
        //should throw size_mismatch_error 
        BOOST_CHECK_THROW(h5::field_imp(group,"data1", tid,{},{2}),
                          size_mismatch_error);

        BOOST_CHECK_THROW(h5::field_imp(group,"data1",tid,{1},{}),
                          size_mismatch_error);

        //again size mismatch error since 
        BOOST_CHECK_THROW(h5::field_imp(group,"data1",tid,{},{}),
                          size_mismatch_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_create_with_filter)
    {
        h5::h5deflate_filter filter; 
        h5::field_imp field(group,"data",type_id_t::FLOAT32,{0,100,200},{1,100,200},filter);
        BOOST_CHECK(field.is_valid());
        BOOST_CHECK_EQUAL(field.rank(),3);
        BOOST_CHECK_EQUAL(field.size(),0);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_create_copy)
    {
        h5::field_imp field1{group,"data",type_id_t::FLOAT32,{10,200},{1,200}};
        BOOST_CHECK(field1.is_valid());
        BOOST_CHECK_EQUAL(field1.rank(),2);
        BOOST_CHECK_EQUAL(field1.size(),2000);

        h5::field_imp field2 = field1;
        BOOST_CHECK(field2.is_valid());
        BOOST_CHECK_EQUAL(field2.rank(),field1.rank());
        BOOST_CHECK_EQUAL(field2.size(),field2.size());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_create_move)
    {
        h5::field_imp field1{group,"data",type_id_t::FLOAT32,{10,200},{1,200}};
        BOOST_CHECK(field1.is_valid());
        BOOST_CHECK_EQUAL(field1.rank(),2);
        BOOST_CHECK_EQUAL(field1.size(),2000);

        h5::field_imp field2(std::move(field1));
        BOOST_CHECK(field2.is_valid());
        BOOST_CHECK_EQUAL(field2.rank(),2);
        BOOST_CHECK_EQUAL(field2.size(),2000);
        BOOST_CHECK(!field1.is_valid());

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_assignment)
    {
        h5::field_imp field1{group,"data",type_id_t::FLOAT32,{10,200},{1,200}};
        h5::field_imp field2,field3;
        BOOST_CHECK(field1.is_valid());
        BOOST_CHECK_EQUAL(field1.rank(),2);
        BOOST_CHECK_EQUAL(field1.size(),2000);

        //copy assignment
        field2 = field1;
        BOOST_CHECK(field2.is_valid());
        BOOST_CHECK_EQUAL(field2.rank(),field1.rank());
        BOOST_CHECK_EQUAL(field2.size(),field1.size());
        BOOST_CHECK(field1.is_valid());

        field3 = std::move(field1);
        BOOST_CHECK(field3.is_valid());
        BOOST_CHECK_EQUAL(field3.rank(),field2.rank());
        BOOST_CHECK_EQUAL(field3.size(),field2.size());
        BOOST_CHECK(!field1.is_valid());

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_inquery)
    {
        h5::field_imp field1{group,"data",type_id_t::FLOAT32,{10,200},{1,200}};

        BOOST_CHECK(field1.is_valid());
        BOOST_CHECK_EQUAL(field1.name(),"data");
        BOOST_CHECK_EQUAL(field1.size(),2000);
        BOOST_CHECK_EQUAL(field1.type_id(),type_id_t::FLOAT32);
        BOOST_CHECK_EQUAL(field1.filename(),"field_imp_test.h5");
    }


    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_parent)
    {

        h5::field_imp field1{group,"data",type_id_t::FLOAT32,{10,200},{1,200}};
        h5::group_imp p(h5::object_imp(field1.parent()));

        BOOST_CHECK(p.is_valid());
        BOOST_CHECK_EQUAL(p.name(),"data");
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_string_array_data)
    {
        shape_t s{2,3};

        h5::field_imp dset{group,"sarray",type_id_t::STRING,{2,3},{1,3}};

        auto swrite = dynamic_array<string>::create(s);
        swrite(0,0) = "hello"; swrite(0,1) = "world"; swrite(0,2) = "this";
        swrite(1,0) = "is"; swrite(1,1) = "a string"; swrite(1,2) = "array";
        
        BOOST_CHECK_NO_THROW(dset.write(type_id_t::STRING,{swrite.size()},
                             static_cast<void*>(swrite.data())));

        auto sread = dynamic_array<string>::create(s);

        BOOST_CHECK_NO_THROW(dset.read(type_id_t::STRING,{sread.size()},
                                       static_cast<void*>(sread.data())));

        BOOST_CHECK_EQUAL_COLLECTIONS(swrite.begin(),swrite.end(),
                                      sread.begin(),sread.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_string_scalar_data)
    {
        h5::field_imp field{group,"sscalar",type_id_t::STRING,{1},{1}};
        string write = "hello world";
        field.write(type_id_t::STRING,{1},&write);
        string read;
        field.read(type_id_t::STRING,{1},&read);
        BOOST_CHECK_EQUAL(read,write);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_bool_scalar_data)
    {
        bool_t read_flag,write_flag;

        h5::field_imp field{group,"flag",type_id_t::BOOL,{1},{1}};

        read_flag = false; write_flag = true;
        field.write(type_id_t::BOOL,{1},&write_flag);
        field.read(type_id_t::BOOL,{1},&read_flag);
        BOOST_CHECK_EQUAL(read_flag,write_flag);
        
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_string_selection) 
    {
        shape_t shape({10,20});
        h5::field_imp field{group,"text",type_id_t::STRING,
                            h5::type_imp::to_index_vector(shape),{1,20}};

        std::vector<string> writebuf(10);
        std::vector<string> readbuf(10);

        for(size_t i=0;i<10;i++)
        {
            std::stringstream ss;

            //select regtion in the dataset
            std::vector<slice> selection({slice(i),slice(10,20)});
            //set buffer value
            
            ss<<"bla "<<i;
            std::fill(writebuf.begin(),writebuf.end(),string(ss.str()));
            
            //apply selection
            field.apply_selection(selection);
            BOOST_CHECK_EQUAL(field.size(),10);

            //write data
            field.write(type_id_t::STRING,{writebuf.size()},writebuf.data());

            //read data back
            field.read(type_id_t::STRING,{readbuf.size()},readbuf.data());

            //compare data
            BOOST_CHECK_EQUAL_COLLECTIONS(writebuf.begin(),writebuf.end(),
                                          readbuf.begin(),readbuf.end());
            field.clear_selections();
            BOOST_CHECK_EQUAL(field.size(),10*20);
        }

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_scalar_data,T,test_types)
    {
        typedef uniform_distribution<T> dist_type; 
        //start with a scalar dataset
        dist_type generator;
        type_id_t tid = type_id_map<T>::type_id;
        h5::field_imp scalar_ds{group,"scalar_dataset",tid, {1},{1}};
        T write = generator();
        BOOST_CHECK_NO_THROW(scalar_ds.write(tid,{1},&write));
        T read;
        BOOST_CHECK_NO_THROW(scalar_ds.read(tid,{1},&read));
        BOOST_CHECK_EQUAL(read,write);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_array_data,T,test_types)
    {
        typedef uniform_distribution<T> dist_type;
        dist_type generator;
        shape_t s{3,3};
        shape_t cs{1,3}; 
        type_id_t tid = type_id_map<T>::type_id;
        h5::field_imp ds{group,"array_dataset",tid,{3,3},{1,3}};
        auto write = dynamic_array<T>::create(s);
        auto read  = dynamic_array<T>::create(s);
        std::generate(write.begin(),write.end(),generator);

        BOOST_CHECK_NO_THROW(ds.write(tid,{write.size()},write.data()));
        BOOST_CHECK_NO_THROW(ds.read(tid,{write.size()},read.data()));
        
        //check equality
        BOOST_CHECK_EQUAL_COLLECTIONS(write.begin(),write.end(),
                                      read.begin(),read.end());
    }

    //-----------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_selection,T,test_types)
    {
        shape_t shape({10,20});
        type_id_t tid = type_id_map<T>::type_id;
        h5::field_imp dset(group,"flags",tid,{10,20},{1,20});

        h5::type_imp::index_vector_type s = dset.shape();
        BOOST_CHECK_EQUAL(dset.size(),10*20);

        std::vector<T> writebuf(10);
        std::vector<T> readbuf(10);

        //check single value selection
        std::vector<slice> selection({slice(1),slice(2)});
        dset.apply_selection(selection);
        BOOST_CHECK_EQUAL(dset.size(),1);

        for(size_t i=0;i<10;i++)
        {
            //select regtion in the dataset
            std::vector<slice> selection({slice(i),slice(10,20)});
            //set buffer value
            std::fill(writebuf.begin(),writebuf.end(),T(i));
            
            //apply selection
            dset.apply_selection(selection);

            //check new properties of the dataset with selection
            BOOST_CHECK_EQUAL(dset.size(),10);
            BOOST_CHECK_EQUAL(dset.rank(),1);
            h5::type_imp::index_vector_type sel_s = dset.shape();
            BOOST_CHECK_EQUAL(sel_s.size(),1);
            BOOST_CHECK_EQUAL(sel_s[0],10);

            //write data
            dset.write(tid,{writebuf.size()},writebuf.data());

            //read data back
            dset.read(tid,{readbuf.size()},readbuf.data());

            //compare data
            BOOST_CHECK_EQUAL_COLLECTIONS(writebuf.begin(),writebuf.end(),
                                          readbuf.begin(),readbuf.end());
            dset.clear_selections();
        }

    }
BOOST_AUTO_TEST_SUITE_END()



