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

    struct array_construction_imp
    {
        template<typename Sig> struct result
        {
            typedef pni::core::array type;
        };

        template<typename ATYPE,typename ...ARGT>
        pni::core::array create_array(ARGT ...args) const
        {
            return pni::core::array(std::move(ATYPE(args...)));
        }

        template<typename T,typename CTYPE> 
            void copy_data(pni::core::array &a,const CTYPE &values) const
        {
            auto aiter = a.begin();
            auto viter = values.begin();
            while(aiter != a.end())
                *(aiter++) = (viter++)->template as<T>();

        }

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


    \tparam ITERT iterator type for the array parser
    */
    template<typename ITERT> 
    struct array_parser : boost::spirit::qi::grammar<ITERT,pni::core::array()>
    {
        //types
        typedef std::vector<pni::core::value> data_t;
        boost::spirit::qi::rule<ITERT,data_t()> data_rule;
        boost::spirit::qi::rule<ITERT,pni::core::array()> array_rule;
        boost::phoenix::function<array_construction_imp> array_construction;

        //members
        char _start_sign;
        char _stop_sign;
        value_parser<ITERT> value_;
        delimiter_parser<ITERT> delimiter_;

        array_parser() : 
            array_parser::base_type(array_rule),
            _start_sign('['),
            _stop_sign(']'),
            delimiter_(',')

        {
            init();
        }

        array_parser(char start,char stop,char del):
            array_parser::base_type(array_rule),
            _start_sign(start),
            _stop_sign(stop),
            delimiter_(del)
        {
            init();
        }


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
