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
 * Implementation of an HDF5 attribute object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#include "H5AttributeObject.hpp"
#include "H5Exceptions.hpp"



namespace pni{
    namespace nx{
        namespace h5{
            //===========implementation of private methods=====================
            herr_t H5AttributeObject::__get_attribute_names(hid_t locid,
                    const char *name, const H5A_info_t *info,void *data)
            {
                std::vector<String> *vector = (std::vector<String> *)data;
                vector->push_back(String(name));

                return 0;
            }

            //=======implementation of constructors and destructors============
            //implementation of the default constructor
            H5AttributeObject::H5AttributeObject():H5NamedObject(){
            }

            //-----------------------------------------------------------------
            //implementation of the copy constructor
            H5AttributeObject::H5AttributeObject(const H5AttributeObject &o):
                H5NamedObject(o){
            }

            //-----------------------------------------------------------------
            //implementation of the conversion constructor
            H5AttributeObject::H5AttributeObject(const H5Object &o):
                H5NamedObject(o){
            }

            //-----------------------------------------------------------------
            //implementation of the move constructor
            H5AttributeObject::H5AttributeObject(H5AttributeObject &&o):
                H5NamedObject(std::move(o)){
            }

            //-----------------------------------------------------------------
            //implementation of the move conversion constructor
            H5AttributeObject::H5AttributeObject(H5Object &&o):
                H5NamedObject(std::move(o)){
            }

            //-----------------------------------------------------------------
            //implementation of a constructor using an object ID to 
            //create the object.
            H5AttributeObject::H5AttributeObject(const hid_t&oid):
                H5NamedObject(oid){
            }

            //-----------------------------------------------------------------
            //implementation of the destructor
            H5AttributeObject::~H5AttributeObject(){
            }

            //=======implementation of assignment operators====================
            //implementation of copy assignment operator
            H5AttributeObject &H5AttributeObject::operator=(const
                    H5AttributeObject &o){
                if(this == &o) return *this;

                H5NamedObject::operator=(o);

                return *this;
            }

            //-----------------------------------------------------------------
            //implementation of copy conversion operator
            H5AttributeObject &H5AttributeObject::operator=(const H5Object &o)
            {
                if(this == &o) return *this;
                
                H5NamedObject::operator=(o);

                return *this;
            }

            //-----------------------------------------------------------------
            //implementation of move assignment operator
            H5AttributeObject &H5AttributeObject::operator=(H5AttributeObject
                    &&o)
            {
                if(this == &o) return *this;     
                
                H5NamedObject::operator=(std::move(o));

                return *this;
            }

            //-----------------------------------------------------------------
            //implementation of move conversion operator
            H5AttributeObject &H5AttributeObject::operator=(H5Object &&o){
                if(this == &o) return *this;

                H5NamedObject::operator=(std::move(o));
                return *this;
            }

            //=======implementation of attribute management methods===========


            //-----------------------------------------------------------------
            //implementation of the attribute open method
            H5Attribute H5AttributeObject::attr(const String &n) const {
                EXCEPTION_SETUP("H5Attribute H5AttributeObject::"
                        "open_attr(const String &n) const");

                hid_t aid = 0;
                if(H5Aexists(id(),n.c_str())<=0){
                    EXCEPTION_INIT(H5AttributeError,
                            "Attribute does not exist!");
                    EXCEPTION_THROW();
                }

                aid = H5Aopen(id(),n.c_str(),H5P_DEFAULT);
                if(aid < 0){
                    EXCEPTION_INIT(H5AttributeError,
                            "Error opening attribute!");
                    EXCEPTION_THROW();
                }
                H5Attribute a(aid);
                H5Aclose(aid);
                return a;
            }

            //------------------------------------------------------------------
            //get number of attributes
            size_t H5AttributeObject::nattr() const{
                H5O_info_t info;
                H5Oget_info(id(),&info);

                return info.num_attrs;
            }

            //------------------------------------------------------------------
            bool H5AttributeObject::has_attr(const String &n) const
            {
                EXCEPTION_SETUP("bool H5AttributeObject::"
                        "has_attr(const String &n) const");

                htri_t ret = H5Aexists(id(),n.c_str());
                if(ret >0 ){
                    return true;
                }else if(ret == 0){
                    return false;
                }else{
                    //something went wrong - throw an exception here
                    EXCEPTION_INIT(H5AttributeError,
                            "Error while checking for existance of attribute ["+
                            n+"]!");
                    EXCEPTION_THROW();
                }
            }

            //------------------------------------------------------------------
            void H5AttributeObject::del_attr(const String &n) const
            {
                EXCEPTION_SETUP("void H5AttributeObject::"
                        "del_attr(const String &n) const");

                herr_t err = H5Adelete(id(),n.c_str());
                if(err < 0){
                    EXCEPTION_INIT(H5AttributeError,
                            "Error deleteing attribute ["+n+"]!");
                    EXCEPTION_THROW();
                }

            }

            //------------------------------------------------------------------
            std::vector<String> H5AttributeObject::attr_names() const
            {
                EXCEPTION_SETUP("std::vector<String> H5AttributeObject::"
                        "attr_names() const");

                std::vector<String> names(0); 

                hsize_t n=0; 
                herr_t err = H5Aiterate2(id(),H5_INDEX_NAME,H5_ITER_NATIVE,&n,
                        H5AttributeObject::__get_attribute_names,(void *)&(names));
                if(err < 0){
                    EXCEPTION_INIT(H5AttributeError,
                            "Error obtaining attribute name list!");
                    EXCEPTION_THROW();
                }

                return names;
            }
                


        
        //end of namespace
        }
    }
}
