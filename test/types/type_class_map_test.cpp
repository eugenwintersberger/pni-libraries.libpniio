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
//  Created on: Sep 27, 2012
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
#include <pni/types/type_class_map.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>
#include <iostream>

using namespace pni;

namespace std
{
    ostream& operator<<(ostream &stream,const pni::type_class_t &tcid)
    {
        using namespace pni;
        switch(tcid)
        {
            case type_class_t::None: return stream<<"NONE";
            case type_class_t::Integer: return stream<<"INTEGER";
            case type_class_t::Float: return stream<<"FLOAT";
            case type_class_t::Binary: return stream<<"BINARY";
            case type_class_t::Bool:   return stream<<"BOOL";
            case type_class_t::Complex: return stream<<"COMPLEX";
            case type_class_t::String:  return stream<<"STRING";
            default:
                return stream;
        }
    }
}

BOOST_AUTO_TEST_SUITE(type_class_map_test)

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_type_class_map_integer)
    {
        BOOST_CHECK(type_class_map<uint8>::type_class  == type_class_t::Integer);
        BOOST_CHECK(type_class_map<int8>::type_class == type_class_t::Integer);
        BOOST_CHECK(type_class_map<uint16>::type_class == type_class_t::Integer);
        BOOST_CHECK(type_class_map<int16>::type_class == type_class_t::Integer);
        BOOST_CHECK(type_class_map<uint32>::type_class == type_class_t::Integer);
        BOOST_CHECK(type_class_map<int32>::type_class == type_class_t::Integer);
        BOOST_CHECK(type_class_map<uint64>::type_class == type_class_t::Integer);
        BOOST_CHECK(type_class_map<int64>::type_class == type_class_t::Integer);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_type_class_map_float)
    {
        BOOST_CHECK(type_class_map<float32>::type_class == type_class_t::Float);
        BOOST_CHECK(type_class_map<float64>::type_class == type_class_t::Float);
        BOOST_CHECK(type_class_map<float128>::type_class == type_class_t::Float);
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE(test_type_class_map_complex)
    {
        BOOST_CHECK(type_class_map<complex32>::type_class == type_class_t::Complex);
        BOOST_CHECK(type_class_map<complex64>::type_class == type_class_t::Complex);
        BOOST_CHECK(type_class_map<complex128>::type_class == type_class_t::Complex);
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE(test_type_class_map_others)
    {
        BOOST_CHECK(type_class_map<string>::type_class == type_class_t::String);
        BOOST_CHECK(type_class_map<binary>::type_class == type_class_t::Binary);
        BOOST_CHECK(type_class_map<bool_t>::type_class == type_class_t::Bool);
        BOOST_CHECK(type_class_map<hdf5::datatype::EBool>::type_class == type_class_t::Bool);

        BOOST_CHECK(type_class_map<none>::type_class == type_class_t::None);
    }

BOOST_AUTO_TEST_SUITE_END()
