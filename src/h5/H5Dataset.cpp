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
 * Created on: Jan 12, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <pni/utils/Buffer.hpp>

#include "H5Dataset.hpp"
#include "H5ObjectType.hpp"
#include "H5Exceptions.hpp"


namespace pni{
    namespace nx{
        namespace h5{
            
            //===implementation of constructors and destructors================
            //implementation of the default constructor
            H5Dataset::H5Dataset():H5AttributeObject(){
            }

            //-----------------------------------------------------------------
            //implementation of the copy constructor
            H5Dataset::H5Dataset(const H5Dataset &o):H5AttributeObject(o){
                _space = o._space;
                _type  = o._type;
            }

            //-----------------------------------------------------------------
            //implementation of the copy conversion constructor
            H5Dataset::H5Dataset(const H5Object &o):H5AttributeObject(o){
                EXCEPTION_SETUP("H5Dataset::H5Dataset(const H5Object &o)");

                //check if the type is ok for conversion
                if(type() != H5ObjectType::DATASET){
                    EXCEPTION_INIT(H5DataSetError,"Object is not a dataset!");
                    EXCEPTION_THROW();
                }

                //copy the datatype and dataspace
                _space = H5Dataspace(H5Dget_space(id()));
                _type  = H5Datatype(H5Dget_type(id()));

            }

            //-----------------------------------------------------------------
            //implementation of the move constrcutor
            H5Dataset::H5Dataset(H5Dataset &&o):H5AttributeObject(std::move(o)){
                _space = std::move(o._space);
                _type  = std::move(o._type);
            }

            //-----------------------------------------------------------------
            //implementation of the move conversion constructor
            H5Dataset::H5Dataset(H5Object &&o):H5AttributeObject(std::move(o)){
                EXCEPTION_SETUP("H5Dataset::H5Dataset(H5Object &&o)");

                if(type() != H5ObjectType::DATASET){
                    EXCEPTION_INIT(H5DataSetError,"Object is not a dataset!");
                    EXCEPTION_THROW();
                }

                //move datatype and data space
                _space = H5Dataspace(H5Dget_space(id()));
                _type  = H5Datatype(H5Dget_type(id()));
            }

            //-----------------------------------------------------------------
            //! constructor 
            H5Dataset::H5Dataset(const String &n, const H5Group &g, const TypeID &tid,
                    const Shape &s,const Shape &cs){
                EXCEPTION_SETUP("H5Dataset::H5Dataset(const String &n, "
                        "const H5Group &g, const TypeID &tid,const Shape &s,"
                        "const Shape &cs)");

                //create the datat type
                _type = H5Datatype(tid);
                
                //create the data space
                _space = H5Dataspace(s);

                //create the link creation property list
                hid_t lpl = H5Pcreate(H5P_LINK_CREATE);
                H5Pset_create_intermediate_group(lpl,1);
                
                //create the dataset creation property list
                hid_t cpl = H5Pcreate(H5P_DATASET_CREATE);
                if(cs.rank() != 0){
                    H5Pset_layout(cpl,H5D_CHUNKED);
                    Buffer<hsize_t> cdims(cs.rank());
                    for(size_t i=0;i<cs.rank();i++) cdims[i]=cs[i];
                    H5Pset_chunk(cpl,cs.rank(),cdims.ptr());
                }

                //create the datase
                hid_t did = H5Dcreate2(g.id(),n.c_str(),_type.id(),_space.id(),
                        lpl,cpl,H5P_DEFAULT);
                if(did<0){
                    String estr = "Cannot create dataset ["+n+
                        "] below ["+path()+"!";
                    EXCEPTION_INIT(H5DataSetError,estr);
                    EXCEPTION_THROW();
                }

                H5Object::id(did);
                //construction done - close property lists
                H5Pclose(lpl);
                H5Pclose(cpl);
            }

            //-----------------------------------------------------------------
            //implementation of the default destructor 
            H5Dataset::~H5Dataset(){
                _space.close();
                _type.close();
            }

            //=========implementation of the assignment operators==============


        //end of namespace
        }
    }
}

