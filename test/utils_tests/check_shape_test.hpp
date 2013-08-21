/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jul 10, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include <type_traits>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/utils/types.hpp>
#include <pni/io/nx/nexus_utils.hpp>

using namespace pni::core;
using namespace pni::io::nx;


/*!
\ingroup nexus_utility_tests
\brief test for shape check

Test the check_shape function template between different in memory
container and Nexus objects as well as among the container objects themselves. 

Here we have to check basically two features:



As Nexus objects we consider fields and attributes where two of each are created
with a size of 25 and 36 elements. 

Here we assume that TA is one of our array types while TB can be everything that
has a size member function.

\tparam TA container type 1
\tparam TB container type 2
*/
template<typename TA,typename TB>
class check_shape_test : public CppUnit::TestFixture
{
        typedef check_shape_test<TA,TB> this_test_t;
        CPPUNIT_TEST_SUITE(this_test_t);
        CPPUNIT_TEST(test_no_throw_containers);
        CPPUNIT_TEST(test_no_throw_nexus);
        CPPUNIT_TEST(test_no_throw_mixed);
        CPPUNIT_TEST(test_throw_containers);
        CPPUNIT_TEST(test_throw_nexus);
        CPPUNIT_TEST(test_throw_mixed);
        CPPUNIT_TEST_SUITE_END();
        
        h5::nxfile file;
        h5::nxfield field1,field2,field3,field4;
        h5::nxattribute attribute1,attribute2,
                        attribute3,attribute4;

        shape_t s1;
        shape_t s2;
        shape_t s3;
        shape_t s4;

        TA a1,a2,a3,a4;
        TB b1,b2,b3,b4;

        //need some special functions 
        template<typename T,typename STORAGE,typename IMAP>
        static void create_container(const shape_t &s,darray<T,STORAGE,IMAP> &a)
        {
            a = darray<T,STORAGE,IMAP>(s);
        }

        template<typename ATYPE>
        static void create_container(const shape_t &s,numarray<ATYPE> &a )
        {
            a = numarray<ATYPE>(s);
        }
        
    public:
        void setUp();
        void tearDown();
        
        void test_throw();

        //----------------------tests for non-throwing checks---------------
        /*!
        \brief test containers

        Test non-throwing check template for containers.
        */
        void test_no_throw_containers();

        /*!
        \brief test nexus objects

        Test non-throwing check template for nexus objects.
        */
        void test_no_throw_nexus();

        /*!
        \brief test all objects

        Test non-throwin check template with all objects together. 
        */
        void test_no_throw_mixed();
        
        //----------------------tests for throwing checks---------------
        /*!
        \brief test containers

        Test throwing check template for containers.
        */
        void test_throw_containers();

        /*!
        \brief test nexus objects

        Test throwing check template for nexus objects.
        */
        void test_throw_nexus();

        /*!
        \brief test all objects

        Test throwing check template with all objects together. 
        */
        void test_throw_mixed();
};

//-----------------------------------------------------------------------------
template<typename TA,typename TB> void check_shape_test<TA,TB>::setUp()
{
    s1 = shape_t{6,5};
    s2 = shape_t{6};
    s3 = shape_t{7,10};
    s4 = shape_t{100};

    file = h5::nxfile::create_file("check_size_test.nx",true);
    field1 = file.create_field<uint8>("field1",s1);
    field2 = file.create_field<float64>("field2",s2);
    field3 = file.create_field<uint32>("field3",s3);
    field4 = file.create_field<complex32>("field4",s4);

    attribute1 = field1.attr<float32>("attr",s1);
    attribute2 = field2.attr<int64>("attr",s2);
    attribute3 = field3.attr<int8>("attr",s3);
    attribute4 = field4.attr<string>("attr",s4);

    create_container(s1,a1);
    create_container(s2,a2);
    create_container(s3,a3);
    create_container(s4,a4);

    create_container(s1,b1);
    create_container(s2,b2);
    create_container(s3,b3);
    create_container(s4,b4);

}

//-----------------------------------------------------------------------------
template<typename TA,typename TB> void check_shape_test<TA,TB>::tearDown()
{
    //close all Nexus objects
    attribute1.close();
    attribute2.close();
    attribute3.close();
    attribute4.close();
    field1.close();
    field2.close();
    field3.close();
    field4.close();

    file.close();


}

