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
 *************************************************************************
 * NXGroupTest.cpp
 *
 *  Created on: Aug 4, 2011
 *      Author: Eugen Wintersberger
 */

#include "NXGroupTest.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include "NX.hpp"
#include "NXObjectType.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NXGroupTest);

//------------------------------------------------------------------------------
void NXGroupTest::setUp(){
	_fname = "test.group.h5";
	Index i;
    _f = NXFile::create_file("NXGroupTest.h5",true,0);
    CPPUNIT_ASSERT(_f.object_type() == pni::nx::NXObjectType::NXGROUP);


	_write_str_attr = "hello world";
	_write_scalar_attr = 100;
	_shape = Shape();
	_shape = {3,3};

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
    _read_array_attr.shape(_shape);
    _read_array_attr.allocate();

}

//------------------------------------------------------------------------------
void NXGroupTest::tearDown(){
	//close the file
	std::cerr<<"0000000000000000000 CLOSING FILE 00000000000000000000000!"<<std::endl;
	_f.close();
}

//------------------------------------------------------------------------------
void NXGroupTest::test_linking()
{
    NXGroup g = _f.create_group("/scan_1/detector/data");
    CPPUNIT_ASSERT_NO_THROW(g.link("/collection/detector/data"));
    CPPUNIT_ASSERT(_f.exists("/collection/detector/data"));

    NXGroup ref = g.open("/scan_1");
    CPPUNIT_ASSERT_NO_THROW(g.link(ref,"a_link"));
    CPPUNIT_ASSERT(_f.exists("/scan_1/a_link"));

    NXFile file = NXFile::create_file("NXGroupTest2.h5",true,0);
    file.create_group("/test/data");
    CPPUNIT_ASSERT_NO_THROW(g.link("NXGroupTest2.h5:/test/data","/external/data"));
    CPPUNIT_ASSERT(_f.exists("/external/data"));
}

//------------------------------------------------------------------------------
void NXGroupTest::testCreation(){
	std::cout<<"void NXGroupTest::testCreation()------------------------------";
	std::cout<<std::endl;
	NXGroup g;
    CPPUNIT_ASSERT(!g.is_valid());

	g = _f.create_group("/hello/world");
    CPPUNIT_ASSERT(g.is_valid());
	g.close();
    CPPUNIT_ASSERT(!g.is_valid());
	g = _f.create_group("/directory_1");
    CPPUNIT_ASSERT(g.is_valid());
    CPPUNIT_ASSERT(g.path() == "/directory_1");
    CPPUNIT_ASSERT(g.name() == "directory_1");
    CPPUNIT_ASSERT(g.base() == "/");


	//test copy constructor
	NXGroup g1(g);
	CPPUNIT_ASSERT(g1.is_valid());
	CPPUNIT_ASSERT(g.is_valid());
	CPPUNIT_ASSERT(g1.name() == g.name());

	//test move constructor
	NXGroup g2 = std::move(g1);
	CPPUNIT_ASSERT(!g1.is_valid());
	CPPUNIT_ASSERT(g2.is_valid());

}

//------------------------------------------------------------------------------
void NXGroupTest::testOpen(){
	std::cout<<"void NXGroupTest::testOpen()----------------------------------";
	std::cout<<std::endl;
	NXGroup g1,g2;

	g1 = _f.create_group("/directory1/data");

	g2 = _f.open("/directory1");
	NXGroup g = g2.open("data");
	NXGroup g3;
	g3 = g2.open("data");

	NXGroup g4 = _f.open("/directory1/data");

	CPPUNIT_ASSERT_THROW(_f.open("directory2"),pni::nx::NXGroupError);
	CPPUNIT_ASSERT_NO_THROW(_f.open("directory1/data"));

	g1.close();
	g2.close();

}

//------------------------------------------------------------------------------
void NXGroupTest::testAttributes(){
	std::cout<<"void NXGroupTest::testAttributes()----------------------------";
	std::cout<<std::endl;
	NXGroup g;

	g = _f.create_group("/Hello/world1");

	//write attribute data
	g.attr<String>("StringAttribute").write(_write_str_attr);
	g.attr<Float64>("FloatScalarAttribute").write(_write_scalar_attr);
	g.attr<Complex64>("IndexOfRefraction").write(_write_cmplx_scalar);
	g.attr<Float64>("ArrayAttribute",_write_array_attr.shape()).write(_write_array_attr);
    CPPUNIT_ASSERT(g.nattr() == 4);
   
    NXGroup::attr_iterator aiter = g.attr_begin();
    while(aiter){
        std::cout<<aiter->name()<<std::endl;
        aiter++;
    }

    for(auto iter = g.attr_begin();iter != g.attr_end();iter++)
        std::cout<<iter->name()<<std::endl;


	//read data
	g.attr("StringAttribute").read(_read_str_attr);
	g.attr("FloatScalarAttribute").read(_read_scalar_attr);
	g.attr("ArrayAttribute").read(_read_array_attr);
	g.attr("IndexOfRefraction").read(_read_cmplx_scalar);

	//check if values are the same
	CPPUNIT_ASSERT(_write_str_attr == _read_str_attr);
	CPPUNIT_ASSERT(_read_scalar_attr == _read_scalar_attr);
	CPPUNIT_ASSERT(_read_array_attr == _write_array_attr);
	CPPUNIT_ASSERT(_write_cmplx_scalar == _read_cmplx_scalar);
}

