/*
 * Declaration of Nexus object template.
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************/

//implementation of the arrayshape test

#include<cppunit/extensions/HelperMacros.h>

#include "NX.hpp"
#include "NXExceptions.hpp"
#include "NXFileTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NXFileTest);

//------------------------------------------------------------------------------
void NXFileTest::setUp(){
	_fname1 = "test.file-1.h5";
	_fname2 = "test.file-2.h5";
	Index i;

	_write_str_attr = "hello world";
	_write_scalar_attr = 100;
	_shape = Shape();
	_shape.rank(2);
	_shape.dim(0,3);
	_shape.dim(1,3);

	_write_array_attr = Int16Array();
	i.rank(_shape.rank());
	_write_array_attr.shape(_shape);
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

	_read_array_attr = Int16Array();

}

//------------------------------------------------------------------------------
void NXFileTest::tearDown(){
	//after finishing the tests we need to remove all created files
	path path2(_fname2);

	if(exists(path2)) remove_all(path2);
}

//------------------------------------------------------------------------------
void NXFileTest::testCreation(){
	std::cout<<"void NXFileTest::testCreation()-------------------------------";
	std::cout<<std::endl;
	NXFile f;

	//initially create the file
	CPPUNIT_ASSERT_NO_THROW(f.filename(_fname1));
	CPPUNIT_ASSERT_NO_THROW(f.overwrite(true));
	CPPUNIT_ASSERT_NO_THROW(f.create());
	CPPUNIT_ASSERT_NO_THROW(f.close());

	//recreating the file should cause an error
	f.overwrite(false);
	CPPUNIT_ASSERT_THROW(f.create(),pni::nx::NXFileError); //here we except an error

	//now if we set overwrite
	f.overwrite(true);
	//everything should work fine
	CPPUNIT_ASSERT_NO_THROW(f.create());
	//check if all exceptions are thrown correctly on an already opened file
	CPPUNIT_ASSERT_THROW(f.overwrite(false),pni::nx::NXFileError);
	CPPUNIT_ASSERT_THROW(f.read_only(false),pni::nx::NXFileError);
	CPPUNIT_ASSERT_THROW(f.split_size(100),pni::nx::NXFileError);
	CPPUNIT_ASSERT_THROW(f.open(),pni::nx::NXFileError);
	CPPUNIT_ASSERT_THROW(f.create(),pni::nx::NXFileError);

	f.close();

}

//------------------------------------------------------------------------------
void NXFileTest::testOpen(){
	std::cout<<"void NXFileTest::testOpen()-----------------------------------";
	std::cout<<std::endl;
	NXFile f;

	CPPUNIT_ASSERT_NO_THROW(f.filename(_fname1));
	CPPUNIT_ASSERT_NO_THROW(f.overwrite(true));
	CPPUNIT_ASSERT_NO_THROW(f.read_only(false));
	CPPUNIT_ASSERT_NO_THROW(f.create());
	CPPUNIT_ASSERT_NO_THROW(f.close());

	CPPUNIT_ASSERT_NO_THROW(f.open());
	//check if all exceptions are thrown correctly on an already opened file
	CPPUNIT_ASSERT_THROW(f.overwrite(false),pni::nx::NXFileError);
	CPPUNIT_ASSERT_THROW(f.read_only(false),pni::nx::NXFileError);
	CPPUNIT_ASSERT_THROW(f.split_size(100),pni::nx::NXFileError);
	CPPUNIT_ASSERT_THROW(f.open(),pni::nx::NXFileError);
	CPPUNIT_ASSERT_THROW(f.create(),pni::nx::NXFileError);

	CPPUNIT_ASSERT_NO_THROW(f.close());

	//try to open a file which does not exist
	CPPUNIT_ASSERT_NO_THROW(f.filename(_fname2));
	CPPUNIT_ASSERT_THROW(f.open(),pni::nx::NXFileError);

	CPPUNIT_ASSERT_NO_THROW(f.create());
	CPPUNIT_ASSERT_NO_THROW(f.close());
	CPPUNIT_ASSERT_NO_THROW(f.open());
	CPPUNIT_ASSERT_NO_THROW(f.close());

}

//------------------------------------------------------------------------------
void NXFileTest::testAttributes(){
	std::cout<<"void NXFileTest::testAttributes()-----------------------------";
	std::cout<<std::endl;
	NXFile f;

	//create a new file
	f.filename(_fname1);
	f.overwrite(true);
	f.create();

	//write attribute data
	f.set_attr("StringAttribute",_write_str_attr);
	f.set_attr("FloatScalarAttribute",_write_scalar_attr);
	f.set_attr("IndexOfRefraction",_write_cmplx_scalar);
	f.set_attr("ArrayAttribute",_write_array_attr);

	//close and reopen the file
	f.close();
	f.open();


	//read data
	f.get_attr("StringAttribute",_read_str_attr);
	f.get_attr("FloatScalarAttribute",_read_scalar_attr);
	f.get_attr("ArrayAttribute",_read_array_attr);
	f.get_attr("IndexOfRefraction",_read_cmplx_scalar);

	//check if values are the same
	CPPUNIT_ASSERT(_write_str_attr == _read_str_attr);
	CPPUNIT_ASSERT(_read_scalar_attr == _read_scalar_attr);
	CPPUNIT_ASSERT(_read_array_attr == _write_array_attr);
	CPPUNIT_ASSERT(_write_cmplx_scalar == _read_cmplx_scalar);
	f.close();
}

//------------------------------------------------------------------------------
void NXFileTest::testAttributeExceptions(){
	std::cout<<"void NXFileTest::testAttributeExceptions()--------------------";
	std::cout<<std::endl;
	NXFile f;

	//create a new file
	f.filename(_fname1);
	f.overwrite(true);
	f.create();

	//write attribute data
	f.set_attr("StringAttribute",_write_str_attr);
	f.set_attr("FloatScalarAttribute",_write_scalar_attr);
	f.set_attr("IndexOfRefraction",_write_cmplx_scalar);
	f.set_attr("ArrayAttribute",_write_array_attr);

	//it is possible to overwrite attributes
	CPPUNIT_ASSERT_NO_THROW(f.set_attr("StringAttribute",_write_str_attr));
	CPPUNIT_ASSERT_NO_THROW(f.set_attr("FloatScalarAttribute",_write_scalar_attr));
	CPPUNIT_ASSERT_NO_THROW(f.set_attr("IndexOfRefraction",_write_cmplx_scalar));
	CPPUNIT_ASSERT_NO_THROW(f.set_attr("ArrayAttribute",_write_array_attr));

	//trying to read attributes that do not exist
	CPPUNIT_ASSERT_THROW(f.get_attr("StringAttribute_not",_read_str_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(f.get_attr("FloatScalarAttribute_not",_read_scalar_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(f.get_attr("ArrayAttribute_not",_read_array_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(f.get_attr("IndexOfRefraction_not",_read_cmplx_scalar),H5AttributeError);

	f.close();
}




