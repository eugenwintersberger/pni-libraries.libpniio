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

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>
#include "test_types.hpp"
#include "nxfield_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct nxfield_inquiry_test_fixture : nxfield_test_fixture
{
    static const string fieldname;

    nxfield_inquiry_test_fixture():
        nxfield_test_fixture("nxfield_inquiry_test.nxs")
    {}
};

const string nxfield_inquiry_test_fixture::fieldname = "data";

BOOST_FIXTURE_TEST_SUITE(nxfield_inquiry_test,nxfield_inquiry_test_fixture)
    
    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_name,T,field_test_types)
    {
        h5::nxfield field = create_field<T>(fieldname,default_shape);
        BOOST_CHECK_EQUAL(field.name(),fieldname);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_filename,T,field_test_types)
    {
        h5::nxfield field = create_field<T>(fieldname,default_shape);
        BOOST_CHECK_EQUAL(field.filename(),filename);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_is_valid,T,field_test_types)
    {
        h5::nxfield f2; 
        BOOST_CHECK(!f2.is_valid());

        h5::nxfield field = create_field<T>(fieldname,default_shape);
        BOOST_CHECK(field.is_valid());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_size,T,field_test_types)
    {
        h5::nxfield field = create_field<T>(fieldname,default_shape);
        BOOST_CHECK_EQUAL(field.size(),default_size);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_rank,T,field_test_types)
    {
        h5::nxfield field = create_field<T>(fieldname,default_shape);
        BOOST_CHECK_EQUAL(field.rank(),2);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_shape,T,field_test_types)
    {
        h5::nxfield field = create_field<T>(fieldname,default_shape);
        auto rs = field.shape<shape_t>();
        BOOST_CHECK_EQUAL_COLLECTIONS(rs.begin(),rs.end(),
                                      default_shape.begin(),default_shape.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_type_id,T,field_test_types)
    {
        h5::nxfield field = create_field<T>(fieldname,default_shape);
        type_id_t tid = type_id_map<T>::type_id;
        BOOST_CHECK_EQUAL(field.type_id(),tid);
    }

BOOST_AUTO_TEST_SUITE_END()



