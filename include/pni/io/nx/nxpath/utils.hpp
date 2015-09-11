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
//
// Created on: Jun 27, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include <pni/core/types.hpp>
#include "nxpath.hpp"


namespace pni{
namespace io{
namespace nx{    

    //!
    //! \ingroup nxpath_utils
    //! \brief make a relative path
    //! 
    //! Take a given path and make it relative with respect to a particular 
    //! other path (typically the path of a parent object). 
    //! 
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    //! nxpath entry = nxpath::from_string("/:NXentry");
    //! nxpath det   = nxpath::from_string("/:NXentry/:NXinstrument/:NXdetector");
    //! 
    //! nxpath det_rel = make_relative(entry,det);
    //! std::cout<<det_rel<<std::endl;
    //! // output: :NXinstrument/:NXdetector
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //! 
    //! For this procedure to work both paths must be absolute as we need a
    //! common starting point (which would be the root group). In the case that 
    //! Both 
    //! 
    //! * both paths must be absolute (as we need a common starting point which 
    //!   would be the root group
    //! * if boths paths have a file section it must be equal 
    //! * if 
    //! 
    //! A typical application would be to find all instances of `NXdetector` 
    //! in a given instrument group. 
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    //! 
    //! std::vector<h5::nxobject> detectors; 
    //! 
    //! 
    nxpath make_relative(const nxpath &parent_path,const nxpath &orig_path);

    //!
    //! \ingroup nxpath_utils
    //! \brief check if two paths are matching
    //! 
    //! See the users guide for details about when paths are considered as 
    //! matching. 
    //! 
    //! \param a path as string
    //! \param b path as string
    //! \return true if the paths are matching, false otherwise
    //!
    bool match(const pni::core::string &a,const pni::core::string &b);

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup nxpath_utils
    //! \brief check if paths are matching
    //! 
    //! See the users guide for details about when paths are considered as 
    //! matching.
    //! 
    //! \param a reference to first path
    //! \param b reference to second path
    //! \return true if paths are matching, false otherwise
    //! 
    bool match(const nxpath &a,const nxpath &b);

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup nxpath_utils
    //! \brief check if path elements match
    //! 
    //! See the users guide for details about when paths elements are
    //! considered as matching.
    //! 
    //! \param a reference to first path element
    //! \param b reference to second path element
    //! \return true if the elements are matching, false otherwise
    //! 
    bool match(const nxpath::element_type &a,const nxpath::element_type &b);


    //------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_utils
    //! \brief create object element
    //!
    //! This utilty function creates an element for the object section of a 
    //! Nexus path. 
    //!
    //! \throws value_error if both arguments are empty strings
    //!
    //! \param name the name of the object
    //! \param type the type of the object
    //! \return instance of object element
    nxpath::element_type object_element(const pni::core::string &name,
                                        const pni::core::string &type);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_utils
    //! \brief split a nexus path
    //!
    //! Splits  a given Nexus path in to two parts at  a particular index s 
    //! of the group part of the path.If the split index is larger or equal 
    //! the size of the input path an exception will be thrown.
    //!
    //! The best is to have a look at the following example
    //!
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    //! string srep = "file.nx:///entry:NXentry/instrument:NXinstrument/data";
    //! nxpath path = nxpath::from_string(srep);
    //! nxpath p1,p2;
    //! split_path(path,1,p1,p2);
    //! 
    //! std::cout<<p1<<std::endl;
    //! std::cout<<p2<<std::endl;
    //! 
    //! // output
    //! // file.nx:///entry:NXentry
    //! // instrument:NXinstrument/data
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //! 
    //! \throws pni::core::index_error if s exceeds input path size
    //! \param p original path
    //! \param s index where to split 
    //! \param p1 first part of the path
    //! \param p2 second part of the path
    //!
    void split_path(const nxpath &p,size_t s,nxpath &p1,nxpath &p2);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_utils
    //! \brief split path at last element
    //!
    //! Split the path at the last element. This is a particularly usefull 
    //! function for traversing through a path. The only portion of a path 
    //! which mast not be a group is the last element. 
    //! 
    //! \throws pni::core::index_error 
    //! \param p reference to the original path
    //! \param gp path with groups
    //! \param op path with final object
    //!
    void split_last(const nxpath &p,nxpath &gp,nxpath &op);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_utils
    //! \brief check if path has a file section
    //! 
    //! Return true if an instance of nxpath has a non-empty file section. 
    //!
    //! \param p reference to an instance of nxpath
    //! \return true if path has a file section, false otherwise
    bool has_file_section(const nxpath &p);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_utils
    //! \brief check if path has an attribute section
    //!
    //! Return true if an instance of nxpath has a non-empty attribute section.
    //! 
    //! \param p reference to an instance of nxpath
    //! \return true if the path has an attribute section, false otherweise.
    bool has_attribute_section(const nxpath &p);
    
