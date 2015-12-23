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
// Created on: Jul 22, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/h5/h5datatype.hpp>
#include <pni/io/nx/h5/h5dataspace.hpp>
#include <pni/io/nx/h5/attribute_utils.hpp>
#include <pni/io/nx/h5/object_imp.hpp>
#include <pni/io/nx/h5/h5object_types.hpp>
#include <pni/core/types.hpp>
#include "h5_imp_test_utils.hpp"

using namespace pni::core;
using namespace pni::io::nx;

struct h5object_types_test_fixture
{
    h5::object_imp file;

    h5object_types_test_fixture():
        file(h5::object_imp(H5Fcreate("h5object_types_test.h5",H5F_ACC_TRUNC,
                               H5P_DEFAULT,H5P_DEFAULT)))
    {}

    ~h5object_types_test_fixture()
    {
        file.close();
    }
};

using pni::io::object_error;
using pni::io::invalid_object_error;

BOOST_FIXTURE_TEST_SUITE(h5object_types_test,h5object_types_test_fixture)


    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_plist)
    {
        h5::object_imp obj{H5Pcreate(H5P_FILE_CREATE)};
        BOOST_CHECK(obj.is_valid());
        BOOST_CHECK_EQUAL(h5::get_hdf5_type(obj),h5::h5object_type::PLIST);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_file)
    {
        BOOST_CHECK_EQUAL(h5::get_hdf5_type(file),h5::h5object_type::FILE);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_group)
    {
        h5::object_imp obj{H5Gcreate2(file.id(),"hello",H5P_DEFAULT,H5P_DEFAULT,
                               H5P_DEFAULT)};
        BOOST_CHECK_EQUAL(h5::get_hdf5_type(obj),h5::h5object_type::GROUP);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_dataset)
    {
        h5::h5dataspace space{{3,3}};
        const h5::h5datatype &type = h5::get_type(type_id_t::FLOAT32);
        h5::object_imp cplist{H5Pcreate(H5P_DATASET_CREATE)};
        H5Pset_layout(cplist.id(),H5D_CHUNKED);
        h5::type_imp::index_vector_type cs{1,3};
        H5Pset_chunk(cplist.id(),cs.size(),cs.data());


        h5::object_imp obj{H5Dcreate2(file.id(),"hello",
                                  type.object().id(),
                                  space.id(),
                                  H5P_DEFAULT,
                                  cplist.id(),
                                  H5P_DEFAULT)};
        BOOST_CHECK_EQUAL(h5::get_hdf5_type(obj),h5::h5object_type::DATASET);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_attribute)
    {
        h5::h5dataspace space{{3,3}};
        const h5::h5datatype &type = h5::get_type(type_id_t::INT16);

        h5::object_imp obj{h5::create_attribute(file,"test",type,space,false)};
        BOOST_CHECK_EQUAL(h5::get_hdf5_type(obj),h5::h5object_type::ATTRIBUTE);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_hdf5_type_datatype)
    {
        h5::h5datatype type = h5::make_type(type_id_t::COMPLEX128);
        BOOST_CHECK_EQUAL(h5::get_hdf5_type(type.object()),h5::h5object_type::DATATYPE);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_hdf5_type_dataspace)
    {
        h5::h5dataspace space{{1,2,3}};
        BOOST_CHECK_EQUAL(h5::get_hdf5_type(space.object()),h5::h5object_type::DATASPACE);
    }


    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nexus_file)
    {
        BOOST_CHECK_EQUAL(h5::get_nexus_type(file),nxobject_type::NXFILE);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nexus_attribute)
    {
    h5::h5dataspace space{{3,3}};
        const h5::h5datatype &type = h5::get_type(type_id_t::INT16);

        h5::object_imp obj{h5::create_attribute(file,"test",type,space,false)};
        BOOST_CHECK_EQUAL(h5::get_nexus_type(obj),nxobject_type::NXATTRIBUTE);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nexus_field)
    {
        h5::h5dataspace space{{3,3}};
        const h5::h5datatype &type = h5::get_type(type_id_t::FLOAT32);
        h5::object_imp cplist{H5Pcreate(H5P_DATASET_CREATE)};
        H5Pset_layout(cplist.id(),H5D_CHUNKED);
        h5::type_imp::index_vector_type cs{1,3};
        H5Pset_chunk(cplist.id(),cs.size(),cs.data());

        h5::object_imp obj{H5Dcreate2(file.id(),"hello",
                                  type.object().id(),
                                  space.id(),
                                  H5P_DEFAULT,
                                  cplist.id(),
                                  H5P_DEFAULT)};
        BOOST_CHECK_EQUAL(h5::get_nexus_type(obj),nxobject_type::NXFIELD);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nexus_group)
    {
        h5::object_imp obj{H5Gcreate2(file.id(),"hello",H5P_DEFAULT,
                                      H5P_DEFAULT,H5P_DEFAULT)};

        BOOST_CHECK_EQUAL(h5::get_nexus_type(obj),nxobject_type::NXGROUP);
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_nexus_type_error)
    {
        //trigger invalid_object_error
        h5::object_imp obj;

        BOOST_CHECK_THROW(h5::get_nexus_type(obj),invalid_object_error);

        //trigger a type error
        h5::h5datatype type = h5::make_type(type_id_t::FLOAT32);
        BOOST_CHECK_THROW(h5::get_nexus_type(type.object()),type_error);
    }

BOOST_AUTO_TEST_SUITE_END()
