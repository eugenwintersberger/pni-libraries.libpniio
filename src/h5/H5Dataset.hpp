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

                    //---------some private IO templates----------------------
                    template<typename T> void __write(const T *ptr) const;
                    template<typename T> void __read(T *ptr) const; 

                    //--------------------------------------------------------
                    H5Dataspace __obtain_dataspace() const{
                        return  H5Dataspace(H5Dget_space(id()));
                    }

                    H5Datatype __obtain_datatype() const{
                        return H5Datatype(H5Dget_type(id()));
                    }
                public:
                    //===================Constructors and destructors==========
                    //! default constructor
                    explicit H5Dataset();
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
                    explicit H5Dataset(const String &n, const H5Group &g,
                            const H5Datatype &t, const H5Dataspace &s);
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
                    explicit H5Dataset(const String &n,const H5Group &g,
                            const H5Datatype &t, const H5Dataspace &s,const Shape &cs);
                    //! constructor for a scalar object
                    explicit H5Dataset(const String &n, const H5Group &g,
                            const H5Datatype &t);
                    //! construct from an object ID
                    explicit H5Dataset(const hid_t &oid);
                    //! construction for a simple 
                    ~H5Dataset();

                    //=================factory methods=========================
                    //create multidimensional dataset
                    template<typename T> static H5Dataset create(
                            const String &n,const H5Group &g,const Shape &s,
                            const Shape &cs)
                    {
                        //create the datatype
                        H5Datatype type = H5DatatypeFactory::create_type<T>();

                        //create the data space
                        Shape ms(s.rank());
                        for(size_t i=0;i<s.rank();i++){
                            ms.dim(i,H5Dataspace::UNLIMITED);
                        }
                        H5Dataspace space(s,ms);

                        //create the data type
                        return H5Dataset(n,g,type,space,cs);
                    }




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

                    
                    H5Group parent() const;

                    //===============reading data methods======================
                    //! reading simple data from the dataset

                    //! Read a single data value from the dataset. In order 
                    //! to succeed the dataset must be a scalar dataset or 
                    //! the total size of the dataset must be 1.
                    //! \throws ShapeMissmatchError if dataset is not scalar
                    //! \throws H5DataSetError in all other error cases
                    //! \param value variable where to store the data
                    template<typename T> void read(T &value) const;

                    //! reading data to a buffer

                    //! Copy data from a dataset to the buffer. The size
                    //! of the dataset and the buffer must match.
                    //! \throws SizeMissmatchError if sizes do not match
                    //! \throws H5DataSetError in all other cases
                    //! \param buffer buffer where to store data
                    template<typename T,template<typename> class BT> 
                        void read(BT<T> &buffer) const;
                    template<typename T,template<typename> class BT>
                        void read(Array<T,BT> &array) const;
                    template<typename T> 
                        void read(Scalar<T> &data) const;

                    template<typename T>
                        void read(std::complex<T> &scalar) const;

                    //! read binary scalar
                    void read(Binary &b) const;
                    //! read a string scalar
                    void read(String &b) const;


                    template<typename Object> Object read() const;
                    template<typename Object> 
                        Object read(const H5Selection &s) const;

                    //===============writing data methods======================
                    //! write a single value

                    //! This method writes a single value of a particular type
                    //! reading the data from variable value. This method 
                    //! works only if the dataspace of the dataset is scalar or 
                    //! the total dataspace size is 1.
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

                    //! write a complex scalar
                    template<typename T> 
                        void write(const std::complex<T> &scalar) const;

                    //! write a binary scalar
                    void write(const Binary &b) const;
                    //! write a String value
                    void write(const String &b) const;

                    //! create a new link to this dataset

                    //! This method creates a new link to this dataset.
                    //! With this method only a local link can be established.
                    //! \param path name of the new link to this object
                    void link(const String &path) const;

                    //! creates a new link to this dataset

                    //! This creates a new link to this dataset with name n
                    //! below group g. Like link(const String &n) this method 
                    //! can only produce file local links.
                    void link(const H5Group &g,const String &n) const;




            };
            //==========implementation of private IO methods===================
            //write template for a simple pointer
            template<typename T> void H5Dataset::__write(const T *ptr) const{
                EXCEPTION_SETUP("template<typename T> void H5Dataset::"
                        "__write(const T *ptr)");


                //select the proper memory data type
                
                H5Datatype mem_type = H5DatatypeFactory::create_type<T>();

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
                
                H5Datatype mem_type = H5DatatypeFactory::create_type<T>();

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
                    EXCEPTION_INIT(ShapeMissmatchError,"Dataset is not scalar!");
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
                    EXCEPTION_INIT(ShapeMissmatchError,"Dataset is not scalar!");
                    EXCEPTION_THROW();
                }
                __read(&value);
            }

            //-----------------------------------------------------------------
            //implementation of writing data form a buffer
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
            //implementation of reading data to a buffer
            template<typename T,template<typename> class BT>
                void H5Dataset::read(BT<T> &buffer) const{
                EXCEPTION_SETUP("template<typename T,template<typename> "
                        "class BT> void H5Dataset::read(BT<T> &buffer) const");
                
                if(_space.is_scalar()){
                    EXCEPTION_INIT(ShapeMissmatchError,"Dataset is scalar!");
                    EXCEPTION_THROW();
                }

                if(_space.size() != buffer.size()){
                    EXCEPTION_INIT(SizeMissmatchError,
                            "Buffer and dataset size do not match!");
                    EXCEPTION_THROW();
                }

                __read(buffer.ptr());
            }

            //-----------------------------------------------------------------
            //implementation of writing data from a scalar
            template<typename T>
                void H5Dataset::write(const Scalar<T> &scalar) const{
                EXCEPTION_SETUP("template<typename T> void H5Dataset::"
                        "write(const Scalar<T> &scalar)");

                if(_space.size() != 1){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Dataset is not scalar!");
                    EXCEPTION_THROW();
                }

                __write(scalar.ptr());
            }

            //-----------------------------------------------------------------
            //implementation writing complex data
            template<typename T>
                void H5Dataset::write(const std::complex<T> &scalar) const
            {
                EXCEPTION_SETUP("template<typename T> void H5Dataset::"
                        "write(const std::complex<T> &scalar) constw");

                if(_space.size() != 1){
                    EXCEPTION_INIT(ShapeMissmatchError,"Dataset is not scalar!");
                    EXCEPTION_THROW();
                }

                __write(&scalar);
            }

            //-----------------------------------------------------------------
            //implementation of reading data to a scalar
            template<typename T>
                void H5Dataset::read(Scalar<T> &scalar) const{
                EXCEPTION_SETUP("template<typename T> void H5Dataset::"
                        "read(Scalar<T> &scalar) const");

                if(_space.size() != 1){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Dataset is not scalar!");
                    EXCEPTION_THROW();
                }

                __read(scalar.ptr());
            }

            //-----------------------------------------------------------------
            //read complex scalar
            template<typename T>
                void H5Dataset::read(std::complex<T> &scalar) const
            {
                EXCEPTION_SETUP("template<typename T> void H5Dataset::"
                        "read(std::complex<T> &scalar) const");
                if(_space.size() != 1){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Dataset is not scalar!");
                    EXCEPTION_THROW();
                }

                __read(&scalar);
            }


            
            //-----------------------------------------------------------------
            //implementation of writting data from an array
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

            //-----------------------------------------------------------------
            //implementation of reading data to an array
            template<typename T,template<typename> class BT>
                void H5Dataset::read(Array<T,BT> &array) const{
                EXCEPTION_SETUP("template<typename T,template<typename> "
                        "class BT> void H5Dataset::readArray<T,BT> &array) const");

                if(_space.is_scalar()){
                    EXCEPTION_INIT(ShapeMissmatchError,"Dataset is scalar!");
                    EXCEPTION_THROW();
                }

                if(_space.shape() != array.shape()){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Dataset and array shape do not match");
                    EXCEPTION_THROW();
                }

                __read(array.ptr());
            }

        
        //end of namespace
        }
    }
}


#endif
