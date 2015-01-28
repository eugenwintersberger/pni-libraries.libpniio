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
// Created on: Jan 22, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <sstream>

#include<pni/core/types.hpp>
#include<pni/core/error.hpp>
#include<vector>

#include "../exceptions.hpp"
#include "parser.hpp"


namespace pni{
namespace io{

    using namespace pni;
    using namespace boost::spirit;
    
    template<typename ITERT> class parser<ITERT,uint8,true>
    {
        public:
            typedef ITERT iterator_type;
            typedef uint8 value_type;
        private:
            typedef element_rule_type<iterator_type,uint16> rule_type ;
            typedef typename  rule_type::type parser_type;

            parser_type _parser_instance;
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
            value_type parse(const string &data)
            {
                iterator_type start = data.begin();
                iterator_type stop  = data.end();
                uint16 tmp;
                value_type result;

                try
                {
                    if(!qi::parse(start,stop,_parser_instance>qi::eoi,tmp))
                    {
                        throw parser_error(EXCEPTION_RECORD,
                                "Failure parsing primitive type!");
                    }
                }
                catch(...)
                {
                    throw parser_error(EXCEPTION_RECORD,
                            "Failed parsing uint8 value!");
                }

                try
                {
                    result = convert<value_type>(tmp);
                }
                catch(...)
                {
                    throw parser_error(EXCEPTION_RECORD,
                            "Failure during type conversion after parsing!");
                }

                return result;
            }
    };


    template<typename ITERT> class parser<ITERT,int8,true>
    {
        public:
            typedef ITERT iterator_type;
            typedef int8 value_type;
        private:
            typedef element_rule_type<iterator_type,int16> rule_type ;
            typedef typename  rule_type::type parser_type;

            parser_type _parser_instance;
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
            value_type parse(const string &data)
            {
                iterator_type start = data.begin();
                iterator_type stop  = data.end();
                int16 tmp;
                value_type result;

                try
                {
                    if(!qi::parse(start,stop,_parser_instance>qi::eoi,tmp))
                    {
                        throw parser_error(EXCEPTION_RECORD,
                                "Failure parsing primitive type!");
                    }
                }
                catch(...)
                {
                    throw parser_error(EXCEPTION_RECORD,
                            "Failed parsing int8 value!");
                }

                try
                {
                    result = convert<value_type>(tmp);
                }
                catch(...)
                {
                    throw parser_error(EXCEPTION_RECORD,
                            "Failure during type conversion after parsing!");
                }

                return result;
            }
    };

//end of namespace
}
}

