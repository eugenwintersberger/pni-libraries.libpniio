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

CPPUNIT_TEST_SUITE_REGISTRATION(NXFieldTest);

//------------------------------------------------------------------------------
void NXFieldTest::setUp(){
    file = NXFile::create_file("NXFieldTest.h5",true,0);

	for(size_t i=0;i<n;i++) testdata[i] = i+1;

	nx = 2;
	ny = 3;
    fshape = {nx,ny};
}

//------------------------------------------------------------------------------
void NXFieldTest::tearDown(){
	file.close();
}

//------------------------------------------------------------------------------
void NXFieldTest::testCreation(){
	std::cout<<"NXFieldTest::testCreation()----------------------------";
	std::cout<<std::endl;

	NXField field;

	CPPUNIT_ASSERT_NO_THROW(field = file.create_field<UInt16>("test1"));
    CPPUNIT_ASSERT(field.is_valid());

	Shape shape = {100,123};

	CPPUNIT_ASSERT_NO_THROW(field = file.create_field<Float32>("test2",shape));
	CPPUNIT_ASSERT(field.is_valid());

	Float32Scalar scalar("scalar","m","a scalar");
	Complex128Array array(shape,"array","nm","AFM image");

	CPPUNIT_ASSERT_NO_THROW(field = file.create_field<Float32>(scalar.name()));
	CPPUNIT_ASSERT(field.is_valid());
	CPPUNIT_ASSERT_NO_THROW(field =
            file.create_field<Complex128>(array.name(),array.shape()));
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
    /*
    NXLZFFilter lzf;
    NXDeflateFilter deflate;
    
    deflate.compression_rate(9);
    field = file.create_numericfield("test_defalte",
            TypeID::UINT16,shape,"cps","scalar counter",deflate);
    */

}

//------------------------------------------------------------------------------
void NXFieldTest::testOpen(){
	std::cout<<"NXFieldTest::testOpen()--------------------------------";
	std::cout<<std::endl;
	file.create_field<UInt32>("data1");

	NXField f1 = file.open("data1");

	NXField f2;
	f2 = file.open("data1");
}

//------------------------------------------------------------------------------
void NXFieldTest::testAssignment(){
	std::cout<<"NXFieldTest::testAssignment()--------------------------";
	std::cout<<std::endl;

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
