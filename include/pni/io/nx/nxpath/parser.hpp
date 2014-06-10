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

#include "nxpath.hpp"

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

            component_rule = +char_("-_a-zA-z0-9");
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
    //! \brief filename parser
    //! 
    //! This parser parses a file name. Of all components in a Nexus path, 
    //! a filename is allowed to contain one or many periods '.'. 
    //! In fact, a filename must have an extension to make it distinguishable 
    //! from other path elements.
    /*!
    \code
    path/filename.ext
    \endcode
    */
    //!
    //! \tparam ITERT iterator type for the parser
    //!
    template<typename ITERT> struct filename_parser :
    boost::spirit::qi::grammar<ITERT,string()>
    {
        //! rule for the file name including path up to the first extension
        boost::spirit::qi::rule<ITERT,string()> base_rule;
       
        //! rule for extensions
        boost::spirit::qi::rule<ITERT,string()> extension_rule;

        //! rule for a group element
        boost::spirit::qi::rule<ITERT,string()> filename_rule;

        //! default constructor
        filename_parser() : filename_parser::base_type(filename_rule)
        {
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;
            using boost::spirit::qi::_1;

            base_rule = +char_("-_a-zA-z0-9/.");
            extension_rule = +char_("-_a-zA-z0-9");
            filename_rule =  base_rule>>+('.'>extension_rule);
        }
    };




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
        nxpath_parser() : nxpath_parser::base_type(nxpath_rule)
        {

        }

        
    };
                                    
        
                                                        



//end of namespace
}
}
}
