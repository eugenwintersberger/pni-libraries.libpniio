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

#define NX 128
#define NY 256

void NXFieldTest::setUp(){
	_fname = "test.field.h5";
	Index i;
	_f.setFileName(_fname);
	_f.setOverwrite(true);
	_f.create();


	_write_str_attr = "hello world";
	_write_scalar_attr = 100;
	_shape = ArrayShape();
	_shape.setRank(2);
	_shape.setDimension(0,3);
	_shape.setDimension(1,3);

	_write_array_attr = Int16Array();
	i.setRank(_shape.getRank());
	_write_array_attr.setShape(_shape);
	_write_array_attr.allocate();
	i[0] = 0; i[1] = 0; _write_array_attr(i) = 1;
	i[0] = 0; i[1] = 1; _write_array_attr(i) = 2;
	i[0] = 0; i[1] = 2; _write_array_attr(i) = 3;
	i[0] = 1; i[1] = 0; _write_array_attr(i) = 4;
	i[0] = 1; i[1] = 1; _write_array_attr(i) = 5;
	i[0] = 1; i[1] = 2; _write_array_attr(i) = 6;
	i[0] = 2; i[1] = 0; _write_array_attr(i) = 7;
	i[0] = 2; i[1] = 1; _write_array_attr(i) = 8;
	i[0] = 2; i[1] = 2; _write_array_attr(i) = 9;

	_write_cmplx_scalar = Complex64(1,-2);
	_write_cmplx_scalar.setName("write_complx_scalar");
	_write_cmplx_scalar.setUnit("a.u.");
	_write_cmplx_scalar.setDescription("a stupid write buffer");

	_read_array_attr = Int16Array();

	_data_shape = ArrayShape();
	_data_shape.setRank(2);
	_data_shape.setDimension(0,NX);
	_data_shape.setDimension(1,NY);

	_f64_data_array_write = Float64Array();
	_f64_data_array_write.setShape(_data_shape);
	_f64_data_array_write.allocate();
	_f64_data_array_write.setName("write_data_array");
	_f64_data_array_write.setDescription("a stupid write buffer");
	_f64_data_array_write.setUnit("a.u.");
}

void NXFieldTest::tearDown(){
	_f.close();
}

void NXFieldTest::testCreation(){
	std::cerr<<"NXFieldTest::testCreation ---------------------------------------"<<std::endl;
	NXGroup g = _f.createGroup("data");
	NXField dset;
	ArrayShape dshape(2);
	dshape.setDimension(0,NX);
	dshape.setDimension(1,NY);
	_f64_data_array_read = Float64Array(_data_shape);
	_f64_data_array_read.allocate();
	_f64_data_array_read.setName("array");
	_f64_data_array_read.setUnit("a.u.");
	_f64_data_array_read.setDescription("a read buffer");

	//creating data fields for saving arrays
	//_f.createField("field_1",FLOAT64,2,dims);
	CPPUNIT_ASSERT_NO_THROW(dset = _f.createNumericField("field_1",PNITypeID::FLOAT64,dshape,"a.u.","data"));
	CPPUNIT_ASSERT_NO_THROW(dset = _f.createNumericField("field_2",PNITypeID::COMPLEX128,_data_shape,"a.u","data"));
	CPPUNIT_ASSERT_NO_THROW(dset = _f.createNumericField(_f64_data_array_read));

	//creating data fields for saving scalars
	CPPUNIT_ASSERT_NO_THROW(dset = _f.createNumericField("field_4",PNITypeID::COMPLEX64,"a.u.","data"));
	CPPUNIT_ASSERT_NO_THROW(dset = _f.createNumericField(_write_cmplx_scalar));

	//creating data fields for saving strings
	String str = "hello world!";
	dset = _f.createStringField("field_6");


	//try now everything with a group as a generating object

	//creating data fields for saving arrays
	dset = g.createNumericField("field_1",PNITypeID::FLOAT64,dshape,"a.u.","data");
	dset = g.createNumericField("field_2",PNITypeID::COMPLEX128,_data_shape,"a.u.","data");
	dset = g.createNumericField(_f64_data_array_read);

	//creating data fields for saving scalars
	dset = g.createNumericField("field_4",PNITypeID::COMPLEX64,"a.u.","data");
	dset = g.createNumericField(_write_cmplx_scalar);

	//creating data fields for saving strings
	dset = g.createStringField("field_6");
	//CPPUNIT_ASSERT_THROW(g.createField("subdir/field_1",str),H5DataSetError);


	g.close();
}

