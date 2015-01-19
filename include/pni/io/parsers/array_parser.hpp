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
#include<pni/core/type_erasures.hpp>
#include<pni/core/arrays.hpp>
#include<vector>

#include "../exceptions.hpp"
#include "value_parser.hpp"
#include "delimiter_parser.hpp"


namespace pni{
namespace io{

    //!
    //! \ingroup parser_classes
    //! \brief array construction lazy function
    //! 
    //! This is the implementation of a lazy function for phoenix which can 
    //! be used to create an array from a container. 
    //!
    struct array_construction_imp
    {
        //! determine the return type of the function
        template<typename Sig> struct result
        {
            //! the return type
            typedef pni::core::array type;
        };

        //---------------------------------------------------------------------
        /*!
        \brief lazy function implementation

        This operator finally implements the lazy function. 
        \tparam Arg argument type
        \param n container with input data
        \return instance of pni::core::array
        */
        template<typename Arg> pni::core::array operator()(Arg const &n) const
        {
            using namespace pni::core;
            shape_t shape{n.size()};
           
            //create the array
            array a = pni::core::make_array(n[0].type_id(),shape);
            std::copy(n.begin(),n.end(),a.begin());

            return a;
        }

    };

    //!
    //! \ingroup parser_classes
    //! \brief array parser
    //! 
    //! Numeric arrays have typically the following string representation
    //! They start with a start symbol (here '[') and are terminated by a stop
    //! symbol (here ']'). In between these symbols the data values are shown
    //! separated by a delimiter symbol (here the ','). 
    //! All these symbols can be configured for this class. 
    //!
    //! \tparam ITERT iterator type for the array parser
    //!
    template<typename ITERT> 
    struct array_parser : boost::spirit::qi::grammar<ITERT,pni::core::array()>
    {
        //================public types=========================================
        //! container type for data
        typedef std::vector<pni::core::value> data_t;
        //! data parsing rule
        boost::spirit::qi::rule<ITERT,data_t()> data_rule;
        //! the entire array rule
        boost::spirit::qi::rule<ITERT,pni::core::array()> array_rule;
        //! lazy function for array creation
        boost::phoenix::function<array_construction_imp> array_construction;

        //=======================local variables===============================
        //! starting symbol
        char _start_sign;
        //! end symbol
        char _stop_sign;
        //! parser for values
        value_parser<ITERT> value_;
        //! parser for delimiters
        delimiter_parser<ITERT> delimiter_;

        //====================methods and constructor===========================
        //! default constructor
        array_parser() : 
            array_parser::base_type(array_rule),
            _start_sign('['),
            _stop_sign(']'),
            delimiter_(',')

        {
            init();
        }

        //---------------------------------------------------------------------
        /*!
        \brief constructor

        \param start start symbol
        \param stop end symbol
        \param del data delimiter symbol
        */
        array_parser(char start,char stop,char del):
            array_parser::base_type(array_rule),
            _start_sign(start),
            _stop_sign(stop),
            delimiter_(del)
        {
            init();
        }

        //---------------------------------------------------------------------
        /*!
        \brief constructor

        Using this constructor is setting up the array parser in a way so that
        no start and stop symbol are required.
        \param del delimiter symbol
        */
        array_parser(char del):
            array_parser::base_type(array_rule),
            delimiter_(del)
        {
            using namespace pni::core;
            using namespace boost::spirit::qi;
            using boost::spirit::qi::_1;
            using namespace boost::fusion;
            using namespace boost::phoenix;

            data_rule = value_ % delimiter_;    
            array_rule = (data_rule)[_val = array_construction(_1)];
        }


        //---------------------------------------------------------------------
        //! Initialization function used by all constructors
        void init()
        {
            using namespace pni::core;
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;
            using boost::spirit::qi::_1;

            data_rule = value_ % delimiter_;    
            array_rule = (_start_sign>data_rule>_stop_sign)
                         [_val = array_construction(_1)];

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
    template<typename PTYPE>
    pni::core::array array_from_string(const pni::core::string &s,const PTYPE &p)
    {
        using namespace pni::core;
        typedef typename PTYPE::iterator_type iterator_t;

        iterator_t start_iter = s.begin();
        iterator_t stop_iter  = s.end();

        array a;
        try
        {
            parse(start_iter,stop_iter,p,a);
        }
        catch(...)
        {
            throw parser_error(EXCEPTION_RECORD,
                    "Cannot parse array data from string: "
                    "\""+s+"\"!");
        }

        return a;
    }

//end of namespace
}
}
