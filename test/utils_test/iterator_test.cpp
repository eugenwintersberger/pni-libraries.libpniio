//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pninexus.
//
// pninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
//  Created on: Jul 12, 2012
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include <boost/test/included/unit_test.hpp>
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include <boost/current_function.hpp>
#include <pni/utilities/container_iterator.hpp>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>

using namespace pni;

namespace itest_types
{
    typedef std::vector<double> iterable;
    typedef container_iterator<iterable> const_iterator;
    typedef container_iterator<const iterable> iterator;

}

namespace std{

    ostream &operator<<(ostream &stream,
                        const itest_types::iterator &i)
    {
        stream<<*i;
        return stream;
    }
    
    ostream &operator<<(ostream &stream,
                        const itest_types::const_iterator &i)
    {
        stream<<*i;
        return stream;
    }

}

struct iterator_test_fixture
{
    itest_types::iterable vector;

    iterator_test_fixture():
        vector(itest_types::iterable{1,2,3,4,5,6,7})
    {}
};

BOOST_FIXTURE_TEST_SUITE(iterator_test,iterator_test_fixture)

//
// test default construction of iterators
//
// After default construction the resulting iterator should be invalid.
//
BOOST_AUTO_TEST_CASE(test_default_construction)
{
    using namespace itest_types;
    
    iterator iter;
    BOOST_CHECK(!iter); 

    const_iterator citer;
    BOOST_CHECK(!citer);
}

//----------------------------------------------------------------------------
//
// test standard constructor 
//
// The construction is done with the address to a container and an initial 
// position
// 
BOOST_AUTO_TEST_CASE(test_standard_construction)
{
    using namespace itest_types;
    
    //====================testing standard construction========================
    //check construction on the first element - this is how begin() method
    //would create an interator.
    iterator iter1(&vector,0);
    BOOST_CHECK(iter1);

    const_iterator citer1(&vector,0);
    BOOST_CHECK(citer1);

    //check construction on the last+1 element - this is how end() method
    //produces the final iterator.
    iterator iter2(&vector,vector.size());
    const_iterator citer2(&vector,vector.size());
    BOOST_CHECK(!iter2);
    BOOST_CHECK(!citer2);


    //check construction on a negative element (should lead to an invalid 
    //iterator)
    iterator iter3(&vector,-1);
    const_iterator citer3(&vector,-1);
    BOOST_CHECK(!iter3);
    BOOST_CHECK(!citer3);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_copy_construction)
{
    using namespace itest_types;
    iterator iter1(&vector,0);
    iterator iter2(iter1);
    BOOST_CHECK(iter1);
    BOOST_CHECK(iter2);
    BOOST_CHECK(iter1 == iter2);

    const_iterator citer1(&vector,0);
    const_iterator citer2(citer1);
    BOOST_CHECK(citer1);
    BOOST_CHECK(citer2);
    BOOST_CHECK(citer1 == citer2);
}

