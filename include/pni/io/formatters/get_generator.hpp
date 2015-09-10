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

#include "primitive_generators.hpp"
#include "value_generator.hpp"

namespace pni{
namespace io{
    
    //!
    //! \ingroup formatter_internal_classes
    //! \brief get generator for type
    //!
    //! Template to obtain the appropriate generator for a particular type. 
    //!
    //! \tparam ITERT iterator type
    //! \tparam T data type for output
    //!
    template<typename ITERT, typename T> struct get_generator
    {
        //! generator type
        typedef typename boost::mpl::at<primitive_generators<ITERT>,T>::type type;
    };

    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup formatter_internal_classes
    //! \brief get generator for value
    //! 
    //! Get a generator for a value type erasure. 
    //! 
    template<typename ITERT> struct get_generator<ITERT,pni::core::value>
    {
        //! generator type
        typedef value_generator<ITERT,pni::core::value> type;
    };
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup formatter_internal_classes
    //! \brief get generator for value_ref
    //! 
    //! Get a generator for the value_ref type erasure.
    //!
    template<typename ITERT> struct get_generator<ITERT,pni::core::value_ref>
    {
        //! generator type
        typedef value_generator<ITERT,pni::core::value_ref> type;
    };
   
    

//end of namespace
}
}
