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
// Created on: Feb 11, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <iterator>
#include <complex>
#include <pni/core/types.hpp>
#include <pni/core/type_erasures.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/mpl/map.hpp>

#include "primitive_generators.hpp"

namespace pni{
namespace io{

    using namespace pni::core;
    using namespace boost::spirit;
    
    template<typename ITERT,typename T>
    using my_uint_karma = karma::uint_generator<T>;

    //!
    //! \ingroup formatter_classes
    //! \brief generator for complex numbers
    //!
    //! This is a karma generator for complex numbers. 
    //!
    //! \tparam OITER output iterator
    //! \tparam T base type for the copmlex type
    template<
             typename OITER             
            >
    struct value_generator : karma::grammar<OITER,value()>
    {
        //!
        //! \brief get real part
        //! 
        //! This is a lazy function returning the real part of a complex 
        //! number.
        //! 
        struct lazy_to_string
        {
            typedef std::back_insert_iterator<core::string> iterator_type;
            typedef primitive_generators<iterator_type> generator_map;
            //!
            //! \brief result type of the lazy function
            //! 
            template<typename Sig> struct result
            {
                typedef string type; //!< result type
            };
            
            template<typename T>
            static string _to_string(const value &v)
            {
                typedef typename boost::mpl::at<generator_map,T>::type generator_type;                
                
                string formatter_result;
                iterator_type inserter(formatter_result);
                
                karma::generate(inserter,generator_type(),v.template as<T>());
                
                return formatter_result;
            }

            //!
            //! \brief get real part
            //!
            //! This function template actually implements the extraction of 
            //! the real part from a complex number.
            //! 
            //! \tparam Arg argument type (must be a complex type)
            //! \param n complex input argument
            //! \return real part of the complex number
            //!
            template<typename Arg>
            string operator()(Arg const &n) const
            {
                switch(type_id(n))
                {
                    case type_id_t::UINT8:
                        return _to_string<uint8>(n);
                    case type_id_t::INT8:
                        return _to_string<int8>(n);
                    case type_id_t::UINT16:
                        return _to_string<uint16>(n);
                    case type_id_t::INT16:
                        return _to_string<int16>(n);
                    case type_id_t::UINT32:
                        return _to_string<uint32>(n);
                    case type_id_t::INT32:
                        return _to_string<int32>(n);
                    case type_id_t::UINT64:
                        return _to_string<uint64>(n);
                    case type_id_t::INT64:
                        return _to_string<int64>(n);
                    case type_id_t::FLOAT32:
                        return _to_string<float32>(n);
                    case type_id_t::FLOAT64:
                        return _to_string<float64>(n);
                    case type_id_t::FLOAT128:
                        return _to_string<float128>(n);
                    case type_id_t::COMPLEX32:
                        return _to_string<complex32>(n);
                    case type_id_t::COMPLEX64:
                        return _to_string<complex64>(n);
                    case type_id_t::COMPLEX128:
                        return _to_string<complex128>(n);
                    case type_id_t::BOOL:
                        return _to_string<bool_t>(n);
                    case type_id_t::STRING:
                        return n.template as<string>();                            
                    default:
                        throw type_error(EXCEPTION_RECORD,
                            "The value instances holds an unkown type!");
                    
                }
                return "hello world";
            }
        };

        

        //-------------------------------------------------------------------
        //! instance of the get_real lazy function
        boost::phoenix::function<lazy_to_string> to_string;      
       
        //! total rule for complex numbers
        karma::rule<OITER,value()>  value_rule; 

        //!
        //! \brief default constructor
        //! 
        //! Default constructor for the complex number rule. 
        //!
        value_generator(): value_generator::base_type(value_rule)
        {
            using karma::_1;
            using karma::_val;

            value_rule = karma::string[_1 = to_string(_val)];
        }
        
    };

}
}