BOOST_AUTO_TEST_CASE(test_move_construction)
{
    using namespace itest_types;

    //======================check move construction===========================
    iterator iter1(&vector,0);
    iterator iter2 = std::move(iter1);
    BOOST_CHECK(!iter1);
    BOOST_CHECK(iter2);
    BOOST_CHECK(iter1 != iter2);

    const_iterator citer1(&vector,0);
    const_iterator citer2 = std::move(citer1);
    BOOST_CHECK(!citer1);
    BOOST_CHECK(citer2);
    BOOST_CHECK(citer1 != citer2);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_assignment)
{
    using namespace itest_types;
    iterator iterator1(&vector,2);
    const_iterator const_iterator1(&vector,2);
    
    iterator iterator2;
    const_iterator const_iterator2;

    //====================check copy assignment================================
    iterator2 = iterator1;
    const_iterator2 = const_iterator1;
    BOOST_CHECK(iterator2);
    BOOST_CHECK(iterator1);
    BOOST_CHECK(const_iterator2);
    BOOST_CHECK(const_iterator1);

    //======================check move assignment==============================
    iterator iterator3;
    const_iterator const_iterator3;

    iterator3 = std::move(iterator1);
    const_iterator3 = std::move(const_iterator1);
    BOOST_CHECK(iterator3);
    BOOST_CHECK(!iterator1);
    BOOST_CHECK(const_iterator3);
    BOOST_CHECK(!const_iterator1);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_comparison)
{
    using namespace itest_types;

    iterator iterator1(&vector,0);
    const_iterator const_iterator1(&vector,0);

    iterator iterator2 = iterator1;
    const_iterator const_iterator2 = const_iterator1;

    //check for equality
    BOOST_CHECK_EQUAL(iterator1,iterator2);
    BOOST_CHECK_EQUAL(const_iterator1,const_iterator2);

    //check for inequality
    iterator iterator3(&vector,3);
    const_iterator const_iterator3(&vector,3);
    BOOST_CHECK_NE(iterator1,iterator3);
    BOOST_CHECK_NE(const_iterator1,const_iterator3);

    //check for greater than
    BOOST_CHECK_GT(iterator3,iterator1);
    BOOST_CHECK_GT(const_iterator3,const_iterator1);
    BOOST_CHECK_GE(iterator3,iterator1);
    BOOST_CHECK_GE(const_iterator3,const_iterator1);

    BOOST_CHECK_LT(iterator1,iterator3);
    BOOST_CHECK_LT(const_iterator1,const_iterator3);
    BOOST_CHECK_LE(iterator1,iterator3);
    BOOST_CHECK_LE(const_iterator1,const_iterator3);

    iterator1 += 3;
    const_iterator1 += 3;
    BOOST_CHECK_GE(iterator3,iterator1);
    BOOST_CHECK_GE(const_iterator3,const_iterator1);
    BOOST_CHECK_LE(iterator1,iterator3);
    BOOST_CHECK_LE(const_iterator1,const_iterator3);

}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_unary_arithmetics)
{
    using namespace itest_types;

    iterator iterator1(&vector,0);
    const_iterator const_iterator1(&vector,0);

    iterator1 += 5;
    const_iterator1 += 5;
    BOOST_CHECK_EQUAL(iterator1,iterator(&vector,5));
    BOOST_CHECK_EQUAL(const_iterator1,const_iterator(&vector,5));

    iterator1 -= 2;
    const_iterator1 -= 2;
    BOOST_CHECK_EQUAL(iterator1,iterator(&vector,3));
    BOOST_CHECK_EQUAL(const_iterator1,const_iterator(&vector,3));

}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_binary_arithmetics)
{
    using namespace itest_types;

    iterator iterator1(&vector,0);
    const_iterator const_iterator1(&vector,0);

    //=================test binary add=========================================
    BOOST_CHECK_EQUAL((iterator1+5),iterator(&vector,5));
    BOOST_CHECK_EQUAL((5+iterator1),iterator(&vector,5));
    BOOST_CHECK_EQUAL((const_iterator1+5),const_iterator(&vector,5));
    BOOST_CHECK_EQUAL((5+const_iterator1),const_iterator(&vector,5));

    //====================test binary sub======================================
    iterator1 = iterator(&vector,3);
    const_iterator1 = const_iterator(&vector,3);
    BOOST_CHECK_EQUAL((iterator1-2),iterator(&vector,1));
    BOOST_CHECK_EQUAL((const_iterator1-2),const_iterator(&vector,1));

    //=====================test binary add iterators===========================
    iterator iterator2(&vector,5);
    const_iterator const_iterator2(&vector,5);
    BOOST_CHECK_EQUAL((iterator2 - iterator1),2);
    BOOST_CHECK_EQUAL((const_iterator2 - const_iterator1),2);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_stl_algos)
{
    using namespace itest_types;
    iterable::iterator siter1 = vector.begin()+2;
    iterable::iterator siter2 = vector.begin()+5;
    BOOST_CHECK_EQUAL(std::distance(siter1,siter2),3);
    
    iterator iter1(&vector,2),iter2(&vector,5);
    BOOST_CHECK_EQUAL(std::distance(iter1,iter2),3);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_increment)
{
    using namespace itest_types;
    iterator iter(&vector,0);

    BOOST_CHECK_EQUAL(*iter,1);
    iter++;
    BOOST_CHECK_EQUAL(*iter,2);
    ++iter;
    BOOST_CHECK_EQUAL(*iter,3);
    BOOST_CHECK_EQUAL(*iter++,3);
    BOOST_CHECK_EQUAL(*iter,4);

    --iter;
    BOOST_CHECK_EQUAL(*iter,3);
    BOOST_CHECK_EQUAL(*iter--,3);
    BOOST_CHECK_EQUAL(*iter,2);
    iter--;
    BOOST_CHECK_EQUAL(*iter,1);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_ptr_access)
{
    using namespace itest_types;
    std::vector<string> v{"hello","world","this","is","a text"};

    typedef container_iterator<std::vector<string>> iterator_t;

    iterator_t first(&v,0);
    BOOST_CHECK_EQUAL(first->size(),5u);
}

BOOST_AUTO_TEST_SUITE_END()
