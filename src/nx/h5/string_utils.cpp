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
// Created on: Jul 21, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "string_utils.hpp"
#include <pni/core/error.hpp>


namespace pni{
namespace io{
namespace nx{
namespace h5{
    using namespace pni::core;
    
    //utility function to check whether or not a data type is a string type
    bool is_string_type(const h5datatype &type)
    {
        if(H5Tget_class(type.object().id())==H5T_STRING)
            return true;
        else
            return false;
    }

    //-------------------------------------------------------------------------
    bool is_vl_string(const h5datatype &type)
    {
        //if the type is not even a string type we can immediately 
        //return false
        if(!is_string_type(type)) return false;

        //check the string type
        htri_t result = H5Tis_variable_str(type.object().id());

        if(result >0)
            return true;
        else if(result == 0)
            return false;
        else
            throw object_error(EXCEPTION_RECORD,
                    "Cannot retrieve VL status of string type!");
    }

    //-------------------------------------------------------------------------
    bool is_static_string(const h5datatype &type)
    {
        if(!is_string_type(type)) return false;

        return !is_vl_string(type);
    }
    
     //-------------------------------------------------------------------------
    size_t static_string_size(const h5datatype &type)
    {
        if(!is_static_string(type))
            throw type_error(EXCEPTION_RECORD,
                    "Data type is not a static string type!");

        size_t size = H5Tget_size(type.object().id());
        
        if(!size)
            throw object_error(EXCEPTION_RECORD,
                    "Error retrieving the size of the string type!");

        return size;
    }

    //------------------------------------------------------------------------
    void copy_from_vector(const char_vector_type &vector,size_t nstrs,
                          size_t strsize,string *strings,
                          const formatter_ptr &formatter)
    {
        if(vector.size()!=nstrs*strsize)
            throw size_mismatch_error(EXCEPTION_RECORD,
                    "The vector size does not match the total number of "
                    "required characater!");

        for(size_t i = 0;i<nstrs;++i)
        {
            strings[i] = (*formatter)(string(vector.data()+i*strsize,strsize));
            
        }
    }

    //------------------------------------------------------------------------
    void copy_from_vector(const char_ptr_vector_type &vector,
                          size_t nstrs,string *strings,
                          const formatter_ptr &formatter)
    {
        if(nstrs!=vector.size())
            throw size_mismatch_error(EXCEPTION_RECORD,
                    "Number of strings does not match vector size!");

        for(const char *v: vector)
        {
            if(v==nullptr) continue; 
            
            *strings = (*formatter)(string(v));
            strings++;
        }
    }
    
    //-------------------------------------------------------------------------
    bool is_nullterm_str(const h5datatype &type)
    {
        return H5T_STR_NULLTERM == H5Tget_strpad(type.object().id());
    }
    
    //-------------------------------------------------------------------------
    bool is_nullpad_str(const h5datatype &type)
    {
        return H5T_STR_NULLPAD == H5Tget_strpad(type.object().id());
    }
    
    //-------------------------------------------------------------------------
    bool is_spacepad_str(const h5datatype &type)
    {
        return H5T_STR_SPACEPAD == H5Tget_strpad(type.object().id());
    }

//end of namespace
}
}
}
}
