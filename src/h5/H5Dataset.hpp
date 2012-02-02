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
 * Implementation of a general named HDF5 object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#ifndef __H5DATASET_HPP__
#define __H5DATASET_HPP__

#include <pni/utils/Types.hpp>

using namespace pni::utils;

#include "H5AttributeObject.hpp"
#include "H5Datatype.hpp"
#include "H5Dataspace.hpp"
#include "H5Group.hpp"
#include "H5ObjectType.hpp"



namespace pni{
    namespace nx{
        namespace h5{
            class H5Selection;

            //! \ingroup nxh5_classes
            //! \brief dataset object

            //! Datasets are the essential data holding objects in HDF5.
            class H5Dataset:public H5AttributeObject{
                private:
                    H5Dataspace _space; //!< local dataspace of the dataset
                    H5Datatype  _type;  //!< local datatype of the dataset

                    //---------some private IO templates----------------------
                    template<typename T> void __write(const T *ptr) const;
                    template<typename T> void __read(T *ptr) const; 
                public:
                    //===================Constructors and destructors==========
                    //! default constructor
                    H5Dataset();
                    //! copy constructor
                    H5Dataset(const H5Dataset &o);
                    //! copy conversion constructor
                    H5Dataset(const H5Object &o);
                    //! move constructor
                    H5Dataset(H5Dataset &&o);
                    //! move conversion constructor
                    H5Dataset(H5Object &&o);
                    //! constructor - contiguous dataset
    
                    //! Creates a contiguous array of shape s. The result is 
                    //! most probably the simplest form of a dataset. 
                    //! Such a dataset cannot be resized. The shape of the 
                    //! dataspace is determined by the argument s which is 
                    //! the intial as well as the maximum size of the dataspace.
                    //! \param n name of the dataset
                    //! \param g parent group
                    //! \param t id of the data type
                    //! \param s shape of the dataset
                    H5Dataset(const String &n, const H5Group &g,const TypeID &t,
                              const Shape &s);
                    //! constructor - chunked dataset
                    
                    //! Constructor for a chunked dataset. Unlike contiguous
                    //! datasets chunked datasets can be resized. Its content 
                    //! is subdivided into several chunks. Furthermore chunked 
                    //! datasets can be compressed. Where the compression
                    //! algorithm is applied ot invidual chunks not on the 
                    //! entire dataset.
                    //! \param n dataset name
                    //! \param g parent group
                    //! \param t ID of the data type
                    //! \param s shape of the dataset
                    //! \param cs chunk shape
                    H5Dataset(const String &n,const H5Group &g,const TypeID &t,
                              const Shape &s,const Shape &cs);
                    //! constructor for a scalar object
                    H5Dataset(const String &n, const H5Group &g,
                            const TypeID &t);
                    //! construct from an object ID
                    H5Dataset(const hid_t &oid);
                    //! construction for a simple 
                    virtual ~H5Dataset();


                    //=================assignment operators====================
                    //! copy assignment operator
                    H5Dataset &operator=(const H5Dataset &o);
                    //! copy conversion assignment
                    H5Dataset &operator=(const H5Object &o);
                    //! move assignment operator
                    H5Dataset &operator=(H5Dataset &&o);
                    //! move conversion assignment
                    H5Dataset &operator=(H5Object &&o);

                    //=================methods to modify the dataset===========
                    //! modify the shape of the dataset

                    //! Modifies the entire shape of a dataset.
                    //! \param s new dataset shape
                    void resize(const Shape &s);
                    //! extend the shape along a dimension

                    //! Extends the dataset along one dimension.
                    //! \param e index of the extend dimension
                    void extend(const size_t &e,const size_t &n=1);
                    //! total number of elements

                    //! Returns the total number of elements stored in the 
                    //! dataset.
                    //! \return total number of elements
                    size_t size() const;
                    //! shape of dataset

                    //! Returns the shape of the dataset.
                    //! \return dataset shape
                    Shape  shape() const;

                    //! rank of the dataset

                    //! Returns the number of dimensions of the dataset.
                    //! \return number of dimensions
                    size_t rank() const;
                    //! number of elements

                    //! Returns the number of elements along dimension i. 
                    //! \throws IndexError if i exceeds dataset rank
                    //! \param i index of the dimension
                    //! \return number of elements along i
                    size_t dim(const size_t &i) const;
                    //! datat type

                    //! Datatype of the dataset. 
                    //! \return type id of the datatype of the dataset
                    TypeID type_id() const;

                    H5Selection selection(size_t stride=1,size_t offset=0) const;

                    const H5Dataspace &space() const{
                        return _space;
                    }


                    //===============reading data methods======================
                    template<typename T> void read(T &value) const;
                    template<typename T> 
                        void read(const H5Selection &s,T&value) const;
                    template<typename T,template<typename> class BT> 
                        void read(BT<T> &buffer) const;
                    template<typename T,template<typename> class BT>
                        void read(Array<T,BT> &array) const;
                    template<typename T> 
                        void read(Scalar<T> &data) const;

                    template<typename Object> Object read() const;
                    template<typename Object> 
                        Object read(const H5Selection &s) const;

                    //===============writing data methods======================
                    //! write a single value

                    //! This method writes a single value of a particular type
                    //! reading the data from variable value. This method 
                    //! works only if the dataspace of the dataset is scalar. 
                    //! \throws ShapeMissmatchError if the dataspace is not scalar
                    //! \throws H5DataSetError in case of other errors
                    //! \param value data source
                    template<typename T> void write(const T &value) const;


