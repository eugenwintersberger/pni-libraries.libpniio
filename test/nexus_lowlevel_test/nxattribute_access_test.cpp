//
// Declaration of Nexus object template.
//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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

//implementation of the arrayshape test

#include<cppunit/extensions/HelperMacros.h>

#include <pni/io/nx/nx.hpp>
#include "nxattribute_access_test.hpp"

//------------------------------------------------------------------------------
void nxattribute_access_test::setUp() 
{ 
    f = h5::nxfile::create_file(filename,true);
    group = f.root().create_group("entry");
    field = f.root().create_field<float32>("temperature");
    
    group.attributes.create<string>("attr1");
    group.attributes.create<float32>("temperature");
    group.attributes.create<float64>("matrix",shape);
    
    field.attributes.create<string>("attr1");
    field.attributes.create<float32>("temperature");
    field.attributes.create<float64>("matrix",shape);
}

//----------------------------------------------------------------------------
void nxattribute_access_test::tearDown() 
{   
    group.close();
    field.close();
    f.close();
}
