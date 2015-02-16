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
    // GENERATORS FOR UNSIGNED INTEGER TYPES
    //------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief get generator for uint8
    //!
    template<typename ITERT> struct get_generator<ITERT,uint8>
    {
        //! generator type
        typedef karma::uint_generator<uint8> type;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief get generator for uint16
    //!
    template<typename ITERT> struct get_generator<ITERT,uint16>
    {
        //! generator type
        typedef karma::uint_generator<uint16> type;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief get generator for uint32
    //!
    template<typename ITERT> struct get_generator<ITERT,uint32>
    {
        //! generator type
        typedef karma::uint_generator<uint32> type;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief get generator for uint64
    //!
    template<typename ITERT> struct get_generator<ITERT,uint64>
    {
        //! generator type
        typedef karma::uint_generator<uint64> type;
    };
    //------------------------------------------------------------------------
    // GENERATORS FOR SIGNED INTEGER TYPES
    //------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief get generator for uint8
    //!
    template<typename ITERT> struct get_generator<ITERT,int8>
    {
        //! generator type
        typedef karma::int_generator<int8> type;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief get generator for int16
    //!
    template<typename ITERT> struct get_generator<ITERT,int16>
    {
        //! generator type
        typedef karma::int_generator<int16> type;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief get generator for int32
    //!
    template<typename ITERT> struct get_generator<ITERT,int32>
    {
        //! generator type
        typedef karma::int_generator<int32> type;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief get generator for int64
    //!
    template<typename ITERT> struct get_generator<ITERT,int64>
    {
        //! generator type
        typedef karma::int_generator<int64> type;
    };

    //------------------------------------------------------------------------
    // GENERATORS FOR FLOATING POINT TYPES
    //------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief get generator for float32
    //!
    template<typename ITERT> struct get_generator<ITERT,float32>
    {
        //! generator type
        typedef karma::real_generator<float32,float_policy<float32>> type;
    };
    
    //------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief get generator for float64
    //!
    template<typename ITERT> struct get_generator<ITERT,float64>
    {
        //! generator type
        typedef karma::real_generator<float64,float_policy<float64>> type;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief get generator for float128
    //!
    template<typename ITERT> struct get_generator<ITERT,float128>
    {
        //! generator type
        typedef karma::real_generator<float128,float_policy<float128>> type;
    };

    //------------------------------------------------------------------------
    // GENERATORS FOR COMPLEX FLOATING POINT TYPES
    //------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief get generator for complex numbers
    //!
    //! Provides the generator for complex types 
    //! 
    //! \tparam ITERT iterator type
    //! \tparam T base type of the complex number
    template<
             typename ITERT,
             typename T
            >
    struct get_generator<ITERT,std::complex<T>>
    {
        //! generator type
        typedef complex_generator<ITERT,T> type;
    };

    //-------------------------------------------------------------------------
    // GENERATORS FOR BOOLEAN VALUES
    //-------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief get generator for bool_t
    //!
    template<typename ITERT> struct get_generator<ITERT,bool_t>
    {
        //! generator type
        typedef karma::bool_generator<bool> type;
    };

//end of namespace
}
}
