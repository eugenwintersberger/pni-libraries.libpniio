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

#include<pni/core/types.hpp>
#include<pni/core/type_erasures.hpp>
#include<vector>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include "complex_rule.hpp"
#include "value_rule.hpp"

namespace pni{
namespace io{

    template<
             typename ITERT,
             typename T
            >
    struct element_rule_type
    {
        typedef typename  mpl::at<spirit_rules,T>::type type;
    };

    //------------------------------------------------------------------------
    template<
             typename ITERT,
             typename T
            >
    struct element_rule_type<ITERT,std::complex<T>>
    {
        typedef complex_rule<ITERT,T> type;
    };


    //------------------------------------------------------------------------
    template<typename ITERT>
    struct element_rule_type<ITERT,pni::core::value>
    {
        typedef value_rule<ITERT> type;
    };

//end of namespace
}
}
