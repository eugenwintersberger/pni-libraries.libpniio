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
#include <pni/utils/DBuffer.hpp>
#include <pni/utils/SBuffer.hpp>
#include <pni/utils/RBuffer.hpp>

using namespace pni::utils;

#include "H5NamedObject.hpp"
#include "H5Dataspace.hpp"
#include "H5Datatype.hpp"
#include "H5Exceptions.hpp"
#include "H5DatatypeFactory.hpp"

namespace pni{
namespace nx{
namespace h5{
    /*! 
    \ingroup nxh5_classes
    \brief HDF5 attribute object

    An HDF5 attribute behaves basically like a dataset with the 
    exception that (for obvious reasons) no other attributes 
    can be attached to it. In addition attributes cannot use 
    compression nor can they be used along with a chunked layout.
    Attribute objects are derived from H5NamedObject. However, 
    the semantics of the name(), base(), and path() methods is 
    slightly different. name() returns the name of the attribute
    while base() and path() return emtpy strings as an attribute
    */ 
    class H5Attribute:public H5NamedObject
    {
        private:
            H5Dataspace _dspace; //!< dataspace of the attribute
            H5Datatype _dtype;   //!< data type of the attribute

            //-----------------------------------------------------------------
            /*! 
            \brief set dataspace and datatype

            This ethod uses the HDF5 ID of an attribute object
            to obtain the dataspace and the datatype. 
            Thus it sets the internal state of the class.
            */
            void __set_space_type();

            //-----------------------------------------------------------------
            /*! 
            \brief pointer read

            Private method reading data form the attribute to a 
            memory region addressed by ptr. An exception is 
            thrown if an error occurs
            \throws H5AttributeError in case of IO errors
            \param ptr pointer to memory
            */
            template<typename T> void __read_to_ptr(T *ptr) const
            {
                H5Datatype mem_type = H5DatatypeFactory::create_type<T>();
                herr_t err = H5Aread(id(),mem_type.id(),(void *)ptr);
                if(err < 0)
                    throw H5AttributeError(EXCEPTION_RECORD,
                            "Error reading attribute ["+this->name()+"]!");
            } 

            //-----------------------------------------------------------------
            /*! 
            \brief pointer write

            Private method writing data from memory addressed by 
            ptr to the attribute.
            \throws H5AttributeError in case of IO errors
            \param ptr pointer to memory
            */
            template<typename T> void __write_from_ptr(const T *ptr) const
            {
                H5Datatype mem_type = H5DatatypeFactory::create_type<T>();
                herr_t err = H5Awrite(id(),mem_type.id(),(void *)ptr);
                if(err<0)
                    throw H5AttributeError(EXCEPTION_RECORD, 
                        "Error writing attribute ["+this->name()+"]!");
            }

            //-----------------------------------------------------------------
            /*!
            \brief write buffer type

            Write data from a buffer template
            */
            template<template<typename ...> class BTYPE,typename ...OTS>
                void _write_buffer(const BTYPE<OTS...> &buffer) const
            {
                //check if the buffer we are trying to read from is allocated
                if(!buffer.is_allocated())
                    throw MemoryNotAllocatedError(EXCEPTION_RECORD, 
                                            "Buffer not allocated!");

                check_equal_size(buffer,this->_dspace.shape(),EXCEPTION_RECORD);

                __write_from_ptr(buffer.ptr());
            }

            //-----------------------------------------------------------------
            /*!
            \brief write buffer from an array

            */
            template<template<typename ...> class ATYPE,typename ...OTS>
                void _write_array(const ATYPE<OTS...> &array) const
            {
                if(!array.storage().is_allocated())
                    throw MemoryNotAllocatedError(EXCEPTION_RECORD,
                            "Array is not allocated!");

                check_equal_shape(array,this->_dspace,EXCEPTION_RECORD);
                
                __write_from_ptr(array.storage().ptr());

            }

            //-----------------------------------------------------------------
            template<typename ...OTS> 
                void _write_array(const NumArray<OTS...> &array) const
            {
                if(!array.storage().storage().is_allocated())
                    throw MemoryNotAllocatedError(EXCEPTION_RECORD,
                            "Array is not allocated!");

                check_equal_shape(array,_dspace,EXCEPTION_RECORD);
                
                __write_from_ptr(array.storage().storage().ptr());
            }

            //-----------------------------------------------------------------
            template<template<typename ...> class BTYPE,typename ...OTS>
                void _read_buffer(BTYPE<OTS...> &buffer) const
            {
                //check if the buffer is allocated
                if(!buffer.is_allocated())
                    throw MemoryNotAllocatedError(EXCEPTION_RECORD, 
                                             "Buffer not allocated!");

                check_equal_size(buffer,this->_dspace,EXCEPTION_RECORD);

                __read_to_ptr(buffer.ptr());
            }

            //-----------------------------------------------------------------
            template<template<typename ...> class ATYPE,typename ...OTS>
                void _read_array(ATYPE<OTS...> &array) const
            {
                typedef typename ATYPE<OTS...>::value_type value_type;
                if(!array.storage().is_allocated())
                    throw MemoryNotAllocatedError(EXCEPTION_RECORD, 
                                             "Array is not allocated!");

                check_equal_shape(_dspace,array,EXCEPTION_RECORD);

                __read_to_ptr(const_cast<value_type *>(array.storage().ptr()));
            }

