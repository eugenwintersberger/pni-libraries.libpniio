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
 * Declaration of a HDF5 selection class.
 *
 * Created on: Jan 16, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#ifndef __H5SELECTION_HPP__
#define __H5SELECTION_HPP__

#include <pni/utils/Buffer.hpp>

using namespace pni::utils;

#include "H5Dataspace.hpp"
#include "H5Dataset.hpp"
#include "H5DatatypeFactory.hpp"

namespace pni{
    namespace nx{
        namespace h5{

            //! \ingroup nxh5_classes
            //! \brief selection object

            //! A selection allows to read only a part of the data stored
            //! in a dataset. In other words one can read only a strip or 
            //! a single frame from a 3D dataset. This implies a
            //! simple problem: how to describe the shape of the selection.
            //! For obvious reasons to define a selection with respect 
            //! to the target HDF5 dataset the rank of the selections shape 
            //! must be equal to that of the dataset. However, the array 
            //! (in general it will be an array) which will hold the data
            //! can have a different shape (think of a 2D slice from a 
            //! 3D block of data). This implies that we have to manage 
            //! to kinds of shapes: the selection shape (the shape with 
            //! respect to the HDF5 dataset) and the memory shape which 
            //! describes the shape of the object in memory holding the 
            //! data.
            class H5Selection{
                private:
                    Buffer<hsize_t> _offset;  //!< selection offset
                    Buffer<hsize_t> _stride;  //!< selection stride
                    Buffer<hsize_t> _counts;  //!< number of elements along each dimension
                    const H5Dataset *_dataset;     //!< local reference to the dataset
                                             //!< to which the selection
                                             //!< belongs.

                    template<typename T> void __write(const H5Datatype &mt,
                            const H5Dataspace &ms,const T *ptr) const;
                    template<typename T> void __read(const H5Datatype &mt,
                            const H5Dataspace &ms,T *ptr) const;
                public:
                    //============constructors and destructor==================
                    //! copy constructor
                    H5Selection(const H5Selection &o);
                    //! move constructor
                    H5Selection(H5Selection &&o);
                    //! construction with shape
                    
                    //! Construct a selection object from a shape object. 
                    //! The shape object only defines the counts along each 
                    //! dimension. The stride and offset are set with default 
                    //! values and must be adjusted after object 
                    //! instantiation.
                    //! \param s shape (counts and rank) of the selection
                    //! \param offset default offset (0)
                    //! \param stride default stride (1)
                    explicit H5Selection(const H5Dataset &ds,
                                const Shape &s,size_t offset=0,size_t stride=1);

                    H5Selection(const std::initializer_list<hsize_t> &offset,
                                const std::initializer_list<hsize_t> &stride,
                                const std::initializer_list<hsize_t> &count); 
                    //! destructor
                    virtual ~H5Selection();

                    //===========assignment operators==========================
                    //! copy assignment operator
                    H5Selection &operator=(const H5Selection &o);
                    //! move assignment operator
                    H5Selection &operator=(H5Selection &&o);

                    //! number of elements in the selection

                    //! Returns the number of elements in the selection. 
                    //! \return number of elements
                    size_t size() const;

                    //! rank of the selection

                    //! Return the rank (number of dimensions) of the selection.
                    //! \return number of dimensions
                    size_t rank() const;

                    //! shape of the selection

                    //! Returns the shape of the selection
                    Shape shape() const;

                    //! selection dataspace

                    //! Return a constant reference to the dataspace describing
                    //! the selection.
                    //! \return dataspace reference
                    H5Dataspace space() const;

                    //! read/write offset 

                    //! Returns a read write reference to offset value i.
                    //! \throws IndexError if i exceeds selection rank
                    //! \param i index of the requested offset value
                    //! \return reference to offset value
                    hsize_t &offset(size_t i);
                    //! read offset 

                    //! Returns a copy of offset value i. 
                    //! \throws IndexError if i exceeds selection rank
                    //! \param i index of the requested offset value
                    //! \return offset value
                    hsize_t offset(size_t i) const;
                    //! set offset

                    //! Set the offset value for dimension i.
                    //! \throws IndexError if i exceeds selection rank
                    //! \param i dimension index
                    //! \param o offset value along i
                    void offset(size_t i,hsize_t o);

