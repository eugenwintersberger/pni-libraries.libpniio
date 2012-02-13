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


            //=========Implementation fo constructors an destructors===========
            //implementation of the default constructor
            H5File::H5File():H5Group(){
                EXCEPTION_SETUP("H5File::H5File(");
            }

            H5File::H5File(hid_t id):H5Group(id){

            }

            //-----------------------------------------------------------------
            //implementation of the move constructor
            H5File::H5File(H5File &&o):H5Group(std::move(o)){

            }

            //-----------------------------------------------------------------
            //implementation of the destructor
            H5File::~H5File() {
                close();
            }

            //=================Implementation of assignment operators==========
            H5File &H5File::operator=(H5File &&o){
                (H5Group &)(*this) = std::move((H5Group &)o);
                return *this;
            }


            //=============Implementation of file specific methods=============
            void H5File::close(){
                //check for open objects in the file
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
                }

            }
            
            //-----------------------------------------------------------------
            H5File H5File::open_file(const String &n,bool ro){
                EXCEPTION_SETUP("H5File H5File::open_file(const String &n,"
                        "bool ro)");

                hid_t fid;

                //check if the file is a valid HDF5 file
                if(!H5Fis_hdf5(n.c_str())){
                    EXCEPTION_INIT(H5FileError,"File ["+String(n)+
                            "] is not an HDF5 file!");
                    EXCEPTION_THROW();
                }

                hid_t acc_plist = H5Pcreate(H5P_FILE_ACCESS);
                if(acc_plist<0){
                    EXCEPTION_INIT(H5PropertyListError,"Cannot create file "
                            "access property list for file ["+String(n)+"]!");
                    EXCEPTION_THROW();
                }

                //open the file in the appropriate mode
                if(ro){
                    fid = H5Fopen(n.c_str(),H5F_ACC_RDONLY,acc_plist);
                    if(fid<0){
                        EXCEPTION_INIT(H5FileError,"Error opening file "+
                                String(n)+" in read only mode!");
                        H5Pclose(acc_plist);
                        EXCEPTION_THROW();
                    }
                }else{
                    fid = H5Fopen(n.c_str(),H5F_ACC_RDWR,acc_plist);
                    if(fid<0){
                        EXCEPTION_INIT(H5FileError,"Error opening file "+
                                String(n)+" in read/write mode!");
                        H5Pclose(acc_plist);
                        EXCEPTION_THROW();
                    }
                }

                //close property lists
                H5Pclose(acc_plist);

                H5File f(fid);
                H5Fclose(fid);

                return f;

            }


            //-----------------------------------------------------------------
            H5File H5File::create_file(const String &n,bool overwrite,ssize_t ssize){
                EXCEPTION_SETUP("void H5File::create(const String &n,"
                        "bool overwrite)");
                hid_t fid;

                //create property lists for file creation an access
                hid_t create_plist = H5Pcreate(H5P_FILE_CREATE);
                if(create_plist<0){
                    EXCEPTION_INIT(H5PropertyListError,"Cannot create file "
                            "creation property list for file ["+String(n)+"]!");
                    EXCEPTION_THROW();
                }

                hid_t acc_plist = H5Pcreate(H5P_FILE_ACCESS);
                if(acc_plist<0){
                    EXCEPTION_INIT(H5PropertyListError,"Cannot create file "
                            "access property list for file ["+String(n)+"]!");
                    EXCEPTION_THROW();
                }

                if(ssize > 0){
                    //enable splitting
                    H5Pset_fapl_family(acc_plist,ssize*1024*1024,H5P_DEFAULT);
                }

                if(overwrite){
                    fid = H5Fcreate(n.c_str(),H5F_ACC_TRUNC,create_plist,acc_plist);
                    if(fid<0){
                        EXCEPTION_INIT(H5FileError,"Error create file "+
                                String(n)+" in overwrite mode!");
                        H5Pclose(acc_plist);
                        EXCEPTION_THROW()
                    }
                }else{
                    fid = H5Fcreate(n.c_str(),H5F_ACC_EXCL,create_plist,acc_plist);
                    if(fid<0){
                        EXCEPTION_INIT(H5FileError,"Error create file "+
                                String(n)+" file most probably already "
                                "exists - use overwrite!");
                        H5Pclose(acc_plist);
                        EXCEPTION_THROW();
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
            void H5File::flush() const{
                if(is_valid()) H5Fflush(id(),H5F_SCOPE_LOCAL);
            }
            
            //-----------------------------------------------------------------
            String H5File::path() const {
                EXCEPTION_SETUP("String H5File::path() const");
                Buffer<char> buffer;

                if(is_valid()){
                    //if the object has already been created return this value
                    hsize_t bsize;
                    bsize = H5Fget_name(id(),NULL,1)+1;
                    buffer.allocate(bsize);

                    H5Fget_name(id(),buffer.ptr(),bsize);
                    String name(buffer.ptr());
                    return name;
                }

                return String("");
            }

//end of namespace
}
}
}

