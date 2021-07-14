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
// Created on: Feb 11, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <utility>
#include <pni/types.hpp>
#include <list>
#include <pni/windows.hpp>
#include <boost/filesystem.hpp>
#include <h5cpp/hdf5.hpp>

namespace pni{
namespace io{
namespace nexus{
        
//!
//! \ingroup nxpath_code
//! \brief Nexus path class
//!
//! This class represents a full Nexus path. Such a path describes the
//! position of an object within a Nexus file. In general the path has
//! a form like this
//!
//! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//! filename://entry:NXentry/instrument:NXinstrument/detector/data@attrname
//! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!
//! More specific this can be written as
//! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//! [filename://]path
//! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!
//! Usage
//! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//! string path_str = .....;
//! nxpath path = nxpath::from_string(path_str);
//! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!
//! A path can either be absolute or relative to a particular
//! object. However, a path with a filename part is always absolute (for
//! obvious reasons).
//!
class PNINEXUS_EXPORT Path
{
  public:
    //! object element (groupname:class)
    using Element = std::pair<pni::string,pni::string>;
    //! a list of subsequent objects
    using ElementList =  std::list<Element>;
    //! iterator over elements
    using ElementIterator =  ElementList::iterator;
    //! const iterator over elements
    using ConstElementIterator =  ElementList::const_iterator;

  private:
#ifdef _MSC_VER
#pragma warning(disable: 4251)
#endif
    //! name of the file
    pni::string _file_name;
    //! name of an attribute
    pni::string _attribute_name;
    //! list of groups
    ElementList _elements;
#ifdef _MSC_VER
#pragma warning(default: 4251)
#endif

  public:
    //===============constructors and destructor=======================
    //!
    //! \brief default constructor
    //!
    Path();
    //-----------------------------------------------------------------
    //!
    //! \brief constructor
    //!
    //! \param file name of the file
    //! \param groups a list of elements for the object path
    //! \param attr the optional name of an attribute
    //!
    Path(const boost::filesystem::path &file,
         const ElementList &groups,
         const pni::string &attr);

    //!
    //! @brief constructor
    //!
    //! Construct a NeXus path from an HDF5 path. This constructor is
    //! deliberately non-explicit. As an HDF5 path does not contain
    //! any file or attribute information only the element section
    //! of the path will be set.
    //!
    //! @param path reference to the original HDF5 path
    //!
    Path(const hdf5::Path &path);

    //-----------------------------------------------------------------
    //!
    //! \brief create path from string
    //!
    //! This method creates a path from a string passed to it.
    //!
    //! \throws parser_error in case of parsing problems
    //!
    //! \param input string with path representation
    //!
    //! \return path instance
    //!
    static Path from_string(const std::string &input);

    //-----------------------------------------------------------------
    //!
    //! \brief create string from path
    //!
    //! Returns the string representation of a path.
    //!
    //! \param p reference to path instance
    //! \return string representation of the path
    //!
    static std::string to_string(const Path &p);

    //!
    //! @brief conversion to an HDF5 path
    //!
    //! This conversion is only possible if the NeXus path is unique.
    //! Otherwise an exception will be thrown.
    //!
    //! As an HDF5 path does not contain any information about the file
    //! or an attribute this conversion basically copies the names
    //! of all object links to the HDF5 path.
    //!
    //! @throws std::runtime_error in case of a failure
    //! @return new instance of hdf5::Path
    //!
    operator hdf5::Path();

    //===============public member methods=============================
    //!
    //! \brief true if has filename
    //!
    //! Returns true if the path contains a file name.
    //! \return true if filename exists
    //!
    bool has_filename() const noexcept;

    //-----------------------------------------------------------------
    //!
    //! \brief true if has attribute
    //!
    //! Returns true if the path contains an attribute name.
    //! \return true if path has attribute
    //!
    bool has_attribute() const noexcept;

    //-----------------------------------------------------------------
    //!
    //! \brief return the filename
    //!
    boost::filesystem::path filename() const noexcept;

    //----------------------------------------------------------------
    //!
    //! \brief set the filename
    //!
    void filename(const boost::filesystem::path &file);

    //-----------------------------------------------------------------
    //!
    //! \brief return the attribute name
    //!
    std::string attribute() const noexcept;

    //----------------------------------------------------------------
    //!
    //! \brief set the attribute name
    //!
    void attribute(const std::string &attribute_name);

    //-----------------------------------------------------------------
    //!
    //! \brief append element
    //!
    //! Append a new element to the end of the Nexus path.
    //!
    //! \throws value_error if one tries to push_back a root group
    //! to a non-empty path
    //!
    //! \param o element to append
    //!
    void push_back(const Element &o);

    //----------------------------------------------------------------
    //!
    //! \brief prepend element
    //!
    //! Append an element to the beginning of the Nexus path.
    //!
    //! \param o element to append
    //!
    void push_front(const Element &o);

    //----------------------------------------------------------------
    //!
    //! \brief last element from path
    //!
    void pop_front();

    //----------------------------------------------------------------
    //!
    //! \brief remove first element from path
    //!
    void pop_back();

    //-----------------------------------------------------------------
    //!
    //! \brief get last element
    //!
    //! Return the last element of the Nexus path.
    //!
    //! \return last element
    Element front() const
    {
      return _elements.front();
    }

    //----------------------------------------------------------------
    //!
    //! \brief get first element
    //!
    //! Return the first element of the Nexus path
    //!
    //! \return first element
    //!
    Element back() const;

    //------------------------------------------------------------------
    //!
    //! \brief return number of group entries
    //!
    size_t size() const;

    //===================iterators======================================
    //!
    //! \brief get iterator to first element
    //!
    ElementIterator begin();

    //----------------------------------------------------------------
    //!
    //! \brief get iterator to last+1 element
    ElementIterator end();

    //----------------------------------------------------------------
    //!
    //! \brief get const iterator to first element
    //!
    ConstElementIterator begin() const;

    //----------------------------------------------------------------
    //!
    //! \brief get const iterator to last+1 element
    //!
    ConstElementIterator end() const;
};


//end of namespace
} // namespace nexus
} // namespace io
} // namespace pni
