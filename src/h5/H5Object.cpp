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
 * Implementation of a general HDF5 Object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "H5Object.hpp"

namespace pni{
    namespace nx{
        namespace h5{
            //=================constrcutors and destructors====================
            H5Object::H5Object(const hid_t &id)
                :_id(id)
            {
                //if the id passed to the constructor is valid 
                //we need to increment the reference counter for this ID.
                //The reason is simply that somewhere outside there is 
                //still a handle to this ID.
                if(H5Iis_valid(_id)) H5Iinc_ref(_id);
            }
            
            //-----------------------------------------------------------------
            H5Object::H5Object()
                :_id(0)
            {
            }

            //-----------------------------------------------------------------
            H5Object::H5Object(const H5Object &o)
                :_id(o._id)
            {
                //need to increment the reference 
                //counter for this object
                if(H5Iis_valid(_id)) H5Iinc_ref(_id);
            }

            //-----------------------------------------------------------------
            H5Object::H5Object(H5Object &&o)
                :_id(o._id) 
            {
                o._id = 0;
                //since the id is removed from the original object we do not
                //have to care about the reference counter
            }
            
            //-----------------------------------------------------------------
            H5Object::~H5Object(){
                if(is_valid()) H5Oclose(id());
                _id = 0;
            }   


            //================assignment operators=============================
            //implementation of the copy assignment operator
            H5Object &H5Object::operator=(const H5Object &o){

                if(this == &o) return *this;

                close(); //close the actual object
                _id = o._id;

                //if the original object is valid we have to increment 
                //the reference counter for this id
                if(is_valid()) H5Iinc_ref(_id);

                return *this;
            }
        
            //-----------------------------------------------------------------
            //implementation of the move assignment operator
            H5Object &H5Object::operator=(H5Object &&o){

                if(this == &o) return *this;

                close(); //close the actual object
                _id = o._id;
                o._id = 0;

                //As this is a move operation we do not need to care
                //about the IDs reference. 

                return *this;
            }
           
            //=============basic manipulation methods==========================
            bool H5Object::is_valid() const {
                if(H5Iis_valid(_id)>0) return true;

                return false;
            }
    
            //-----------------------------------------------------------------
            void H5Object::close() {
                if(is_valid()) H5Oclose(_id);
                _id = 0;
            }
            
            //-----------------------------------------------------------------
            const hid_t &H5Object::id() const {
                return _id;
            }

            //-----------------------------------------------------------------
            H5ObjectType H5Object::object_type() const {
                H5I_type_t tid;

                tid = H5Iget_type(_id);
                switch(tid){
                    case H5I_FILE: return H5ObjectType::FILE;
                    case H5I_GROUP: return H5ObjectType::GROUP;
                    case H5I_DATASET: return H5ObjectType::DATASET;
                    case H5I_DATATYPE: return H5ObjectType::DATATYPE;
                    case H5I_DATASPACE: return H5ObjectType::DATASPACE;
                    case H5I_ATTR: return H5ObjectType::ATTRIBUTE;
                    default:
                        return H5ObjectType::BADID;

                };
            }



        }
    }
}
