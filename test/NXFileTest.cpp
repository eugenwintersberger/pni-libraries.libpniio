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

	f.create();
	f.close();
	CPPUNIT_ASSERT_NO_THROW(f.open());

}

void NXFileTest::testAttributes(){
	NXFile f;

	//create a new file
	f.setFileName(_fname1);
	f.setOverwrite();
	f.create();

	//create attribute data
	String write_str_attr = "hello world";
	Float64Scalar write_scalar_attr = 100;
	ArrayShape shape;
	Int16Array write_array_attr;
	Complex64Scalar write_cmplx_scalar = Complex64(1,-2);

	shape.setRank(2);
	shape.setDimension(0,3);
	shape.setDimension(1,3);
	write_array_attr.setShape(shape);
	write_array_attr.Allocate();
	write_array_attr(0,0) = 1; write_array_attr(0,1) = 2; write_array_attr(0,2) = 3;
	write_array_attr(1,0) = 4; write_array_attr(1,1) = 5; write_array_attr(1,2) = 6;
	write_array_attr(2,0) = 7; write_array_attr(2,1) = 8; write_array_attr(2,2) = 9;

	//write attribute data
	f.setAttribute("StringAttribute",write_str_attr);
	f.setAttribute("FloatScalarAttribute",write_scalar_attr);
	f.setAttribute("IndexOfRefraction",write_cmplx_scalar);
	f.setAttribute("ArrayAttribute",write_array_attr);

	//close and reopen the file
	f.close();
	f.open();

	//creat attributes to read data to
	String read_str_attr;
	Float64Scalar read_scalar_attr;
	Int16Array read_array_attr;
	Complex64Scalar read_cmplx_scalar;

	//read data
	f.getAttribute("StringAttribute",read_str_attr);
	f.getAttribute("FloatScalarAttribute",read_scalar_attr);
	f.getAttribute("ArrayAttribute",read_array_attr);
	f.getAttribute("IndexOfRefraction",read_cmplx_scalar);

	//check if values are the same
	CPPUNIT_ASSERT(write_str_attr == read_str_attr);
	CPPUNIT_ASSERT(read_scalar_attr == read_scalar_attr);
	CPPUNIT_ASSERT(read_array_attr == write_array_attr);
	CPPUNIT_ASSERT(write_cmplx_scalar == read_cmplx_scalar);
}

void NXFileTest::testAttributeExceptions(){

}


