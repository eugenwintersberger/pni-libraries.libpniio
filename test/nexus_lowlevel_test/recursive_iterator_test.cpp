//
// Declaration of Nexus object template.
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
//  Created on: Aug 8, 2014
//      Author: Eugen Wintersberger
//

#include <boost/current_function.hpp>
#include "recursive_iterator_test.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/nxobject_type.hpp>
#include <pni/io/nx/algorithms.hpp>
#include <pni/io/exceptions.hpp>

using pni::io::invalid_object_error;

CPPUNIT_TEST_SUITE_REGISTRATION(recursive_iterator_test);

//------------------------------------------------------------------------------
void recursive_iterator_test::setUp()
{
    _f = h5::nxfile::create_file("recursive_iterator_test.nxs",true,0);
}

//------------------------------------------------------------------------------
void recursive_iterator_test::tearDown()
{
	_f.close();
}


//------------------------------------------------------------------------------
void recursive_iterator_test::test_creation()
{
	std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    h5::nxgroup g = _f.root();
    iterator_type iter;
    CPPUNIT_ASSERT(!iter);

}


