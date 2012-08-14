/*
 * NXFileH5Implementation.cpp
 *
 *  Created on: Jun 30, 2011
 *      Author: eugen
 */

#include "H5File.hpp"
#include "H5Attribute.hpp"
#include "H5Exceptions.hpp"

#include <sstream>

namespace pni{
namespace nx{
namespace h5{


    //=========Implementation fo constructors an destructors===================
    //implementation of the default constructor
    H5File::H5File():H5Group(){ }
   
    //-------------------------------------------------------------------------
    //implement constructor (protected) using an HDF5 ID object
    H5File::H5File(hid_t id):H5Group(id){ }

    //-------------------------------------------------------------------------
    //implementation of the move constructor
    H5File::H5File(H5File &&o):H5Group(std::move(o)){ }

    //-------------------------------------------------------------------------
    //implementation of copy constructor
    H5File::H5File(const H5File &o):H5Group(o) { } 

    //-------------------------------------------------------------------------
    //implementation of the destructor
    H5File::~H5File() 
    {
        if(is_valid()){
            /*
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

            */

            H5Fflush(id(),H5F_SCOPE_GLOBAL);
            H5Fclose(id());
            H5Object::id(0);
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
            /*
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

            */

            H5Fflush(id(),H5F_SCOPE_GLOBAL);
            H5Fclose(id());
            H5Object::id(0);
        }

    }
    
    //-------------------------------------------------------------------------
    H5File H5File::open_file(const String &n,bool ro)
    {

        hid_t fid;

        //check if the file is a valid HDF5 file
        if(!H5Fis_hdf5(n.c_str()))
            throw H5FileError(EXCEPTION_RECORD, 
                  "File ["+String(n)+"] is not an HDF5 file!");

        hid_t acc_plist = H5Pcreate(H5P_FILE_ACCESS);
        if(acc_plist<0)
            throw H5PropertyListError(EXCEPTION_RECORD, 
                  "Cannot create file access property list for file "
                  "["+String(n)+"]!");

        //open the file in the appropriate mode
        if(ro)
        {
            fid = H5Fopen(n.c_str(),H5F_ACC_RDONLY,acc_plist);
            if(fid<0)
            {
                H5Pclose(acc_plist);
                throw H5FileError(EXCEPTION_RECORD, 
                      "Error opening file "+String(n)+" in read only mode!");
            }
        }
        else
        {
            fid = H5Fopen(n.c_str(),H5F_ACC_RDWR,acc_plist);
            if(fid<0)
            {
                H5Pclose(acc_plist);
                throw H5FileError(EXCEPTION_RECORD,
                      "Error opening file "+ String(n)+" in read/write mode!"); 
            }
        }

        //close property lists
        H5Pclose(acc_plist);

        H5File f(fid);
        H5Fclose(fid);

        return f;
    }


    //-------------------------------------------------------------------------
    H5File H5File::create_file(const String &n,bool overwrite,ssize_t ssize)
    {
        hid_t fid;

        //create property lists for file creation an access
        hid_t create_plist = H5Pcreate(H5P_FILE_CREATE);
        if(create_plist<0)
            throw H5PropertyListError(EXCEPTION_RECORD, 
                  "Cannot create file creation property list for file "
                  "["+String(n)+"]!");

        hid_t acc_plist = H5Pcreate(H5P_FILE_ACCESS);
        if(acc_plist<0)
            throw H5PropertyListError(EXCEPTION_RECORD, 
                  "Cannot create file access property list for file "
                  "["+String(n)+"]!");

        if(ssize > 0)
            //enable splitting
            H5Pset_fapl_family(acc_plist,ssize*1024*1024,H5P_DEFAULT);

        if(overwrite)
        {
            fid = H5Fcreate(n.c_str(),H5F_ACC_TRUNC,create_plist,acc_plist);
            if(fid<0)
            {
                H5Pclose(acc_plist);
                throw H5FileError(EXCEPTION_RECORD,
                "Error create file "+String(n)+" in overwrite mode!");
            }
        }
        else
        {
            fid = H5Fcreate(n.c_str(),H5F_ACC_EXCL,create_plist,acc_plist);
            if(fid<0)
            {
                H5Pclose(acc_plist);
                throw H5FileError(EXCEPTION_RECORD,
                "Error create file "+String(n)+" file most probably already "
                "exists - use overwrite!");
            }
        }

        H5File f(fid);
        H5Fclose(fid);

        //in the end we need to set the HDF5 version to the correct
        //value
        unsigned major,minor,rel;
        H5get_libversion(&major,&minor,&rel);
        std::ostringstream vstring;
        vstring<<major<<"."<<minor<<"."<<rel;

        H5Attribute a = f.attr<String>("HDF5_version");
        a.write(String(vstring.str()));
        a.close();

        return f;
    }

    //-----------------------------------------------------------------
    void H5File::flush() const
    {
        if(is_valid()) H5Fflush(id(),H5F_SCOPE_LOCAL);
    }
    
    //-----------------------------------------------------------------
    String H5File::path() const {
        DBuffer<char> buffer;

        if(is_valid())
        {
            //if the object has already been created return this value
            hsize_t bsize;
            bsize = H5Fget_name(id(),NULL,1)+1;
            buffer.allocate(bsize);

            H5Fget_name(id(),const_cast<char *>(buffer.ptr()),bsize);
            String name(buffer.ptr());
            return name;
        }

        return String("");
    }

//end of namespace
}
}
}

