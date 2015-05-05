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
        <dimensions rank="1">            
            <dim index="1" value="3"/>            
        </dimensions>
        {0.data}
    </field>
    <field name="data_comp" type="{0.type_name}">
        <dimensions rank="3">
            <dim index="2" value="2048"/>
            <dim index="1" value="1"/>
            <dim index="3" value="512"/>
        </dimensions>
        <strategy compression="true" rate="3" shuffle="true"/>
    </field>
</group>
"""

xml_test_header="""
#pragma once

#include <boost/current_function.hpp>
#include <functional>
#include <random>

#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml.hpp>
#include <pni/core/arrays.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <EqualityCheck.hpp>


using namespace pni::core;
using namespace pni::io::nx;

class multidim_field_test_{0.type_name} : public CppUnit::TestFixture
{{ 
    private:
        CPPUNIT_TEST_SUITE(multidim_field_test_{0.type_name});
        CPPUNIT_TEST(test_inquery);
        CPPUNIT_TEST(test_create_object);
        CPPUNIT_TEST(test_create_compression_object);
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
        void test_create_compression_object();
}};
"""

xml_test_source="""
#include <pni/io/nx/algorithms/create_field.hpp>
#include "multidim_field_test_{0.type_name}.hpp"

typedef std::vector<{0.type_name}> array_type;

CPPUNIT_TEST_SUITE_REGISTRATION(multidim_field_test_{0.type_name});

//-----------------------------------------------------------------------------
void multidim_field_test_{0.type_name}::setUp() 
{{ 
    file = h5::nxfile::create_file("multidim_field_test_{0.type_name}.nxs",
                                    true);
    h5::nxgroup root = file.root();
    group = root.create_group("test","NXdetector");
}}

//-----------------------------------------------------------------------------
void multidim_field_test_{0.type_name}::tearDown() 
{{ 
    close(group);
    file.close();
}}

//-----------------------------------------------------------------------------
void multidim_field_test_{0.type_name}::test_inquery()
{{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    root = xml::create_from_file("multidim_field_{0.type_name}.xml");
    child = root.get_child("group.field");
    
    CPPUNIT_ASSERT(xml::field::size(child)==3);
    CPPUNIT_ASSERT(xml::field::rank(child)==1);
    CPPUNIT_ASSERT(xml::field::type_id(child) == type_id_t::{0.type_id});
   
    array_type r{{{0.cpp_data}}};
    auto data = xml::field::data_from_xml<array_type>(child);

    for(auto r_iter = r.begin(),d_iter = data.begin();
        d_iter != data.end();
        ++d_iter,++r_iter)
        check_equality(*d_iter,*r_iter);
}}

//-----------------------------------------------------------------------------
void multidim_field_test_{0.type_name}::test_create_object()
{{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    root = xml::create_from_file("multidim_field_{0.type_name}.xml");
    child = root.get_child("group.field");

    //attach the field to the group
    h5::nxfield field = xml::field::object_from_xml(group,child);

    CPPUNIT_ASSERT(field.size() == 3);
    CPPUNIT_ASSERT(field.rank() == 1);
    CPPUNIT_ASSERT(field.type_id() == type_id_t::{0.type_id});
}}

//-----------------------------------------------------------------------------
void multidim_field_test_{0.type_name}::test_create_compression_object()
{{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    using namespace pni::io::nx::xml;
    
    root = xml::create_from_file("multidim_field_{0.type_name}.xml");
    root = root.get_child("group");
    auto child_iter = root.begin();
    child_iter++;
    child_iter++;

    //attach the field to the group
    h5::nxfield field = xml::field::object_from_xml(group,child_iter->second);

    CPPUNIT_ASSERT(field.size() == 2048*512);
    CPPUNIT_ASSERT(field.rank() == 3);
    CPPUNIT_ASSERT(field.type_id() == type_id_t::{0.type_id});
}}

//-----------------------------------------------------------------------------
void multidim_field_test_{0.type_name}::test_from_object()
{{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    using namespace pni::io::nx::xml;
   
    h5::nxobject field = create_field<{0.type_name}>(group,
                        "data",shape_t{{3}});
    array_type r{{{0.cpp_data}}};
    CPPUNIT_ASSERT_NO_THROW(write(field,r));

    root = xml::node();
    root.add_child("group",xml::group::object_to_xml(group));
    xml::node field_node;
    CPPUNIT_ASSERT_NO_THROW(field_node = xml::field::object_to_xml(field));
    xml::field::data_to_xml(field_node,r);
    child = root.add_child("group.field",field_node);

    CPPUNIT_ASSERT(xml::field::size(child) == 3);
    CPPUNIT_ASSERT(xml::field::rank(child) == 1);
    CPPUNIT_ASSERT(xml::field::type_id(child) ==
                   type_id_t::{0.type_id});    

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


mdim_data =    [TestData("uint8", "UINT8", "1 2 3","1, 2, 3"),
               TestData("int8",  "INT8",  "-4 3 -10","-4, 3, -10"),
               TestData("uint16","UINT16","200 300 400",
                                          "200, 300, 400"),
               TestData("int16", "INT16", "-234 500 -34",
                                          "-234, 500, -34"),
               TestData("uint32","UINT32","4000 2000 345",
                                          "4000, 2000, 345"),
               TestData("int32", "INT32", "23456 -3453 40392",
                                          "23456, -3453, 40392"),
               TestData("uint64","UINT64","4013945 39458 14056",
                                          "4013945,39458,14056"),
               TestData("int64", "INT64", "-4013945 304213 -405982",
                                          "-4013945, 304213, -405982"),

               TestData("float32", "FLOAT32", "2.3455 -34.e+2 -42.e-5",
                                              "2.3455, -34.e+2, -42.e-5"),
               TestData("float64", "FLOAT64", "-1.233e+4 239e-3 30495.e-8",
                                              "-1.233e+4, 239e-3, 30495.e-8"),
               TestData("float128","FLOAT128","123.24354e-4 40394.e-4 1.23e+5",
                                              "123.24354e-4, 40394.e-4, 1.23e+5"),

               TestData("complex32", "COMPLEX32",
                        "34.+j123.e-3 34.e-2+I98.3 453.98-i743.29",
                        "{34.,123.e-3},{34.e-2,98.3},{453.98,-743.29}"),
               TestData("complex64", "COMPLEX64",
                        "-23.-I8.203 893e+4-j23.12 9.e-8+I732e+3",
                        "{-23.,-8.203},{893e+4,-23.12},{9.e-8,732e+3}"),
               TestData("complex128","COMPLEX128",
                        "123+I340 -I34.9 345.2",
                        "{123,340},{0.,-34.9},{345.2,0.}"),
               TestData("bool_t","BOOL","true true false","true,true,false")

               ]


def generate_filenames(data):
    xmlfile = "multidim_field_{0.type_name}.xml".format(data)
    cppfile = "multidim_field_test_{0.type_name}.cpp".format(data)
    hppfile = "multidim_field_test_{0.type_name}.hpp".format(data)

    return (xmlfile,cppfile,hppfile)

def write_file(fname,data):

    with open(fname,"w") as output_file:
        output_file.write(data)
    

#generate the XML file
for data in mdim_data:
    xml_file,cpp_file,hpp_file = generate_filenames(data)
   
    xml_data = xml_scalar_attribute.format(data)
    write_file(xml_file,xml_data)

    header_data = xml_test_header.format(data)
    write_file(hpp_file,header_data)

    source_data = xml_test_source.format(data)
    write_file(cpp_file,source_data)
    

