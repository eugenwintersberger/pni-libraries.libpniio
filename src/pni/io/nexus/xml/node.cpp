//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 11, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <sstream>
#include <fstream>
#include <locale>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <algorithm>

#include <pni/io/exceptions.hpp>
#include <pni/io/nexus/xml/node.hpp>

namespace pni{
namespace io{
namespace nexus{
namespace xml{

using namespace pni::core;

Node::Node(const boost::property_tree::ptree &ptree):
    boost::property_tree::ptree(ptree)
{}

Node::Node():
    boost::property_tree::ptree()
{}

Node Node::from_string(const std::string &s)
{
  std::stringstream stream(s.c_str());
  Node t;
  try
  {
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml(stream,tree);
    t = tree;
  }
  catch(boost::property_tree::ptree_bad_data &)
  {
    throw pni::io::parser_error(EXCEPTION_RECORD,
                                "A parser error occured due to invalid input data!");
  }
  catch(boost::property_tree::ptree_bad_path &)
  {
    throw pni::io::parser_error(EXCEPTION_RECORD,
                                "A parser error occured as the requested object could not"
                                " be resolved!");
  }
  catch(boost::property_tree::ptree_error &)
  {
    throw pni::io::parser_error(EXCEPTION_RECORD,
                                "A general parser error has occured!");
  }
  catch(...)
  {
    //whatever exception is thrown here is related to parsing
    throw pni::io::parser_error(EXCEPTION_RECORD,
                                "A unkown fatal error parsing XML string has occured!");
  }

  return t;
}

//-------------------------------------------------------------------------
Node Node::from_file(const boost::filesystem::path &path)
{
  std::ifstream stream(path.string());
  if(!stream.is_open())
  {
    std::stringstream ss;
    ss<<"Error opening "<<path<<" for reading!";
    throw file_error(EXCEPTION_RECORD,ss.str());
  }


  Node t;
  try
  {
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml(stream,tree);
    t = tree;
  }
  catch(...)
  {
    std::stringstream ss;
    ss<<"Error parsing XML file "<<path<<"!";
    throw pni::io::parser_error(EXCEPTION_RECORD,ss.str());
  }

  return t;
}

//------------------------------------------------------------------------
std::string Node::attribute_path(const std::string &attribute_name)
{
  return "<xmlattr>."+attribute_name;
}

//------------------------------------------------------------------------
Node Node::attribute(const std::string &name) const
{
  try
  {
    return this->get_child(attribute_path(name));
  }
  catch(boost::property_tree::ptree_bad_path &)
  {
    throw key_error(EXCEPTION_RECORD, "Attribute not found!");
  }
  catch(...)
  {
    throw parser_error(EXCEPTION_RECORD,
                       "Unkown error when retrieving attribute!");
  }
}

//------------------------------------------------------------------------
bool Node::has_attribute(const std::string &name) const
{
  auto attr = this->get_child_optional(attribute_path(name));

  return attr.is_initialized();
}

//------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const Node &n)
{
#if BOOST_VERSION > 105500
  using key_type = typename Node::key_type;
#else
  using key_type = typename Node::key_type::value_type;
#endif
  boost::property_tree::xml_writer_settings<key_type> settings('\t',1);

  using boost::property_tree::ptree;
  boost::property_tree::write_xml(o,dynamic_cast<const ptree&>(n),settings);
  return o;
}

//-------------------------------------------------------------------------
std::string Node::name() const
{
  if(has_attribute("name"))
    return attribute("name").str_data();
  else
    return string();
}

////-------------------------------------------------------------------------
//Node Node::get_child_by_name(const std::string &name) const
//{
//  auto result = std::find(begin(),end(),[&name](const Node &node) { node.name() == name; });
//  if()
//  for(auto child: parent)
//    if(get_name(child.second)==name) return child.second;
//
//  return Node();
//}

std::string Node::str_data() const
{
  std::string data = boost::property_tree::ptree::data();
  boost::algorithm::trim(data);

  //we do not care about line breaks - the data of a node is considered
  //a linear stream of elements.
  std::replace(data.begin(),data.end(),'\n',' ');

  return data;
}

//-------------------------------------------------------------------------
void Node::data(const std::string &cdata)
{
  put_value(cdata);
}


//end of namespace
} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