            //-----------------------------------------------------------------
            template<typename ...OTS>
                void _read_array(NumArray<OTS...> &array) const
            {
                typedef typename NumArray<OTS...>::value_type value_type;
                if(!array.storage().storage().is_allocated())
                    throw MemoryNotAllocatedError(EXCEPTION_RECORD, 
                                             "Array is not allocated!");

                check_equal_shape(_dspace,array,EXCEPTION_RECORD);

                __read_to_ptr(const_cast<value_type *>(array.storage().storage().ptr()));
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


            //===================reading and writting data=====================
            /*! \brief write a single scalar

            Write a single scalar value of a POD type. 
            \tparam T POD type
            \param v reference to the data to write
            */
            template<typename T> void write(const T &v) const
            {
                if(!_dspace.is_scalar())
                    throw ShapeMissmatchError(EXCEPTION_RECORD, 
                        "Attribute ["+this->name()+"]is not scalar!");

                __write_from_ptr(&v);
            }
       
            //-----------------------------------------------------------------
            /*! 
            \brief write a string to the attribure

            Write attribute from a string value.
            \throws H5AttributeError in case of general IO errors
            \param s string to write 
            */
            void write(const String &s) const;


            //-----------------------------------------------------------------
            /*!
            \brief write from a static buffer 

            Write data form a static buffer.
            \throws SizeMissmatchError attribute and buffer size do not match
            \throws H5AttributeError in case of general IO errors
            \tparam OTS template arguments to SBuffer template
            \param buffer instance of SBuffer<OTS...> whose data to write
            */
            template<typename ...OTS> 
                void write(const SBuffer<OTS...> &buffer) const
            {
                this->_write_buffer(buffer);
            }

            //-----------------------------------------------------------------
            /*!
            \brief write from a dynamic buffer

            Write data from a dynamic buffer.
            \throws MemoryNotAllocatedError if buffer not allocated
            \throws SizeMissmatchError if buffer and attribute size do not match
            \throws H5AttributeError in case of any other IO error
            \tparam OTS template arguments
            \param buffer instance of DBuffer
            */
            template<typename ...OTS>
                void write(const DBuffer<OTS...> &buffer) const
            {
                this->_write_buffer(buffer);
            }

            //-----------------------------------------------------------------
            /*!
            \brief write data from a refbuffer

            Write data from a reference buffer.
            \throws MemoryNotAllocatedError if buffer not allocated
            \throws SizeMissmatchError if buffer and attribute size do not match
            \throws H5AttributeError in case of any other IO error
            */
            template<typename ...OTS>
                void write(const RBuffer<OTS...> &buffer) const
            {
                this->_write_buffer(buffer);
            }
           
            //-----------------------------------------------------------------
            /*! 
            \brief write from a numeric array

            Write data form an array to the attribute
            \throws MemoryAccessError if array buffer not allocated
            \throws ShapeMissmatchError array and attribute shape do not match
            \param o array object from whicht to write data
            */
            template<typename ...OTS>
                void write(const NumArray<OTS...> &o) const
            {
                this->_write_array(o);
            }

            //-----------------------------------------------------------------
            template<typename ...OTS>
                void write(const DArray<OTS...> &o) const
            {
                this->_write_array(o);
            }

            //-----------------------------------------------------------------
            template<typename ...OTS>
                void write(const SArray<OTS...> &o) const
            {
                this->_write_array(o);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief read to POD

            Read data from an attribute to a POD value. 
            \throws ShapeMissmatchError if attribute is not scalar
            \throws H5AttributeError in case of general IO errors
            \param value POD value to which data will be stored
            */
            template<typename T> void read(T &value) const
            {
                if(!_dspace.is_scalar())
                    throw ShapeMissmatchError(EXCEPTION_RECORD, 
                            "Attribute ["+this->name()+"] not scalar!");

                __read_to_ptr(&value);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief read to string

            Reads a string value from an attribute.
            \throws ShapeMissmatchError if attribute is not scalar
            \throws H5AttributeError in case of general IO errors
            \param s string variable to which data will be written
            */
            void read(String &s) const;
            
            //-----------------------------------------------------------------
            /*! 
            \brief read data to DBuffer

            Read data from the attribute and store it to an 
            instance of a buffer object. The buffer object might
            be an instance of Buffer<T> or RefBuffer<T>. 
            \throws MemoryAllocationError if buffer not allocated
            \throws SizeMissmatchError if buffer and attribute size do not match
            \throws H5AttributeError in case of general IO errors 
            \param buffer buffer object 
            */
            template<typename ...OTS> void read(DBuffer<OTS...> &buffer) const
            {
                this->_read_buffer(buffer);
            }

            template<typename ...OTS> void read(SBuffer<OTS...> &buffer) const
            {
                this->_read_buffer(buffer);
            }

            template<typename ...OTS> void read(RBuffer<OTS...> &buffer) const
            {
                this->_read_buffer(buffer);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief read to Array<T>

            Read data to array a.
            \throws MemoryAllocationError if array buffer not allocated
            \throws ShapeMissmatchERror if array and attribute shape do not match
            \throws H5AttributeError in case of general IO errors
            \param a array where to store data
            */
            template<typename ...OTS> void read(NumArray<OTS...> &a) const
            {
                this->_read_array(a);
            }

            template<typename ...OTS> void read(DArray<OTS...> &a) const
            {
                this->_read_array(a);
            }

            template<typename ...OTS> void read(SArray<OTS...> &a) const
            {
                this->_read_array(a);
            }
           
            //============attribute inquery methods====================
            //! obtain attribute shape

            //! Returns the shape of the attribute.
            //! \return shape object
            template<typename CTYPE> CTYPE shape() const
            {
                return this->_dspace.template shape<CTYPE>();
            }

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
    

            

//end of namespace
}
}
}


#endif

