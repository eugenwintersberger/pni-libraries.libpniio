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

#include "H5Attribute.hpp"
#include "H5Exceptions.hpp"


namespace pni{
    namespace nx{
        namespace h5{
            //===============private methods===================================
            void H5Attribute::__set_space_type(){
                hid_t dspace_id = 0;
                hid_t dtype_id = 0;

                dspace_id = H5Aget_space(id());
                dtype_id  = H5Aget_type(id());

                //we can use this Ids to create new H5Objects from which 
                //the datatype and the dataspace can be constructed.
                _dspace = H5Dataspace(dspace_id);
                _dtype  = H5Datatype(dtype_id);
            }

            //===========constructors and destructors==========================
            //! implementation of the default constructor
            H5Attribute::H5Attribute():H5NamedObject(){
                //there is nothing we have to do here
            }

            //-----------------------------------------------------------------
            //implementation of the copy constructor
            H5Attribute::H5Attribute(const H5Attribute &o):H5NamedObject(o){
                //once the ID is set we can obtain the datatype and 
                //the data space
                __set_space_type();
            }

            //-----------------------------------------------------------------
            //implementation of the move constructor
            H5Attribute::H5Attribute(H5Attribute &&o)
                :H5NamedObject(std::move(o)){
                _dspace = std::move(o._dspace);
                _dtype  = std::move(o._dtype);
            }

            //-----------------------------------------------------------------
            H5Attribute::H5Attribute(const hid_t &id):H5NamedObject(id){
                __set_space_type();
            }

            //! destructor
            H5Attribute::~H5Attribute(){
                _dspace.close();
                _dtype.close();
            }

            //===============implementation of assignment operators============

            //! copy assignment operator
            H5Attribute &H5Attribute::operator=(const H5Attribute &a){
               if(this != &a){
                   (H5NamedObject &)(*this) = (H5NamedObject &)a;
                   __set_space_type();
               }
               return *this;
            }
            //! move assignment operator
            H5Attribute &H5Attribute::operator=(H5Attribute &&o){
                if(this != &o){
                    (H5NamedObject &)(*this) = std::move((H5NamedObject &&)o);
                    _dspace = std::move(o._dspace);
                    _dtype  = std::move(o._dtype);
                }
                return *this;
            }

            //=========implementation of inquery methods=======================
            const Shape &H5Attribute::shape() const{
                return _dspace.shape();
            }

            TypeID H5Attribute::type_id() const{
                return _dtype.type_id();
            }
            
            //-----------------------------------------------------------------
            //implementation of write from String
            void H5Attribute::write(const String &s) const{
                EXCEPTION_SETUP("void H5Attribute::write(const String &s) "
                        "const");

                H5Datatype mem_type = H5Datatype::create<String>();
                herr_t err = H5Awrite(id(),mem_type.id(),s.c_str());
                if(err < 0){
                    EXCEPTION_INIT(H5AttributeError,
                            "Error writing attribute data");
                    EXCEPTION_THROW();
                }
            }

            //-----------------------------------------------------------------
            //implementation to read to string
            void H5Attribute::read(String &s) const{
                EXCEPTION_SETUP("void H5Attribute::read(String &s) const");
                
                s.resize(_dspace.shape().size());
                H5Datatype mem_type = H5Datatype::create<String>();
                herr_t err = H5Aread(id(),mem_type.id(),(void *)s.c_str());
                if(err<0){
                    EXCEPTION_INIT(H5AttributeError,
                            "Error writing attribute!");
                    EXCEPTION_THROW();
                }
            }
           
            //-----------------------------------------------------------------
            String H5Attribute::read() const{
                String s;
                this->read(s);
                return s;
            }

        //end of namespace
        }
    }
}

