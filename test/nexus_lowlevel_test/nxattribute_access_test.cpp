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

#include<boost/test/unit_test.hpp>

#include <pni/io/nx/nx.hpp>
#include <pni/core/types.hpp>
#include "test_types.hpp"
#include "nxattribute_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct nxattribute_access_test_fixture : nxattribute_test_fixture
{
    static const std::vector<string> attr_names;

    nxattribute_access_test_fixture():
        nxattribute_test_fixture("nxattribute_access_test.nxs")
    {
        group.attributes.create<string>("attr1");
        group.attributes.create<float32>("temperature");
        group.attributes.create<float64>("matrix",default_shape);

        field.attributes.create<string>("attr1");
        field.attributes.create<float32>("temperature");
        field.attributes.create<float64>("matrix",default_shape);

    }
};

const std::vector<string> nxattribute_access_test_fixture::attr_names = 
{"attr1","matrix","temperature"};


BOOST_FIXTURE_TEST_SUITE(nxattribute_access_test,nxattribute_access_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_by_index,P,attr_parent_types)
    {
        P parent; 
        get_parent(parent);
        
        BOOST_CHECK_EQUAL(parent.attributes.size(),3);

        for(size_t index = 0; index < parent.attributes.size(); ++index)
            BOOST_CHECK_EQUAL(parent.attributes[index].name(),attr_names[index]);

        //try to create a new attribute of same name should throw
        BOOST_CHECK_THROW(parent.attributes[3],index_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_by_name,P,attr_parent_types)
    {
        P parent; 
        get_parent(parent);

        BOOST_CHECK_EQUAL(parent.attributes["attr1"].size(),1);
        BOOST_CHECK_EQUAL(parent.attributes["temperature"].size(),1);
        BOOST_CHECK_EQUAL(parent.attributes["matrix"].size(),12);

        BOOST_CHECK_THROW(parent.attributes["bla"],key_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_by_begin_end,P,attr_parent_types)
    {
        P parent;
        get_parent(parent);

        auto start_iter = parent.attributes.begin();
        auto end_iter   = parent.attributes.end();

        BOOST_CHECK_EQUAL(std::distance(start_iter,end_iter),3);
        
        auto name_iter = attr_names.begin();
        for(;start_iter != end_iter; ++start_iter,++name_iter)
            BOOST_CHECK_EQUAL((*start_iter).name(),*name_iter);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_by_foreach,P,attr_parent_types)
    {
        P parent;
        get_parent(parent);
        
        auto name_iter = attr_names.begin();
        for(auto attr: parent.attributes)
            BOOST_CHECK_EQUAL(attr.name(),*name_iter++);

    }

BOOST_AUTO_TEST_SUITE_END()
