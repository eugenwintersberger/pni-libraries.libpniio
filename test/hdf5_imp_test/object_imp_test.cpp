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
// Created on: Jul 14, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/h5/object_imp.hpp>
#include <iostream>
#include "h5_imp_test_utils.hpp"

using namespace pni::core;
using namespace pni::io::nx;


struct object_imp_test_fixture
{
    hid_t file;

    object_imp_test_fixture():
        file(H5Fcreate("h5object_Test.h5",H5F_ACC_TRUNC,H5P_DEFAULT,H5P_DEFAULT))
    {}

    ~object_imp_test_fixture()
    {
        H5Fclose(file);
    }
};

BOOST_FIXTURE_TEST_SUITE(object_imp_test,object_imp_test_fixture)


    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_default)
    {
        h5::object_imp o;
        BOOST_CHECK(!o.is_valid());
        BOOST_CHECK_NO_THROW(o.close());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_create_from_dataset)
    {
        h5::object_imp group(H5Oopen(file,"/",H5P_DEFAULT));
        h5::object_imp space(H5Screate(H5S_SCALAR));
        h5::object_imp type(H5Tcopy(H5T_NATIVE_FLOAT));

        h5::object_imp dataset(H5Dcreate2(group.id(),"test",type.id(),space.id(),
                         H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT));
        
        BOOST_CHECK(dataset.is_valid());
        BOOST_CHECK_EQUAL(get_hdf5_type(dataset),h5::h5object_type::DATASET);
        BOOST_CHECK_EQUAL(get_nexus_type(dataset),nxobject_type::NXFIELD);
        BOOST_CHECK_NO_THROW(dataset.close());
        BOOST_CHECK(!dataset.is_valid());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_create_from_attribute)
    {
        h5::object_imp group(H5Oopen(file,"/",H5P_DEFAULT));
        h5::object_imp space(H5Screate(H5S_SCALAR));
        h5::object_imp type(H5Tcopy(H5T_NATIVE_FLOAT));

        h5::object_imp attribute(H5Acreate2(group.id(),"test",type.id(),space.id(),
                           H5P_DEFAULT,H5P_DEFAULT));


        BOOST_CHECK(attribute.is_valid());
        BOOST_CHECK_EQUAL(get_hdf5_type(attribute),h5::h5object_type::ATTRIBUTE);
        BOOST_CHECK_EQUAL(get_nexus_type(attribute),nxobject_type::NXATTRIBUTE);
        BOOST_CHECK_NO_THROW(attribute.close());
        BOOST_CHECK(!attribute.is_valid());
        
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_create_from_dataspace)
    {
        h5::object_imp o(H5Screate(H5S_SCALAR));
        BOOST_CHECK(o.is_valid());
        BOOST_CHECK_EQUAL(get_hdf5_type(o),h5::h5object_type::DATASPACE);
        BOOST_CHECK_THROW(get_nexus_type(o),type_error);
        BOOST_CHECK_NO_THROW(o.close());
        BOOST_CHECK(!o.is_valid());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_create_from_datatype)
    {
        h5::object_imp o(H5Tcopy(H5T_NATIVE_DOUBLE));
        
        BOOST_CHECK(o.is_valid());
        BOOST_CHECK_EQUAL(get_hdf5_type(o),h5::h5object_type::DATATYPE);
        BOOST_CHECK_THROW(get_nexus_type(o),type_error);
        BOOST_CHECK_NO_THROW(o.close());
        BOOST_CHECK(!o.is_valid());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_create_from_file)
    {
        h5::object_imp o(H5Fcreate("test.h5",H5F_ACC_TRUNC,H5P_DEFAULT,H5P_DEFAULT));

        BOOST_CHECK(o.is_valid());
        BOOST_CHECK_EQUAL(get_hdf5_type(o),h5::h5object_type::FILE);
        BOOST_CHECK_EQUAL(get_nexus_type(o),nxobject_type::NXFILE);
        BOOST_CHECK_NO_THROW(o.close());
        BOOST_CHECK(!o.is_valid());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_create_from_plist)
    {
        h5::object_imp o(H5Pcreate(H5P_DATASET_CREATE));

        BOOST_CHECK(o.is_valid());
        BOOST_CHECK_EQUAL(get_hdf5_type(o),h5::h5object_type::PLIST);
        BOOST_CHECK_THROW(get_nexus_type(o),type_error);
        BOOST_CHECK_NO_THROW(o.close());
        BOOST_CHECK(!o.is_valid());
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_move)
    {
        h5::object_imp o(H5Pcreate(H5P_DATASET_CREATE));
        {
            h5::object_imp tmp(H5Tcopy(H5T_NATIVE_FLOAT));
            o = std::move(tmp);
            BOOST_CHECK(o.is_valid());
            BOOST_CHECK(!tmp.is_valid());
        }

        BOOST_CHECK(o.is_valid());
        BOOST_CHECK_EQUAL(get_hdf5_type(o),h5::h5object_type::DATATYPE);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_copy)
    {
        h5::object_imp o(H5Pcreate(H5P_DATASET_CREATE));
        h5::object_imp o2(o);

        BOOST_CHECK_EQUAL(o,o2);

    }

BOOST_AUTO_TEST_SUITE_END()
