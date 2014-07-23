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
#include "hdf5_utilities_test.hpp"
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/nxexceptions.hpp>
#include <pni/io/nx/h5/h5datatype.hpp>
#include <pni/io/nx/h5/h5dataspace.hpp>
#include <pni/io/nx/h5/attribute_utils.hpp>


CPPUNIT_TEST_SUITE_REGISTRATION(hdf5_utilities_test);

using pni::io::object_error;
using pni::io::invalid_object_error;

//-----------------------------------------------------------------------------
object_imp hdf5_utilities_test::create_link_create_list() const
{
    object_imp cplist{H5Pcreate(H5P_LINK_CREATE)};
    H5Pset_create_intermediate_group(cplist.id(),1);
    return cplist;
}

//-----------------------------------------------------------------------------
object_imp hdf5_utilities_test::create_group(const object_imp &parent,
                                             const string &name) const 
{
    object_imp cplist = create_link_create_list();
    return object_imp{H5Gcreate2(parent.id(),name.c_str(),cplist.id(),
                      H5P_DEFAULT,H5P_DEFAULT)};
}

//-----------------------------------------------------------------------------
object_imp hdf5_utilities_test::create_dataset(const object_imp &parent,
                                               const string &name) const
{
    object_imp cplist = create_link_create_list();
    h5dataspace space;
    const h5datatype &type = get_type(type_id_t::FLOAT32);

    return object_imp{H5Dcreate2(parent.id(),
                                 name.c_str(),
                                 type.object().id(),
                                 space.object().id(),
                                 H5P_DEFAULT,
                                 H5P_DEFAULT,
                                 H5P_DEFAULT)};
}

//-----------------------------------------------------------------------------
object_imp hdf5_utilities_test::create_attribute(const object_imp &parent,
                                                 const string &name) const
{
    h5dataspace space;
    const h5datatype &type = get_type(type_id_t::FLOAT32);

    return object_imp{H5Acreate(parent.id(),name.c_str(),
                                type.object().id(),
                                space.object().id(),
                                H5P_DEFAULT,H5P_DEFAULT)};
}

//-----------------------------------------------------------------------------
void hdf5_utilities_test::setUp()
{
    file = object_imp(H5Fcreate("hdf5_utilities_test.h5",H5F_ACC_TRUNC,
                               H5P_DEFAULT,H5P_DEFAULT));

    root = object_imp{H5Gopen2(file.id(),"/",H5P_DEFAULT)};

    group = create_group(file,"/scan_1/detector/data");
    dataset = create_dataset(group,"data");
    attribute = create_attribute(dataset,"test");
}

//-----------------------------------------------------------------------------
void hdf5_utilities_test::tearDown()
{
    group.close();
    attribute.close();
    dataset.close();
    root.close();
    file.close();
}

//----------------------------------------------------------------------------
void hdf5_utilities_test::test_get_filename()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    CPPUNIT_ASSERT(get_filename(root) == "hdf5_utilities_test.h5");
    CPPUNIT_ASSERT(get_filename(group)=="hdf5_utilities_test.h5");
    CPPUNIT_ASSERT(get_filename(dataset)=="hdf5_utilities_test.h5");
    CPPUNIT_ASSERT(get_filename(attribute)=="hdf5_utilities_test.h5");

    CPPUNIT_ASSERT_THROW(get_filename(object_imp()),invalid_object_error);
}

//----------------------------------------------------------------------------
void hdf5_utilities_test::test_get_path()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    CPPUNIT_ASSERT(get_path(root) == "/");
    CPPUNIT_ASSERT(get_path(group) == "/scan_1/detector/data");
    CPPUNIT_ASSERT(get_path(dataset) == "/scan_1/detector/data/data");

    CPPUNIT_ASSERT_THROW(get_path(object_imp()),invalid_object_error); 
}

//----------------------------------------------------------------------------
void hdf5_utilities_test::test_get_name()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    CPPUNIT_ASSERT(get_name(root) == "/");
    CPPUNIT_ASSERT(get_name(group)=="data");
    CPPUNIT_ASSERT(get_name(dataset) == "data");
    CPPUNIT_ASSERT(get_name(attribute) == "test");

    CPPUNIT_ASSERT_THROW(get_name(object_imp()),invalid_object_error);
}

//----------------------------------------------------------------------------
void hdf5_utilities_test::test_get_parent()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(get_parent(root) == root);
    CPPUNIT_ASSERT(get_parent(dataset) == group);
    CPPUNIT_ASSERT(get_parent(attribute) == dataset);

    object_imp p{H5Gopen2(root.id(),"/scan_1/detector",H5P_DEFAULT)};
    CPPUNIT_ASSERT(get_parent(group) == p);

    CPPUNIT_ASSERT_THROW(get_parent(object_imp()),invalid_object_error);

}

//----------------------------------------------------------------------------
void hdf5_utilities_test::test_get_parent_path()
{
    CPPUNIT_ASSERT(get_parent_path(root) == "/");
    CPPUNIT_ASSERT(get_parent_path(dataset) == "/scan_1/detector/data");
    CPPUNIT_ASSERT(get_parent_path(group) == "/scan_1/detector");

    CPPUNIT_ASSERT_THROW(get_parent_path(object_imp()),invalid_object_error);
}