                    //! set offset with initializer list

                    //! Use this method to set the offset of the selection
                    //! using an initialzer list.
                    void offset(const std::initializer_list<hsize_t> &l);


                    //! get offset buffer

                    //! This method must be used to obtain a reference to the 
                    //! offset buffer of the selection.
                    //! \return reference to the offset buffer
                    const Buffer<hsize_t> &offset() const;
                   
                    //! read/write stride

                    //! Returns a read/write reference to the stride value
                    //! along dimension i.
                    //! \throws IndexError if i exceeds selection rank
                    //! \param i dimension index
                    //! \return reference to the stride of dimension i
                    hsize_t &stride(size_t i);
                    //! copy of stride along i

                    //! Returns a copy of the stride value along dimension i.
                    //! \throws IndexError if i exceeds selection rank
                    //! \param i dimension index
                    //! \return stride value along dimension i
                    hsize_t stride(size_t i) const;
                    //! set stride along i

                    //! Set the stride value along dimension i to s.
                    //! \throws IndexError if i exceeds selection rank
                    //! \param i dimension index
                    //! \param s stride along i
                    void stride(size_t i,hsize_t s);

                    //! set stride with initializer list

                    //! Set the stride values using an initializer list.
                    void stride(const std::initializer_list<hsize_t> &l);

                    //! get stride buffer

                    //! Return a constant reference to the buffer with the 
                    //! stride values of the selection.
                    //! \return reference to the stride buffer
                    const Buffer<hsize_t> &stride() const;

                    //! read/write count

                    //! Returns a read write reference to the count value 
                    //! along dimension i.
                    //! \throws IndexError if i exceeds selection rank
                    //! \param i dimension index
                    //! \return reference to the count value along i
                    hsize_t &count(size_t i);
                    //! copy of count along i

                    //! Returns a copy of the count value along dimension i.
                    //! \throws IndexError if i exceeds selection rank
                    //! \param i dimension index
                    //! \return count along dimension i
                    hsize_t count(size_t i) const;
                    //! set count value

                    //! Sets the count value along dimension i to c.
                    //! \throws IndexError if i exceeds selection rank
                    //! \param i dimension index
                    //! \param c count value
                    void count(size_t i,hsize_t c);

                    //! set count with initializer list

                    //! Set the count values using an initializer list.
                    void count(const std::initializer_list<hsize_t> &l);

                    //! get count buffer

                    //! Returns a constant reference to the buffer with the 
                    //! count values of the selection.
                    //! \return reference to the count buffer
                    const Buffer<hsize_t> &count() const;
                    
                    //! write a single value with selection

                    //! write a single value at the location specified by 
                    //! selection. To use a selection the dataset must not
                    //! be scalar. 
                    //! \throws ShapeMissmatchError if the dataset is scalar
                    //! \throws H5DataSetError in cases of other errors
                    //! \param s selection object
                    //! \param value object from which to read data
                    template<typename T> void write(const T &value) const;

                    //! write a single string value

                    //! Stings need a slightly different handling than all 
                    //! other data. Thats why this method was overloaded.
                    //! \param value the string to write
                    void write(const String &value) const;

                    //! read a simple value from the selection
                    template<typename T> void read(T &value) const;


                    //! read a string value 

                    //! Read a string value from the selection. This works only
                    //! if the size of the selection is 1. 
                    //! \param value variable where to store the data
                    void read(String &value) const;

                    
                    //! write a buffer with selection

                    //! Writes teh content of a memory buffer to the dataset
                    //! in the region defined by the selection s. 
                    //! For this purpose the size of the selection must match
                    //! the size of the buffer.
                    //! \throws SizeMissmatchBuffer selection and buffer sizes do not match
                    //! \throws H5DataSetError in case of other errors
                    //! \param s selection object
                    //! \param buffer reference to the buffer object
                    template<typename T,template<typename> class BT>
                        void write(const BT<T> &buffer) const;

                    //! read a buffer from selection

                    //! Write the content of the selection into the buffer
                    //! buffer object. This operation will only succeed if the 
                    //! size of the selection matches the size of the buffer.
                    //! \param buffer Buffer object where to store the data
                    template<typename T,template<typename> class BT>
                        void read(BT<T> &buffer) const;
                    
                    //! write an array with selection

