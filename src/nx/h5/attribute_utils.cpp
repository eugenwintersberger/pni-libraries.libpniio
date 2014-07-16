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
// Created on: Jul 15, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nx/h5/attribute_utils.hpp>
#include <pni/io/nx/h5/h5_error_stack.hpp>


namespace pni{
namespace io{
namespace nx{
namespace h5{
    //-------------------------------------------------------------------------
    bool has_attribute(const object_imp &parent,const string &name) 
    {
        htri_t ret = H5Aexists(parent.id(),name.c_str());
        if(ret >0 ) return true;
        else if(ret == 0) return false;
        else
            throw object_error(EXCEPTION_RECORD,
                    "Error checking for existence of attribute ["+name
                    +"] on object ["+get_object_path(parent.id())+"]!\n\n"
                    +get_h5_error_string());
    }
    
    //-------------------------------------------------------------------------
    void delete_attribute(const object_imp &parent,const string &name) 
    {
        herr_t err = H5Adelete(parent.id(),name.c_str());
        if(err < 0)
            throw object_error(EXCEPTION_RECORD,
                    "Error deleteing attribute ["+name+"] from object [" 
                    +get_object_path(parent.id())+"]!\n\n"
                    +get_h5_error_string());
    }
    //------------------------------------------------------------------------
    object_imp create_attribute(const object_imp &parent,const string &name,
                              const h5datatype &type,const h5dataspace &space,
                              bool overwrite)
    {
        //what to do if the attribute already exists?
        if(has_attribute(parent,name))
        {
            //if the overwrite flag is set the original attribute will be 
            //removed
            if(overwrite) 
                delete_attribute(parent,name);
            else
                throw object_error(EXCEPTION_RECORD,
                        "Attribute ["+name+"] already exists on object ["
                        +get_object_path(parent.id())+"]!\n\n"
                        +get_h5_error_string());
        }

        return object_imp(H5Acreate2(parent.id(),
                                   name.c_str(),
                                   type.object().id(),
                                   space.object().id(),
                                   H5P_DEFAULT,
                                   H5P_DEFAULT));
    }

    //------------------------------------------------------------------------
    object_imp get_attribute_by_name(const object_imp &parent,const string &name) 
    {
        if(!has_attribute(parent,name))
            throw key_error(EXCEPTION_RECORD,
                     "Object ["+get_object_path(parent.id())
                     +"] has no attribute ["+name+"]!");

        return object_imp(H5Aopen(parent.id(),name.c_str(),H5P_DEFAULT));
    }

    //-------------------------------------------------------------------------
    //get number of attributes
    size_t get_number_of_attributes(const object_imp &parent) noexcept
    {
        H5O_info_t info;
        H5Oget_info(parent.id(),&info);

        return info.num_attrs;
    }

    //-------------------------------------------------------------------------
    //implementation of opening an attribute by index
    object_imp get_attribute_by_index(const object_imp &parent,size_t i) 
    {
        if(i>=get_number_of_attributes(parent))
        {
            std::stringstream ss;
            ss<<"Index ("<<i<<") exceeds number of attributes ("
              <<get_number_of_attributes(parent)<<" on object ["
              <<get_object_path(parent.id())<<"]!";
            throw index_error(EXCEPTION_RECORD,ss.str());
        }

        return object_imp(H5Aopen_by_idx(parent.id(),".",H5_INDEX_NAME,
                                       H5_ITER_INC,i,H5P_DEFAULT,H5P_DEFAULT));

    }

        
//end of namespace
}
}
}
}
