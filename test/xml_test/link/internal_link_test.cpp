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
//  Created on: Apr 22, 2015
//      Author: Eugen Wintersberger
//

#include <vector>
#include "internal_link_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(internal_link_test);

//-----------------------------------------------------------------------------
void internal_link_test::setUp() 
{
    //generate the basic NeXus file structure
    nxs_file = h5::nxfile::create_file(nxs_file_name,true);
    h5::nxgroup root_group = nxs_file.root();
    
    h5::nxgroup g = root_group.create_group("data","NXdata");
    g.create_field<uint16>("data",shape_t{1,1024,2048});
    
    root_node = xml::create_from_file(xml_file_name);
    link_node = root_node.get_child("link");
}

//-----------------------------------------------------------------------------
void internal_link_test::tearDown() 
{     
    nxs_file.close();
} 


//-----------------------------------------------------------------------------
void internal_link_test::test_link()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(xml::has_attribute(link_node,"name"));
    CPPUNIT_ASSERT(xml::has_attribute(link_node,"target"));
    
    h5::nxobject root = nxs_file.root();
    xml::link::object_from_xml(root,link_node);
    
    h5::nxfield ldata = get_object(root,"linked_data");
    CPPUNIT_ASSERT(ldata.size() == 1024*2048);
    CPPUNIT_ASSERT(ldata.type_id() == type_id_t::UINT16);
    CPPUNIT_ASSERT(ldata.rank() == 3);

}
