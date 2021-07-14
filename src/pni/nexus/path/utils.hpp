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
// ===========================================================================
//
// Created on: Jun 27, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include <pni/types.hpp>
#include <pni/nexus/path/path.hpp>
#include <pni/nexus/path/path_object.hpp>
#include <pni/windows.hpp>


namespace pni{
namespace io{
namespace nexus{


//!
//! @brief check if two paths are matching
//!
//! See the users guide for details about when paths are considered as
//! matching.
//!
//! @param a path as string
//! @param b path as string
//! @return true if the paths are matching, false otherwise
//!
PNINEXUS_EXPORT bool match(const std::string &a,const std::string &b);

//-------------------------------------------------------------------------
//!
//! @brief check if paths are matching
//!
//! See the users guide for details about when paths are considered as
//! matching.
//!
//! @param a reference to first path
//! @param b reference to second path
//! @return true if paths are matching, false otherwise
//!
PNINEXUS_EXPORT bool match(const Path &a,const Path &b);

//-------------------------------------------------------------------------
//!
//! @brief check if path elements match
//!
//! See the users guide for details about when paths elements are
//! considered as matching.
//!
//! @param a reference to first path element
//! @param b reference to second path element
//! @return true if the elements are matching, false otherwise
//!
PNINEXUS_EXPORT bool match(const Path::Element &a,
                        const Path::Element &b);


//------------------------------------------------------------------------
//!
//! @brief create object element
//!
//! This utilty function creates an element for the object section of a
//! Nexus path.
//!
//! @throws value_error if both arguments are empty strings
//!
//! @param name the name of the object
//! @param type the type of the object
//! @return instance of object element
//!
PNINEXUS_EXPORT Path::Element object_element(const std::string &name,
                                          const std::string &type);

//------------------------------------------------------------------------
//!
//! @brief split a nexus path
//!
//! Splits  a given Nexus path in to two parts at  a particular index s
//! of the group part of the path.If the split index is larger or equal
//! the size of the input path an exception will be thrown.
//!
//! The best is to have a look at the following example
//!
//! @code
//! std:::string srep = "file.nx:///entry:NXentry/instrument:NXinstrument/data";
//! nexus::Path path = nexus::Path::from_string(srep);
//! nexus::Path p1,p2;
//! nexus::split_path(path,1,p1,p2);
//!
//! std::cout<<p1<<std::endl;
//! std::cout<<p2<<std::endl;
//!
//! // output
//! // file.nx:///entry:NXentry
//! // instrument:NXinstrument/data
//! @endcode
//!
//! @throws pni::index_error if s exceeds input path size
//! @param p original path
//! @param s index where to split
//! @param p1 first part of the path
//! @param p2 second part of the path
//!
PNINEXUS_EXPORT void split_path(const Path &p,size_t s,Path &p1,Path &p2);

//--------------------------------------------------------------------------
//!
//! @brief split path at last element
//!
//! Split the path at the last element. This is a particularly usefull
//! function for traversing through a path. The only portion of a path
//! which mast not be a group is the last element.
//!
//! @throws pni::index_error
//! @param p reference to the original path
//! @param gp path with groups
//! @param op path with final object
//!
PNINEXUS_EXPORT void split_last(const Path &p,Path &gp,Path &op);

//--------------------------------------------------------------------------
//!
//! @brief check if path has a file section
//!
//! Return true if an instance of nxpath has a non-empty file section.
//!
//! @param p reference to an instance of nxpath
//! @return true if path has a file section, false otherwise
PNINEXUS_EXPORT bool has_file_section(const Path &p);

//------------------------------------------------------------------------
//!
//! @brief check if path has an attribute section
//!
//! Return true if an instance of nxpath has a non-empty attribute section.
//!
//! @param p reference to an instance of nxpath
//! @return true if the path has an attribute section, false otherweise.
PNINEXUS_EXPORT bool has_attribute_section(const Path &p);
    
//------------------------------------------------------------------------
//!
//! @brief check if element is root
//!
//! The root element has the form ("/","NXroot"). This function returns
//! true if the passed element is the root element.
//!
//! @throw value_error if both name and type are empty strings
//!
//! @param e element instance
//! @return true if root element, false otherwise
//!
PNINEXUS_EXPORT bool is_root_element(const Path::Element &e);

//--------------------------------------------------------------------------
//!
//! @brief check if path is absolute
//!
//! @param p path instance
//! @return true if path is absolute, false otherwise
//!
PNINEXUS_EXPORT bool is_absolute(const Path &p);

//--------------------------------------------------------------------------
//!
//! @brief checks name part of a path element
//!
//! This function returns true when the path element passed to it has a
//! name.
//!
//! @param e reference to the element
//! @return true if e has a name, false otherwise
//!
PNINEXUS_EXPORT bool has_name(const Path::Element &e);

//--------------------------------------------------------------------------
//!
//! @brief checks class part of a path element
//!
//! This function returns true when the path element passed to it has a
//! non-empty class string.
//! @param e reference to the element
//! @return true if e has a class, false otherwise
//!
PNINEXUS_EXPORT bool has_class(const Path::Element &e);

//--------------------------------------------------------------------------
//!
//! @brief check element completeness
//!
//! A path element is considered as complete if both, name and class field
//! are not empty. It follows from this that an element refering to a
//! field must never be complete as it has no attribute NX_class. Thus,
//! this function can be used as a first check if a path element referes
//! to a field or to a group.
//!
//! @throws value_error if both parts of the element are empty strings
//!
//! @param e reference to the path element
//! @return true if element is complete, false otherwise
//!
PNINEXUS_EXPORT bool is_complete(const Path::Element &e);

//--------------------------------------------------------------------------
//!
//! @brief check if path is empty
//!
//! A path is considered empty if does not contain
//! @li a file section
//! @li an object section
//! @li and an attribute section
//!
//! If this is the case this function returns true. In fact a default
//! constructed path is empty.
//! @param p path to check
//! @return true if the path is empty
//!
PNINEXUS_EXPORT bool is_empty(const Path &p);

//--------------------------------------------------------------------------
//!
//! @brief join two paths
//!
//! Join two paths together. This operation can only be carried out if the
//! paths satisfiy some criteria
//! @li a must not have an attribute set
//! @li b must not have the file section set
//! @li b must not be an absolute path
//!
//! If one of these requirements is not satisfied value_error is thrown.
//! If one of the paths is empty the other one is returned unchanged.
//!
//! @throws value_error if join requirements are not met by either a or b
//! @param a first path
//! @param b second path
//! @return joined path
//!
PNINEXUS_EXPORT Path join(const Path &a,const Path &b);

//--------------------------------------------------------------------------
//!
//! @brief read path from an input stream
//! @relates Path
//!
//! Constructing a nexus path from a stream. Analogously to the output
//! operator this is used to read a path from a stream-able source.
//!
//! @code
//! nexus::Path p;
//! std::cin>>p;
//! @endcode
//!
//! @param i reference to the input stream
//! @param p reference to the path
//! @return reference to the advanced original stream
//!
PNINEXUS_EXPORT std::istream &operator>>(std::istream &i,Path &p);

//--------------------------------------------------------------------------
//!
//! @brief equality operator for path elements
//! @relates Path
//!
//! Two path elements are considered equal if their name and, in the case
//! of groups class, are equal.
//!
//! @param a reference to the element on the left hand-side of the operator
//! @param b reference to the element on the right hand-side of the operator
//! @return true if the elements are equal
//!
PNINEXUS_EXPORT bool operator==(const Path::Element &a,const Path::Element &b);

//--------------------------------------------------------------------------
//!
//! @brief inequality operator for path elements
//! @relates Path
//!
//!
//! @param a reference to the element on the left hand-side of the operator
//! @param b reference to the element on the right hand-side of the operator
//! @return true if the elements are no equal
//!
PNINEXUS_EXPORT bool operator!=(const Path::Element &a,const Path::Element &b);

//--------------------------------------------------------------------------
//!
//! @brief equality operator for two path objects
//! @relates Path
//!
//! Compare to path objects. They are considered equal if both paths
//! contain the same components.
//!
//! @param lhs reference to the path on the left hand-side
//! @param rhs reference to the path on the right hand-side
//! @return true if equal, false otherwise
//!
PNINEXUS_EXPORT bool operator==(const Path &lhs,const Path &rhs);

//--------------------------------------------------------------------------
//!
//! @brief inequality operator for two path objects
//! @relates Path
//!
//! Compares two path objects and returns true if they are not equal.
//! @param lhs reference to the path on the left hand-side
//! @param rhs reference to the path on the right hand-side
//! @return true if not equal, false otherwise
//!
PNINEXUS_EXPORT bool operator!=(const Path &lhs,const Path &rhs);
    
//------------------------------------------------------------------------
//!
//! @brief output operator for single elements
//! @relates Path::Element
//!
//! Write a single object element to an output stream.
//!
//! @param stream output stream reference
//! @param e object element
//! @return reference to the modified stream
//!
PNINEXUS_EXPORT std::ostream &operator<<(std::ostream &stream,
                                      const Path::Element &e);

//--------------------------------------------------------------------------
//!
//! @brief output operator for a nexus path
//! @relates Path
//!
//! Prints a NeXus path to an output stream. One can either use this to
//! write a Nexus path to standard out
//!
//! @code
//! nexus::Path p = ....;
//! std::cout<<p<<std::endl;
//! @endcode
//!
//! or to a string using the stringstream operator
//!
//! @code
//! std::stringstream ss;
//! ss<<p;
//! @endcode
//!
//! @param stream reference to the output stream
//! @param p reference to the path
//! @return reference to the output operator
//!
PNINEXUS_EXPORT std::ostream &operator<<(std::ostream &stream,const Path &p);

//!
//! @brief return true if a NeXus path is unique
//!
//! A NeXus path is considered unique if all elements in its object section
//! have an object name. In this case the path can be unamiguously mapped
//! to an HDF5 path.
//!
//! @param path reference to the NeXus path
//! @return true if path is unique, false otherwise.
//!
PNINEXUS_EXPORT bool is_unique(const Path &path);

//!
//! @brief get the NeXus path for an HDF5 node
//!
//! @param node reference to the HDF5 node
//!
//! @pre the node must be a valid HDF5 object
//!
PNINEXUS_EXPORT Path get_path(const hdf5::node::Node &node);

//!
//! @brief get the NeXus path for an HDF5 attribute
//!
//! @param attribute reference to the attribute for which to obtain the path
//!
//! @pre the attribute must be a valid HDF5 object
//!
PNINEXUS_EXPORT Path get_path(const hdf5::attribute::Attribute &attribute);

//!
//! @brief get NeXus path for an HDF5 link
//!
//! As a link is just a name its last element will never have the base_class
//! attribute set even if the link references a group. This ensures that
//! this function also works with unresolvable links.
//!
//! @param link reference to an HDF5 link
//! @pre the parent of the link must be valid
//! @return instance of a NeXus path
PNINEXUS_EXPORT Path get_path(const hdf5::node::Link &link);


//!
//! @brief search for objects
//!
//! Searches recursively below `base` and return a list of path objects which
//! match `path`.
//! The function distinguishes two situations
//!
//! * if `path` is a relative path the paths of all child objects of
//!   `base` are taken relative to `base`
//! * if `path` is an absolute path the full path of each child must match.
//!
//! There are some important notes when it comes to dealing with links.
//! Under the hood get_objects iterates over links rather than nodes. This
//! allows the function to handle unresolvable links. If a particular link is
//! resolvable it will be converted into the appropriate node type. In the
//! case of an unresolvable link the link itself will be stored.
//!
//! @throws std::runtime_error in case of a failure
//! @param base the base group from which to start the search
//! @param path the path which to match
//!
//! @return a list of path objects
//!
PNINEXUS_EXPORT PathObjectList get_objects(const hdf5::node::Group &base,
                                        const Path &path);

//end of namespace
} // namespace nexus
} // namespace io
} // namespace pni
