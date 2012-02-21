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
 * Implementation of the HDF5 dataset class
 *
 * Created on: Jan 12, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <pni/utils/Buffer.hpp>

#include "H5Dataset.hpp"
#include "H5ObjectType.hpp"
#include "H5Exceptions.hpp"
#include "H5Link.hpp"
#include "H5Selection.hpp"


namespace pni{
    namespace nx{
        namespace h5{
            //============implementation of private methods====================
            //throw a ShapeMissmatchError exception if dataset not scalar
            void H5Dataset::__throw_if_not_scalar(const String &method) const
            {
                String desc = "Dataset ["+this->name()+"] is not scalar!";
                if(_space.size()!=1){
                    ShapeMissmatchError error(method,desc);
                    throw(error);
                }
            }

            //-----------------------------------------------------------------
            //implementation of the buffer check routine
            void H5Dataset::__check_buffer(const String &method,
                                           const BufferObject &buffer) const
            {
                std::stringstream bs; bs<<buffer.size();
                std::stringstream ss; ss<<_space.size();

                String desc_not_alloc = "Buffer is not allocated - cannot "
                    "read data from dataset ["+this->name()+"]!";
                String desc_size_err = "Buffer size ("+bs.str()+") and dataset "
                    "["+ this->name()+"] size ("+ss.str()+") do not match!";

                if(!buffer.is_allocated()){
                    MemoryAccessError error(method,desc_not_alloc);
                    throw(error);
                }

                if(_space.size() != buffer.size()){
                    SizeMissmatchError error(method,desc_size_err);
                    throw(error);
                }
            }
           
            //-----------------------------------------------------------------
            //implementation of the 
            void H5Dataset::__check_array(const String &method,
                                          const ArrayObject &array) const
            {
                std::stringstream as; as<<array.shape();
                std::stringstream ss; ss<<_space.shape();

                String desc_not_alloc = "Array not allocated - cannot write "
                                        "data to dataset ["+this->name()+"]!";
                String desc_shape_error = "Dataset ["+this->name()+"] shape "
                    "("+ss.str()+") and array shape ("+as.str()+") do not "
                    "match!";

                //check if the array buffer is allocated
                if(!array.buffer().is_allocated()){
                    MemoryAccessError error(method,desc_not_alloc);
                    throw(error);
                }

                //check if dataspace shape and array shape are equal
                if(_space.shape() != array.shape()){
                    ShapeMissmatchError error(method,desc_shape_error);
                    throw(error);
                }

            }
            //===implementation of constructors and destructors================
            //implementation of the default constructor
            H5Dataset::H5Dataset():H5AttributeObject(){
            
            }

            //-----------------------------------------------------------------
            //implementation of the copy constructor
            H5Dataset::H5Dataset(const H5Dataset &o):
                H5AttributeObject(o),
                _space(o._space) 
            {
            }

            //-----------------------------------------------------------------
            //implementation of the copy conversion constructor
            H5Dataset::H5Dataset(const H5Object &o):H5AttributeObject(o)
            {
                EXCEPTION_SETUP("H5Dataset::H5Dataset(const H5Object &o)");

                //check if the type is ok for conversion
                if(object_type() != H5ObjectType::DATASET){
                    EXCEPTION_INIT(H5DataSetError,"Object is not a dataset!");
                    EXCEPTION_THROW();
                }

                //copy the datatype and dataspace
                _space = __obtain_dataspace();
            }

            //-----------------------------------------------------------------
            //implementation of the move constrcutor
            H5Dataset::H5Dataset(H5Dataset &&o):
                H5AttributeObject(std::move(o)),
                _space(std::move(o._space)) 
            {
            }

            //-----------------------------------------------------------------
            //implementation of the move conversion constructor
            H5Dataset::H5Dataset(H5Object &&o):H5AttributeObject(std::move(o)){
                EXCEPTION_SETUP("H5Dataset::H5Dataset(H5Object &&o)");

                if(object_type() != H5ObjectType::DATASET){
                    EXCEPTION_INIT(H5DataSetError,"Object is not a dataset!");
                    EXCEPTION_THROW();
                }

                //move datatype and data space
                _space = __obtain_dataspace();
            }

