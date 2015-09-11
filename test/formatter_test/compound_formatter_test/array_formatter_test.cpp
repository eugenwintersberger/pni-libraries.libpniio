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
//  Created on: Apr 28, 2015
//      Author: Eugen Wintersberger
//

#include <boost/current_function.hpp>
#include <pni/io/container_io_config.hpp>
#include "array_formatter_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(array_formatter_test);

//-----------------------------------------------------------------------------
void array_formatter_test::setUp() 
{ 
    typedef dynamic_array<int8> array_type;
    auto data = array_type::create(shape_t{4},
                                   array_type::storage_type{1,2,3,4});
    input = input_type(data);
}

//-----------------------------------------------------------------------------
void array_formatter_test::tearDown() {}

//-----------------------------------------------------------------------------
void array_formatter_test::test_default()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;   
    
    CPPUNIT_ASSERT(format(input)=="1 2 3 4");
}

//-----------------------------------------------------------------------------
void array_formatter_test::test_costum_sep()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    formatter_type f(container_io_config(';'));
  
    CPPUNIT_ASSERT(f(input)=="1;2;3;4");
}

//-----------------------------------------------------------------------------
void array_formatter_test::test_costum_start_stop()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    formatter_type f(container_io_config('(',')'));     
    CPPUNIT_ASSERT(f(input)=="(1 2 3 4)");
}

//-----------------------------------------------------------------------------
void array_formatter_test::test_full_costum()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    formatter_type f(container_io_config('[',']',';'));
    CPPUNIT_ASSERT(f(input)=="[1;2;3;4]");
}
