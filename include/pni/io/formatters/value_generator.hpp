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
#ifdef _MSC_VER
#pragma warning(disable:4348)
#endif
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>
#ifdef _MSC_VER
#pragma warning(default:4348)
#endif
#include <boost/mpl/map.hpp>

#include "primitive_generators.hpp"

namespace pni{
namespace io{


    //!
    //! \ingroup formatter_internal_classes
    //! \brief generator for scalar type erasures 
    //!
    //! This struct implements a generator for the scalar type earsure 
    //! types provided by `libpnicore`: `pni::core::value` and 
    //! `pni::core::value_ref`. 
    //!
    //! \tparam OITER output iterator
    //! \tparam VTYPE scalar type erasure type
    //! 
    template<
             typename OITER,       
             typename VTYPE
            >
    struct value_generator : boost::spirit::karma::grammar<OITER,VTYPE()>
    {
        //!
        //! \brief convert value type to a string 
        //! 
        //! This lazy function converts a value type (``value`` or
        //! ``value_ref`` to a string. This conversion is done in a two 
        //! step process 
        //! 
        //! * first the data type of the data stored in the type erasure is 
        //!   determined 
        //! * a primitive generator for that particular type is selected 
        //!   and applied on the stored data which is extracted using the 
        //!   ``as<T>`` member template of the value type. 
        //! 
        //! 
        struct lazy_to_string
        {
            typedef std::back_insert_iterator<pni::core::string> iterator_type;
            typedef primitive_generators<iterator_type> generator_map;

            //!
            //! \brief result type of the lazy function
            //! 
            template<typename Sig> struct result
            {
                typedef pni::core::string type; //!< result type
            };
           
            //!
            //! \brief typed string conversion
            //! 
            //! This static member function implements the string conversion 
            //! for a particular type. It selects the appropriate primitive
            //! generator according to its template parameter T and performs
            //! the formatting. 
            //!
            //! \tparam T the stored data type 
            //! \param v reference to the type erasure object
            //! \return string with the result of the conversion
            //! 
            template<typename T>
            static pni::core::string _to_string(const VTYPE &v)
            {
                typedef boost::mpl::at<generator_map,T> at_type;
                typedef typename at_type::type generator_type;                
                
                pni::core::string formatter_result;
                iterator_type inserter(formatter_result);
                
                boost::spirit::karma::generate(inserter,
                                               generator_type(),
                                               v.template as<T>());
                
                return formatter_result;
            }

            //!
            //! \brief get real part
            //!
            //! This function template actually implements the extraction of 
            //! the real part from a complex number.
            //! 
            //! \throws value_error if the type erasure is not initialized 
            //! \throws type_error if the type erasure stores an object of an
            //!                    unkown type
            //! 
            //! \tparam Arg argument type (`value` or `value_ref`)
            //! \param n reference to the scalar type erasure
            //! \return string representation of the type erasures data
            //!
            template<typename Arg>
            pni::core::string operator()(const Arg &n) const
            {
                using namespace pni::core;

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
                    case type_id_t::NONE:
                        return "NONE";
                        throw value_error(EXCEPTION_RECORD,
                            "Passed an uninitialized value!");
                    default:
                        throw type_error(EXCEPTION_RECORD,
                            "The value instances holds an unkown type!");
                    
                }                
            }
        };
        

        //-------------------------------------------------------------------
        //! instance of the get_real lazy function
        boost::phoenix::function<lazy_to_string> to_string;      
       
        //! total rule for complex numbers
        boost::spirit::karma::rule<OITER,VTYPE()>  value_rule; 

        //!
        //! \brief default constructor
        //! 
        //! Default constructor for the complex number rule. 
        //!
        value_generator(): value_generator::base_type(value_rule)
        {
            using boost::spirit::karma::_1;
            using boost::spirit::karma::_val;

            value_rule = boost::spirit::karma::string[_1 = to_string(_val)];
        }
        
    };

}
}
