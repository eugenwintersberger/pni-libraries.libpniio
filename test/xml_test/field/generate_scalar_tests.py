#
# (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
#
# This file is part of libpniio.
#
# libpniio is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# libpniio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
# ===========================================================================
#
#  Created on: Apr 20, 2015
#      Author: Eugen Wintersberger
#

#=============================================================================
# this script generates the input files for the different test cases
#=============================================================================

xml_scalar_attribute="""
<group name="test" type="NXdetector">
    <field name="data" type="{0.type_name}">
        {0.data}
    </field>
</group>
"""

xml_test_header="""
#pragma once

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml.hpp>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <EqualityCheck.hpp>

using namespace pni::core;
using namespace pni::io::nx;

class scalar_field_test_{0.type_name} : public CppUnit::TestFixture
{{ 
    private:
        CPPUNIT_TEST_SUITE(scalar_field_test_{0.type_name});
        CPPUNIT_TEST(test_inquery);
        CPPUNIT_TEST(test_create_object);
        CPPUNIT_TEST(test_from_object);
        CPPUNIT_TEST_SUITE_END();

        xml::node root;
        xml::node child;

        h5::nxfile file; 
        h5::nxobject group;

    public:
        void setUp();
        void tearDown();
       
        void test_inquery();
        void test_create_object();
        void test_from_object();
}};
"""

xml_test_source="""
#include <boost/current_function.hpp>
#include <pni/io/nx/algorithms/create_field.hpp>
#include "scalar_field_test_{0.type_name}.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(scalar_field_test_{0.type_name});

//-----------------------------------------------------------------------------
void scalar_field_test_{0.type_name}::setUp() 
{{ 
    file = h5::nxfile::create_file("scalar_attribute_test_{0.type_name}.nxs",
                                    true);
    h5::nxgroup root = file.root();
    group = root.create_group("test","NXdetector");
}}

//-----------------------------------------------------------------------------
void scalar_field_test_{0.type_name}::tearDown() 
{{ 
    close(group);
    file.close();
}}

//-----------------------------------------------------------------------------
void scalar_field_test_{0.type_name}::test_inquery()
{{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    root = xml::create_from_file("scalar_field_{0.type_name}.xml");
    child = root.get_child("group.field");

    CPPUNIT_ASSERT(xml::field::size(child)==1);
    CPPUNIT_ASSERT(xml::field::rank(child)==0);
    CPPUNIT_ASSERT(xml::field::type_id(child) == type_id_t::{0.type_id});
   
    {0.type_name} r{{{0.cpp_data}}};
    auto data = xml::field::data_from_xml<{0.type_name}>(child);
    check_equality(data,r);

}}

//-----------------------------------------------------------------------------
void scalar_field_test_{0.type_name}::test_create_object()
{{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    root = xml::create_from_file("scalar_field_{0.type_name}.xml");
    child = root.get_child("group.field");

    //attach the attribute to the group
    h5::nxfield field = xml::field::object_from_xml(group,child);

    CPPUNIT_ASSERT(field.size() == 1);
    CPPUNIT_ASSERT(field.rank() == 1);
    CPPUNIT_ASSERT(field.type_id() == type_id_t::{0.type_id});
}}

//-----------------------------------------------------------------------------
void scalar_field_test_{0.type_name}::test_from_object()
{{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    using namespace pni::io::nx::xml;
   
    h5::nxobject field = create_field<{0.type_name}>(group,"data");
    {0.type_name} r{{{0.cpp_data}}};
    write(field,r);

    root = xml::node();
    root.add_child("group",xml::group::object_to_xml(group));
    xml::node field_node = xml::attribute::object_to_xml(field);
    xml::attribute::data_to_xml(field_node,r);
    child = root.add_child("group.field",field_node);

    CPPUNIT_ASSERT(xml::field::size(child) == 1);
    CPPUNIT_ASSERT(xml::field::rank(child) == 0);
    CPPUNIT_ASSERT(xml::field::type_id(child) ==
                   type_id_t::{0.type_id});

    std::cout<<root<<std::endl;

}}
"""

class TestData(object):
    def __init__(self,tname,tid,data,cppdata=None):
        self.type_name = tname
        self.type_id   = tid
        self.data     = data

        if cppdata:
            self.cpp_data = cppdata
        else:
            self.cpp_data = data


scalar_data = [TestData("uint8","UINT8","1"),
               TestData("int8","INT8","-4"),
               TestData("uint16","UINT16","200"),
               TestData("int16","INT16","-234"),
               TestData("uint32","UINT32","4000"),
               TestData("int32","INT32","23456"),
               TestData("uint64","UINT64","4013945"),
               TestData("int64","INT64","-4013945"),
               TestData("float32","FLOAT32","2.3455"),
               TestData("float64","FLOAT64","-1.233e+4"),
               TestData("float128","FLOAT128","123.24354e-4"),
               TestData("complex32","COMPLEX32","34.+j123.e-3","34.,123.e-3"),
               TestData("complex64","COMPLEX64","-23.-I8.203","-23.,-8.203"),
               TestData("complex128","COMPLEX128","123+I340","123,340"),
               TestData("string","STRING","hello world, a text",
                        "\"hello world, a text\""),
               TestData("bool_t","BOOL","true")

               ]


def generate_filenames(data):
    xmlfile = "scalar_field_{0.type_name}.xml".format(data)
    cppfile = "scalar_field_test_{0.type_name}.cpp".format(data)
    hppfile = "scalar_field_test_{0.type_name}.hpp".format(data)

    return (xmlfile,cppfile,hppfile)

def write_file(fname,data):

    with open(fname,"w") as output_file:
        output_file.write(data)
    

#generate the XML file
for data in scalar_data:
    xml_file,cpp_file,hpp_file = generate_filenames(data)
   
    xml_data = xml_scalar_attribute.format(data)
    write_file(xml_file,xml_data)

    header_data = xml_test_header.format(data)
    write_file(hpp_file,header_data)

    source_data = xml_test_source.format(data)
    write_file(cpp_file,source_data)
    

