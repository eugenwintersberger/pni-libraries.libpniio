//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Sep 08, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//

#include <pni/formatters/scalar_format.hpp>
#include <boost/format.hpp>

namespace pni{
    using namespace pni;

#define SCALAR_FORMAT_FUNCTION(type) \
    string format(type v)\
    {\
        return ""; \
    }

    //=========================================================================
    string format(const uint8 &v)
    {
        boost::format fmt("%|+|");
        fmt % uint16(v);

        return fmt.str();
    }

    //=========================================================================
    string format(const int8 &v)
    {
        boost::format fmt("%|+|");
        fmt % int16(v);
        return fmt.str();
    }

    //=========================================================================
    string format(const uint16 &v)
    {
        boost::format fmt("%|+|");
        fmt % v;
        return fmt.str();
    }

    //=========================================================================
    string format(const int16 &v)
    {
        boost::format fmt("%|+|");
        fmt %v;
        return fmt.str();
    }

    //=========================================================================
    string format(const uint32 &v)
    {
        boost::format fmt("%|+|");
        fmt %v;
        return fmt.str();
    }

    //=========================================================================
    string format(const int32 &v)
    {
        boost::format fmt("%|+|");
        fmt %v;
        return fmt.str();
    }

    string format(const uint64 &v)
    {
        boost::format fmt("%|+|");
        fmt %v;
        return fmt.str();
    }

    string format(const int64 &v)
    {
        boost::format fmt("%|+|");
        fmt %v;
        return fmt.str();
    }

    string format(const float32 &v)
    {
        boost::format fmt("%|+.9e|");
        fmt %v;
        return fmt.str();
    }
    string format(const float64 &v)
    {
        boost::format fmt("%|+.17e|");
        fmt %v;
        return fmt.str();
    }

    string format(const float128 &v)
    {
        boost::format fmt("%|+.17e|");
        fmt %v;
        return fmt.str();
    }

    string format(const complex32 &v)
    {
        boost::format fmt_p("%|+.9e|+I%|.9e|");
        boost::format fmt_m("%|+.9e|-I%|.9e|");

        if(v.imag()<0)
        {
            fmt_m %v.real() %(-1.*v.imag());
            return fmt_m.str();
        }
        else
        {
            fmt_p %v.real() %v.imag();
            return fmt_p.str();
        }

    }
    string format(const complex64 &v)
    {
        boost::format fmt_p("%|+.17e|+I%|.17e|");
        boost::format fmt_m("%|+.17e|-I%|.17e|");

        if(v.imag()<0)
        {
            fmt_m %v.real() %(-1.*v.imag());
            return fmt_m.str();
        }
        else
        {
            fmt_p %v.real() %v.imag();
            return fmt_p.str();
        }
    }

    string format(const complex128 &v)
    {
        boost::format fmt_p("%|+.17e|+I%|.17e|");
        boost::format fmt_m("%|+.17e|-I%|.17e|");

        if(v.imag()<0)
        {
            fmt_m %v.real() %(-1.*v.imag());
            return fmt_m.str();
        }
        else
        {
            fmt_p %v.real() %v.imag();
            return fmt_p.str();
        }
    }

    string format(const bool_t &v)
    {
        if(v)
            return "true";
        else
            return "false";
    }

    //-------------------------------------------------------------------------
    string format(const string &s)
    {
        return s;
    }

    //-------------------------------------------------------------------------
    string format(const value &v)
    {
        switch(v.type_id())
        {
            case type_id_t::UINT8:
                return format(v.as<uint8>());
            case type_id_t::INT8:
                return format(v.as<int8>());
            case type_id_t::INT16:
                return format(v.as<int16>());
            case type_id_t::UINT16:
                return format(v.as<uint16>());
            case type_id_t::UINT32:
                return format(v.as<uint32>());
            case type_id_t::INT32:
                return format(v.as<int32>());
            case type_id_t::UINT64:
                return format(v.as<uint64>());
            case type_id_t::INT64:
                return format(v.as<int64>());
            case type_id_t::FLOAT32:
                return format(v.as<float32>());
            case type_id_t::FLOAT64:
                return format(v.as<float64>());
            case type_id_t::FLOAT128:
                return format(v.as<float128>());
            case type_id_t::COMPLEX32:
                return format(v.as<complex32>());
            case type_id_t::COMPLEX64:
                return format(v.as<complex64>());
            case type_id_t::COMPLEX128:
                return format(v.as<complex128>());
            case type_id_t::BOOL:
                return format(v.as<bool_t>());
            case type_id_t::STRING:
                return format(v.as<string>());
            default:
                return "";
        }
    }

    //-------------------------------------------------------------------------
    string format(const value_ref &)
    {
        return "";
    }

//end of namespace
}
