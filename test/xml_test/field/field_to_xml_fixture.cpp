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
//  Created on: Nov 25, 2014
//      Author: Eugen Wintersberger
//

#include <boost/property_tree/xml_parser.hpp>
#include <pni/io/nx/xml/attribute_data.hpp>
#include "field_to_xml_fixture.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(field_to_xml_fixture);

void field_to_xml_fixture::setUp()
{
    file = h5::nxfile::create_file("field_to_xml_fixture.nxs",true);
    root_group = file.root();
}

//-----------------------------------------------------------------------------
void field_to_xml_fixture::tearDown()
{
    close(root_group);
    close(field);
    file.close();
}


//-----------------------------------------------------------------------------
void field_to_xml_fixture::test_to_xml_1()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    shape_t s{3,4};
    field = create_field<float32>(root_group,"data",s);
    write(create_attribute<string>(field,"units"),string("nm"));
    write(create_attribute<string>(field,"long_name"),"testing data");

    xml::node n = xml::field::object_to_xml(field);

    CPPUNIT_ASSERT(str_data::read(n,"name")=="data");
    CPPUNIT_ASSERT(str_data::read(n,"type")=="float32");
    CPPUNIT_ASSERT(str_data::read(n,"units")=="nm");
    CPPUNIT_ASSERT(str_data::read(n,"long_name")=="testing data");
}

//-----------------------------------------------------------------------------
void field_to_xml_fixture::test_to_xml_2()
{
    using namespace pni::io::nx::xml;
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    float32_dist distribution;
   
    shape_t s{3,4};
    auto data = dynamic_array<float32>::create(s);
    std::generate(data.begin(),data.end(),distribution);
    field = create_field<float32>(root_group,"data",s);
    write(create_attribute<string>(field,"units"),"nm");
    write(create_attribute<string>(field,"long_name"),"testing data");
    write(field,data);

    root = xml::node();
    xml::node n = xml::field::object_to_xml(field);
    root.add_child("field",n);

    CPPUNIT_ASSERT(str_attr::read(n,"name")=="data");
    CPPUNIT_ASSERT(str_attr::read(n,"type")=="float32");
    CPPUNIT_ASSERT(str_attr::read(n,"units")=="nm");
    CPPUNIT_ASSERT(str_attr::read(n,"long_name")=="testing data");
}

//----------------------------------------------------------------------------
void field_to_xml_fixture::test_to_xml_3()
{
    using namespace pni::io::nx::xml;
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    field = create_field<string>(root_group,"text");
    write(field,"hello world");
    write(create_attribute<string>(field,"units"),"none");
    write(create_attribute<string>(field,"long_name"),"some text");

    root = xml::node();
    xml::node n = xml::field::object_to_xml(field);
    root.add_child("field",n);
    std::cout<<root<<std::endl;
}



