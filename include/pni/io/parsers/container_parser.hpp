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
             typename T
            >
    class parser<ITERT,std::vector<T>,false>
    {
        public:
            typedef std::vector<T>  result_type;
            typedef ITERT           iterator_type;
            typedef qi::expectation_failure<iterator_type> expectation_error;
        private:
            typedef T value_type; 
            //! element rule
            typename element_rule_type<ITERT,value_type>::type element_;

            //! starting symbol
            char _start_token;
            //! end symbol
            char _stop_token;
            //! parser for delimiters
            delimiter_parser<ITERT> delimiter_;

        public:
            //! default constructor
            parser() : 
                _start_token('['),
                _stop_token(']'),
                delimiter_(',')

            { }

            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! \param start start symbol
            //! \param stop end symbol
            //! \param del data delimiter symbol
            //!
            parser(char start,char stop,char del):
                _start_token(start),
                _stop_token(stop),
                delimiter_(del)
            { }

            //-----------------------------------------------------------------
            //!
            //! \ingroup parser_classes
            //! \brief extract array data from string 
            //!
            //! This template function can be used to extract an array from a
            //! string  using a parser type. Most naturally this parser would 
            //! be an instance of array_parser. An exception is thrown either 
            //! when the string represents data that cannot be parsed by the 
            //! parser or when the resulting array has a length 0.
            //!
            //! \throws parser_error in case of errors
            //! \tparam PTYPE parser type
            //! \param s string to parse
            //! \param p parser instance
            //! \return array instance
            //!
            result_type  parse(const core::string &s) const
            {
                using namespace pni::core;

                result_type container;

                auto rule = element_ % delimiter_;

                try
                {
                    if((_start_token == ' ') && (_stop_token == ' '))
                        qi::parse(s.begin(),s.end(),element_%delimiter_,container);
                    else
                        qi::parse(s.begin(),s.end(),
                                  _start_token>(element_ % delimiter_)>_stop_token,
                                  container);
                }
                catch(...)
                {
                    throw parser_error(EXCEPTION_RECORD,
                            "Cannot parse array data from string: "
                            "\""+s+"\"!");
                }

                return container;
            }

    };


//end of namespace
}
}
