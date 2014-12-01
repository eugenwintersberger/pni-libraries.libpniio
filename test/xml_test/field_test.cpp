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
#include "field_test.hpp"
#include "../uniform_distribution.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(field_test);

void field_test::setUp()
{
    file = h5::nxfile::create_file("xml_field_test.nxs",true);
    root_group = file.root();
}

//-----------------------------------------------------------------------------
void field_test::tearDown()
{
    root_group.close();
    field.close();
    file.close();
}

//-----------------------------------------------------------------------------
void field_test::setup_xml(const string &fname)
{
    root = xml::create_from_file(fname);
    child = root.get_child("field");
}

//-----------------------------------------------------------------------------
void field_test::test_from_xml_1()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    setup_xml("field1.xml");

    CPPUNIT_ASSERT_NO_THROW(field = xml::field::object_from_xml(root_group,child));
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
void field_test::test_name()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    setup_xml("field1.xml");
    CPPUNIT_ASSERT(xml::field::name(child)=="data");
    setup_xml("field3.xml");
    CPPUNIT_ASSERT_THROW(xml::field::name(child),pni::io::parser_error);
}

//-----------------------------------------------------------------------------
void field_test::test_size()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    setup_xml("field1.xml");
    CPPUNIT_ASSERT(xml::field::size(child)==1);
    setup_xml("field5.xml");
    CPPUNIT_ASSERT(xml::field::size(child)== 100*55*10);
}

//-----------------------------------------------------------------------------
void field_test::test_rank()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    setup_xml("field1.xml");
    CPPUNIT_ASSERT(xml::field::rank(child)==0);
    setup_xml("field5.xml");
    CPPUNIT_ASSERT(xml::field::rank(child)==3);
}

//-----------------------------------------------------------------------------
void field_test::test_shape()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    setup_xml("field1.xml");
    shape_t s;
    CPPUNIT_ASSERT_NO_THROW(s = xml::field::shape(child));
    CPPUNIT_ASSERT(s == shape_t{1});

    setup_xml("field5.xml");
    CPPUNIT_ASSERT_NO_THROW(s = xml::field::shape(child));
    CPPUNIT_ASSERT(s == shape_t({100,55,10}));
}

//-----------------------------------------------------------------------------
void field_test::test_long_name()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    setup_xml("field1.xml");
    CPPUNIT_ASSERT(xml::field::long_name(child)=="motor along x-axis");
    setup_xml("field5.xml");
    CPPUNIT_ASSERT(xml::field::long_name(child)=="motor along x-axis");

    setup_xml("field3.xml");
    CPPUNIT_ASSERT_THROW(xml::field::long_name(child),pni::io::parser_error);
}

//-----------------------------------------------------------------------------
void field_test::test_unit()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    setup_xml("field1.xml");
    CPPUNIT_ASSERT(xml::field::unit(child)=="m");
    setup_xml("field3.xml");
    CPPUNIT_ASSERT_THROW(xml::field::unit(child),pni::io::parser_error);
}

//-----------------------------------------------------------------------------
void field_test::test_from_xml_2()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    setup_xml("field2.xml");

    CPPUNIT_ASSERT_NO_THROW(field = xml::field::object_from_xml(root_group,child));
    CPPUNIT_ASSERT(is_valid(field));
    CPPUNIT_ASSERT(get_rank(field) == 1);
    CPPUNIT_ASSERT(get_size(field) == 1);
    CPPUNIT_ASSERT(get_type(field) == type_id_t::FLOAT32);

}

//-----------------------------------------------------------------------------
void field_test::test_from_xml_2_with_object()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    setup_xml("field2.xml");
    
    h5::nxobject parent(root_group);
    CPPUNIT_ASSERT_NO_THROW(field = xml::field::object_from_xml(parent,child));
    CPPUNIT_ASSERT(is_valid(field));
    CPPUNIT_ASSERT(get_rank(field) == 1);
    CPPUNIT_ASSERT(get_size(field) == 1);
    CPPUNIT_ASSERT(get_type(field) == type_id_t::FLOAT32);

}

//-----------------------------------------------------------------------------
void field_test::test_from_xml_3()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    setup_xml("field3.xml");
    CPPUNIT_ASSERT_THROW(xml::field::object_from_xml(root_group,child),
                         pni::io::parser_error);
    CPPUNIT_ASSERT_THROW(xml::field::object_from_xml(h5::nxobject(root_group),child),
                         pni::io::parser_error);
                                                
}

//-----------------------------------------------------------------------------
void field_test::test_from_xml_4()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    setup_xml("field4.xml");
    CPPUNIT_ASSERT_THROW(xml::field::object_from_xml(root_group,child),
                         pni::io::parser_error);
}

