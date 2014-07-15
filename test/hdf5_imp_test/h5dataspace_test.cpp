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
    CPPUNIT_ASSERT(space.is_scalar());
    CPPUNIT_ASSERT(space.rank() == 0);
    CPPUNIT_ASSERT(space.size() == 1);
}

//----------------------------------------------------------------------------
void h5dataspace_test::test_object_construction()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5dataspace space1(h5object(H5Screate_simple(3,dims,dims)));
    CPPUNIT_ASSERT(!space1.is_scalar());
    CPPUNIT_ASSERT(space1.rank() == 3);
    CPPUNIT_ASSERT(space1.size() == 600);
}

//----------------------------------------------------------------------------
void h5dataspace_test::test_init_list_construction()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5dataspace space({3,2,3,4});
    CPPUNIT_ASSERT(!space.is_scalar());
    CPPUNIT_ASSERT(space.rank()==4);
    CPPUNIT_ASSERT(space.size() == 72);

    h5dataspace space2({10,50},{100,500});
    CPPUNIT_ASSERT(!space2.is_scalar());
    CPPUNIT_ASSERT(space2.rank() == 2);
    CPPUNIT_ASSERT(space2.size() == 500);

    //fails because of different rank of current and maximum list
    CPPUNIT_ASSERT_THROW(h5dataspace({10,50},{100}),shape_mismatch_error);
    CPPUNIT_ASSERT_THROW(h5dataspace({10},{100,500}),shape_mismatch_error);
    //must fail because current number of elements exceeds the maximum 
    //number of elements
    CPPUNIT_ASSERT_THROW(h5dataspace({200},{100}),pni::io::object_error);
}

//----------------------------------------------------------------------------
void h5dataspace_test::test_container_construction()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef std::list<hsize_t> list_type;
    
    list_type cdims={10,4,3};

    h5dataspace s1(cdims);
    CPPUNIT_ASSERT(!s1.is_scalar());
    CPPUNIT_ASSERT(s1.rank() == 3);
    CPPUNIT_ASSERT(s1.size() == 120);
    
    list_type mdims = {100,400,300};
    h5dataspace s2(cdims,mdims);
    CPPUNIT_ASSERT(!s2.is_scalar());
    CPPUNIT_ASSERT(s2.rank() == 3);
    CPPUNIT_ASSERT(s2.size() == 120);

    CPPUNIT_ASSERT_THROW(h5dataspace(list_type{10,20},list_type{10}),
                         shape_mismatch_error);
    CPPUNIT_ASSERT_THROW(h5dataspace(list_type{10},list_type{100,200}),
                         shape_mismatch_error);
    CPPUNIT_ASSERT_THROW(h5dataspace(list_type{100},list_type{10}),
                         pni::io::object_error);
}

//----------------------------------------------------------------------------
void h5dataspace_test::test_current_iterator()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef std::list<hsize_t> list_type;
    list_type shape{20,40,10};

    h5dataspace space(shape);
    
    auto liter = shape.begin();
    auto siter = space.current_begin();
    for(;siter!=space.current_end();++siter,++liter)
        CPPUNIT_ASSERT(*siter == *liter);
}

//----------------------------------------------------------------------------
void h5dataspace_test::test_maximum_iterator()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef std::list<hsize_t> list_type;
    list_type shape{20,40,10};
    list_type mshape{200,400,100};

    h5dataspace space(shape,mshape);
    
    auto cliter = shape.begin();
    auto mliter = mshape.begin();
    auto citer = space.current_begin();
    auto miter = space.maximum_begin();
    for(;miter!=space.maximum_end();++cliter,++mliter,++citer,++miter)
    {
        CPPUNIT_ASSERT(*citer == *cliter);
        CPPUNIT_ASSERT(*miter == *mliter);
    }
}

