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
    using namespace pni::core;

    //forward declaration of path 
    class nxpath;

    //! \ingroup nxpath_code 
    //! \brief append element 
    //! 
    //! Append an element to a path. 
    //! 
    void append(nxpath &p,const string &gname,const string &gclass);

    //!
    //! \ingroup nxpath_code
    //! \brief prepend element
    //! 
    //! Prepend an element to the beginning of a path.
    //! 
    //! \param p path 
    //! \param gname group name of the element
    //! \param gclass group class of the element
    //!
    void prepend(nxpath &p,const string &gname,const string &gclass);


    //------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
    //! \brief split a nexus path
    //!
    //! Splits  a given Nexus path in to two parts at  a particular index s 
    //! of the group part of the path.If the split index is larger or equal 
    //! the size of the input path an exception will be thrown.
    //!
    //! The best is to have a look at the following example
    /*!
    \code{.cpp}
    nxpath path = nxpath::from_string("file.nx:///entry:NXentry/instrument:NXinstrument/data");
    nxpath p1,p2;
    split_path(path,1,p1,p2);

    std::cout<<p1<<std::endl;
    std::cout<<p2<<std::endl;

    // output
    // file.nx:///entry:NXentry
    // instrument:NXinstrument/data

    \endcode
    */
    //! \throws pni::core::index_error if s exceeds input path size
    //! \param p original path
    //! \param s index where to split 
    //! \param p1 first part of the path
    //! \param p2 second part of the path
    //!
    void split_path(const nxpath &p,size_t s,nxpath &p1,nxpath &p2);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
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
    //! \ingroup nxpath_code
    //! \brief convert path to string 
    //!
    //! Convert a Nexus path to a string. 
    //! \param p reference to nexus path
    //! \return string representation of p
    //!
    string string_from_path(const nxpath &p);
    
    //------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
    //! \brief check if element is root
    //!
    //! The root element has the form ("/","NXroot"). This function returns
    //! true if the passed element is the root element.
    //! 
    //! \param e element instance
    //! \return true if root element, false otherwise
    //!
    bool is_root_element(const nxpath::element_type &e);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
    //!
    //! \param p path instance
    //! \return true if path is absolute, false otherwise
    //!
    bool is_absolute(const nxpath &p);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
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
    //! \ingroup nxpath_code
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
    //! \ingroup nxpath_code
    //! \brief check element completness
    //! 
    //! A path element is considered as complete if both, name and class field 
    //! are not empty. It follows from this that an element refering to a 
    //! field must never be complete as it has no attribute NX_class. Thus, 
    //! this function can be used as a first check if a path element referes 
    //! to a field or to a group. 
    //! 
    //! \param e reference to the path element
    //! \return true if element is complete, false otherwise
    //!
    bool is_complete(const nxpath::element_type &e);


    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
    //! \brief input operator for a nexus path
    //! 
    //! Constructing a nexus path from a stream. Analogously to the output 
    //! operator this is used to read a path from a stream-able source.
    /*!
    \code{.cpp}
    nxpath p;
    std::cin>>p;
    \endcode
    */
    //! \param i reference to the input stream
    //! \param p reference to the path
    //! \return reference to the advanced original stream
    //!
    std::istream &operator>>(std::istream &i,nxpath &p);

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
    //! \brief equality operator for two path objects
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
    //! \ingroup nxpath_code
    //! \brief inequality operator for two path objects
    //!
    //! Compars two path objects and returns true if they are not equal. 
    //! \param lhs reference to the path on the left handside
    //! \param rhs reference to the path on the right handside
    //! \return true if not equal, false otherwise
    //!
    bool operator!=(const nxpath &lhs,const nxpath &rhs);
    
    //------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
    //! \brief output operator for single elements
    //!
    //! Write a single object element to an output stream. 
    //!
    //! \param stream output stream reference
    //! \param e object element
    //! \return reference to the modified stream
    //!
    std::ostream &operator<<(std::ostream &stream,
                             const nxpath::element_type &e);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
    //! \brief output operator for object path
    //!
    //! Write an entire object path to an output stream
    //!
    //! \param stream output stream reference
    //! \param e object path 
    //! \return reference to the modified stream
    //!
    std::ostream &operator<<(std::ostream &stream,
                             const nxpath::elements_type &e);


    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
    //! \brief output operator for a nexus path
    //! 
    //! Prints a nexus path to an output stream. One can either use this to 
    //! write a Nexus path to standard out 
    /*!
    \code{.cpp}
    nxpath p = ....;
    std::cout<<p<<std::endl;
    \endcode
    */
    //! or to a string using the stringstream operator
    /*!
    \code{.cpp}
    std::stringstream ss;
    ss<<p;
    \endcode
    */
    //!
    //! \param o reference to the output stream
    //! \param p reference to the path
    //! \return reference to the output operator
    //!
    std::ostream &operator<<(std::ostream &stream,const nxpath &p);

//end of namespace
}
}
}