//-----------------------------------------------------------------------------
void field_test::test_from_xml_5()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    setup_xml("field5.xml");
    field = xml::field::object_from_xml(root_group,child);

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
void field_test::test_to_xml_1()
{
    typedef xml::attribute_data<string> attr_data;
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    shape_t s{3,4};
    field = root_group.create_field<float32>("data",s);
    field.attributes.create<string>("units").write("nm");
    field.attributes.create<string>("long_name").write("testing data");

    xml::node n = xml::field::object_to_xml(field);

    CPPUNIT_ASSERT(attr_data::read(n,"name")=="data");
    CPPUNIT_ASSERT(attr_data::read(n,"type")=="float32");
    CPPUNIT_ASSERT(attr_data::read(n,"units")=="nm");
    CPPUNIT_ASSERT(attr_data::read(n,"long_name")=="testing data");

    //test with object
    n = xml::field::object_to_xml(h5::nxobject(field));
    CPPUNIT_ASSERT(attr_data::read(n,"name")=="data");
    CPPUNIT_ASSERT(attr_data::read(n,"type")=="float32");
    CPPUNIT_ASSERT(attr_data::read(n,"units")=="nm");
    CPPUNIT_ASSERT(attr_data::read(n,"long_name")=="testing data");
}

//-----------------------------------------------------------------------------
void field_test::test_to_xml_2()
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
    xml::node n = xml::field::object_to_xml(field);
    root.add_child("field",n);

    CPPUNIT_ASSERT(attr_data::read(n,"name")=="data");
    CPPUNIT_ASSERT(attr_data::read(n,"type")=="float32");
    CPPUNIT_ASSERT(attr_data::read(n,"units")=="nm");
    CPPUNIT_ASSERT(attr_data::read(n,"long_name")=="testing data");
    std::cout<<root<<std::endl;
}

//----------------------------------------------------------------------------
void field_test::test_to_xml_3()
{
    using namespace pni::io::nx::xml;
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    field = root_group.create_field<string>("text");
    field.write("hello world");
    field.attributes.create<string>("units").write("none");
    field.attributes.create<string>("long_name").write("some text");

    root = xml::node();
    xml::node n = xml::field::object_to_xml(field);
    root.add_child("field",n);
    std::cout<<root<<std::endl;
}

//---------------------------------------------------------------------------
void field_test::test_read_data_scalar()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    setup_xml("field_test_data_scalar.xml");
    
    array data = xml::field::data_from_xml(child);
    CPPUNIT_ASSERT(data.size()==1);
    CPPUNIT_ASSERT(data.rank()==1);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(float32(1.234),data[0].as<float32>(),1.e-8);
} 

//---------------------------------------------------------------------------
void field_test::test_read_data_array()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    setup_xml("field_test_data_array.xml");
    std::vector<int32> ref_data{-1,2,-3,4,-5,6};

    array data = xml::field::data_from_xml(child);
    auto iter = ref_data.begin();
    for(auto d:data)
        CPPUNIT_ASSERT(d.as<int32>()==*(iter++));
}

//----------------------------------------------------------------------------
void field_test::test_write_data_scalar()
{
    using namespace boost::property_tree;
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    array data = make_array(type_id_t::FLOAT32,shape_t{1});
    data[0] = float32(1.234);

    field = root_group.create_field<float32>("temperature");
    field.attributes.create<string>("long_name").write("sample temperature");
    field.attributes.create<string>("units").write("centigrade");

    root = xml::node();
    xml::node n = xml::field::object_to_xml(field);
    xml::field::data_to_xml(data,n);
    root.add_child("field",n);
    write_xml("test_field_scalar.xml",root);
    CPPUNIT_ASSERT(!std::system("xmldiff -c test_field_scalar.xml field_test_data_scalar.xml"));
}

//----------------------------------------------------------------------------
void field_test::test_write_data_array()
{
    using namespace boost::property_tree;
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    std::vector<int32> buffer{-1,2,-3,4,-5,6};
    array data = make_array(type_id_t::INT32,shape_t{3,2});
    std::copy(buffer.begin(),buffer.end(),data.begin());

    field = root_group.create_field<int32>("matrix",shape_t{3,2});
    field.attributes.create<string>("long_name").write("random data");
    field.attributes.create<string>("units").write("a.u.");

    root = xml::node();
    xml::node n = xml::field::object_to_xml(field);
    xml::field::data_to_xml(data,n);
    root.add_child("field",n);
    write_xml("test_field_array.xml",root);
    CPPUNIT_ASSERT(!std::system("xmldiff -c test_field_array.xml field_test_data_array.xml"));
}


