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
 *  Created on: Jun 30, 2011
 *      Author: Eugen Wintersberger
 */

#include <pni/io/nx/h5/H5File.hpp>
#include <pni/io/nx/h5/H5Attribute.hpp>

#include <pni/io/nx/h5/h5_error_stack.hpp>
#include <pni/io/nx/nxexceptions.hpp>

#include <sstream>

namespace pni{
namespace io{
namespace nx{
namespace h5{


    //=========Implementation fo constructors an destructors===================
    //implementation of the default constructor
    H5File::H5File():H5Group(){ }
   
    //-------------------------------------------------------------------------
    //implement constructor (protected) using an HDF5 ID object
    H5File::H5File(hid_t id):H5Group(id){ }

    //--------------------------------------------------------------------------
    //implementation of the move constructor
    H5File::H5File(H5File &&o):H5Group(std::move(o)){ }

    //-------------------------------------------------------------------------
    //implementation of copy constructor
    H5File::H5File(const H5File &o):H5Group(o) { } 

    //-------------------------------------------------------------------------
    //implementation of the destructor
    H5File::~H5File() 
    {
        if(is_valid())
        {
            std::cerr<<"File: "<<name()<<std::endl;
            std::cerr<<"Open files:      "<<
                H5Fget_obj_count(id(),H5F_OBJ_FILE)<<std::endl;
            std::cerr<<"Open data sets:  "<<
                H5Fget_obj_count(id(),H5F_OBJ_DATASET)<<std::endl;
            std::cerr<<"Open groups:     "<<
                H5Fget_obj_count(id(),H5F_OBJ_GROUP)<<std::endl;
            std::cerr<<"Open data type:  "<<
                H5Fget_obj_count(id(),H5F_OBJ_DATATYPE)<<std::endl;
            std::cerr<<"Open attributes: "<<
                H5Fget_obj_count(id(),H5F_OBJ_ATTR)<<std::endl;
            H5Fflush(id(),H5F_SCOPE_GLOBAL);
            H5Fclose(id());
            H5Object::reset_id();
            H5garbage_collect();
        }
    }

    //=================Implementation of assignment operators==================
    H5File &H5File::operator=(H5File &&o)
    {
        if(this != &o) H5Group::operator=(std::move(o));

        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of copy assignment
    H5File &H5File::operator=(const H5File &o)
    {
        if(this != &o) H5Group::operator=(o);

        return *this;
    }


    //=================Implementation of file specific methods=================
    void H5File::close()
    {
        //check for open objects in the file
        if(is_valid())
        {
            std::cerr<<"File: "<<name()<<std::endl;
            std::cerr<<"Open files:      "<<
                H5Fget_obj_count(id(),H5F_OBJ_FILE)<<std::endl;
            std::cerr<<"Open data sets:  "<<
                H5Fget_obj_count(id(),H5F_OBJ_DATASET)<<std::endl;
            std::cerr<<"Open groups:     "<<
                H5Fget_obj_count(id(),H5F_OBJ_GROUP)<<std::endl;
            std::cerr<<"Open data type:  "<<
                H5Fget_obj_count(id(),H5F_OBJ_DATATYPE)<<std::endl;
            std::cerr<<"Open attributes: "<<
                H5Fget_obj_count(id(),H5F_OBJ_ATTR)<<std::endl;
            H5Fflush(id(),H5F_SCOPE_GLOBAL);
            H5Fclose(id());
            H5Object::reset_id();
            H5garbage_collect();
        }

    }
    
    //-------------------------------------------------------------------------
    H5File H5File::open_file(const string &n,bool ro)
    {
        hid_t fid;
        
        //check if the file is a valid HDF5 file
        if(!H5Fis_hdf5(n.c_str()))
            throw pni::io::nx::nxfile_error(EXCEPTION_RECORD, 
                  "File ["+string(n)+"] is not an HDF5 file!\n\n"+
                  get_h5_error_string());

        hid_t acc_plist = H5Pcreate(H5P_FILE_ACCESS);
        if(acc_plist<0)
            throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD, 
                  "Cannot create file access property list for file "
                  "["+string(n)+"]!\n\n"+get_h5_error_string());

        //open the file in the appropriate mode
        if(ro)
        {
            fid = H5Fopen(n.c_str(),H5F_ACC_RDONLY,acc_plist);
            if(fid<0)
            {
                H5Pclose(acc_plist);
                throw pni::io::nx::nxfile_error(EXCEPTION_RECORD, 
                      "Error opening file "+string(n)+" in read only mode!\n\n"+
                      get_h5_error_string());
            }
        }
        else
        {
            fid = H5Fopen(n.c_str(),H5F_ACC_RDWR,acc_plist);
            if(fid<0)
            {
                H5Pclose(acc_plist);
                throw pni::io::nx::nxfile_error(EXCEPTION_RECORD,
                      "Error opening file "+ string(n)+
                      " in read/write mode!\n\n"+get_h5_error_string()); 
            }
        }

        //close property lists
        H5Pclose(acc_plist);
        H5File f(fid);

        return f;
    }


