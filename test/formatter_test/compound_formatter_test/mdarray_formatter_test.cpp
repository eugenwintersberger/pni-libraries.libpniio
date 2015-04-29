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
//  Created on: Apr 29, 2015
//      Author: Eugen Wintersberger
//

#include <pni/io/container_io_config.hpp>
#include "mdarray_formatter_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(mdarray_formatter_test);

//-----------------------------------------------------------------------------
void mdarray_formatter_test::setUp() 
{ 
    input = input_type::create(shape_t{4},
                               input_type::storage_type{1,2,3,4});    
}

//-----------------------------------------------------------------------------
void mdarray_formatter_test::tearDown() {}

//-----------------------------------------------------------------------------
void mdarray_formatter_test::test_default()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
     
    try
    {
        std::cout<<format(input)<<std::endl;
        CPPUNIT_ASSERT(format(input)=="1 2 3 4");
    }
    catch(value_error &error)
    {
        std::cerr<<error<<std::endl;
    }
}

//-----------------------------------------------------------------------------
void mdarray_formatter_test::test_costum_sep()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    container_io_config config(';');    
    CPPUNIT_ASSERT(format(input,config)=="1;2;3;4");
}

//-----------------------------------------------------------------------------
void mdarray_formatter_test::test_costum_start_stop()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
  
    container_io_config config('(',')');  
    try
    {
        std::cout<<format(input,config)<<std::endl;  
    }
    catch(type_error &error)
    {
        std::cerr<<error<<std::endl;
    }
    catch(value_error &error)
    {
        std::cerr<<error<<std::endl;
    }
    CPPUNIT_ASSERT(format(input,config)=="(1 2 3 4)");
}
