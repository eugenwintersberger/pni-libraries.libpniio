/*
 * Declaration of Nexus object template.
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * NXNumericFieldTest.cpp
 *
 *  Created on: Dec 3, 2011
 *      Author: Eugen Wintersberger
 */

#include "NXFieldTest.hpp"
#include "../EqualityCheck.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxexceptions.hpp>
#include <pni/io/nx/nexus_utils.hpp>

#include <pni/core/arrays.hpp>

CPPUNIT_TEST_SUITE_REGISTRATION(NXFieldTest);

//------------------------------------------------------------------------------
void NXFieldTest::setUp()
{
    file = nxfile::create_file("NXFieldTest.h5",true,0);

	for(size_t i=0;i<n;i++) testdata[i] = i+1;

	nx = 2;
	ny = 3;
    fshape = {nx,ny};
}

//------------------------------------------------------------------------------
void NXFieldTest::tearDown(){ file.close(); }

//------------------------------------------------------------------------------
void NXFieldTest::test_creation()
{
	std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

	nxfield field;

	CPPUNIT_ASSERT_NO_THROW(field = file.create_field<uint16>("test1"));
    CPPUNIT_ASSERT(field.is_valid());
    CPPUNIT_ASSERT(field.rank()==1);
    CPPUNIT_ASSERT(field.size() == 1);

	//check copy construction
	nxfield field2(field);
	CPPUNIT_ASSERT(field.is_valid());
	CPPUNIT_ASSERT(field2.is_valid());
    CPPUNIT_ASSERT(field2.rank()== 1);
    CPPUNIT_ASSERT(field2.size() == 1);

	//check move construction
	nxfield field3 = std::move(field);
	CPPUNIT_ASSERT(field3.is_valid());
    CPPUNIT_ASSERT(field3.rank() == 1);
    CPPUNIT_ASSERT(field3.size() == 1);
	CPPUNIT_ASSERT(!field.is_valid());

    //create fields with filters
    nxdeflate_filter deflate(9,true);
   
    shape_t shape({100,100});
    field = file.create_field<float32>("test_defalte", shape,deflate);
    CPPUNIT_ASSERT(field.is_valid());
    CPPUNIT_ASSERT(field.rank() == 2);
    CPPUNIT_ASSERT(field.size() == 100*100);

    //throw ShapeMissmatchError if the rank of the chunk and the field shape 
    //do not match
    shape_t cshape({100});
    //file.create_field<float32>("test_fail",shape,cshape);
    /*
    CPPUNIT_ASSERT_THROW(file.create_field<float32>("test_fail",shape,cshape),
                         shape_mismatch_error);
    CPPUNIT_ASSERT_THROW(file.create_field<float32>("test_fail",shape,cshape,deflate),
                         shape_mismatch_error);
                         */

    //create a field with a utilty function
    field = create_field(file,"test_util", type_id_t::UINT32);
    field = create_field(file,"test_util2",type_id_t::FLOAT128,
                         shape_t{0,1024,1024},shape_t{1,1024,1024});
    field = create_field(file,"test_util3",type_id_t::FLOAT128,
                         shape_t{0,1024,1024},shape_t{1,1024,1024},deflate);

}

//------------------------------------------------------------------------------
void NXFieldTest::test_open()
{
	std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

	file.create_field<uint32>("data1");

	nxfield f1 = file.open("data1");

	nxfield f2;
	f2 = file.open("data1");
}

//------------------------------------------------------------------------------
void NXFieldTest::test_parent()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    nxfield f = file.create_field<float64>("/detector/data");
    nxgroup p = f.parent();
    CPPUNIT_ASSERT(p.is_valid());
    CPPUNIT_ASSERT(p.name() == "detector");
    f = file.create_field<uint16>("temperature");
    CPPUNIT_ASSERT(f.parent().name() == "/");
}

//------------------------------------------------------------------------------
void NXFieldTest::test_assignment()
{
	std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

	nxfield field = file.create_field<uint16>("test1");
	CPPUNIT_ASSERT(field.is_valid());

	nxfield field2;

	//testing copy assignment
	CPPUNIT_ASSERT_NO_THROW(field2 = field);
	CPPUNIT_ASSERT(field2.is_valid());
	CPPUNIT_ASSERT(field.is_valid());
    CPPUNIT_ASSERT(field2.size() == field.size());
    CPPUNIT_ASSERT(field2.rank() == field.rank());

	//move assignment
	nxfield field3;
	CPPUNIT_ASSERT_NO_THROW(field3 = std::move(field2));
	CPPUNIT_ASSERT(field3.is_valid());
	CPPUNIT_ASSERT(!field2.is_valid());
    CPPUNIT_ASSERT(field3.size() == field.size());
    CPPUNIT_ASSERT(field3.rank() == field.rank());
}