//-----------------------------------------------------------------------------
template<typename TA,typename TB> 
void check_shape_test<TA,TB>::test_throw_containers()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //fine - have same shape
    CPPUNIT_ASSERT_NO_THROW(check_shape(a1,b1,EXCEPTION_RECORD));

    //not fine - have already different rank
    CPPUNIT_ASSERT_THROW(check_shape(a1,b2,EXCEPTION_RECORD),shape_mismatch_error);

    //not fine - have same rank but different shape
    CPPUNIT_ASSERT_THROW(check_shape(a1,b3,EXCEPTION_RECORD),shape_mismatch_error);

    //that was so far easy - now we have to consider selections
    CPPUNIT_ASSERT_NO_THROW(check_shape(a2,b4(slice(0,6)),EXCEPTION_RECORD));
    CPPUNIT_ASSERT_THROW(check_shape(a2,b4(slice(0,7)),EXCEPTION_RECORD),
                         shape_mismatch_error);
}

//-----------------------------------------------------------------------------
template<typename TA,typename TB>
void check_shape_test<TA,TB>::test_throw_nexus()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //-------------------start with fields--------------------------------
    //this is fine
    CPPUNIT_ASSERT_NO_THROW(check_shape(field1,field1,EXCEPTION_RECORD));

    //different rank
    CPPUNIT_ASSERT_THROW(check_shape(field1,field2,EXCEPTION_RECORD),
                         shape_mismatch_error);

    //same rank but different number of elements along each dimension
    CPPUNIT_ASSERT_THROW(check_shape(field1,field3,EXCEPTION_RECORD),
                         shape_mismatch_error);

    //now with selections
    CPPUNIT_ASSERT_NO_THROW(check_shape(field2,field4(slice(0,6)),
                            EXCEPTION_RECORD));
    CPPUNIT_ASSERT_THROW(check_shape(field2,field4(slice(0,7)),
                         EXCEPTION_RECORD),shape_mismatch_error);

    //---------------------now the attributes------------------------------
    //this is fine
    CPPUNIT_ASSERT_NO_THROW(check_shape(attribute1,attribute1,
                            EXCEPTION_RECORD));

    //different rank
    CPPUNIT_ASSERT_THROW(check_shape(attribute1,attribute2,EXCEPTION_RECORD),
                         shape_mismatch_error);

    //same rank but different number of elements along each dimension
    CPPUNIT_ASSERT_THROW(check_shape(attribute1,attribute3,EXCEPTION_RECORD),
                         shape_mismatch_error);

    //as attributes currently do not support partial IO we do not have to check
    //any selection mechanism.

}

