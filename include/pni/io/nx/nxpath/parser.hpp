//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jun 10, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include "nxpath.hpp"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <utility>


namespace pni{
namespace io{
namespace nx{

//add here an additional namespace to avoid namespace polution from the boost
//spirit framework.
namespace parsers{

    using namespace boost::spirit;
    using namespace boost::phoenix;

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
    //! \brief nexus identifier parser
    //!
    //! This code parsers a single Nexus identifier which would be a fieldname
    //! a group name or an attribute name. 
    //!
    template<typename ITERT>
    struct id_parser : qi::grammar<ITERT,string()>
    {
        qi::rule<ITERT,string()> id_rule;

        id_parser() : id_parser::base_type(id_rule)
        {
            id_rule = +qi::char_("-_a-zA-Z0-9");
        }
    };
    
    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
    //! \brief parser for group elements
    //! 
    //! This parser handles a single group element of the group portion of 
    //! a Nexus path. A group element has the syntax
    /*!
    \code
    <groupname>:<groupclass>
    \endcode
    */
    //!
    //! \tparam ITERT iterator type for the parser
    //!
    template<typename ITERT> 
    struct element_parser : qi::grammar<
                                        ITERT,
                                        locals<string,string>,
                                        nxpath::element_type()
                                       >
    {
        typedef nxpath::element_type element_type;

        //! rule for a single component
        qi::rule<ITERT,string()> name_rule;
        qi::rule<ITERT,string()> class_rule;
        qi::rule<ITERT,string()> dot_rule;

        id_parser<ITERT> id_;
        
        //! rule for a group element
        qi::rule< ITERT,locals<string,string>,nxpath::element_type()> element_rule;

        //! default constructor
        element_parser() : element_parser::base_type(element_rule)
        {
            using qi::_1;
    

            //a name is basically nothing else than a simple Nexus identifier
            name_rule =   id_[_val = _1];
            //a classname must alwasy start with a :
            class_rule =   lit(":") > id_[_val = _1];

            dot_rule = (lit(".")>!id_)[_val="."] 
                       || 
                       (lit(".")>!(id_ | lit(".")))[_val+="."];

            element_rule =  (
                              dot_rule[_a = _1,_b = ""]
                            |
                              (class_rule[_b = _1] )
                            | 
                              (name_rule[_a = _1] || class_rule[_b = _1])
                            )[_val = construct<element_type>(_a,_b)];
        }

    };
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
    //! \brief parser for group path
    //!
    //! Parser for the group portion of a Nexus path. The group portion has 
    //! the structure
    /*!
    \code
    /<name>:<class>/<name>:<class>/....
    \endcode
    */
    //! \tparam ITERT iterator type for the parser
    //!
    template<typename ITERT>
    struct elements_parser : qi::grammar<ITERT,nxpath::elements_type()>
    {
        //! rule for the entire group portion
        qi::rule<ITERT,nxpath::elements_type()> elements_rule;
        //! group element parser
        element_parser<ITERT> element_; 

        //! default constructor
        elements_parser() : elements_parser::base_type(elements_rule)
        {
            //[push_back(_val,construct<nxpath::element_type>("/","NXroot"))] 
            elements_rule = (element_ % '/') >-lit("/");
        }
    };



    //------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
    //! \brief parser for a nexus path
    //! 
    //! \tparam ITERT iterator type
    //!
    template<typename ITERT>
    struct nxpath_parser : qi::grammar<ITERT,
                                       locals
                                       <
                                           nxpath::elements_type,
                                           string
                                       >,
                                       nxpath()>
    {
        qi::rule<ITERT,
                 locals
                 <
                     nxpath::elements_type,
                     string
                 >,
                 nxpath()> nxpath_rule;

        qi::rule<ITERT,nxpath::element_type()> root_rule;
                
        //add parser for the filepath
        id_parser<ITERT> id_;

        //add parser for the elements
        elements_parser<ITERT> element_rule;

        nxpath_parser(const string &fname="") :
            nxpath_parser::base_type(nxpath_rule),
            _filename(fname)
        {
            using boost::spirit::qi::_1;
            using boost::phoenix::merge;
            using boost::phoenix::ref;

            root_rule = lit("/")[_val = construct<nxpath::element_type>("/","NXroot")];
            root_rule.name("root_rule");
           
            nxpath_rule = eps[_a = construct<nxpath::elements_type>(),_b="",
                              _val = construct<nxpath>(boost::phoenix::ref(_filename),_a,_b),
                              push_back(_val,construct<nxpath::element_type>("/","NXroot")) 
                              ]
                          >>
                          (   root_rule[push_back(_a,_1)]
                           || 
                              element_rule[insert(_a,end(_a),begin(_1),end(_1))]
                           || 
                              (lit("@")>id_[_b=_1])
                           ) [_val = construct<nxpath>(boost::phoenix::ref(_filename),_a,_b)] 
                          >eoi; //finally EOI is the terminal for the string
        }

        private:
            string _filename;
    };

    //------------------------------------------------------------------------
    nxpath parse_path(const string &input);

//end of parser namespace
}
                                    
//end of namespace
}
}
}
