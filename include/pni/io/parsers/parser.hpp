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
#include <pni/core/type_erasures/value.hpp>
#include <pni/core/arrays/slice.hpp>

#include "../exceptions.hpp"
#include "conversion_trait.hpp"
#include "../container_io_config.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

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

    template<typename T>
    class parser<std::complex<T>>
    {
    private:
        using base_type = T;
        parser<base_type> _base_parser;
    public:
        using result_type = std::complex<T>;

        result_type operator()(const pni::core::string &input) const
        {
            using namespace pni::core;

            boost::regex cmplx_regex(default_complex_regexp);

            result_type value;
            boost::smatch results;
            if(boost::regex_match(input,results,cmplx_regex))
            {
                base_type real_part  = 0.0,
                          imag_part  = 0.0,
                          image_sign = 1.0;
                string part = results.str("REALPART");
                if(!part.empty()) real_part = _base_parser(part);

                part = results.str("IMAGSIGN");
                if(!part.empty())
                {
                    if(part[0]=='-') image_sign = -1.0;
                }

                part = results.str("IMAGPART");
                if(!part.empty()) imag_part = _base_parser(part);

                return result_type(real_part,image_sign*imag_part);

            }
            else
            {
                std::stringstream ss;
                ss<<"Cannot convert ["<<input<<"] to "<<type_id(value)<<"!";
                throw parser_error(EXCEPTION_RECORD,ss.str());
            }
        }
    };

    template<>
    class parser<pni::core::bool_t>
    {
    private:
        boost::regex _true_regex;
        boost::regex _false_regex;
    public:
        using result_type = bool;

        explicit parser();

        explicit parser(const pni::core::string &true_regex,
                        const pni::core::string &false_regex);

        result_type operator()(const pni::core::string &input) const;

    };


    template<>
    class parser<pni::core::slice>
    {
    private:
        //!
        //! regular expression for slices
        //!
        boost::regex _regexpr;
    public:
        using result_type = pni::core::slice;

        explicit parser();

        result_type operator()(const pni::core::string &input) const;
    };

    //!
    //! \ingroup parser_classes
    //! \brief parser for general values
    //!
    //! This is a specialization of the parser class for the value type erasure.
    //! The parser tries to identify the value provided by the data string
    //! and converts it to the appropriate type which will then be wrapped
    //! in an instance of pni::core::value.
    //!
    //! The class currently supports the following types
    //! * 64Bit integer
    //! * 64Bit floating point
    //! * 64Bit complex floats
    //! * and strings
    //!
    template<>
    class parser<pni::core::value>
    {
    private:
        //!
        //! parser for integer values
        //!
        parser<pni::core::int64>     _int_parser;

        //!
        //! parser for float values (doubles)
        //!
        parser<pni::core::float64>   _float_parser;

        //!
        //! parser for complex values
        //!
        parser<pni::core::complex64> _complex_parser;
    public:
        using result_type = pni::core::value;

        result_type operator()(const pni::core::string &data) const;
    };

    template<>
    class parser<pni::core::string>
    {
        public:
            using result_type = pni::core::string;

            result_type operator()(const pni::core::string &data) const;
    };

    template<
             typename T
            >
    class parser<std::vector<T>>
    {
        private:
            container_io_config _config;
        public:
            using value_type  = T;
            using result_type = std::vector<value_type>;

            parser(const container_io_config &config=container_io_config()):
                _config(config)
            {}

            result_type operator()(const pni::core::string &) const
            {

                return result_type();
            }
    };


//end of namespace
}
}
