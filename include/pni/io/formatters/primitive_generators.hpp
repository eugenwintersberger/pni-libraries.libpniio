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
// Created on: Apr 27, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <pni/core/types.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/mpl/map.hpp>

#include "float_policy.hpp"
#include "complex_generator.hpp"

namespace pni{
namespace io{
    
    //
    // First we need a unified template interface for all generator templates.
    // The first template argument should be the interator and the second
    // the attribute type.
    //
    template<typename ITERT,typename T>
    using pni_io_uint_generator = boost::spirit::karma::uint_generator<T>;
    
    template<typename ITERT,typename T>
    using pni_io_int_generator  = boost::spirit::karma::int_generator<T>;
    
    template<typename ITERT,typename T>
    using pni_io_real_generator = boost::spirit::karma::real_generator<T,float_policy<T>>;

    template<typename ITERT,typename T>
    using pni_io_complex_generator = complex_generator<ITERT,T>;
    
    template<typename ITERT,typename T>
    using pni_io_bool_generator = boost::spirit::karma::bool_generator<T>;
    
    template<typename ITERT>
    using primitive_generators = 
    boost::mpl::map<
        boost::mpl::pair<pni::core::uint8, 
                         pni_io_uint_generator<ITERT,pni::core::uint8>>,
        boost::mpl::pair<pni::core::uint16,
                         pni_io_uint_generator<ITERT,pni::core::uint16>>,
        boost::mpl::pair<pni::core::uint32,
                         pni_io_uint_generator<ITERT,pni::core::uint32>>,
        boost::mpl::pair<pni::core::uint64,
                         pni_io_uint_generator<ITERT,pni::core::uint64>>,
        boost::mpl::pair<pni::core::int8, 
                         pni_io_int_generator<ITERT,pni::core::int8>>,
        boost::mpl::pair<pni::core::int16,
                         pni_io_int_generator<ITERT,pni::core::int16>>,
        boost::mpl::pair<pni::core::int32,
                         pni_io_int_generator<ITERT,pni::core::int32>>,
        boost::mpl::pair<pni::core::int64,
                         pni_io_int_generator<ITERT,pni::core::int64>>,
        boost::mpl::pair<pni::core::float32,
                         pni_io_real_generator<ITERT,pni::core::float32>>,
        boost::mpl::pair<pni::core::float64,
                         pni_io_real_generator<ITERT,pni::core::float64>>,
        boost::mpl::pair<pni::core::float128,
                         pni_io_real_generator<ITERT,pni::core::float128>>,        
        boost::mpl::pair<pni::core::bool_t,
                         pni_io_bool_generator<ITERT,pni::core::bool_t>>,
        boost::mpl::pair<pni::core::complex32,
                         pni_io_complex_generator<ITERT,pni::core::float32>>,
        boost::mpl::pair<pni::core::complex64,
                         pni_io_complex_generator<ITERT,pni::core::float64>>,
        boost::mpl::pair<pni::core::complex128,
                         pni_io_complex_generator<ITERT,pni::core::float128>>
    >;

//end of namespace
}
}