    //------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_utils
    //! \brief check if element is root
    //!
    //! The root element has the form ("/","NXroot"). This function returns
    //! true if the passed element is the root element.
    //! 
    //! \throw value_error if both name and type are empty strings
    //! 
    //! \param e element instance
    //! \return true if root element, false otherwise
    //!
    bool is_root_element(const nxpath::element_type &e);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_utils
    //!
    //! \param p path instance
    //! \return true if path is absolute, false otherwise
    //!
    bool is_absolute(const nxpath &p);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_utils
    //! \brief checks name part of a path element
    //!
    //! This function returns true when the path element passed to it has a 
    //! name. 
    //! 
    //! \param e reference to the element
    //! \return true if e has a name, false otherwise
    //!
    bool has_name(const nxpath::element_type &e);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_utils
    //! \brief checks class part of a path element
    //! 
    //! This function returns true when the path element passed to it has a
    //! non-empty class string. 
    //! \param e reference to the element
    //! \return true if e has a class, false otherwise
    //!
    bool has_class(const nxpath::element_type &e);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_utils
    //! \brief check element completness
    //! 
    //! A path element is considered as complete if both, name and class field 
    //! are not empty. It follows from this that an element refering to a 
    //! field must never be complete as it has no attribute NX_class. Thus, 
    //! this function can be used as a first check if a path element referes 
    //! to a field or to a group. 
    //! 
    //! \throws value_error if both parts of the element are empty strings
    //! 
    //! \param e reference to the path element
    //! \return true if element is complete, false otherwise
    //!
    bool is_complete(const nxpath::element_type &e);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_utils
    //! \brief check if path is empty
    //! 
    //! A path is considered empty if does not contain
    //! \li a file section
    //! \li an object section
    //! \li and an attribute section
    //! 
    //! If this is the case this function returns true. In fact a default 
    //! constructed path is empty.
    //! \param p path to check
    //! \return true if the path is empty
    bool is_empty(const nxpath &p);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_utils
    //! \brief join two paths
    //! 
    //! Join two paths together. This operation can only be carried out if the 
    //! paths satisfiy some criteria
    //! \li a must not have an attribute set
    //! \li b must not have the file section set
    //! \li b must not be an absolute path
    //! 
    //! If one of these requirements is not satisfied value_error is thrown. 
    //! If one of the paths is empty the other one is returned unchanged.
    //! 
    //! \throws value_error if join requirements are not met by either a or b
    //! \param a first path 
    //! \param b second path
    //! \return joined path 
    nxpath join(const nxpath &a,const nxpath &b);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_operators
    //! \brief read path from an input stream
    //! \relates nxpath
    //! 
    //! Constructing a nexus path from a stream. Analogously to the output 
    //! operator this is used to read a path from a stream-able source.
    //!
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    //! nxpath p;
    //! std::cin>>p;
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //! 
    //! \param i reference to the input stream
    //! \param p reference to the path
    //! \return reference to the advanced original stream
    //!
    std::istream &operator>>(std::istream &i,nxpath &p);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_operators
    //! \brief equality operator for path elements
    //! \relates nxpath
    //! 
    //! Two path elements are considered equal if their name and, in the case 
    //! of groups class, are equal. 
    //! 
    //! \param a reference to the element on the left handside of the operator
    //! \param b reference to the element on the right handside of the operator
    //! \return true if the elements are equal
    //! 
    bool operator==(const nxpath::element_type &a,
                    const nxpath::element_type &b);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_operators
    //! \brief inequality operator for path elements
    //! \relates nxpath
    //! 
    //! 
    //! \param a reference to the element on the left handside of the operator
    //! \param b reference to the element on the right handside of the operator
    //! \return true if the elements are no equal
    //! 
    bool operator!=(const nxpath::element_type &a,
                    const nxpath::element_type &b);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_operators
    //! \brief equality operator for two path objects
    //! \relates nxpath
    //!
    //! Compare to path objects. They are considered equal if both paths 
    //! contain the same components. 
    //! 
    //! \param lhs reference to the path on the left handside
    //! \param rhs reference to the path on the right handside
    //! \return true if equal, false otherwise
    //!
    bool operator==(const nxpath &lhs,const nxpath &rhs);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_operators
    //! \brief inequality operator for two path objects
    //! \relates nxpath
    //!
    //! Compars two path objects and returns true if they are not equal. 
    //! \param lhs reference to the path on the left handside
    //! \param rhs reference to the path on the right handside
    //! \return true if not equal, false otherwise
    //!
    bool operator!=(const nxpath &lhs,const nxpath &rhs);
    
    //------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_operators
    //! \brief output operator for single elements
    //! \relates nxpath
    //!
    //! Write a single object element to an output stream. 
    //!
    //! \param stream output stream reference
    //! \param e object element
    //! \return reference to the modified stream
    //!
    std::ostream &operator<<(std::ostream &stream,
                             const nxpath::element_type &e);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_operators
    //! \brief output operator for a nexus path
    //! \relatex nxpath
    //! 
    //! Prints a nexus path to an output stream. One can either use this to 
    //! write a Nexus path to standard out 
    //!
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    //! nxpath p = ....;
    //! std::cout<<p<<std::endl;
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //! 
    //! or to a string using the stringstream operator
    //!
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    //! std::stringstream ss;
    //! ss<<p;
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //!
    //! \param stream reference to the output stream
    //! \param p reference to the path
    //! \return reference to the output operator
    //!
    std::ostream &operator<<(std::ostream &stream,const nxpath &p);

//end of namespace
}
}
}
