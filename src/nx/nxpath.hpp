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



            //===================iterators======================================
            //! get iterator to first element
            iterator begin() { return _groups.begin(); }

            //! get iterator to last+1 element
            iterator end()   { return _groups.end();   }

            //! get const iterator to first element
            const_iterator begin() const { return _groups.begin(); }

            //! get const iterator to last+1 element
            const_iterator end() const   { return _groups.end();   }
    };

    /*!
    \brief parser for group elements

    */
    template<typename ITERT>
    struct element_parser :
    boost::spirit::qi::grammar<ITERT,
                               boost::spirit::locals<string,string>, 
                               nxpath::group_element_t()>
    {
        boost::spirit::qi::rule<ITERT,string()> component_rule;
        boost::spirit::qi::rule<ITERT,
                                boost::spirit::locals<string,string>, 
                                nxpath::group_element_t()> group_element_rule;

        element_parser() : element_parser::base_type(group_element_rule)
        {
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;

            component_rule = +char_("-_a-zA-z0-9.");
            group_element_rule =  eps[_a="",_b=""]>>(
                                  (component_rule[_a=_1]>>-(':'>component_rule[_b=_1]))                              |
                                  (':'>component_rule)[_b = _1]
                    )[_val = construct<nxpath::group_element_t>(_a,_b)];

        }


    };


    /*!
    \brief parser for group path

    */
    template<typename ITERT>
    struct nxpath_parser :
        boost::spirit::qi::grammar<ITERT,nxpath::group_path_t()>
    {
        boost::spirit::qi::rule<ITERT,nxpath::group_path_t()> path_rule;
        element_parser<ITERT> element_; 

        nxpath_parser() : nxpath_parser::base_type(path_rule)
        {
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;

            path_rule = ('/'>>element_ % '/') | ( element_ % '/');

        }


    };


    void split_path(const string &input, string &file,string &groups,string
            &attribute);
    nxpath path_from_string(const string &p);
//end of namespace
}
}
}
