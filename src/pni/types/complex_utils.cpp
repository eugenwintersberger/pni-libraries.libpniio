//!
//! (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of libpnicore.
//!
//! libpnicore is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! libpnicore is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//!
//! ===========================================================================
//!
//! Created on: Sep 9, 2011
//!     Author: Eugen Wintersberger
//!
//!/

#include <pni/types/complex_utils.hpp>
#include <pni/types/convert.hpp>

namespace pni{
namespace core{

    //-------------------------------------------------------------------------
    bool operator==(const complex32 &a,const complex64 &b)
    {
        auto _a = convert<complex64>(a);

        return (_a == b);
    }

    //-------------------------------------------------------------------------
    bool operator==(const complex32 &a,const complex128 &b)
    {
        auto _a = convert<complex128>(a);

        return (_a == b);
    }

    //-------------------------------------------------------------------------
    bool operator==(const complex64 &a,const complex32 &b)
    {
        auto _b = convert<complex64>(b);
        return (a == _b);
    }

    //-------------------------------------------------------------------------
    bool operator==(const complex64 &a,const complex128 &b)
    {
        auto _a = convert<complex128>(a);
        return(_a == b);
    }

    //-------------------------------------------------------------------------
    bool operator==(const complex128 &a,const complex32 &b)
    {
        auto _b = convert<complex128>(b);
        return(_b == a);
    }

    //-------------------------------------------------------------------------
    bool operator==(const complex128 &a,const complex64 &b)
    {
        auto _b = convert<complex128>(b);
        return(_b == a);
    }

    //-------------------------------------------------------------------------
    bool operator!=(const complex32 &a,const complex64 &b)
    {
        if(a == b) return false;
        return true;
    }

    //-------------------------------------------------------------------------
    bool operator!=(const complex32 &a,const complex128 &b)
    {
        if(a==b) return false;
        return true;
    }

    //-------------------------------------------------------------------------
    bool operator!=(const complex64 &a,const complex32 &b)
    {
        if(a==b) return false;
        return true;
    }

    //-------------------------------------------------------------------------
    bool operator!=(const complex64 &a,const complex128 &b)
    {
        if(a==b) return false;
        return true;
    }

    //-------------------------------------------------------------------------
    bool operator!=(const complex128 &a,const complex32 &b)
    {
        if(a==b) return false;
        return true;
    }

    //-------------------------------------------------------------------------
    bool operator!=(const complex128 &a,const complex64 &b)
    {
        if(a==b) return false;
        return true;
    }
}
}




