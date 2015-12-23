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
#include <pni/io/nx/h5/h5datatype.hpp>
#include <pni/io/nx/h5/h5dataspace.hpp>
#include <pni/io/nx/h5/attribute_utils.hpp>
#include <pni/io/nx/h5/object_imp.hpp>
#include <pni/io/nx/h5/hdf5_utilities.hpp>
#include "h5_imp_test_utils.hpp"

using namespace pni::core;
using namespace pni::io::nx;
using pni::io::object_error;
using pni::io::invalid_object_error;


struct hdf5_utilities_test_fixture
{
    h5::object_imp file;
    h5::object_imp root;
    h5::object_imp group;
    h5::object_imp dataset;
    h5::object_imp attribute;

    //-------------------------------------------------------------------------
    static h5::object_imp create_link_create_list()
    {
        h5::object_imp cplist{H5Pcreate(H5P_LINK_CREATE)};
        H5Pset_create_intermediate_group(cplist.id(),1);
        return cplist;
    }

    //-------------------------------------------------------------------------
    static h5::object_imp create_group(const h5::object_imp &parent, 
                                       const string &name) 
    {
        h5::object_imp cplist = create_link_create_list();
        return h5::object_imp{H5Gcreate2(parent.id(),name.c_str(),cplist.id(),
                              H5P_DEFAULT,H5P_DEFAULT)};
    }

    //-------------------------------------------------------------------------
    static h5::object_imp create_dataset(const h5::object_imp &parent,
                                         const string &name) 
    {
        h5::h5dataspace space;
        const h5::h5datatype &type = h5::get_type(type_id_t::FLOAT32);
        h5::object_imp cplist{H5Pcreate(H5P_DATASET_CREATE)};
        H5Pset_layout(cplist.id(),H5D_CHUNKED);
        h5::type_imp::index_vector_type cs{1};
        H5Pset_chunk(cplist.id(),1,cs.data());

        return h5::object_imp{H5Dcreate2(parent.id(),
                                         name.c_str(),
                                         type.object().id(),
                                         space.id(),
                                         H5P_DEFAULT,
                                         cplist.id(),
                                         H5P_DEFAULT)};
    }
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
    hdf5_utilities_test_fixture():
        file(h5::object_imp(H5Fcreate("hdf5_utilities_test.h5",H5F_ACC_TRUNC,
                            H5P_DEFAULT,H5P_DEFAULT))),
        root(h5::object_imp{H5Gopen2(file.id(),"/",H5P_DEFAULT)}),
        group(create_group(file,"/scan_1/detector/data")),
        dataset(create_dataset(group,"data")),
        attribute(create_attribute(dataset,"test"))
    {}

    ~hdf5_utilities_test_fixture()
    {
        group.close();
        attribute.close();
        dataset.close();
        root.close();
        file.close();
    }
};


BOOST_FIXTURE_TEST_SUITE(hdf5_utilities_test,hdf5_utilities_test_fixture)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_get_filename)
    {
        BOOST_CHECK_EQUAL(h5::get_filename(root),"hdf5_utilities_test.h5");
        BOOST_CHECK_EQUAL(h5::get_filename(group),"hdf5_utilities_test.h5");
        BOOST_CHECK_EQUAL(h5::get_filename(dataset),"hdf5_utilities_test.h5");
        BOOST_CHECK_EQUAL(h5::get_filename(attribute),"hdf5_utilities_test.h5");

        BOOST_CHECK_THROW(h5::get_filename(h5::object_imp()),invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_get_path)
    {
        BOOST_CHECK_EQUAL(h5::get_path(root),"/");
        BOOST_CHECK_EQUAL(h5::get_path(group),"/scan_1/detector/data");
        BOOST_CHECK_EQUAL(h5::get_path(dataset),"/scan_1/detector/data/data");

        BOOST_CHECK_THROW(h5::get_path(h5::object_imp()),invalid_object_error); 
        BOOST_CHECK_THROW(h5::get_path(attribute),type_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_get_name)
    {
        BOOST_CHECK_EQUAL(h5::get_name(root),"/");
        BOOST_CHECK_EQUAL(h5::get_name(group),"data");
        BOOST_CHECK_EQUAL(h5::get_name(dataset),"data");
        BOOST_CHECK_EQUAL(h5::get_name(attribute),"test");

        BOOST_CHECK_THROW(h5::get_name(h5::object_imp()),invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_get_parent)
    {
        BOOST_CHECK_EQUAL(h5::get_parent(root),root);
        BOOST_CHECK_EQUAL(h5::get_parent(dataset),group);
        BOOST_CHECK_EQUAL(h5::get_parent(attribute),dataset);

        h5::object_imp p{H5Gopen2(root.id(),"/scan_1/detector",H5P_DEFAULT)};
        BOOST_CHECK_EQUAL(h5::get_parent(group),p);

        BOOST_CHECK_THROW(h5::get_parent(h5::object_imp()),invalid_object_error);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_get_parent_path)
    {
        BOOST_CHECK_EQUAL(h5::get_parent_path(root),"/");
        BOOST_CHECK_EQUAL(h5::get_parent_path(dataset),"/scan_1/detector/data");
        BOOST_CHECK_EQUAL(h5::get_parent_path(group),"/scan_1/detector");

        BOOST_CHECK_THROW(h5::get_parent_path(h5::object_imp()),invalid_object_error);
        BOOST_CHECK_THROW(h5::get_parent_path(attribute),type_error);
    }

BOOST_AUTO_TEST_SUITE_END()
