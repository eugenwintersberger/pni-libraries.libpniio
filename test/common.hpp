//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Sep 13, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
///
#pragma once

//header file for the BOOST_CURRENT_FUNCTION macro
#include<boost/current_function.hpp>

//header files for CPPUNIT tests
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

//headers from pniutils
#include<pni/core/types.hpp>

//local template for equality checks
#include "EqualityCheck.hpp"

//common macros
#define PRINT_TEST_FUNCTION_SIG std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

