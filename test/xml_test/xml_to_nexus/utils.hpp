//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//
// ===========================================================================
#pragma once

#include <pni/core/types.hpp>

#include <pni/io/nx/algorithms/read.hpp>
#include <pni/io/nx/algorithms/is_field.hpp>
#include <pni/io/nx/algorithms/get_name.hpp>
#include <pni/io/nx/algorithms/get_type.hpp>
#include <pni/io/nx/algorithms/get_size.hpp>
#include <pni/io/nx/algorithms/get_unit.hpp>
#include <pni/io/nx/algorithms/get_shape.hpp>
#include <pni/io/nx/algorithms/is_group.hpp>
#include <pni/io/nx/algorithms/get_class.hpp>

template<
         typename TT,
         typename OT
        >
TT get_data(const OT &object)
{
    using namespace pni::core;
    using namespace pni::io::nx;

    TT buffer;
    read(object,buffer);
    return buffer;
}


//-----------------------------------------------------------------------------
template<typename T>
void test_field(const T &object,const pni::core::string &name,
                pni::core::type_id_t tid)
{
    using namespace pni::io::nx;
    using namespace pni::core;

    BOOST_CHECK(is_field(object));
    BOOST_CHECK_EQUAL(get_name(object),name);
    BOOST_CHECK_EQUAL(get_type(object),tid);
}

//-----------------------------------------------------------------------------
template<typename T>
void test_field(const T &object,const pni::core::string &name,
                pni::core::type_id_t tid,
                size_t size,const pni::core::string &unit)
{
    using namespace pni::core;
    using namespace pni::io::nx;

    test_field(object,name,tid);
    BOOST_CHECK_EQUAL(get_unit(object),unit);
    BOOST_CHECK_EQUAL(get_size(object),size);
}

//-----------------------------------------------------------------------------
template<typename T>
void test_field(const T &object,const pni::core::string &name,
                pni::core::type_id_t tid,
                const pni::core::shape_t &shape,const pni::core::string &unit)
{
    using namespace pni::core;
    using namespace pni::io::nx;

    test_field(object,name,tid);
    BOOST_CHECK_EQUAL(get_unit(object),unit);
    auto s = get_shape<shape_t>(object);
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(),s.end(),shape.begin(),shape.end());
}

//-----------------------------------------------------------------------------
template<typename T>
void test_group(const T &object,const pni::core::string &name,
                const pni::core::string &c)
{
    using namespace pni::core;
    using namespace pni::io::nx;

    BOOST_CHECK(is_group(object));
    BOOST_CHECK_EQUAL(get_name(object),name);
    BOOST_CHECK_EQUAL(get_class(object),c);
}
