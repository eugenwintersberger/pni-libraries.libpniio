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

#include<pni/core/Types.hpp>
#include<pni/core/TypeIDMap.hpp>

#include "NXField.hpp"
#include "NXGroup.hpp"

using namespace pni::core;

namespace pni{
namespace io{
namespace nx{

    /*!
    \ingroup nexus_lowlevel
    \brief create a field from a TypeID

    A utility function that creates a field dynamically using a type ID to
    identify the data type to use. This function is intended for situations
    where the types ID is a runtime parameter rather than a comiple time
    constant.  
    
    \code
    //create a default field of shape {1} and chunk shape {1}
    auto f = create_field(g,"test",TypeID::STRING);

    //create a field with custom shape and chunk shape
    Shape s{0,1024,1024};
    Shape cs{1,1024,1024};
    auto f = create_field(g,"test2",TypeID::UINT16,s,cs);

    //create a field with a filter - in this case shape and chunk shape
    //must be provided 
    NXDeflateFilter deflate(9,true);
    auto f = create_field(g,"test3",TypeID::UINT16,s,cs,deflate);
    \endcode
   
    \throws TypeError if type ID does not exist
    \param g group objecct in below which to create the field
    \param fname name of the field 
    \param tid type ID of the field
    \param args optional arguments (see code example above) 
    \return field type 
    */
    template<typename GTYPE,typename ...ATYPES>
    typename GTYPE::field_type
    create_field(const GTYPE &g,const String &fname,const TypeID &tid,
                 ATYPES ...args)
    {
        if(tid == TypeID::UINT8)
            return g.create_field<UInt8>(fname,args...);
        if(tid == TypeID::INT8)
            return g.create_field<Int8>(fname,args...);
        if(tid == TypeID::UINT16)
            return g.create_field<UInt16>(fname,args...);
        if(tid == TypeID::INT16)
            return g.create_field<Int16>(fname,args...);
        if(tid == TypeID::UINT32)
            return g.create_field<UInt32>(fname,args...);
        if(tid == TypeID::INT32)
            return g.create_field<Int32>(fname,args...);
        if(tid == TypeID::UINT64)
            return g.create_field<UInt64>(fname,args...);
        if(tid == TypeID::INT64)
            return g.create_field<Int64>(fname,args...);
        if(tid == TypeID::FLOAT32)
            return g.create_field<Float32>(fname,args...);
        if(tid == TypeID::FLOAT64)
            return g.create_field<Float64>(fname,args...);
        if(tid == TypeID::FLOAT128)
            return g.create_field<Float128>(fname,args...);
        if(tid == TypeID::COMPLEX32)
            return g.create_field<Complex32>(fname,args...);
        if(tid == TypeID::COMPLEX64)
            return g.create_field<Complex64>(fname,args...);
        if(tid == TypeID::COMPLEX128)
            return g.create_field<Complex128>(fname,args...);
        if(tid == TypeID::BINARY)
            return g.create_field<Binary>(fname,args...);
        if(tid == TypeID::STRING)
            return g.create_field<String>(fname,args...);   
        else
        {
            throw TypeError(EXCEPTION_RECORD,"Unsupported data type!");
        }

    }




//end of namespace
}
}
}
