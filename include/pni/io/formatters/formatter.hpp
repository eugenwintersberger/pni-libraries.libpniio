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

#include <vector>
#include <iterator>
#include <pni/core/types.hpp>
#include <pni/core/type_erasures.hpp>
#include <boost/spirit/include/karma.hpp>

#include "../container_io_config.hpp"
#include "get_generator.hpp"
#include "spirit_container_traits.hpp"

namespace pni{
namespace io{

    using namespace pni;
    using namespace boost::spirit;

    //!
    //! \ingroup formatter_classes
    //! \brief scalar formatter
    //! 
    //! This is the default implementation of a formatter. It is intended to 
    //! be used with scalar and complex primitive types. 
    //! 
    //! \tparam T primitive type
    template<typename T> 
    class formatter
    {
        private: 
            //! output iterator type
            typedef std::back_insert_iterator<core::string> iterator_type;
            //! generator type
            typedef typename get_generator<iterator_type,T>::type generator_type; 
            
            //! generator instance
            generator_type generator;
    
        public:

            //!
            //! \brief generate output
            //! 
            //! Take the input value and convert it to its string 
            //! representation.
            //! 
            //! \param value a value of type T
            //! \return string representation of value
            //! 
            core::string operator()(const T &v) const
            {
                core::string buffer;
                iterator_type inserter(buffer);

                karma::generate(inserter,generator,v);

                return buffer;
            }            
    };
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief formatter for strings
    //! 
    //! A specialization of the formatter template for scalar values for 
    //! strings. In fact this formatter does nothing else than passing 
    //! the string through to output. 
    //!
    template<> class formatter<core::string>
    {
        public:
            core::string operator()(const core::string &v) const
            {
                return v;
            }
    };    
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief formatter for value_ref type erasure
    //! 
    //! A specialization of the formatter template for scalar values for the 
    //! value_ref type erasure.
    //!
    template<> class formatter<core::value_ref>
    {
        public:
            core::string operator()(const core::value_ref &v) const
            {
                return formatter<core::value>()(core::to_value(v));
            }
    };
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief formatter for containers
    //! 
    //! Most of the container formatters are using this code. Do not 
    //! instantiate this template class by yourself. This will be done by the 
    //! specializations of the formatter template for the various container 
    //! types. 
    //! 
    //! \tparam CTYPE container type
    //! 
    template<typename CTYPE>
    class container_formatter
    {
        private:
            typedef CTYPE container_type;
            //! output iterator type
            typedef std::back_insert_iterator<core::string> iterator_type;
            //! element type of the container
            typedef typename container_type::value_type value_type;
            //! generator type
            typedef get_generator<iterator_type,value_type> getter_type;
            typedef typename getter_type::type generator_type; 
            //! generator instance
            generator_type generator;
        public:
            //! 
            //! \brief generate output
            //! 
            //! Take the input vector and return its string representation. 
            //!
            //! \param v input container
            //! \param config output configuration for the container
            //! \return string representation of the input vector
            //! 
            core::string operator()(const container_type &v,
                                    const container_io_config config = 
                                    container_io_config()) const
            {
                core::string buffer;
                iterator_type inserter(buffer);                
                
                auto sep_rule  = karma::char_(config.seperator());                
                auto cont_rule = generator % sep_rule;
                
                if(config.start_symbol() && config.stop_symbol())
                {                                   
                    karma::generate(inserter,config.start_symbol()<<
                                             cont_rule<<
                                             config.stop_symbol(),v);
                }
                else
                {
                    karma::generate(inserter,cont_rule,v);   
                }                    
               
                return buffer;
            }                
    };
    
    
    //------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief vector formatter
    //!
    //! Specialization of the default formatter for vectors.  The elements of
    //! the vector must be of a primitive type.
    //!
    //! \tparam T element type of the vector
    //!
    template<typename T> 
    class formatter<std::vector<T>>
    {
        private:
            typedef container_formatter<std::vector<T>> formatter_type;
            formatter_type f;

        public:           

            //! 
            //! \brief generate output
            //! 
            //! Take the input vector and return its string representation. 
            //!
            //! \param v input vector
            //! \return string representation of the input vector
            //! 
            core::string operator()(const std::vector<T> &v,
                                    const container_io_config config = 
                                    container_io_config()) const
            {
                return f(v,config);
            }
    };
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief formatter for the array type erasure
    //! 
    //! This is a specialization of the formatter template for instances of the 
    //! array type erasure. 
    //! 
    template<>
    class formatter<core::array>
    {
        private:
            typedef std::vector<core::value> container_type;
            typedef container_formatter<container_type> formatter_type;
            formatter_type f;           
            
        public:            
            
            //-----------------------------------------------------------------
            core::string operator()(const core::array &v,
                                    const container_io_config &config = 
                                          container_io_config()) const
            {
                //there seems to be a crucial problem with the array iterator
                //have not figured this out yet. However, we should use it 
                //with care!
                container_type c(v.size());
                std::copy(v.begin(),v.end(),c.begin());
                return f(c,config);
            }
            
    };
    
    //-------------------------------------------------------------------------
    //! 
    //! \ingroup formatter_classes
    //! \brief formatter for mdarray instances
    //! 
    //! Specialization of the formatter template for instances of the mdarray
    //! template. 
    //! 
    //! \tparam OTYPES template parameters for mdarray
    //! 
    template<typename ...OTYPES>
    class formatter<mdarray<OTYPES...>>
    {
        private:
            typedef mdarray<OTYPES...> container_type;      
            typedef container_formatter<container_type> formatter_type;
            formatter_type f;

        public:           

            //! 
            //! \brief generate output
            //! 
            //! Take the input vector and return its string representation. 
            //!
            //! \param v input vector
            //! \return string representation of the input vector
            //! 
            core::string operator()(const mdarray<OTYPES...> &v,
                                    const container_io_config config = 
                                    container_io_config()) const                                    
            {          
                return f(v,config);
            }
        
    };
    
    //-------------------------------------------------------------------------
    //! 
    //! \ingroup formatter_classes
    //! \brief formatter for a string vector
    //! 
    //! Specialization of the formatter template for a vector of strings. 
    //! 
    template<> 
    class formatter<std::vector<core::string>>
    {
        private:
            //! output iterator type
            typedef std::back_insert_iterator<core::string> iterator_type;           
        public:

            //! 
            //! \brief generate output
            //! 
            //! Take the input vector and return its string representation. 
            //!
            //! \param v input vector
            //! \return string representation of the input vector
            //! 
            core::string operator()(const std::vector<core::string> &v) const
            {
                core::string buffer;
                iterator_type inserter(buffer);

                karma::generate(inserter,karma::string % '\n',v);

                return buffer;
            }
    };
    
    

//end of namespace
}
}