void NXFieldTest::testOpen(){
	std::cerr<<"NXFieldTest::testOpen ---------------------------------------"<<std::endl;
	NXField dset;
	NXGroup g;

	_f.createNumericField("field",PNITypeID::COMPLEX128,_data_shape,"a.u.","data buffer");
	_f.createGroup("data");
	CPPUNIT_ASSERT_NO_THROW(_f.openField("field"));
	CPPUNIT_ASSERT_NO_THROW(_f.createNumericField("data/field_2",PNITypeID::FLOAT32,_data_shape,"a.u.","data"));
	CPPUNIT_ASSERT_NO_THROW(_f.openField("/data/field_2"));

}

void NXFieldTest::testInsertData(){

}

void NXFieldTest::testInsertDataExceptions(){

}

void NXFieldTest::testGetData(){
	NXField dset;
	ArrayShape dshape(2);
	dshape.setDimension(0,NX);
	dshape.setDimension(1,NY);

	//write data to disk
	testAppendData();

	//read data
	CPPUNIT_ASSERT_NO_THROW(dset = _f.openField("field_1"));
	for(UInt64 i=0;i<dset.getDimension(0);i++){
		Float64 value;
		switch(i){
		case 0: value = 1.2; break;
		case 1: value = 1.3; break;
		case 2: value = 1.4; break;
		default:
			value = 0.; break;
		}
		CPPUNIT_ASSERT_NO_THROW(dset.get(i,_f64_data_array_write));
		for(UInt64 i=0;i<_f64_data_array_write.getShape().getSize();i++){
				CPPUNIT_ASSERT(_f64_data_array_write[i] == value);
		}
	}

	//read data from complex scalar
	CPPUNIT_ASSERT_NO_THROW(dset = _f.openField(_write_cmplx_scalar.getName()));
	for(UInt64 i=0;i<dset.getDimension(0);i++){
		Complex64 value;
		switch(i){
		case 0: value = Complex64(1,2); break;
		case 1: value = Complex64(3,4); break;
		case 2: value = Complex64(5,6); break;
		case 3: value = Complex64(7,8); break;
		default:
			value = Complex64(0,0); break;
		}
		CPPUNIT_ASSERT_NO_THROW(dset.get(i,_write_cmplx_scalar));
		std::cout<<i<<" : "<<_write_cmplx_scalar<<std::endl;
		CPPUNIT_ASSERT(_write_cmplx_scalar == value);
	}

	//read string data - this is important
	CPPUNIT_ASSERT_NO_THROW(dset = _f.openField("field_5"));
	String s;
	CPPUNIT_ASSERT_NO_THROW(dset.get(0,s));
	CPPUNIT_ASSERT(s == "hello world this is a text");
	CPPUNIT_ASSERT_NO_THROW(dset.get(1,s));
	CPPUNIT_ASSERT(s == "another text");

}

void NXFieldTest::testGetDataExceptions(){

}



