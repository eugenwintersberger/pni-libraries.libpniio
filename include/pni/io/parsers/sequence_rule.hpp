// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jan 29, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//


#pragma once

#include <sstream>

#include<pni/core/types.hpp>
#include<pni/core/error.hpp>
#include<vector>

#include "../exceptions.hpp"
#include "get_rule_type.hpp"
#include "delimiter_rule.hpp"
#include "primitive_type_parser.hpp"


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
    //! The container can be any STL compliant container type.
    //!
    //! \tparam ITERT input iterator type
    //! \tparam CTYPE container type
    //!
    template<
             typename ITERT,
             typename ST 
            >
    struct sequence_rule : qi::grammar<ITERT,ST()>
    {
        //! value type of the sequence type
        typedef typename ST::value_type value_type; 
        //! rule to parse the value_type of the sequence
        typename get_rule_type<ITERT,value_type>::type element_rule_;

        //! delimiter rule
        delimiter_rule<ITERT> delimiter_;

        //! a possible start symbol
        char start_symbol_;
        //! a possible stop symbol
        char stop_symbol_;
        //! the full rule to parse the sequence
        qi::rule<ITERT,ST()> sequence_;

        //--------------------------------------------------------------------
        //!
        //! \brief default constructor
        //!
        //! When using the default constructor the elements are assumed to be 
        //! separated by an arbitrary number of blanks. No start and stop 
        //! symbol are taken into account.
        //!
        sequence_rule() : sequence_rule::base_type(sequence_)
        { 
            sequence_ = element_rule_ %(+qi::blank); 
        }

        //--------------------------------------------------------------------
        //!
        //! \brief constructor
        //!
        //! This version of the sequence_rule constructor allows passing a
        //! a custom delimiter symbol. The delimiter_rule class is used 
        //! to parse the delimiter. Thus, the delimiter symbol can have an 
        //! arbitrary number of preceding and tailing blanks. 
        //!
        sequence_rule(char del): 
            sequence_rule::base_type(sequence_),
            delimiter_(del)
        {
            sequence_ = element_rule_ % delimiter_;
        }

        //--------------------------------------------------------------------
        //!
        //! \brief constructor
        //! 
        //! Set a start and stop symbol. In this case the rule expects that the 
        //! sequence is embraced into a start and stop symbol. However, the 
        //! individual elements are still separated by an arbitrary number of
        //! blanks. 
        //!
        sequence_rule(char start,char stop):
            sequence_rule::base_type(sequence_),
            start_symbol_(start),
            stop_symbol_(stop)
        {
            sequence_ = start_symbol_>(element_rule_ % (+qi::blank))>stop_symbol_;
        }

        //--------------------------------------------------------------------
        //!
        //! \brief constructor
        //! 
        //! Customizes the start and stop symbol as well as the delimiter 
        //! symbol. 
        //! 
        sequence_rule(char start,char stop,char del):
            sequence_rule::base_type(sequence_),
            delimiter_(del),
            start_symbol_(start),
            stop_symbol_(stop)
        {
            sequence_ = start_symbol_>(element_rule_ % delimiter_)>stop_symbol_;
        }

    };

//end of namespace
}
}
