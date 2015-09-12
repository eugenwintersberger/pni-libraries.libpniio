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
//  Created on: Sep 11, 2015
//      Author: Eugen Wintersberger
//

#include <boost/current_function.hpp>
#include <pni/core/types.hpp>
#include <pni/io/nx/nxpath/nxpath.hpp>
#include <pni/io/nx/nxpath/make_relative.hpp>
#include "test_make_relative.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(test_make_relative);

using namespace pni::core;
using namespace pni::io::nx;

//----------------------------------------------------------------------------
void test_make_relative::setUp() { }

//----------------------------------------------------------------------------
void test_make_relative::tearDown() {}

//----------------------------------------------------------------------------
void test_make_relative::test_1()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    string p1 = "/:NXentry";
    string p2 = "/:NXentry/instrument:NXinstrument";

    string p2r = nxpath::to_string(make_relative(p1,p2));
    std::cout<<p2r<<std::endl;
    CPPUNIT_ASSERT(p2r=="instrument:NXinstrument");
}   

//----------------------------------------------------------------------------
void test_make_relative::test_2()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    string parent = "/:NXentry";
    string orig = "/";

    CPPUNIT_ASSERT_THROW(make_relative(parent,orig),value_error);
}

//----------------------------------------------------------------------------
void test_make_relative::test_3()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    string parent = "/:NXentry";
    string orig   = "/:NXentry";

    CPPUNIT_ASSERT(nxpath::to_string(make_relative(parent,orig))==".");
}