                    //! write a buffer 

                    //! Write the content of a memory buffer to the dataset.
                    //! The dataset must not be scalar. In order to succeed
                    //! the size of the buffer must match the size of the 
                    //! dataset.
                    //! \throws SizeMissmatchError sizes do not match
                    //! \throws H5DataSetError in cases of other errors
                    //! \param buffer reference to the buffer
                    template<typename T,template<typename> class BT>
                        void write(const BT<T> &buffer) const;


                    //! write an array

                    //! Write an array to the dataset. In order to succeed
                    //! The shape of the array must match the shape of the 
                    //! dataset. In addtion the dataset must not be scalar.
                    //! \throws ShapeMissmatchError if array and dataset shape do not match
                    //! \throws H5DataSetError in case of other errors
                    //! \param array array to write to disk
                    template<typename T,template<typename> class BT>
                        void write(const Array<T,BT> &array) const;


                    //! write a scalar

                    //! Write a single scalar object to disk. This can only 
                    //! succeed if the dataset is a scalar.
                    //! \throws ShapeMissmatchError if not a scalar dataset
                    //! \throws H5DataSetError in case of all other errors
                    //! \param scalar scalar object to write to disk
                    template<typename T> 
                        void write(const Scalar<T> &scalar) const;



            };
            //==========implementation of private IO methods===================
            //write template for a simple pointer
            template<typename T> void H5Dataset::__write(const T *ptr) const{
                EXCEPTION_SETUP("template<typename T> void H5Dataset::"
                        "__write(const T *ptr)");

                H5Datatype mem_type;

                //select the proper memory data type
                if(this->type_id() != TypeID::BINARY){
                    mem_type = H5Datatype::create<T>();
                }else{
                    mem_type = H5Datatype(TypeID::BINARY);
                }
                //write data to disk
                herr_t err = H5Dwrite(id(),mem_type.id(),H5S_ALL,H5S_ALL,
                                      H5P_DEFAULT,(const void *)ptr);
                if(err<0){
                    EXCEPTION_INIT(H5DataSetError,
                            "Error writing data to dataset!");
                    EXCEPTION_THROW();
                }
            }

            //----------------------------------------------------------------
            //read template for a simple pointer
            template<typename T> void H5Dataset::__read(T *ptr) const{
                EXCEPTION_SETUP("template<typename T> void H5Dataset::"
                        "__read(const T *ptr");
                
                H5Datatype mem_type;

                //select the proper memory data type
                if(this->type_id() != TypeID::BINARY){
                    mem_type = H5Datatype::create<T>();
                }else{
                    mem_type = H5Datatype(TypeID::BINARY);
                }
                //write data to disk
                herr_t err = H5Dread(id(),mem_type.id(),H5S_ALL,H5S_ALL,
                                      H5P_DEFAULT,(void *)ptr);
                if(err<0){
                    EXCEPTION_INIT(H5DataSetError,
                            "Error writing data to dataset!");
                    EXCEPTION_THROW();
                }


            }

            //=============implementation of writing templates=================
            //implementation of a simpel write template
            template<typename T>
                void H5Dataset::write(const T &value) const{
                EXCEPTION_SETUP("template<typename T> void H5Dataset::"
                        "write(const T &value)");

                if(_space.size()!=1){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Dataset is not scalar!");
                    EXCEPTION_THROW();
                }
                __write(&value);
            }

            //-----------------------------------------------------------------
            //implementation of simple read template
            template<typename T> void H5Dataset::read(T &value) const{
                EXCEPTION_SETUP("template<typename T> void H5Dataset::"
                        "read(T &value)");

                if(_space.size()!=1){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Dataset is not scalar!");
                    EXCEPTION_THROW();
                }
                __read(&value);
            }

            //-----------------------------------------------------------------
            template<typename T,template<typename> class BT>
                void H5Dataset::write(const BT<T> &buffer) const{
                EXCEPTION_SETUP("template<typename T,template<typename> "
                        "class BT> void H5Dataset::write(const BT<T> &buffer)");
                
                if(_space.is_scalar()){
                    EXCEPTION_INIT(ShapeMissmatchError,"Dataset is scalar!");
                    EXCEPTION_THROW();
                }

                if(_space.size() != buffer.size()){
                    EXCEPTION_INIT(SizeMissmatchError,
                            "Buffer and dataset size do not match!");
                    EXCEPTION_THROW();
                }

                __write(buffer.ptr());
            }

            //-----------------------------------------------------------------
            template<typename T>
                void H5Dataset::write(const Scalar<T> &scalar) const{
                EXCEPTION_SETUP("template<typename T> void H5Dataset::"
                        "write(const Scalar<T> &scalar)");

                if(!_space.is_scalar()){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Dataset is not scalar!");
                    EXCEPTION_THROW();
                }

                __write(scalar.ptr());
            }

            
            //-----------------------------------------------------------------
            template<typename T,template<typename> class BT>
                void H5Dataset::write(const Array<T,BT> &array) const{
                EXCEPTION_SETUP("template<typename T,template<typename> "
                        "class BT> void H5Dataset::write(const Array<T,BT> "
                        "&array)");

                if(_space.is_scalar()){
                    EXCEPTION_INIT(ShapeMissmatchError,"Dataset is scalar!");
                    EXCEPTION_THROW();
                }

                if(_space.shape() != array.shape()){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Dataset and array shape do not match");
                    EXCEPTION_THROW();
                }

                __write(array.ptr());
            }

        
        //end of namespace
        }
    }
}


#endif
