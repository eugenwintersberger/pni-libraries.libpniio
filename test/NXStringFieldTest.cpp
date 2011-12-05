/*
 * NXStringFieldTest.cpp
 *
 *  Created on: Dec 5, 2011
 *      Author: Eugen Wintersberger
 */

#include "NXStringFieldTest.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include "NX.hpp"
#include "NXExceptions.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NXStringFieldTest);

//------------------------------------------------------------------------------
void NXStringFieldTest::setUp(){
	file.setFileName("NXStringFieldTest.h5");
	file.setOverwrite(true);
	file.setReadOnly(false);
	file.create();

	strdata.push_back(String("Hello"));
	strdata.push_back(String("this is a test"));
	strdata.push_back(String("a stupid text"));
}

//------------------------------------------------------------------------------
void NXStringFieldTest::tearDown(){
	file.close();
	strdata.clear();
}

//------------------------------------------------------------------------------
void NXStringFieldTest::testCreation(){
	std::cout<<"NXStringFieldTest::testCreation()-----------------------------";
	std::cout<<std::endl;

	NXStringField field;  //default constructor

	//standard construction
	NXStringField f2 = file.createStringField("text");
	CPPUNIT_ASSERT(f2.isOpen());

	//copy construction
	NXStringField f3(f2);
	CPPUNIT_ASSERT(f2.isOpen());
	CPPUNIT_ASSERT(f3.isOpen());

	//move construction
	NXStringField f4 = std::move(f2);
	CPPUNIT_ASSERT(f4.isOpen());
	CPPUNIT_ASSERT(!f2.isOpen());
}

//------------------------------------------------------------------------------
void NXStringFieldTest::testOpen(){
	std::cout<<"NXStringFieldTest::testOpen()---------------------------------";
	std::cout<<std::endl;

	file.createStringField("text1");
	file.createStringField("text2");

	NXStringField f1 = file.open("text1");
	f1 = file.open("text2");

	file.createNumericField("data",PNITypeID::UINT32,"cps","numeric test data");
	CPPUNIT_ASSERT_THROW(f1 = std::move(file.open("data")),pni::nx::NXFieldError);
}

//------------------------------------------------------------------------------
void NXStringFieldTest::testAssignment(){
	std::cout<<"NXStringFieldTest::testAssignment()---------------------------";
	std::cout<<std::endl;

	NXStringField f;
	CPPUNIT_ASSERT_NO_THROW(f = file.createStringField("text1"));
	CPPUNIT_ASSERT(f.isOpen());

	NXStringField f2;
	CPPUNIT_ASSERT_NO_THROW(f2 = f);
	CPPUNIT_ASSERT(f2.isOpen());
	CPPUNIT_ASSERT(f.isOpen());

	NXStringField f3;
	CPPUNIT_ASSERT_NO_THROW(f3 = std::move(f));
	CPPUNIT_ASSERT(f3.isOpen());
	CPPUNIT_ASSERT(!f.isOpen());
}

//------------------------------------------------------------------------------
void NXStringFieldTest::testAppend(){
	std::cout<<"NXStringFieldTest::testAppend()-------------------------------";
	std::cout<<std::endl;

	NXStringField field = file.createStringField("text");
	for(String &s: strdata ){
		CPPUNIT_ASSERT_NO_THROW(field.append(s));
	}


}


//------------------------------------------------------------------------------
void NXStringFieldTest::testGetIndividual(){
	std::cout<<"NXStringFieldTest::testGetIndividual()------------------------";
	std::cout<<std::endl;

	testAppend();
	NXStringField field = file.open("text");

	for(UInt64 i=0;i<strdata.size();i++){
		String s = field.get(i);
	}
}

//------------------------------------------------------------------------------
void NXStringFieldTest::testGetAll(){
	std::cout<<"NXStringFieldTest::testGetAll()-------------------------------";
	std::cout<<std::endl;
	NXStringField write = file.createStringField("text");

	char sep = '\n';
	String total;
	for(String &s: strdata){
		total += s+sep;
		write.append(s);
	}
	std::cout<<total<<std::endl;


	NXStringField read = file.open("text");
	std::cout<<"start with reading"<<std::endl;
	String text;
	text = read.get(sep);
	CPPUNIT_ASSERT(total == text);

}
