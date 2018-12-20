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
// ===========================================================================
//
//  Created on: Feb 11, 2015
//      Author: Eugen Wintersberger
//

#include <pni/core/types.hpp>
#include <boost/test/unit_test.hpp>
#include <pni/io/formatters.hpp>

using namespace pni::core;
using namespace pni::io;

BOOST_AUTO_TEST_SUITE(bool_vector_formatter_test)

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_format)
    {
        typedef bool_t                     element_type;
        typedef std::vector<element_type>  input_type;
        input_type     input ={true,false,false,true} ;

        BOOST_TEST(format(input) == "true false false true");
    }

BOOST_AUTO_TEST_SUITE_END()
