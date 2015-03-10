//
// Declaration of Nexus object template.
//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================

//testing class for ArrayShape objects

#pragma once

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>

#include <pni/io/nx/nx.hpp>

using namespace pni::core;
using namespace pni::io::nx;

template<typename T>
class nxattribute_creation_test: public CppUnit::TestFixture 
{
	CPPUNIT_TEST_SUITE(nxattribute_creation_test);
	CPPUNIT_TEST(test_scalar_no_overwrite<h5::nxgroup>);
	CPPUNIT_TEST(test_scalar_no_overwrite<h5::nxfield>);
    CPPUNIT_TEST(test_scalar_with_overwrite<h5::nxgroup>);
    CPPUNIT_TEST(test_scalar_with_overwrite<h5::nxfield>);
    CPPUNIT_TEST(test_multidim_no_overwrite<h5::nxgroup>);
    CPPUNIT_TEST(test_multidim_no_overwrite<h5::nxfield>);
    CPPUNIT_TEST(test_multidim_with_overwrite<h5::nxgroup>);
    CPPUNIT_TEST(test_multidim_with_overwrite<h5::nxfield>);
    CPPUNIT_TEST(test_copy_construction);
    CPPUNIT_TEST(test_move_construction);
	CPPUNIT_TEST_SUITE_END();
    h5::nxfile f;
    h5::nxgroup root;
    h5::nxfield field;
    static const string filename;
    static const shape_t shape;
    static const size_t size = 12;

    template<typename ST> 
    static bool check_shape(const ST &a,const ST &b)
    {
        return std::equal(a.begin(),a.end(),b.begin()); 
    }

    void get_parent(h5::nxgroup &group)
    {
        group = root;
    }

    void get_parent(h5::nxfield &f)
    {
        f = field;
    }
public:
	void setUp();
	void tearDown();

	//testing basic file functionality
    template<typename P> void test_scalar_no_overwrite();
    template<typename P> void test_scalar_with_overwrite();
    template<typename P> void test_multidim_no_overwrite();
    template<typename P> void test_multidim_with_overwrite();
    void test_copy_construction();
    void test_move_construction();

};

template<typename T>
const string nxattribute_creation_test<T>::filename="nxattribute_creation_test.nxs";
template<typename T>
const shape_t nxattribute_creation_test<T>::shape = shape_t{3,4};

//------------------------------------------------------------------------------
template<typename T>
void nxattribute_creation_test<T>::setUp() 
{ 
    f = h5::nxfile::create_file(filename,true);
    root = f.root();
    field = root.create_field<float32>("temperature");
}

//----------------------------------------------------------------------------
template<typename T>
void nxattribute_creation_test<T>::tearDown() 
{   
    root.close();
    field.close();
    f.close();
}

//----------------------------------------------------------------------------
template<typename T>
template<typename P>
void nxattribute_creation_test<T>::test_scalar_no_overwrite()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    P parent; 
    get_parent(parent);

    h5::nxattribute attr;
    CPPUNIT_ASSERT_NO_THROW(attr = parent.attributes.template create<T>("test"));
    CPPUNIT_ASSERT(attr.is_valid());
    CPPUNIT_ASSERT(attr.size() == 1);
    CPPUNIT_ASSERT(attr.type_id() == type_id_map<T>::type_id);

    //try to create a new attribute of same name should throw
    CPPUNIT_ASSERT_THROW(parent.attributes.template create<T>("test"),object_error);

}

//----------------------------------------------------------------------------
template<typename T>
template<typename P>
void nxattribute_creation_test<T>::test_scalar_with_overwrite()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    P parent; 
    get_parent(parent);

    h5::nxattribute attr;
    CPPUNIT_ASSERT_NO_THROW(attr = parent.attributes.template create<T>("test"));
    CPPUNIT_ASSERT(attr.is_valid());
    CPPUNIT_ASSERT(attr.size() == 1);
    CPPUNIT_ASSERT(attr.type_id() == type_id_map<T>::type_id);

    //try to create a new attribute of same name should throw
    CPPUNIT_ASSERT_NO_THROW(parent.attributes.template create<string>("test",true));
}

//----------------------------------------------------------------------------
template<typename T>
template<typename P>
void nxattribute_creation_test<T>::test_multidim_no_overwrite()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    P parent; 
    get_parent(parent);

    h5::nxattribute attr;
    CPPUNIT_ASSERT_NO_THROW(attr = parent.attributes.template create<T>("test",shape));
    CPPUNIT_ASSERT(attr.is_valid());
    CPPUNIT_ASSERT(attr.size() == size);
    CPPUNIT_ASSERT(attr.type_id() == type_id_map<T>::type_id);
    CPPUNIT_ASSERT(check_shape(attr.template shape<shape_t>(),shape));

    //try to create a new attribute of same name should throw
    CPPUNIT_ASSERT_THROW(parent.attributes.template create<T>("test",shape),object_error);
}

//----------------------------------------------------------------------------
template<typename T>
template<typename P>
void nxattribute_creation_test<T>::test_multidim_with_overwrite()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    P parent; 
    get_parent(parent);

    h5::nxattribute attr;
    CPPUNIT_ASSERT_NO_THROW(attr = parent.attributes.template
            create<T>("test",shape));
    CPPUNIT_ASSERT(attr.is_valid());
    CPPUNIT_ASSERT(attr.size() == size);
    CPPUNIT_ASSERT(attr.type_id() == type_id_map<T>::type_id);
    CPPUNIT_ASSERT(check_shape(attr.template shape<shape_t>(),shape));

    //try to create a new attribute of same name should throw
    CPPUNIT_ASSERT_NO_THROW(parent.attributes.template create<string>("test",shape,true));
}

//----------------------------------------------------------------------------
template<typename T>
void nxattribute_creation_test<T>::test_copy_construction()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    auto attr1 = field.attributes.create<T>("test");

    //copy construction
    h5::nxattribute attr = attr1;
    CPPUNIT_ASSERT(attr.is_valid());
    CPPUNIT_ASSERT(attr1.is_valid());
    CPPUNIT_ASSERT(attr.name() == attr1.name());
}

//----------------------------------------------------------------------------
template<typename T>
void nxattribute_creation_test<T>::test_move_construction()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    auto attr1 = field.attributes.create<T>("test");

    //copy construction
    h5::nxattribute attr = std::move(attr1);
    CPPUNIT_ASSERT(attr.is_valid());
    CPPUNIT_ASSERT(!attr1.is_valid());
    CPPUNIT_ASSERT(attr.name() == "test");
}

