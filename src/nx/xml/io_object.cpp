//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Nov 28, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nx/xml/io_object.hpp>
#include <pni/io/nx/xml/dimensions.hpp>
#include <pni/io/nx/xml/node_data.hpp>


namespace pni{
namespace io{
namespace nx{
namespace xml{

    attribute_data io_object::name_attribute = attribute_data("name");
    attribute_data io_object::type_attribute = attribute_data("type");
    string_decoder_type io_object::string_decoder = string_decoder_type();
   
    template<typename T>
    value convert(type_id_t tid,T v)
    {
        if(tid == type_id_t::UINT8)         return value(uint8(v));
        else if(tid == type_id_t::INT8)     return value(int8(v));
        else if(tid == type_id_t::UINT16)   return value(uint16(v));
        else if(tid == type_id_t::INT16)    return value(int16(v));
        else if(tid == type_id_t::UINT32)   return value(uint32(v));
        else if(tid == type_id_t::INT32)    return value(int32(v));
        else if(tid == type_id_t::UINT64)   return value(uint64(v));
        else if(tid == type_id_t::INT64)    return value(int64(v));
        else if(tid == type_id_t::FLOAT32)  return value(float32(v));
        else if(tid == type_id_t::FLOAT64)  return value(float64(v));
        else if(tid == type_id_t::FLOAT128) return value(float128(v));
        else if(tid == type_id_t::COMPLEX32) return value(complex32(v));
        else if(tid == type_id_t::COMPLEX64) return value(complex64(v));
        else if(tid == type_id_t::COMPLEX128) return value(complex128(v));
        else if(tid == type_id_t::STRING)
        {
            std::stringstream ss;
            ss<<v;
            return value(ss.str());
        }
        else if(tid == type_id_t::BOOL)     return value(bool_t(v));
        else
            throw type_error(EXCEPTION_RECORD, "unsupported  type!");
    }

    //------------------------------------------------------------------------
    template<typename T>
    value convert(type_id_t tid,const std::complex<T> &v)
    {
        if(tid == type_id_t::COMPLEX32)
            return value(complex32(v));
        else if(tid == type_id_t::COMPLEX64)
            return value(complex64(v));
        else if(tid == type_id_t::COMPLEX128)
            return value(complex128(v));
        else 
            throw type_error(EXCEPTION_RECORD,
                    "Cannot convert a complex type to anyting else!");
    }

    //------------------------------------------------------------------------
    value convert(type_id_t tid,const string &v)
    {
        if(tid == type_id_t::STRING)
            return value(v);
        else
            throw type_error(EXCEPTION_RECORD,
                    "Cannot convert string to non-string type!");
    }

    //------------------------------------------------------------------------
    value convert(type_id_t tid,const value &v)
    {
        type_id_t sid = v.type_id();
        if(sid == type_id_t::UINT8) return convert(tid,v.as<uint8>());
        else if(sid == type_id_t::INT8)  return convert(tid,v.as<int8>());
        else if(sid == type_id_t::UINT16) return convert(tid,v.as<uint16>());
        else if(sid == type_id_t::INT16)  return convert(tid,v.as<int16>());
        else if(sid == type_id_t::UINT32) return convert(tid,v.as<uint32>());
        else if(sid == type_id_t::INT32)  return convert(tid,v.as<int32>());
        else if(sid == type_id_t::UINT64) return convert(tid,v.as<uint64>());
        else if(sid == type_id_t::INT64)  return convert(tid,v.as<int64>());
        else if(sid == type_id_t::FLOAT32) return convert(tid,v.as<float32>());
        else if(sid == type_id_t::FLOAT64) return convert(tid,v.as<float64>());
        else if(sid == type_id_t::FLOAT128) 
            return convert(tid,v.as<float128>());
        else if(sid == type_id_t::COMPLEX32)
            return convert(tid,v.as<complex32>());
        else if(sid == type_id_t::COMPLEX64)
            return convert(tid,v.as<complex64>());
        else if(sid == type_id_t::COMPLEX128)
            return convert(tid,v.as<complex128>());
        else if(sid == type_id_t::BOOL)
            return convert(tid,v.as<bool_t>());
        else if(sid == type_id_t::STRING)
            return convert(tid,v.as<string>());
        else 
            throw type_error(EXCEPTION_RECORD,
                    "Cannot handle data type!");
        
    }

    //------------------------------------------------------------------------
    size_t io_object::size(const node &io_node)
    {
        if(io_node.count("dimensions"))
            return dimensions::size(io_node.get_child("dimensions"));
        else
            return 1;
    }

    //------------------------------------------------------------------------
    size_t io_object::rank(const node &io_node)
    {
        if(io_node.count("dimensions"))
            return dimensions::rank(io_node.get_child("dimensions"));
        else 
            return 0;
    }

    //------------------------------------------------------------------------
    string io_object::name(const node &io_node)
    {
        return string_decoder.decode(name_attribute.read(io_node));
    }
    
    //------------------------------------------------------------------------
    shape_t io_object::shape(const node &io_node)
    {
        shape_t shape{1};
        if(io_node.count("dimensions"))
            shape = dimensions::object_from_xml(io_node.get_child("dimensions"));

        return shape;
    }

    //------------------------------------------------------------------------
    type_id_t io_object::type_id(const node &io_node)
    {
        string type = string_decoder.decode(type_attribute.read(io_node));
        return type_id_from_str(type);
    }
    
    //--------------------------------------------------------------------
    array io_object::data_from_xml(const node &io_node,char separator)
    {
        decoder<array> dec(separator);

        //read string representation from the node
        string data_rep = node_data().read(io_node);

        if(!data_rep.empty())
        {
            //read shape and type id from the node
            type_id_t tid = type_id(io_node);
            shape_t   s   = shape(io_node);

            //create the output array
            array data = make_array(tid,s);
            const auto buffer = dec.decode(data_rep);
            size_t index=0;
            for(const auto v: buffer) 
                data[index++] = convert(tid,static_cast<value>(v));

            /*
            if(data.size() == 1)
                data[0] = read_node(tid,io_node);
            else 
            {
                decoder_type decoder(separator);

            }
            */

            return data;
        }

        return array();
    }

    //------------------------------------------------------------------------
    void io_object::data_to_xml(const array &data,node &io_node)
    {
        if(data.size()!=size(io_node))
            throw size_mismatch_error(EXCEPTION_RECORD,
                    "Array size and field size do not match!");

        std::stringstream ss;
        //ss<<data;
        io_node.put_value(ss.str());
    }
//end of namespace
}
}
}
}
