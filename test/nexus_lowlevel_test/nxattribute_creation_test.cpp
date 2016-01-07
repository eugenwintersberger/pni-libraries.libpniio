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
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/nx.hpp>

#include "test_types.hpp"
#include "nxattribute_test_fixture.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct nxattribute_creation_test_fixture : nxattribute_test_fixture
{
    nxattribute_creation_test_fixture():
        nxattribute_test_fixture("nxattribute_creation_test.nxs")
    {}
};

BOOST_FIXTURE_TEST_SUITE(nxattribute_creation_test,nxattribute_creation_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_scalar_no_overwrite,T,parent_attr_types)
    {
        typedef typename boost::mpl::front<T>::type parent_type;
        typedef typename boost::mpl::back<T>::type attribute_type;
        
        parent_type parent; 
        get_parent(parent);

        h5::nxattribute attr;
        BOOST_CHECK_NO_THROW(attr = parent.attributes.template create<attribute_type>("test"));
        BOOST_CHECK(attr.is_valid());
        BOOST_CHECK_EQUAL(attr.size(),1);
        type_id_t tid = type_id_map<attribute_type>::type_id;
        BOOST_CHECK_EQUAL(attr.type_id(),tid);

        //try to create a new attribute of same name should throw
        BOOST_CHECK_THROW(parent.attributes.template create<attribute_type>("test"),
                          pni::io::object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_scalar_with_overwrite,T,parent_attr_types)
    {
        typedef typename boost::mpl::front<T>::type parent_type;
        typedef typename boost::mpl::back<T>::type attribute_type;

        parent_type parent; 
        get_parent(parent);

        h5::nxattribute attr;
        BOOST_CHECK_NO_THROW(attr = parent.attributes.template create<attribute_type>("test"));
        BOOST_CHECK(attr.is_valid());
        BOOST_CHECK_EQUAL(attr.size() , 1);
        BOOST_CHECK_EQUAL(attr.rank() , 1);
        type_id_t tid = type_id_map<attribute_type>::type_id;
        BOOST_CHECK_EQUAL(attr.type_id() , tid);

        //try to create a new attribute of same name should throw
        BOOST_CHECK_NO_THROW(parent.attributes.template create<string>("test",true));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_multidim_no_overwrite,T,parent_attr_types)
    {
        typedef typename boost::mpl::front<T>::type parent_type;
        typedef typename boost::mpl::back<T>::type attribute_type;
        
        parent_type parent; 
        get_parent(parent);

        h5::nxattribute attr;
        BOOST_CHECK_NO_THROW(attr = parent.attributes.template create<attribute_type>("test",default_shape));
        BOOST_CHECK(attr.is_valid());
        BOOST_CHECK_EQUAL(attr.size() , default_size);
        type_id_t tid = type_id_map<attribute_type>::type_id;
        BOOST_CHECK_EQUAL(attr.type_id() , tid);

        auto a_shape = attr.template shape<shape_t>();
        BOOST_CHECK_EQUAL_COLLECTIONS(a_shape.begin(),a_shape.end(),
                                      default_shape.begin(),default_shape.end());

        //try to create a new attribute of same name should throw
        BOOST_CHECK_THROW(parent.attributes.template create<attribute_type>("test",default_shape),
                          pni::io::object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_multidim_with_overwrite,T,parent_attr_types)
    {
        typedef typename boost::mpl::front<T>::type parent_type;
        typedef typename boost::mpl::back<T>::type attribute_type;
        
        parent_type parent; 
        get_parent(parent);

        h5::nxattribute attr;
        BOOST_CHECK_NO_THROW(attr = parent.attributes.template
                                    create<attribute_type>("test",default_shape));
        BOOST_CHECK(attr.is_valid());
        BOOST_CHECK_EQUAL(attr.size(),default_size);
        type_id_t tid = type_id_map<attribute_type>::type_id;
        BOOST_CHECK_EQUAL(attr.type_id(),tid );

        auto a_shape = attr.template shape<shape_t>();
        BOOST_CHECK_EQUAL_COLLECTIONS(a_shape.begin(),a_shape.end(),
                                      default_shape.begin(),default_shape.end());

        //try to create a new attribute of same name should throw
        BOOST_CHECK_NO_THROW(parent.attributes.template
                create<string>("test",default_shape,true));
    }


    //----------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_construction,T,attribute_test_types)
    {
        auto attr1 = field.attributes.create<T>("test");

        //copy construction
        h5::nxattribute attr = attr1;
        BOOST_CHECK(attr.is_valid());
        BOOST_CHECK(attr1.is_valid());
        BOOST_CHECK_EQUAL(attr.name(),attr1.name());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_move_construction,T,attribute_test_types)
    {
        auto attr1 = field.attributes.create<T>("test");

        //copy construction
        h5::nxattribute attr = std::move(attr1);
        BOOST_CHECK(attr.is_valid());
        BOOST_CHECK(!attr1.is_valid());
        BOOST_CHECK_EQUAL(attr.name(),"test");
    }


BOOST_AUTO_TEST_SUITE_END()