void NXFieldTest::testAppendData(){
	std::cerr<<"NXFieldTest::testAppendData ---------------------------------------"<<std::endl;
	NXField dset;
	ArrayShape dshape(2);
	dshape.setDimension(0,NX);
	dshape.setDimension(1,NY);

	_f64_data_array_write = 1.2;
	//creating data fields for saving arrays
	CPPUNIT_ASSERT_NO_THROW(dset = _f.createNumericField("field_1",PNITypeID::FLOAT64,_data_shape,"a.z.","data"));
	CPPUNIT_ASSERT_NO_THROW(dset.append(_f64_data_array_write));
	_f64_data_array_write = 1.3;
	CPPUNIT_ASSERT_NO_THROW(dset.append(_f64_data_array_write));
	_f64_data_array_write = 1.4;
	CPPUNIT_ASSERT_NO_THROW(dset.append(_f64_data_array_write));

	CPPUNIT_ASSERT_NO_THROW(dset = _f.createNumericField("field_2",PNITypeID::FLOAT64,_data_shape,"a.u.","data"));
	_f64_data_array_write = 2.234e-12;
	CPPUNIT_ASSERT_NO_THROW(dset.append(_f64_data_array_write));

	CPPUNIT_ASSERT_NO_THROW(dset = _f.createNumericField(_f64_data_array_write));
	_f64_data_array_write = 2.451e+12;
	CPPUNIT_ASSERT_NO_THROW(dset.append(_f64_data_array_write));

	//writing scalar data
	CPPUNIT_ASSERT_NO_THROW(dset = _f.createNumericField(_write_cmplx_scalar));
	_write_cmplx_scalar = Complex64(1,2);
	CPPUNIT_ASSERT_NO_THROW(dset.append(_write_cmplx_scalar));
	_write_cmplx_scalar = Complex64(3,4);
	CPPUNIT_ASSERT_NO_THROW(dset.append(_write_cmplx_scalar));
	_write_cmplx_scalar = Complex64(5,6);
	CPPUNIT_ASSERT_NO_THROW(dset.append(_write_cmplx_scalar));

	//write string data
	String s = "hello world this is a text";
	CPPUNIT_ASSERT_NO_THROW(dset = _f.createStringField("field_5"));
	CPPUNIT_ASSERT_NO_THROW(dset.append(s));
	s = "another text";
	CPPUNIT_ASSERT_NO_THROW(dset.append(s));

	CPPUNIT_ASSERT_NO_THROW(dset = _f.openField(_write_cmplx_scalar.getName()));
	_write_cmplx_scalar = Complex64(7,8);
	CPPUNIT_ASSERT_NO_THROW(dset.append(_write_cmplx_scalar));
}

void NXFieldTest::testAppendDataExceptions(){
	std::cerr<<"NXFieldTest::testWriteDataExceptions ---------------------------------------"<<std::endl;
	NXField dset;
	ArrayShape shape(2);
	shape.setDimension(0,NX);
	shape.setDimension(1,NY-1);
	String s = "hello world this is a text";

	_f64_data_array_write = 1.2;
	//-------------------testing exceptions for array data---------------------
	//creating data fields for saving arrays
	dset = _f.createNumericField("field_1",PNITypeID::INT64,shape,"a.u.","data");
	CPPUNIT_ASSERT_THROW(dset.append(_f64_data_array_write),ShapeMissmatchError);

	dset = _f.createNumericField("field_2",PNITypeID::FLOAT64,shape,"a.u.","data");
	CPPUNIT_ASSERT_THROW(dset.append(_f64_data_array_write),ShapeMissmatchError);
	CPPUNIT_ASSERT_THROW(dset.append(s),pni::nx::NXFieldError);
	CPPUNIT_ASSERT_THROW(dset.append(_write_cmplx_scalar),pni::nx::NXFieldError);
	CPPUNIT_ASSERT_THROW(dset.append(s),pni::nx::NXFieldError);


	//------------------testing exceptions for scalar data---------------------
	dset = _f.createNumericField("field_3",PNITypeID::FLOAT64,"a.u.","data");
	CPPUNIT_ASSERT_THROW(dset.append(_write_cmplx_scalar),pni::nx::NXFieldError);
	CPPUNIT_ASSERT_THROW(dset.append(_f64_data_array_write),ShapeMissmatchError);
	CPPUNIT_ASSERT_THROW(dset.append(s),pni::nx::NXFieldError);

	//-------------------testing exceptions for string data--------------------
	dset = _f.createStringField("field_4");
	CPPUNIT_ASSERT_THROW(dset.append(_write_cmplx_scalar),pni::nx::NXFieldError);
	CPPUNIT_ASSERT_THROW(dset.append(_f64_data_array_write),ShapeMissmatchError);

}