            //-----------------------------------------------------------------
            //implementation of the constructor for a contigous array
            H5Dataset::H5Dataset(const String &n,const H5Group &g,
                    const H5Datatype &t,const H5Dataspace &s){
                EXCEPTION_SETUP("H5Dataset::H5Dataset(const String &n,"
                        "const H5Group &g, const TypeID &tid,const Shape &s)");


                //create link creation property list
                hid_t lpl = H5Pcreate(H5P_LINK_CREATE);
                H5Pset_create_intermediate_group(lpl,1);

                //create the datase
                hid_t did = H5Dcreate2(g.id(),n.c_str(),t.id(),s.id(),
                        lpl,H5P_DEFAULT,H5P_DEFAULT);
                if(did<0){
                    String estr = "Cannot create dataset ["+n+
                        "] below ["+path()+"]!";
                    EXCEPTION_INIT(H5DataSetError,estr);
                    EXCEPTION_THROW();
                }

                //set id
                H5Object::id(did);

                //get dataspace
                _space = __obtain_dataspace();

                //close property list
                H5Pclose(lpl);
            }

            //-----------------------------------------------------------------
            //implementation of a constructor for a chunked dataset
            H5Dataset::H5Dataset(const String &n, const H5Group &g, 
                    const H5Datatype &t, const H5Dataspace &s,const Shape &cs){
                EXCEPTION_SETUP("H5Dataset::H5Dataset(const String &n, "
                        "const H5Group &g, const TypeID &tid,const Shape &s,"
                        "const Shape &cs)");

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
                hid_t did = H5Dcreate2(g.id(),n.c_str(),t.id(),s.id(),
                        lpl,cpl,H5P_DEFAULT);
                if(did<0){
                    String estr = "Cannot create dataset ["+n+
                        "] below ["+g.path()+"]!";
                    EXCEPTION_INIT(H5DataSetError,estr);
                    EXCEPTION_THROW();
                }

                H5Object::id(did);
                _space = __obtain_dataspace();
                //construction done - close property lists
                H5Pclose(lpl);
                H5Pclose(cpl);
            }
            
            //-----------------------------------------------------------------
            //implementation of a constructor for a chunked dataset with filter
            H5Dataset::H5Dataset(const String &n, const H5Group &g, 
                    const H5Datatype &t, const H5Dataspace &s,const Shape &cs,
                    const H5Filter &filter){
                EXCEPTION_SETUP("H5Dataset::H5Dataset(const String &n, "
                        "const H5Group &g, const TypeID &tid,const Shape &s,"
                        "const Shape &cs,const H5Filter &filter)");

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

                //setup the filter
                filter.setup(cpl);

                

                //create the datase
                hid_t did = H5Dcreate2(g.id(),n.c_str(),t.id(),s.id(),
                        lpl,cpl,H5P_DEFAULT);
                if(did<0){
                    String estr = "Cannot create dataset ["+n+
                        "] below ["+g.path()+"]!";
                    EXCEPTION_INIT(H5DataSetError,estr);
                    EXCEPTION_THROW();
                }

                H5Object::id(did);
                _space = __obtain_dataspace();
                //construction done - close property lists
                H5Pclose(lpl);
                H5Pclose(cpl);
            }

            //-----------------------------------------------------------------
            //implement construction from an object id
            H5Dataset::H5Dataset(const hid_t &oid):H5AttributeObject(oid){
                EXCEPTION_SETUP("H5Dataset::H5Dataset(const hid_t &oid)");

                if(object_type() != H5ObjectType::DATASET){
                    EXCEPTION_INIT(H5DataSetError,
                            "Object ID does not belong to a dataset!");
                    EXCEPTION_THROW();
                }

                _space = H5Dataspace(H5Dget_space(id()));
            }

