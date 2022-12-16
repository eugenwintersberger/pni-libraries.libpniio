//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
//************************************************************************
// Created on: Jul 11, 2013
//     Authors:
//             Eugen Wintersberger <eugen.wintersberger@desy.de>
//             Jan Kotanski <jan.kotanski@desy.de>
//
#pragma once

#include <pni/types.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem.hpp>
#include <pni/windows.hpp>
#include <pni/parsers.hpp>

namespace pni{
namespace nexus{
namespace xml{    
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
//!
//! @ingroup nexus_xml_classes
//! @brief alias for ptree
//!
//! This alias creates the new type name node which can be used within
//! the xml namespace instead of boost::property_tree::ptree;
//!
class PNINEXUS_EXPORT Node : public boost::property_tree::ptree
{
#ifdef _MSC_VER
#pragma warning(pop)
#endif
  private:

    //!
    //! @brief create an attribute path
    //!
    //! This function is intended for internal use only. It creates a valid
    //! attribute path from an attribute name.
    //!
    //! @param attribute_name the name of the attribute
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
    //! @throws pni::parser_error in case of parsing issues
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
    //! @param name the name of the attribute
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
    //! @return content of the name attribute of a tag
    //!
    std::string name() const;

    std::string str_data() const;

    void data(const std::string &cdata);

    //Node get_child_by_name(const std::string &name) const;

    template<typename DataT> DataT data() const
    {
      pni::parser<DataT> p;

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
PNINEXUS_EXPORT std::ostream &operator<<(std::ostream &o,const Node &n);


//end of namespace
} // namespace xml
} // namespace nexus
} // namespace pni