//-----------------------------------------------------------------------------
template<typename TA,typename TB>
void check_shape_test<TA,TB>::test_throw_mixed()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //---------------check fields and containers--------------------------
    //fine - same rank, same number of elements
    CPPUNIT_ASSERT_NO_THROW(check_shape(field1,a1,EXCEPTION_RECORD));
    CPPUNIT_ASSERT_NO_THROW(check_shape(b1,field1,EXCEPTION_RECORD));

    //different rank - must fail
    CPPUNIT_ASSERT_THROW(check_shape(a2,field1,EXCEPTION_RECORD),shape_mismatch_error);
    CPPUNIT_ASSERT_THROW(check_shape(b2,field1,EXCEPTION_RECORD),shape_mismatch_error);

    //same rank but different number of elements
    CPPUNIT_ASSERT_THROW(check_shape(a3,field1,EXCEPTION_RECORD),shape_mismatch_error);
    CPPUNIT_ASSERT_THROW(check_shape(b3,field1,EXCEPTION_RECORD),shape_mismatch_error);

    //for fields we still need to check for selections
    CPPUNIT_ASSERT_NO_THROW(check_shape(a2,field4(slice(0,6)),EXCEPTION_RECORD));
    CPPUNIT_ASSERT_THROW(check_shape(a2,field4(slice(0,7)),EXCEPTION_RECORD),
                         shape_mismatch_error);

    //--------------check with attributes----------------------------------
    //fine - same rank, same number of elements
    CPPUNIT_ASSERT_NO_THROW(check_shape(attribute1,a1,EXCEPTION_RECORD));
    CPPUNIT_ASSERT_NO_THROW(check_shape(b1,attribute1,EXCEPTION_RECORD));

    //different rank - must fail
    CPPUNIT_ASSERT_THROW(check_shape(a2,attribute1,EXCEPTION_RECORD),shape_mismatch_error);
    CPPUNIT_ASSERT_THROW(check_shape(b2,attribute1,EXCEPTION_RECORD),shape_mismatch_error);

    //same rank but different number of elements
    CPPUNIT_ASSERT_THROW(check_shape(a3,attribute1,EXCEPTION_RECORD),shape_mismatch_error);
    CPPUNIT_ASSERT_THROW(check_shape(b3,attribute1,EXCEPTION_RECORD),shape_mismatch_error);
}
//-----------------------------------------------------------------------------
template<typename TA,typename TB> 
void check_shape_test<TA,TB>::test_no_throw_containers()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //fine - have same shape
    CPPUNIT_ASSERT(check_shape(a1,b1));

    //not fine - have already different rank
    CPPUNIT_ASSERT(!check_shape(a1,b2));

    //not fine - have same rank but different shape
    CPPUNIT_ASSERT(!check_shape(a1,b3));

    //that was so far easy - now we have to consider selections
    CPPUNIT_ASSERT(check_shape(a2,b4(slice(0,6))));
    CPPUNIT_ASSERT(!check_shape(a2,b4(slice(0,7))));
}

//-----------------------------------------------------------------------------
template<typename TA,typename TB>
void check_shape_test<TA,TB>::test_no_throw_nexus()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //-------------------start with fields--------------------------------
    //this is fine
    CPPUNIT_ASSERT(check_shape(field1,field1));

    //different rank
    CPPUNIT_ASSERT(!check_shape(field1,field2));

    //same rank but different number of elements along each dimension
    CPPUNIT_ASSERT(!check_shape(field1,field3));

    //now with selections
    CPPUNIT_ASSERT(check_shape(field2,field4(slice(0,6))));
    CPPUNIT_ASSERT(!check_shape(field2,field4(slice(0,7))));

    //---------------------now the attributes------------------------------
    //this is fine
    CPPUNIT_ASSERT(check_shape(attribute1,attribute1));

    //different rank
    CPPUNIT_ASSERT(!check_shape(attribute1,attribute2));

    //same rank but different number of elements along each dimension
    CPPUNIT_ASSERT(!check_shape(attribute1,attribute3));

    //as attributes currently do not support partial IO we do not have to check
    //any selection mechanism.

}

//-----------------------------------------------------------------------------
template<typename TA,typename TB>
void check_shape_test<TA,TB>::test_no_throw_mixed()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //---------------check fields and containers--------------------------
    //fine - same rank, same number of elements
    CPPUNIT_ASSERT(check_shape(field1,a1));
    CPPUNIT_ASSERT(check_shape(b1,field1));

    //different rank - must fail
    CPPUNIT_ASSERT(!check_shape(a2,field1));
    CPPUNIT_ASSERT(!check_shape(b2,field1));

    //same rank but different number of elements
    CPPUNIT_ASSERT(!check_shape(a3,field1));
    CPPUNIT_ASSERT(!check_shape(b3,field1));

    //for fields we still need to check for selections
    CPPUNIT_ASSERT(check_shape(a2,field4(slice(0,6))));
    CPPUNIT_ASSERT(!check_shape(a2,field4(slice(0,7))));

    //--------------check with attributes----------------------------------
    //fine - same rank, same number of elements
    CPPUNIT_ASSERT(check_shape(attribute1,a1));
    CPPUNIT_ASSERT(check_shape(b1,attribute1));

    //different rank - must fail
    CPPUNIT_ASSERT(!check_shape(a2,attribute1));
    CPPUNIT_ASSERT(!check_shape(b2,attribute1));

    //same rank but different number of elements
    CPPUNIT_ASSERT(!check_shape(a3,attribute1));
    CPPUNIT_ASSERT(!check_shape(b3,attribute1));
}