            //-----------------------------------------------------------------
            //implementation of the default destructor 
            H5Dataset::~H5Dataset(){
                _space.close();
            }

            //=========implementation of the assignment operators==============
            //implementation of the  copy assignment operator
            H5Dataset &H5Dataset::operator=(const H5Dataset &o){
                if(this != &o){
                    (H5AttributeObject &)(*this) = (H5AttributeObject &)o;
                    _space = o._space;
                }
                return *this;
            }

            //-----------------------------------------------------------------
            //implementation of the  copy conversion assignment
            H5Dataset &H5Dataset::operator=(const H5Object &o){
                EXCEPTION_SETUP("H5Dataset &H5Dataset::operator="
                        "(const H5Object &o)");
                if(o.object_type()!=H5ObjectType::DATASET){
                    EXCEPTION_INIT(H5DataSetError,"Object is not a dataset!");
                    EXCEPTION_THROW();
                }

                if(this != &o){
                    (H5Object &)(*this) = o;
                    _space = __obtain_dataspace();
                }
                return *this;
            }

            //-----------------------------------------------------------------
            //implementation of the  move assignment operator
            H5Dataset &H5Dataset::operator=(H5Dataset &&o){
                if(this != &o){
                    (H5AttributeObject &)(*this) = std::move((H5AttributeObject
                                &)o);
                    _space = std::move(o._space);
                }
                return *this;
            }

            //-----------------------------------------------------------------
            //! move conversion assignment
            H5Dataset &H5Dataset::operator=(H5Object &&o){
                EXCEPTION_SETUP("H5Dataset &H5Dataset::operator="
                        "(H5Object &&o)");
                if(o.object_type() != H5ObjectType::DATASET){
                    EXCEPTION_INIT(H5DataSetError,"Object is not a dataset!");
                    EXCEPTION_THROW();
                }

                if(this != &o){
                    (H5Object &)(*this) = std::move(o);
                    _space = __obtain_dataspace();
                }
                return *this;
            }

            //=========implementation of inquery methods========================
            void H5Dataset::resize(const Shape &s){
                EXCEPTION_SETUP("void H5Dataset::resize(const Shape &s)");

                if(s.rank() != _space.rank()){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "New shape does not have the same rank!");
                    EXCEPTION_THROW();
                }
                Buffer<hsize_t> b(s.rank());
                for(size_t i=0;i<s.rank();i++) b[i] = s[i];

                herr_t err = H5Dset_extent(id(),b.ptr());
                if(err < 0){
                    EXCEPTION_INIT(H5DataSetError, 
                            "Resizing of dataset ["+name()+"] failed!");
                    EXCEPTION_THROW();
                }
               

                //re-fetch data space
                _space = __obtain_dataspace();
            }

            //-----------------------------------------------------------------
            void H5Dataset::grow(const size_t &e,const size_t &n){
                EXCEPTION_SETUP("void H5Dataset::extend(const size_t &e,"
                        "const size_t &n)");

                if(e>=rank()){
                    std::stringstream se; se << e;
                    std::stringstream sr; sr << rank();
                    EXCEPTION_INIT(IndexError,"Dimension index ("+se.str()+") "
                            "exceeds rank of dataspace ["+name()+"] which is "
                            "("+sr.str()+")!");
                    EXCEPTION_THROW();
                }

                Buffer<hsize_t> b(_space.rank());
                for(size_t i=0;i<_space.rank();i++) b[i] = _space[i];
                b[e] += n;

                herr_t err = H5Dset_extent(id(),b.ptr());
                if(err < 0){
                    EXCEPTION_INIT(H5DataSetError,
                            "Grow of dataset ["+name()+"] failed!");
                    EXCEPTION_THROW();
                }

                //re-fetch the new dataspace
                _space.grow(e,n);
            }

            //------------------------------------------------------------------
            size_t H5Dataset::size() const{
                return _space.size();
            }