//------------------------------------------------------------------------------
void NXGroupTest::testAttributeExceptions(){
	std::cout<<"void NXGroupTest::testAttributeExceptions()-------------------";
	std::cout<<std::endl;
	NXGroup g;

	g = _f.create_group("/hello/world");

	//write attribute data
	g.attr<String>("StringAttribute").write(_write_str_attr);
	g.attr<Float64>("FloatScalarAttribute").write(_write_scalar_attr);
	g.attr<Complex64>("IndexOfRefraction").write(_write_cmplx_scalar);
	g.attr<Float64>("ArrayAttribute",_write_array_attr.shape()).write(_write_array_attr);

	//trying to overwrite attributes
	CPPUNIT_ASSERT_NO_THROW(g.attr<String>("StringAttribute").write(_write_str_attr));
	CPPUNIT_ASSERT_NO_THROW(g.attr<Float64>("FloatScalarAttribute").write(_write_scalar_attr));
	CPPUNIT_ASSERT_NO_THROW(g.attr<Complex64>("IndexOfRefraction").write(_write_cmplx_scalar));
	CPPUNIT_ASSERT_NO_THROW(g.attr<Float64>("ArrayAttribute",_write_array_attr.shape()).write(_write_array_attr));

	//trying to read attributes that do not exist
	CPPUNIT_ASSERT_THROW(g.attr("StringAttribute_not").read(_read_str_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(g.attr("FloatScalarAttribute_not").read(_read_scalar_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(g.attr("ArrayAttribute_not").read(_read_array_attr),H5AttributeError);
	CPPUNIT_ASSERT_THROW(g.attr("IndexOfRefraction_not").read(_read_cmplx_scalar),H5AttributeError);

	g.close();
}

//------------------------------------------------------------------------------
void NXGroupTest::testInternalLinks(){

}

//------------------------------------------------------------------------------
void NXGroupTest::testExistence(){
	std::cout<<"void NXGroupTest::testExistence()-----------------------------";
	std::cout<<std::endl;
	NXGroup g1,g2;
	NXField f;

	g1 = _f.create_group("/scan_1/instrument");
	g1 = _f.create_group("/scan_2/instrument/detector");

	g1 = _f.open("scan_1");
	CPPUNIT_ASSERT(g1.exists("instrument"));
	CPPUNIT_ASSERT(g1.exists("/scan_2"));
	CPPUNIT_ASSERT(!g1.exists("/instrument"));
	g2 = _f.open("scan_2");
	CPPUNIT_ASSERT(g2.exists("instrument/detector/"));
	CPPUNIT_ASSERT(!g2.exists("/instrument/detector/data"));

	CPPUNIT_ASSERT(_f.exists("scan_1"));
	CPPUNIT_ASSERT(_f.exists("/scan_1/instrument"));
	CPPUNIT_ASSERT(_f.exists("scan_2/instrument/detector"));
}

//------------------------------------------------------------------------------
void NXGroupTest::testRemove(){

	NXGroup g1;
	NXField f;
}

//------------------------------------------------------------------------------
void NXGroupTest::testAssignment(){
	std::cout<<"void NXGroupTest::testAssignment()----------------------------";
	std::cout<<std::endl;
	NXGroup g1,g2;

	CPPUNIT_ASSERT_NO_THROW(g1 = _f.create_group("test1"));
	CPPUNIT_ASSERT_NO_THROW(g2 = g1);
	CPPUNIT_ASSERT(g1.is_valid());
	CPPUNIT_ASSERT(g2.is_valid());

	NXGroup g3;
	CPPUNIT_ASSERT_NO_THROW(g3 = std::move(g2));
	CPPUNIT_ASSERT(g3.is_valid());
	CPPUNIT_ASSERT(!g2.is_valid());
}

//------------------------------------------------------------------------------
void NXGroupTest::test_comparison(){
    std::cout<<"void NXGroupTest::test_comparison()---------------------------";
    std::cout<<std::endl;

    NXGroup g1 = _f.create_group("hello/world");
    NXGroup g2 = _f["/hello/world"];

    CPPUNIT_ASSERT(g1 == g2);

    g2 = _f["/hello"];
    CPPUNIT_ASSERT(g1 != g2);

    g1.link("/link");
    g2 = _f["/link"];
    CPPUNIT_ASSERT(g1 == g2);

}

//-----------------------------------------------------------------------------
void NXGroupTest::test_iterator()
{
    std::cout<<"void NXGroupTest::test_iterator()-----------------------------";
    std::cout<<std::endl;

    NXGroup g = _f.create_group("data");
    g.create_group("dir1");
    g.create_group("dir2");
    g.create_group("dir3");

    for(auto &sg: g){
        std::cout<<sg.path()<<std::endl;
    }
}

