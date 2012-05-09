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
            //====================private methods==============================

            //implementation of the buffer allocation routine
            void H5Dataspace::__set_buffers(){
                if(!is_scalar()){
                    _maxdims.allocate(rank());
                    _dims.allocate(rank());
                    H5Sget_simple_extent_dims(id(),_dims.ptr(),_maxdims.ptr());
                }
            }

            //-----------------------------------------------------------------
            void H5Dataspace::__create_dataspace(){
                EXCEPTION_SETUP("void H5Dataspace::__create_dataspace()");

                herr_t err = H5Sset_extent_simple(id(),
                        _dims.size(),
                        _dims.ptr(),
                        _maxdims.ptr()
                        );
                                
                if(err<0){
                    EXCEPTION_INIT(H5DataSpaceError,"Cannot create HDF5 dataspace!");
                    EXCEPTION_THROW();
                }
            }
            //=============Constructors and destructors========================
            H5Dataspace::H5Dataspace():H5Object(H5Screate(H5S_SCALAR))
            {
                //the dataspace is initialized as a scalar dataspace
            }

            //-----------------------------------------------------------------
            //implementation of the copy constructor
            H5Dataspace::H5Dataspace(const H5Dataspace &o):H5Object(o),
                _maxdims(o._maxdims),_dims(o._dims)
            {

            }

            //-----------------------------------------------------------------
            //implementation of the copy conversion constructor
            H5Dataspace::H5Dataspace(const H5Object &o):H5Object(o){
                //now we have to set the shape object
                __set_buffers();
            }

            //-----------------------------------------------------------------
            //implementation of the move constructor
            H5Dataspace::H5Dataspace(H5Dataspace &&o):
                H5Object(std::move(o)),
                _maxdims(std::move(o._maxdims)),
                _dims(std::move(o._dims))
            {

            }

            //-----------------------------------------------------------------
            //implementation of the move conversion constructor
            H5Dataspace::H5Dataspace(H5Object &&o):H5Object(std::move(o)){
                //this is a perfekt application for the __set_buffers() method
                __set_buffers();
            }


            //-----------------------------------------------------------------
            H5Dataspace::H5Dataspace(const Shape &s):
                H5Object(H5Screate(H5S_SCALAR)),
                _maxdims(s.rank()),
                _dims(s.rank())
            {
                EXCEPTION_SETUP("H5Dataspace::H5Dataspace(const Shape &s,"
                        "int extdim)");
                
                //set buffers
                for(size_t i=0;i<s.rank();i++){
                    _maxdims[i] = s[i];
                    _dims[i] = s[i];
                }

                //set dataspace to simple
                __create_dataspace();    
            }

            //----------------------------------------------------------------
            //construct dataspace form initializer list
            H5Dataspace::H5Dataspace(const std::initializer_list<hsize_t> &list):
                H5Object(H5Screate(H5S_SCALAR)),
                _maxdims(list),
                _dims(list)
                
            {
                EXCEPTION_SETUP("H5Datspace::"
                        "H5Dataspace(std::initializer_list list)");
                
                __create_dataspace();
            }

            //-----------------------------------------------------------------
            H5Dataspace::H5Dataspace(const Shape &s,const Shape &ms):
                H5Object(H5Screate(H5S_SCALAR)),
                _maxdims(ms.rank()),
                _dims(s.rank())
            {
                EXCEPTION_SETUP("H5Dataspace::H5Dataspace(const Shape &s,"
                        "const Shape &ms)");

                //check if the ranks of the shapes is equal
                if(s.rank() != ms.rank()){
                    EXCEPTION_INIT(ShapeMissmatchError,"Initial shape and "
                            "maximum shape have different rank");
                    EXCEPTION_THROW();
                }

                //set buffer values
                for(size_t i=0;i<s.rank();i++){
                    _dims[i] = s[i];
                    _maxdims[i] = ms[i];
                }

                //resize the dataspace to a simple one
                __create_dataspace();
            }

            //-----------------------------------------------------------------
            //construction from two initializer lists
            H5Dataspace::H5Dataspace(const std::initializer_list<hsize_t> &dlist,
                                     const std::initializer_list<hsize_t> &mlist)
                :H5Object(H5Screate(H5S_SCALAR)),
                 _maxdims(mlist),
                 _dims(dlist)
            {
                EXCEPTION_SETUP("H5Dataspace::H5Dataspace("
                        "hstd::initializer_list<hsize_t> dlist,"
                        "std::initializer_list<hsize_t> mlist)");

                //check if the sizes of the two initializer lists match
                if(mlist.size() != dlist.size()){
                    EXCEPTION_INIT(SizeMissmatchError,
                        "Iinitializer list sizes do not match!");
                    EXCEPTION_THROW();
                }

                //finally resize the dataspace
                __create_dataspace();
            }

            //-----------------------------------------------------------------
            H5Dataspace::H5Dataspace(const hid_t &tid):H5Object(tid){
                __set_buffers();
            }
    
            //-----------------------------------------------------------------
            H5Dataspace::~H5Dataspace(){
                if(is_valid()) H5Sclose(id());
                //reset the object ID
                H5Object::id(0);
            }

            //===================Assignment operators==========================
            //implementation of the copy assignment operator
            H5Dataspace &H5Dataspace::operator=(const H5Dataspace &o){
                if (this == &o) return *this;

                H5Object::operator=(o);
                _dims  = o._dims;
                _maxdims = o._maxdims;

                return *this;
            }

            //-----------------------------------------------------------------
            //implementation of the copy conversion assignment operator
            H5Dataspace &H5Dataspace::operator=(const H5Object &o){
                if(this == &o) return *this;
                    
                H5Object::operator=(o);
                __set_buffers();

                return *this;
            }

            //-----------------------------------------------------------------
            //implementation of the move assignment operator
            H5Dataspace &H5Dataspace::operator=(H5Dataspace &&o){
                if(this == &o) return *this;

                H5Object::operator=(std::move(o));
                _dims  = std::move(o._dims);
                _maxdims = std::move(o._maxdims);

                return *this;
            }

            //-----------------------------------------------------------------
            //implementation of the move conversion operator
            H5Dataspace &H5Dataspace::operator=(H5Object &&o){
                if(this == &o) return *this;

                H5Object::operator=(std::move(o));
                __set_buffers();

                return *this;
            }

            //===================Other methods=================================
            //implementation of is_scalar
            bool H5Dataspace::is_scalar() const {
                H5S_class_t type = H5Sget_simple_extent_type(id());
                if(type == H5S_SCALAR) return true;
                return false;
            }

            //-----------------------------------------------------------------
            Shape H5Dataspace::shape() const {
                if(is_scalar()) return Shape();

                std::vector<size_t> d(rank());
                for(size_t i=0;i<rank();i++) d[i]= _dims[i];

                return Shape(d);
            }

            //-----------------------------------------------------------------
            Shape H5Dataspace::maxshape() const {
                if(is_scalar()) return Shape();

                std::vector<size_t> d(rank());
                for(size_t i=0;i<rank();i++) d[i] = _maxdims[i];

                return Shape(d);
            }

            //-----------------------------------------------------------------
            size_t H5Dataspace::rank() const {
                //return 0 if the dataspace is scalar
                if(is_scalar()) return 0;

                //return the number of dimension if the dataspace is simple
                return H5Sget_simple_extent_ndims(id());
            }

            //-----------------------------------------------------------------
            size_t H5Dataspace::dim(size_t i) const {
                //return 0 if the dataspace is scalar
                if(is_scalar()) return 0;

                //return the number of elements along dimension i if the 
                //dataspace is simple
                return _dims[i];
            }

            //-----------------------------------------------------------------
            size_t H5Dataspace::max_dim(size_t i) const {
                //return 0 if the dataspace is scalar
                if(is_scalar()) return 0;

                //return the maximum number of elements along i if the 
                //dataspace is simple
                return _maxdims[i];
            }

            //-----------------------------------------------------------------
            size_t H5Dataspace::size() const {
                //return 1 if the dataspace is scalar
                if(is_scalar()) return 1;

                //return the number of elements in the dataspace if the 
                //dataspcae is simple
                return H5Sget_simple_extent_npoints(id());
            }

            //-----------------------------------------------------------------
            size_t H5Dataspace::operator[](size_t i) const {
                return dim(i);
            }

            //-----------------------------------------------------------------
            void H5Dataspace::close(){
                if(is_valid()) H5Sclose(id());
            }

            //-----------------------------------------------------------------
            void H5Dataspace::resize(const Shape &s){
                EXCEPTION_SETUP("void H5Datspace::resize(const Shape &s)");
                
                _dims.allocate(s.rank());
                _maxdims.allocate(s.rank());

                for(size_t i=0;i<s.rank();i++){
                    _dims[i] = s[i];
                    _maxdims[i] = s[i];
                }

                __create_dataspace();
            }

            //-----------------------------------------------------------------
            void H5Dataspace::resize(const std::initializer_list<hsize_t> &list){
                EXCEPTION_SETUP("void H5Dataspace::"
                        "resize(std::initializer_list<hsize_t> list)");

                _dims = list;
                _maxdims = list;

                __create_dataspace();
            }

            //-----------------------------------------------------------------
            void H5Dataspace::resize(const Shape &s,const Shape &ms){
                EXCEPTION_SETUP("void H5Dataspace::resize(const Shape &s,"
                        "const Shape &ms)");

                if(s.rank() != ms.rank()){
                    EXCEPTION_INIT(ShapeMissmatchError,"Shape and Max. Shape"
                            " are not of same rank!");
                    EXCEPTION_THROW();
                }

                _dims.allocate(s.rank());
                _maxdims.allocate(ms.rank());
                for(size_t i=0;i<s.rank();i++){
                    _dims[i] = s[i];
                    _maxdims[i] = ms[i];
                }

                __create_dataspace();
            }

            //------------------------------------------------------------------
            void H5Dataspace::resize(const std::initializer_list<hsize_t> &dlist,
                                     const std::initializer_list<hsize_t> &mlist)
            {
                EXCEPTION_SETUP("void H5Dataspace::resize("
                        "std::initializer_list<hsize_t> dlist,"
                        "std::initializer_list<hsize_t> mlist)");

                if(dlist.size() != mlist.size()){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Sizes of initializer lists do not match!");
                    EXCEPTION_THROW();
                }

                _dims = dlist;
                _maxdims = mlist;

                __create_dataspace();
            }

            //------------------------------------------------------------------
            void H5Dataspace::grow(size_t dim,size_t ext){
                EXCEPTION_SETUP("void H5Dataspace::"
                        "grow(size_t dim,size_t ext) const");

                if(dim >= rank()){
                    EXCEPTION_INIT(IndexError,"Index larger than rank!");
                    EXCEPTION_THROW();
                }

                _dims[dim] += ext;
                __create_dataspace();
            }



            //======================operators===================================
            std::ostream &operator<<(std::ostream &o,const H5Dataspace &s){
                o<<"HDF5 Dataspace: "<<s.rank()<<" dimensions"<<std::endl;
                o<<"act. # of elements: ( ";
                for(size_t i=0;i<s.rank();i++){
                    o<<s._dims[i]<<" ";
                }
                o<<")";

                return o;
            }

        
        //end of namespace
        }
    }
}
            
