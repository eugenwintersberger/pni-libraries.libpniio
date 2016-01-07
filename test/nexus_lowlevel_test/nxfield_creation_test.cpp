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

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/exceptions.hpp>
#include "test_types.hpp"
#include "base_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;
using pni::io::object_error;

struct nxfield_creation_test_fixture : base_fixture
{
    nxfield_creation_test_fixture():
        base_fixture("nxfield_creation_test.nxs")
    {}
};

BOOST_FIXTURE_TEST_SUITE(nxfield_creation_test,nxfield_creation_test_fixture)

    //------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_scalar,T,field_test_types)
    {
        h5::nxfield field;

        BOOST_CHECK_NO_THROW(field = root.create_field<T>("test"));
        BOOST_CHECK_EQUAL(field.size(),1);
        BOOST_CHECK_EQUAL(field.rank(),1);

        shape_t rs{1};
        auto s = field.shape<shape_t>();
        BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(),s.end(),rs.begin(),rs.end());

        //should throw - the field already exists
        BOOST_CHECK_THROW(root.create_field<T>("test"),object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_multidim_default_chunk,T,field_test_types)
    {
        h5::nxfield field;
        
        shape_t s{3,4};
        BOOST_CHECK_NO_THROW(field = root.create_field<T>("test",s));
        BOOST_CHECK_EQUAL(field.size(),12);
        BOOST_CHECK_EQUAL(field.rank(),2);

        auto rs = field.shape<shape_t>();
        BOOST_CHECK_EQUAL_COLLECTIONS(rs.begin(),rs.end(),s.begin(),s.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_multidim_custom_chunk,T,field_test_types)
    {
        h5::nxfield field;
        shape_t s{3,4},c{1,4};

        BOOST_CHECK_NO_THROW(field = root.create_field<T>("test",s,c));
        BOOST_CHECK_EQUAL(field.size(),12);
        BOOST_CHECK_EQUAL(field.rank(),2);

        auto rs = field.shape<shape_t>();
        BOOST_CHECK_EQUAL_COLLECTIONS(rs.begin(),rs.end(),s.begin(),s.end());

        //check error cases
        BOOST_CHECK_THROW(root.create_field<T>("error1",s,shape_t{4}),
                          size_mismatch_error);
        BOOST_CHECK_THROW(root.create_field<T>("test",s,c),object_error);

    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_multidim_default_chunk_filter,T,field_test_types)
    {
        h5::nxdeflate_filter filter(9,true);
        h5::nxfield field;
        shape_t s{3,4};

        BOOST_CHECK_NO_THROW(field = root.create_field<T>("test",s,filter));
        BOOST_CHECK_EQUAL(field.size(),12);
        BOOST_CHECK_EQUAL(field.rank(),2);

        auto rs = field.shape<shape_t>();
        BOOST_CHECK_EQUAL_COLLECTIONS(rs.begin(),rs.end(),s.begin(),s.end());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_multidim_custom_chunk_filter,T,field_test_types)
    {
        h5::nxdeflate_filter filter(9,true);
        h5::nxfield field;
        shape_t s{3,4},c{1,4};

        BOOST_CHECK_NO_THROW(field = root.create_field<T>("test",s,c,filter));
        BOOST_CHECK_EQUAL(field.size(),12);
        BOOST_CHECK_EQUAL(field.rank(),2);

        auto rs = field.shape<shape_t>();
        BOOST_CHECK_EQUAL_COLLECTIONS(rs.begin(),rs.end(),s.begin(),s.end());

        //check error cases
        BOOST_CHECK_THROW(root.create_field<T>("error1",s,shape_t{4},filter),
                             size_mismatch_error);
        BOOST_CHECK_THROW(root.create_field<T>("test",s,c,filter),object_error);
    }

BOOST_AUTO_TEST_SUITE_END()

