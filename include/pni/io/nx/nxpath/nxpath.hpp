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
// Created on: Feb 11, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <utility>
#include <pni/core/types.hpp>
#include <list>

namespace pni{
namespace io{
namespace nx{
        
    //!
    //! \ingroup nxpath_code
    //! \brief Nexus path class
    //!
    //! This class represents a full Nexus path. Such a path describes the 
    //! position of an object within a Nexus file. In general the path has 
    //! a form like this
    /*!
    \code
    filename://entry:NXentry/instrument:NXinstrument/detector/data@attrname
    \endcode
    */
    //! More specific this can be written as
    /*!
    \code
    [filename://]path
    \endcode
    */
    //! Usage
    /*!
    \code
    string path_str = .....;
    nxpath path = nxpath::from_string(path_str);
    \endcode
    */
    //! A path can either be absolute or relative to a particular 
    //! object. However, a path with a filename part is always absolute (for
    //! obvious reasons).
    //!
    class nxpath
    {
        public: 
            //! object element (groupname:class)
            typedef std::pair<pni::core::string,pni::core::string> element_type;
            //! a list of subsequent objects
            typedef std::list<element_type> elements_type;
            //! iterator over elements
            typedef elements_type::iterator iterator;
            //! const iterator over elements
            typedef elements_type::const_iterator const_iterator;

        private:
            //! name of the file
            pni::core::string _file_name;
            //! name of an attribute
            pni::core::string _attribute_name;
            //! list of groups
            elements_type _elements;

        public:
            //===============constructors and destructor=======================
            //!
            //! \brief default constructor
            //! 
            nxpath();
            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! \param file name of the file
            //! \param groups a list of elements for the object path
            //! \param attr the optional name of an attribute
            //!
            explicit nxpath(const pni::core::string &file,
                            const elements_type &groups,
                            const pni::core::string &attr);
           
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
            static nxpath from_string(const pni::core::string &input);

            //-----------------------------------------------------------------
            //!
            //! \brief create string from path
            //!
            //! Returns the string representation of a path.
            //!
            //! \param p reference to path instance
            //! \return string representation of the path
            //!
            static pni::core::string to_string(const nxpath &p);
           
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
            pni::core::string filename() const noexcept;

            //----------------------------------------------------------------
            //!
            //! \brief set the filename
            //!
            void filename(const pni::core::string &f);

            //-----------------------------------------------------------------
            //!
            //! \brief return the attribute name
            //!
            pni::core::string attribute() const noexcept;

            //----------------------------------------------------------------
            //!
            //! \brief set the attribute name
            //!
            void attribute(const pni::core::string &a);

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
            void push_back(const element_type &o);

            //----------------------------------------------------------------
            //! 
            //! \brief prepend element
            //! 
            //! Append an element to the beginning of the Nexus path.
            //! 
            //! \param o element to append
            //! 
            void push_front(const element_type &o);

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
            element_type front() const 
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
            element_type back() const;

            //------------------------------------------------------------------
            //!
            //! \brief return number of group entries
            //!
            size_t size() const;

            //===================iterators======================================
            //!
            //! \brief get iterator to first element
            //!
            iterator begin();

            //----------------------------------------------------------------
            //!
            //! \brief get iterator to last+1 element
            iterator end();

            //----------------------------------------------------------------
            //!
            //! \brief get const iterator to first element
            //!
            const_iterator begin() const;

            //----------------------------------------------------------------
            //! 
            //! \brief get const iterator to last+1 element
            //!
            const_iterator end() const;
    };


//end of namespace
}
}
}
