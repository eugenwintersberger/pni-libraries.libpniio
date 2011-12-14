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

#include "NXNumericFieldTest.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include "NX.hpp"
#include "NXExceptions.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NXNumericFieldTest);

//------------------------------------------------------------------------------
void NXNumericFieldTest::setUp(){
	file.filename("NXNumericFieldTest.h5");
	file.overwrite(true);
	file.read_only(false);
	file.create();

	for(size_t i=0;i<n;i++) testdata[i] = i+1;

	nx = 2;
	ny = 3;
	fshape.rank(2);
	fshape.dim(0,nx);
	fshape.dim(1,ny);
}

//------------------------------------------------------------------------------
void NXNumericFieldTest::tearDown(){
	file.close();
}

//------------------------------------------------------------------------------
void NXNumericFieldTest::testCreation(){
	std::cout<<"NXNumericFieldTest::testCreation()----------------------------";
	std::cout<<std::endl;

	NXNumericField field;

	CPPUNIT_ASSERT_NO_THROW(field = file.create_numericfield("test1",
							TypeID::UINT16,"cps","scalar counter"));
	CPPUNIT_ASSERT(field.is_open());

	Shape shape(2);
	shape.dim(0,100);
	shape.dim(1,123);

	CPPUNIT_ASSERT_NO_THROW(field = file.create_numericfield("test2",
							TypeID::FLOAT32,shape,"cps","array detector"));
	CPPUNIT_ASSERT(field.is_open());

	Float32Scalar scalar("scalar","m","a scalar");
	Complex128Array array(shape,"array","nm","AFM image");

	CPPUNIT_ASSERT_NO_THROW(field = file.create_numericfield(scalar));
	CPPUNIT_ASSERT(field.is_open());
	CPPUNIT_ASSERT_NO_THROW(field = file.create_numericfield(array));
	CPPUNIT_ASSERT(field.is_open());

	//check copy construction
	NXNumericField field2(field);
	CPPUNIT_ASSERT(field2.is_open());
	CPPUNIT_ASSERT(field.is_open());

	//check move construction
	NXNumericField field3 = std::move(field);
	CPPUNIT_ASSERT(field3.is_open());
	CPPUNIT_ASSERT(!field.is_open());

}

//------------------------------------------------------------------------------
void NXNumericFieldTest::testOpen(){
	std::cout<<"NXNumericFieldTest::testOpen()--------------------------------";
	std::cout<<std::endl;
	file.create_numericfield("data1",TypeID::UINT32,"cps","test data");

	NXNumericField f1 = file.open("data1");

	NXNumericField f2;
	f2 = file.open("data1");
}

//------------------------------------------------------------------------------
void NXNumericFieldTest::testAssignment(){
	std::cout<<"NXNumericFieldTest::testAssignment()--------------------------";
	std::cout<<std::endl;

	NXNumericField field = file.create_numericfield("test1",TypeID::UINT16,
							"cps","scalar field");
	CPPUNIT_ASSERT(field.is_open());

	NXNumericField field2;

	//testing copy assignment
	CPPUNIT_ASSERT_NO_THROW(field2 = field);
	CPPUNIT_ASSERT(field2.is_open());
	CPPUNIT_ASSERT(field.is_open());

	//move assignment
	NXNumericField field3;
	CPPUNIT_ASSERT_NO_THROW(field3 = std::move(field));
	CPPUNIT_ASSERT(field3.is_open());
	CPPUNIT_ASSERT(!field.is_open());
}

//------------------------------------------------------------------------------
void NXNumericFieldTest::testAppend(){
	std::cout<<"NXNumericFieldTest::testAppend()------------------------------";
	std::cout<<std::endl;

	Shape shape(2);
	shape.dim(0,nx);
	shape.dim(1,ny);
	Float32Array earray(shape,"detector","cps","an area detector");

	NXNumericField field1 = file.create_numericfield(earray);
	//append single elements
	for(size_t i=0;i<4;i++){
		earray = testdata[i];
		field1.append(earray);
	}

	//append an entire block
	Shape tshape(3);
	tshape.dim(0,6);
	tshape.dim(1,nx);
	tshape.dim(2,ny);
	Float32Array tarray(tshape,"detector","a.u","a data block");
	CPPUNIT_ASSERT_THROW(field1.append(tarray),pni::nx::NXFieldError);
	tarray.unit("cps");
	Index index(3);
	for(index[0]=0;index[0]<6;index[0]++){
		for(index[1]=0;index[1]<nx;index[1]++){
			for(index[2]=0;index[2]<ny;index[2]++){
				tarray(index) = testdata[index[0]+4];
			}
		}
	}
	CPPUNIT_ASSERT_NO_THROW(field1.append(tarray));

	//check for scalar numeric field
	UInt16Scalar scalar("scalar","cps","a scalar counter");
	field1 = file.create_numericfield(scalar);
	for(size_t i=0; i<5;i++){
		scalar = testdata[i];
		field1.append(scalar);
	}

	//append a complete array
	Shape sshape(1);
	sshape.dim(0,5);
	UInt16Array sarray(sshape,scalar.name(),scalar.unit(),scalar.description());
	for(size_t i=0;i<sshape.size();i++) sarray[i] = testdata[i+5];
	CPPUNIT_ASSERT_NO_THROW(field1.append(sarray));

}

