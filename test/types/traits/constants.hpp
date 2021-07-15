//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jan 7, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include <vector>
#include <pni/types.hpp>

typedef std::vector<pni::type_id_t> id_vector_type;

static const id_vector_type integer_ids = { pni::type_id_t::UINT8,
                                            pni::type_id_t::INT8,
                                            pni::type_id_t::UINT16,
                                            pni::type_id_t::INT16,
                                            pni::type_id_t::UINT32,
                                            pni::type_id_t::INT32,
                                            pni::type_id_t::UINT64,
                                            pni::type_id_t::INT64};

static const id_vector_type float_ids = {pni::type_id_t::FLOAT32,
                                         pni::type_id_t::FLOAT64,
                                         pni::type_id_t::FLOAT128};

static const id_vector_type complex_ids = {pni::type_id_t::COMPLEX32,
                                           pni::type_id_t::COMPLEX64,
                                           pni::type_id_t::COMPLEX128};

static const id_vector_type non_numeric_ids = {pni::type_id_t::STRING,
                                               pni::type_id_t::NONE,
                                               pni::type_id_t::BINARY,
                                               pni::type_id_t::BOOL};
