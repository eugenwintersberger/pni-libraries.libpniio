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

#include <boost/current_function.hpp>
#include "detector_master_file_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(detector_master_file_test);

//-----------------------------------------------------------------------------
void detector_master_file_test::setUp() 
{    
}

//-----------------------------------------------------------------------------
void detector_master_file_test::tearDown() 
{    
} 


//-----------------------------------------------------------------------------
void detector_master_file_test::test_data_file()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    file = h5::nxfile::create_file(nxs_data_file,true);
    root_group = file.root();
    
    root_node = xml::create_from_file(xml_data_file);
    
    xml::xml_to_nexus(root_node,root_group,
                    [](const h5::nxobject &o) { return get_size(o) <= 3; });
}
//-----------------------------------------------------------------------------
void detector_master_file_test::test_master_file()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    file = h5::nxfile::create_file(nxs_master_file,true);
    root_group = file.root();
    
    root_node = xml::create_from_file(xml_master_file);
    
    xml::xml_to_nexus(root_node,root_group,
                    [](const h5::nxobject &o) { return get_size(o) <= 3; });
}

