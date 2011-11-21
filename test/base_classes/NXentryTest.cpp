/*
 * NXrootTest.cpp
 *
 *  Created on: Sep 23, 2011
 *      Author: eugen
 */

#include<cppunit/extensions/HelperMacros.h>
#include<pni/utils/PNITypes.hpp>

#include "NXentryTest.hpp"
#include "../../src/base_classes/BaseClassExceptions.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;

CPPUNIT_TEST_SUITE_REGISTRATION(NXentryTest);

#define TESTSTRING "hello world"

void NXentryTest::setUp(){
	CPPUNIT_ASSERT_NO_THROW(f.setFileName("NXentry.h5"));
	CPPUNIT_ASSERT_NO_THROW(f.setOverwrite(true));
	CPPUNIT_ASSERT_NO_THROW(f.create());
}

void NXentryTest::tearDown(){
	CPPUNIT_ASSERT_NO_THROW(f.close());
}

void NXentryTest::testCreation(){
	NXentry e;

	CPPUNIT_ASSERT_NO_THROW(e = f.createEntry("scan_1"));
	CPPUNIT_ASSERT_NO_THROW(e = f.createEntry("scan_2"));
	CPPUNIT_ASSERT_NO_THROW(e = f.openEntry("scan_1"));
	CPPUNIT_ASSERT_THROW(e=f.createEntry("scan_1"),pni::nx::NXrootError);
}

void NXentryTest::testStringFields(){
	NXentry e;
	String s;

	CPPUNIT_ASSERT_NO_THROW(e = f.createEntry("scan_1"));
	CPPUNIT_ASSERT_NO_THROW(e.title().write(TESTSTRING));
	CPPUNIT_ASSERT_NO_THROW(e.title().read(s));
	std::cout<<"STRING VALUE "<<s<<std::endl;
	CPPUNIT_ASSERT(s == TESTSTRING);

	CPPUNIT_ASSERT_NO_THROW(e.experiment_identifier().write(TESTSTRING));
	CPPUNIT_ASSERT_NO_THROW(e.experiment_identifier().read(s));
	CPPUNIT_ASSERT(s == TESTSTRING);

	CPPUNIT_ASSERT_NO_THROW(e.experiment_description().write(TESTSTRING));
	CPPUNIT_ASSERT_NO_THROW(e.experiment_description().read(s));
	CPPUNIT_ASSERT(s == TESTSTRING);

	CPPUNIT_ASSERT_NO_THROW(e.collection_identifier().write(TESTSTRING));
	CPPUNIT_ASSERT_NO_THROW(e.collection_identifier().read(s));
	CPPUNIT_ASSERT(s == TESTSTRING);

	CPPUNIT_ASSERT_NO_THROW(e.collection_description().write(TESTSTRING));
	CPPUNIT_ASSERT_NO_THROW(e.collection_description().read(s));
	CPPUNIT_ASSERT(s == TESTSTRING);

	CPPUNIT_ASSERT_NO_THROW(e.entry_identifier().write(TESTSTRING));
	CPPUNIT_ASSERT_NO_THROW(e.entry_identifier().read(s));
	CPPUNIT_ASSERT(s == TESTSTRING);

	CPPUNIT_ASSERT_NO_THROW(e.definition(TESTSTRING,TESTSTRING).write(TESTSTRING));
	CPPUNIT_ASSERT_NO_THROW(e.definition().read(s));
	CPPUNIT_ASSERT(s == TESTSTRING);
	CPPUNIT_ASSERT_NO_THROW(e.definition().getAttribute("version",s));
	CPPUNIT_ASSERT(s == TESTSTRING);
	CPPUNIT_ASSERT_NO_THROW(e.definition().getAttribute("url",s));
	CPPUNIT_ASSERT(s == TESTSTRING);

	CPPUNIT_ASSERT_NO_THROW(e.definition_local(TESTSTRING,TESTSTRING,TESTSTRING));
	CPPUNIT_ASSERT(e.definition_local() == TESTSTRING);
	CPPUNIT_ASSERT(e.definition_local_version() == TESTSTRING);
	CPPUNIT_ASSERT(e.definition_local_url() == TESTSTRING);

	CPPUNIT_ASSERT_NO_THROW(e.start_time(TESTSTRING));
	CPPUNIT_ASSERT(e.start_time() == TESTSTRING);

	CPPUNIT_ASSERT_NO_THROW(e.end_time(TESTSTRING));
	CPPUNIT_ASSERT(e.end_time() == TESTSTRING);

	CPPUNIT_ASSERT_NO_THROW(e.run_cycle(TESTSTRING));
	CPPUNIT_ASSERT(e.run_cycle() == TESTSTRING);

	CPPUNIT_ASSERT_NO_THROW(e.revision(TESTSTRING,TESTSTRING));
	CPPUNIT_ASSERT_NO_THROW(e.revision() == TESTSTRING);
	CPPUNIT_ASSERT_NO_THROW(e.revision_comment() == TESTSTRING);

	CPPUNIT_ASSERT_NO_THROW(e.program_name(TESTSTRING,TESTSTRING,TESTSTRING));
	CPPUNIT_ASSERT(e.program_name() == TESTSTRING);
	CPPUNIT_ASSERT(e.program_name_version() == TESTSTRING);
	CPPUNIT_ASSERT(e.program_name_configuration() == TESTSTRING);


}

void NXentryTest::testScalarFields(){
	NXentry e;
	Float32Scalar time("duration","s","scan duraction");
	Float64Scalar time2;

	CPPUNIT_ASSERT_NO_THROW(e = f.createEntry("scan_3"));

	CPPUNIT_ASSERT_NO_THROW(e.duration(time));
	CPPUNIT_ASSERT(e.duration<Float32>() == time);
	CPPUNIT_ASSERT_NO_THROW(time = e.duration<Float32>());
	CPPUNIT_ASSERT_NO_THROW(time2 = e.duration<Float64>());
	std::cout<<time2<<std::endl;
	std::cout<<time<<std::endl;

	Float32Scalar ctime(20.0,"ctime","s");
	CPPUNIT_ASSERT_NO_THROW(e.collection_time(ctime));
	CPPUNIT_ASSERT(e.collection_time<Float64>() == ctime );

	Float64Scalar fpath(100.,"flightpath","m");
	CPPUNIT_ASSERT_NO_THROW(e.pre_sample_flightpath(fpath));
	CPPUNIT_ASSERT(e.pre_sample_flightpath<Float32>() == fpath);


}

void NXentryTest::testObjectFields(){

}


