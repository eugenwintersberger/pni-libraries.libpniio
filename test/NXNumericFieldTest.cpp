/*
 * NXNumericFieldTest.cpp
 *
 *  Created on: Dec 3, 2011
 *      Author: eugen
 */

#include "NXNumericFieldTest.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include "NX.hpp"
#include "NXExceptions.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NXNumericFieldTest);

//------------------------------------------------------------------------------
void NXNumericFieldTest::setUp(){
	file.setFileName("NXNumericFieldTest.h5");
	file.setOverwrite(true);
	file.setReadOnly(false);
	file.create();

	for(UInt64 i=0;i<n;i++) testdata[i] = i+1;
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

	CPPUNIT_ASSERT_NO_THROW(field = file.createNumericField("test1",
							PNITypeID::UINT16,"cps","scalar counter"));
	CPPUNIT_ASSERT(field.isOpen());

	ArrayShape shape(2);
	shape.setDimension(0,100);
	shape.setDimension(1,123);

	CPPUNIT_ASSERT_NO_THROW(field = file.createNumericField("test2",
							PNITypeID::FLOAT32,shape,"cps","array detector"));
	CPPUNIT_ASSERT(field.isOpen());

	Float32Scalar scalar("scalar","m","a scalar");
	Complex128Array array(shape,"array","nm","AFM image");

	CPPUNIT_ASSERT_NO_THROW(field = file.createNumericField(scalar));
	CPPUNIT_ASSERT(field.isOpen());
	CPPUNIT_ASSERT_NO_THROW(field = file.createNumericField(array));
	CPPUNIT_ASSERT(field.isOpen());

	//check copy construction
	NXNumericField field2(field);
	CPPUNIT_ASSERT(field2.isOpen());
	CPPUNIT_ASSERT(field.isOpen());

	//check move construction
	NXNumericField field3 = std::move(field);
	CPPUNIT_ASSERT(field3.isOpen());
	CPPUNIT_ASSERT(!field.isOpen());

}

//------------------------------------------------------------------------------
void NXNumericFieldTest::testAssignment(){
	std::cout<<"NXNumericFieldTest::testAssignment()--------------------------";
	std::cout<<std::endl;

	NXNumericField field = file.createNumericField("test1",PNITypeID::UINT16,
							"cps","scalar field");
	CPPUNIT_ASSERT(field.isOpen());

	NXNumericField field2;

	//testing copy assignment
	CPPUNIT_ASSERT_NO_THROW(field2 = field);
	CPPUNIT_ASSERT(field2.isOpen());
	CPPUNIT_ASSERT(field.isOpen());

	//move assignment
	NXNumericField field3;
	CPPUNIT_ASSERT_NO_THROW(field3 = std::move(field));
	CPPUNIT_ASSERT(field3.isOpen());
	CPPUNIT_ASSERT(!field.isOpen());
}

//------------------------------------------------------------------------------
void NXNumericFieldTest::testAppend(){
	std::cout<<"NXNumericFieldTest::testAppend()------------------------------";
	std::cout<<std::endl;

	ArrayShape shape(2);
	shape.setDimension(0,nx);
	shape.setDimension(1,ny);
	Float32Array earray(shape,"detector","cps","an area detector");

	NXNumericField field1 = file.createNumericField(earray);
	//append single elements
	for(UInt32 i=0;i<4;i++){
		earray = testdata[i];
		field1.append(earray);
	}

	//append an entire block
	ArrayShape tshape(3);
	tshape.setDimension(0,6);
	tshape.setDimension(1,nx);
	tshape.setDimension(2,ny);
	Float32Array tarray(tshape,"detector","a.u","a data block");
	CPPUNIT_ASSERT_THROW(field1.append(tarray),pni::nx::NXFieldError);
	tarray.setUnit("cps");
	Index index(3);
	for(index[0]=0;index[0]>6;index[0]++){
		for(index[1]=0;index[1]<nx;index[1]++){
			for(index[2]=0;index[2]<ny;index[2]++){
				tarray(index) = testdata[index[0]+6];
			}
		}
	}
	CPPUNIT_ASSERT_NO_THROW(field1.append(tarray));

	//check for scalar numeric field
	UInt16Scalar scalar("scalar","cps","a scalar counter");
	field1 = file.createNumericField(scalar);
	for(UInt32 i=0; i<5;i++){
		scalar = testdata[i];
		field1.append(scalar);
	}

	//append a complete array
	ArrayShape sshape(1);
	sshape.setDimension(0,5);
	UInt16Array sarray(sshape,scalar.getName(),scalar.getUnit(),scalar.getDescription());
	for(UInt64 i=0;i<sshape.getSize();i++) sarray[i] = testdata[i+5];
	CPPUNIT_ASSERT_NO_THROW(field1.append(sarray));

}

//------------------------------------------------------------------------------
void NXNumericFieldTest::testGetIndividual(){

}

//------------------------------------------------------------------------------
void NXNumericFieldTest::testGetAll(){
	std::cout<<"NXNumericFieldTest::testGetAll()------------------------------";
	std::cout<<std::endl;

	//write data
	testAppend();

	Float32Array array;
	UInt32Array scalar;

	NXNumericField field1;




}
