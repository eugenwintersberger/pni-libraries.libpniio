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
// Created on: Jan 20, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include "complex_rule.hpp"
#include "value_rule.hpp"
#include "slice_rule.hpp"

namespace pni{
namespace io{

    //!
    //! \ingroup parser_classes
    //! \brief obtain rule type
    //! 
    //! This template provides the appropriate rule to parse a value of a 
    //! given data type T. This rule may also depends on the iterator type
    //! which is passed as the first template parameters.
    //!
    //! \tparam ITERT iterator type
    //! \tparam T data type for which to select the parsing rule
    //!
    template<
             typename ITERT,
             typename T
            >
    struct get_rule_type
    {
        //! parsing rule for T 
        typedef typename  boost::mpl::at<spirit_rules,T>::type type;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup parser_classes
    //! \brief obtain rule for complex numbers
    //!
    //! This specialization of the get_rule_type template for complex number
    //! types. 
    //!
    //! \tparam ITERT iterator type
    //! \tparam T base type for the complex type
    //!
    template<
             typename ITERT,
             typename T
            >
    struct get_rule_type<ITERT,std::complex<T>>
    {
        //! parsing rule for the complex type
        typedef complex_rule<ITERT,std::complex<T>> type;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup parser_classes
    //! \brief obtain rule for parsing values
    //!
    //! This specialization provides the rule type for parsing value instances.
    //! 
    //! \tparam ITERT iterator type
    //! 
    template<typename ITERT>
    struct get_rule_type<ITERT,pni::core::value>
    {
        //! rule type for parsing value type erasures
        typedef value_rule<ITERT> type;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup parser_classes
    //! \brief obtain rule for parsing slices
    //! 
    //! This specialization provides the rule type for parsing slices. 
    //! 
    //! \tparam ITERT iterator type
    //! 
    template<typename ITERT>
    struct get_rule_type<ITERT,pni::core::slice>
    {
        //! rule type for parsing a slice
        typedef slice_rule<ITERT> type;
    };

//end of namespace
}
}
