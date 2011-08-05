/*
 * NXFieldTest.cpp
 *
 *  Created on: Aug 5, 2011
 *      Author: eugen
 */

#include "NXFieldTest.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include "NX.hpp"
#include "NXExceptions.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NXFieldTest);

void NXFieldTest::setUp(){
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

	_data_shape = ArrayShape();
	_data_shape.setRank(2);
	_data_shape.setDimension(0,1024);
	_data_shape.setDimension(1,2048);

	_f64_data_array_write = Float64Array();
	_f64_data_array_write.setShape(_data_shape);
	_f64_data_array_write.Allocate();
}

void NXFieldTest::tearDown(){
	_f.close();
	//after finishing the tests we need to remove all created files
	path path1(_fname);

	if(exists(path1)) remove_all(path1);
}

void NXFieldTest::testCreation(){
	NXGroup g = *_f.createGroup("data");
	NXField dset;
	UInt32 dims[2];
	dims[0] = 1024;
	dims[1] = 2048;
	_f64_data_array_read = Float64Array(_data_shape);
	_f64_data_array_read.Allocate();

	//creating data fields for saving arrays
	dset = *_f.createField("field_1",FLOAT64,2,dims);
	dset = *_f.createField("field_2",COMPLEX128,_data_shape);
	dset = *_f.createField("field_3",_f64_data_array_read);

	//creating data fields for saving scalars
	dset = *_f.createField("field_4",COMPLEX64);
	dset = *_f.createField("field_5",_write_cmplx_scalar);

	//creating data fields for saving strings
	String str = "hello world!";
	dset = *_f.createField("field_6",str);


	//try now everything with a group as a generating object

	//creating data fields for saving arrays
	dset = *g.createField("field_1",FLOAT64,2,dims);
	dset = *g.createField("field_2",COMPLEX128,_data_shape);
	dset = *g.createField("field_3",_f64_data_array_read);

	//creating data fields for saving scalars
	dset = *g.createField("field_4",COMPLEX64);
	dset = *g.createField("field_5",_write_cmplx_scalar);

	//creating data fields for saving strings
	dset = *g.createField("field_6",str);
	CPPUNIT_ASSERT_THROW(g.createField("subdir/field_1",str),H5DataSetError);


	g.close();
}

void NXFieldTest::testOpen(){
	NXField dset;
	NXGroup g;

	_f.createField("field",COMPLEX128,_data_shape);
	_f.createGroup("data");
	dset = *_f.openField("field");
	CPPUNIT_ASSERT_NO_THROW(_f.createField("data/field_2",FLOAT32,_data_shape));
	dset = *_f.openField("/data/field_2");

}

void NXFieldTest::testWriteData(){
	NXField dset;
	UInt32 dims[2];
	dims[0] = 1024;
	dims[1] = 2048;

	_f64_data_array_write = 1.2;
	//creating data fields for saving arrays
	dset = *_f.createField("field_1",FLOAT64,2,dims);
	dset.write(_f64_data_array_write);

	dset = *_f.createField("field_2",FLOAT64,_data_shape);
	_f64_data_array_write = 2.234e-12;
	dset.write(_f64_data_array_write);

	dset = *_f.createField("field_3",_f64_data_array_write);
	_f64_data_array_write = 2.451e+12;
	dset.write(_f64_data_array_write);

	//writing scalar data
	dset = *_f.createField("field_4",_write_cmplx_scalar);
	dset.write(_write_cmplx_scalar);

	//write string data
	String s = "hello world this is a text";
	dset = *_f.createField("field_5",s);
	dset.write(s);
}

