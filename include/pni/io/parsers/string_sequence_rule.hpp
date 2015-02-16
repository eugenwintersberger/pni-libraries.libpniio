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

#include <boost/algorithm/string.hpp>
#include <boost/spirit/include/phoenix.hpp>
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

    //!
    //! \ingroup parser_classes
    //! \brief lazy string trimming
    //! 
    //! This lazy function is used to remove leading and trailing blanks 
    //! from strings. 
    //!
    struct trim_string
    {
        //! 
        //! \brief return type of the lazy function
        //! 
        template<typename Sig> struct result
        {
            typedef core::string type; //!< return value 
        };

        //--------------------------------------------------------------------
        //! 
        //! \brief trim implementation
        //! 
        //! Implements string trimming (stripping of all leading and trailing
        //! blanks) as a lazy function.
        //! 
        //! \tparam Arg input argument type
        //! \param n input argument
        //! \return string with all leading and trailing blanks removed
        //!
        template<typename Arg>
        core::string operator()(Arg const &n) const
        {
            string output(n.begin(),n.end());
            boost::trim(output);
            return output;
        }
    };


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
    //! \tparam ST container type
    //!
    template<
             typename ITERT,
             typename ST
            >
    struct string_sequence_rule : qi::grammar<ITERT,ST()>
    {
        //! rule to parse a single element of the sequence
        qi::rule<ITERT,core::string()> element_rule_;
        //! rule for the start symbol of the sequence
        qi::rule<ITERT> start_;
        //! rule for the stop symbol for the sequence
        qi::rule<ITERT> stop_;
        //! rule for the delimiter symbol for the sequence
        qi::rule<ITERT> delimiter_;

        //! the full rule to parse the sequence
        qi::rule<ITERT,ST()> sequence_;

        //! lazy function to trim the read string
        boost::phoenix::function<trim_string> trim;

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
            using qi::_val;
            using qi::_1;

            delimiter_ = +qi::blank;
            element_rule_ = (*(qi::char_-delimiter_))[_val = trim(_1)];
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
        //! \param del delimiter character for the sequence
        //! 
        string_sequence_rule(char del): 
            string_sequence_rule::base_type(sequence_)
        {
            using qi::_val;
            using qi::_1;

            delimiter_ = qi::char_(del);
            element_rule_ = (*(qi::char_-delimiter_))[_val = trim(_1)];
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
        //! \param start the start symbol for the sequence
        //! \param stop  the stop symbol for the sequence
        //!
        string_sequence_rule(char start,char stop):
            string_sequence_rule::base_type(sequence_)
        {
            using qi::_1;
            using qi::_val;

            start_ = qi::char_(start)>*qi::blank;
            stop_  = *qi::blank>qi::char_(stop);
            delimiter_ = (+qi::blank);
            element_rule_ = (+(qi::char_-(qi::lit(stop)|delimiter_)))[_val=trim(_1)];
            sequence_ = start_> (element_rule_ % delimiter_)>stop_;
        }

        //--------------------------------------------------------------------
        //!
        //! \brief constructor
        //! 
        //! Customizes the start and stop symbol as well as the delimiter 
        //! symbol. 
        //!
        //! \param start the start symbol for the sequence
        //! \param stop  the stop symbol for the sequence
        //! \param del   the delimiter symbol for the sequence
        //! 
        string_sequence_rule(char start,char stop,char del):
            string_sequence_rule::base_type(sequence_)
        {
            start_ = qi::char_(start)>*qi::blank;
            stop_  = *qi::blank>qi::char_(stop);
            delimiter_ = qi::char_(del);

            element_rule_ = (*(qi::char_-(qi::lit(stop)|delimiter_)))[qi::_val =
                trim(qi::_1)];
            sequence_ = start_>(element_rule_ % delimiter_)>stop_;
        }

    };

//end of namespace
}
}
