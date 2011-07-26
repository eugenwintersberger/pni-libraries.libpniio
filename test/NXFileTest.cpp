//implementation of the arrayshape test

#include<cppunit/extensions/HelperMacros.h>

#include "nx.hpp"
#include "NXFileTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NXFileTest);

void NXFileTest::setUp(){
	_fname1 = "test.1.h5";
	_fname2 = "test.2.h5";
}

void NXFileTest::tearDown(){
	//after finishing the tests we need to remove all created files
	path path1(_fname1);
	path path2(_fname2);

	if(exists(path1)) remove_all(path1);
	if(exists(path2)) remove_all(path2);
}

void NXFileTest::testCreation(){
	NXFile f;

	//initially create the file
	f.setFileName(_fname1);
	f.create();
	f.close();

	//recreating the file should cause an error
	CPPUNIT_ASSERT_THROW(f.create(),H5FileException); //here we except an error

	//now if we set overwrite
	f.setOverwrite();
	//everything should work fine
	CPPUNIT_ASSERT_NO_THROW(f.create());

	f.close();

}

void NXFileTest::testOpen(){
	NXFile f;

	f.setFileName(_fname1);
	f.setOverwrite();
	f.create();
	f.close();

	CPPUNIT_ASSERT_NO_THROW(f.open());

	f.close();

	//try to open a file which does not exist
	f.setFileName(_fname2);
	CPPUNIT_ASSERT_THROW(f.open(),H5FileException);

}


