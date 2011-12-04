/*
 * NXFieldTest.cpp
 *
 *  Created on: Aug 5, 2011
 *      Author: eugen
 */


#include <map>
#include <vector>
#include "NXFieldTest.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include "NX.hpp"
#include "NXExceptions.hpp"

//CPPUNIT_TEST_SUITE_REGISTRATION(NXFieldTest);

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
	Float64Array array(dshape);
	Int64Scalar scalar("scalar","nm","a testing scalar");
	array.allocate();
	array.setName("array");
	array.setUnit("a.u.");
	array.setDescription("a read buffer");
	ArrayShape eshape(0); //element shape for scalar values
	ArrayShape sshape(1);  //array shape for scalar values (total container)
	sshape.setDimension(0,0);

	//shape of an array container after creation
	ArrayShape cshape(3);
	cshape.setDimension(0,0);
	cshape.setDimension(1,dshape.getDimension(0));
	cshape.setDimension(2,dshape.getDimension(1));


	//creating data fields for saving arrays

	//classic array construction using a constructor
	NXField f1 = _f.createNumericField(array);
	CPPUNIT_ASSERT(f1.getElementShape() == array.getShape());
	CPPUNIT_ASSERT(f1.getShape() == cshape);
	CPPUNIT_ASSERT(f1.getTypeID() == array.getTypeID());
	CPPUNIT_ASSERT(f1.isOpen());

	NXField f2 = _f.createNumericField("field_1",PNITypeID::UINT64,dshape,"a.u","data");
	CPPUNIT_ASSERT(f2.getElementShape() == dshape);
	CPPUNIT_ASSERT(f2.getShape() == cshape);
	CPPUNIT_ASSERT(f2.getTypeID() == PNITypeID::UINT64);
	CPPUNIT_ASSERT(f2.isOpen());

	//classic scalar construction
	NXField f3 = _f.createNumericField(scalar);
	CPPUNIT_ASSERT(f3.getTypeID() == PNITypeID::INT64);
	CPPUNIT_ASSERT(f3.getElementShape() == eshape);
	CPPUNIT_ASSERT(f3.getShape() == sshape);
	CPPUNIT_ASSERT(f3.isOpen());

	//classic scalar construction
	NXField f5 = _f.createNumericField("scalar_2",PNITypeID::INT32,"m","distance to something");
	CPPUNIT_ASSERT(f5.getTypeID() == PNITypeID::INT32);
	CPPUNIT_ASSERT(f5.getElementShape() == eshape);
	CPPUNIT_ASSERT(f5.getShape() == sshape);
	CPPUNIT_ASSERT(f5.isOpen());

	//create a string field
	NXField f4 = _f.createStringField("teststring");
	CPPUNIT_ASSERT(f4.getTypeID() == PNITypeID::STRING);
	CPPUNIT_ASSERT(f4.getShape() == sshape);
	CPPUNIT_ASSERT(f4.getElementShape() == eshape);
	CPPUNIT_ASSERT(f4.isOpen());

	//testing copy constructor on scalar array
	NXField f6(f5);
	CPPUNIT_ASSERT(f6.getTypeID()==f5.getTypeID());
	CPPUNIT_ASSERT(f6.getShape() == f5.getShape());
	CPPUNIT_ASSERT(f6.getElementShape() == f5.getElementShape());
	CPPUNIT_ASSERT(f6.isOpen());
	CPPUNIT_ASSERT(f5.isOpen());

	//testing copy constructor on array array
	NXField f7(f1);
	CPPUNIT_ASSERT(f7.getTypeID()==f1.getTypeID());
	CPPUNIT_ASSERT(f7.getShape() == f1.getShape());
	CPPUNIT_ASSERT(f7.getElementShape() == f1.getElementShape());
	CPPUNIT_ASSERT(f7.isOpen());
	CPPUNIT_ASSERT(f1.isOpen());

	//testing copy constructor on string array
	NXField f8(f4);
	CPPUNIT_ASSERT(f8.getTypeID()==f4.getTypeID());
	CPPUNIT_ASSERT(f8.getShape() == f4.getShape());
	CPPUNIT_ASSERT(f8.getElementShape() == f4.getElementShape());
	CPPUNIT_ASSERT(f8.isOpen());
	CPPUNIT_ASSERT(f4.isOpen());

	//testing move constructor on scalar array
	NXField f9 = std::move(f5);
	CPPUNIT_ASSERT(f9.getTypeID()==f6.getTypeID());
	CPPUNIT_ASSERT(f9.getShape() == f6.getShape());
	CPPUNIT_ASSERT(f9.getElementShape() == f6.getElementShape());
	CPPUNIT_ASSERT(f9.isOpen());
	CPPUNIT_ASSERT(!f5.isOpen());

	//testing move constructor on array array
	NXField f10 = std::move(f1);
	CPPUNIT_ASSERT(f10.getTypeID()==f7.getTypeID());
	CPPUNIT_ASSERT(f10.getShape() == f7.getShape());
	CPPUNIT_ASSERT(f10.getElementShape() == f7.getElementShape());
	CPPUNIT_ASSERT(f10.isOpen());
	CPPUNIT_ASSERT(!f1.isOpen());

	//testing move constructor on string array
	NXField f11 = std::move(f4);
	CPPUNIT_ASSERT(f11.getTypeID()==f8.getTypeID());
	CPPUNIT_ASSERT(f11.getShape() == f8.getShape());
	CPPUNIT_ASSERT(f11.getElementShape() == f8.getElementShape());
	CPPUNIT_ASSERT(f11.isOpen());
	CPPUNIT_ASSERT(!f4.isOpen());

	g.close();
}

