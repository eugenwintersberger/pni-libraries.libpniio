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
#include "attribute_utils_test.hpp"
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/nxexceptions.hpp>
#include <pni/io/nx/h5/h5datatype.hpp>
#include <pni/io/nx/h5/h5dataspace.hpp>
#include <pni/io/nx/h5/hdf5_utilities.hpp>
#include <pni/io/nx/h5/attribute_utils.hpp>
#include <pni/io/nx/nxobject_type.hpp>


CPPUNIT_TEST_SUITE_REGISTRATION(attribute_utils_test);

using pni::io::object_error;
using pni::io::invalid_object_error;

//-----------------------------------------------------------------------------
object_imp attribute_utils_test::create_attribute(const object_imp &parent,
                                                  const string &name) const
{
    h5dataspace space;
    const h5datatype &type = get_type(type_id_t::FLOAT32);

    return object_imp{H5Acreate(parent.id(),name.c_str(),
                                type.object().id(),
                                space.id(),
                                H5P_DEFAULT,H5P_DEFAULT)};
}

//-----------------------------------------------------------------------------
void attribute_utils_test::setUp()
{
    file = object_imp(H5Fcreate("hdf5_utilities_test.h5",H5F_ACC_TRUNC,
                               H5P_DEFAULT,H5P_DEFAULT));

    root = object_imp{H5Gopen2(file.id(),"/",H5P_DEFAULT)};

    attribute = create_attribute(root,"test");
}

//-----------------------------------------------------------------------------
void attribute_utils_test::tearDown()
{
    attribute.close();
    root.close();
    file.close();
}

//----------------------------------------------------------------------------
void attribute_utils_test::test_has_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    CPPUNIT_ASSERT(has_attribute(root,"test"));
    CPPUNIT_ASSERT(!has_attribute(root,"bla"));

    CPPUNIT_ASSERT_THROW(has_attribute(object_imp(),"test"),invalid_object_error);
}

//----------------------------------------------------------------------------
void attribute_utils_test::test_delete_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT_NO_THROW(delete_attribute(root,"test"));
    CPPUNIT_ASSERT(!has_attribute(root,"test"));

    CPPUNIT_ASSERT_THROW(delete_attribute(root,"test"),key_error);
    CPPUNIT_ASSERT_THROW(delete_attribute(object_imp(),"test"),invalid_object_error);
}

//-----------------------------------------------------------------------------
void attribute_utils_test::test_create_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    using pni::io::nx::h5::create_attribute;

    CPPUNIT_ASSERT(!has_attribute(root,"bla"));
    //set overwrite to false - should work as the attribute does not exist
    //yet
    CPPUNIT_ASSERT_NO_THROW(create_attribute(root,"bla",
                                             get_type(type_id_t::FLOAT32),
                                             h5dataspace(),
                                             false));
    CPPUNIT_ASSERT(has_attribute(root,"bla"));

    //must throw - attribute already exists
    CPPUNIT_ASSERT_THROW(create_attribute(root,"bla",
                                          get_type(type_id_t::FLOAT32),
                                          h5dataspace(),
                                          false),object_error);

    //must  not throw - overwrite existing attribute
    CPPUNIT_ASSERT_NO_THROW(create_attribute(root,"bla",
                                             get_type(type_id_t::INT16),
                                             h5dataspace(),
                                             true));

    CPPUNIT_ASSERT(has_attribute(root,"bla"));

    //must throw - attribute already exists
    CPPUNIT_ASSERT_THROW(create_attribute(object_imp(),"bla",
                                          get_type(type_id_t::FLOAT32),
                                          h5dataspace(),
                                          false),invalid_object_error);
    
}

//----------------------------------------------------------------------------
void attribute_utils_test::test_get_number_of_attributes()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    using pni::io::nx::h5::create_attribute;
    
    CPPUNIT_ASSERT(get_number_of_attributes(root)==1);

    CPPUNIT_ASSERT_NO_THROW(create_attribute(root,"bla",
                                             get_type(type_id_t::FLOAT32),
                                             h5dataspace(),
                                             false));
    CPPUNIT_ASSERT(get_number_of_attributes(root)==2);
    CPPUNIT_ASSERT_NO_THROW(delete_attribute(root,"bla"));
    CPPUNIT_ASSERT(get_number_of_attributes(root)==1);
    CPPUNIT_ASSERT_NO_THROW(delete_attribute(root,"test"));
    CPPUNIT_ASSERT(get_number_of_attributes(root)==0);

    CPPUNIT_ASSERT_THROW(get_number_of_attributes(object_imp()),invalid_object_error);
}

//----------------------------------------------------------------------------
void attribute_utils_test::test_get_attribute_by_name()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    object_imp att;
    CPPUNIT_ASSERT_NO_THROW(att = get_attribute_by_name(root,"test"));
    CPPUNIT_ASSERT(get_name(att) == "test");
    CPPUNIT_ASSERT(get_nexus_type(att) == pni::io::nx::nxobject_type::NXATTRIBUTE);

    CPPUNIT_ASSERT_THROW(get_attribute_by_name(root,"bla"),key_error);
    CPPUNIT_ASSERT_THROW(get_attribute_by_name(object_imp(),"test"),invalid_object_error);
}

//----------------------------------------------------------------------------
void attribute_utils_test::test_get_attribute_by_index()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    object_imp att;
    CPPUNIT_ASSERT_NO_THROW(att = get_attribute_by_index(root,0));
    CPPUNIT_ASSERT(get_name(att) == "test");
    CPPUNIT_ASSERT(get_nexus_type(att) == pni::io::nx::nxobject_type::NXATTRIBUTE);
    
    CPPUNIT_ASSERT_THROW(get_attribute_by_index(root,1),index_error);
    CPPUNIT_ASSERT_THROW(get_attribute_by_index(object_imp(),0),invalid_object_error);
}

