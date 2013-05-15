/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: May 6, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */


#pragma once

#include <sstream>

#include<pni/core/types.hpp>
#include<pni/core/exceptions.hpp>
#include<pni/core/value.hpp>
#include<pni/core/darray.hpp>
#include<pni/core/array.hpp>
#include<vector>

#include "value_parser.hpp"
#include "delimiter_parser.hpp"


namespace pni{
namespace io{

    /*!
    \ingroup parser_classes
    \brief array construction lazy function

    This is the implementation of a lazy function for phoenix which can be used
    to create an array from a container. 
    */
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
        \brief create an array

        Template member function creating an instance of pni::core::array from
        an arbitrary number of arguments. 
        \tparam ATYPE array type
        \tparam ARGT argumen types
        \param args variadic argument list
        \return instance of pni::core::array
        */
        template<typename ATYPE,typename ...ARGT>
        pni::core::array create_array(ARGT ...args) const
        {
            return pni::core::array(std::move(ATYPE(args...)));
        }

        //---------------------------------------------------------------------
        /*!
        \brief copy data to array

        Copy data form an arbitrary container type to an instance of
        pni::core::array. The value_type of the container should be
        pni::core::value. 
        \tparam T data type of elements
        \tparam CTYPE container instance with values of type pni::core::value
        \param a array to which to copy
        \param values source values
        */
        template<typename T,typename CTYPE> 
            void copy_data(pni::core::array &a,const CTYPE &values) const
        {
            auto aiter = a.begin();
            auto viter = values.begin();
            while(aiter != a.end())
                *(aiter++) = (viter++)->template as<T>();

        }

        //---------------------------------------------------------------------
        /*!
        \brief create array
        
        Create an instance of pni::core::array as a function of a shape and a
        type id. 
        \throws type_error if tid is an unknown type
        \param shape the shape of the array
        \param tid type id of the array
        \return instance of pni::core::array
        */
        pni::core::array create_array(pni::core::shape_t &shape,
                                      pni::core::type_id_t tid) const
        {
            using namespace pni::core;

            if(tid == type_id_t::UINT8)
                return create_array<darray<uint8>>(shape);
            else if(tid == type_id_t::INT8)
                return create_array<darray<int8>>(shape);
            else if(tid == type_id_t::UINT16)
                return create_array<darray<uint16>>(shape);
            else if(tid == type_id_t::INT16)
                return create_array<darray<int16>>(shape);
            else if(tid == type_id_t::UINT32)
                return create_array<darray<uint32>>(shape);
            else if(tid == type_id_t::INT32)
                return create_array<darray<int32>>(shape);
            else if(tid == type_id_t::UINT64)
                return create_array<darray<uint64>>(shape);
            else if(tid == type_id_t::INT64)
                return create_array<darray<int64>>(shape);

            else if(tid == type_id_t::FLOAT32)
                return create_array<darray<float32>>(shape);
            else if(tid == type_id_t::FLOAT64)
                return create_array<darray<float64>>(shape);
            else if(tid == type_id_t::FLOAT128)
                return create_array<darray<float128>>(shape);
            else
            {
                std::stringstream ss;
                ss<<"Unsupported type id = "<<tid;
                throw type_error(EXCEPTION_RECORD,ss.str());
            }

            //this is just a dummy return - the code here will never be reached
            //as an exception is thrown if the type code cannot be handled.
            return create_array<darray<float128>>(shape);


        }
      
        //---------------------------------------------------------------------
        /*!
        \brief copy data

        Copies data from a container with elements of type pni::core::value 
        to an instance of pni::core::array. 

        \throws type_error if the type of the values is not supported
        \param array target array 
        \param values source container
        */
        template<typename CTYPE>
        void copy_data(pni::core::array &array,const CTYPE &values) const
        {
            using namespace pni::core;
            type_id_t tid = values.begin()->type_id();

            if(tid == type_id_t::UINT8) copy_data<uint8>(array,values);
            else if(tid == type_id_t::INT8) copy_data<int8>(array,values);
            else if(tid == type_id_t::UINT16) copy_data<uint16>(array,values);
            else if(tid == type_id_t::INT16) copy_data<int16>(array,values);
            else if(tid == type_id_t::UINT32) copy_data<uint32>(array,values);
            else if(tid == type_id_t::INT32) copy_data<int32>(array,values);
            else if(tid == type_id_t::UINT64) copy_data<uint64>(array,values);
            else if(tid == type_id_t::INT64) copy_data<int64>(array,values);

            else if(tid == type_id_t::FLOAT32) copy_data<float32>(array,values);
            else if(tid == type_id_t::FLOAT64) copy_data<float64>(array,values);
            else if(tid == type_id_t::FLOAT128) copy_data<float128>(array,values);
            else
            {
                std::stringstream ss;
                ss<<"Unsupported type id = "<<tid;
                throw type_error(EXCEPTION_RECORD,ss.str());
            }
        }

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
            array a = create_array(shape,n[0].type_id());
            copy_data(a,n);

            return a;
        }

    };

    /*!
    \ingroup parser_classes
    \brief array parser

    Numeric arrays have typically the following string representation
    \code
    [1, 4, 10, -12]
    \endcode
    They start with a start symbol (here '[') and are terminated by a stop
    symbol (here ']'). In between these symbols the data values are shown
    separated by a delimiter symbol (here the ','). 
    All these symbols can be configured for this class. 

    \code 
    typedef string::iterator iterator_t;
    typedef array_parser<iterator_t> parser_t;

    string data = "(1 2 43 5   5 5)";
    parser_t parser('(',')',' ');
    array a;
    parse(data.begin(),data.end(),parser,a);
    \endcode


    \tparam ITERT iterator type for the array parser
    */
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
        //! Initialization function used by all constructors
        void init()
        {
            using namespace pni::core;
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;

            data_rule = value_ % delimiter_;    
            array_rule = (_start_sign>data_rule>_stop_sign)
                         [_val = array_construction(_1)];

        }


    };

//end of namespace
}
}
