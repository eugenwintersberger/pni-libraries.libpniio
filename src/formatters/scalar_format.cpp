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

#include <pni/io/formatters/scalar_format.hpp>
#include <pni/io/formatters/formatter.hpp>

namespace pni{
namespace io{
    using namespace pni::core;

#define SCALAR_FORMAT_FUNCTION(type) \
    string format(type v)\
    {\
        formatter<type> f; \
        return f(v); \
    }

    //-------------------------------------------------------------------------
    SCALAR_FORMAT_FUNCTION(uint8)
    SCALAR_FORMAT_FUNCTION(int8)
    SCALAR_FORMAT_FUNCTION(uint16) 
    SCALAR_FORMAT_FUNCTION(int16)
    SCALAR_FORMAT_FUNCTION(uint32)
    SCALAR_FORMAT_FUNCTION(int32)
    SCALAR_FORMAT_FUNCTION(uint64)
    SCALAR_FORMAT_FUNCTION(int64)

    SCALAR_FORMAT_FUNCTION(float32)
    SCALAR_FORMAT_FUNCTION(float64) 
    SCALAR_FORMAT_FUNCTION(float128)
    
    SCALAR_FORMAT_FUNCTION(complex32)
    SCALAR_FORMAT_FUNCTION(complex64)
    SCALAR_FORMAT_FUNCTION(complex128)

    SCALAR_FORMAT_FUNCTION(bool_t)

    //-------------------------------------------------------------------------
    string format(const string &s)
    {
        formatter<string> f;
        return f(s);
    }

    //-------------------------------------------------------------------------
    string format(const value &v)
    {
        formatter<value> f;
        return f(v);
    }

    //-------------------------------------------------------------------------
    string format(const value_ref &v)
    {
        formatter<value_ref> f;
        return f(v);
    }

//end of namespace
}
}
