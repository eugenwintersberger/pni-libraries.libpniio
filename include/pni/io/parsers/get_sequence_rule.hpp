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
// Created on: Feb 2, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include "sequence_rule.hpp"
#include "string_sequence_rule.hpp"


namespace pni{
namespace io{


    template<
             typename ITERT,
             typename ST,
             bool     has_string = std::is_same<
                 typename ST::value_type,core::string>::value
            >
    struct get_sequence_rule
    {
        typedef sequence_rule<ITERT,ST> type;
    };


    template<
             typename ITERT,
             typename ST
            >
    struct get_sequence_rule<ITERT,ST,true>
    {
        typedef string_sequence_rule<ITERT,ST> type;
    };

//end of namespace
}
}
