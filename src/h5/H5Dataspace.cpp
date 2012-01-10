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
 * Implementation of a general HDF5 Dataspace object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#include <pni/utils/Shape.hpp>
#include <pni/utils/Buffer.hpp>

using namespace pni::utils;

#include "H5Dataspace.hpp"
#include "H5Exceptions.hpp"

namespace pni{
    namespace nx {
        namespace h5 {
            //=============Constructors and destructors========================
            H5Dataspace::H5Dataspace(){
                hid_t sid = H5Screate(H5S_SCALAR);
                H5Object::id(sid);
                _shape.rank(0);
            }

            //-----------------------------------------------------------------
            H5Dataspace::H5Dataspace(const H5Dataspace &o):H5Object(o){
                _shape = o._shape;
            }

            //-----------------------------------------------------------------
            H5Dataspace::H5Dataspace(H5Dataspace &&o):
                H5Object(std::move(o)){
                    _shape = std::move(o._shape);
            }

            //-----------------------------------------------------------------
            H5Dataspace::H5Dataspace(const Shape &s,const Shape &maxshape,
                                     int extdim){
                EXCEPTION_SETUP("H5Dataspace::H5Dataspace(const Shape &s,"
                        "const Shape &maxshape, int extdim)");
                hid_t sid = 0;
                Buffer<hsize_t> dims;
                Buffer<hsize_t> maxdims;
                
                dims.allocate(s.rank());

                for(size_t i=0;i<s.rank();i++) dims[i] = s[i];

                if((maxshape.rank()!=0)&&(maxshape.rank()==s.rank())){
                    maxdims.allocate(s.rank());
                    for(size_t i=0;i<s.rank();i++) maxdims[i] = maxshape[i];
                }else{
                    EXCEPTION_INIT(ShapeMissmatchError,"Rank of Shape and max."
                            "Shape do not match!");
                    EXCEPTION_THROW();
                }

                
                sid = H5Screate_simple(s.rank(),dims.ptr(),maxdims.ptr());
                if(sid<0){
                    EXCEPTION_INIT(H5DataSpaceError,"Cannot create HDF5 dataspace!");
                    EXCEPTION_THROW();
                }

                H5Object::id(sid);
                __set_shape_object();
            }
    
            //-----------------------------------------------------------------
            H5Dataspace::~H5Dataspace(){
            }

            //===================Assignment operators==========================
            H5Dataspace &H5Dataspace::operator=(const H5Dataspace &o){
                if(this != &o){
                    (H5Object &)(*this) = (H5Object &)o;
                    _shape = o._shape;
                }

                return *this;
            }

            //-----------------------------------------------------------------
            H5Dataspace &H5Dataspace::operator=(H5Dataspace &&o){
                if(this != &o){
                    (H5Object &)(*this) = std::move((H5Object &&)o);
                    _shape = std::move(o._shape);
                }

                return *this;
            }

            //===================Other methods=================================
            //implementation of is_scalar
            bool H5Dataspace::is_scalar() const {
                if(H5Sis_simple(id())) return false;

                return true;
            }

            const Shape &H5Dataspace::shape() const {
                return _shape;
            }

            size_t H5Dataspace::rank() const {
                return _shape.rank();
            }

            size_t H5Dataspace::dim(size_t i) const {
                return _shape.dim(i);
            }

            size_t H5Dataspace::size() const {
                return _shape.size();
            }

            size_t H5Dataspace::operator[](size_t i) const {
                return _shape.dim(i);
            }


            //====================private methods==============================
            //implementation of the shape method
            void H5Dataspace::__set_shape_object(){
                EXCEPTION_SETUP("Shape H5Dataspace::shape() const");

	            UInt32 rank;
	            Buffer<hsize_t> dims;

                if(is_scalar()){
                    _shape=Shape(0);
                    return;
                }


		        //obtain the rank of the data space
		        rank = H5Sget_simple_extent_ndims(id());
                if(rank < 0){
                    EXCEPTION_INIT(H5DataSpaceError,"Cannot obtain data-space rank!");
                    EXCEPTION_THROW();
                }
                _shape.rank(rank);
                
                dims.allocate(rank);
                //obtain the number of elements along each dimension of the data-space
                rank = H5Sget_simple_extent_dims(id(),dims.ptr(),NULL);
                if(rank < 0){
                    EXCEPTION_INIT(H5DataSpaceError,
                                  "Cannot obtain data-space dimensions!");
                    EXCEPTION_THROW();
                }

                for(size_t i=0;i<rank;i++) _shape.dim(i,(size_t)dims[i]);

            }

        
        //end of namespace
        }
    }
}
            
