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

namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;

    //!
    //! \ingroup xml_classes
    //! \brief alias for ptree
    //! 
    //! This alias creates the new type name node which can be used within 
    //! the xml namespace instead of boost::property_tree::ptree;
    //!
    using node = boost::property_tree::ptree;


    //-------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief create xml node from string
    //!
    //! \throws parser_error in case of parsing problems
    //! \param s string from which to read the data
    //! \return node instance
    //!
    node create_from_string(const string &s);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief create xml node from file
    //! 
    //! \throws pni::io::parser_error in case of parsing issues
    //! \throws file_error in case of problems opening the file
    //! \param s name of the file
    //! \return node instance
    //!
    node create_from_file(const string &s);

    //------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief create an attribute path
    //! 
    //! This function is intended for internal use only. It creates a valid 
    //! attribute path from an attribute name.
    //! 
    //! \param name the name of the attribute
    //! \return a valid property tree attribute path
    //! 
    string attribute_path(const string &name);


    //------------------------------------------------------------------------
    //! 
    //! \ingroup xml_classes
    //! \brief get attribute node 
    //! 
    //! Returns an attribute node from its parent node. 
    //! 
    //! \throws key_error if the attribute does not exist
    //! \throws parser_error in case of any other error
    //!
    //! \param parent the node from which to retrieve the attribute
    //! \param name the name of the attribute
    //! \return node representing the attribute
    //! 
    node get_attribute(const node &parent,const string &name);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief check for attribute existence
    //! 
    //! Returns true if the node parent has a an attribute name attached to it.
    //! Otherwise false is returned.
    //!
    //! \param parent reference to the parent node
    //! \param name the attributes name
    //! \return true if the attribute exists, false otherwise
    //!
    bool has_attribute(const node &parent,const string &name);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief XML stream output
    //! 
    //! Write property tree structure as XML to an output stream.
    //! \param o reference output stream
    //! \param n node to write to the output stream
    //! \return modified output stream
    //!
    std::ostream &operator<<(std::ostream &o,const node &n);


//end of namespace
}
}
}
}
