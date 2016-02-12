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
#include "insert.hpp"

#ifdef _MSC_VER
#pragma warning(disable:4348)
#endif
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/include/std_pair.hpp>
#ifdef _MSC_VER
#pragma warning(default:4348)
#endif
#include <utility>


namespace pni{
namespace io{
namespace nx{

//add here an additional namespace to avoid namespace polution from the boost
//spirit framework.
namespace parsers{


    //------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_internal_code
    //! \brief nexus identifier parser
    //!
    //! This code parsers a single Nexus identifier which would be a fieldname
    //! a group name or an attribute name. 
    //!
    template<typename ITERT>
    struct id_parser : boost::spirit::qi::grammar<ITERT,pni::core::string()>
    {
        //! the major rule to parse an ID
        boost::spirit::qi::rule<ITERT,pni::core::string()> id_rule;

        //! 
        //! \brief default constructor
        //!
        id_parser() : id_parser::base_type(id_rule)
        {
            using namespace boost::spirit;
            using namespace boost::phoenix;
            id_rule = +qi::char_("-_a-zA-Z0-9");
        }
    };
    
    //-------------------------------------------------------------------------
    //! 
    //! \ingroup nxpath_internal_code
    //! \brief parser dots
    //! 
    //! Parser for one or two dots. 
    //! 
    template<typename ITERT>
    struct dot_parser : boost::spirit::qi::grammar<ITERT,pni::core::string()>
    {
        boost::spirit::qi::rule<ITERT,pni::core::string()> dot_rule;
        
        dot_parser() : dot_parser::base_type(dot_rule)
        {
            using namespace boost::spirit;
            using namespace boost::phoenix;
            using qi::_1;
            dot_rule = lit(".")[_val = "."]||lit(".")[_val += "."];
        }
    };
    
    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_internal_code
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
    struct element_parser : boost::spirit::qi::grammar<
                                        ITERT,
                                        boost::spirit::locals<
                                               pni::core::string,
                                               pni::core::string
                                              >,
                                        nxpath::element_type()
                                       >
    {
        //! a single path element type
        typedef nxpath::element_type element_type;
        //! string rule type
        typedef boost::spirit::qi::rule<ITERT,pni::core::string()> 
            string_rule_type;
        //! type for parser locals
        typedef boost::spirit::locals<pni::core::string,pni::core::string> 
            locals_type;
        
        string_rule_type name_rule;   //!< rule for a single name        
        string_rule_type class_rule;  //!< rule for a class
            
        id_parser<ITERT>  id_;    //!< rule for a path ID
        dot_parser<ITERT> dots_;  //!< rule to parse dots
        
        //! rule for a full group element
        boost::spirit::qi::rule< ITERT,locals_type,nxpath::element_type()> 
            element_rule;

        //! default constructor
        element_parser() : element_parser::base_type(element_rule)
        {
            using namespace boost::spirit;
            using namespace boost::phoenix;
            using qi::_1;
    
            //a name is basically nothing else than a simple Nexus identifier
            name_rule =   id_[_val = _1] | dots_[_val=_1];
            //a classname must alwasy start with a :
            class_rule =   lit(":") > id_[_val = _1];           

            element_rule =  eps[_a = "", _b=""]>>(
                              name_rule[_a = _1] || class_rule[_b = _1]
                            )[_val = construct<element_type>(_a,_b)];
        }

    };
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_internal_code
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
    struct elements_parser : boost::spirit::qi::grammar<ITERT,nxpath::elements_type()>
    {
        //! rule for the entire group portion
        boost::spirit::qi::rule<ITERT,nxpath::elements_type()> elements_rule;
        //! group element parser
        element_parser<ITERT> element_; 

        //! default constructor
        elements_parser() : elements_parser::base_type(elements_rule)
        {
            using namespace boost::spirit;
            using namespace boost::phoenix;
            //[push_back(_val,construct<nxpath::element_type>("/","NXroot"))] 
            elements_rule = (element_ % '/') >-lit("/");
        }
    };



    //------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_internal_code
    //! \brief parser for a nexus path
    //!
    //! The parser has to local elements:
    //! \li the elements list
    //! \li a string for an optional attribute
    //! 
    //! \tparam ITERT iterator type
    //!
    template<typename ITERT>
    struct nxpath_parser : boost::spirit::qi::grammar<ITERT,
                                       boost::spirit::locals
                                       <
                                           nxpath::elements_type,
                                           pni::core::string
                                       >,
                                       nxpath()>
    {
        //! rule for the path
        boost::spirit::qi::rule<ITERT,
                 boost::spirit::locals
                 <
                     nxpath::elements_type,
                     pni::core::string
                 >,
                 nxpath()> nxpath_rule;

        //! rule for the root part of the path
        boost::spirit::qi::rule<ITERT,nxpath::element_type()> root_rule;
                
        //!parser for an individual Nexus ID
        id_parser<ITERT> id_;

        //! parser for a single element
        elements_parser<ITERT> element_rule;

        //--------------------------------------------------------------------
        //!
        //! \brief constructor
        //!
        //! \param fname the filename of the path
        //!
        nxpath_parser(const pni::core::string &fname="") :
            nxpath_parser::base_type(nxpath_rule),
            _filename(fname)
        {
            using namespace boost::spirit;
            using namespace boost::phoenix;
            using boost::spirit::qi::_1;
           // using boost::phoenix::merge;
            using boost::phoenix::ref;

            root_rule = lit("/")[_val = construct<nxpath::element_type>("/","NXroot")];
            root_rule.name("root_rule");
#ifdef CLANG_CXX
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunsequenced"
#endif
            nxpath_rule = eps[
                              //we start with an empty elements list
                              _a = construct<nxpath::elements_type>(), 
                              //and we start with an empty attribute
                              _b="",
                              //finally we start with an empty path which holds
                              //only a single root element
                              _val = construct<nxpath>(boost::phoenix::ref(_filename),_a,_b),
                              //this is where we add the root element
                              push_back(_val,construct<nxpath::element_type>("/","NXroot")) 
                              ]
                          >>
                          (   //parse the root element
                              root_rule[push_back(_a,_1)] 
                           || 
                              element_rule[pni::io::nx::insert(_a,end(_a),begin(_1),end(_1))]
                           || 
                              //here we do the attribute part
                              (lit("@")>id_[_b=_1])
                           ) [_val = construct<nxpath>(boost::phoenix::ref(_filename),_a,_b)] 
                          >eoi; //finally EOI is the terminal for the string
#ifdef CLANG_CXX
#pragma GCC diagnostic pop
#endif
        }

        private:
            //! the filename part
            pni::core::string _filename;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_internal_code
    //! \brief parser string to path
    //!
    //! Parse a string input and generate a path instance from it. 
    //!
    //! \throws parser_error in case of a parser problem
    //!
    //! \param input string from which to construct the path
    //! \return nxpath instance
    //!
    nxpath parse_path(const pni::core::string &input);

//end of parser namespace
}
                                    
//end of namespace
}
}
}
