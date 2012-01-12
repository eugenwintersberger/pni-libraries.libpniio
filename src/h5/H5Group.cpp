/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Implementation of an HDF5 group object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#include "H5Group.hpp"
#include "H5Dataset.hpp"
#include "H5Exceptions.hpp"


namespace pni{
    namespace nx{
        namespace h5{
            //========implementation of constructors and destructors=========== 
            //implementation of the default constructor
            H5Group::H5Group():H5AttributeObject(){
            }
            
            //-----------------------------------------------------------------
            //implementation of the copy constructor
            H5Group::H5Group(const H5Group &o):H5AttributeObject(o){
            }

            //-----------------------------------------------------------------
            //implementation of the copy conversion constructor
            H5Group::H5Group(const H5Object &o):H5AttributeObject(o){

            }

            //-----------------------------------------------------------------
            //implementation of the move constructor
            H5Group::H5Group(H5Group &&o):H5AttributeObject(std::move(o)){
            }

            //-----------------------------------------------------------------
            //implementation of the conversion move constructor
            H5Group::H5Group(H5Object &&o):H5AttributeObject(std::move(o)){

            }

            //-----------------------------------------------------------------
            //implementation of the standard constructor
            H5Group::H5Group(const String &name,const H5Group &parent){
                EXCEPTION_SETUP("H5Group::H5Group(const string &name,"
                        "const String &parent)");
                hid_t link_pl; //link creation property list
                hid_t cr_pl;   //creation property list

                //create link property list
                link_pl = H5Pcreate(H5P_LINK_CREATE);
                H5Pset_create_intermediate_group(link_pl,1);
                cr_pl = H5Pcreate(H5P_GROUP_CREATE);
                H5Pset_create_intermediate_group(cr_pl,1);

                hid_t gid = H5Gcreate2(parent.id(),name.c_str(),
                        link_pl,cr_pl,H5P_DEFAULT);

                if(gid<0){
                    String estr = "Error creating group ["+name+
                                  "] under ["+parent.path()+"!";
                    EXCEPTION_INIT(H5GroupError,estr);
                    EXCEPTION_THROW();
                }

                H5Object::id(gid);
            }

            //-----------------------------------------------------------------
            //implemenation of the destructor
            H5Group::~H5Group(){
            }

            //======implementation of assignment operators=====================
            //implementation of copy assignment
            H5Group &H5Group::operator=(const H5Group &o){
                if(this != &o){
                    (H5AttributeObject &)(*this) = (H5AttributeObject &)o;
                }
                return *this;
            }
            
            //-----------------------------------------------------------------
            //implementation of copy conversion assignment
            H5Group &H5Group::operator=(const H5Object &o){
                if(this != &o){
                    (H5AttributeObject &)(*this) = o;
                }
                return *this;
            }

            //-----------------------------------------------------------------
            //implementation of move assignment
            H5Group &H5Group::operator=(H5Group &&o){
                if(this != &o){
                    (H5AttributeObject &)(*this) = std::move((H5AttributeObject
                                &)o);
                }
                return *this;
            }
            
            //-----------------------------------------------------------------
            //implementation of move conversion assignment
            H5Group &H5Group::operator=(H5Object &&o){
                if(this != &o){
                    (H5AttributeObject &)(*this) = std::move(o);
                }
                return *this;
            }

            //=======implemenation of object creating methods==================
            //!create a multidimensional dataset
            H5Dataset H5Group::dataset(const String &n,const TypeID &tid,
                    const Shape &s,const Shape &ChunkShape){
                EXCEPTION_SETUP("H5Dataset H5Group::dataset(const String &n,"
                        "const TypeId &tid,const Shape &s,const Shape "
                        "&ChunkShape=Shape(0))");

                return H5Dataset(n,*this,tid,s,ChunkShape);


            }

            //! create a scalar dataset
            H5Dataset H5Group::dataset(const String &n,const TypeID &tid){
                EXCEPTION_SETUP("H5Dataset H5Group::dataset(const String &n,"
                        "const TypeId &tid)");
                Shape s(1);
                s.dim(0,0);
                Shape cs(1);
                s.dim(0,1);

                return H5Dataset(n,*this,tid,s,cs);
            }


            //! create group
            H5Group H5Group::group(const String &n){
                return H5Group(n,*this);
            }

            //-----------------------------------------------------------------
            H5Object H5Group::open(const String &n){
                return H5Object();
            }


        //end of namespace
        }
    }
}


