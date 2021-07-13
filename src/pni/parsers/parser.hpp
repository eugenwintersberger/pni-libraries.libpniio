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

#include <pni/core/types.hpp>
#include <pni/core/type_erasures/value.hpp>
#include <pni/core/arrays/slice.hpp>

#include <pni/exceptions.hpp>
#include <pni/parsers/conversion_trait.hpp>
#include <pni/container_io_config.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <pni/windows.hpp>

namespace pni{
namespace io{

    static const boost::regex default_int_regexp("^[+-]?\\d+$") ;
    static const boost::regex default_float_regexp("^[+-]?\\d+\\.(\\d+)?([Ee][+-]?\\d+)?$");
    static const boost::regex default_complex_regexp("^(?<REALPART>[+-]?\\d+\\.(\\d+)?([Ee][+-]?\\d+)?)?((?<IMAGSIGN>[+-]?[ijI])(?<IMAGPART>[+-]?\\d+\\.(\\d+)?([Ee][+-]?\\d+)?)?)?$");


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
    //! By default the output iterator is a const string iterator.
    //!
    //! \tparam T     primitive data type
    //!
    template<
             typename T
            >
    class parser
    {
    private:
        using conversion_t = conversion_trait<T>;
        using read_type = typename conversion_t::read_type;
        using type_info_t = pni::core::type_info<T>;
    public:
        using result_type = T;
        //!
        //! \brief parser primitive type
        //!
        //! Parses the input string and returns an instance of a primitive type.
        //! In case of errors parser_error is thrown.
        //!
        //! \throws parser_error in case of any problems
        //! \param data the string with input data
        //! \return instance of the primitive type
        //!
        result_type operator()(const pni::core::string &data) const
        {
            using namespace pni::core;

            result_type value;

            if((!type_info_t::is_signed) && (data[0] == '-'))
            {
                std::stringstream ss;
                ss<<"Cannot store a signed value ["<<data<<"] an instance of "
                  <<type_id(value);
                throw parser_error(EXCEPTION_RECORD,ss.str());
            }

            try
            {
                value = conversion_t::convert(
                        boost::lexical_cast<read_type>(data));

            }
            catch(const boost::bad_lexical_cast &)
            {
                std::stringstream ss;
                ss<<"Could not convert ["<<data<<"] to a value of type ";
                ss<<type_id(value);
                throw parser_error(EXCEPTION_RECORD,ss.str());
            }
            catch(const pni::core::range_error &error)
            {
                std::stringstream ss;
                ss<<"A range error occured with: "<<error.description()<<std::endl;
                ss<<"Could not convert input ["<<data<<"] to a value fo type ";
                ss<<type_id(result_type());
                throw parser_error(EXCEPTION_RECORD,ss.str());
            }
            catch(...)
            {
                std::stringstream ss;
                ss<<"Unknown error when trying to convert ["<<data<<"] to ";
                ss<<type_id(result_type());
                throw parser_error(EXCEPTION_RECORD,ss.str());
            }

            return value;
        }
    };

//end of namespace
}
}
