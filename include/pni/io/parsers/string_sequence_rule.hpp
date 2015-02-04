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
// Created on: Feb 2, 2015
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
    struct string_sequence_rule : qi::grammar<ITERT,ST()>
    {
        qi::rule<ITERT,core::string()> element_rule_;
        //! delimiter rule
        //delimiter_rule<ITERT> delimiter_;
        qi::rule<ITERT> start_;
        qi::rule<ITERT> stop_;
        qi::rule<ITERT> delimiter_;

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
        string_sequence_rule() : string_sequence_rule::base_type(sequence_)
        { 
            delimiter_ = +qi::blank;
            element_rule_ = *(qi::char_-qi::blank);
            sequence_ = element_rule_ % delimiter_; 
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
        string_sequence_rule(char del): 
            string_sequence_rule::base_type(sequence_),
            delimiter_(qi::char_(del))
        {
            element_rule_ = *(qi::char_-delimiter_);
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
        string_sequence_rule(char start,char stop):
            string_sequence_rule::base_type(sequence_)
        {
            start_ = qi::char_(start)>*qi::blank;
            stop_  = *qi::blank>qi::char_(stop);
            delimiter_ = (+qi::blank);
            element_rule_ = +(qi::char_-(qi::lit(stop)|qi::blank));
            sequence_ = start_> (element_rule_ % delimiter_)>stop_;
        }

        //--------------------------------------------------------------------
        //!
        //! \brief constructor
        //! 
        //! Customizes the start and stop symbol as well as the delimiter 
        //! symbol. 
        //! 
        string_sequence_rule(char start,char stop,char del):
            string_sequence_rule::base_type(sequence_)
        {
            start_ = qi::char_(start)>>*qi::blank;
            stop_  = *qi::blank>>qi::char_(stop);
            delimiter_ = *qi::blank>>qi::char_(del)>>*qi::blank;

            element_rule_ = *(qi::char_-(qi::lit(stop)|delimiter_));
            sequence_ = start_>(element_rule_ % delimiter_)>stop_;
        }

    };

//end of namespace
}
}
