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
 * Implementation of a general named HDF5 object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <pni/utils/Buffer.hpp>

using namespace pni::utils;

#include "H5NamedObject.hpp"
#include "H5Exceptions.hpp"
#include "H5Group.hpp"
#include "H5Path.hpp"

namespace pni{
    namespace nx{
        namespace h5{

            //=============implementation of constructors and destructors======
            H5NamedObject::H5NamedObject():H5Object(){
            }

            //-----------------------------------------------------------------
            H5NamedObject::H5NamedObject(const H5NamedObject &o):H5Object(o){
            }

            //-----------------------------------------------------------------
            H5NamedObject::H5NamedObject(const H5Object &o):H5Object(o){

            }

            //-----------------------------------------------------------------
            H5NamedObject::H5NamedObject(H5NamedObject &&o)
                :H5Object(std::move(o)){

            }

            //-----------------------------------------------------------------
            H5NamedObject::H5NamedObject(H5Object &&o)
                :H5Object(std::move(o)){

            }

            //-----------------------------------------------------------------
            H5NamedObject::H5NamedObject(const hid_t &id):H5Object(id){
            }

            //-----------------------------------------------------------------
            H5NamedObject::~H5NamedObject(){

            }

            //===========implementation of assignment operators================

            H5NamedObject &H5NamedObject::operator=(const H5NamedObject &o){
                if(this == &o) return *this;

                H5Object::operator=(o);

                return *this;
            }

            //-----------------------------------------------------------------
            H5NamedObject &H5NamedObject::operator=(const H5Object &o){
                if(this == &o) return *this;

                H5Object::operator=(o);
                
                return *this;
            }

            //-----------------------------------------------------------------
            H5NamedObject &H5NamedObject::operator=(H5NamedObject &&o){
                if(this == &o) return *this;

                H5Object::operator=(std::move(o));

                return *this;
            }

            //-----------------------------------------------------------------
            H5NamedObject &H5NamedObject::operator=(H5Object &&o){
                if(this == &o) return *this;

                H5Object::operator=(std::move(o));

                return *this;
            }

            //================implementation of name operations================

            String H5NamedObject::name() const{
                String p = path();

                //if the path is empty return an empty string
                if(p.empty()) return p;

                if((p.size() == 1) && (p[0] == '/')) return p;

                //need to extract the the name information from the path
                size_t lpos = p.find_last_of("/");
                String name = p;
                if(lpos != p.npos){
                    name = String(p,lpos+1,p.size()-lpos+1);
                }

                return name;
            }
            
            //-----------------------------------------------------------------
            String H5NamedObject::base() const{
                String p(path());

                if(p.empty()) return p;

                //if the string is of size 1 and has
                //only one / return this
                String base;
                if((p.size() == 1) && (p[0] == '/')){
                    base = "/";
                    return base;
                }

                size_t lpos = p.find_last_of("/");
                if(lpos != p.npos){
                    //if the / has been found in the 
                    //first position we can simply return this
                    if(lpos == 0){
                        base = String("/");
                    }else{
                        //in all other cases a bit more work 
                        //is necessary
                        base = String(p,0,lpos+1);

                        //remove a trailing /
                        if(base[base.size()-1] == '/'){
                            base = String(base,0,base.size()-1);
                        }
                    }
                }

                return base;
            }

            //-----------------------------------------------------------------
            String H5NamedObject::path() const{
                EXCEPTION_SETUP("String H5NamedObject::path() const");
                Buffer<char> buffer;

                if(is_valid()){
                    //if the object has already been created return this value
                    hsize_t bsize;
                    bsize = H5Iget_name(id(),NULL,1)+1;
                    buffer.allocate(bsize);

                    H5Iget_name(id(),buffer.ptr(),bsize);
                    String name(buffer.ptr());
                    return name;
                }

                return String("");
            }

            //----------------------------------------------------------------
            /*
            H5Group H5NamedObject::parent() const
            {
                hid_t fid = H5Iget_file_id(id());
                H5Path path(base());
                hid_t gid = H5Gopen2(fid,"/",H5P_DEFAULT);
                H5Group g(H5NamedObject(gid));

                return g.open(base());

                H5Fclose(fid);

                //if there is nothing in the path we can return the root group
                if(path.size() == 0){
                    H5Group g(H5NamedObject(gid));
                    H5Gclose(gid);
                    return g;
                }

                hid_t oid = gid;
                for(String &name: path){
                    gid = H5Gopen2(oid,name.c_str(),H5P_DEFAULT);
                    H5Gclose(oid);
                    oid = gid;
                }

                H5Group g(H5NamedObject(gid)); 
                H5Gclose(gid);
                return g;
            }
            */


        //end of namespace
        }
    }
}
