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

	_write_str_attr = "hello world";
	_write_scalar_attr = 100;
	_shape = {3,3};

	_write_array_attr = ArrayFactory<Int16>::create(_shape);

    Int16 value = 0;
    for(Int16 &v: _write_array_attr) v = value++;

	_write_cmplx_scalar = Complex64(1,-2);

	_read_array_attr = ArrayFactory<Int16>::create(_shape);

}

//------------------------------------------------------------------------------
void NXFileTest::tearDown(){
	//after finishing the tests we need to remove all created files
}

//------------------------------------------------------------------------------
void NXFileTest::testCreation(){
	std::cout<<"void NXFileTest::testCreation()-------------------------------";
	std::cout<<std::endl;
	NXFile f;

	//initially create the file
	CPPUNIT_ASSERT(!f.is_valid());
	CPPUNIT_ASSERT_NO_THROW(f = NXFile::create_file("NXFileTest.h5",true,0));
	CPPUNIT_ASSERT(f.is_valid());
    CPPUNIT_ASSERT_NO_THROW(f.close());
    CPPUNIT_ASSERT(!f.is_valid());

	//recreating the file should cause an error
	CPPUNIT_ASSERT_THROW(NXFile::create_file("NXFileTest.h5",false)
            ,pni::nx::NXFileError); //here we except an error

	//everything should work fine
	CPPUNIT_ASSERT_NO_THROW(f = NXFile::create_file("NXFileTest.h5",true,0));
    f.flush();
    //should produce no exception as HDF5 allows multiple files to be open
	CPPUNIT_ASSERT_NO_THROW(NXFile::open_file("NXFileTest.h5",true));
    //try now with readonly flag set
    CPPUNIT_ASSERT_NO_THROW(NXFile::open_file("NXFileTest.h5",false));

    //try now multiple calls to create
    //if overwrite is not set an exception should be thrown
	CPPUNIT_ASSERT_THROW(NXFile::create_file("NXFileTest.h5",false,0),
            pni::nx::NXFileError);
    CPPUNIT_ASSERT_THROW(NXFile::create_file("NXFileTest.h5",true,0),
            pni::nx::NXFileError);

	f.close();

    //check copy ans move constructor
	CPPUNIT_ASSERT_NO_THROW(f = NXFile::create_file("NXFileTest.h5",true,0));
    CPPUNIT_ASSERT(f.is_valid());
    NXFile f2(f);
    CPPUNIT_ASSERT(f.is_valid());
    CPPUNIT_ASSERT(f2.is_valid());

    //check move construction
    NXFile f3 = std::move(f2);
    CPPUNIT_ASSERT(f3.is_valid());
    CPPUNIT_ASSERT(!f2.is_valid());
    CPPUNIT_ASSERT(f.is_valid());

}

//------------------------------------------------------------------------------
void NXFileTest::testOpen(){
	std::cout<<"void NXFileTest::testOpen()-----------------------------------";
	std::cout<<std::endl;
	NXFile f;

    CPPUNIT_ASSERT_NO_THROW(f = NXFile::create_file("NXFileTest.h5",true,0));
    CPPUNIT_ASSERT_NO_THROW(f.close());

	CPPUNIT_ASSERT_NO_THROW(f = NXFile::open_file("NXFileTest.h5",true));
	//here we should get exceptions because the file is already open
	CPPUNIT_ASSERT_NO_THROW(NXFile::open_file("NXFileTest.h5",true));

    //here we should  get an exception - the file is already open
	CPPUNIT_ASSERT_THROW(NXFile::create_file("NXFileTest.h5",true,0),
            pni::nx::NXFileError);

	CPPUNIT_ASSERT_NO_THROW(f.close());

	//try to open a file which does not exist
	CPPUNIT_ASSERT_THROW(NXFile::open_file("blabla.h5",true),pni::nx::NXFileError);

}

//------------------------------------------------------------------------------
void NXFileTest::testAttributes(){
	std::cout<<"void NXFileTest::testAttributes()-----------------------------";
	std::cout<<std::endl;
	NXFile f;

	//create a new file
    f = NXFile::create_file("NXFileTest.h5",true,0);

	//write attribute data
	CPPUNIT_ASSERT_NO_THROW(
            f.attr<String>("StringAttribute").write(_write_str_attr));
	CPPUNIT_ASSERT_NO_THROW(
            f.attr<Float32>("FloatScalarAttribute").write(_write_scalar_attr));
	CPPUNIT_ASSERT_NO_THROW(
            f.attr<Complex64>("IndexOfRefraction").write(_write_cmplx_scalar));
	CPPUNIT_ASSERT_NO_THROW(
            f.attr<Float64>("ArrayAttribute",_write_array_attr.shape())
            .write(_write_array_attr));

	//close and reopen the file
	f.close();
	f = NXFile::open_file("NXFileTest.h5",false);


	//read data
	CPPUNIT_ASSERT_NO_THROW(f.attr("StringAttribute").read(_read_str_attr));
	CPPUNIT_ASSERT_NO_THROW(f.attr("FloatScalarAttribute").read(_read_scalar_attr));
	CPPUNIT_ASSERT_NO_THROW(f.attr("ArrayAttribute").read(_read_array_attr));
	CPPUNIT_ASSERT_NO_THROW(f.attr("IndexOfRefraction").read(_read_cmplx_scalar));

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
    f = NXFile::create_file("NXFileTest.h5",true,0);

	//write attribute data
	f.attr<String>("StringAttribute").write(_write_str_attr);
	f.attr<Float64>("FloatScalarAttribute").write(_write_scalar_attr);
	f.attr<Complex64>("IndexOfRefraction").write(_write_cmplx_scalar);
	f.attr<Float64>("ArrayAttribute",_write_array_attr.shape()).write(_write_array_attr);

	//it is possible to overwrite attributes
	CPPUNIT_ASSERT_NO_THROW(f.attr("StringAttribute").write(_write_str_attr));
	CPPUNIT_ASSERT_NO_THROW(f.attr("FloatScalarAttribute").write(_write_scalar_attr));
	CPPUNIT_ASSERT_NO_THROW(f.attr("IndexOfRefraction").write(_write_cmplx_scalar));
	CPPUNIT_ASSERT_NO_THROW(f.attr("ArrayAttribute").write(_write_array_attr));

	//trying to read attributes that do not exist
	CPPUNIT_ASSERT_THROW(f.attr("StringAttribute_not").read(_read_str_attr),pni::nx::NXAttributeError);
	CPPUNIT_ASSERT_THROW(f.attr("FloatScalarAttribute_not").read(_read_scalar_attr),pni::nx::NXAttributeError);
	CPPUNIT_ASSERT_THROW(f.attr("ArrayAttribute_not").read(_read_array_attr),pni::nx::NXAttributeError);
	CPPUNIT_ASSERT_THROW(f.attr("IndexOfRefraction_not").read(_read_cmplx_scalar),pni::nx::NXAttributeError);

	f.close();
}

//-----------------------------------------------------------------------------
void NXFileTest::test_iterator()
{
    std::cout<<"void NXFileTest::test_iterator()-----------------------------";
    std::cout<<std::endl;

    NXFile f = NXFile::create_file("NXFileTest.h5",true,0);
    f.create_group("dir1");
    f.create_group("dir2");
    f.create_group("dir3");

#ifdef NOFOREACH
    for(auto iter = f.begin(); iter!=f.end();iter++){
        auto &g = *iter;
#else
    for(auto &g: f){
#endif
        std::cout<<g.path()<<std::endl;
    }

    f.close();

}
