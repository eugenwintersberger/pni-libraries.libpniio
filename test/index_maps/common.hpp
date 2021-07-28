//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pninexus.
//
// pninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
//  Created on: Oct 25, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <vector>
#include <list>
#include <pni/arrays/slice.hpp>

typedef std::vector<size_t> vector_index_type;
typedef std::list<size_t>   list_index_type;
typedef std::vector<pni::slice> slice_vector;


template<
         typename MAPT,
         typename INDEXT
        >
struct offset_arg
    {
        MAPT map;
        INDEXT index;
        size_t expected_offset;
    };

template<
         typename MAPT,
         typename INDEXT
        >
struct selection_offset_arg
{
    slice_vector slices;
    MAPT map;
    INDEXT sel_index;
    size_t expected_offset;
};
