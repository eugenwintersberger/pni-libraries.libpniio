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

#include <vector>
#include <utility>
#include <pni/core/types.hpp>
#include <list>

namespace pni{
namespace io{
namespace nx{

    using namespace pni::core;
    //!
    //! \ingroup nxpath_code
    //! \brief Nexus path class
    //!
    //! This class represents a full Nexus path. Such a path describes the 
    //! position of an object within a Nexus file. In general the path has 
    //! a form like this
    /*!
    \code
    filename:///entry:NXentry/instrument:NXinstrument/detector/data@attrname
    \endcode
    */
    //! More specific this can be written as
    /*!
    \code
    [filename://][/]path
    \endcode
    */
    //! Usage
    /*!
    \code
    string path_str = .....;
    nxpath path = nxpath::from_string(path_str);
    \endcode
    */
    //!
    class nxpath
    {
        public: 
            //! object element (groupname:class)
            typedef std::pair<string,string> element_type;
            //! a list of subsequent objects
            typedef std::list<element_type> elements_type;
            //! iterator over elements
            typedef elements_type::iterator iterator;
            //! const iterator over elements
            typedef elements_type::const_iterator const_iterator;

        private:
            //! name of the file
            string _file_name;
            //! name of an attribute
            string _attribute_name;
            //! list of groups
            elements_type _elements;

        public:
            //===============constructors and destructor=======================
            //! default constructor
            nxpath();
            //-----------------------------------------------------------------
            //! constructor
            nxpath(const string &file,const elements_type &groups,
                   const string &attr);
            
            static nxpath from_string(const string &input);

            static string to_string(const nxpath &p);
           
            //===============public member methods=============================
            //!
            //! \brief true if has filename
            //!
            //! Returns true if the path contains a file name. 
            //! \return true if filename exists
            //!
            bool has_filename() const  { return !_file_name.empty(); }

            //-----------------------------------------------------------------
            //!
            //! \brief true if has attribute
            //!
            //! Returns true if the path contains an attribute name.
            //! \return true if path has attribute
            //!
            bool has_attribute() const { return !_attribute_name.empty(); }

            //-----------------------------------------------------------------
            //! return the filename
            string filename() const { return _file_name; }

            //-----------------------------------------------------------------
            //! return the attribute name
            string attribute() const { return _attribute_name; }


            //-----------------------------------------------------------------
            //!
            //! \brief append element
            //! 
            //! Append a new element to the end of the Nexus path. 
            //!
            //! \param o element to append
            //! 
            void push_back(const element_type &o) { _elements.push_back(o); }

            //----------------------------------------------------------------
            //! 
            //! \brief prepend element
            //! 
            //! Append an element to the beginning of the Nexus path.
            //! 
            //! \param o element to append
            //! 
            void push_front(const element_type &o) { _elements.push_front(o); }

            //----------------------------------------------------------------
            //! 
            //! \brief last element from path
            //! 
            void pop_front() { _elements.pop_front(); }

            //----------------------------------------------------------------
            //! 
            //! \brief remove first element from path
            //!
            void pop_back() { _elements.pop_back(); }

            //-----------------------------------------------------------------
            //!
            //! \brief get last element
            //! 
            //! Return the last element of the Nexus path. 
            //! 
            //! \return last element
            element_type front() const { return _elements.front(); }

            //----------------------------------------------------------------
            //!
            //! \brief get first element
            //!
            //! Return the first element of the Nexus path
            //! 
            //! \return first element
            //!
            element_type back() const { return _elements.back(); }


            //------------------------------------------------------------------
            //! return number of group entries
            size_t size() const { return _elements.size(); }

            //------------------------------------------------------------------
            //! return true if path is absolute
            bool is_absolute() const;

            //===================iterators======================================
            //! get iterator to first element
            iterator begin() { return _elements.begin(); }

            //----------------------------------------------------------------
            //! get iterator to last+1 element
            iterator end()   { return _elements.end();   }

            //----------------------------------------------------------------
            //! get const iterator to first element
            const_iterator begin() const { return _elements.begin(); }

            //----------------------------------------------------------------
            //! get const iterator to last+1 element
            const_iterator end() const   { return _elements.end();   }
    };

    std::ostream &operator<<(std::ostream &stream,
                             const nxpath::element_type &e);

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
