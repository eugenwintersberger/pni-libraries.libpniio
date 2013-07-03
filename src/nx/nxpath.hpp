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

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/variant.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/optional/optional.hpp>


namespace pni{
namespace io{
namespace nx{

    using namespace pni::core;
    /*!
    \ingroup nxpath_code
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
            //! object element (groupname:class)
            typedef std::pair<string,string> object_element_t;
            //! a list of subsequent objects
            typedef std::list<object_element_t> object_path_t;
            //! iterator over elements
            typedef object_path_t::iterator iterator;
            //! const iterator over elements
            typedef object_path_t::const_iterator const_iterator;

        private:
            //! name of the file
            string _file_name;
            //! name of an attribute
            string _attribute_name;
            //! list of groups
            object_path_t _objects;
            //! declar path as absolute
            bool _is_absolute;
        public:
            //===============constructors and destructor=======================
            //! default constructor
            nxpath();
            //-----------------------------------------------------------------
            //! constructor
            nxpath(const string &file,const object_path_t &groups,
                   const string &attr,bool absolute=false);
           
            //===============public member methods=============================
            /*!
            \brief true if has filename

            Returns true if the path contains a file name. 
            \return true if filename exists
            */
            bool has_filename() const  { return !_file_name.empty(); }

            //-----------------------------------------------------------------
            /*!
            \brief true if has attribute

            Returns true if the path contains an attribute name.
            \return true if path has attribute
            */
            bool has_attribute() const { return !_attribute_name.empty(); }

            //-----------------------------------------------------------------
            //! return the filename
            string filename() const { return _file_name; }

            //-----------------------------------------------------------------
            //! return the attribute name
            string attribute() const { return _attribute_name; }

            //-----------------------------------------------------------------
            /*! 
            \brief append group element 

            Append a group element to the end of the groups list. 
            \param gname name of the group
            \param gclass class of the group
            */
            void append(const string &gname,const string &gclass);

            //-----------------------------------------------------------------
            /*! 
            \brief add group element 

            Prepend a group element to the beginning of the list.
            \param gname name of the group
            \param gclass class of the group
            */
            void prepend(const string &gname,const string &gclass);

            //------------------------------------------------------------------
            //! return number of group entries
            size_t size() const { return _objects.size(); }

            //------------------------------------------------------------------
            //! return true if path is absolute
            bool is_absolute() const {return _is_absolute; }

            //===================iterators======================================
            //! get iterator to first element
            iterator begin() { return _objects.begin(); }

            //! get iterator to last+1 element
            iterator end()   { return _objects.end();   }

            //! get const iterator to first element
            const_iterator begin() const { return _objects.begin(); }

            //! get const iterator to last+1 element
            const_iterator end() const   { return _objects.end();   }
    };

    //--------------------------------------------------------------------------
    /*!
    \ingroup nxpath_code
    \brief parser for group elements

    This parser handles a single group element of the group portion of a Nexus
    path. A group element has the syntax
    \code
    <groupname>:<groupclass>
    \endcode

    \tparam ITERT iterator type for the parser
    */
    template<typename ITERT>
    struct element_parser :
    boost::spirit::qi::grammar<ITERT,
                               boost::spirit::locals<string,string>, 
                               nxpath::object_element_t()>
    {
        //! rule for a single component
        boost::spirit::qi::rule<ITERT,string()> component_rule;

        //! rule for a group element
        boost::spirit::qi::rule<ITERT,
                                boost::spirit::locals<string,string>, 
                                nxpath::object_element_t()> object_element_rule;

        //! default constructor
        element_parser() : element_parser::base_type(object_element_rule)
        {
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;

            component_rule = +char_("-_a-zA-z0-9.");
            object_element_rule =  eps[_a="",_b=""]>>(
                                  (component_rule[_a=_1]>>-(':'>component_rule[_b=_1]))                              |
                                  (':'>component_rule)[_b = _1]
                    )[_val = construct<nxpath::object_element_t>(_a,_b)];

        }


    };


    //-------------------------------------------------------------------------
    /*!
    \ingroup nxpath_code
    \brief parser for group path

    Parser for the group portion of a Nexus path. The group portion has the
    structure
    \code
    <name>:<class>/<name>:<class>/....
    \endcode
    
    \tparam ITERT iterator type for the parser
    */
    template<typename ITERT>
    struct nxpath_parser :
        boost::spirit::qi::grammar<ITERT,nxpath::object_path_t()>
    {
        //! rule for the entire group portion
        boost::spirit::qi::rule<ITERT,nxpath::object_path_t()> path_rule;
        //! group element parser
        element_parser<ITERT> element_; 

        //! default constructor
        nxpath_parser() : nxpath_parser::base_type(path_rule)
        {
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;

            path_rule = ('/'>>element_ % '/') | ( element_ % '/');

        }


    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup nxpath_code
    \brief check if path is fs path

    This function checks if a string represents a path to a file on the
    filesystem. For this check it assumes that the last element of the path is
    the name of the file which has the form
    \code
    [basename].[extension]
    \endcode
    This function is necessary for splitting the string representation of a
    nexus path. In cases where only the filename or the object path is given we
    need a way to distinguish between these two types of paths. 

    \param s the path as string
    \return true of s represents a file path
    */
    bool is_file_path(const string &s);


    //-------------------------------------------------------------------------
    /*!
    \ingroup nxpath_code
    \brief split nexus path

    This is a service function used by path_from_string. It takes the complete
    Nexus path as a string and splits it into three pieces at the :// and the @
    token

    \li the filename
    \li the object path
    \li the attribute name

    This function was implemented in order to keep the parsers for the different
    components of the path as easy as possible. In other words this is something
    like a very simple lexxer. 

    \param input the full Nexus path
    \param file the filename 
    \param groups the group portion of the path
    \param attribute the attribute name
    */
    void split_path(const string &input, string &file,string &groups,string
            &attribute);

    //-------------------------------------------------------------------------
    /*!
    \ingroup nxpath_code
    \brief creates a path from a string

    This function takes a full Nexus path as its input argument, parses it and
    constructs a nxpath instance out of it.

    \param p full Nexus path as string
    \return instance of nxpath
    */
    nxpath path_from_string(const string &p);


//end of namespace
}
}
}
