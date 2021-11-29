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

static const id_vector_type integer_ids = { pni::type_id_t::UInt8,
                                            pni::type_id_t::Int8,
                                            pni::type_id_t::UInt16,
                                            pni::type_id_t::Int16,
                                            pni::type_id_t::UInt32,
                                            pni::type_id_t::Int32,
                                            pni::type_id_t::UInt64,
                                            pni::type_id_t::Int64};

static const id_vector_type float_ids = {pni::type_id_t::Float32,
                                         pni::type_id_t::Float64,
                                         pni::type_id_t::Float128};

static const id_vector_type complex_ids = {pni::type_id_t::Complex32,
                                           pni::type_id_t::Complex64,
                                           pni::type_id_t::Complex128};

static const id_vector_type non_numeric_ids = {pni::type_id_t::String,
                                               pni::type_id_t::None,
                                               pni::type_id_t::Binary,
                                               pni::type_id_t::Bool};
