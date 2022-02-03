//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Nov 07, 2013
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
//

#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include "../boost_unit_test.hpp"
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include <boost/mpl/list.hpp>
#include <array>
#include <h5cpp/contrib/nexus/ebool.hpp>
#include "test_trait.hpp"

using namespace pni;

template<typename T>
using array_type = std::array<T,4>;

//data types for which to test container construction
typedef boost::mpl::list<array_type<uint8>,
                         array_type<int8>,
                         array_type<uint16>,
                         array_type<int16>,
                         array_type<uint32>,
                         array_type<int32>,
                         array_type<uint64>,
                         array_type<int64>,
                         array_type<float32>,
                         array_type<float64>,
                         array_type<float128>,
                         array_type<complex32>,
                         array_type<complex64>,
                         array_type<complex128>,
                         array_type<string>,
                         array_type<bool_t>,
                         array_type<hdf5::datatype::EBool>
                         > test_types;


BOOST_AUTO_TEST_SUITE(container_utils_array_test)

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE_TEMPLATE(test_create_from_size,CT,test_types)
{
    typedef test_trait<CT> trait_type;
    typedef typename trait_type::generator_type generator_type;
    typedef typename trait_type::utils_type utils_type;
    generator_type generator;

    //without initializiation value
    auto c1 = utils_type::create(4);
    BOOST_CHECK_EQUAL(c1.size(),4u);


    //with initializiation value
    auto random_value = generator();
    auto c2 = utils_type::create(4,random_value);
    for(auto c: c2)
        BOOST_CHECK_EQUAL(c,random_value);

    //check exception
    BOOST_CHECK_THROW(utils_type::create(5),size_mismatch_error);
    BOOST_CHECK_THROW(utils_type::create(3),size_mismatch_error);
}


BOOST_AUTO_TEST_SUITE_END()



