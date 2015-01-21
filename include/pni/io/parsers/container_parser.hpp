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
// Created on: May 6, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//


#pragma once

#include <sstream>

#include<pni/core/types.hpp>
#include<pni/core/error.hpp>
#include<vector>

#include "../exceptions.hpp"
#include "element_rule_type.hpp"
#include "delimiter_parser.hpp"


namespace pni{
namespace io{

    using namespace pni;
    using namespace boost::spirit;

    //------------------------------------------------------------------------
    //!
    //! \ingroup parser_classes
    //! \brief container parser
    //! 
    //! This parser reads a linear container of data from a string. The data
    //! type of the container is assumed to be homogeneous. This means that 
    //! all elements must match with the parser selected for the element
    //! type.
    //! 
    //! In their string representation container data is assumed to be embraced 
    //! between a start and a stop token. The elements are assumed to be 
    //! separated by a delimiter token.
    //! 
    //! 
    //!
    //! \tparam ITERT input iterator type
    //! \tparam CTYPE container type
    //!
    template<
             typename ITERT,
             typename CTYPE
            > 
    struct container_parser : qi::grammar<ITERT,CTYPE()>
    {
        //================public types=========================================
        //! element type of the container
        typedef typename CTYPE::value_type value_type;
        //! element rule
        typename element_rule_type<ITERT,value_type>::type element_;
        //! container rule
        qi::rule<ITERT,CTYPE()> container_rule;

        //=======================local variables===============================
        //! starting symbol
        char _start_token;
        //! end symbol
        char _stop_token;
        //! parser for delimiters
        delimiter_parser<ITERT> delimiter_;

        //====================methods and constructor===========================
        //! default constructor
        container_parser() : 
            container_parser::base_type(container_rule),
            _start_token('['),
            _stop_token(']'),
            delimiter_(',')

        {
            init();
        }

        //---------------------------------------------------------------------
        //!
        //! \brief constructor
        //!
        //! \param start start symbol
        //! \param stop end symbol
        //! \param del data delimiter symbol
        //!
        container_parser(char start,char stop,char del):
            container_parser::base_type(container_rule),
            _start_token(start),
            _stop_token(stop),
            delimiter_(del)
        {
            init();
        }

        //---------------------------------------------------------------------
        //!
        //! Initialization function used by all constructors
        //!
        void init()
        {
            using namespace boost::spirit::qi;

            container_rule = _start_token > (element_ % delimiter_) >
                _stop_token;    
        }
    };


    //!
    //! \ingroup parser_classes
    //! \brief extract array data from string 
    //!
    //! This template function can be used to extract an array from a string 
    //! using a parser type. Most naturally this parser would be an instance 
    //! of array_parser. An exception is thrown either when the string 
    //! represents data that cannot be parsed by the parser or when the 
    //! resulting array has a length 0.
    //!
    //! \throws parser_error in case of errors
    //! \tparam PTYPE parser type
    //! \param s string to parse
    //! \param p parser instance
    //! \return array instance
    //!
    template<typename CTYPE>
    CTYPE  container_from_string(const core::string &s)
    {
        using namespace pni::core;
        typedef typename CTYPE::iterator_type iterator_type;
        typedef container_parser<iterator_type,CTYPE> parser_type;
        parser_type parser;

        iterator_type start_iter = s.begin();
        iterator_type stop_iter  = s.end();

        CTYPE container;
        try
        {
            parse(start_iter,stop_iter,parser,container);
        }
        catch(...)
        {
            throw parser_error(EXCEPTION_RECORD,
                    "Cannot parse array data from string: "
                    "\""+s+"\"!");
        }

        return container;
    }

//end of namespace
}
}
