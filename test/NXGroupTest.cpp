/*
 * NXGroupTest.cpp
 *
 *  Created on: Aug 4, 2011
 *      Author: eugen
 */

#include "NXGroupTest.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include "nx.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NXGroupTest);

void NXGroupTest::setUp(){
	_fname = "test.1.h5";

	_f.setFileName(_fname);
	_f.setOverwrite();
	_f.create();


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

void NXGroupTest::tearDown(){
	_f.close();
	//after finishing the tests we need to remove all created files
	path path1(_fname);

	if(exists(path1)) remove_all(path1);
}

void NXGroupTest::testCreation(){
	NXGroup g;

	g = *_f.createGroup("/hello/world");
	g = *_f.createGroup("/directory_1");


	g.close();
}

void NXGroupTest::testOpen(){

}

void NXGroupTest::testAttributes(){
	NXGroup g;

	g = *_f.createGroup("/Hello/world1");

	//write attribute data
	g.setAttribute("StringAttribute",_write_str_attr);
	g.setAttribute("FloatScalarAttribute",_write_scalar_attr);
	g.setAttribute("IndexOfRefraction",_write_cmplx_scalar);
	g.setAttribute("ArrayAttribute",_write_array_attr);


	//read data
	g.getAttribute("StringAttribute",_read_str_attr);
	g.getAttribute("FloatScalarAttribute",_read_scalar_attr);
	g.getAttribute("ArrayAttribute",_read_array_attr);
	g.getAttribute("IndexOfRefraction",_read_cmplx_scalar);

	//check if values are the same
	CPPUNIT_ASSERT(_write_str_attr == _read_str_attr);
	CPPUNIT_ASSERT(_read_scalar_attr == _read_scalar_attr);
	CPPUNIT_ASSERT(_read_array_attr == _write_array_attr);
	CPPUNIT_ASSERT(_write_cmplx_scalar == _read_cmplx_scalar);
}

void NXGroupTest::testAttributeExceptions(){
	NXGroup g;

	g = *_f.createGroup("/hello/world");

	//write attribute data
	g.setAttribute("StringAttribute",_write_str_attr);
	g.setAttribute("FloatScalarAttribute",_write_scalar_attr);
	g.setAttribute("IndexOfRefraction",_write_cmplx_scalar);
	g.setAttribute("ArrayAttribute",_write_array_attr);

	//trying to overwrite attributes
	CPPUNIT_ASSERT_THROW(g.setAttribute("StringAttribute",_write_str_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(g.setAttribute("FloatScalarAttribute",_write_scalar_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(g.setAttribute("IndexOfRefraction",_write_cmplx_scalar),H5AttributeError);
	CPPUNIT_ASSERT_THROW(g.setAttribute("ArrayAttribute",_write_array_attr),H5AttributeError);

	//trying to read attributes that do not exist
	CPPUNIT_ASSERT_THROW(g.getAttribute("StringAttribute_not",_read_str_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(g.getAttribute("FloatScalarAttribute_not",_read_scalar_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(g.getAttribute("ArrayAttribute_not",_read_array_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(g.getAttribute("IndexOfRefraction_not",_read_cmplx_scalar),H5AttributeError);

	g.close();
}

