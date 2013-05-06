/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: Feb 11, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <vector>
#include <utility>
#include <pni/core/types.hpp>
#include <list>


namespace pni{
namespace io{
namespace nx{

    using namespace pni::core;
    /*!
    \brief Nexus path class

    This class represents a full Nexus path. Such a path describes the position
    of an object within a Nexus file. In general the path has a form like this
    \code
    filename:///entry:NXentry/instrument:NXinstrument/detector/data@attrname
    \endcode
    More specific this can be written as
    \code
    [filename://][/]path
    \endcode
    Usage
    \code
    string path_str = .....;
    nxpath path = nxpath::from_string(path_str);
    \endcode
    */
    class nxpath
    {
        public: 
            //! group element (groupname:class)
            typedef std::pair<string,string> group_element_t;
            //! a list of subsequent groups 
            typedef std::list<group_element_t> group_path_t;
            //! iterator over elements
            typedef group_path_t::iterator iterator;
            //! const iterator over elements
            typedef group_path_t::const_iterator const_iterator;

        private:
            //! name of the file
            string _file_name;
            //! name of an attribute
            string _attribute_name;
            //! list of groups
            group_path_t _groups;
        public:
            //===============constructors and destructor=======================
            //! default constructor
            nxpath();
            //-----------------------------------------------------------------
            //! constructor
            nxpath(const string &file,const group_path_t &groups,
                   const string &attr);
           
            //===============public member methods=============================
            bool has_filename() const  { return !_file_name.empty(); }
            bool has_attribute() const { return !_attribute_name.empty(); }



            


            //===================iterators======================================
            iterator begin() { return _groups.begin(); }
            iterator end()   { return _groups.end();   }
            const_iterator begin() const { return _groups.begin(); }
            const_iterator end() const   { return _groups.end();   }
    };

//end of namespace
}
}
}
