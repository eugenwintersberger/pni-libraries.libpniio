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


#include <sstream>
#include <algorithm>
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
       
        check_if_valid(loc,EXCEPTION_RECORD,"Parent group invalid - "
                                            "link creation failed!");

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
        check_if_valid(loc,EXCEPTION_RECORD,"Parent group invalid -  "
                                            "link creation failed!");

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
    void h5link::check_if_valid(const group_imp &loc,
                                const exception_record &record,
                                const string &message)
    {
        if(!loc.is_valid())
            throw pni::io::invalid_object_error(record,message);
    }

    //-------------------------------------------------------------------------
    void h5link::check_if_exists(const group_imp &loc,const string &lname,
                                 const exception_record &record,
                                 const string &message)
    {
        string exc_message = "Group ["+get_path(loc.object())
                             +"] does not have a child ["+lname+ "]";
        if(message.empty())
            exc_message += "!";
        else
            exc_message += ":"+message;

        if(!loc.has_child(lname)) throw key_error(record,exc_message);
    }
    
    //-------------------------------------------------------------------------
    void h5link::check_if_exists(const group_imp &loc,size_t index,
                                 const exception_record &record,
                                 const string &message)
    {
        std::stringstream ss;
        ss<<"Group ["<<get_path(loc.object())<<"] has "<<loc.size()
          <<"children, index was "<<index;
        
        string exc_message = ss.str();
        if(message.empty())
            exc_message += "!";
        else
            exc_message += ": "+message;

        if(index>=loc.size())
            throw index_error(record,exc_message);
        
    }

    //-------------------------------------------------------------------------
    H5L_info_t h5link::get_link_info(const group_imp &loc,const string &lname)
    {
        check_if_valid(loc,EXCEPTION_RECORD,"Invalid parent group - "
                                            "cannot retrieve link info!");
        check_if_exists(loc,lname,EXCEPTION_RECORD,"cannot retrieve link info");

        H5L_info_t info;

        if(H5Lget_info(loc.object().id(),lname.c_str(),&info,H5P_DEFAULT)<0)
        {
            throw pni::io::link_error(EXCEPTION_RECORD,
                    "Error obtaining link type for child ["+lname+"] of group"+
                    "["+get_path(loc.object())+"]!");
        }

        return info;
    }

    //------------------------------------------------------------------------
    H5L_info_t h5link::get_link_info(const group_imp &loc,size_t index)
    {
        check_if_valid(loc,EXCEPTION_RECORD,"Invalid parent group - "
                                            "cannot retrieve link info!");
        check_if_exists(loc,index,EXCEPTION_RECORD,
                        "cannot retrieve link info");

        H5L_info_t info;

        if(H5Lget_info_by_idx(loc.object().id(),".",
                              H5_INDEX_NAME,H5_ITER_NATIVE,
                              index,&info,H5P_DEFAULT)<0)
        {
            std::stringstream ss;
            ss<<"Error obtaining link type for child ["<<index
              <<"] of group ["<<get_path(loc.object())<<"]!";
            throw pni::io::link_error(EXCEPTION_RECORD,ss.str());
                    
        }
        
        return info;

    }

    //------------------------------------------------------------------------
    auto h5link::link_name(const group_imp &loc,size_t index)
        -> string
    {
        check_if_valid(loc,EXCEPTION_RECORD,"Parent group invalid - "
                                            "cannot obtain link name!");
        check_if_exists(loc,index,EXCEPTION_RECORD,"cannot obtain link name!");

        ssize_t size = H5Lget_name_by_idx(loc.object().id(),
                                          ".",
                                          H5_INDEX_NAME,
                                          H5_ITER_NATIVE,
                                          index,
                                          NULL,
                                          0,
                                          H5P_DEFAULT);

        if(size<0)
        {
            std::stringstream ss;
            ss<<"Cannot obtain the size of the link with index "<<index
              <<" of group ["<<get_path(loc.object())<<"]!";
            throw pni::io::link_error(EXCEPTION_RECORD,ss.str());
        }

        string name(size,' ');
        size = H5Lget_name_by_idx(loc.object().id(),".",H5_INDEX_NAME,
                                  H5_ITER_NATIVE,index,
                                  const_cast<char*>(name.data()),
                                  name.size()+1,H5P_DEFAULT);
        if(size<0)
        {
            std::stringstream ss;
            ss<<"Cannot obtain the name of the link with index "<<index
              <<" of group ["<<get_path(loc.object())<<"]!";
            throw pni::io::link_error(EXCEPTION_RECORD,ss.str());
        }
        
        return name;
                     
    }

    //------------------------------------------------------------------------
    auto h5link::link_target(const group_imp &loc,size_t index)
        -> pni::io::nx::nxpath
    {
        string name = link_name(loc,index);

        return link_target(loc,name);
    }

    //------------------------------------------------------------------------
    auto h5link::link_target(const group_imp &loc,
                             const pni::core::string &lname)
        -> pni::io::nx::nxpath
    {
        using namespace pni::io::nx;

        switch(link_type(loc,lname))
        {
            case nxlink_type::HARD: 
                return nxpath::from_string(get_path(loc.at(lname)));
            case nxlink_type::SOFT:
                return get_soft_link_target(loc,lname);
            case nxlink_type::EXTERNAL:
                return get_external_link_target(loc,lname);
            default:
                return nxpath();
        }
    }

    //------------------------------------------------------------------------
    auto h5link::get_link_value(const group_imp &loc,const string &lname)
        -> string
    {

        H5L_info_t info = get_link_info(loc,lname);
        string value(info.u.val_size-1,' ');

        if(H5Lget_val(loc.object().id(),lname.c_str(),
                      reinterpret_cast<void*>(const_cast<char*>(value.data())),
                      info.u.val_size,
                      H5P_DEFAULT)<0)
        {
            throw  pni::io::link_error(EXCEPTION_RECORD,
                    "Cannot obtain link value for link ["+lname+"] in group"
                    " ]"+get_path(loc.object())+"]!");
        }

        return value;
    }

    //-------------------------------------------------------------------------
    auto h5link::get_soft_link_target(const group_imp &loc,
                                      const pni::core::string &lname)
        -> pni::io::nx::nxpath
    {
        string value = get_link_value(loc,lname);

        nxpath target = nxpath::from_string(loc.filename()+":/"+value);

        return target;
    }
             
    //-------------------------------------------------------------------------
    auto h5link::get_external_link_target(const group_imp &loc,
                                          const string &lname)
        -> pni::io::nx::nxpath

    {
        string value = get_link_value(loc,lname);
        auto first_iter = std::find(value.begin(),value.end(),'\0');
        std::advance(first_iter,1);
        auto last_iter = std::find(first_iter,value.end(),'\0');
                       

        string filename(first_iter,last_iter);
        std::advance(last_iter,1);
        string object_path(last_iter,value.end());
                               

        return nxpath::from_string(filename+":/"+object_path);
    }
    
    //-------------------------------------------------------------------------
    auto h5link::link_type(const group_imp &loc,const string &name)
        -> pni::io::nx::nxlink_type
    {
        check_if_valid(loc,EXCEPTION_RECORD,"Parent group invalid - "
                                            "cannot obtain link type!");
        check_if_exists(loc,name,EXCEPTION_RECORD,"cannot obtain link type!");

        H5L_info_t info = get_link_info(loc,name);
        
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
