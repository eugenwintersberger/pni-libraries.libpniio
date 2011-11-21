/*
 * NXrootTest.cpp
 *
 *  Created on: Sep 23, 2011
 *      Author: eugen
 */

#include<cppunit/extensions/HelperMacros.h>
#include<pni/utils/PNITypes.hpp>

#include "NXrootTest.hpp"
#include "../../src/base_classes/BaseClassExceptions.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;

CPPUNIT_TEST_SUITE_REGISTRATION(NXrootTest);


void NXrootTest::setUp(){

}

void NXrootTest::tearDown(){


}

void NXrootTest::testCreation(){
	NXroot f;

	CPPUNIT_ASSERT_NO_THROW(f.setFileName("NXroot.h5"));
	CPPUNIT_ASSERT_NO_THROW(f.setOverwrite(true));
	CPPUNIT_ASSERT_NO_THROW(f.create());
	CPPUNIT_ASSERT_NO_THROW(f.setOverwrite(false));
	CPPUNIT_ASSERT_NO_THROW(f.close());
	CPPUNIT_ASSERT_THROW(f.create(),pni::nx::NXrootError);

	CPPUNIT_ASSERT_NO_THROW(f.setOverwrite(true));
	CPPUNIT_ASSERT_NO_THROW(f.create());
	CPPUNIT_ASSERT_NO_THROW(f.close());
}

void NXrootTest::testOpen(){
	NXroot f;

	CPPUNIT_ASSERT_NO_THROW(f.setFileName("NXroot.h5"));
	CPPUNIT_ASSERT_NO_THROW(f.setOverwrite(true));
	CPPUNIT_ASSERT_NO_THROW(f.create());
	CPPUNIT_ASSERT_NO_THROW(f.close());

	CPPUNIT_ASSERT_NO_THROW(f.open());
	CPPUNIT_ASSERT_NO_THROW(f.close());
}

void NXrootTest::testAttributes(){
	NXroot f;

	//create a new file
	CPPUNIT_ASSERT_NO_THROW(f.setFileName("NXroot.h5"));
	CPPUNIT_ASSERT_NO_THROW(f.setOverwrite(true));
	CPPUNIT_ASSERT_NO_THROW(f.create());
	CPPUNIT_ASSERT_NO_THROW(f.close());

	//open the file read only
	CPPUNIT_ASSERT_NO_THROW(f.setReadOnly(true));
	CPPUNIT_ASSERT_NO_THROW(f.open());
	CPPUNIT_ASSERT(f.getFileTime() == f.getFileUpdateTime());
	CPPUNIT_ASSERT_NO_THROW(f.close());

	//open the file read/write - should change the update time
	CPPUNIT_ASSERT_NO_THROW(f.setReadOnly(false));
	//wait here some time
	CPPUNIT_ASSERT_NO_THROW(f.open());
	CPPUNIT_ASSERT_NO_THROW(f.close());

}

void NXrootTest::testEntry(){
	NXroot f;
	NXentry e;

	//create a new file
	CPPUNIT_ASSERT_NO_THROW(f.setFileName("NXroot.h5"));
	CPPUNIT_ASSERT_NO_THROW(f.setOverwrite(true));
	CPPUNIT_ASSERT_NO_THROW(f.create());

	CPPUNIT_ASSERT_NO_THROW(e = f.createEntry("scan_1"));
	CPPUNIT_ASSERT_NO_THROW(e.close());
	CPPUNIT_ASSERT_NO_THROW(e = f.openEntry("scan_1"));
	CPPUNIT_ASSERT_NO_THROW(e.close());

	NXentry e2;
	CPPUNIT_ASSERT_NO_THROW(e2 = f.createEntry("scan_2"));
	CPPUNIT_ASSERT_NO_THROW(e = f.openEntry("scan_2"));

}


