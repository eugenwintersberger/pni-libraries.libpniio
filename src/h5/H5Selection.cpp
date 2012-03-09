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
            //=================Implementation of private methods================
            void H5Selection::__throw_if_not_scalar(const String &method) const
            {
                String desc ="Selection is not scalar!"; 
                if(this->size()!=1){
                    ShapeMissmatchError error(method,desc);
                    throw(error);
                }
            }
            
            //------------------------------------------------------------------
            void H5Selection::__throw_if_selection_app_fails
                (herr_t err, const String &method)const
            {
                if(err < 0){
                    H5DataSetError error(method,"Error applying selection!");
                    throw(error);
                }
            }
           
            //------------------------------------------------------------------
            void H5Selection::__throw_selection_read_fail
                (herr_t err,const String &method) const
            {
                String d = "Error reading data via selection to dataset"
                           " ["+_dataset->name()+"]!";
                if(err < 0){
                    H5DataSetError error(method,d);
                    throw(error);
                }
            }

            //------------------------------------------------------------------
            void H5Selection::__throw_selection_write_fail
                (herr_t err,const String &method) const
            {
                String d = "Error writing data via selection to dataset"
                           " ["+_dataset->name()+"]!";
                if(err < 0){
                    H5DataSetError error(method,d);
                    throw(error);
                }
            }

            //==============Implementation of constructors and destructors======
            //implementation of the default constructor
            H5Selection::H5Selection()
            {
            }

            //------------------------------------------------------------------
            //implementation of the copy constructor
            H5Selection::H5Selection(const H5Selection &o)
                :_offset(o._offset),_stride(o._stride),_counts(o._counts),
                 _dataset(o._dataset)
            {
            }

            //------------------------------------------------------------------
            //implementation of the move constructor
            H5Selection::H5Selection(H5Selection &&o)
                : _offset(std::move(o._offset)),_stride(std::move(o._stride)),
                 _counts(std::move(o._counts)),
                 _dataset(o._dataset)
            {
            }

            
            //-------------------------------------------------------------------
            //implementation of the shape constructor
            H5Selection::H5Selection(const H5Dataset &ds,const Shape &s,
                    size_t offset,size_t stride)
                :_offset(s.rank()),_stride(s.rank()),_counts(s.rank()),
                 _dataset(&ds)
            {
                EXCEPTION_SETUP("H5Selection::H5Selection(const H5Dataset &ds,"
                                "const Shape &s,size_t offset,size_t stride)");

                if(s.rank() != ds.rank()){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Rank of dataset ["+ds.name()+"] and selection "
                            "rank do not match!");
                    EXCEPTION_THROW();
                }

                //set offset and stride
                _offset = offset;
                _stride = stride;
                for(size_t i=0;i<s.rank();i++) _counts[i] = s[i];

            }


            //------------------------------------------------------------------
            //implementation of the destructor
            H5Selection::~H5Selection(){
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
                    _stride  = o._stride;
                    _offset  = o._offset;
                    _counts  = o._counts;
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
                    _stride  = std::move(o._stride);
                    _offset  = std::move(o._offset);
                    _counts  = std::move(o._counts);
                    _dataset = o._dataset;
                    o._dataset = nullptr;
                }
                return *this;
            }

            //========implementation of inquery methods=========================
            //get size
            size_t H5Selection::size() const{
                if(rank() == 0) return 0;
                
                size_t s = 1;
                for(size_t i=0;i<rank();i++) s *= _counts[i];

                return s;
            }

            //------------------------------------------------------------------
            //get number of dimensions
            size_t H5Selection::rank() const {
                return _counts.size();
            }

            //------------------------------------------------------------------
            //get shape
            Shape H5Selection::shape() const {
                if(rank() == 0 ) return Shape();
                Shape s(rank()); 
                for(size_t i=0;i<rank();i++) s.dim(i,_counts[i]);
                return s;
            }
            

            //------------------------------------------------------------------
            //return reference to the dataspace
            H5Dataspace H5Selection::space() const{
                H5Dataspace s(shape());
                return s;
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
            void H5Selection::offset(const std::initializer_list<hsize_t> &l){
                EXCEPTION_SETUP("void H5Selection::"
                        "offset(std::initializer_list<hsize_t> &l)");

                if(l.size() != rank()){
                    EXCEPTION_INIT(SizeMissmatchError, "Number of elements "
                            "in initializer list exceeds selection rank!");
                    EXCEPTION_THROW();
                }

                _offset = l;
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
            void H5Selection::stride(const std::initializer_list<hsize_t> &l){
                EXCEPTION_SETUP("void H5Selection::"
                        "stride(const std::initializer_list<hsize_t> &l)");

                if(l.size() != rank()){
                    EXCEPTION_INIT(SizeMissmatchError,"Number of elements "
                            "in initializer list exceeds selection rank");
                    EXCEPTION_THROW();
                }

                _stride = l;
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
            }

            //-----------------------------------------------------------------
            void H5Selection::count(const std::initializer_list<hsize_t> &l){
                EXCEPTION_SETUP("void H5Selection::"
                        "count(const std::initialize_list<hsize_t> &l)");

                if(l.size() != _counts.size()){
                    EXCEPTION_INIT(SizeMissmatchError,"Number of elements "
                            "in initializer list exceeds selection rank!");
                    EXCEPTION_THROW();
                }

                _counts = l;
            }

            //-----------------------------------------------------------------
            const Buffer<hsize_t> &H5Selection::count() const {
                return _counts;
            }

            //-----------------------------------------------------------------
            TypeID H5Selection::type_id() const
            {
                return _dataset->type_id();
            }

            //=============specializations of the IO methods===================
            //implementation of writing a binary value
            void H5Selection::write(const Binary &value) const
            {
                EXCEPTION_SETUP("void H5Selection::write(const BinaryType &value) "
                        "const");

                __throw_if_not_scalar("void H5Selection::write(const "
                                      "BinaryType &value) const");
                
                //create memory dataspace and datatype
                H5Datatype mt = H5DatatypeFactory::create_type<Binary>();
                H5Dataspace ms;

                __write(mt,ms,&value);
            }

            //------------------------------------------------------------------
            //implementation of the write string method 
            void H5Selection::write(const String &value) const{
                EXCEPTION_SETUP("void H5Selection::"
                        "write(const String &value)");

                __throw_if_not_scalar("template<> void H5Selection::write"
                                      "(const String &value)");

                const char *ptr = value.c_str();

                herr_t err;
                //select the proper memory data type
                H5Datatype mem_type = H5Datatype(H5Dget_type(_dataset->id()));
                H5Dataspace ms;
                
                //set selection to the file datasets original dataset
                //==========>here we would have to lock the dataset object 
                err = H5Sselect_hyperslab(_dataset->space().id(),
                        H5S_SELECT_SET,
                        this->offset().ptr(), //set the offset pointer
                        this->stride().ptr(), //set the stride pointer
                        this->count().ptr(),  //set the count pointer
                        NULL);
                __throw_if_selection_app_fails(err,"void H5Selection::"
                                               "write(const String &value)");

                //write data to disk
                err = H5Dwrite(_dataset->id(),
                        mem_type.id(),          //set memory data type
                        ms.id(),           //set selection data space
                        _dataset->space().id(),  //set file data space
                        H5P_DEFAULT,
                        &ptr);
                __throw_selection_write_fail(err,"void H5Selection::"
                                             "write(const String &value)");

                //remove selection from the dataspace
                H5Sselect_none(_dataset->space().id());

            }

            //------------------------------------------------------------------
            //implementation of the read string method 
            void H5Selection::read(String &value) const{
                EXCEPTION_SETUP("void H5Selection::read(String &value) const");

                __throw_if_not_scalar("void H5Selection::read(String &value)"
                                      " const");

                herr_t err;
                //set selection to the file datasets original dataset
                //==========>here we would have to lock the dataset object 
                err = H5Sselect_hyperslab(_dataset->space().id(),
                        H5S_SELECT_SET,
                        this->offset().ptr(), //set the offset pointer
                        this->stride().ptr(), //set the stride pointer
                        this->count().ptr(),  //set the count pointer
                        NULL);
                __throw_if_selection_app_fails(err,"void H5Selection::"
                                               "read(String &value) const");
                
                const char *ptr = nullptr;
	            hid_t xfer_plist = H5Pcreate(H5P_DATASET_XFER);
                
                //select the proper memory data type
                H5Datatype mem_type = H5Datatype(H5Dget_type(_dataset->id()));
                H5Dataspace ms;

                //write data to disk
                err = H5Dread(_dataset->id(),
                        mem_type.id(),          //set memory data type
                        ms.id(),           //set selection data space
                        _dataset->space().id(),  //set file data space
                        xfer_plist,
                        &ptr);
                __throw_selection_read_fail(err,"void H5Selection::read"
                                            "(String &value) const");

                //copy content of the pointer to the string object
                try{
                    value = String(ptr);
                }catch(...){
                    value = "";
                }
                
                //remove selection from the dataspace
                H5Sselect_none(_dataset->space().id());

                //reclaim memory from HDF5 library.
                H5Dvlen_reclaim(mem_type.id(),_dataset->space().id(),
                                xfer_plist,&ptr);


            }
           
            //---------------------------------------------------------------
            //implementation of reading a binary value
            void H5Selection::read(Binary &value) const
            {
                EXCEPTION_SETUP("void H5Selection::read(BinaryType &value) "
                        "const");

                __throw_if_not_scalar("void H5Selection::read(BinaryType "
                                      "&value) const");

                //create memory dataspace and datatype
                H5Datatype mt = H5DatatypeFactory::create_type<Binary>();
                H5Dataspace ms;

                __read(mt,ms,&value);
            }

        }
    }
}



