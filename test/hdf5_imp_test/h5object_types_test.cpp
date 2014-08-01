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
#include "h5object_types_test.hpp"
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/nxexceptions.hpp>
#include <pni/io/nx/h5/h5datatype.hpp>
#include <pni/io/nx/h5/h5dataspace.hpp>
#include <pni/io/nx/h5/attribute_utils.hpp>


CPPUNIT_TEST_SUITE_REGISTRATION(h5object_types_test);

using pni::io::object_error;
using pni::io::invalid_object_error;

//-----------------------------------------------------------------------------
void h5object_types_test::setUp()
{
    file = object_imp(H5Fcreate("h5object_types_test.h5",H5F_ACC_TRUNC,
                               H5P_DEFAULT,H5P_DEFAULT));
}

//-----------------------------------------------------------------------------
void h5object_types_test::tearDown()
{
    file.close();
}

//----------------------------------------------------------------------------
void h5object_types_test::test_hdf5_type_plist()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    object_imp obj{H5Pcreate(H5P_FILE_CREATE)};
    CPPUNIT_ASSERT(obj.is_valid());
    CPPUNIT_ASSERT(get_hdf5_type(obj) == h5object_type::PLIST);
}

//----------------------------------------------------------------------------
void h5object_types_test::test_hdf5_type_file()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(get_hdf5_type(file) == h5object_type::FILE);
}

//----------------------------------------------------------------------------
void h5object_types_test::test_hdf5_type_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    object_imp obj{H5Gcreate2(file.id(),"hello",H5P_DEFAULT,H5P_DEFAULT,
                           H5P_DEFAULT)};
    CPPUNIT_ASSERT(get_hdf5_type(obj) == h5object_type::GROUP);
}

//----------------------------------------------------------------------------
void h5object_types_test::test_hdf5_type_dataset()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    h5dataspace space{{3,3}};
    const h5datatype &type = get_type(type_id_t::FLOAT32);
    object_imp cplist{H5Pcreate(H5P_DATASET_CREATE)};
    H5Pset_layout(cplist.id(),H5D_CHUNKED);
    type_imp::index_vector_type cs{1,3};
    H5Pset_chunk(cplist.id(),cs.size(),cs.data());


    object_imp obj{H5Dcreate2(file.id(),"hello",
                              type.object().id(),
                              space.id(),
                              H5P_DEFAULT,
                              cplist.id(),
                              H5P_DEFAULT)};
    CPPUNIT_ASSERT(get_hdf5_type(obj) == h5object_type::DATASET);
}

//----------------------------------------------------------------------------
void h5object_types_test::test_hdf5_type_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5dataspace space{{3,3}};
    const h5datatype &type = get_type(type_id_t::INT16);

    object_imp obj{create_attribute(file,"test",type,space,false)};
    CPPUNIT_ASSERT(get_hdf5_type(obj) == h5object_type::ATTRIBUTE);
}

//----------------------------------------------------------------------------
void h5object_types_test::test_hdf5_type_datatype()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    h5datatype type = make_type(type_id_t::COMPLEX128);
    CPPUNIT_ASSERT(get_hdf5_type(type.object()) == h5object_type::DATATYPE);
}

//----------------------------------------------------------------------------
void h5object_types_test::test_hdf5_type_dataspace()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    h5dataspace space{{1,2,3}};
    //CPPUNIT_ASSERT(get_hdf5_type(space.object()) == h5object_type::DATASPACE);
}

//----------------------------------------------------------------------------
void h5object_types_test::test_hdf5_type_error()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    //trigger invalid_object_error
    object_imp obj;

    CPPUNIT_ASSERT_THROW(get_hdf5_type(obj),invalid_object_error);

    //trigger a type error
    //HAVE CURRENTLY NO GOOD IDEA HOW TO TEST THIS
}

//----------------------------------------------------------------------------
void h5object_types_test::test_nexus_type_file()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(get_nexus_type(file) == pni::io::nx::nxobject_type::NXFILE);
}

//----------------------------------------------------------------------------
void h5object_types_test::test_nexus_type_attribute()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    h5dataspace space{{3,3}};
    const h5datatype &type = get_type(type_id_t::INT16);

    object_imp obj{create_attribute(file,"test",type,space,false)};
    CPPUNIT_ASSERT(get_nexus_type(obj) ==
            pni::io::nx::nxobject_type::NXATTRIBUTE);
}

//----------------------------------------------------------------------------
void h5object_types_test::test_nexus_type_field()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    h5dataspace space{{3,3}};
    const h5datatype &type = get_type(type_id_t::FLOAT32);
    object_imp cplist{H5Pcreate(H5P_DATASET_CREATE)};
    H5Pset_layout(cplist.id(),H5D_CHUNKED);
    type_imp::index_vector_type cs{1,3};
    H5Pset_chunk(cplist.id(),cs.size(),cs.data());

    object_imp obj{H5Dcreate2(file.id(),"hello",
                              type.object().id(),
                              space.id(),
                              H5P_DEFAULT,
                              cplist.id(),
                              H5P_DEFAULT)};
    CPPUNIT_ASSERT(get_nexus_type(obj) == pni::io::nx::nxobject_type::NXFIELD);
}

//----------------------------------------------------------------------------
void h5object_types_test::test_nexus_type_group()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    object_imp obj{H5Gcreate2(file.id(),"hello",H5P_DEFAULT,H5P_DEFAULT,
                           H5P_DEFAULT)};
    CPPUNIT_ASSERT(get_nexus_type(obj) == pni::io::nx::nxobject_type::NXGROUP);
}

//----------------------------------------------------------------------------
void h5object_types_test::test_nexus_type_error()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    //trigger invalid_object_error
    object_imp obj;

    CPPUNIT_ASSERT_THROW(get_nexus_type(obj),invalid_object_error);

    //trigger a type error
    h5datatype type = make_type(type_id_t::FLOAT32);
    CPPUNIT_ASSERT_THROW(get_nexus_type(type.object()),type_error);
}
