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
#include "field_imp_test.hpp"
#include <boost/current_function.hpp>
#include <pni/io/nx/h5/h5deflate_filter.hpp>
#include <pni/io/nx/h5/type_imp.hpp>

CPPUNIT_TEST_SUITE_REGISTRATION(field_imp_test);


void field_imp_test::setUp()
{
    _file = file_imp::create("field_imp_test.h5",true,0);
    _group = group_imp(_file.root(),"data");
}

//-----------------------------------------------------------------------------
void field_imp_test::tearDown()
{
    _group.close();
    _file.close();
}

//-----------------------------------------------------------------------------
void field_imp_test::test_create_default()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    field_imp field;

    CPPUNIT_ASSERT(!field.is_valid());
}

//-----------------------------------------------------------------------------
void field_imp_test::test_create_no_filter()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    field_imp field(_group,"data",type_id_t::FLOAT32,{1},{1});
    CPPUNIT_ASSERT(field.is_valid());
    CPPUNIT_ASSERT(field.rank() == 1);
    CPPUNIT_ASSERT(field.size() == 1);

    field_imp field1(_group,"data2",type_id_t::FLOAT32,{10,200},{1,200});
    CPPUNIT_ASSERT(field1.is_valid());
    CPPUNIT_ASSERT(field1.rank() == 2);
    CPPUNIT_ASSERT(field1.size() == 2000);

}

//-----------------------------------------------------------------------------
void field_imp_test::test_create_errors()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    type_id_t tid = type_id_t::FLOAT32;
    
    CPPUNIT_ASSERT_NO_THROW(field_imp(_group,"data",tid,{1},{1}));

    //should throw as field does already exist
    CPPUNIT_ASSERT_THROW(field_imp(_group,"data",tid,{1},{2}),object_error);
    
    //should throw size_mismatch_error 
    CPPUNIT_ASSERT_THROW(field_imp(_group,"data1", tid,{},{2}),
                         size_mismatch_error);

    CPPUNIT_ASSERT_THROW(field_imp(_group,"data1",tid,{1},{}),
                         size_mismatch_error);

    //again size mismatch error since 
    CPPUNIT_ASSERT_THROW(field_imp(_group,"data1",tid,{},{}),size_mismatch_error);

}

//-----------------------------------------------------------------------------
void field_imp_test::test_create_with_filter()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5deflate_filter filter; 
    field_imp field(_group,"data",type_id_t::FLOAT32,{0,100,200},{1,100,200},filter);
    CPPUNIT_ASSERT(field.is_valid());
    CPPUNIT_ASSERT(field.rank() == 3);
    CPPUNIT_ASSERT(field.size() == 0);
}

//-----------------------------------------------------------------------------
void field_imp_test::test_create_copy()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    field_imp field1{_group,"data",type_id_t::FLOAT32,{10,200},{1,200}};
    CPPUNIT_ASSERT(field1.is_valid());
    CPPUNIT_ASSERT(field1.rank() == 2);
    CPPUNIT_ASSERT(field1.size() == 2000);

    field_imp field2 = field1;
    CPPUNIT_ASSERT(field2.is_valid());
    CPPUNIT_ASSERT(field2.rank() == field1.rank());
    CPPUNIT_ASSERT(field2.size() == field2.size());


}

//-----------------------------------------------------------------------------
void field_imp_test::test_create_move()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    field_imp field1{_group,"data",type_id_t::FLOAT32,{10,200},{1,200}};
    CPPUNIT_ASSERT(field1.is_valid());
    CPPUNIT_ASSERT(field1.rank() == 2);
    CPPUNIT_ASSERT(field1.size() == 2000);

    field_imp field2(std::move(field1));
    CPPUNIT_ASSERT(field2.is_valid());
    CPPUNIT_ASSERT(field2.rank() == 2);
    CPPUNIT_ASSERT(field2.size() == 2000);
    CPPUNIT_ASSERT(!field1.is_valid());

}

