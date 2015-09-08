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
#include "conversion_trait.hpp"
#include "delimiter_rule.hpp"
#include "parser.hpp"
#include "get_sequence_rule.hpp"


namespace pni{
namespace io{

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
    class parser<ITERT,std::vector<T>>
    {
        public:
            //! result type for the parser
            typedef std::vector<T>  result_type;
            //! input iterator type
            typedef ITERT           iterator_type;
            //! parser exception type
            typedef boost::spirit::qi::expectation_failure<iterator_type> 
                    expectation_error;
        private:
            //! conversion trait used during parsing
            typedef conversion_trait<T> trait_type;
            //! data type to read 
            typedef typename trait_type::read_type read_type;
            //! buffer type used for reading
            typedef std::vector<read_type> buffer_type;
            //! rule type to parse the sequence
            typename get_sequence_rule<ITERT,buffer_type>::type sequence_;

        public:
            //-----------------------------------------------------------------
            //!
            //! \brief default constructor
            //! 
            parser() : sequence_() 
            {}

            //-----------------------------------------------------------------
            //! 
            //! \brief constructor
            //! 
            //! \param del delimiter symbol for the sequence
            //!
            parser(char del): sequence_(del) 
            {}

            //-----------------------------------------------------------------
            //! 
            //! \brief constructor
            //! 
            //! \param start the start symbol for the sequence
            //! \param stop  the stop symbol for the sequence
            //!
            parser(char start,char stop) : sequence_(start,stop) 
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //! 
            //! \param start the start symbol for the sequence
            //! \param stop  the stop symbol for the sequence
            //! \param del   the delimiter symbol for the sequence
            //! 
            parser(char start,char stop,char del) : sequence_(start,stop,del) 
            {}


            //-----------------------------------------------------------------
            //!
            //! \brief parse a string
            //!
            //! Parses a string and stores the result in a vector. 
            //!
            //! \throws parser_error in case of errors
            //! \throws range_error in the case of an error during conversion
            //! 
            //! \param s string to parse
            //! \return instance of std::vector with the parsed data
            //!
            result_type  operator()(const core::string &s) const
            {
                using namespace pni::core;
                using namespace boost::spirit;
                
                buffer_type container;

                try
                {
                    if(!qi::parse(s.begin(),s.end(),sequence_>qi::eoi,container))
                    {
                        throw parser_error(EXCEPTION_RECORD,
                                "Error parsing sequence!");
                    }
                }
                catch(...)
                {
                    throw parser_error(EXCEPTION_RECORD,
                            "Cannot parse array data from string: "
                            "\""+s+"\"!");
                }

                //perform the conversion to the requested type - maybe not the
                //best solution - but should be sufficient for now.
                //Remove this code when we found a better way to handle (u)int8 
                //values.
                try
                {
                    result_type result;
                    for(auto e: container)
                        result.push_back(trait_type::convert(e));

                    return result;
                    
                }
                catch(...)
                {
                    throw parser_error(EXCEPTION_RECORD,
                            "Error during type conversion!");
                }
            }

    };


//end of namespace
}
}
