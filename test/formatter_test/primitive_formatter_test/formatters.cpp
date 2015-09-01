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
//  Created on: Sep 01, 2015
//      Author: Eugen Wintersberger
//

#include "formatters.hpp"
#include <pni/io/formatters/formatter.hpp>

using namespace pni::io;
using namespace pni::core;

typedef formatter<uint8>  uint8_formatter;
typedef formatter<int8>   int8_formatter;
typedef formatter<uint16> uint16_formatter;
typedef formatter<int16>  int16_formatter;
typedef formatter<uint32> uint32_formatter;
typedef formatter<int32>  int32_formatter;
typedef formatter<uint64> uint64_formatter;
typedef formatter<int64>  int64_formatter;

typedef formatter<float32>  float32_formatter;
typedef formatter<float64>  float64_formatter;
typedef formatter<float128> float128_formatter;

typedef formatter<complex32>  complex32_formatter;
typedef formatter<complex64>  complex64_formatter;
typedef formatter<complex128> complex128_formatter;

typedef formatter<string> string_formatter;
typedef formatter<bool_t> bool_formatter;
typedef formatter<value> value_formatter;

string format(uint8 v)
{
    uint8_formatter f;
    return f(v);
}

string format(int8 v)
{
    int8_formatter f;
    return f(v);
}

string format(uint16 v)
{
    uint16_formatter f;
    return f(v);
}

string format(int16 v)
{
    int16_formatter f;
    return f(v);
}

string format(uint32 v)
{
    uint32_formatter f;
    return f(v);
}

string format(int32 v)
{
    int32_formatter f;
    return f(v);
}

string format(uint64 v)
{
    uint64_formatter f;
    return f(v);
}

string format(int64 v)
{
    int64_formatter f;
    return f(v);
}

string format(float32 v)
{
    float32_formatter f;
    return f(v);
}

string format(float64 v)
{
    float64_formatter f;
    return f(v);
}

string format(float128 v)
{
    float128_formatter f;
    return f(v);
}

string format(complex32 v)
{
    complex32_formatter f;
    return f(v);
}

string format(complex64 v)
{
    complex64_formatter f;
    return f(v);
}

string format(complex128 v)
{
    complex128_formatter f;
    return f(v);
}

string format(bool_t v)
{
    bool_formatter f;
    return f(v);
}

string format(value v)
{
    value_formatter f;
    return f(v);
}
