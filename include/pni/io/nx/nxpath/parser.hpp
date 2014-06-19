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
    template<typename ITERT> struct element_parser :
    boost::spirit::qi::grammar<ITERT,
                               boost::spirit::locals<string,string>, 
                               nxpath::element_type()>
    {
        //! rule for a single component
        boost::spirit::qi::rule<ITERT,string()> component_rule;

        //! rule for a group element
        boost::spirit::qi::rule<ITERT,
                                boost::spirit::locals<string,string>, 
                                nxpath::element_type()> element_rule;

        //! default constructor
        element_parser() : element_parser::base_type(element_rule)
        {
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;
            using boost::spirit::qi::_1;

            component_rule = +char_("-_a-zA-Z0-9");
            element_rule =  eps[_a="",_b=""]>>(
                                  (component_rule[_a=_1]>>-(':'>component_rule[_b=_1]))                              |
                                  (':'>component_rule)[_b = _1]
                    )[_val = construct<nxpath::element_type>(_a,_b)];
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
    struct elements_parser :
        boost::spirit::qi::grammar<ITERT,nxpath::elements_type()>
    {
        //! rule for the entire group portion
        boost::spirit::qi::rule<ITERT,nxpath::elements_type()> elements_rule;
        //! group element parser
        element_parser<ITERT> element_; 

        //! default constructor
        elements_parser() : elements_parser::base_type(elements_rule)
        {
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;

            elements_rule = ('/'>>element_ % '/') | ( element_ % '/');
        }
    };

    //--------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_code
    //! \brief file path parser
    //! 
    //! This parser parses a file name. Of all components in a Nexus path, 
    //! a filename is allowed to contain one or many periods '.'. 
    //! In fact, a filename must have an extension to make it distinguishable 
    //! from other path elements. Every file path must be terminated with a 
    //! :// even when only the file is given.
    /*!
    \code
    path/filename.ext://
    \endcode
    */
    //!
    //! \tparam ITERT iterator type for the parser
    //!
    template<typename ITERT> struct filepath_parser :
    boost::spirit::qi::grammar<ITERT,string()>
    {
        //! rule for the file name including path up to the first extension
        boost::spirit::qi::rule<ITERT,string()> base_rule;

        //! rule for a group element
        boost::spirit::qi::rule<ITERT,string()> filepath_rule;


        //! default constructor
        filepath_parser() : filepath_parser::base_type(filepath_rule)
        {
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;
            using boost::spirit::qi::_1;

            //the basename of a file must not contain any / or . 
            base_rule = *char_("-_a-zA-Z0-9./");
            filepath_rule = base_rule[_val = _1] > lit("://");
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
    struct nxpath_parser : 
        boost::spirit::qi::grammar<ITERT,
                                   boost::spirit::locals
                                   <
                                       string,
                                       nxpath::elements_type,
                                       string,
                                       bool
                                   >,
                                   nxpath()>

    {
        boost::spirit::qi::rule<ITERT,
                               boost::spirit::locals
                               <
                                   string,
                                   nxpath::elements_type,
                                   string,
                                   bool
                               >,
                               nxpath()> nxpath_rule;

        //add parser for the filepath
        filepath_parser<ITERT> filepath_rule;

        //add parser for the elements
        elements_parser<ITERT> element_rule;

        nxpath_parser() : nxpath_parser::base_type(nxpath_rule)
        {
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;
            using boost::spirit::qi::_1;
            
            nxpath_rule = eps[_a="",_c="",_d=false]>>
                          (-filepath_rule[_a=_1] || lit("://")
                           || -lit("/")[_d=true]
                           || element_rule[_b=_1]
                           || (lit("@")>+char_("-_a-zA-Z0-9")[_c = _1])) 
                          [_val = construct<nxpath>(_a,_b,_c,_d)];
        }
    };
                                    
//end of namespace
}
}
}