void NXFieldTest::testWriteDataExceptions(){
	NXField dset;
	UInt32 dims[2];
	dims[0] = 512;
	dims[1] = 2048;
	String s = "hello world this is a text";

	_f64_data_array_write = 1.2;
	//-------------------testing exceptions for array data---------------------
	//creating data fields for saving arrays
	dset = *_f.createField("field_1",INT64,2,dims);
	CPPUNIT_ASSERT_THROW(dset.write(_f64_data_array_write),TypeError);

	dset = *_f.createField("field_2",FLOAT64,2,dims);
	CPPUNIT_ASSERT_THROW(dset.write(_f64_data_array_write),ShapeMissmatchError);
	CPPUNIT_ASSERT_THROW(dset.write(s),pni::nx::NXFieldError);
	CPPUNIT_ASSERT_THROW(dset.write(_write_cmplx_scalar),pni::nx::NXFieldError);
	CPPUNIT_ASSERT_THROW(dset.write(s),pni::nx::NXFieldError);


	//------------------testing exceptions for scalar data---------------------
	dset = *_f.createField("field_3",FLOAT64);
	CPPUNIT_ASSERT_THROW(dset.write(_write_cmplx_scalar),TypeError);
	CPPUNIT_ASSERT_THROW(dset.write(_f64_data_array_write),pni::nx::NXFieldError);
	CPPUNIT_ASSERT_THROW(dset.write(s),pni::nx::NXFieldError);

	//-------------------testing exceptions for string data--------------------
	dset = *_f.createField("field_4",s);
	CPPUNIT_ASSERT_THROW(dset.write(_write_cmplx_scalar),pni::nx::NXFieldError);
	CPPUNIT_ASSERT_THROW(dset.write(_f64_data_array_write),pni::nx::NXFieldError);
	String s2 = "hello";
	CPPUNIT_ASSERT_THROW(dset.write(s2),SizeMissmatchError);

}

void NXFieldTest::testReadData(){
	NXField dset;
	UInt32 dims[2];
	dims[0] = 1024;
	dims[1] = 2048;
	String s;

	_f64_data_array_write = 1.2;
	//creating data fields for saving arrays
	dset = *_f.createField("field_1",FLOAT64,2,dims);
	dset.write(_f64_data_array_write);

	Float64Array reader;
	CPPUNIT_ASSERT_NO_THROW(dset.read(reader));
	Float64Array reader2(2,dims);
	CPPUNIT_ASSERT_NO_THROW(dset.read(reader2));

	//writing scalar data
	dset = *_f.createField("field_2",_write_cmplx_scalar);
	dset.write(_write_cmplx_scalar);
	Complex64Scalar scalar;
	CPPUNIT_ASSERT_NO_THROW(dset.read(scalar));

	//write string data
	s = "hello world this is a text";
	dset = *_f.createField("field_3",s);
	String s2;
	dset.write(s);
	CPPUNIT_ASSERT_NO_THROW(dset.read(s2));

}

void NXFieldTest::testReadDataExceptions(){
	NXField dset;
	UInt32 dims[2];
	dims[0] = 1024;
	dims[1] = 2048;
	String s;

	_f64_data_array_write = 1.2;
	//creating data fields for saving arrays
	dset = *_f.createField("field_1",FLOAT64,2,dims);
	dset.write(_f64_data_array_write);

	Int64Array reader;
	CPPUNIT_ASSERT_THROW(dset.read(reader),TypeError);
	CPPUNIT_ASSERT_THROW(dset.read(s),pni::nx::NXFieldError);

	//writing scalar data
	dset = *_f.createField("field_2",_write_cmplx_scalar);
	dset.write(_write_cmplx_scalar);
	Int64Scalar scalar;
	CPPUNIT_ASSERT_THROW(dset.read(scalar),TypeError);
	CPPUNIT_ASSERT_THROW(dset.read(s),pni::nx::NXFieldError);

	//write string data
	s = "hello world this is a text";
	dset = *_f.createField("field_3",s);
	dset.write(s);
	CPPUNIT_ASSERT_THROW(dset.read(_f64_data_array_write),pni::nx::NXFieldError);
}

void NXFieldTest::testAttributes(){
	NXField f;

	f = *_f.createField("data",FLOAT64,_data_shape);

	//write attribute data
	f.setAttribute("StringAttribute",_write_str_attr);
	f.setAttribute("FloatScalarAttribute",_write_scalar_attr);
	f.setAttribute("IndexOfRefraction",_write_cmplx_scalar);
	f.setAttribute("ArrayAttribute",_write_array_attr);


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

	f.close();
}

void NXFieldTest::testAttributeExceptions(){
	NXField f;

	f = *_f.createField("data",FLOAT32,_data_shape);

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
