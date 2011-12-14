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
 * NXBinaryFieldTest.cpp
 *
 *  Created on: Dec 5, 2011
 *      Author: Eugen Wintersberger
 */

#include "NXBinaryFieldTest.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include "NX.hpp"
#include "NXExceptions.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NXBinaryFieldTest);

//------------------------------------------------------------------------------
void NXBinaryFieldTest::setUp(){
	file.filename("NXBinaryFieldTest.h5");
	file.overwrite(true);
	file.read_only(false);
	file.create();
	testdata[0] = 10; testdata[1] = 12; testdata[2] = 100;
	testdata[3] = 2;  testdata[4] = 200; testdata[5] = 201;
	testdata[6] = 17; testdata[7] = 42; testdata[8] = 193;
	testdata[9] = 192;
}

//------------------------------------------------------------------------------
void NXBinaryFieldTest::tearDown(){
	file.close();
}

//------------------------------------------------------------------------------
void NXBinaryFieldTest::testCreation(){
	std::cout<<"NXBinaryFieldTest::testCreation()-----------------------------";
	std::cout<<std::endl;

	NXBinaryField field;  //default constructor

	//standard construction
	NXBinaryField f2 = file.create_binaryfield("text");
	CPPUNIT_ASSERT(f2.is_open());

	//copy construction
	NXBinaryField f3(f2);
	CPPUNIT_ASSERT(f2.is_open());
	CPPUNIT_ASSERT(f3.is_open());

	//move construction
	NXBinaryField f4 = std::move(f2);
	CPPUNIT_ASSERT(f4.is_open());
	CPPUNIT_ASSERT(!f2.is_open());
}

//------------------------------------------------------------------------------
void NXBinaryFieldTest::testOpen(){
	std::cout<<"NXBinaryFieldTest::testOpen()---------------------------------";
	std::cout<<std::endl;

	file.create_binaryfield("text1");
	file.create_binaryfield("text2");

	NXBinaryField f1 = file.open("text1");
	f1 = file.open("text2");

	file.create_numericfield("data",TypeID::UINT32,"cps","numeric test data");
	CPPUNIT_ASSERT_THROW(f1 = std::move(file.open("data")),pni::nx::NXFieldError);
}

//------------------------------------------------------------------------------
void NXBinaryFieldTest::testAssignment(){
	std::cout<<"NXBinaryFieldTest::testAssignment()---------------------------";
	std::cout<<std::endl;

	NXBinaryField f;
	CPPUNIT_ASSERT_NO_THROW(f = file.create_binaryfield("text1"));
	CPPUNIT_ASSERT(f.is_open());

	NXBinaryField f2;
	CPPUNIT_ASSERT_NO_THROW(f2 = f);
	CPPUNIT_ASSERT(f2.is_open());
	CPPUNIT_ASSERT(f.is_open());

	NXBinaryField f3;
	CPPUNIT_ASSERT_NO_THROW(f3 = std::move(f));
	CPPUNIT_ASSERT(f3.is_open());
	CPPUNIT_ASSERT(!f.is_open());
}

//------------------------------------------------------------------------------
void NXBinaryFieldTest::testAppend(){
	std::cout<<"NXBinaryFieldTest::testAppend()-------------------------------";
	std::cout<<std::endl;

	Buffer<Binary> buffer(10);
	for(size_t i=0;i<buffer.size();i++) buffer[i] = testdata[i];

	NXBinaryField field = file.create_binaryfield("bindump");

	CPPUNIT_ASSERT_NO_THROW(field.append(buffer));
}

//------------------------------------------------------------------------------
void NXBinaryFieldTest::testGetAll(){
	std::cout<<"NXBinaryFieldTest::testGetAll()-------------------------------";
	std::cout<<std::endl;

	Buffer<Binary> writeb(10),readb(10);
	for(size_t i=0;i<writeb.size();i++) writeb[i] = testdata[i];

	NXBinaryField field = file.create_binaryfield("bindump");
	CPPUNIT_ASSERT_NO_THROW(field.append(writeb));

	//readback data
	CPPUNIT_ASSERT_NO_THROW(field.get(readb));

	for(size_t i=0;i<readb.size();i++){
		CPPUNIT_ASSERT(readb[i] == testdata[i]);
	}

}

//------------------------------------------------------------------------------
void NXBinaryFieldTest::testGet(){
	std::cout<<"NXBinaryFieldTest::testGet()----------------------------------";
	std::cout<<std::endl;

	Buffer<Binary> writeb(10), readb(3);
	for(size_t i=0;i<writeb.size();i++) writeb[i] = testdata[i];

	NXBinaryField field = file.create_binaryfield("bindump");
	CPPUNIT_ASSERT_NO_THROW(field.append(writeb));

	//partial read back
	CPPUNIT_ASSERT_NO_THROW(field.get(2,readb));
	for(size_t i=0;i<readb.size();i++) CPPUNIT_ASSERT(readb[i] == testdata[i+2]);

	//throw an exception
	CPPUNIT_ASSERT_THROW(field.get(100,readb),pni::nx::NXFieldError);
	CPPUNIT_ASSERT_THROW(field.get(8,readb),pni::nx::NXFieldError);
}

//------------------------------------------------------------------------------
void NXBinaryFieldTest::testSet(){
	std::cout<<"NXBinaryFieldTest::testSet()----------------------------------";
	std::cout<<std::endl;

	Buffer<Binary> writeb(10),readb(10);
	for(size_t i=0;i<writeb.size();i++) writeb[i] = testdata[i];

	NXBinaryField field = file.create_binaryfield("bindump");
	CPPUNIT_ASSERT_NO_THROW(field.set(5,writeb));

	//readback data
	CPPUNIT_ASSERT_NO_THROW(field.get(5,readb));
	for(size_t i=0;i<readb.size();i++) CPPUNIT_ASSERT(readb[i] == testdata[i]);

}

//------------------------------------------------------------------------------
void NXBinaryFieldTest::testStreamIO(){
	std::cout<<"NXBinaryFieldTest::testStreamIO()-----------------------------";
	std::cout<<std::endl;

	Buffer<Binary> writeb(10),readb(10);
	for(size_t i=0;i<writeb.size();i++) writeb[i] = testdata[i];

	NXBinaryField field = file.create_binaryfield("bindump");

	CPPUNIT_ASSERT_NO_THROW(field<<writeb);
	CPPUNIT_ASSERT_NO_THROW(field<<writeb);

	CPPUNIT_ASSERT_NO_THROW(field>>readb);
	CPPUNIT_ASSERT_NO_THROW(field>>readb);

}
