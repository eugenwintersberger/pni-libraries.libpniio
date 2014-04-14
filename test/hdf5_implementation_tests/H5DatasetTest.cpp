/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: Jan 17, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include "H5DatasetTest.hpp"
#include <boost/current_function.hpp>
#include <pni/io/nx/h5/H5DeflateFilter.hpp>

CPPUNIT_TEST_SUITE_REGISTRATION(H5DatasetTest);


void H5DatasetTest::setUp()
{
    _file = H5File::create_file("H5DatasetTest.h5",true,0);
    _group =H5Group("data",_file);
}

//-----------------------------------------------------------------------------
void H5DatasetTest::tearDown()
{
    _group.close();
    _file.close();
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_creation()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t s{10,50};
    H5Dataspace space(s);
    H5Datatype type   = H5DatatypeFactory::create_type<type_id_t::FLOAT32>();

    //create contiguous dataset
    H5Dataset ds1("ds1",_group,type,space);
    CPPUNIT_ASSERT(ds1.is_valid());
    CPPUNIT_ASSERT(ds1.type_id()==type_id_t::FLOAT32);
    CPPUNIT_ASSERT(ds1.rank() == 2);
    CPPUNIT_ASSERT(ds1.size() == 10*50);

    //create a chunked dataset
    shape_t cs{1,50};
    type = H5DatatypeFactory::create_type<type_id_t::UINT32>();
    H5Dataset ds2("ds2",_group,type,space,cs);
    CPPUNIT_ASSERT(ds2.is_valid());
    CPPUNIT_ASSERT(ds2.type_id() == type_id_t::UINT32);

    //create a scalar dataset
    type = H5DatatypeFactory::create_type<type_id_t::FLOAT128>();
    H5Dataset ds3("ds3",_group,type,H5Dataspace());
    CPPUNIT_ASSERT(ds3.is_valid());
    CPPUNIT_ASSERT(ds3.type_id() == type_id_t::FLOAT128);
    CPPUNIT_ASSERT(ds3.rank() == 0);
    CPPUNIT_ASSERT(ds3.size() == 1);

    //test copy constructor
    H5Dataset ds4 = ds2;
    CPPUNIT_ASSERT(ds4.is_valid());
    CPPUNIT_ASSERT(ds2.is_valid());
    CPPUNIT_ASSERT(ds4.type_id() == ds2.type_id());
    CPPUNIT_ASSERT(ds4.size() == ds2.size());
    CPPUNIT_ASSERT(ds4.rank() == ds2.rank());

    //test move constructor
    H5Dataset ds5 = std::move(ds4);
    CPPUNIT_ASSERT(ds5.is_valid());
    CPPUNIT_ASSERT(!ds4.is_valid());
    CPPUNIT_ASSERT(ds5.type_id() == ds2.type_id());
    CPPUNIT_ASSERT(ds5.size() == ds2.size());
    CPPUNIT_ASSERT(ds5.rank() == ds2.rank());

    //create a chunked datatype with a filter
    H5DeflateFilter filter(9,true);
    H5Dataset dsc("compressed_data",_group,type,space,cs,filter);
    
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    shape_t s{1024,512};
    H5Datatype type = H5DatatypeFactory::create_type<type_id_t::FLOAT32>();
    H5Dataspace space(s);
    H5Dataset ds("ds",_group,type,space);

    H5Dataset ds1;

    //testing copy assignment
    CPPUNIT_ASSERT_NO_THROW(ds1 = ds);
    CPPUNIT_ASSERT(ds1.is_valid());
    CPPUNIT_ASSERT(ds.is_valid());
    
    //testing move assignment
    H5Dataset ds2;
    CPPUNIT_ASSERT_NO_THROW(ds2 = std::move(ds1));
    CPPUNIT_ASSERT(ds2.is_valid());
    CPPUNIT_ASSERT(!ds1.is_valid());
    
    //testing close
    ds2.close();
    CPPUNIT_ASSERT(!ds2.is_valid());

}

//----------------------------------------------------------------------------
void H5DatasetTest::test_inquery()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    shape_t s = {1024,512};
    H5Datatype type = H5DatatypeFactory::create_type<float128>();
    H5Dataspace space(s);
    H5Dataset ds("ds",_file,type,space);

    CPPUNIT_ASSERT(ds.is_valid());
    CPPUNIT_ASSERT(ds.filename() == "H5DatasetTest.h5");
    CPPUNIT_ASSERT(ds.type_id() == type_id_t::FLOAT128);
    CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),ds.shape<shape_t>().begin()));

    H5Dataset ds2("/scan_1/detector/data",_file,type,space);
    CPPUNIT_ASSERT(ds2.path() == "/scan_1/detector/data");
    CPPUNIT_ASSERT(ds2.base() == "/scan_1/detector");
    CPPUNIT_ASSERT(ds2.name() == "data");
    H5Group g = ds2.parent();
    CPPUNIT_ASSERT(g.is_valid());
    CPPUNIT_ASSERT(g.path() == "/scan_1/detector");
    CPPUNIT_ASSERT(g.base() == "/scan_1");
    CPPUNIT_ASSERT(g.name() == "detector");
    g = _file.open("/scan_1/detector");
    CPPUNIT_ASSERT(g.path() == "/scan_1/detector");
    CPPUNIT_ASSERT(g.base() == "/scan_1");
    CPPUNIT_ASSERT(g.name() == "detector");
    CPPUNIT_ASSERT_NO_THROW(ds = g.open("/scan_1/detector/data"));
    CPPUNIT_ASSERT(ds2.path() == "/scan_1/detector/data");
    CPPUNIT_ASSERT(ds2.base() == "/scan_1/detector");
    CPPUNIT_ASSERT(ds2.name() == "data");

}


//-----------------------------------------------------------------------------
void H5DatasetTest::test_parent()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    H5Datatype type = H5DatatypeFactory::create_type<uint16>();
    H5Dataspace space;
    H5Dataset d("/detector/data",_file,type,space);

    H5Group p(d.parent());
    CPPUNIT_ASSERT(p.name() == "detector");
    H5Dataset t("temperature",_file,type,space);
    CPPUNIT_ASSERT(H5Group(t.parent()).name() == "/");
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_resize()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //create base shape
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
}

//------------------------------------------------------------------------------
void H5DatasetTest::test_string_array_data()
{
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
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_string_scalar_data()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    H5Datatype type = H5DatatypeFactory::create_type<string>();
    H5Dataspace space;

    H5Dataset dset("sscalar",_group,type,space);

    string write = "hello world";
    dset.write(&write);
    string read;
    dset.read(&read);
    CPPUNIT_ASSERT(read == write);
}

//-----------------------------------------------------------------------------
void H5DatasetTest::test_bool_scalar_data()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    Bool read_flag,write_flag;

    H5Datatype type = H5DatatypeFactory::create_type<Bool>();
    H5Dataspace space;

    H5Dataset dset("flag",_group,type,space);

    read_flag = false; write_flag = true;
    dset.write(&write_flag);
    dset.read(&read_flag);
    CPPUNIT_ASSERT(read_flag == write_flag);

}



//-----------------------------------------------------------------------------
void H5DatasetTest::test_string_selection() 
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
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

}



