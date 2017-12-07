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
//  Created on: Sep 16, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <boost/test/unit_test.hpp>
#include <pni/io/nx/algorithms/read.hpp>
#include <pni/io/nx/algorithms/write.hpp>

#include "../../base_fixture.hpp"
#include "../../multidim_policy.hpp"
#include "../../data_policy.hpp"
#include "../../nexus_lowlevel_test/test_types.hpp"

using namespace pni::core;
using namespace pni::io::nx;


struct read_write_test_fixture : base_fixture,
                                 multidim_policy,
                                 data_policy
                                
{
    read_write_test_fixture():
        base_fixture("read_write_test.nx"),
        multidim_policy(),
        data_policy()
    {}
};

BOOST_FIXTURE_TEST_SUITE(read_write_test,read_write_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_group,T,attribute_test_types)
    {
        typedef dynamic_array<T> array_type; 
        array_type a;

        BOOST_CHECK_THROW(read(h5::nxobject(root),a),type_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_field_full,T,field_test_types)
    {
        auto write_buffer = create_random_array<T>(shape);
        auto read_buffer = create_array<T>(shape);
        h5::nxfield field = root.create_field<T>("data",shape);
       
        BOOST_CHECK_NO_THROW(write(field,write_buffer));
        BOOST_CHECK_NO_THROW(read(field,read_buffer));

        BOOST_CHECK_EQUAL_COLLECTIONS(write_buffer.begin(),write_buffer.end(),
                                      read_buffer.begin(),read_buffer.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_field_object_full,T,field_test_types)
    {
        auto write_buffer = create_random_array<T>(shape);
        auto read_buffer = create_array<T>(shape);
        h5::nxobject field = root.create_field<T>("data",shape);
        
        BOOST_CHECK_NO_THROW(write(field,write_buffer));
        BOOST_CHECK_NO_THROW(read(field,read_buffer));

        BOOST_CHECK_EQUAL_COLLECTIONS(write_buffer.begin(),write_buffer.end(),
                                      read_buffer.begin(),read_buffer.end());
       
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_field_partial,T,field_test_types)
    {
        h5::nxfield field = root.create_field<T>("data",shape);
        auto read_buffer = create_array<T>(shape_t{4});

        for(size_t i=0;i<3;++i)
        {
            auto write_buffer = create_random_array<T>(shape_t{4});
            BOOST_CHECK_NO_THROW(write(field,write_buffer,i,slice(0,4)));
            BOOST_CHECK_NO_THROW(read(field,read_buffer,i,slice(0,4)));

            BOOST_CHECK_EQUAL_COLLECTIONS(write_buffer.begin(),write_buffer.end(),
                                          read_buffer.begin(),read_buffer.end());
        }
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_field_object_partial,T,field_test_types)
    {
        h5::nxobject field = root.create_field<T>("data",shape);
        auto read_buffer = create_array<T>(shape_t{4});

        for(size_t i=0;i<3;++i)
        {
            auto write_buffer = create_random_array<T>(shape_t{4});
            BOOST_CHECK_NO_THROW(write(field,write_buffer,i,slice(0,4)));
            BOOST_CHECK_NO_THROW(read(field,read_buffer,i,slice(0,4)));

            BOOST_CHECK_EQUAL_COLLECTIONS(write_buffer.begin(),write_buffer.end(),
                                          read_buffer.begin(),read_buffer.end());
        }
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_attribute_full,T,attribute_test_types)
    {
        auto write_buffer = create_random_array<T>(shape);
        auto read_buffer = create_array<T>(shape);
        h5::nxattribute attribute = root.attributes.create<T>("data",shape);
       
        BOOST_CHECK_NO_THROW(write(attribute,write_buffer));
        BOOST_CHECK_NO_THROW(read(attribute,read_buffer));

        BOOST_CHECK_EQUAL_COLLECTIONS(write_buffer.begin(),write_buffer.end(),
                                      read_buffer.begin(),read_buffer.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_attribute_object_full,T,attribute_test_types)
    {
        auto write_buffer = create_random_array<T>(shape);
        auto read_buffer = create_array<T>(shape);
        h5::nxobject attribute = root.attributes.create<T>("data",shape);
        
        BOOST_CHECK_NO_THROW(write(attribute,write_buffer));
        BOOST_CHECK_NO_THROW(read(attribute,read_buffer));

        BOOST_CHECK_EQUAL_COLLECTIONS(write_buffer.begin(),write_buffer.end(),
                                      read_buffer.begin(),read_buffer.end());
    }
    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_attribute_partial,T,attribute_test_types)
    {
        h5::nxattribute attribute = root.attributes.create<T>("data",shape);
        auto read_buffer = create_array<T>(shape_t{4});

        for(size_t i=0;i<3;++i)
        {
            auto write_buffer = create_random_array<T>(shape_t{4});
            BOOST_CHECK_NO_THROW(write(attribute,write_buffer,i,slice(0,4)));
            BOOST_CHECK_NO_THROW(read(attribute,read_buffer,i,slice(0,4)));

            BOOST_CHECK_EQUAL_COLLECTIONS(write_buffer.begin(),write_buffer.end(),
                                          read_buffer.begin(),read_buffer.end());
        }
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_attribute_object_partial,T,attribute_test_types)
    {
        h5::nxobject attribute = root.attributes.create<T>("data",shape);
        auto read_buffer = create_array<T>(shape_t{4});

        for(size_t i=0;i<3;++i)
        {
            auto write_buffer = create_random_array<T>(shape_t{4});
            BOOST_CHECK_NO_THROW(write(attribute,write_buffer,i,slice(0,4)));
            BOOST_CHECK_NO_THROW(read(attribute,read_buffer,i,slice(0,4)));

            BOOST_CHECK_EQUAL_COLLECTIONS(write_buffer.begin(),write_buffer.end(),
                                          read_buffer.begin(),read_buffer.end());
        }
    }
BOOST_AUTO_TEST_SUITE_END()


