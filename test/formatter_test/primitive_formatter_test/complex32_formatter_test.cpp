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

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/io/formatters/scalar_format.hpp>

using namespace pni::core;
using namespace pni::io;

BOOST_AUTO_TEST_SUITE(complex32_formatter_test)

    BOOST_AUTO_TEST_CASE(test)
    {
        typedef complex32 input_type; 
        string result = format(input_type(1.256987,3.452907));
        BOOST_CHECK_EQUAL(result,"1.256987e00+I3.452907e00");
        
        result = format(input_type(1.256987,-3.452907));
        BOOST_CHECK_EQUAL(result,"1.256987e00-I3.452907e00");

        result = format(input_type(-1.256987,-3.452907));
        BOOST_CHECK_EQUAL(result,"-1.256987e00-I3.452907e00");
        
        result = format(input_type(-1.256987,3.452907));
        BOOST_CHECK_EQUAL(result,"-1.256987e00+I3.452907e00");

        result = format(input_type(0,3.45));
        BOOST_CHECK_EQUAL(result,"0.0e00+I3.45e00");
        
        result = format(input_type(0,-3.45));
        BOOST_CHECK_EQUAL(result,"0.0e00-I3.45e00");
    }

BOOST_AUTO_TEST_SUITE_END()


