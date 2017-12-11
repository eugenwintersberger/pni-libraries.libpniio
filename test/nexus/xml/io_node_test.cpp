//
// (c) Copyright 2017 DESY
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Dec 11, 2017
//
#include <boost/test/unit_test.hpp>

#include <boost/property_tree/xml_parser.hpp>
#include <pni/io/nexus/xml/io_node.hpp>
#include <pni/io/nexus/xml/field_node.hpp>
#include <vector>

using namespace pni::io::nexus;

BOOST_AUTO_TEST_SUITE(NexusXMLTest)
BOOST_AUTO_TEST_SUITE(IONodeTest)


BOOST_AUTO_TEST_SUITE(InqueryTests)

//-------------------------------------------------------------------------
xml::Node get_object(const std::string &f,const std::string &n)
{
  xml::Node root  = xml::create_from_file(f);
  return root.get_child(n);
}


//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_name)
{
  xml::Node n = get_object("io_node/object1.xml","object1");
  BOOST_CHECK_EQUAL(xml::IONode::name(n),"hello");

  n = get_object("io_node/object1.xml","object2");
  BOOST_CHECK_THROW(xml::IONode::name(n),pni::core::key_error);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_size)
{
  xml::Node n = get_object("io_node/object2.xml","object1");
  BOOST_CHECK_EQUAL(xml::IONode::size(n),1);

  n = get_object("io_node/object2.xml","object2");
  BOOST_CHECK_EQUAL(xml::IONode::size(n),40);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_rank)
{
  xml::Node n = get_object("io_node/object2.xml","object1");
  BOOST_CHECK_EQUAL(xml::FieldNode::rank(n),0);

  n = get_object("io_node/object2.xml","object2");
  BOOST_CHECK_EQUAL(xml::FieldNode::rank(n),2);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_shape)
{
  hdf5::Dimensions s = xml::IONode::shape(get_object("io_node/object2.xml","object1"));
  hdf5::Dimensions r{1};
  BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(),s.end(),r.begin(),r.end());

  s = xml::FieldNode::shape(get_object("io_node/object2.xml","object2"));
  r = hdf5::Dimensions{10,4};
  BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(),s.end(),r.begin(),r.end());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(DataFromXMLTest)


//-------------------------------------------------------------------------
xml::Node get_object(const std::string &f,const std::string &n)
{
  xml::Node root  = xml::create_from_file(f);
  return root.get_child(n);
}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_scalar)
{
  xml::Node o = get_object("io_node/object3.xml","field1");
  auto data = xml::IONode::data_from_xml<pni::core::float32>(o);
  BOOST_CHECK_CLOSE(pni::core::float32(1.23),data,1.e-6);

}

//-------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_array)
{
  typedef std::vector<pni::core::uint32> vector_type;

  xml::Node o = get_object("io_node/object3.xml","field2");
  auto data = xml::IONode::data_from_xml<vector_type>(o);
  BOOST_CHECK_EQUAL(data.size(),6);

  for(pni::core::uint32 i=0;i<6;++i)
    BOOST_CHECK_EQUAL(data[i],i+1);
}

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_string)
{
  using namespace pni::core;
  xml::Node o = get_object("io_node/object3.xml","field3");

  BOOST_CHECK_EQUAL(xml::IONode::type_id(o),type_id_t::STRING);
  auto text = xml::IONode::data_from_xml<std::string>(o);
  boost::algorithm::trim(text);
  BOOST_CHECK_EQUAL(text,"This is a stupid text");
}

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_bool)
{
  using namespace pni::core;
  xml::Node o = get_object("io_node/object3.xml","field4");
  BOOST_CHECK(xml::IONode::data_from_xml<bool_t>(o));

  o = get_object("io_node/object3.xml","field5");
  BOOST_CHECK(!xml::IONode::data_from_xml<bool_t>(o));

  o = get_object("io_node/object3.xml","field6");
  BOOST_CHECK_THROW(xml::IONode::data_from_xml<bool_t>(o),
                    pni::io::parser_error);

  o = get_object("io_node/object3.xml","field7");
  BOOST_CHECK_THROW(xml::IONode::data_from_xml<bool_t>(o),
                    pni::io::parser_error);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