void NXFieldTest::testStreamIO(){
	NXField dset;
	Float64 data[4]={0.1,0.45,-1.234,110.342};
	Float64Scalar scalar("scalar","m","a testing scalar");
	String sdata[5]={"Hello world","this is a stupid text","where each line",
			         "has a different","length"};

	//----------------write data via streams------------------------------------
	CPPUNIT_ASSERT_NO_THROW(dset = _f.createNumericField(_f64_data_array_write));
	for(UInt64 i=0;i<4;i++){
		_f64_data_array_write = data[i];
		CPPUNIT_ASSERT_NO_THROW(dset<<_f64_data_array_write);
	}

	CPPUNIT_ASSERT_NO_THROW(dset=_f.createNumericField(scalar));
	for(UInt64 i=0;i<4;i++){
		scalar = data[i];
		CPPUNIT_ASSERT_NO_THROW(dset<<scalar);
	}

	CPPUNIT_ASSERT_NO_THROW(dset = _f.createStringField("log"));
	for(UInt64 i=0;i<5;i++) CPPUNIT_ASSERT_NO_THROW(dset<<sdata[i]);

	//-----------read data via streams------------------------------------------
	dset = _f.openField(_f64_data_array_write.getName());
	for(UInt64 i=0;i<4;i++){
		CPPUNIT_ASSERT_NO_THROW(dset>>_f64_data_array_write);
		for(UInt64 j=0;j<_f64_data_array_write.getShape().getSize();j++) CPPUNIT_ASSERT(_f64_data_array_write[j]==data[i]);
	}

	dset = _f.openField(scalar.getName());
	for(UInt64 i=0;i<4;i++){
		CPPUNIT_ASSERT_NO_THROW(dset>>scalar);
		CPPUNIT_ASSERT(scalar == data[i]);
	}

	dset = _f.openField("log");
	String s;
	for(UInt64 i=0;i<5;i++){
		CPPUNIT_ASSERT_NO_THROW(dset>>s);
		CPPUNIT_ASSERT(s == sdata[i]);
	}

}

void NXFieldTest::testAttributes(){
	std::cerr<<"NXFieldTest::testAttributes ---------------------------------------"<<std::endl;
	NXField f;

	f = _f.createNumericField("data",PNITypeID::FLOAT64,_data_shape,"a.u.","data");

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
	std::cerr<<"NXFieldTest::testAttributeExceptions ---------------------------------------"<<std::endl;
	NXField f;

	f = _f.createNumericField("data",PNITypeID::FLOAT32,_data_shape,"a.u.","data");

	//write attribute data
	f.setAttribute("StringAttribute",_write_str_attr);
	f.setAttribute("FloatScalarAttribute",_write_scalar_attr);
	f.setAttribute("IndexOfRefraction",_write_cmplx_scalar);
	f.setAttribute("ArrayAttribute",_write_array_attr);

	//trying to overwrite attributes
	CPPUNIT_ASSERT_NO_THROW(f.setAttribute("StringAttribute",_write_str_attr));
	CPPUNIT_ASSERT_NO_THROW(f.setAttribute("FloatScalarAttribute",_write_scalar_attr));
	CPPUNIT_ASSERT_NO_THROW(f.setAttribute("IndexOfRefraction",_write_cmplx_scalar));
	CPPUNIT_ASSERT_NO_THROW(f.setAttribute("ArrayAttribute",_write_array_attr));

	//trying to read attributes that do not exist
	CPPUNIT_ASSERT_THROW(f.getAttribute("StringAttribute_not",_read_str_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(f.getAttribute("FloatScalarAttribute_not",_read_scalar_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(f.getAttribute("ArrayAttribute_not",_read_array_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(f.getAttribute("IndexOfRefraction_not",_read_cmplx_scalar),H5AttributeError);

	f.close();
}

void NXFieldTest::testLinks(){
	std::cerr<<"NXFieldTest::testLinks ---------------------------------------"<<std::endl;
	ArrayShape s(2);
	s.setDimension(0,NX);
	s.setDimension(1,NY);
	NXField f1,f2;
	NXGroup g1,g2;

	g1 = _f.createGroup("/data1");
	g2 = _f.createGroup("/data2");

	f1 = g1.createNumericField("det1",PNITypeID::UINT32,s,"a.u.","data");
	f2 = g2.createNumericField("det2",PNITypeID::FLOAT32,s,"a.u.","data");

	f1.createLink(g2,"original_data");
	f2.createLink(g1,"corrected_data");
	f1.createLink(g2);
	f2.createLink(g1);


}
