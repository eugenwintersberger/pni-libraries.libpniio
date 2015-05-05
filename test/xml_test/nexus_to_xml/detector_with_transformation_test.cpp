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
//  Created on: Apr 24, 2015
//      Author: Eugen Wintersberger
//

#include <pni/io/nx/algorithms/close.hpp>
#include <pni/io/nx/algorithms/get_child.hpp>
#include <fstream>
#include <vector>
#include "detector_with_transformation_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(detector_with_transformation_test);

//-----------------------------------------------------------------------------
void detector_with_transformation_test::setUp() 
{
    file = h5::nxfile::open_file(nxs_file);
    root_group = file.root();
}

//-----------------------------------------------------------------------------
void detector_with_transformation_test::tearDown() 
{ 
    close(root_group);
    file.close();
} 


//-----------------------------------------------------------------------------
void detector_with_transformation_test::test()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    using namespace pni::io::nx::xml;
    
    auto c = get_child(root_group,"","NXentry");
    nexus_to_xml(c,root_node,
                 [](const h5::nxobject &o) { return get_size(o) <= 3; });
                 
    std::ofstream stream(xml_file);
    stream<<root_node;
    
}

