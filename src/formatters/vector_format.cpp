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
// Created on: Sep 08, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//

#include <pni/io/formatters/vector_format.hpp>
#include <pni/io/formatters/formatter.hpp>

namespace pni{
namespace io{

    using namespace pni::core;

#define DEFINE_VECTOR_FORMAT(type)\
    string format(const std::vector<type> &v,\
                  const container_io_config &config) \
    {\
        formatter<std::vector<type>> f; \
        return f(v,config);  \
    }

    DEFINE_VECTOR_FORMAT(pni::core::uint8)
    DEFINE_VECTOR_FORMAT(pni::core::int8)
    DEFINE_VECTOR_FORMAT(pni::core::uint16)
    DEFINE_VECTOR_FORMAT(pni::core::int16)
    DEFINE_VECTOR_FORMAT(pni::core::uint32)
    DEFINE_VECTOR_FORMAT(pni::core::int32)
    DEFINE_VECTOR_FORMAT(pni::core::uint64)
    DEFINE_VECTOR_FORMAT(pni::core::int64)

    DEFINE_VECTOR_FORMAT(pni::core::float32)
    DEFINE_VECTOR_FORMAT(pni::core::float64)
    DEFINE_VECTOR_FORMAT(pni::core::float128)
    
    DEFINE_VECTOR_FORMAT(pni::core::complex32)
    DEFINE_VECTOR_FORMAT(pni::core::complex64)
    DEFINE_VECTOR_FORMAT(pni::core::complex128)

    DEFINE_VECTOR_FORMAT(pni::core::bool_t)

    DEFINE_VECTOR_FORMAT(pni::core::value)

}
}