                    //! 
                    template<typename T,template<typename> class BT>
                        void write(const Array<T,BT> &array) const;

                    //! read an array

                    //! Read an array from the selection. This method will 
                    //! only succeed if the size of the selection matches
                    //! that of the array. 
                    //! \throws SizeMissmatchError if sizes do not match
                    //! \throws H5DataSetError in cases of other errors
                    //! \param array array where to store the data
                    template<typename T,template<typename> class BT>
                        void read(Array<T,BT> &array) const;
                    
                    //! write a scalar with selection

                    //! Write a scalar value in the region defined by the
                    //! selection. In order to succeed the dataset must not be 
                    //! scalar. 
                    //! \throws ShapeMissmatchError if the dataset is scalar
                    //! \throws H5DataSetError in case of all other errors
                    //! \param s selection object
                    //! \param scalar the scalar object which to write to disk
                    template<typename T>
                        void write(const Scalar<T> &scalar) const;

                    //! read a selection to a scalar

                    //! Write the content of a selection to a scalar. This 
                    //! methhod succeeds only if the size of the selection 
                    //! is 1. If this is not the case a SizeMissmatchError 
                    //! will be thrown.
                    //! \throws SizeMissmatchError if selection size not 1
                    //! \throws H5DatasetError in case of other errors
                    //! \param scalar object where to store data
                    template<typename T> 
                        void read(Scalar<T> &scalar) const;

            };


            //===============template implementation============================
            //write template for a simple pointer with a selection
            template<typename T> void H5Selection::__write(const H5Datatype &mt,
                    const H5Dataspace &ms,const T *ptr) const
            {
                EXCEPTION_SETUP("template<typename T> void H5Selection::"
                        "__write(const T *ptr)");
                herr_t err;
                
                //set selection to the file datasets original dataset
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
                        mt.id(),          //set memory data type
                        ms.id(),           //set selection data space
                        _dataset->space().id(),  //set file data space
                        H5P_DEFAULT,
                        (const void *)ptr);


                if(err < 0){
                    EXCEPTION_INIT(H5DataSetError,
                            "Error writing data to dataset!");
                    EXCEPTION_THROW();
                }

                //remove selection from the dataspace
                H5Sselect_none(_dataset->space().id());
            
            } 

            //-----------------------------------------------------------------
            //read template for a simple pointer with a selection
            template<typename T> void H5Selection::__read(const H5Datatype &mt,
                    const H5Dataspace &ms,T *ptr) const 
            {
                EXCEPTION_SETUP("template<typename T> void H5Selection::"
                        "__read(T *ptr)");
                herr_t err;
                
                //set selection to the file datasets original dataset
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
                err = H5Dread(_dataset->id(),
                        mt.id(),         //set memory data type
                        ms.id(),          //set the selection data space
                        _dataset->space().id(), //set the file data space
                        H5P_DEFAULT,
                        (void *)ptr);
                if(err < 0){
                    EXCEPTION_INIT(H5DataSetError,
                            "Error writing data to dataset!");
                    EXCEPTION_THROW();
                }

                //remove selection from the dataspace
                H5Sselect_none(_dataset->space().id());
            } 
            
            //-----------------------------------------------------------------
            //implementation of a simple write with selection
            template<typename T> void H5Selection::write(const T &value) const{
                EXCEPTION_SETUP("template<typename T> void H5Selection::"
                        "write(const T &value)");
                
                //here we have to check that the selection referes to 
                //a single value only
                if(this->size()!=1){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Selection is not scalar!");
                    EXCEPTION_THROW();
                }

                //create datatspace and datatype
                H5Datatype mt = H5DatatypeFactory::create_type<T>();
                H5Dataspace ms;

                __write(mt,ms,&value); 
                
            }


            //-----------------------------------------------------------------
            //implementation of a simple read with selection
            template<typename T> void H5Selection::read(T &value) const{
                EXCEPTION_SETUP("template<typename T> void H5Selection::"
                        "read(T &value)");
                
                //here we have to check that the selection referes to 
                //a single value only
                if(this->size()!=1){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Selection is not scalar!");
                    EXCEPTION_THROW();
                }

                //create memory dataspace and datatype
                H5Datatype mt = H5DatatypeFactory::create_type<T>();
                H5Dataspace ms;

                __read(mt,ms,&value); 
                
            }
            
