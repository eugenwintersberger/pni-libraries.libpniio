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
//************************************************************************
// Created on: Jul 11, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem.hpp>
#include <pni/io/windows.hpp>
#include <pni/io/parsers.hpp>

namespace pni{
namespace io{
namespace nexus{
namespace xml{    

//!
//! @ingroup nexus_xml_classes
//! @brief alias for ptree
//!
//! This alias creates the new type name node which can be used within
//! the xml namespace instead of boost::property_tree::ptree;
//!
class PNIIO_EXPORT Node : public boost::property_tree::ptree
{
  private:

    //!
    //! @brief create an attribute path
    //!
    //! This function is intended for internal use only. It creates a valid
    //! attribute path from an attribute name.
    //!
    //! @param name the name of the attribute
    //! @return a valid property tree attribute path
    //!
    static std::string attribute_path(const std::string &attribute_name);
  public:
    using boost::property_tree::ptree::ptree;

    Node(const boost::property_tree::ptree &ptree);
    Node();

    //-------------------------------------------------------------------------
    //!
    //! @brief  create xml node from string
    //!
    //! Parses a string provided by the user and returns an XML node from it.
    //!
    //! \throws parser_error in case of parsing problems
    //! \param s string from which to read the data
    //! \return node instance
    //!
    static Node from_string(const std::string &s);

    //!
    //! @brief create xml node from file
    //!
    //! Reads XML data from a file and returns an XML node refering to the
    //! root element of the XML tree.
    //!
    //! @throws pni::io::parser_error in case of parsing issues
    //! @throws file_error in case of problems opening the file
    //! @param path the path to the file from which to read data
    //! @return node instance
    //!
    static Node from_file(const boost::filesystem::path &path);

    //!
    //! @brief get attribute node
    //!
    //! Returns an attribute node from its parent node.
    //!
    //! @throws key_error if the attribute does not exist
    //! @throws parser_error in case of any other error
    //!
    //! @param parent the node from which to retrieve the attribute
    //! @param name the name of the attribute
    //! @param node representing the attribute
    //!
    Node attribute(const std::string &name) const;

    //-------------------------------------------------------------------------
    //!
    //! @ingroup nexus_xml_classes
    //! @brief check for attribute existence
    //!
    //! Returns true if the node parent has a an attribute name attached to it.
    //! Otherwise false is returned.
    //!
    //! @param parent reference to the parent node
    //! @param name the attributes name
    //! @return true if the attribute exists, false otherwise
    //!
    bool has_attribute(const std::string &name) const;

    //!
    //! @brief get name of a node
    //!
    //! Return the name of a node as determined by the content of its
    //! name attribute. This is a convenience function.
    //! If the node does not have a name attribute an empty string is
    //! returned.
    //!
    //! @param n node with name attribute
    //! @return content of the name attribute of a tag
    //!
    std::string name() const;

    std::string str_data() const;

    void data(const std::string &cdata);

    //Node get_child_by_name(const std::string &name) const;

    template<typename T> T data() const
    {
      pni::io::parser<T> p;

      return p(str_data());
    }

};

//-------------------------------------------------------------------------
//!
//! @ingroup nexus_xml_classes
//! @brief XML stream output
//!
//! Write property tree structure as XML to an output stream.
//! @param o reference output stream
//! @param n node to write to the output stream
//! @return modified output stream
//!
PNIIO_EXPORT std::ostream &operator<<(std::ostream &o,const Node &n);


//end of namespace
} // namespace xml
} // namespace nexus
} // namespace io
} // namespace pni
