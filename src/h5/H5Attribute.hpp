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

#include<sstream>

#include <pni/utils/Types.hpp>
#include <pni/utils/Scalar.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/Buffer.hpp>

using namespace pni::utils;

#include "H5NamedObject.hpp"
#include "H5Dataspace.hpp"
#include "H5Datatype.hpp"
#include "H5Exceptions.hpp"
#include "H5DatatypeFactory.hpp"

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
            //! while base() and path() return emtpy strings as an attribute
            //! 
            class H5Attribute:public H5NamedObject{
                private:
                    H5Dataspace _dspace; //!< dataspace of the attribute
                    H5Datatype _dtype;   //!< data type of the attribute

                    //! set dataspace and datatype

                    //! This ethod uses the HDF5 ID of an attribute object
                    //! to obtain the dataspace and the datatype. 
                    //! Thus it sets the internal state of the class.
                    void __set_space_type();

                    //! pointer read

                    //! Private method reading data form the attribute to a 
                    //! memory region addressed by ptr. An exception is 
                    //! thrown if an error occurs
                    //! \throws H5AttributeError in case of IO errors
                    //! \param ptr pointer to memory
                    template<typename T> void __read_to_ptr(T *ptr) const;

                    //! pointer write

                    //! Private method writing data from memory addressed by 
                    //! ptr to the attribute.
                    //! \throws H5AttributeError in case of IO errors
                    //! \param ptr pointer to memory
                    template<typename T> void __write_from_ptr(const T *ptr)
                        const;

                    //---------methods to create objects from the attribute----
                    //! create POD data

                    //! Private method to create a plain old data object. The 
                    //! newly created object is asigned to object which is 
                    //! passed by reference. A ShapeMissmatchError is thrown 
                    //! if the attribute is not scalar.
                    //! \throws ShapeMissmatchError if attribute not scalar
                    //! \param object reference to target object
                    template<typename T> void __create_object(T &object) const{
                        EXCEPTION_SETUP("template<typename T> void "
                                "H5Attribute::__create_object(T &object)"
                                "const");

                        if(!_dspace.is_scalar()){
                            EXCEPTION_INIT(ShapeMissmatchError,
                                    "Cannot create POD object - "
                                    "attribute ["+name()+"] is not scalar");
                            EXCEPTION_THROW();
                        }

                    }

                    //! create a buffer object

                    //! Private method to create a Buffer<T> object from the 
                    //! attribute object. The Buffer<T> object is created with 
                    //! enough memory allocated to store the entire content 
                    //! of the attribute. If the attribute is scalar the size 
                    //! of the buffer is 1. 
                    //! \param object reference ot the new object
                    template<typename T> 
                        void __create_object(Buffer<T> &object) const{
                        //allocate memory to hold all the data 
                        if(_dspace.is_scalar()){
                            //in the case of a scalar type 
                            object.allocate(1);
                        }else{
                            object.allocate(_dspace.shape().size());
                        }
                    }

                    //! create a scalar object
                    
                    //! This creates a scalar object from an attribute object.
                    //! All mandatory attribute: name,unit, and description 
                    //! of the object are set to NONE. If the attribute is not
                    //! scalar a ShapeMissmatchError will be thrown.
                    //! \throw ShapeMissmatchError if attribute not scalar
                    //! \param object reference to object
                    template<typename T>
                        void __create_object(Scalar<T> &object) const{
                        EXCEPTION_SETUP("template<typename T> void"
                                " __create_object(Scalar<T> &object) const");

                        if(!_dspace.is_scalar()){
                            EXCEPTION_INIT(ShapeMissmatchError,"Cannot create "
                                    "scalar object - attribute ["+name()+"] "
                                    "is not scalar!");
                            EXCEPTION_THROW();
                        }
                        
                        object = Scalar<T>("NONE","NONE","NONE");
                    }

                    //! create an array object

                    //! Create an array type from an attribute. All mandatory
                    //! attributes of the array: name, unit, and description
                    //! are set to NONE. If the attribute is scalar
                    //! ShapeMissmatchError is thrown
                    //! \throws ShapeMissmatchError
                    //! \param object reference to new object
                    template<typename T,template<typename> class BT>
                        void __create_object(Array<T,BT> &object) const{
                        EXCEPTION_SETUP("template<typename T,template<typename>"
                                "class BT> void __create_object(Array<T,BT> "
                                "&object) const");

                        if(_dspace.is_scalar()){
                            EXCEPTION_INIT(ShapeMissmatchError,"Cannot create "
                                    "array data - attribute ["+name()+"] is"
                                    " not scalar!");
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

                    //! This constructor takes the ID to an attribute object
                    //! and initializes the class. The ID can be obtained 
                    //! with HDF5s C interface.
                    //! \param id HDF5 id of the attribute object.
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

                    //! Write data from a buffer object ot the attribute.
                    //! \throws MemoryAccessError if buffer not allocated
                    //! \throws SizeMissmatchError attribute and buffer size do not match
                    //! \throws H5AttributeError in case of general IO errors
                    //! \param buffer buffer whose data to write 
                    template<typename T,template<typename> class BT> 
                        void write(const BT<T> buffer) const;

                    //! write from Scalar<T> 

                    //! Writing data form a scalar object to the attribute.
                    //! \throws ShapeMissmatchError if attribute is not scalar
                    //! \throws H5AttributeError in case of general IO errors
                    //! \param o scalar from which to write data
                    template<typename T> void write(const Scalar<T> &o) const;

                    //! write from Array<T> 

                    //! Write data form an array to the attribute
                    //! \throws MemoryAccessError if array buffer not allocated
                    //! \throws ShapeMissmatchError array and attribute shape do not match
                    //! \param o array object from whicht to write data
                    template<typename T,template<typename> class BT >
                        void write(const Array<T,BT> &o) const;

                    //! write POD data

                    //! Write attribute from plain old data objects (in other
                    //! words native data types). 
                    //! \throws ShapeMissmatchError attribute not scalar
                    //! \throws H5AttributeError general IO errors
                    //! \param value POD value from which to read data
                    template<typename T> void write(const T &value) const;

                    //! write from String

                    //! Write attribute from a string value.
                    //! \throws H5AttributeError in case of general IO errors
                    //! \param s string to write 
                    void write(const String &s) const;

                    //! read to buffer 

                    //! Read data from the attribute and store it to an 
                    //! instance of a buffer object. The buffer object might
                    //! be an instance of Buffer<T> or RefBuffer<T>. 
                    //! \throws MemoryAllocationError if buffer not allocated
                    //! \throws SizeMissmatchError if buffer and attribute size do not match
                    //! \throws H5AttributeError in case of general IO errors 
                    //! \param buffer buffer object 
                    template<typename T,template<typename> class BT> 
                        void read(BT<T> buffer) const;

                    //! read to Array<T>

                    //! Read data to array a.
                    //! \throws MemoryAllocationError if array buffer not allocated
                    //! \throws ShapeMissmatchERror if array and attribute shape do not match
                    //! \throws H5AttributeError in case of general IO errors
                    //! \param a array where to store data
                    template<typename T,template<typename> class BT> 
                        void read(Array<T,BT> &a) const;

                    //! read to Scalar<T>

                    //! Read data to a scalar. As an attribute object does not
                    //! carry any additional information about the object, 
                    //! units, description and other important attributes must
                    //! be set by the user.
                    //! \throws ShapeMissmatchError if attribute not scalar
                    //! \throws H5AttributeError in case of general IO erros
                    //! \param s scalar object 
                    template<typename T> void read(Scalar<T> &s) const;

                    //! read to POD

                    //! Read data from an attribute to a POD value. 
                    //! \throws ShapeMissmatchError if attribute is not scalar
                    //! \throws H5AttributeError in case of general IO errors
                    //! \param value POD value to which data will be stored
                    template<typename T> void read(T &value) const;

                    //! read to string

                    //! Reads a string value from an attribute.
                    //! \throws ShapeMissmatchError if attribute is not scalar
                    //! \throws H5AttributeError in case of general IO errors
                    //! \param s string variable to which data will be written
                    void read(String &s) const;
                    
                    //! read to an arbitrary object

                    //! This method can be used to read data to an arbitrary 
                    //! object whose type massed be passed as a template 
                    //! parameter explicit in the code. The method tries to 
                    //! construct an instance of type OBJ according to its needs
                    //! and raises an exception if this fails. Once the instance
                    //! is created the attributes data is read to this object
                    //! which is finally returned. 
                    //! \throws ShapeMissmatchError if OBJ does not support the attributes shape
                    //! \throws H5AttributeError in case of general IO errors
                    //! \return instance of OBJ with attribute data
                    template<typename OBJ> OBJ read() const;


                    //============attribute inquery methods====================
                    //! obtain attribute shape

                    //! Returns the shape of the attribute.
                    //! \return shape object
                    Shape shape() const;

                    //! return type_id

                    //! Return the ID of the datatype used for the attribute.
                    //! \return type ID
                    TypeID type_id() const;

                    //! close attribute

                    //! This method closes the attribute object.
                    virtual void close();

                    //! return base name

                    //! Returns an empty string since an attribute has no 
                    //! base name.
                    //! \return empty string
                    virtual String base() const;

                    //! return path

                    //! Returns an empty string as an attribute has no path.
                    //! \return empty string
                    virtual String path() const; 

                    //! get name

                    //! Return the name of the attribute as string.
                    //! \return attribute name
                    virtual String name() const;


            };

            //===============private template declarations=====================
            //implementation of reading to pointer
            template<typename T> void H5Attribute::__read_to_ptr(T *ptr) const{
                EXCEPTION_SETUP("template<typename T> void H5Attribute::"
                        "__read_to_ptr(T *ptr) const");

                H5Datatype mem_type = H5DatatypeFactory::create_type<T>();
                herr_t err = H5Aread(id(),mem_type.id(),(void *)ptr);
                if(err < 0){
                    EXCEPTION_INIT(H5AttributeError,
                            "Error reading attribute ["+name()+"]!");
                    EXCEPTION_THROW();
                }
            } 
           
            //------------------------------------------------------------------
            //implementation of writing from pointer
            template<typename T> 
                void H5Attribute::__write_from_ptr(const T *ptr) const {
                EXCEPTION_SETUP("template<typename T>  void H5Attribute::"
                        "__write_from_ptr(const T *ptr)");

                H5Datatype mem_type = H5DatatypeFactory::create_type<T>();
                herr_t err = H5Awrite(id(),mem_type.id(),(void *)ptr);
                if(err<0){
                    EXCEPTION_INIT(H5AttributeError,
                            "Error writing attribute ["+name()+"]!");
                    EXCEPTION_THROW()
                }
            }

            //=======templates for writing attribute data======================
            template<typename T> void H5Attribute::write(const T &value) const{
                EXCEPTION_SETUP("template<typename T> void H5Attribute::"
                        "write(const T &value) const");

                if(!_dspace.is_scalar()){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Attribute ["+name()+"]is not scalar!");
                    EXCEPTION_THROW();
                }

                __write_from_ptr(&value);
            }

            //------------------------------------------------------------------
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
                    std::stringstream bs_stream; 
                    bs_stream<<buffer.size();
                    std::stringstream as_stream;
                    as_stream<<_dspace.size();
                    EXCEPTION_INIT(SizeMissmatchError,
                            "Buffer size ("+bs_stream.str()+") and size of "
                            "attribute ["+name()+"] ("+as_stream.str()+")"
                            "do not match!");
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
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Attribute ["+name()+"] is not a scalar");
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
                    std::stringstream oshape;
                    oshape<<o.shape();
                    std::stringstream ashape;
                    ashape<<_dspace.shape();
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Array shape ("+oshape.str()+") and attribute shape"
                            " ("+ashape.str()+") of attribute ["+name()+"] do"
                            " not match!");
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
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Attribute ["+name()+"] not scalar!");
                    EXCEPTION_THROW();
                }

                __read_to_ptr(&value);
            }
           
            //------------------------------------------------------------------
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
                    std::stringstream bs;
                    bs << buffer.size();
                    std::stringstream as;
                    as << this->_dspace.size();
                    EXCEPTION_INIT(SizeMissmatchError,
                            "Buffer size ("+bs.str()+") and dataspace size "
                            " ("+as.str()+") of attribute ["+name()+"] do "
                            "not match!");
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
                    std::stringstream bshape;
                    bshape << a.shape();
                    std::stringstream ashape;
                    ashape << _dspace.shape();
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Array shape ("+bshape.str()+") and dataspace shape"
                            " ("+ashape.str()+") of attribute ["+name()+"] do"
                            " not match!");
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
                            "Attribute ["+name()+"] is not scalar!");
                    EXCEPTION_THROW();
                }

                __read_to_ptr(s.ptr());
            }
            
            

        //end of namespace
        }
    }
}


#endif