//------------------------------------------------------------------------------
void NXFieldTest::test_resize()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //create base shape
    shape_t s({0,1024});
    shape_t cs({1,1024});

    nxfield field = file.create_field<float32>("ds",s);
    CPPUNIT_ASSERT(field.is_valid());
    auto shape = field.shape<shape_t>();
    CPPUNIT_ASSERT(std::equal(shape.begin(),shape.end(),s.begin()));

    CPPUNIT_ASSERT_NO_THROW(field.grow(0));
    s = shape_t({1,1024});
    CPPUNIT_ASSERT(field.rank()  == s.size());
    shape = field.shape<shape_t>();
    CPPUNIT_ASSERT(std::equal(shape.begin(),shape.end(),s.begin()));
    s = shape_t({4,1024});
    CPPUNIT_ASSERT_NO_THROW(field.grow(0,3));
    CPPUNIT_ASSERT(field.rank()  == s.size());
    shape = field.shape<shape_t>();
    CPPUNIT_ASSERT(std::equal(shape.begin(),shape.end(),s.begin()));

    nxfield field2 = file.create_field<string>("ss");
    CPPUNIT_ASSERT(field2.rank() == 1);
    CPPUNIT_ASSERT(field2.size() == 1);
    CPPUNIT_ASSERT_NO_THROW(field2.grow(0));
    CPPUNIT_ASSERT(field2.rank() == 1);
    CPPUNIT_ASSERT(field2.size() == 2);
    CPPUNIT_ASSERT_NO_THROW(field2.grow(0,10));
    CPPUNIT_ASSERT(field2.rank() == 1);
    CPPUNIT_ASSERT(field2.size() == 12);

    //reshape the dataset
    s = shape_t{100,512};
    CPPUNIT_ASSERT_NO_THROW(field.resize(s));
    shape = field.shape<shape_t>();
    CPPUNIT_ASSERT(std::equal(shape.begin(),shape.end(),s.begin()));
}
//------------------------------------------------------------------------------
void NXFieldTest::test_io_string_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    nxfield field1 = file.create_field<string>("scalar");

    string write,read;
    write = "hello";
    read = "";

    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(write == read);

    CPPUNIT_ASSERT_NO_THROW(field1.grow(0));
    CPPUNIT_ASSERT_THROW(field1.write(write),shape_mismatch_error);

    //try to write a literal
    nxfield field2 = file.create_field<string>("scalar_2");
    CPPUNIT_ASSERT_NO_THROW(field2.write("hello world"));
    CPPUNIT_ASSERT_NO_THROW(field2.read(read));
    CPPUNIT_ASSERT(read == "hello world");
}

//------------------------------------------------------------------------------
void NXFieldTest::test_io_bool_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    nxfield field1 = file.create_field<bool_t>("scalar");

    bool_t write,read;
    write = true;
    read = false;

    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(write == read);

    CPPUNIT_ASSERT_NO_THROW(field1.grow(0));
    CPPUNIT_ASSERT_THROW(field1.write(write),shape_mismatch_error);
}
//------------------------------------------------------------------------------
void NXFieldTest::test_io_string_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t s{3,4};
    auto write = dynamic_array<string>::create(s);
    auto read  = dynamic_array<string>::create(s);

    std::fill(write.begin(),write.end(),"Hello");
    std::fill(read.begin(),read.end(),"");

    nxfield field1 = file.create_field<string>("array",s);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(std::equal(write.begin(),write.end(),read.begin()));

    field1 = file.create_field<string>("array2",{2,2});
    CPPUNIT_ASSERT_THROW(field1.write(write),shape_mismatch_error);

    nxdeflate_filter deflate;
    deflate.compression_rate(9);
    deflate.shuffle(true);

    field1 = file.create_field<string>("array2_delfate",s,deflate);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(std::equal(write.begin(),write.end(),read.begin()));

}

//------------------------------------------------------------------------------
/*
void NXFieldTest::test_io_bool_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t s{3,4};
    darray<bool> write(s);
    darray<bool> read(s);

    std::fill(write.begin(),write.end(),true);
    std::fill(write.begin(),write.end(),false);

    nxfield field1 = file.create_field<bool>("array",s);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(std::equal(write.begin(),write.end(),read.begin()));

    field1 = file.create_field<bool>("array2",{2,2});
    CPPUNIT_ASSERT_THROW(field1.write(write),shape_mismatch_error);

    nxdeflate_filter deflate;
    deflate.compression_rate(9);
    deflate.shuffle(true);

    field1 = file.create_field<bool>("array2_delfate",s,deflate);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(std::equal(write.begin(),write.end(),read.begin()));

}
*/

//-----------------------------------------------------------------------------
void NXFieldTest::test_grow()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t s{0};
    nxfield field = file.create_field<bool_t>("flags",s);
    CPPUNIT_ASSERT(field.size() == 0);

    field.grow(0);
    CPPUNIT_ASSERT(field.size() == 1);
    field.grow(0);
    CPPUNIT_ASSERT(field.size() == 2);
}

//-----------------------------------------------------------------------------
void NXFieldTest::test_io_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    auto data = dynamic_array<float64>::create(shape_t({10,5}));
    array o(data);

    nxfield field = file.create_field<float64>("data",data.shape<shape_t>());
    double index = 0.;
    for(auto iter=o.begin();iter!=o.end();++iter)
        *iter = index++;

    field.write(o);

    //read back data
    array o2(data);
    std::fill(o2.begin(),o2.end(),float64(0));
    

    field.read(o2);
    for(auto iter1=o.begin(),iter2=o2.begin();
        iter1!=o.end();
        ++iter1,++iter2)
        check_equality(iter1->as<float64>(),iter2->as<float64>());

}

