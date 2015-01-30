//
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
// Created on: Jan 23, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//

#pragma once

#include<pni/core/types.hpp>
#include<vector>
#include<limits>

#include <boost/spirit/include/qi.hpp>

#include "../exceptions.hpp"
#include "get_rule_type.hpp"

namespace pni{
namespace io{

    using namespace boost::spirit;
    using namespace pni;

    //!
    //! \ingroup parser_classes
    //! \brief default conversion trait
    //!
    //! Conversion trait used to convert parsed data to the requested 
    //! type. In this default version nothing has to be done as the 
    //! type read from the string is the same as the type requested by
    //! the user.
    //! 
    //! \tparam T result type
    //! 
    template<typename T>
    struct conversion_trait
    {
        typedef T result_type;
        typedef T read_type;

        static result_type convert(read_type &&v) 
        { 
            return v; 
        }
    };

    //------------------------------------------------------------------------
    //! 
    //! \ingroup parser_classes
    //! \brief uint8 conversion trait
    //! 
    //! Specialization of the conversion_trait template for the uint8 type. 
    //! In this special case uint16 is used for parsing the data.
    //!
    template<>
    struct conversion_trait<uint8>
    {
        typedef uint8  result_type;
        typedef uint16 read_type;

        static result_type convert(read_type &&v) 
        { 
            return pni::core::convert<result_type>(v); 
        }
    };

    //------------------------------------------------------------------------
    //! 
    //! \ingroup parser_classes
    //! \brief int8 conversion trait
    //! 
    //! Specialization of the conversion_trait template for the int8 type. 
    //! In this special case int16 is used for parsing the data.
    //!
    template<>
    struct conversion_trait<int8>
    {
        typedef int8  result_type;
        typedef int16 read_type;

        static result_type convert(read_type &&v) 
        { 
            return pni::core::convert<result_type>(v); 
        }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup parser_classes
    //! \brief parser for primitive types
    //!
    //! This version of the parser structure provides a default parsing 
    //! implementation for primitive types. The aim of this class is 
    //! to hide all the complexity of the boost::spirit::qi parsers. 
    //! In addition it catches all spirit exceptions and wraps them 
    //! into a parser_error exception. 
    //! 
    //! Use this parser to parse a single primitive value from a string.
    //! The input data must be trimmed - so no leading or trailing 
    //! blanks are allowed. The string is supposed to end with the last 
    //! character assembling the value to parse.
    //! 
    //! \tparam ITERT iterator type
    //! \tparam T     primitive data type
    //!
    template<
             typename ITERT,
             typename T
            >
    class parser 
    {
        public:
            typedef ITERT iterator_type;
            typedef T     result_type;
            typedef qi::expectation_failure<iterator_type> expectation_error;
        private:
            typedef conversion_trait<result_type>   trait_type;
            typedef typename trait_type::read_type  read_type;
            typename get_rule_type<iterator_type,read_type>::type _rule;

        public:
            //!
            //! \brief parser primitive type
            //! 
            //! Parses the input string and returns an instance of a primitive type.
            //! In case of errors parser_error is thrown. 
            //!
            //! \throws parser_error in case of any problems
            //! \param data the string with input data
            //! \return instance of the primitive type
            result_type parse(const string &data) const
            {
                read_type   buffer;
                
                try
                {
                    if(!qi::parse(data.begin(),data.end(),_rule>qi::eoi,buffer))
                    {
                        throw parser_error(EXCEPTION_RECORD,
                                "Failure parsing primitive type!");
                    }

                }
                catch(const expectation_error &error)
                {
                    throw parser_error(EXCEPTION_RECORD,
                            "Syntax error!");
                }

                try
                {
                    return trait_type::convert(std::move(buffer));
                }
                catch(...)
                {
                    throw parser_error(EXCEPTION_RECORD,
                            "Failure during type conversion!");
                }

            }
    };


//end of namespace
}
}
