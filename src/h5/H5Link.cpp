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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Implementation of the H5Link link manager class.
 *
 * Created on: Feb 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#include "H5Exceptions.hpp"
#include "H5Dataset.hpp"
#include "H5Group.hpp"
#include "H5File.hpp"

#include "H5Link.hpp"

namespace pni{
namespace io{
namespace nx{
namespace h5{

    //===============implementation of private methods=========================
    void H5Link::__split_path(const string &path,string &file,string &opath)
    {
        size_t cpos = path.find_first_of(':');

        if(cpos == string::npos)
        {
            //if there is no colon in the path the link should be 
            //internal
            file = "";
            opath = path;
        }
        else if(cpos != 0)
        {
            //if the colon appears not in the first position of the 
            //path string this is most probably an external link
            file = string(path,0,cpos);
            opath = string(path,cpos+1);
        }
        else throw H5LinkError(EXCEPTION_RECORD,"Invalid target string!");
    }

    //-------------------------------------------------------------------------
    void H5Link::__create_ext_link(const string &file,const string &opath,
                                   const H5Group &ref,const string &name)
    {
        hid_t lcpl = H5Pcreate(H5P_LINK_CREATE);
        H5Pset_create_intermediate_group(lcpl,1);

        herr_t err = H5Lcreate_external(file.c_str(),opath.c_str(),
                ref.id(),name.c_str(),lcpl,H5P_DEFAULT);
        if(err < 0)
            throw H5LinkError(EXCEPTION_RECORD,
                    "Error creating external link!");

    }

    //-------------------------------------------------------------------------
    void H5Link::__create_int_link(const string &opath,const H5Group &ref,
                                   const string &name)
    {
        hid_t lcpl = H5Pcreate(H5P_LINK_CREATE);
        H5Pset_create_intermediate_group(lcpl,1);

        herr_t err = H5Lcreate_soft(opath.c_str(),ref.id(),name.c_str(),
                lcpl,H5P_DEFAULT);
        if(err < 0)
            throw H5LinkError(EXCEPTION_RECORD,
                    "Error creating internal link!");
    }

    //================implementation of public methods=========================
    void H5Link::create(const string &s,const H5Group &ref,const string &name)
    {
        string filepath,opath;

        __split_path(s,filepath,opath);

        if(filepath != "")
            //create an external link
            __create_ext_link(filepath,opath,ref,name);
        else
            __create_int_link(opath,ref,name);
    }

    //-------------------------------------------------------------------------
    void H5Link::create(const H5Group &g,const H5Group &ref,const string &name)
    {
        __create_int_link(g.path(),ref,name);
    }

    //-------------------------------------------------------------------------
    void H5Link::create(const H5Dataset &d,const H5Group &ref,const string &n)
    {
        __create_int_link(d.path(),ref,n);
    }


//end of namespace
}
}
}
}