    //-------------------------------------------------------------------------
    H5File H5File::create_file(const string &n,bool overwrite,ssize_t ssize)
    {
        hid_t fid;

        //create property lists for file creation an access
        hid_t create_plist = H5Pcreate(H5P_FILE_CREATE);
        if(create_plist<0)
            throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD, 
                  "Cannot create file creation property list for file "
                  "["+string(n)+"]!\n\n"+get_h5_error_string());

        hid_t acc_plist = H5Pcreate(H5P_FILE_ACCESS);
        if(acc_plist<0)
            throw pni::io::nx::nxbackend_error(EXCEPTION_RECORD, 
                  "Cannot create file access property list for file "
                  "["+string(n)+"]!\n\n"+get_h5_error_string());

        if(ssize > 0)
            //enable splitting
            H5Pset_fapl_family(acc_plist,ssize*1024*1024,H5P_DEFAULT);

        if(overwrite)
        {
            fid = H5Fcreate(n.c_str(),H5F_ACC_TRUNC,create_plist,acc_plist);
            if(fid<0)
            {
                H5Pclose(acc_plist);
                H5Pclose(create_plist);
                pni::io::nx::nxfile_error error(EXCEPTION_RECORD,
                "Error create file "+string(n)+" in overwrite mode!\n\n"+
                get_h5_error_string());
                std::cerr<<error<<std::endl;
                throw error;
            }
        }
        else
        {
            fid = H5Fcreate(n.c_str(),H5F_ACC_EXCL,create_plist,acc_plist);
            if(fid<0)
            {
                H5Pclose(acc_plist);
                H5Pclose(create_plist);
                pni::io::nx::nxfile_error error(EXCEPTION_RECORD,
                "Error create file "+string(n)+" file most probably already "
                "exists - use overwrite!\n\n"+get_h5_error_string());
                std::cerr<<error<<std::endl;
                throw error;
            }
        }

        H5File f(fid);

        //in the end we need to set the HDF5 version to the correct
        //value
        unsigned major,minor,rel;
        H5get_libversion(&major,&minor,&rel);
        std::ostringstream vstring;
        vstring<<major<<"."<<minor<<"."<<rel;

        H5Attribute a = f.attr<string>("HDF5_version");
        string version(vstring.str());
        a.write(&version);
        a.close();

        //close file create and access property lists
        H5Pclose(create_plist);
        H5Pclose(acc_plist);

        return f;
    }

    //-------------------------------------------------------------------------
    void H5File::flush() const
    {
        if(is_valid()) H5Fflush(id(),H5F_SCOPE_LOCAL);
    }
    
    //-------------------------------------------------------------------------
    string H5File::path() const 
    {
        dbuffer<char> buffer;

        if(is_valid())
        {
            //if the object has already been created return this value
            hsize_t bsize;
            bsize = H5Fget_name(id(),NULL,1)+1;
            buffer.allocate(bsize);

            H5Fget_name(id(),const_cast<char *>(buffer.ptr()),bsize);
            string name(buffer.ptr());
            return name;
        }

        return string("");
    }

    //-------------------------------------------------------------------------
    string H5File::base() const
    {
        string p(H5File::path());

        
        //need to extract the the name information from the path
        size_t lpos = p.find_last_of("/");
        string base = "";
        if(lpos != p.npos) base = string(p,0,lpos+1);

        return base;
    }

    //-------------------------------------------------------------------------
    string H5File::name() const
    {
        string p(H5File::path());

        //need to extract the the name information from the path
        size_t lpos = p.find_last_of("/");
        string name = p;
        if(lpos != p.npos) name = string(p,lpos+1,p.size()-lpos+1);

        return name;
    }


    //-------------------------------------------------------------------------
    bool H5File::is_readonly() const
    {
        unsigned int stat;
        H5Fget_intent(id(),&stat);

        if(stat==H5F_ACC_RDWR) return false;
        return true;
    }

//end of namespace
}
}
}
}
