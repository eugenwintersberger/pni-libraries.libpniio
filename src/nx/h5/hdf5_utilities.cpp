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
// Created on: Aug 20, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/exceptions.hpp>
#include <pni/io/nx/h5/hdf5_utilities.hpp>
#include <pni/io/nx/h5/object_imp.hpp>
#include <pni/io/nx/h5/h5_error_stack.hpp>



namespace pni{
namespace io{
namespace nx{
namespace h5{

    using pni::io::io_error;

    string get_filename(hid_t id)
    {
        //first we need to determine the size of the file name
        ssize_t nsize = H5Fget_name(id,nullptr,0);
        if(nsize<0)
            throw io_error(EXCEPTION_RECORD,
                    "Error retrieving length of file name!");

        //nsize is now the number of characters in the file name.
        string buffer(nsize,' ');
        //we have to read one more character to get the binary 0
        if(H5Fget_name(id,const_cast<char*>(buffer.data()),nsize+1)<0)
            throw io_error(EXCEPTION_RECORD,
                    "Error retrieving filename!");

        return buffer;
    }

    //-------------------------------------------------------------------------
    string get_filename(const object_imp &obj)
    {
        if(obj.is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Object is not valid - cannot obtain filename!");

        return get_filename(obj.id());
    }
   
    //-------------------------------------------------------------------------
    string get_object_path(hid_t id)
    {
        //if the object has already been created return this value
        ssize_t bsize = H5Iget_name(id,NULL,1);
        if(bsize<0)
            throw io_error(EXCEPTION_RECORD,
                    "Error retrieving length of object name!");

        string buffer(bsize,' ');

        if(H5Iget_name(id,const_cast<char*>(buffer.data()),bsize+1)<0)
            throw io_error(EXCEPTION_RECORD,
                    "Error retrieving object name!");

        return buffer;
    }

    //------------------------------------------------------------------------
    string get_attribute_name(const object_imp &object)
    {
        ssize_t buffer_size = H5Aget_name(object.id(),0,NULL);
        if(buffer_size<0)
            throw io_error(EXCEPTION_RECORD,
                    "Error retrieving length of attribute name!\n\n"+
                    get_h5_error_string());

        string name(buffer_size,' ');

        if(H5Aget_name(object.id(),buffer_size+1,
                       const_cast<char*>(name.data()))<0)
            throw io_error(EXCEPTION_RECORD,
                    "Error retrieving name of attribute!\n\n"+
                    get_h5_error_string());

        return name;
    }

    //------------------------------------------------------------------------
    string get_others_name(const object_imp &object)
    {
        string p = get_object_path(object.id());

        //if the path is empty return an empty string
        if(p.empty()) return p;

        if((p.size() == 1) && (p[0] == '/')) return p;

        //need to extract the the name information from the path
        size_t lpos = p.find_last_of("/");
        string name = p;
        if(lpos != p.npos) name = string(p,lpos+1,p.size()-lpos+1);

        return name;
    }
    //------------------------------------------------------------------------
    string get_name(const object_imp &obj) 
    {
        if(!obj.is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Try to obtain the name of an invalid object!");

        if(get_hdf5_type(obj) == h5object_type::ATTRIBUTE)
            return get_attribute_name(obj);
        else
            return get_others_name(obj);

    }

    //------------------------------------------------------------------------
    string get_parent_path(hid_t id)
    {
        string opath = get_object_path(id);

        if(opath.empty()) return opath;

        //if the string is of size 1 and has
        //only one / return this
        if((opath.size() == 1) && (opath[0] == '/')) 
            return string("/");

        size_t lpos = opath.find_last_of("/");
        string base;
        if(lpos != opath.npos)
        {
            base = string(opath,0,lpos+1);
            //remove a trailing /, except the base is just the root group
            if((base.size()>1) && (base[base.size()-1] == '/'))
                base = string(base,0,base.size()-1);
        }

        return base;
    }
    
    //-------------------------------------------------------------------------
    object_imp get_object_parent(const object_imp &obj)
    {
        object_imp file(H5Iget_file_id(obj.id()));

        return object_imp(H5Oopen(file.id(),
                                get_parent_path(obj.id()).c_str(),
                                H5P_DEFAULT));
    }

    //------------------------------------------------------------------------
    object_imp get_attribute_parent(const object_imp &obj)
    {
        //attempt to retrieve the parent object
        return object_imp(H5Oopen(obj.id(),".",H5P_DEFAULT));
    }

    //------------------------------------------------------------------------
    object_imp get_parent(const object_imp &obj) 
    {
        if(get_hdf5_type(obj)==h5object_type::ATTRIBUTE)
            return get_attribute_parent(obj);
        else
            return get_object_parent(obj);
    }

//end of namespace
}
}
}
}
