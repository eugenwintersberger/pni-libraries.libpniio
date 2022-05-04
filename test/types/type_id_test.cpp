//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Oct 15, 2015
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
//
#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include <boost/test/unit_test.hpp>
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include <pni/types.hpp>
#include <pni/arrays.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/joint_view.hpp>

using namespace pni;

typedef boost::mpl::list<uint8,int8,
                         uint16,int16,
                         uint32,int32,
                         uint64,int64,
                         float32,float64,float128,
                         complex32,complex64,complex128,
                         string,bool_t,hdf5::datatype::EBool> scalar_types;


template<typename ElementT> using sarray = static_array<ElementT,1>;
template<typename ElementT> using darray = dynamic_array<ElementT>;
template<typename ElementT> using farray = fixed_dim_array<ElementT,2>;

typedef boost::mpl::list<sarray<uint8>,sarray<int8>,
                         sarray<uint16>,sarray<int16>,
                         sarray<uint32>,sarray<int32>,
                         sarray<uint64>,sarray<int64>,
                         sarray<float32>,sarray<float64>,sarray<float128>,
                         sarray<complex32>,
                         sarray<complex64>,
                         sarray<complex128>,
                         sarray<string>,sarray<bool_t>, sarray<hdf5::datatype::EBool>> sarray_types;

typedef boost::mpl::list<darray<uint8>,darray<int8>,
                         darray<uint16>,darray<int16>,
                         darray<uint32>,darray<int32>,
                         darray<uint64>,darray<int64>,
                         darray<float32>,darray<float64>,darray<float128>,
                         darray<complex32>,
                         darray<complex64>,
                         darray<complex128>,
                         darray<string>,darray<bool_t>,darray<hdf5::datatype::EBool>> darray_types;

typedef boost::mpl::list<farray<uint8>,farray<int8>,
                         farray<uint16>,farray<int16>,
                         farray<uint32>,farray<int32>,
                         farray<uint64>,farray<int64>,
                         farray<float32>,farray<float64>,farray<float128>,
                         farray<complex32>,
                         farray<complex64>,
                         farray<complex128>,
                         farray<string>,farray<bool_t>,farray<hdf5::datatype::EBool>> farray_types;

typedef boost::mpl::joint_view<sarray_types,
                               farray_types> array_types_1;
typedef boost::mpl::joint_view<array_types_1,darray_types> array_types;




BOOST_AUTO_TEST_SUITE(type_id_test)

    BOOST_AUTO_TEST_CASE_TEMPLATE(type_id_scalar_test,ElementT,scalar_types)
    {
        type_id_t tid = type_id_map<ElementT>::type_id;

        ElementT instance;
        BOOST_CHECK_EQUAL(type_id(instance),tid);
        ElementT &reference = instance;
        BOOST_CHECK_EQUAL(type_id(reference),tid);
        ElementT *pointer = &instance;
        BOOST_CHECK_EQUAL(type_id(pointer),tid);

        const ElementT &const_reference = instance;
        BOOST_CHECK_EQUAL(type_id(const_reference),tid);
        const ElementT *const_pointer = &instance;
        BOOST_CHECK_EQUAL(type_id(const_pointer),tid);
    }

    BOOST_AUTO_TEST_CASE_TEMPLATE(type_id_container_test,ElementT,array_types)
    {
        type_id_t tid = type_id_map<typename ElementT::value_type>::type_id;
        ElementT instance;
        BOOST_CHECK_EQUAL(type_id(instance),tid);

        //check references
        ElementT &reference = instance;
        BOOST_CHECK_EQUAL(type_id(reference),tid);
        const ElementT &const_reference = instance;
        BOOST_CHECK_EQUAL(type_id(const_reference),tid);

        //check pointers
        ElementT *pointer = &instance;
        BOOST_CHECK_EQUAL(type_id(pointer),tid);
        const ElementT *const_pointer = &instance;
        BOOST_CHECK_EQUAL(type_id(const_pointer),tid);
    }

BOOST_AUTO_TEST_SUITE_END()

