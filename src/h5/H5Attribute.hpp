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
 * Declaration of an HDF5 attribute object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#ifndef __H5ATTRIBUTE_HPP__
#define __H5ATTRIBUTE_HPP__

#include <pni/utils/Types.hpp>
#include <pni/utils/Scalar.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/Buffer.hpp>

using namespace pni::utils;

#include "H5NamedObject.hpp"
#include "H5Dataspace.hpp"
#include "H5Datatype.hpp"
#include "H5Exceptions.hpp"

namespace pni{
    namespace nx{
        namespace h5{
            //! \ingroup nxh5_classes
            //! \brief HDF5 attribute object

            //! An HDF5 attribute behaves basically like a dataset with the 
            //! exception that (for obvious reasons) no other attributes 
            //! can be attached to it. In addition attributes cannot use 
            //! compression nor can they be used along with a chunked layout.
            //! Attribute objects are derived from H5NamedObject. However, 
            //! the semantics of the name(), base(), and path() methods is 
            //! slightly different. name() returns the name of the attribute
            //! while base() the name of the object the attribute is attached 
            //! to. The path() method returns somehting like a path to an 
            //! attribute according to the following syntax base():name().
            //! 
            class H5Attribute:public H5NamedObject{
                private:
                    H5Dataspace _dspace; //!< dataspace of the attribute
                    H5Datatype _dtype;   //!< data type of the attribute

                    //obtain the dataspace and datatype from the object ID
                    //that belongs to this attribute object
                    void __set_space_type();

                    //read and write data from typed pointer
                    template<typename T> void __read_to_ptr(T *ptr) const;
                    template<typename T> void __write_from_ptr(const T *ptr)
                        const;

                    //---------methods to create objects from the attribute----
                    //! create a plain old data or string object
                    template<typename T> 
                        void __create_object(T &object) const{
                        //there is nothing we need to do here 
                    }

                    //! create a buffer object
                    template<typename T> 
                        void __create_object(Buffer<T> &object) const{
                        //allocate memory to hold all the data 
                        object.allocate(_dspace.shape().size());
                    }

                    //! create a scalar object
                    template<typename T>
                        void __create_object(Scalar<T> &object) const{
                        EXCEPTION_SETUP("template<typename T> void"
                                " __create_object(Scalar<T> &object) const");

                        if(!_dspace.is_scalar()){
                            EXCEPTION_INIT(ShapeMissmatchError,
                                    "Attribute is not scalar!");
                            EXCEPTION_THROW();
                        }
                        
                        object = Scalar<T>("NONE","NONE","NONE");
                    }

                    //! create an array object
                    template<typename T,template<typename> class BT>
                        void __create_object(Array<T,BT> &object) const{
                        EXCEPTION_SETUP("template<typename T,template<typename>"
                                "class BT> void __create_object(Array<T,BT> "
                                "&object) const");

                        if(_dspace.is_scalar()){
                            EXCEPTION_INIT(ShapeMissmatchError,
                                    "Attribute is scalar!");
                            EXCEPTION_THROW();
                        }
                        object =
                            Array<T,BT>(_dspace.shape(),"NONE","NONE","NONE");
                    }

                public:
                    //================constructors and destructors=============
                    //! default constructor
                    explicit H5Attribute();
                    //! copy constructor
                    H5Attribute(const H5Attribute &o);
                    //! move constructor
                    H5Attribute(H5Attribute &&o);
                    //! construct from HDF5 type ID
                    explicit H5Attribute(const hid_t &id);
                    
                    //! destructor
                    ~H5Attribute();

                    //=============assignment operators========================
                    //! copy assignment operator
                    H5Attribute &operator=(const H5Attribute &a);
                    //! move assignment operator
                    H5Attribute &operator=(H5Attribute &&o);


                    //=============reading and writting data===================
                    //! write from a buffer
                    template<typename T,template<typename> class BT> 
                        void write(const BT<T> buffer) const;
                    //! write from Scalar<T> 
                    template<typename T> void write(const Scalar<T> &o) const;
                    //! write from Array<T> 
                    template<typename T,template<typename> class BT >
                        void write(const Array<T,BT> &o) const;
                    template<typename T> void write(const T &value) const;
                    //! write from String
                    void write(const String &s) const;

                    //! read to buffer 
                    template<typename T,template<typename> class BT> 
                        void read(BT<T> buffer) const;
                    //! read to Array<T>
                    template<typename T,template<typename> class BT> 
                        void read(Array<T,BT> &a) const;
                    //! read to Scalar<T>
                    template<typename T> void read(Scalar<T> &s) const;
                    //! read to plain old data or string
                    template<typename T> void read(T &value) const;
                    //! read to string
                    
                    //! read without argument
                    template<typename OBJ> OBJ read() const;
                    void read(String &s) const;


                    //============attribute inquery methods====================
                    const Shape &shape() const;
                    TypeID type_id() const;
                    virtual void close();


            };

            //===============private template declarations=====================

            template<typename T> void H5Attribute::__read_to_ptr(T *ptr) const{
                EXCEPTION_SETUP("template<typename T> void H5Attribute::"
                        "__read_to_ptr(T *ptr) const");

                H5Datatype mem_type = H5Datatype::create<T>();
                herr_t err = H5Aread(id(),mem_type.id(),(void *)ptr);
                if(err < 0){
                    EXCEPTION_INIT(H5AttributeError,"Error reading attribute!");
                    EXCEPTION_THROW();
                }
            } 
            
