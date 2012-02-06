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
 * Implementation of a HDF5 selection class.
 *
 * Created on: Jan 16, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <cstdarg>
#include "H5Selection.hpp"
#include "H5Exceptions.hpp"


namespace pni{
    namespace nx{
        namespace h5{
            //==========Implementation of private methods=======================
            void H5Selection::__update_shape(){
                for(size_t i=0;i<_shape.rank();i++) _shape.dim(i,_counts[i]);
            }

            //------------------------------------------------------------------
            void H5Selection::__update_dataspace(){
                _sspace = H5Dataspace(_shape);
            }

            //==============Implementation of constructors and destructors======
            //implementation of the default constructor
            /*H5Selection::H5Selection(){
             
            }*/

            //------------------------------------------------------------------
            //implementation of the copy constructor
            H5Selection::H5Selection(const H5Selection &o)
                :_shape(o._shape),_sspace(o._sspace),_offset(o._offset),
                 _stride(o._stride),_counts(o._counts),_dataset(o._dataset)
            {
            }

            //------------------------------------------------------------------
            //implementation of the move constructor
            H5Selection::H5Selection(H5Selection &&o)
                :_shape(std::move(o._shape)),_sspace(std::move(o._sspace)),
                 _offset(std::move(o._offset)),_stride(std::move(o._stride)),
                 _counts(std::move(o._counts)),
                 _dataset(o._dataset)
            {
            }

            
            //------------------------------------------------------------------
            //implementation of the shape constructor
            H5Selection::H5Selection(const H5Dataset &ds,const Shape &s,
                    size_t offset,size_t stride)
                :_dataset(&ds)
            {
                _offset.allocate(s.rank());
                _stride.allocate(s.rank());
                _counts.allocate(s.rank());

                //set offset and stride
                _offset = offset;
                _stride = stride;
                for(size_t i=0;i<s.rank();i++) _counts[i] = s[i];

                _shape = s;
                __update_shape();
                __update_dataspace();
            }

            //------------------------------------------------------------------
            //implementation of the destructor
            H5Selection::~H5Selection(){
                _sspace.close();
                _offset.free();
                _stride.free();
                _counts.free();
                _dataset = nullptr;

            }

            //==============Implementation of assignment operators==============
            //implementation of the copy assignment operator
            H5Selection &H5Selection::operator=(const H5Selection &o){
                EXCEPTION_SETUP("H5Selection &H5Selection::operator="
                        "(const H5Selection &o)");

                if(this != &o){
                    _sspace  = o._sspace;
                    _stride  = o._stride;
                    _offset  = o._offset;
                    _counts  = o._counts;
                    _shape   = o._shape;
                    _dataset = o._dataset;
                }

                return *this;
            }

            //------------------------------------------------------------------
            //implementation of the move assignment operator
            H5Selection &H5Selection::operator=(H5Selection &&o){
                EXCEPTION_SETUP("H5Selection &H5Selection::operator="
                        "(H5Selection &&o)");

                //original names 
                if(this != &o){
                    _sspace  = std::move(o._sspace);
                    _stride  = std::move(o._stride);
                    _offset  = std::move(o._offset);
                    _counts  = std::move(o._counts);
                    _shape   = std::move(o._shape);
                    _dataset = o._dataset;
                    o._dataset = nullptr;
                }
                return *this;
            }

            //========implementation of inquery methods=========================
            //get size
            size_t H5Selection::size() const{
                return _shape.size();
            }

            //------------------------------------------------------------------
            //get number of dimensions
            size_t H5Selection::rank() const {
                return _shape.rank();
            }

            //------------------------------------------------------------------
            //get shape
            const Shape &H5Selection::shape() const {
                return _shape;
            }

            //------------------------------------------------------------------
            //return reference to the dataspace
            const H5Dataspace &H5Selection::space() const{
                return _sspace;
            }

            
            //=================implementation of modifier methods===============
            //access single offset values
            hsize_t &H5Selection::offset(size_t i){
                return _offset[i];
            }

            //------------------------------------------------------------------
            //access single offset value
            hsize_t H5Selection::offset(size_t i) const {
                return _offset[i];
            }

            //------------------------------------------------------------------
            //set all offset values in a single call
            void H5Selection::offset(size_t i,hsize_t o) {
                _offset[i] = o;
            }

            //------------------------------------------------------------------
            const Buffer<hsize_t> &H5Selection::offset() const {
                return _offset;
            }

            //------------------------------------------------------------------
            hsize_t &H5Selection::stride(size_t i){
                return _stride[i];
            }

            //------------------------------------------------------------------
            hsize_t H5Selection::stride(size_t i) const{
                return _stride[i];
            }

            //------------------------------------------------------------------
            void H5Selection::stride(size_t i,hsize_t s) {
                _stride[i] = s;
            }

            //------------------------------------------------------------------
            const Buffer<hsize_t> &H5Selection::stride() const {
                return _stride;
            }

            //------------------------------------------------------------------
            hsize_t &H5Selection::count(size_t i){
                return _counts[i];
            }

            //------------------------------------------------------------------
            hsize_t H5Selection::count(size_t i) const{
                return _counts[i];
            }

            //------------------------------------------------------------------
            void H5Selection::count(size_t i,hsize_t c) {
                _counts[i] = c;
                __update_shape();
                __update_dataspace();
            }

            //-----------------------------------------------------------------
            const Buffer<hsize_t> &H5Selection::count() const {
                return _counts;
            }

            //=============specializations of the IO methods===================
            
            void H5Selection::write(const String &value){
                EXCEPTION_SETUP("template<> void H5Selection::"
                        "write(const String &value)");

                std::cout<<"use string writer ...."<<std::endl;

                if(this->size()!=1){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Selection is not scalar!");
                    EXCEPTION_THROW();
                }

                const char *ptr = value.c_str();

                herr_t err;
                //select the proper memory data type
                H5Datatype mem_type = H5Datatype(H5Dget_type(_dataset->id()));
                
                //set selection to the file datasets original dataset
                //==========>here we would have to lock the dataset object 
                err = H5Sselect_hyperslab(_dataset->space().id(),
                        H5S_SELECT_SET,
                        this->offset().ptr(), //set the offset pointer
                        this->stride().ptr(), //set the stride pointer
                        this->count().ptr(),  //set the count pointer
                        NULL);
                if(err < 0){
                    EXCEPTION_INIT(H5DataSetError,
                            "Error applying selection!");
                    EXCEPTION_THROW();
                }

                //write data to disk
                err = H5Dwrite(_dataset->id(),
                        mem_type.id(),          //set memory data type
                        _sspace.id(),           //set selection data space
                        _dataset->space().id(),  //set file data space
                        H5P_DEFAULT,
                        &ptr);
                if(err < 0){
                    EXCEPTION_INIT(H5DataSetError,
                            "Error writing data to dataset!");
                    EXCEPTION_THROW();
                }

                //remove selection from the dataspace
                H5Sselect_none(_dataset->space().id());

                //===========>the dataset object can be releasd.
            }


        }
    }
}



