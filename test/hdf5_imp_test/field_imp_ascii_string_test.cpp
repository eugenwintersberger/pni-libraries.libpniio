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
// Created on: Jul 17, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <boost/test/unit_test.hpp>
#include <boost/current_function.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/h5/h5deflate_filter.hpp>
#include <pni/io/nx/h5/type_imp.hpp>
#include <pni/io/nx/h5/file_imp.hpp>
#include <pni/io/nx/h5/group_imp.hpp>
#include <pni/io/nx/h5/field_imp.hpp>
#include <pni/io/nx/h5/field_factory.hpp>
#include <boost/mpl/list.hpp>
#include "../uniform_distribution.hpp"

using namespace pni::core;
using namespace pni::io::nx;
using pni::io::object_error;


struct field_imp_ascii_string_test_fixture
{
    h5::file_imp file;
    h5::field_imp field;

    field_imp_ascii_string_test_fixture():
        file(h5::file_imp::open("ascii_string_test.h5")),
        field(h5::field_imp(file.root().at("description")))
    {}

    //-------------------------------------------------------------------------
    ~field_imp_ascii_string_test_fixture()
    {
        field.close();
        file.close();
    }
};

BOOST_FIXTURE_TEST_SUITE(field_imp_ascii_string_test,field_imp_ascii_string_test_fixture)
    
    BOOST_AUTO_TEST_CASE(test_read_description)
    {
        string buffer;
        BOOST_CHECK_NO_THROW(field.read(type_id_t::STRING,{1},&buffer));
    }


BOOST_AUTO_TEST_SUITE_END()



