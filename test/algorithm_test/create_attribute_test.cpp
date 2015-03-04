//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
//  Created on: Jul 5, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "create_attribute_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(create_attribute_test);

//-----------------------------------------------------------------------------
void create_attribute_test::setUp()
{
    field_shape = shape_t{0,10,10};
    cs_shape  = shape_t{1,10,10};

    file = h5::nxfile::create_file("create_attribute_test.nx",true);
    root = file.root();
    group = root.create_group("group","NXentry");
    group.create_group("instrument","NXinstrument");
    field = group.create_field<int32>("test");
    attr  = field.attributes.create<float32>("temperature");
}

//-----------------------------------------------------------------------------
void create_attribute_test::tearDown() 
{ 
    attr.close();
    field.close();
    group.close();
    root.close();
    file.close();
}
//-----------------------------------------------------------------------------

void create_attribute_test::default_test(const h5::nxobject &a)
{
    CPPUNIT_ASSERT(is_valid(a));
    CPPUNIT_ASSERT(is_attribute(a));
}

//-----------------------------------------------------------------------------
void create_attribute_test::test_group_object()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject root_group = root;
    
    h5::nxobject f;
    CPPUNIT_ASSERT_NO_THROW(f=create_attribute<float32>(root_group,"test1"));
    CPPUNIT_ASSERT(is_valid(f));
    CPPUNIT_ASSERT(is_attribute(f));
    CPPUNIT_ASSERT(get_name(f)=="test1");
    CPPUNIT_ASSERT(get_rank(f)==0);
    CPPUNIT_ASSERT(get_type(f) == type_id_t::FLOAT32);
    auto s = get_shape<shape_t>(f);
    CPPUNIT_ASSERT(s.size()== 0);
    //by default overwrite is false - this should throw
    CPPUNIT_ASSERT_THROW(create_attribute<float64>(root_group,"test1"),object_error);
    //if we wet overwrite to true - we can create a new attribute
    CPPUNIT_ASSERT_NO_THROW(f = create_attribute<float64>(root_group,"test1",true));
    CPPUNIT_ASSERT(get_type(f)==type_id_t::FLOAT64);
    CPPUNIT_ASSERT_NO_THROW(f = create_attribute(root_group,type_id_t::INT16,"test1",true));
    CPPUNIT_ASSERT(get_type(f) == type_id_t::INT16);

    CPPUNIT_ASSERT(is_valid(f=create_attribute<float32>(root_group,"test2",shape_t{4,3})));
    CPPUNIT_ASSERT(is_attribute(f));
    CPPUNIT_ASSERT(get_name(f)=="test2");
    CPPUNIT_ASSERT(get_rank(f)==2);
    CPPUNIT_ASSERT(get_type(f) == type_id_t::FLOAT32);
    s = get_shape<shape_t>(f);
    CPPUNIT_ASSERT(s[0] == 4);
    CPPUNIT_ASSERT(s[1] == 3);

}

//-----------------------------------------------------------------------------
void create_attribute_test::test_field_object()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject parent = field;
    
    h5::nxobject f;
    CPPUNIT_ASSERT(is_valid(f=create_attribute<string>(parent,"test2")));    
    CPPUNIT_ASSERT(is_attribute(f));
    CPPUNIT_ASSERT(get_name(f)=="test2");
    CPPUNIT_ASSERT(get_rank(f)==0);
    CPPUNIT_ASSERT(get_type(f) == type_id_t::STRING);
    auto s = get_shape<shape_t>(f);
    CPPUNIT_ASSERT(s.size() == 0);
    CPPUNIT_ASSERT_THROW(f=create_attribute<int16>(parent,"test2"),object_error);
    CPPUNIT_ASSERT_NO_THROW(f=create_attribute<int16>(parent,"test2",true));
}

//-----------------------------------------------------------------------------
void create_attribute_test::test_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject object = group.attributes["NX_class"];
    CPPUNIT_ASSERT_THROW(create_attribute<float32>(object,"g1"),type_error);
}

//----------------------------------------------------------------------------
void create_attribute_test::test_errors()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject object;

    CPPUNIT_ASSERT_THROW(create_attribute<string>(object,"test"),
                         invalid_object_error);
}

