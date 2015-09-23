//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Feb 10, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//


#include <pni/io/nx/h5/h5link.hpp>
#include <pni/io/nx/h5/group_imp.hpp>
#include <pni/io/nx/nxpath/utils.hpp>

#include <pni/io/nx/h5/h5_error_stack.hpp>
#include <pni/io/exceptions.hpp>
#include <pni/io/nx/h5/hdf5_utilities.hpp>

namespace pni{
namespace io{
namespace nx{
namespace h5{
    
    using namespace pni::core;

    //===============implementation of private methods=========================
    string h5link::_nx2hdf5path(const nxpath &p)
    {
        string h5p;

        if(is_absolute(p))
            h5p = "/";

        size_t index = 0;
        for(auto iter = p.begin();iter!=p.end();++iter,++index)
        {
            string element = iter->first;
            if(element.empty())
                throw pni::core::value_error(EXCEPTION_RECORD,
                        "The Nexus path ["+nxpath::to_string(p)+"]"
                        " contains element without a name!");

            //add element
            h5p += element;

            //need a trailing / for all objects except the last one
            if(index != p.size()-1) h5p += "/";
        }

        return h5p;
    }


    //-------------------------------------------------------------------------
    void h5link::create_external_link(const nxpath &path,const group_imp &loc,
                                      const string &name)
    {
        using namespace pni::core; 
        
        if(!loc.is_valid())
            throw pni::io::invalid_object_error(EXCEPTION_RECORD,
                    "Cannot create a link below an invalid group object!");

        if(path.filename().empty())
            throw value_error(EXCEPTION_RECORD,
                    "For an external link a target filename must be provided!");

        if(!is_absolute(path))
            throw value_error(EXCEPTION_RECORD,
                    "For an external link the target path must be absolute!");

        //convert the user provided path to an HDF5 path
        string h5path = _nx2hdf5path(path);

        herr_t err = H5Lcreate_external(path.filename().c_str(),h5path.c_str(),
                                        loc.object().id(),name.c_str(),
                                        H5P_DEFAULT,H5P_DEFAULT);
        if(err < 0)
            throw pni::io::link_error(EXCEPTION_RECORD,
                    "Error creating external link!\n\n"+get_h5_error_string());

    }

    //-------------------------------------------------------------------------
    void h5link::create_internal_link(const nxpath &target,const group_imp &loc,
                                      const string &name)
    {
        using namespace pni::core;
        if(!loc.is_valid())
            throw pni::io::invalid_object_error(EXCEPTION_RECORD,
                    "Cannot create a link below an invalid group object!");

        if(!target.filename().empty())
            throw value_error(EXCEPTION_RECORD,
                    "Target paths for internal links must not contain a "
                    "filename!");

        string target_path = _nx2hdf5path(target);

        herr_t err = H5Lcreate_soft(target_path.c_str(),loc.object().id(),
                                    name.c_str(),H5P_DEFAULT,H5P_DEFAULT);
        if(err < 0)
            throw pni::io::link_error(EXCEPTION_RECORD,
                    "Error creating internal link!\n\n"+
                    get_h5_error_string());
    }

    
    //-------------------------------------------------------------------------
    pni::io::nx::nxlink_type h5link::link_type(const group_imp &loc,
                                               const string &name)
    {
        H5L_info_t info;

        if(!loc.has_child(name))
            throw key_error(EXCEPTION_RECORD,
                    "Group ["+get_path(loc.object())
                    +"] does not have a child ["+name+ "]!");

        if(H5Lget_info(loc.object().id(),name.c_str(),&info,H5P_DEFAULT)<0)
        {
            throw pni::io::link_error(EXCEPTION_RECORD,
                    "Error obtaining link type for child ["+name+"] of group"+
                    "["+get_path(loc.object())+"]!");
        }

        if(info.type == H5L_TYPE_EXTERNAL)
            return pni::io::nx::nxlink_type::EXTERNAL;
        else if(info.type == H5L_TYPE_HARD)
            return pni::io::nx::nxlink_type::HARD;
        else if(info.type == H5L_TYPE_SOFT)
            return pni::io::nx::nxlink_type::SOFT;
        else 
            throw pni::core::type_error(EXCEPTION_RECORD,
                    "Link is of unknown type!");
    }

//end of namespace
}
}
}
}
