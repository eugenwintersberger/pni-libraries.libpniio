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

CPPUNIT_TEST_SUITE_REGISTRATION(field_imp_test);


void field_imp_test::setUp()
{
    _file = file_imp::create("file_imp_test.h5",true,0);
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
}

//-----------------------------------------------------------------------------
void field_imp_test::test_create_copy()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

}

//-----------------------------------------------------------------------------
void field_imp_test::test_create_move()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

}

//-----------------------------------------------------------------------------
void field_imp_test::test_assignment()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
}

//----------------------------------------------------------------------------
void field_imp_test::test_inquery()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;


}


//-----------------------------------------------------------------------------
void field_imp_test::test_parent()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    /*
    H5Datatype type = H5DatatypeFactory::create_type<uint16>();
    H5Dataspace space;
    H5Dataset d("/detector/data",_file,type,space);

    H5Group p(d.parent());
    CPPUNIT_ASSERT(p.name() == "detector");
    H5Dataset t("temperature",_file,type,space);
    CPPUNIT_ASSERT(H5Group(t.parent()).name() == "/");
    */
}

//-----------------------------------------------------------------------------
void field_imp_test::test_resize()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //create base shape
    /*
    shape_t s{0,1024};
    shape_t cs{1,1024};
    H5Datatype type = H5DatatypeFactory::create_type<uint32>();
    H5Dataspace space({0,1024},{H5S_UNLIMITED,H5S_UNLIMITED});

    H5Dataset ds("ds",_group,type,space,cs);

    CPPUNIT_ASSERT_NO_THROW(ds.grow(0));
    s = shape_t({1,1024});
    CPPUNIT_ASSERT(ds.rank()  == s.size());
    CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),ds.shape<shape_t>().begin()));
    s = shape_t({4,1024});
    CPPUNIT_ASSERT_NO_THROW(ds.grow(0,3));
    CPPUNIT_ASSERT(ds.rank()  == s.size());
    CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),ds.shape<shape_t>().begin()));

    s = shape_t{0};
    cs = shape_t{1};
    type = H5DatatypeFactory::create_type<string>();
    CPPUNIT_ASSERT_NO_THROW(space = H5Dataspace({0},{H5S_UNLIMITED}));
    H5Dataset ss("ss",_group,type,space,cs);
    CPPUNIT_ASSERT(ss.rank() == 1);
    CPPUNIT_ASSERT(ss.size() == 0);
    CPPUNIT_ASSERT_NO_THROW(ss.grow(0));
    CPPUNIT_ASSERT(ss.rank() == 1);
    CPPUNIT_ASSERT(ss.size() == 1);
    CPPUNIT_ASSERT_NO_THROW(ss.grow(0,10));
    CPPUNIT_ASSERT(ss.rank() == 1);
    CPPUNIT_ASSERT(ss.size() == 11);

    //reshape the dataset
    shape_t ns{100,512};
    CPPUNIT_ASSERT_NO_THROW(ds.resize(ns));
    CPPUNIT_ASSERT(std::equal(ns.begin(),ns.end(),ds.shape<shape_t>().begin()));
    */
}

//------------------------------------------------------------------------------
void field_imp_test::test_string_array_data()
{
    /*
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t s{2,3};
    H5Datatype type = H5DatatypeFactory::create_type<string>();
    H5Dataspace space(s);

    H5Dataset dset("sarray",_group,type,space,s);

    auto swrite = dynamic_array<string>::create(s);
    swrite(0,0) = "hello"; swrite(0,1) = "world"; swrite(0,2) = "this";
    swrite(1,0) = "is"; swrite(1,1) = "a string"; swrite(1,2) = "array";
    
    CPPUNIT_ASSERT_NO_THROW(dset.write(swrite.data()));

    auto sread = dynamic_array<string>::create(s);

    CPPUNIT_ASSERT_NO_THROW(dset.read(sread.data()));

    std::equal(swrite.begin(),swrite.end(),sread.begin());
    */
}

//-----------------------------------------------------------------------------
void field_imp_test::test_string_scalar_data()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    /*
    H5Datatype type = H5DatatypeFactory::create_type<string>();
    H5Dataspace space;

    H5Dataset dset("sscalar",_group,type,space);

    string write = "hello world";
    dset.write(&write);
    string read;
    dset.read(&read);
    CPPUNIT_ASSERT(read == write);
    */
}

//-----------------------------------------------------------------------------
void field_imp_test::test_bool_scalar_data()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    /*
    bool_t read_flag,write_flag;

    H5Datatype type = H5DatatypeFactory::create_type<bool_t>();
    H5Dataspace space;

    H5Dataset dset("flag",_group,type,space);

    read_flag = false; write_flag = true;
    dset.write(&write_flag);
    dset.read(&read_flag);
    CPPUNIT_ASSERT(read_flag == write_flag);
    */
}

//-----------------------------------------------------------------------------
void field_imp_test::test_string_selection() 
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    /*
    H5Datatype type = H5DatatypeFactory::create_type<string>();
    shape_t shape({10,20});
    H5Dataspace space(shape);
    H5Dataset dset("text",_group,type,space);

    shape_t s;
    s = dset.shape<shape_t>();
    CPPUNIT_ASSERT(dset.size()==10*20);

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
        dset.apply_selection(selection);
        CPPUNIT_ASSERT(dset.size()==10);

        //write data
        dset.write(writebuf.data());

        //read data back
        dset.read(readbuf.data());

        //compare data
        CPPUNIT_ASSERT(std::equal(writebuf.begin(),writebuf.end(),readbuf.begin()));
        dset.clear_selections();
        CPPUNIT_ASSERT(dset.size() == 10*20);
    }
    */

}



