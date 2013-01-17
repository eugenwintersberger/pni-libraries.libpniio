/*
 * Declaration of Nexus object template.
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * NXAttributeTest.cpp
 *
 *  Created on: Sep 13, 2012
 *      Author: Eugen Wintersberger
 */

#include <boost/current_function.hpp>
#include "NXGroupTest.hpp"

#include<cppunit/extensions/HelperMacros.h>

#include "NX.hpp"
#include "NXAttributeTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NXAttributeTest<NXFile>);
CPPUNIT_TEST_SUITE_REGISTRATION(NXAttributeTest<NXGroup>);
CPPUNIT_TEST_SUITE_REGISTRATION(NXAttributeTest<NXField>);

