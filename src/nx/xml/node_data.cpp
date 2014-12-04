//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 15, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//


#include <pni/io/parsers/array_parser.hpp>
#include <pni/io/nx/xml/node_data.hpp>
#include <boost/algorithm/string.hpp>

namespace pni{
namespace io{
namespace nx{
namespace xml{

    string node_data::read(const node &n) const
    {
        string data = n.data();
        boost::algorithm::trim(data);
        return data;
    }

    //-------------------------------------------------------------------------
    void node_data::write(const string &data,node &n) const
    {
        n.put_value(data);
    }

    
    //------------------------------------------------------------------------
    /*
    value read_node(type_id_t tid,const node &n)
    {
        if(tid == type_id_t::UINT8)
            return value(node_data<uint8>::read(n));
        else if(tid == type_id_t::INT8)
            return value(node_data<int8>::read(n));
        else if(tid == type_id_t::UINT16)
            return value(node_data<uint16>::read(n));
        else if(tid == type_id_t::INT16)
            return value(node_data<int16>::read(n));
        else if(tid == type_id_t::UINT32)
            return value(node_data<uint32>::read(n));
        else if(tid == type_id_t::INT32)
            return value(node_data<int32>::read(n));
        else if(tid == type_id_t::UINT64)
            return value(node_data<uint64>::read(n));
        else if(tid == type_id_t::INT64)
            return value(node_data<int16>::read(n));
        else if(tid == type_id_t::FLOAT32)
            return value(node_data<float32>::read(n));
        else if(tid == type_id_t::FLOAT64)
            return value(node_data<float64>::read(n));
        else if(tid == type_id_t::FLOAT128)
            return value(node_data<float128>::read(n));
        else if(tid == type_id_t::COMPLEX32)
            return value(node_data<complex32>::read(n));
        else if(tid == type_id_t::COMPLEX64)
            return value(node_data<complex64>::read(n));
        else if(tid == type_id_t::COMPLEX128)
            return value(node_data<complex128>::read(n));
        else if(tid == type_id_t::BINARY)
            return value(node_data<binary>::read(n));
        else if(tid == type_id_t::STRING)
            return value(node_data<string>::read(n));
        else if(tid == type_id_t::BOOL)
            return value(node_data<bool_t>::read(n));
        else 
            throw type_error(EXCEPTION_RECORD,
                    "Unsupported data type!");
    }
    */


//end of namespace
}
}
}
}
