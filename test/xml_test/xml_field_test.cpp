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

#include <pni/io/nx/xml/attribute_data.hpp>
#include "xml_field_test.hpp"
#include "../uniform_distribution.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(xml_field_test);

void xml_field_test::setUp()
{
    file = h5::nxfile::create_file("xml_field_test.nxs",true);
    root_group = file.root();
}

//-----------------------------------------------------------------------------
void xml_field_test::tearDown()
{
    root_group.close();
    field.close();
    file.close();
}

//-----------------------------------------------------------------------------
void xml_field_test::test_from_xml_1()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_file("field1.xml");
    child = root.get_child("field");

    CPPUNIT_ASSERT_NO_THROW(field = xml::field::from_xml(root_group,child));
    CPPUNIT_ASSERT(is_valid(field));
    CPPUNIT_ASSERT(get_rank(field) == 1);
    CPPUNIT_ASSERT(get_size(field) == 1);
    CPPUNIT_ASSERT(get_type(field) == type_id_t::FLOAT32);
    CPPUNIT_ASSERT(get_unit(field) == "m");
    auto attr = get_attribute(field,"long_name");
    read(attr,buffer);
    CPPUNIT_ASSERT(buffer == "motor along x-axis");
}

//-----------------------------------------------------------------------------
void xml_field_test::test_from_xml_2()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_file("field2.xml");
    child = root.get_child("field");

    CPPUNIT_ASSERT_NO_THROW(field = xml::field::from_xml(root_group,child,true));
    CPPUNIT_ASSERT(is_valid(field));
    CPPUNIT_ASSERT(get_rank(field) == 1);
    CPPUNIT_ASSERT(get_size(field) == 1);
    CPPUNIT_ASSERT(get_type(field) == type_id_t::FLOAT32);

    float32 buffer;
    read(field,buffer);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(buffer,1.,1.e-8);
}

//-----------------------------------------------------------------------------
void xml_field_test::test_from_xml_3()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_file("field3.xml");
    child = root.get_child("field");

    CPPUNIT_ASSERT_THROW(xml::field::from_xml(root_group,child),
                         pni::io::parser_error);
}

//-----------------------------------------------------------------------------
void xml_field_test::test_from_xml_4()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_file("field4.xml");
    child = root.get_child("field");

    CPPUNIT_ASSERT_THROW(xml::field::from_xml(root_group,child),
                         pni::io::parser_error);
}

//-----------------------------------------------------------------------------
void xml_field_test::test_from_xml_5()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    root = xml::create_from_file("field5.xml");
    child = root.get_child("field");

    field = xml::field::from_xml(root_group,child);

    CPPUNIT_ASSERT(is_valid(field));
    CPPUNIT_ASSERT(get_rank(field) == 3);
    CPPUNIT_ASSERT(get_size(field) == 55000);
    CPPUNIT_ASSERT(get_type(field) == type_id_t::FLOAT32);
    auto shape = get_shape<shape_t>(field);
    CPPUNIT_ASSERT(shape[0] == 100);
    CPPUNIT_ASSERT(shape[1] == 55);
    CPPUNIT_ASSERT(shape[2] == 10);
}

//-----------------------------------------------------------------------------
void xml_field_test::test_to_xml_1()
{
    typedef xml::attribute_data<string> attr_data;
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    shape_t s{3,4};
    field = root_group.create_field<float32>("data",s);
    field.attributes.create<string>("units").write("nm");
    field.attributes.create<string>("long_name").write("testing data");

    xml::node n = xml::field::to_xml(field);

    CPPUNIT_ASSERT(attr_data::read(n,"name")=="data");
    CPPUNIT_ASSERT(attr_data::read(n,"type")=="float32");
    CPPUNIT_ASSERT(attr_data::read(n,"units")=="nm");
    CPPUNIT_ASSERT(attr_data::read(n,"long_name")=="testing data");
}

//-----------------------------------------------------------------------------
void xml_field_test::test_to_xml_2()
{
    using namespace pni::io::nx::xml;
    typedef xml::attribute_data<string> attr_data;
    typedef uniform_distribution<float32> distribution_type;
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    distribution_type distribution;
   
    shape_t s{3,4};
    auto data = dynamic_array<float32>::create(s);
    std::generate(data.begin(),data.end(),distribution);
    field = root_group.create_field<float32>("data",s);
    field.attributes.create<string>("units").write("nm");
    field.attributes.create<string>("long_name").write("testing data");
    field.write(data);

    root = xml::node();
    xml::node n = xml::field::to_xml(field,true);
    root.add_child("field",n);

    CPPUNIT_ASSERT(attr_data::read(n,"name")=="data");
    CPPUNIT_ASSERT(attr_data::read(n,"type")=="float32");
    CPPUNIT_ASSERT(attr_data::read(n,"units")=="nm");
    CPPUNIT_ASSERT(attr_data::read(n,"long_name")=="testing data");
    std::cout<<root<<std::endl;
}

//----------------------------------------------------------------------------
void xml_field_test::test_to_xml_3()
{
    using namespace pni::io::nx::xml;
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    field = root_group.create_field<string>("text");
    field.write("hello world");
    field.attributes.create<string>("units").write("none");
    field.attributes.create<string>("long_name").write("some text");

    root = xml::node();
    xml::node n = xml::field::to_xml(field,true);
    root.add_child("field",n);
    std::cout<<root<<std::endl;
}
