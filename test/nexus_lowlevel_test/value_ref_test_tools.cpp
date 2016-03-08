//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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

#include "value_ref_test_tools.hpp"

using namespace pni::core;

namespace boost {
namespace test_tools {

    void print_log_value<value_ref>::operator()(std::ostream &stream,const value_ref &v)
    {
        switch(v.type_id())
        {
            case type_id_t::UINT8: stream<<v.as<uint8>(); break;
            case type_id_t::INT8:  stream<<v.as<int8>(); break;
            case type_id_t::UINT16: stream<<v.as<uint16>(); break;
            case type_id_t::INT16:  stream<<v.as<int16>(); break;
            case type_id_t::UINT32: stream<<v.as<uint32>(); break;
            case type_id_t::INT32:  stream<<v.as<int32>(); break;
            case type_id_t::UINT64: stream<<v.as<uint64>(); break;
            case type_id_t::INT64:  stream<<v.as<int64>(); break;
            case type_id_t::FLOAT32: stream<<v.as<float32>(); break;
            case type_id_t::FLOAT64: stream<<v.as<float64>(); break;
            case type_id_t::FLOAT128: stream<<v.as<float128>(); break;
            case type_id_t::COMPLEX32: stream<<v.as<complex32>(); break;
            case type_id_t::COMPLEX64: stream<<v.as<complex64>(); break;
            case type_id_t::COMPLEX128: stream<<v.as<complex128>(); break;
            case type_id_t::STRING: stream<<v.as<string>(); break;
            case type_id_t::BOOL: stream<<v.as<bool_t>(); break;
            case type_id_t::BINARY: stream<<v.as<binary>(); break;
            case type_id_t::NONE:   stream<<"NONE"; break;
            default:
                                    stream<<"UNKOWN";
        }
    }
}
}

#ifdef __clang__
namespace pni{
namespace core{
#else
namespace boost {
namespace test_tools {
namespace tt_detail{
#endif
    bool operator==(pni::core::value_ref const& a,pni::core::value_ref const& b)
    {
        if((a.type_id()==type_id_t::STRING) && 
           (b.type_id()==type_id_t::STRING))
            return a.as<string>() == b.as<string>();

        if((a.type_id()==type_id_t::BOOL) &&
           (b.type_id()==type_id_t::BOOL))
            return a.as<bool_t>() == b.as<bool_t>();

        if((a.type_id()==type_id_t::BINARY) && 
           (b.type_id()==type_id_t::BINARY))
            return a.as<binary>() == b.as<binary>();




        type_id_t target_type;
        if(pni::core::is_convertible(a.type_id(),b.type_id()))
            target_type = b.type_id();
        else if(pni::core::is_convertible(b.type_id(),a.type_id()))
            target_type = a.type_id();
        else 
            return false;

        switch(target_type)
        {
            case type_id_t::UINT8: return a.as<uint8>()==b.as<uint8>();
            case type_id_t::INT8:  return a.as<int8>()==b.as<int8>();
            case type_id_t::UINT16: return a.as<uint16>()==b.as<uint16>();
            case type_id_t::INT16:  return a.as<int16>()==b.as<int16>();
            case type_id_t::UINT32: return a.as<uint32>()==b.as<uint32>();
            case type_id_t::INT32:  return a.as<int32>()==b.as<int32>();
            case type_id_t::UINT64: return a.as<uint64>()==b.as<uint64>();
            case type_id_t::INT64:  return a.as<int64>()==b.as<int64>();
            case type_id_t::FLOAT32:  return a.as<float32>()==b.as<float32>();
            case type_id_t::FLOAT64:  return a.as<float64>()==b.as<float64>();
            case type_id_t::FLOAT128:  return a.as<float128>()==b.as<float128>();
            case type_id_t::COMPLEX32:  return a.as<complex32>()==b.as<complex32>();
            case type_id_t::COMPLEX64:  return a.as<complex64>()==b.as<complex64>();
            case type_id_t::COMPLEX128:  return a.as<complex128>()==b.as<complex128>();
            default:
                                 return false;
        }
    }

    bool operator!=(pni::core::value_ref const& a,
                    pni::core::value_ref const& b)
    {
        return !(a==b);
    }
#ifdef __clang__
}
}
#else
}
}
}
#endif

namespace std{

    std::ostream& operator<<(std::ostream &stream,const pni::core::value_ref &v)
    {
        switch(v.type_id())
        {
            case type_id_t::UINT8: stream<<v.as<uint8>(); break;
            case type_id_t::INT8:  stream<<v.as<int8>(); break;
            case type_id_t::UINT16: stream<<v.as<uint16>(); break;
            case type_id_t::INT16:  stream<<v.as<int16>(); break;
            case type_id_t::UINT32: stream<<v.as<uint32>(); break;
            case type_id_t::INT32:  stream<<v.as<int32>(); break;
            case type_id_t::UINT64: stream<<v.as<uint64>(); break;
            case type_id_t::INT64:  stream<<v.as<int64>(); break;
            case type_id_t::FLOAT32: stream<<v.as<float32>(); break;
            case type_id_t::FLOAT64: stream<<v.as<float64>(); break;
            case type_id_t::FLOAT128: stream<<v.as<float128>(); break;
            case type_id_t::COMPLEX32: stream<<v.as<complex32>(); break;
            case type_id_t::COMPLEX64: stream<<v.as<complex64>(); break;
            case type_id_t::COMPLEX128: stream<<v.as<complex128>(); break;
            case type_id_t::STRING: stream<<v.as<string>(); break;
            case type_id_t::BOOL: stream<<v.as<bool_t>(); break;
            case type_id_t::BINARY: stream<<v.as<binary>(); break;
            case type_id_t::NONE:   stream<<"NONE"; break;
            default:
                                    stream<<"UNKOWN";
        }
        return stream;
    }


}
