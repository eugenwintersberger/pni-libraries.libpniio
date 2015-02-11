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

#include <pni/core/types.hpp>
#include <boost/spirit/include/karma.hpp>

#include "float_policy.hpp"
#include "complex_generator.hpp"

namespace pni{
namespace io{
    
    using namespace pni::core;
    using namespace boost::spirit;

    //!
    //! \ingroup formatter_classes
    //! \brief get generator for type
    //!
    //! Template to obtain the appropriate generator for a particular type. 
    //!
    //! \tparam ITERT iterator type
    //! \tparam T data type for output
    //!
    template<typename ITERT, typename T> struct get_generator;

    //------------------------------------------------------------------------
    template<typename ITERT> struct get_generator<ITERT,uint8>
    {
        typedef karma::uint_generator<uint8> type;
    };

    //------------------------------------------------------------------------
    template<typename ITERT> struct get_generator<ITERT,uint16>
    {
        typedef karma::uint_generator<uint16> type;
    };

    //------------------------------------------------------------------------
    template<typename ITERT> struct get_generator<ITERT,float32>
    {
        typedef karma::real_generator<float32,float_policy<float32>> type;
    };
    
    //------------------------------------------------------------------------
    template<typename ITERT> struct get_generator<ITERT,float64>
    {
        typedef karma::real_generator<float64,float_policy<float64>> type;
    };

    //------------------------------------------------------------------------
    template<typename ITERT> struct get_generator<ITERT,float128>
    {
        typedef karma::real_generator<float128,float_policy<float128>> type;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief get generator for complex numbers
    //!
    //! Provides the generator for complex types 
    //! 
    //! \tparam ITERT iterator type
    //! \tparma T base type of the complex number
    template<
             typename ITERT,
             typename T
            >
    struct get_generator<ITERT,std::complex<T>>
    {
        typedef complex_generator<ITERT,T> type;
    };

//end of namespace
}
}