//----------------------------------------------------------------------------
void h5dataspace_test::test_init_list_resize()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5dataspace space{10,20};
    
    CPPUNIT_ASSERT(space.current_dim(0) == 10);
    CPPUNIT_ASSERT(space.maximum_dim(0) == 10);
    CPPUNIT_ASSERT(space.current_dim(1) == 20);
    CPPUNIT_ASSERT(space.maximum_dim(1) == 20);

    space.resize({100,200});
    CPPUNIT_ASSERT(space.current_dim(0) == 100);
    CPPUNIT_ASSERT(space.maximum_dim(0) == 100);
    CPPUNIT_ASSERT(space.current_dim(1) == 200);
    CPPUNIT_ASSERT(space.maximum_dim(1) == 200);

    space.resize({10,20,30},{100,200,300});
    std::cerr<<space.rank()<<std::endl;
    CPPUNIT_ASSERT(space.rank()==3);
    CPPUNIT_ASSERT(space.current_dim(0) == 10);
    CPPUNIT_ASSERT(space.current_dim(1) == 20);
    CPPUNIT_ASSERT(space.current_dim(2) == 30);
                                
    CPPUNIT_ASSERT(space.maximum_dim(0) == 100);
    CPPUNIT_ASSERT(space.maximum_dim(1) == 200);
    CPPUNIT_ASSERT(space.maximum_dim(2) == 300);

    CPPUNIT_ASSERT_THROW(space.resize({10,20},{100}),shape_mismatch_error);
    CPPUNIT_ASSERT_THROW(space.resize({10},{100,200}),shape_mismatch_error);
    CPPUNIT_ASSERT_THROW(space.resize({101,20},{100,200}),
                         pni::io::object_error);
}

//----------------------------------------------------------------------------
void h5dataspace_test::test_container_resize()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef std::list<hsize_t> list_type;

    h5dataspace space{10,20};

    CPPUNIT_ASSERT_NO_THROW(space.resize(list_type{20,40,100}));
    CPPUNIT_ASSERT(space.rank()==3);
    CPPUNIT_ASSERT(space.current_dim(0) == 20);
    CPPUNIT_ASSERT(space.current_dim(1) == 40);
    CPPUNIT_ASSERT(space.current_dim(2) == 100);
    CPPUNIT_ASSERT(space.maximum_dim(0) == 20);
    CPPUNIT_ASSERT(space.maximum_dim(1) == 40);
    CPPUNIT_ASSERT(space.maximum_dim(2) == 100);

    CPPUNIT_ASSERT_NO_THROW(space.resize(list_type{10,30},
                                         list_type{100,300}));
    CPPUNIT_ASSERT(space.rank()==2);
    CPPUNIT_ASSERT(space.current_dim(0) == 10);
    CPPUNIT_ASSERT(space.current_dim(1) == 30);
    CPPUNIT_ASSERT(space.maximum_dim(0) == 100);
    CPPUNIT_ASSERT(space.maximum_dim(1) == 300);
    
    CPPUNIT_ASSERT_THROW(space.resize(list_type{10,30},list_type{10}),
                         shape_mismatch_error);
    CPPUNIT_ASSERT_THROW(space.resize(list_type{10},list_type{100,200}),
                          shape_mismatch_error);
    CPPUNIT_ASSERT_THROW(space.resize(list_type{100,10},list_type{10,200}),
                         pni::io::object_error);

}

//----------------------------------------------------------------------------
void h5dataspace_test::test_grow()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5dataspace space{{10,20},{100,200}};

    CPPUNIT_ASSERT_NO_THROW(space.grow(0));
    CPPUNIT_ASSERT(space.current_dim(0)==11);
    CPPUNIT_ASSERT_NO_THROW(space.grow(0,4));
    CPPUNIT_ASSERT(space.current_dim(0)==15);
    CPPUNIT_ASSERT_NO_THROW(space.grow(1,2));
    CPPUNIT_ASSERT(space.current_dim(1)==22);

    CPPUNIT_ASSERT_THROW(space.grow(0,100),pni::io::object_error);
    CPPUNIT_ASSERT_THROW(space.grow(10),index_error);
}
