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
            //! declar path as absolute
            bool _is_absolute;
        public:
            //===============constructors and destructor=======================
            //! default constructor
            nxpath();
            //-----------------------------------------------------------------
            //! constructor
            nxpath(const string &file,const elements_type &groups,
                   const string &attr,bool absolute=false);
           
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
            void push_back(const element_type &o)
            {
                _elements.push_back(o);
            }

            //----------------------------------------------------------------
            void push_front(const element_type &o)
            {
                _elements.push_front(o);
            }

            //----------------------------------------------------------------
            void pop_front()
            {
                _elements.pop_front();
            }

            //----------------------------------------------------------------
            void pop_back()
            {
                _elements.pop_back();
            }

            //-----------------------------------------------------------------
            element_type front() const
            {
                return _elements.front();
            }

            //----------------------------------------------------------------
            element_type back() const 
            {
                return _elements.back();
            }


            //------------------------------------------------------------------
            //! return number of group entries
            size_t size() const { return _elements.size(); }

            //------------------------------------------------------------------
            //! return true if path is absolute
            bool is_absolute() const {return _is_absolute; }

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



    //-------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
    //! \brief check if path is fs path
    //!
    //! This function checks if a string represents a path to a file on the
    //! filesystem. For this check it assumes that the last element of the 
    //! path is the name of the file which has the form
    /*!
    \code
    [basename].[extension]
    \endcode
    */
    //! This function is necessary for splitting the string representation of a
    //! nexus path. In cases where only the filename or the object path is 
    //! given we need a way to distinguish between these two types of paths. 
    //!
    //! \param s the path as string
    //! \return true of s represents a file path
    //!
    bool is_file_path(const string &s);


    //-------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
    //! \brief split nexus path
    //!
    //! This is a service function used by path_from_string. It takes the 
    //! complete Nexus path as a string and splits it into three pieces at the 
    //! and the @ token
    //!
    //! \li the filename
    //! \li the object path
    //! \li the attribute name
    //!
    //! This function was implemented in order to keep the parsers for the 
    //! different components of the path as easy as possible. In other words 
    //! this is something like a very simple lexxer. 
    //!
    //! \param input the full Nexus path
    //! \param file the filename 
    //! \param groups the group portion of the path
    //! \param attribute the attribute name
    //!
    void split_path(const string &input, string &file,string &groups,
                    string &attribute);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
    //! \brief creates a path from a string
    //!
    //! This function takes a full Nexus path as its input argument, parses 
    //! it and constructs a nxpath instance out of it.
    //!
    //! \param p full Nexus path as string
    //! \return instance of nxpath
    //!
    nxpath path_from_string(const string &p);


//end of namespace
}
}
}
