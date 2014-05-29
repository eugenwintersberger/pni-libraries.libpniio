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
//  Created on: Jul 3, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "create_field_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(create_field_test);

//-----------------------------------------------------------------------------
void create_field_test::setUp()
{
    field_shape = shape_t{0,10,10};
    cs_shape  = shape_t{1,10,10};

    file = h5::nxfile::create_file("create_field_test.nx",true,0);
    root = file.root();
    group = root.create_group("group","NXentry");
    group.create_group("instrument","NXinstrument");
    field = group.create_field<int32>("test");
}

//-----------------------------------------------------------------------------
void create_field_test::tearDown() 
{ 
    field.close();
    group.close();
    root.close();
    file.close();
}


//-----------------------------------------------------------------------------
void create_field_test::test_group()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject root_group = root;
    
    h5::nxobject f;
    f=create_field<float32>(root_group,"test1");
    CPPUNIT_ASSERT(is_valid(f));
    CPPUNIT_ASSERT(is_field(f));
    CPPUNIT_ASSERT(get_name(f)=="test1");
    CPPUNIT_ASSERT(get_rank(f)==1);
    CPPUNIT_ASSERT(get_type(f) == type_id_t::FLOAT32);
    auto s = get_shape<shape_t>(f);
    CPPUNIT_ASSERT(s[0] == 1);

}

//-----------------------------------------------------------------------------
void create_field_test::test_group_from_path()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject gi = root["/group/instrument"];
    nxpath p = path_from_string("/:NXentry/:NXinstrument/data");

    
    h5::nxobject f;
    CPPUNIT_ASSERT_NO_THROW(f=create_field<float32>(gi,p));
    CPPUNIT_ASSERT(is_valid(f));
    CPPUNIT_ASSERT(is_field(f));
    CPPUNIT_ASSERT(get_name(f)=="data");
    CPPUNIT_ASSERT(get_rank(f)==1);
    CPPUNIT_ASSERT(get_type(f) == type_id_t::FLOAT32);
    auto s = get_shape<shape_t>(f);
    CPPUNIT_ASSERT(s[0] == 1);
    
    CPPUNIT_ASSERT_THROW(create_field<uint16>(gi,
                path_from_string("./:NXdetector/data")),nxgroup_error);

}

//-----------------------------------------------------------------------------
void create_field_test::test_group_filter()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxdeflate_filter filter(2,true);
    h5::nxobject root_group = root;
    
    h5::nxobject f;
    CPPUNIT_ASSERT(is_valid(f=create_field<float32>(root_group,"test2",
                               field_shape,cs_shape,filter)));
    CPPUNIT_ASSERT(is_field(f));
    CPPUNIT_ASSERT(get_name(f)=="test2");
    CPPUNIT_ASSERT(get_rank(f)==3);
    CPPUNIT_ASSERT(get_type(f) == type_id_t::FLOAT32);
    auto s = get_shape<shape_t>(f);
    CPPUNIT_ASSERT(s[0] == 0);
}

//-----------------------------------------------------------------------------
void create_field_test::test_group_filter_from_path()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxdeflate_filter filter(2,true);
    h5::nxobject root_group = root;
    
    h5::nxobject f;
    CPPUNIT_ASSERT(is_valid(f=create_field<float32>(root_group,"test2",
                               field_shape,cs_shape,filter)));
    CPPUNIT_ASSERT(is_field(f));
    CPPUNIT_ASSERT(get_name(f)=="test2");
    CPPUNIT_ASSERT(get_rank(f)==3);
    CPPUNIT_ASSERT(get_type(f) == type_id_t::FLOAT32);
    auto s = get_shape<shape_t>(f);
    CPPUNIT_ASSERT(s[0] == 0);
}

//-----------------------------------------------------------------------------
void create_field_test::test_field()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxobject object = field;

    CPPUNIT_ASSERT_THROW(create_field<float32>(object,"g1"),nxfield_error);
}

//-----------------------------------------------------------------------------
void create_field_test::test_attribute()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5::nxobject object = group.attr("NX_class");
    CPPUNIT_ASSERT_THROW(create_field<float32>(object,"g1"),nxattribute_error);
}

