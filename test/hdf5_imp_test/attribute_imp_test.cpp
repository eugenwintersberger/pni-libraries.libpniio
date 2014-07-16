//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 16, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include "attribute_imp_test.hpp"
#include <pni/io/nx/nxdate_time.hpp>


CPPUNIT_TEST_SUITE_REGISTRATION(attribute_imp_test);

//-----------------------------------------------------------------------------
void attribute_imp_test::setUp()
{
    file = file_imp::create("attribute_imp_test.h5",true,0);
    root_group = file.root();
}

//-----------------------------------------------------------------------------
void attribute_imp_test::tearDown()
{
    root_group.close();
    file.close();
}

//-----------------------------------------------------------------------------
void attribute_imp_test::test_creation()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    using pni::io::nx::nxdate_time;

    //default constructor
    attribute_imp a;
    CPPUNIT_ASSERT(!a.is_valid());
  
    //test constructor from new object
    attribute_imp a1(create_attribute(root_group.object(),
                                     "a1",
                                     get_type(type_id_t::STRING),
                                     h5dataspace(),
                                     false));
    CPPUNIT_ASSERT(a1.is_valid());
    CPPUNIT_ASSERT(a1.name() == "a1");

    
    //test construction from copy constructor
    attribute_imp a2(a1);
    CPPUNIT_ASSERT(a2.is_valid());
    CPPUNIT_ASSERT(a2.name() == a1.name());
    
    //test move construction
    attribute_imp a3(std::move(a2));
    CPPUNIT_ASSERT(a3.is_valid());
    CPPUNIT_ASSERT(!a2.is_valid());

}

//-----------------------------------------------------------------------------
void attribute_imp_test::test_assignment()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    attribute_imp a1(create_attribute(root_group.object(),
                                      "a1",
                                      get_type(type_id_t::STRING),
                                      h5dataspace(),
                                      false));
    CPPUNIT_ASSERT(a1.is_valid());

    attribute_imp a2;
    a2 = a1;
    CPPUNIT_ASSERT(a1.is_valid());
    CPPUNIT_ASSERT(a2.is_valid());

    attribute_imp a3;
    a3= std::move(a2);
    CPPUNIT_ASSERT(!a2.is_valid());
    CPPUNIT_ASSERT(a1.is_valid());
    CPPUNIT_ASSERT(a3.is_valid());
}



//-----------------------------------------------------------------------------
void attribute_imp_test::test_inquery()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    attribute_imp a1(create_attribute(root_group.object(),
                                      "a1",
                                      get_type(type_id_t::FLOAT32),
                                      h5dataspace(),
                                      false));
    shape_t shape{10,2};
    attribute_imp a2(create_attribute(root_group.object(),
                                      "a2",
                                      get_type(type_id_t::FLOAT32),
                                      h5dataspace{10,2},
                                      false));

    CPPUNIT_ASSERT(a1.is_valid());
    CPPUNIT_ASSERT(a1.name() == "a1");
    CPPUNIT_ASSERT(a1.filename() == string("attribute_imp_test.h5"));
    CPPUNIT_ASSERT(a1.size() == 1);
    CPPUNIT_ASSERT(a1.rank() == 0);
    CPPUNIT_ASSERT(a1.type_id() == type_id_t::FLOAT32);
    CPPUNIT_ASSERT(a1.shape<shape_t>().size() == 0);


    CPPUNIT_ASSERT(a2.is_valid());
    CPPUNIT_ASSERT(a2.name() == "a2");
    CPPUNIT_ASSERT(a2.filename() == "attribute_imp_test.h5");
    CPPUNIT_ASSERT(a2.size() == 20);
    CPPUNIT_ASSERT(a2.rank() == 2);
    CPPUNIT_ASSERT(a2.type_id() == type_id_t::FLOAT32);
    auto ashape = a2.shape<shape_t>();
    CPPUNIT_ASSERT(std::equal(shape.begin(),shape.end(),ashape.begin()));

    group_imp parent(a1.parent());
    CPPUNIT_ASSERT(parent.is_valid());
    CPPUNIT_ASSERT(parent.name() == "/");
}


