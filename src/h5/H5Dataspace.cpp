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
            //implementation of the copy constructor
            H5Dataspace::H5Dataspace(const H5Dataspace &o):H5Object(o){
                _maxdims = o._maxdims;
                _dims  = o._dims;
                _shape = o._shape;
            }

            //-----------------------------------------------------------------
            //implementation of the move conversion constructor
            H5Dataspace::H5Dataspace(const H5Object &o):H5Object(o){
                //now we have to set the shape object
                __set_buffers();
                __set_shape_object();
            }

            //-----------------------------------------------------------------
            //implementation of the move constructor
            H5Dataspace::H5Dataspace(H5Dataspace &&o):
                H5Object(std::move(o)){
                _maxdims = std::move(o._maxdims);
                _dims = std::move(o._dims);
                _shape = std::move(o._shape);
            }

            //-----------------------------------------------------------------
            //implementation of the move conversion constructor
            H5Dataspace::H5Dataspace(H5Object &&o):H5Object(std::move(o)){
                __set_buffers();
                __set_shape_object();
            }

            //-----------------------------------------------------------------
            H5Dataspace::H5Dataspace(const Shape &s,int extdim){
                EXCEPTION_SETUP("H5Dataspace::H5Dataspace(const Shape &s,"
                        "int extdim)");
                hid_t sid = 0;
                
                _dims.allocate(s.rank());
                _maxdims.allocate(s.rank());

                for(size_t i=0;i<s.rank();i++){
                    _dims[i] = s[i];
                    _maxdims[i] = s[i]; 
                }
                _maxdims[extdim] = H5S_UNLIMITED;
                
                sid = H5Screate_simple(s.rank(),_dims.ptr(),_maxdims.ptr());
                if(sid<0){
                    EXCEPTION_INIT(H5DataSpaceError,"Cannot create HDF5 dataspace!");
                    EXCEPTION_THROW();
                }

                H5Object::id(sid);
                __set_shape_object();
            }

            //-----------------------------------------------------------------
            H5Dataspace::H5Dataspace(const hid_t &tid):H5Object(tid){
                __set_buffers();
                __set_shape_object();
            }
    
            //-----------------------------------------------------------------
            H5Dataspace::~H5Dataspace(){
            }

            //===================Assignment operators==========================
            //implementation of the copy assignment operator
            H5Dataspace &H5Dataspace::operator=(const H5Dataspace &o){
                if(this != &o){
                    (H5Object &)(*this) = (H5Object &)o;
                    _dims  = o._dims;
                    _maxdims = o._maxdims;
                    _shape = o._shape;
                }

                return *this;
            }

            //-----------------------------------------------------------------
            //implementation of the copy conversion assignment operator
            H5Dataspace &H5Dataspace::operator=(const H5Object &o){
                if(this != &o){
                    (H5Object &)(*this) = o;
                    __set_buffers();
                    __set_shape_object();
                }
                return *this;
            }

            //-----------------------------------------------------------------
            //implementation of the move assignment operator
            H5Dataspace &H5Dataspace::operator=(H5Dataspace &&o){
                if(this != &o){
                    (H5Object &)(*this) = std::move((H5Object &&)o);
                    _dims  = std::move(o._dims);
                    _maxdims = std::move(o._maxdims);
                    _shape = std::move(o._shape);
                }

                return *this;
            }

            //-----------------------------------------------------------------
            //implementation of the move conversion operator
            H5Dataspace &H5Dataspace::operator=(H5Object &&o){
                if(this != &o){
                    (H5Object &)(*this) = std::move(o);
                    __set_buffers();
                    __set_shape_object();
                }
                return *this;
            }

            //===================Other methods=================================
            //implementation of is_scalar
            bool H5Dataspace::is_scalar() const {
                H5S_class_t type = H5Sget_simple_extent_type(id());
                if(type == H5S_SCALAR) return true;
                return false;
            }

            const Shape &H5Dataspace::shape() const {
                return _shape;
            }

            size_t H5Dataspace::rank() const {
                return H5Sget_simple_extent_ndims(id());
            }

            size_t H5Dataspace::dim(size_t i) const {
                return _shape.dim(i);
            }

            size_t H5Dataspace::size() const {
                return H5Sget_simple_extent_npoints(id());
            }

            size_t H5Dataspace::operator[](size_t i) const {
                return _shape.dim(i);
            }


            //====================private methods==============================
            //implementation of the shape method
            void H5Dataspace::__set_shape_object(){
                EXCEPTION_SETUP("Shape H5Dataspace::shape() const");

		        
                //obtain the rank of the data space
                if(is_scalar()){
                    _shape=Shape(0);
                    return;
                }

                _shape.rank(rank());
                

                for(size_t i=0;i<rank();i++) _shape.dim(i,(size_t)_dims[i]);

            }

            //implementation of the buffer allocation routine
            void H5Dataspace::__set_buffers(){
                if(!is_scalar()){
                    _maxdims.allocate(rank());
                    _dims.allocate(rank());
                    H5Sget_simple_extent_dims(id(),_dims.ptr(),_maxdims.ptr());
                }
            }

        
        //end of namespace
        }
    }
}
            
