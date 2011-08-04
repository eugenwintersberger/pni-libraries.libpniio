//implementation of the arrayshape test

#include<cppunit/extensions/HelperMacros.h>

#include "nx.hpp"
#include "NXFileTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NXFileTest);

void NXFileTest::setUp(){
	_fname1 = "test.1.h5";
	_fname2 = "test.2.h5";

	_write_str_attr = "hello world";
	_write_scalar_attr = 100;
	_shape = ArrayShape();
	_shape.setRank(2);
	_shape.setDimension(0,3);
	_shape.setDimension(1,3);

	_write_array_attr = Int16Array();
	_write_array_attr.setShape(_shape);
	_write_array_attr.Allocate();
	_write_array_attr(0,0) = 1; _write_array_attr(0,1) = 2; _write_array_attr(0,2) = 3;
	_write_array_attr(1,0) = 4; _write_array_attr(1,1) = 5; _write_array_attr(1,2) = 6;
	_write_array_attr(2,0) = 7; _write_array_attr(2,1) = 8; _write_array_attr(2,2) = 9;

	_write_cmplx_scalar = Complex64(1,-2);

	_read_array_attr = Int16Array();

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
	CPPUNIT_ASSERT_THROW(f.create(),H5FileError); //here we except an error

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
	CPPUNIT_ASSERT_THROW(f.open(),H5FileError);

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

	//write attribute data
	f.setAttribute("StringAttribute",_write_str_attr);
	f.setAttribute("FloatScalarAttribute",_write_scalar_attr);
	f.setAttribute("IndexOfRefraction",_write_cmplx_scalar);
	f.setAttribute("ArrayAttribute",_write_array_attr);

	//close and reopen the file
	f.close();
	f.open();


	//read data
	f.getAttribute("StringAttribute",_read_str_attr);
	f.getAttribute("FloatScalarAttribute",_read_scalar_attr);
	f.getAttribute("ArrayAttribute",_read_array_attr);
	f.getAttribute("IndexOfRefraction",_read_cmplx_scalar);

	//check if values are the same
	CPPUNIT_ASSERT(_write_str_attr == _read_str_attr);
	CPPUNIT_ASSERT(_read_scalar_attr == _read_scalar_attr);
	CPPUNIT_ASSERT(_read_array_attr == _write_array_attr);
	CPPUNIT_ASSERT(_write_cmplx_scalar == _read_cmplx_scalar);
}

void NXFileTest::testAttributeExceptions(){
	NXFile f;

	//create a new file
	f.setFileName(_fname1);
	f.setOverwrite();
	f.create();

	//write attribute data
	f.setAttribute("StringAttribute",_write_str_attr);
	f.setAttribute("FloatScalarAttribute",_write_scalar_attr);
	f.setAttribute("IndexOfRefraction",_write_cmplx_scalar);
	f.setAttribute("ArrayAttribute",_write_array_attr);

	//trying to overwrite attributes
	CPPUNIT_ASSERT_THROW(f.setAttribute("StringAttribute",_write_str_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(f.setAttribute("FloatScalarAttribute",_write_scalar_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(f.setAttribute("IndexOfRefraction",_write_cmplx_scalar),H5AttributeError);
	CPPUNIT_ASSERT_THROW(f.setAttribute("ArrayAttribute",_write_array_attr),H5AttributeError);

	//trying to read attributes that do not exist
	CPPUNIT_ASSERT_THROW(f.getAttribute("StringAttribute_not",_read_str_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(f.getAttribute("FloatScalarAttribute_not",_read_scalar_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(f.getAttribute("ArrayAttribute_not",_read_array_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(f.getAttribute("IndexOfRefraction_not",_read_cmplx_scalar),H5AttributeError);

	f.close();
}