            //-----------------------------------------------------------------
            template<typename T,template<typename> class BT>
                void H5Selection::write(const BT<T> &buffer) const{
                EXCEPTION_SETUP("template<typename T,template<typename> "
                        "class BT> void H5Selection::write(const BT<T> &buffer)");
                

                if(this->size() != buffer.size()){
                    EXCEPTION_INIT(SizeMissmatchError,
                            "Buffer and selection size do not match!");
                    EXCEPTION_THROW();
                }

                //create memory datatype and memory dataspace
                H5Datatype mt = H5DatatypeFactory::create_type<T>();
                Shape s(1); s.dim(0,buffer.size());
                H5Dataspace ms(s);

                __write(mt,ms,buffer.ptr());
            }

            //-----------------------------------------------------------------
            template<typename T,template<typename> class BT>
                void H5Selection::read(BT<T> &buffer) const{
                EXCEPTION_SETUP("template<typename T,template<typename> "
                        "class BT> void H5Selection::read(BT<T> &buffer) const");
                

                if(this->size() != buffer.size()){
                    EXCEPTION_INIT(SizeMissmatchError,
                            "Buffer and selection size do not match!");
                    EXCEPTION_THROW();
                }

                //create memory datatype and memory dataspace
                H5Datatype mt = H5DatatypeFactory::create_type<T>();
                Shape s(1); s.dim(0,buffer.size());
                H5Dataspace ms(s);

                __read(mt,ms,buffer.ptr());
            }
            
            //-----------------------------------------------------------------
            template<typename T> 
                void H5Selection::write(const Scalar<T> &scalar) const{
                EXCEPTION_SETUP("template<typename T> void H5Selection::"
                        "write(const Scalar<T> &scalar)");
                
                if(this->size()!=1){
                    EXCEPTION_INIT(SizeMissmatchError,
                            "Selection size not equal 1!");
                    EXCEPTION_THROW();
                }

                //create memory datatype and memory dataspace
                H5Datatype mt = H5DatatypeFactory::create_type<T>();
                H5Dataspace ms;

                __write(mt,ms,scalar.ptr());
            }
            
            //-----------------------------------------------------------------
            template<typename T> void H5Selection::read(Scalar<T> &scalar) const{
                EXCEPTION_SETUP("template<typename T> void H5Selection::"
                        "read(Scalar<T> &scalar) const");
                
                if(this->size()!=1){
                    EXCEPTION_INIT(SizeMissmatchError,
                            "Selection size not equal 1!");
                    EXCEPTION_THROW();
                }

                //create memory datatype and memory dataspace
                H5Datatype mt = H5DatatypeFactory::create_type<T>();
                H5Dataspace ms;

                __read(mt,ms,scalar.ptr());
            }
            
            //-----------------------------------------------------------------
            template<typename T,template<typename> class BT>
                void H5Selection::write(const Array<T,BT> &array) const{
                EXCEPTION_SETUP("template<typename T,template<typename> "
                        "class BT> void H5Selection::write("
                        "const Array<T,BT> &array)");


                //the size of the array must be equal to the size of the 
                //selection
                if(this->size() != array.shape().size()){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Selection and array size do not match!");
                    EXCEPTION_THROW();
                }

                //create memory datatype and dataspace
                H5Datatype mt = H5DatatypeFactory::create_type<T>();
                H5Dataspace ms(array.shape());

                __write(ms,mt,array.ptr());
            }

            //-----------------------------------------------------------------
            template<typename T,template<typename> class BT>
                void H5Selection::read(Array<T,BT> &array) const{
                EXCEPTION_SETUP("template<typename T,template<typename> "
                        "class BT> void H5Selection::read(Array<T,BT> &array) "
                        "const");


                //the size of the array must be equal to the size of the 
                //selection
                if(this->size() != array.shape().size()){
                    EXCEPTION_INIT(SizeMissmatchError,
                            "Selection and array size do not match!");
                    EXCEPTION_THROW();
                }

                //create memory datatype and dataspace
                H5Datatype mt = H5DatatypeFactory::create_type<T>();
                H5Dataspace ms(array.shape());

                __read(mt,ms,array.ptr());
            }
        //end of namespace
        }
    }
}

#endif

