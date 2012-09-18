/*
 * Declaration of Nexus object template.
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * NXNumericFieldTest.cpp
 *
 *  Created on: Dec 3, 2011
 *      Author: Eugen Wintersberger
 */

#include "NXFieldTest.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include "NX.hpp"
#include "NXExceptions.hpp"
#include "NXFieldUtils.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NXFieldTest);

//------------------------------------------------------------------------------
void NXFieldTest::setUp()
{
    file = NXFile::create_file("NXFieldTest.h5",true,0);

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

	NXField field;

	CPPUNIT_ASSERT_NO_THROW(field = file.create_field<UInt16>("test1"));
    CPPUNIT_ASSERT(field.is_valid());

	//check copy construction
	NXField field2(field);
	CPPUNIT_ASSERT(field2.is_valid());
	CPPUNIT_ASSERT(field.is_valid());

	//check move construction
	NXField field3 = std::move(field);
	CPPUNIT_ASSERT(field3.is_valid());
	CPPUNIT_ASSERT(!field.is_valid());

    //create fields with filters
    NXDeflateFilter deflate(9,true);
   
    shape_t shape{100,100};
    field = file.create_field<Float32>("test_defalte", shape,deflate);

    //create a field with a utilty function
    field = create_field(file,"test_util", TypeID::UINT32);
    field = create_field(file,"test_util2",TypeID::FLOAT128,
                         shape_t{0,1024,1024},shape_t{1,1024,1024});
    field = create_field(file,"test_util3",TypeID::FLOAT128,
                         shape_t{0,1024,1024},shape_t{1,1024,1024},deflate);

}

//------------------------------------------------------------------------------
void NXFieldTest::test_open()
{
	std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

	file.create_field<UInt32>("data1");

	NXField f1 = file.open("data1");

	NXField f2;
	f2 = file.open("data1");
}

//------------------------------------------------------------------------------
void NXFieldTest::test_assignment()
{
	std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

	NXField field = file.create_field<UInt16>("test1");
	CPPUNIT_ASSERT(field.is_valid());

	NXField field2;

	//testing copy assignment
	CPPUNIT_ASSERT_NO_THROW(field2 = field);
	CPPUNIT_ASSERT(field2.is_valid());
	CPPUNIT_ASSERT(field.is_valid());

	//move assignment
	NXField field3;
	CPPUNIT_ASSERT_NO_THROW(field3 = std::move(field));
	CPPUNIT_ASSERT(field3.is_valid());
	CPPUNIT_ASSERT(!field.is_valid());
}

//------------------------------------------------------------------------------
void NXFieldTest::test_resize()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //create base shape
    shape_t s = {0,1024};
    shape_t cs = {1,1024};

    NXField field = file.create_field<Float32>("ds",s);
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

    NXField field2 = file.create_field<String>("ss");
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
    NXField field1 = file.create_field<String>("scalar");

    String write,read;
    write = "hello";
    read = "";

    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(write == read);

    CPPUNIT_ASSERT_NO_THROW(field1.grow(0));
    CPPUNIT_ASSERT_THROW(field1.write(write),ShapeMissmatchError);
}

//------------------------------------------------------------------------------
void NXFieldTest::test_io_bool_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    NXField field1 = file.create_field<Bool>("scalar");

    Bool write,read;
    write = true;
    read = false;

    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(write == read);

    CPPUNIT_ASSERT_NO_THROW(field1.grow(0));
    CPPUNIT_ASSERT_THROW(field1.write(write),ShapeMissmatchError);
}
//------------------------------------------------------------------------------
void NXFieldTest::test_io_string_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t s{3,4};
    DArray<String> write(s);
    DArray<String> read(s);

    std::fill(write.begin(),write.end(),"Hello");
    std::fill(read.begin(),read.end(),"");

    NXField field1 = file.create_field<String>("array",s);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(std::equal(write.begin(),write.end(),read.begin()));

    field1 = file.create_field<String>("array2",{2,2});
    CPPUNIT_ASSERT_THROW(field1.write(write),ShapeMissmatchError);

    NXDeflateFilter deflate;
    deflate.compression_rate(9);
    deflate.shuffle(true);

    field1 = file.create_field<String>("array2_delfate",s,deflate);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(std::equal(write.begin(),write.end(),read.begin()));

}

//------------------------------------------------------------------------------
void NXFieldTest::test_io_bool_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t s{3,4};
    DArray<Bool> write(s);
    DArray<Bool> read(s);

    std::fill(write.begin(),write.end(),true);
    std::fill(write.begin(),write.end(),false);

    NXField field1 = file.create_field<Bool>("array",s);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(std::equal(write.begin(),write.end(),read.begin()));

    field1 = file.create_field<Bool>("array2",{2,2});
    CPPUNIT_ASSERT_THROW(field1.write(write),ShapeMissmatchError);

    NXDeflateFilter deflate;
    deflate.compression_rate(9);
    deflate.shuffle(true);

    field1 = file.create_field<Bool>("array2_delfate",s,deflate);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read));
    CPPUNIT_ASSERT(std::equal(write.begin(),write.end(),read.begin()));

}
//-----------------------------------------------------------------------------
void NXFieldTest::test_io_string_buffer()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t s{5};
    DBuffer<String> write_buffer({"Hello","world","this","is","a test"});
    DBuffer<String> read_buffer(5);

    NXField field1 = file.create_field<String>("buffer",s);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write_buffer));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read_buffer));

    CPPUNIT_ASSERT(std::equal(write_buffer.begin(),write_buffer.end(),
                              read_buffer.begin()));

    //check exceptions
    CPPUNIT_ASSERT_NO_THROW(field1 = file.create_field<String>("buffer2",{200}));
    CPPUNIT_ASSERT_THROW(field1.write(write_buffer),SizeMissmatchError);

    write_buffer.free();
    CPPUNIT_ASSERT_THROW(field1.write(write_buffer),MemoryNotAllocatedError);
}

//-----------------------------------------------------------------------------
void NXFieldTest::test_io_bool_buffer()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t s{5};
    DBuffer<Bool> write_buffer({true,true,false,true,false});
    DBuffer<Bool> read_buffer({false,false,false,false,false});

    NXField field1 = file.create_field<Bool>("buffer",s);
    CPPUNIT_ASSERT_NO_THROW(field1.write(write_buffer));
    CPPUNIT_ASSERT_NO_THROW(field1.read(read_buffer));

    CPPUNIT_ASSERT(std::equal(write_buffer.begin(),write_buffer.end(),
                              read_buffer.begin()));

    //check exceptions
    CPPUNIT_ASSERT_NO_THROW(field1 = file.create_field<Bool>("buffer2",{200}));
    CPPUNIT_ASSERT_THROW(field1.write(write_buffer),SizeMissmatchError);

    write_buffer.free();
    CPPUNIT_ASSERT_THROW(field1.write(write_buffer),MemoryNotAllocatedError);
}

//-----------------------------------------------------------------------------
void NXFieldTest::test_grow()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    shape_t s{0};
    NXField field = file.create_field<Bool>("flags",s);
    CPPUNIT_ASSERT(field.size() == 0);

    field.grow(0);
    CPPUNIT_ASSERT(field.size() == 1);
    field.grow(0);
    CPPUNIT_ASSERT(field.size() == 2);
}


