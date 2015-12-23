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
// Created on: Jul 23, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/h5/object_imp.hpp>
#include <pni/io/nx/h5/attribute_utils.hpp>
#include <pni/io/nx/h5/h5datatype.hpp>
#include <pni/io/nx/h5/h5dataspace.hpp>
#include <pni/io/nx/h5/hdf5_utilities.hpp>
#include <pni/io/nx/h5/attribute_utils.hpp>
#include <pni/io/nx/nxobject_type.hpp>
#include "h5_imp_test_utils.hpp"

using namespace pni::core;
using namespace pni::io::nx;
using pni::io::object_error;
using pni::io::invalid_object_error;

struct attribute_utils_test_fixture
{
    h5::object_imp file;
    h5::object_imp root;
    h5::object_imp attribute;

    //-------------------------------------------------------------------------
    static h5::object_imp create_attribute(const h5::object_imp &parent,
                                           const string &name) 
    {
        h5::h5dataspace space;
        const h5::h5datatype &type = h5::get_type(type_id_t::FLOAT32);

        return h5::object_imp{H5Acreate(parent.id(),name.c_str(),
                                        type.object().id(),
                                        space.id(),
                                        H5P_DEFAULT,H5P_DEFAULT)};
    }

    //-------------------------------------------------------------------------
    attribute_utils_test_fixture():
        file(h5::object_imp(H5Fcreate("hdf5_utilities_test.h5",H5F_ACC_TRUNC,
                                      H5P_DEFAULT,H5P_DEFAULT))),
        root(h5::object_imp{H5Gopen2(file.id(),"/",H5P_DEFAULT)}),
        attribute(create_attribute(root,"test"))
    { }
    //-------------------------------------------------------------------------
    ~attribute_utils_test_fixture()
    {
        attribute.close();
        root.close();
        file.close();
    }
};


BOOST_FIXTURE_TEST_SUITE(attribute_utils_test,attribute_utils_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_has_attribute)
    {
        BOOST_CHECK(h5::has_attribute(root,"test"));
        BOOST_CHECK(!h5::has_attribute(root,"bla"));

        BOOST_CHECK_THROW(h5::has_attribute(h5::object_imp(),"test"),
                          invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_delete_attribute)
    {
        BOOST_CHECK_NO_THROW(h5::delete_attribute(root,"test"));
        BOOST_CHECK(!h5::has_attribute(root,"test"));

        BOOST_CHECK_THROW(h5::delete_attribute(root,"test"),key_error);
        BOOST_CHECK_THROW(h5::delete_attribute(h5::object_imp(),"test"),
                          invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_create_attribute)
    {
        using pni::io::nx::h5::create_attribute;

        BOOST_CHECK(!h5::has_attribute(root,"bla"));
        //set overwrite to false - should work as the attribute does not exist
        //yet
        BOOST_CHECK_NO_THROW(create_attribute(root,"bla",
                                              h5::get_type(type_id_t::FLOAT32),
                                              h5::h5dataspace(),
                                              false));
        BOOST_CHECK(h5::has_attribute(root,"bla"));

        //must throw - attribute already exists
        BOOST_CHECK_THROW(create_attribute(root,"bla",
                                           h5::get_type(type_id_t::FLOAT32),
                                           h5::h5dataspace(),
                                           false),object_error);

        //must  not throw - overwrite existing attribute
        BOOST_CHECK_NO_THROW(create_attribute(root,"bla",
                                              h5::get_type(type_id_t::INT16),
                                              h5::h5dataspace(),
                                              true));

        BOOST_CHECK(h5::has_attribute(root,"bla"));

        //must throw - attribute already exists
        BOOST_CHECK_THROW(create_attribute(h5::object_imp(),"bla",
                                           h5::get_type(type_id_t::FLOAT32),
                                           h5::h5dataspace(),
                                           false),invalid_object_error);
        
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_get_number_of_attributes)
    {
        using pni::io::nx::h5::create_attribute;
        
        BOOST_CHECK_EQUAL(get_number_of_attributes(root),1);

        BOOST_CHECK_NO_THROW(create_attribute(root,"bla",
                                              h5::get_type(type_id_t::FLOAT32),
                                              h5::h5dataspace(),
                                              false));
        BOOST_CHECK_EQUAL(h5::get_number_of_attributes(root),2);
        BOOST_CHECK_NO_THROW(h5::delete_attribute(root,"bla"));
        BOOST_CHECK_EQUAL(h5::get_number_of_attributes(root),1);
        BOOST_CHECK_NO_THROW(h5::delete_attribute(root,"test"));
        BOOST_CHECK_EQUAL(h5::get_number_of_attributes(root),0);

        BOOST_CHECK_THROW(h5::get_number_of_attributes(h5::object_imp()),
                          invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_get_attribute_by_name)
    {
        h5::object_imp att;
        BOOST_CHECK_NO_THROW(att = h5::get_attribute_by_name(root,"test"));
        BOOST_CHECK_EQUAL(h5::get_name(att),"test");
        BOOST_CHECK_EQUAL(h5::get_nexus_type(att),nxobject_type::NXATTRIBUTE);

        BOOST_CHECK_THROW(h5::get_attribute_by_name(root,"bla"),key_error);
        BOOST_CHECK_THROW(h5::get_attribute_by_name(h5::object_imp(),"test"),
                          invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_get_attribute_by_index)
    {
        h5::object_imp att;
        BOOST_CHECK_NO_THROW(att = h5::get_attribute_by_index(root,0));
        BOOST_CHECK_EQUAL(h5::get_name(att),"test");
        BOOST_CHECK_EQUAL(h5::get_nexus_type(att),nxobject_type::NXATTRIBUTE);
        
        BOOST_CHECK_THROW(h5::get_attribute_by_index(root,1),index_error);
        BOOST_CHECK_THROW(h5::get_attribute_by_index(h5::object_imp(),0),
                          invalid_object_error);
    }

BOOST_AUTO_TEST_SUITE_END()

