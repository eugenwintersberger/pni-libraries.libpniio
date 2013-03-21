/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Utilty functions and function templates concerning NXField objects.
 *
 * Created on: Jul 2, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include<pni/core/types.hpp>
#include<pni/core/type_id_map.hpp>

#include "nxfield.hpp"
#include "nxgroup.hpp"

using namespace pni::core;

namespace pni{
namespace io{
namespace nx{
    //need this here to avoid name collisions with tango headers.
    using pni::core::array;
    using pni::core::string;
    using pni::core::exception;

    /*!
    \ingroup nexus_lowlevel
    \brief create a field from a TypeID

    A utility function that creates a field dynamically using a type ID to
    identify the data type to use. This function is intended for situations
    where the types ID is a runtime parameter rather than a comiple time
    constant.  
    
    \code
    //create a default field of shape {1} and chunk shape {1}
    auto f = create_field(g,"test",type_id_t::STRING);

    //create a field with custom shape and chunk shape
    Shape s{0,1024,1024};
    Shape cs{1,1024,1024};
    auto f = create_field(g,"test2",type_id_t::UINT16,s,cs);

    //create a field with a filter - in this case shape and chunk shape
    //must be provided 
    nxdeflate_filter deflate(9,true);
    auto f = create_field(g,"test3",type_id_t::UINT16,s,cs,deflate);
    \endcode
   
    \throws type_error if type ID does not exist
    \param g group objecct in below which to create the field
    \param fname name of the field 
    \param tid type ID of the field
    \param args optional arguments (see code example above) 
    \return field type 
    */
    template<typename GTYPE,typename ...ATYPES>
    typename GTYPE::field_type
    create_field(const GTYPE &g,const string &fname,const type_id_t &tid,
                 ATYPES ...args)
    {
        if(tid == type_id_t::UINT8)
            return g.create_field<uint8>(fname,args...);
        if(tid == type_id_t::INT8)
            return g.create_field<int8>(fname,args...);
        if(tid == type_id_t::UINT16)
            return g.create_field<uint16>(fname,args...);
        if(tid == type_id_t::INT16)
            return g.create_field<int16>(fname,args...);
        if(tid == type_id_t::UINT32)
            return g.create_field<uint32>(fname,args...);
        if(tid == type_id_t::INT32)
            return g.create_field<int32>(fname,args...);
        if(tid == type_id_t::UINT64)
            return g.create_field<uint64>(fname,args...);
        if(tid == type_id_t::INT64)
            return g.create_field<int64>(fname,args...);
        if(tid == type_id_t::FLOAT32)
            return g.create_field<float32>(fname,args...);
        if(tid == type_id_t::FLOAT64)
            return g.create_field<float64>(fname,args...);
        if(tid == type_id_t::FLOAT128)
            return g.create_field<float128>(fname,args...);
        if(tid == type_id_t::COMPLEX32)
            return g.create_field<complex32>(fname,args...);
        if(tid == type_id_t::COMPLEX64)
            return g.create_field<complex64>(fname,args...);
        if(tid == type_id_t::COMPLEX128)
            return g.create_field<complex128>(fname,args...);
        if(tid == type_id_t::BINARY)
            return g.create_field<binary>(fname,args...);
        if(tid == type_id_t::STRING)
            return g.create_field<string>(fname,args...);   
        else
        {
            throw type_error(EXCEPTION_RECORD,"Unsupported data type!");
        }

    }




//end of namespace
}
}
}
