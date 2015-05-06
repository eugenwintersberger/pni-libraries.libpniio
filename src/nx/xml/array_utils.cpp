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
// Created on: Feb 12, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nx/xml/array_utils.hpp>

namespace pni{
namespace io{
namespace nx{
namespace xml{

    

    array make_array(const node &data)
    {
        using namespace pni::core;
        type_id_t tid = io_node::type_id(data);

        switch(tid)
        {
            case type_id_t::UINT8:
                return array(make_array<dynamic_array<uint8>>(data));
            case type_id_t::INT8:
                return array(make_array<dynamic_array<int8>>(data));
            case type_id_t::UINT16:
                return array(make_array<dynamic_array<uint16>>(data));
            case type_id_t::INT16:
                return array(make_array<dynamic_array<int16>>(data));
            case type_id_t::UINT32:
                return array(make_array<dynamic_array<uint32>>(data));
            case type_id_t::INT32:
                return array(make_array<dynamic_array<int32>>(data));
            case type_id_t::UINT64:
                return array(make_array<dynamic_array<uint64>>(data));
            case type_id_t::INT64:
                return array(make_array<dynamic_array<int64>>(data));
            case type_id_t::FLOAT32:
                return array(make_array<dynamic_array<float32>>(data));
            case type_id_t::FLOAT64:
                return array(make_array<dynamic_array<float64>>(data));
            case type_id_t::FLOAT128:
                return array(make_array<dynamic_array<float128>>(data));
            case type_id_t::COMPLEX32:
                return array(make_array<dynamic_array<complex32>>(data));
            case type_id_t::COMPLEX64:
                return array(make_array<dynamic_array<complex64>>(data));
            case type_id_t::COMPLEX128:
                return array(make_array<dynamic_array<complex128>>(data));
            case type_id_t::BOOL:
                return array(make_array<dynamic_array<bool_t>>(data));
            case type_id_t::STRING:
                return array(make_array<dynamic_array<string>>(data));
            default:
                throw type_error(EXCEPTION_RECORD,
                        "Unsupported data type in XML!");
        }
        
    }

//end of namespace
}
}
}
}

