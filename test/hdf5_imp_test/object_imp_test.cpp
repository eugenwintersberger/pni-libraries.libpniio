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
#include "object_imp_test.hpp"
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/nxexceptions.hpp>


CPPUNIT_TEST_SUITE_REGISTRATION(object_imp_test);

using pni::io::object_error;
using pni::io::invalid_object_error;

//-----------------------------------------------------------------------------
void object_imp_test::setUp()
{
    file = H5Fcreate("h5object_Test.h5",H5F_ACC_TRUNC,H5P_DEFAULT,H5P_DEFAULT);
}

//-----------------------------------------------------------------------------
void object_imp_test::tearDown()
{
    H5Fclose(file);
}

//----------------------------------------------------------------------------
void object_imp_test::test_default()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    object_imp o;
    CPPUNIT_ASSERT(!o.is_valid());
    CPPUNIT_ASSERT_NO_THROW(o.close());
}

//----------------------------------------------------------------------------
void object_imp_test::test_create_from_dataset()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    object_imp group(H5Oopen(file,"/",H5P_DEFAULT));
    object_imp space(H5Screate(H5S_SCALAR));
    object_imp type(H5Tcopy(H5T_NATIVE_FLOAT));

    object_imp dataset(H5Dcreate2(group.id(),"test",type.id(),space.id(),
                     H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT));
    
    CPPUNIT_ASSERT(dataset.is_valid());
    CPPUNIT_ASSERT(get_hdf5_type(dataset) == h5object_type::DATASET);
    CPPUNIT_ASSERT(get_nexus_type(dataset) == 
                   pni::io::nx::nxobject_type::NXFIELD);
    CPPUNIT_ASSERT_NO_THROW(dataset.close());
    CPPUNIT_ASSERT(!dataset.is_valid());
}

//----------------------------------------------------------------------------
void object_imp_test::test_create_from_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    object_imp group(H5Oopen(file,"/",H5P_DEFAULT));
    object_imp space(H5Screate(H5S_SCALAR));
    object_imp type(H5Tcopy(H5T_NATIVE_FLOAT));

    object_imp attribute(H5Acreate2(group.id(),"test",type.id(),space.id(),
                       H5P_DEFAULT,H5P_DEFAULT));


    CPPUNIT_ASSERT(attribute.is_valid());
    CPPUNIT_ASSERT(get_hdf5_type(attribute) == h5object_type::ATTRIBUTE);
    CPPUNIT_ASSERT(get_nexus_type(attribute) == 
                   pni::io::nx::nxobject_type::NXATTRIBUTE);
    CPPUNIT_ASSERT_NO_THROW(attribute.close());
    CPPUNIT_ASSERT(!attribute.is_valid());
    
}

//----------------------------------------------------------------------------
void object_imp_test::test_create_from_dataspace()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    object_imp o(H5Screate(H5S_SCALAR));
    CPPUNIT_ASSERT(o.is_valid());
    CPPUNIT_ASSERT(get_hdf5_type(o) == h5object_type::DATASPACE);
    CPPUNIT_ASSERT_THROW(get_nexus_type(o),pni::core::type_error);
    CPPUNIT_ASSERT_NO_THROW(o.close());
    CPPUNIT_ASSERT(!o.is_valid());
}

//----------------------------------------------------------------------------
void object_imp_test::test_create_from_datatype()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    object_imp o(H5Tcopy(H5T_NATIVE_DOUBLE));
    
    CPPUNIT_ASSERT(o.is_valid());
    CPPUNIT_ASSERT(get_hdf5_type(o) == h5object_type::DATATYPE);
    CPPUNIT_ASSERT_THROW(get_nexus_type(o),pni::core::type_error);
    CPPUNIT_ASSERT_NO_THROW(o.close());
    CPPUNIT_ASSERT(!o.is_valid());
}

//----------------------------------------------------------------------------
void object_imp_test::test_create_from_file()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    object_imp o(H5Fcreate("test.h5",H5F_ACC_TRUNC,H5P_DEFAULT,H5P_DEFAULT));

    CPPUNIT_ASSERT(o.is_valid());
    CPPUNIT_ASSERT(get_hdf5_type(o) == h5object_type::FILE);
    CPPUNIT_ASSERT(get_nexus_type(o) == pni::io::nx::nxobject_type::NXFILE);
    CPPUNIT_ASSERT_NO_THROW(o.close());
    CPPUNIT_ASSERT(!o.is_valid());
}

//----------------------------------------------------------------------------
void object_imp_test::test_create_from_plist()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    object_imp o(H5Pcreate(H5P_DATASET_CREATE));

    CPPUNIT_ASSERT(o.is_valid());
    CPPUNIT_ASSERT(get_hdf5_type(o) == h5object_type::PLIST);
    CPPUNIT_ASSERT_THROW(get_nexus_type(o),pni::core::type_error);
    CPPUNIT_ASSERT_NO_THROW(o.close());
    CPPUNIT_ASSERT(!o.is_valid());
}

//----------------------------------------------------------------------------
void object_imp_test::test_move()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    object_imp o(H5Pcreate(H5P_DATASET_CREATE));
    {
        object_imp tmp(H5Tcopy(H5T_NATIVE_FLOAT));
        o = std::move(tmp);
        CPPUNIT_ASSERT(o.is_valid());
        CPPUNIT_ASSERT(!tmp.is_valid());
    }

    CPPUNIT_ASSERT(o.is_valid());
    CPPUNIT_ASSERT(get_hdf5_type(o)==h5object_type::DATATYPE);
}

//----------------------------------------------------------------------------
void object_imp_test::test_copy()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    object_imp o(H5Pcreate(H5P_DATASET_CREATE));
    object_imp o2(o);

    CPPUNIT_ASSERT(o==o2);

}