void NXFieldTest::testAssignment(){
	std::cerr<<"NXFieldTest::testAssignment ---------------------------------------"<<std::endl;
	NXField f2;
	ArrayShape dshape(2);
	dshape.setDimension(0,NX);
	dshape.setDimension(1,NY);
	Float64Array array(dshape);
	array.setName("testdata");
	array.setDescription("a simple testing array");
	array.setUnit("nm");


	NXField f1 = _f.createNumericField(array);
	CPPUNIT_ASSERT(f1.getElementShape() == array.getShape());
	CPPUNIT_ASSERT(f1.getTypeID() == array.getTypeID());

	CPPUNIT_ASSERT_NO_THROW(f2 = f1);
	CPPUNIT_ASSERT(f2.getShape() == f1.getShape());
	CPPUNIT_ASSERT(f2.getTypeID() == f1.getTypeID());
	CPPUNIT_ASSERT(f2.isOpen());
	CPPUNIT_ASSERT(f1.isOpen());

	NXField f3;
	CPPUNIT_ASSERT_NO_THROW(f3 = std::move(f1));
	CPPUNIT_ASSERT(!f1.isOpen());
	CPPUNIT_ASSERT(f3.isOpen());
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
	std::cerr<<"NXFieldTest::testGetData ---------------------------------------"<<std::endl;
	NXField sfield,afield,rfield;
	ArrayShape dshape(2);
	dshape.setDimension(0,NX);
	dshape.setDimension(1,NY);
	Float64Array array(dshape);
	Float64 tdata[] = {1.2,1.3,1.4};
	Float64Scalar scalar("scalar","nm","a testing scalar");

	array.setName("array");
	array.setDescription("a testing array");
	array.setUnit("m");

	//write data to disk
	sfield = _f.createNumericField(array);
	afield = _f.createNumericField(scalar);
	for(UInt64 i=0;i<3;i++){
		array = tdata[i];
		scalar = tdata[i];
		sfield.append(array);
		afield.append(scalar);
	}

	//read data
	CPPUNIT_ASSERT_NO_THROW(rfield = _f.openField(array.getName()));
	for(UInt64 i=0;i<rfield.getShape().getDimension(0);i++){
		CPPUNIT_ASSERT_NO_THROW(rfield.get(i,array));
		for(UInt64 j=0;j<array.getShape().getSize();j++){

				CPPUNIT_ASSERT(array[j] == tdata[i]);
		}
	}

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
	dset = _f.createNumericField("field_1",PNITypeID::FLOAT64,_data_shape,"a.u.","data");
	//CPPUNIT_ASSERT_NO_THROW(dset = _f.createNumericField("field_1",PNITypeID::FLOAT64,_data_shape,"a.z.","data"));
	_f64_data_array_write = 1.3;
	CPPUNIT_ASSERT(dset.isOpen());

	_f64_data_array_write.setUnit("a.u.");
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

	//------------------testing exceptions for scalar data---------------------
	dset = _f.createNumericField("field_3",PNITypeID::FLOAT64,"a.u.","data");
	CPPUNIT_ASSERT_THROW(dset.append(_write_cmplx_scalar),pni::nx::NXFieldError);

	//-------------------testing exceptions for string data--------------------
	dset = _f.createStringField("field_4");

}

void NXFieldTest::testStreamIO(){
	std::cerr<<"NXFieldTest::testStreamIO ---------------------------------------"<<std::endl;
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
	std::cout<<dset.getShape().getDimension(0)<<std::endl;
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

void NXFieldTest::testMap(){
	std::cerr<<"NXFieldTest::testMap ---------------------------------------"<<std::endl;
	typedef std::map<String,NXField> FieldMap;

	FieldMap fmap;
	CPPUNIT_ASSERT_NO_THROW(fmap.insert(FieldMap::value_type("test1",_f.createNumericField("test1",PNITypeID::UINT32,"nm","testing field 1"))));
	CPPUNIT_ASSERT(!fmap.empty());
	CPPUNIT_ASSERT(fmap["test1"].isOpen());
	CPPUNIT_ASSERT_NO_THROW(fmap["test2"] = _f.createNumericField("test2",PNITypeID::UINT32,"nm","testing field 1"));
	CPPUNIT_ASSERT(fmap["test2"].isOpen());

}