            //------------------------------------------------------------------
            Shape H5Dataset::shape() const {
                return _space.shape();
            }

            //-----------------------------------------------------------------
            size_t H5Dataset::rank() const {
                return _space.rank();
            }

            //-----------------------------------------------------------------
            size_t H5Dataset::dim(const size_t &i) const{
                return _space.dim(i);
            }

            //------------------------------------------------------------------
            TypeID H5Dataset::type_id() const{
                return __obtain_datatype().type_id();
            }

            //------------------------------------------------------------------
            //implementation of selection creation  
            H5Selection H5Dataset::selection() const{
                EXCEPTION_SETUP("H5Selection H5Dataset::selection() const");

                if(_space.is_scalar()){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "You cannot create a selection from the scalar"
                            "dataset ["+name()+"]!");
                    EXCEPTION_THROW();
                }

                H5Selection selection(*this,shape(),0,1);
                return selection;
            }

            //------------------------------------------------------------------
            //implementation of writing a string scalar
            void H5Dataset::write(const String &b) const
            {
                EXCEPTION_SETUP("void H5Dataset::write(const String &b) const");
                
                __throw_if_not_scalar("void H5Dataset::write(const String &b) "
                                      "const");
                
                //select the proper memory data type
                
                H5Datatype mem_type(H5Dget_type(id()));
                const char *ptr = b.c_str();

                //write data to disk
                herr_t err = H5Dwrite(id(),mem_type.id(),H5S_ALL,H5S_ALL,
                                      H5P_DEFAULT,(const void *)&ptr);
                if(err<0){
                    EXCEPTION_INIT(H5DataSetError,
                            "Error writing data to dataset!");
                    EXCEPTION_THROW();
                }

            }

            //------------------------------------------------------------------
            //implementation of writing a binary scalar
            void H5Dataset::write(const Binary &b) const
            {
                __throw_if_not_scalar("void H5Datatype::write(const Binary &b)"
                                      " const");
                __write(&b);
            }

            //------------------------------------------------------------------
            //implementation of reading binary scalar
            void H5Dataset::read(Binary &b) const
            {
                __throw_if_not_scalar("void H5Datatype::read(Binary &b) const");
                __read(&b);
            }
           
            //------------------------------------------------------------------
            //implementation of reading string scalar
            void H5Dataset::read(String &b) const
            {
                EXCEPTION_SETUP("void H5Dataset::read(String &b) const");

                __throw_if_not_scalar("void H5Dataset::read(String &b) const");

                H5Datatype mem_type(H5Dget_type(id()));
                const char *ptr = nullptr;
                hid_t xfer_plist = H5Pcreate(H5P_DATASET_XFER);

                //write data to disk
                herr_t err = H5Dread(id(),mem_type.id(),H5S_ALL,H5S_ALL,
                                      xfer_plist,(void *)&ptr);
                if(err<0){
                    EXCEPTION_INIT(H5DataSetError,
                            "Error writing data to dataset ["+name()+"]!");
                    EXCEPTION_THROW();
                }

                try{
                    b = String(ptr);
                }catch(...){
                    b = "";
                }

                H5Dvlen_reclaim(mem_type.id(),_space.id(),xfer_plist,&ptr);

            }

            //-----------------------------------------------------------------
            void H5Dataset::link(const String &linkname) const
            {
                H5Link::create(path(),parent(),linkname);
            }

            //------------------------------------------------------------------
            void H5Dataset::link(const H5Group &g,const String &n) const
            {
                H5Link::create(path(),g,n);
            }

            //------------------------------------------------------------------
            H5Group H5Dataset::parent() const
            {
                hid_t fid = H5Iget_file_id(id());
                hid_t gid = H5Oopen(fid,base().c_str(),H5P_DEFAULT);
                H5Group g(gid);
                H5Fclose(fid);
                H5Oclose(gid);

                return g;
            }



        //end of namespace
        }
    }
}