//-----------------------------------------------------------------------------
void field_imp_test::test_assignment()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    field_imp field1{_group,"data",type_id_t::FLOAT32,{10,200},{1,200}};
    field_imp field2,field3;
    CPPUNIT_ASSERT(field1.is_valid());
    CPPUNIT_ASSERT(field1.rank() == 2);
    CPPUNIT_ASSERT(field1.size() == 2000);

    //copy assignment
    field2 = field1;
    CPPUNIT_ASSERT(field2.is_valid());
    CPPUNIT_ASSERT(field2.rank() == field1.rank());
    CPPUNIT_ASSERT(field2.size() == field1.size());
    CPPUNIT_ASSERT(field1.is_valid());

    field3 = std::move(field1);
    CPPUNIT_ASSERT(field3.is_valid());
    CPPUNIT_ASSERT(field3.rank() == field2.rank());
    CPPUNIT_ASSERT(field3.size() == field2.size());
    CPPUNIT_ASSERT(!field1.is_valid());

}

//----------------------------------------------------------------------------
void field_imp_test::test_inquery()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    field_imp field1{_group,"data",type_id_t::FLOAT32,{10,200},{1,200}};

    CPPUNIT_ASSERT(field1.is_valid());
    CPPUNIT_ASSERT(field1.name() == "data");
    CPPUNIT_ASSERT(field1.size() == 2000);
    CPPUNIT_ASSERT(field1.type_id() == type_id_t::FLOAT32);
    CPPUNIT_ASSERT(field1.filename() == "field_imp_test.h5");
}


//-----------------------------------------------------------------------------
void field_imp_test::test_parent()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;


    field_imp field1{_group,"data",type_id_t::FLOAT32,{10,200},{1,200}};
    group_imp p(object_imp(field1.parent()));

    CPPUNIT_ASSERT(p.is_valid());
    CPPUNIT_ASSERT(p.name() == "data");
}

//-----------------------------------------------------------------------------
void field_imp_test::test_resize()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    field_imp field1{_group,"data",type_id_t::FLOAT32,{10,200},{1,200}};
    CPPUNIT_ASSERT(field1.size() == 2000);

    CPPUNIT_ASSERT_NO_THROW(field1.resize({50,200}));
    CPPUNIT_ASSERT(field1.size() == 10000);
    
    CPPUNIT_ASSERT_THROW(field1.resize({10,20,2000}),shape_mismatch_error);
}

//------------------------------------------------------------------------------
void field_imp_test::test_string_array_data()
{
    
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t s{2,3};

    field_imp dset{_group,"sarray",type_id_t::STRING,{2,3},{1,3}};

    auto swrite = dynamic_array<string>::create(s);
    swrite(0,0) = "hello"; swrite(0,1) = "world"; swrite(0,2) = "this";
    swrite(1,0) = "is"; swrite(1,1) = "a string"; swrite(1,2) = "array";
    
    CPPUNIT_ASSERT_NO_THROW(dset.write(swrite.data()));

    auto sread = dynamic_array<string>::create(s);

    CPPUNIT_ASSERT_NO_THROW(dset.read(sread.data()));

    std::equal(swrite.begin(),swrite.end(),sread.begin());
    
}

//-----------------------------------------------------------------------------
void field_imp_test::test_string_scalar_data()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    field_imp field{_group,"sscalar",type_id_t::STRING,{1},{1}};
    string write = "hello world";
    field.write(&write);
    string read;
    field.read(&read);
    CPPUNIT_ASSERT(read == write);
    
}

//-----------------------------------------------------------------------------
void field_imp_test::test_bool_scalar_data()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    bool_t read_flag,write_flag;

    field_imp field{_group,"flag",type_id_t::BOOL,{1},{1}};

    read_flag = false; write_flag = true;
    field.write(&write_flag);
    field.read(&read_flag);
    CPPUNIT_ASSERT(read_flag == write_flag);
    
}

//-----------------------------------------------------------------------------
void field_imp_test::test_string_selection() 
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t shape({10,20});
    field_imp field{_group,"text",type_id_t::STRING,
                    type_imp::to_index_vector(shape),{1,20}};


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
        CPPUNIT_ASSERT(field.size()==10);

        //write data
        field.write(writebuf.data());

        //read data back
        field.read(readbuf.data());

        //compare data
        CPPUNIT_ASSERT(std::equal(writebuf.begin(),writebuf.end(),readbuf.begin()));
        field.clear_selections();
        CPPUNIT_ASSERT(field.size() == 10*20);
    }

}



