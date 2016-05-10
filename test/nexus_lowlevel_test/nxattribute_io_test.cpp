//
// Declaration of Nexus object template.
//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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

//implementation of the arrayshape test

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>
#include "../uniform_distribution.hpp"
#include "test_types.hpp"
#include "nxattribute_test_fixture.hpp"
#include "value_ref_test_tools.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct nxattribute_io_test_fixture : nxattribute_test_fixture
{
    nxattribute_io_test_fixture():
        nxattribute_test_fixture("nxattribute_io_test.nxs")
    {}
};

BOOST_FIXTURE_TEST_SUITE(nxattribute_io_test,nxattribute_io_test_fixture)

    //------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_mdarray,T,attribute_test_types)
    {
        auto attr = group.attributes.create<T>("a1",default_shape);
        auto write_data = create_random_array<T>(default_shape);
        auto read_data  = create_array<T>(default_shape);

        //write data
        BOOST_CHECK_NO_THROW(attr.write(write_data));
        //read data
        BOOST_CHECK_NO_THROW(attr.read(read_data));
        BOOST_CHECK_EQUAL_COLLECTIONS(read_data.begin(),read_data.end(),
                                      write_data.begin(),write_data.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_mdarray_error,T,attribute_test_types)
    {
        auto attr = group.attributes.create<T>("a1",default_shape);

        T scalar_value;
        BOOST_CHECK_THROW(attr.write(scalar_value),size_mismatch_error);
        BOOST_CHECK_THROW(attr.read(scalar_value),size_mismatch_error);

        auto wrong_size = create_array<T>(shape_t{10});
        BOOST_CHECK_THROW(attr.write(wrong_size),size_mismatch_error);
        BOOST_CHECK_THROW(attr.read(wrong_size),size_mismatch_error);

        wrong_size = create_array<T>(shape_t{10,100});
        BOOST_CHECK_THROW(attr.write(wrong_size),size_mismatch_error);
        BOOST_CHECK_THROW(attr.read(wrong_size),size_mismatch_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_array,T,attribute_test_types)
    {
        auto attr = group.attributes.create<T>("a1",default_shape);
        array write_data(create_random_array<T>(default_shape));
        array read_data(create_array<T>(default_shape));

        //write data
        BOOST_CHECK_NO_THROW(attr.write(write_data));
        //read data
        BOOST_CHECK_NO_THROW(attr.read(read_data));

        //compare data
        BOOST_CHECK_EQUAL_COLLECTIONS(read_data.begin(),read_data.end(),
                                      write_data.begin(),write_data.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_array_error,T,attribute_test_types)
    {
        auto attr = group.attributes.create<T>("a1",default_shape);

        array a(create_array<T>(shape_t{4}));
        BOOST_CHECK_THROW(attr.write(a),size_mismatch_error);

        a = array(create_array<T>(shape_t{10,20}));
        BOOST_CHECK_THROW(attr.write(a),size_mismatch_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_pointer,T,attribute_test_types)
    {
        auto attr = group.attributes.create<T>("a1",default_shape);

        auto write_data = create_random_buffer<T>(default_size);
        auto read_data  = create_buffer<T>(default_size);

        //write data
        BOOST_CHECK_NO_THROW(attr.write(write_data.size(),write_data.data()));
        //read data
        BOOST_CHECK_NO_THROW(attr.read(read_data.size(),read_data.data()));

        //compare data
        BOOST_CHECK_EQUAL_COLLECTIONS(read_data.begin(),read_data.end(),
                                      write_data.begin(),write_data.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_pointer_error,T,attribute_test_types)
    {
        auto attr = group.attributes.create<T>("a1",default_shape);

        auto data = create_random_buffer<T>(default_size);
        
        BOOST_CHECK_THROW(attr.write(default_size+3,data.data()),
                          size_mismatch_error);
        BOOST_CHECK_THROW(attr.write(default_size-1,data.data()),
                          size_mismatch_error);

        BOOST_CHECK_THROW(attr.read(default_size+3,data.data()),
                          size_mismatch_error);
        BOOST_CHECK_THROW(attr.read(default_size-1,data.data()),
                          size_mismatch_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_scalar,T,attribute_test_types)
    {
        auto attr = group.attributes.create<T>("a1");;
       
        auto write_data = create_random_scalar<T>();
        T read_data;

        BOOST_CHECK_NO_THROW(attr.write(write_data));
        BOOST_CHECK_NO_THROW(attr.read(read_data));

        BOOST_CHECK_EQUAL(read_data,write_data);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_scalar_error,T,attribute_test_types)
    {
        auto attr = group.attributes.create<T>("a1",default_shape);
        
        T data;
        BOOST_CHECK_THROW(attr.read(data),size_mismatch_error);
        BOOST_CHECK_THROW(attr.write(data),size_mismatch_error);
    }

BOOST_AUTO_TEST_SUITE_END()


