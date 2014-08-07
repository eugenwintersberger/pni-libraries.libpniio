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
// Created on: Jul 15, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <list>
#include "h5dataspace_test.hpp"
#include <pni/io/exceptions.hpp>


CPPUNIT_TEST_SUITE_REGISTRATION(h5dataspace_test);


//----------------------------------------------------------------------------
void h5dataspace_test::setUp() { }

//----------------------------------------------------------------------------
void h5dataspace_test::tearDown(){ }

//----------------------------------------------------------------------------
void h5dataspace_test::test_default_construction()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    h5dataspace space;
    CPPUNIT_ASSERT(space.rank() == 1);
    CPPUNIT_ASSERT(space.size() == 1);
}

//----------------------------------------------------------------------------
void h5dataspace_test::test_object_construction()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5dataspace space1(object_imp(H5Screate_simple(3,dims,dims)));
    CPPUNIT_ASSERT(space1.rank() == 3);
    CPPUNIT_ASSERT(space1.size() == 600);
}

//----------------------------------------------------------------------------
void h5dataspace_test::test_move_construction()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5dataspace s1{{10,3}};
    CPPUNIT_ASSERT(s1.is_valid());
    CPPUNIT_ASSERT(s1.size() == 30);
    CPPUNIT_ASSERT(s1.rank() == 2);

    h5dataspace s2(std::move(s1));
    CPPUNIT_ASSERT(s2.is_valid());
    CPPUNIT_ASSERT(!s1.is_valid());
    CPPUNIT_ASSERT(s2.rank() == 2);
    CPPUNIT_ASSERT(s2.size() == 30);
}

//----------------------------------------------------------------------------
void h5dataspace_test::test_copy_construction()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5dataspace s1{{10,3}};
    CPPUNIT_ASSERT(s1.is_valid());
    CPPUNIT_ASSERT(s1.size() == 30);
    CPPUNIT_ASSERT(s1.rank() == 2);

    h5dataspace s2(s1);
    CPPUNIT_ASSERT(s2.is_valid());
    CPPUNIT_ASSERT(s1.is_valid());
    CPPUNIT_ASSERT(s2.rank() == 2);
    CPPUNIT_ASSERT(s2.size() == 30);
}

//----------------------------------------------------------------------------
void h5dataspace_test::test_move_assignment()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5dataspace s1{{10,3}};
    CPPUNIT_ASSERT(s1.is_valid());
    CPPUNIT_ASSERT(s1.size() == 30);
    CPPUNIT_ASSERT(s1.rank() == 2);

    h5dataspace s2;
    s2 = std::move(s1);
    CPPUNIT_ASSERT(s2.is_valid());
    CPPUNIT_ASSERT(!s1.is_valid());
    CPPUNIT_ASSERT(s2.rank() == 2);
    CPPUNIT_ASSERT(s2.size() == 30);
}

//----------------------------------------------------------------------------
void h5dataspace_test::test_copy_assignment()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5dataspace s1{{10,3}};
    CPPUNIT_ASSERT(s1.is_valid());
    CPPUNIT_ASSERT(s1.size() == 30);
    CPPUNIT_ASSERT(s1.rank() == 2);

    h5dataspace s2;
    s2 = s1;
    CPPUNIT_ASSERT(s2.is_valid());
    CPPUNIT_ASSERT(s1.is_valid());
    CPPUNIT_ASSERT(s2.rank() == 2);
    CPPUNIT_ASSERT(s2.size() == 30);
}

//----------------------------------------------------------------------------
void h5dataspace_test::test_container_construction()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef type_imp::index_vector_type list_type;
    
    list_type cdims={10,4,3};

    h5dataspace s1(cdims);
    CPPUNIT_ASSERT(s1.rank() == 3);
    CPPUNIT_ASSERT(s1.size() == 120);

    h5dataspace s2{list_type{100,40,30}};
    CPPUNIT_ASSERT(s2.rank() == 3);
    CPPUNIT_ASSERT(s2.size() == 100*40*30);
}

//----------------------------------------------------------------------------
void h5dataspace_test::test_current_iterator()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef type_imp::index_vector_type list_type;
    list_type shape{20,40,10};

    h5dataspace space(shape);
    
    auto liter = shape.begin();
    auto siter = space.shape().begin();
    for(;siter!=space.shape().end();++siter,++liter)
        CPPUNIT_ASSERT(*siter == *liter);
}

//----------------------------------------------------------------------------
void h5dataspace_test::test_grow()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5dataspace space{{10,20}};

    CPPUNIT_ASSERT_NO_THROW(space.grow(0));
    CPPUNIT_ASSERT(space.shape()[0]==11);
    CPPUNIT_ASSERT_NO_THROW(space.grow(0,4));
    CPPUNIT_ASSERT(space.shape()[0] ==15);
    CPPUNIT_ASSERT_NO_THROW(space.grow(1,2));
    CPPUNIT_ASSERT(space.shape()[1]==22);

    CPPUNIT_ASSERT_THROW(space.grow(10),index_error);
}