            template<typename T> 
                void H5Attribute::__write_from_ptr(const T *ptr) const {
                EXCEPTION_SETUP("template<typename T>  void H5Attribute::"
                        "__write_from_ptr(const T *ptr)");

                H5Datatype mem_type = H5Datatype::create<T>();
                herr_t err = H5Awrite(id(),mem_type.id(),(void *)ptr);
                if(err<0){
                    EXCEPTION_INIT(H5AttributeError,"Error writing attribute!");
                    EXCEPTION_THROW()
                }
            }

            //=======templates for writing attribute data======================
            template<typename T> void H5Attribute::write(const T &value) const{
                EXCEPTION_SETUP("template<typename T> void H5Attribute::"
                        "write(const T &value) const");

                if(!_dspace.is_scalar()){
                    EXCEPTION_INIT(ShapeMissmatchError,"Attribute is not scalar!");
                    EXCEPTION_THROW();
                }

                __write_from_ptr(&value);
            }

            template<typename T,template<typename> class BT> 
            void H5Attribute::write(const BT<T> buffer) const{
                EXCEPTION_SETUP("template<typename T,template<typename> class"
                        "BT> void H5Attribute::write(const BT<T> buffer) "
                        "const");

                //check if the buffer we are trying to read from is allocated
                if(!buffer.is_allocated()){
                    EXCEPTION_INIT(MemoryAccessError,"Buffer not allocated!");
                    EXCEPTION_THROW();
                }

                //the size of the attribute must be equal to the size of the 
                //buffer
                if(buffer.size()!=this->_dspace.shape().size()){
                    EXCEPTION_INIT(SizeMissmatchError,"Buffer and attribute"
                            "size do not match");
                    EXCEPTION_THROW();
                }

                __write_from_ptr(buffer.ptr());
            }

            //-----------------------------------------------------------------
            //implementation of write from Scalar<T> 
            template<typename T> 
            void H5Attribute::write(const Scalar<T> &o) const{
                EXCEPTION_SETUP("template<typename T> void H5Attribute::"
                        "write(const Scalar<T> &o) const");
                
                if(!_dspace.is_scalar()){
                    EXCEPTION_INIT(ShapeMissmatchError,"Attribute is not a"
                            "scalar");
                    EXCEPTION_THROW();
                }
                
                __write_from_ptr(o.ptr());
            }

            //-----------------------------------------------------------------
            //implementation of write from Array<T> 
            template<typename T,template<typename> class Buffer >
            void H5Attribute::write(const Array<T,Buffer> &o) const{
                EXCEPTION_SETUP("template<typename T,template<typename> class"
                        " Buffer > void H5Attribute::write(const Array<T,"
                        "Buffer> &o) const");
                
                if(!o.buffer().is_allocated()){
                    EXCEPTION_INIT(MemoryAccessError,"Array not allocated!");
                    EXCEPTION_THROW();
                }

                if(o.shape() != _dspace.shape()){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Array and attribut shape do not match!");
                    EXCEPTION_THROW();
                }
                
                __write_from_ptr(o.ptr());
            }


            //======templates for reading attribute data=======================
            //! 
            template<typename OBJ> OBJ H5Attribute::read() const{
                OBJ object;
                __create_object(object);
                read(object);
                return object;
            }

            //-----------------------------------------------------------------
            template<typename T> void H5Attribute::read(T &value) const {
                EXCEPTION_SETUP("template<typename T> void H5Attribute::"
                        "read(T &value) const");
                if(!_dspace.is_scalar()){
                    EXCEPTION_INIT(ShapeMissmatchError,"Attribute not scalar!");
                    EXCEPTION_THROW();
                }

                __read_to_ptr(&value);
            }
            
            //implementation of read to pointer
            template<typename T,template<typename> class BT> 
                void H5Attribute::read(BT<T> buffer) const{
                EXCEPTION_SETUP("template<typename T,template<typename> class"
                        " BT> void H5Attribute::read(BT<T> buffer) const");

                //check if the buffer is allocated
                if(!buffer.is_allocated()){
                    EXCEPTION_INIT(MemoryAccessError,"Buffer not allocated!");
                    EXCEPTION_THROW();
                }

                //check if the size of the buffer and that of the attribute
                //match
                if(buffer.size() != this->_dspace.shape().size()){
                    EXCEPTION_INIT(SizeMissmatchError,
                            "Buffer and attribute size do not match!");
                    EXCEPTION_THROW();
                }

                __read_to_ptr(buffer.ptr());
            }

            //-----------------------------------------------------------------
            //implementation of read to Array<T>
            template<typename T,template<typename> class BT> 
            void H5Attribute::read(Array<T,BT> &a) const{
                EXCEPTION_SETUP("template<typename T,template<typename> "
                        "class Buffer> void H5Attribute::read(Array<T,"
                        "Buffer> &a) const");
                if(!a.buffer().is_allocated()){
                    EXCEPTION_INIT(MemoryAccessError,"Array is not allocated!");
                    EXCEPTION_THROW();
                }

                if(_dspace.shape()!=a.shape()){
                    EXCEPTION_INIT(ShapeMissmatchError,"Array and attribute"
                            "shape do not match!");
                    EXCEPTION_THROW();
                }
                
                __read_to_ptr(a.ptr());
            }

            //-----------------------------------------------------------------
            //implementation of read to Scalar<T>
            template<typename T> void H5Attribute::read(Scalar<T> &s) const{
                EXCEPTION_SETUP("template<typename T> void H5Attribute::"
                        "read(Scalar<T> &s) const");
                if(!_dspace.is_scalar()){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Attribute is not scalar!");
                    EXCEPTION_THROW();
                }

                __read_to_ptr(s.ptr());
            }
            
            

        //end of namespace
        }
    }
}


#endif