//------------------------------------------------------------------------------
void NXNumericFieldTest::testGetIndividual(){
	std::cout<<"NXNumericFieldTest::testGetIndividual()-----------------------";
	std::cout<<std::endl;

	//write data
	testAppend();
	String unit;

	NXNumericField field1 = file.open("scalar");
	Float32Array array(field1.shape());
	field1.get_attr("units",unit);
	array.unit(unit);

	CPPUNIT_ASSERT_NO_THROW(field1.get(0,array));
	Index index(1);
	for(index[0] = 0; index[0] < array.shape().dim(0); index[0]++){
		CPPUNIT_ASSERT(array(index)==testdata[index[0]]);
	}
	CPPUNIT_ASSERT_THROW(field1.get(1,array),pni::nx::NXFieldError);

	Shape shape(field1.shape());
	shape.dim(0,4);
	array.reset(); array.shape(shape); array.allocate();
	CPPUNIT_ASSERT_NO_THROW(field1.get(2,array));
	for(index[0] = 0; index[0] < array.shape().dim(0); index[0]++){
		CPPUNIT_ASSERT(array(index) == testdata[index[0]+2]);
	}

	CPPUNIT_ASSERT_THROW(field1.get(8,array),pni::nx::NXFieldError);

	Float32Scalar scalar("scalar",unit);
	for(size_t i=0;i<field1.shape().dim(0);i++){
		CPPUNIT_ASSERT_NO_THROW(field1.get(i,scalar));
		CPPUNIT_ASSERT(scalar == testdata[i]);
	}

}

//------------------------------------------------------------------------------
void NXNumericFieldTest::testGetAll(){
	std::cout<<"NXNumericFieldTest::testGetAll()------------------------------";
	std::cout<<std::endl;

	//write data
	testAppend();
	String unit;

	Float32Array array;
	UInt32Array scalar;

	NXNumericField field1 = file.open("detector");
	array.shape(field1.shape());
	field1.get_attr("units",unit);
	array.unit(unit);
	array.allocate();
	CPPUNIT_ASSERT_NO_THROW(field1.get(array));
	Index index(3);
	for(index[0] = 0;index[0] < array.shape().dim(0);index[0]++){
		for(index[1] = 0;index[1] < array.shape().dim(1);index[1]++){
			for(index[2]=0;index[2] < array.shape().dim(2);index[2]++){
				CPPUNIT_ASSERT(array(index) == testdata[index[0]]);
			}
		}
	}

	field1 = file.open("scalar");
	array.reset();
	array.shape(field1.shape()); array.allocate();
	field1.get_attr("units",unit);
	CPPUNIT_ASSERT_NO_THROW(field1.get(array));
	index.rank(1);
	for(index[0] = 0; index[0] < array.shape().dim(0);index[0]++){
		CPPUNIT_ASSERT(array(index) == testdata[index[0]]);
	}


	//check some exceptions
	Shape shape(field1.shape());
	shape.dim(0,shape[0]+1);
	array.reset(); array.shape(shape); array.allocate();
	CPPUNIT_ASSERT_THROW(field1.get(array),ShapeMissmatchError);

}

//-----------------------------------------------------------------------------
void NXNumericFieldTest::testSet(){
	std::cout<<"NXNumericFieldTest::testSet()---------------------------------";
	std::cout<<std::endl;

	//need to create a field
	NXNumericField field = file.create_numericfield("data",TypeID::FLOAT32,"m","testing data");

	Shape shape = field.shape();
	shape.dim(0,10);
	Float64Array array(shape);
	array.unit("m");
	for(size_t i=0;i<shape.dim(0);i++){
		array[i] = i;
	}

	CPPUNIT_ASSERT_NO_THROW(field.set(2,array));
	CPPUNIT_ASSERT(field.shape().dim(0)==12);

	Float32Scalar scalar("data","m","testing data");
	scalar = 10;
	CPPUNIT_ASSERT_NO_THROW(field.set(1,scalar));
	CPPUNIT_ASSERT_NO_THROW(field.set(20,scalar));

	//writing array data
	shape.rank(3);
	shape.dim(0,10);
	shape.dim(1,nx);
	shape.dim(2,ny);
	array.reset(); array.shape(shape); array.allocate();
	Float32Array farray(fshape,"detector","cps","a detector");
	array.unit(farray.unit());

	CPPUNIT_ASSERT_NO_THROW(field = file.create_numericfield(farray));
	for(size_t i=0;i<4;i++){
		farray = i;
		CPPUNIT_ASSERT_NO_THROW(field.set(i,farray));
	}

	array = 10;
	CPPUNIT_ASSERT_NO_THROW(field.set(5,array));



}
