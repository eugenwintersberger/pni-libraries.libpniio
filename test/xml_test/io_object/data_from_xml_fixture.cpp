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
//  Created on: Dec 3, 2014
//      Author: Eugen Wintersberger
//

#include <boost/property_tree/xml_parser.hpp>
#include <pni/io/nx/xml/attribute_data.hpp>
#include "data_from_xml_fixture.hpp"
#include "../../uniform_distribution.hpp"
#include <boost/algorithm/string/trim.hpp>

CPPUNIT_TEST_SUITE_REGISTRATION(data_from_xml_fixture);

void data_from_xml_fixture::setUp()
{}

//----------------------------------------------------------------------------
void data_from_xml_fixture::tearDown()
{}

//-----------------------------------------------------------------------------
xml::node data_from_xml_fixture::get_object(const string &f,const string &n) const
{
    xml::node root  = xml::create_from_file(f);
    return root.get_child(n);
}

//----------------------------------------------------------------------------
void data_from_xml_fixture::test_scalar()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    xml::node o = get_object("object3.xml","field1");
    auto data = xml::io_object::data_from_xml<float32>(o);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.23,data,1.e-6);

}

//----------------------------------------------------------------------------
void data_from_xml_fixture::test_array()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef std::vector<uint32> vector_type;
    
    xml::node o = get_object("object3.xml","field2");
    auto data = xml::io_object::data_from_xml<vector_type>(o,' ');
    std::cout<<data.size()<<std::endl;
    CPPUNIT_ASSERT(data.size()==6);

    for(uint32 i=0;i<6;++i)
        CPPUNIT_ASSERT(data[i]==i+1);
}

//----------------------------------------------------------------------------
void data_from_xml_fixture::test_string()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    xml::node o = get_object("object3.xml","field3");

    CPPUNIT_ASSERT(xml::io_object::type_id(o)==type_id_t::STRING);
    auto text = xml::io_object::data_from_xml<string>(o);
    boost::algorithm::trim(text);
    std::cout<<text<<std::endl;
    CPPUNIT_ASSERT(text == "This is a stupid text");
}

//----------------------------------------------------------------------------
void data_from_xml_fixture::test_bool()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    xml::node o = get_object("object3.xml","field4");
    CPPUNIT_ASSERT(xml::io_object::data_from_xml<bool_t>(o));

    o = get_object("object3.xml","field5");
    CPPUNIT_ASSERT(!xml::io_object::data_from_xml<bool_t>(o));

    o = get_object("object3.xml","field6");
    CPPUNIT_ASSERT_THROW(xml::io_object::data_from_xml<bool_t>(o),
                         pni::io::parser_error);
    o = get_object("object3.xml","field7");
    CPPUNIT_ASSERT_THROW(xml::io_object::data_from_xml<bool_t>(o),
                         pni::io::parser_error);
}
