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
    
    using namespace pni::core;
    namespace mpl = boost::mpl;
    using namespace boost::spirit;
    
    //
    // First we need a unified template interface for all generator templates.
    // The first template argument should be the interator and the second
    // the attribute type.
    //
    template<typename ITERT,typename T>
    using pni_io_uint_generator = karma::uint_generator<T>;
    
    template<typename ITERT,typename T>
    using pni_io_int_generator  = karma::int_generator<T>;
    
    template<typename ITERT,typename T>
    using pni_io_real_generator = karma::real_generator<T,float_policy<T>>;

    template<typename ITERT,typename T>
    using pni_io_complex_generator = complex_generator<ITERT,T>;
    
    template<typename ITERT,typename T>
    using pni_io_bool_generator = karma::bool_generator<T>;
    
    template<typename ITERT>
    using primitive_generators = 
    mpl::map<
        mpl::pair<uint8, pni_io_uint_generator<ITERT,uint8>>,
        mpl::pair<uint16,pni_io_uint_generator<ITERT,uint16>>,
        mpl::pair<uint32,pni_io_uint_generator<ITERT,uint32>>,
        mpl::pair<uint64,pni_io_uint_generator<ITERT,uint64>>,
        mpl::pair<int8, pni_io_int_generator<ITERT,int8>>,
        mpl::pair<int16,pni_io_int_generator<ITERT,int16>>,
        mpl::pair<int32,pni_io_int_generator<ITERT,int32>>,
        mpl::pair<int64,pni_io_int_generator<ITERT,int64>>,
        mpl::pair<float32,pni_io_real_generator<ITERT,float32>>,
        mpl::pair<float64,pni_io_real_generator<ITERT,float64>>,
        mpl::pair<float128,pni_io_real_generator<ITERT,float128>>,        
        mpl::pair<bool_t,pni_io_bool_generator<ITERT,bool_t>>,
        mpl::pair<complex32,pni_io_complex_generator<ITERT,float32>>,
        mpl::pair<complex64,pni_io_complex_generator<ITERT,float64>>,
        mpl::pair<complex128,pni_io_complex_generator<ITERT,float128>>
    >;
    

    
    

//end of namespace
}
}
