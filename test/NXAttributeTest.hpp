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
 * NXAttributeTest.hpp
 *
 *  Created on: Sep 13, 2012
 *      Author: Eugen Wintersberger
 */


#ifndef __NXATTRIBUTETEST_HPP__
#define __NXATTRIBUTETEST_HPP__

#include "NX.hpp"

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>


using namespace pni::utils;
using namespace pni::nx::h5;

/*!
\ingroup test_classes
\brief Attribute facilities test

Testing attribute facilities of different Nexus objects
\tparam APTYPE attribute parent type (group, field, or file)
*/
template<typename APTYPE> class NXAttributeTest: public CppUnit::TestFixture  
{
	CPPUNIT_TEST_SUITE(NXAttributeTest<APTYPE>);
    CPPUNIT_TEST(test_scalar_attribute<UInt8>);
	CPPUNIT_TEST_SUITE_END();
private:
	NXFile _f;
    APTYPE _parent;
    static void create_parent(const NXFile &f,NXFile &p);
    static void create_parent(const NXFile &f,NXGroup &p);
    static void create_parent(const NXFile &f,NXField &p);
public:
	void setUp();
	void tearDown();
    template<typename T> void test_scalar_attribute();
};

//-----------------------------------------------------------------------------
template<typename APTYPE> 
void NXAttributeTest<APTYPE>::create_parent(const NXFile &f,NXFile &p)
{
    p = f;
}

//-----------------------------------------------------------------------------
template<typename APTYPE>
void NXAttributeTest<APTYPE>::create_parent(const NXFile &f,NXGroup &p)
{
    p = f.create_group("testgroup");
}

//-----------------------------------------------------------------------------
template<typename APTYPE>
void NXAttributeTest<APTYPE>::create_parent(const NXFile &f,NXField &p)
{
    p = f.create_field<String>("hello");
    p.write("hello world");
}

//-----------------------------------------------------------------------------
template<typename APTYPE> void NXAttributeTest<APTYPE>::setUp()
{
    //create the file where to store data
    _f = NXFile::create_file("NXAttributeTest.h5",true,0);

    //create the attribute parrent
    create_parent(_f,_parent);
}

//-----------------------------------------------------------------------------
template<typename APTYPE> void NXAttributeTest<APTYPE>::tearDown()
{
    _parent.close();
    _f.close();
}

//-----------------------------------------------------------------------------
template<typename APTYPE> 
template<typename T> void NXAttributeTest<APTYPE>::test_scalar_attribute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //create the attribute
    NXAttribute a = _parent.template attr<T>("a1");

    //check attribute status
    CPPUNIT_ASSERT(a.is_valid());
    CPPUNIT_ASSERT(a.name() == "a1");
    
    T write_value = T(1);
    a.write(write_value);
    
    //close the attribute
    a.close();
    CPPUNIT_ASSERT(!a.is_valid());
    //open the attribute again
    CPPUNIT_ASSERT_NO_THROW(a = _parent.attr("a1"));
    CPPUNIT_ASSERT(a.is_valid());
    CPPUNIT_ASSERT(a.name() == "a1");


    T read_value  = T(0);
    a.read(read_value);
    CPPUNIT_ASSERT(write_value == read_value);
    
    a.close();
    CPPUNIT_ASSERT(!a.is_valid());

    //--------------------test some exceptions---------------------------------
    //try to recreate an attribute
    CPPUNIT_ASSERT_THROW(_parent.template
            attr<T>("a1"),pni::nx::NXAttributeError);

    //try to open a non-existing attribute
    CPPUNIT_ASSERT_THROW(_parent.attr("b1"),pni::nx::NXAttributeError);


}


#endif
