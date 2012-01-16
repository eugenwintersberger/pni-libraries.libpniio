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
#include "H5Selection.hpp"
#include "H5ObjectType.hpp"


namespace pni{
    namespace nx{
        namespace h5{
            

            class H5Dataset:public H5AttributeObject{
                private:
                    H5Dataspace _space; //!< local dataspace of the dataset
                    H5Datatype  _type;  //!< local datatype of the dataset

                    //---------some private IO templates----------------------
                    template<typename T> void __write(const T *ptr);
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
                    //! constructor 
                    H5Dataset(const String &n, const H5Group &g,const TypeID &t,
                              const Shape &s,const Shape &cs=Shape(0));
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


                    //===============reading data methods======================
                    template<typename T> 
                        void read(T &value);
                    template<typename T> 
                        void read(const H5Selection &s,T&value);
                    template<typename T,template<typename> class BT> 
                        void read(BT<T> &buffer);
                    template<typename T,template<typename> class BT>
                        void read(Array<T,BT> &array);
                    template<typename T> 
                        void read(Scalar<T> &data);

                    //===============writing data methods======================
                    template<typename T>
                        void write(const T &value);
                    template<typename T>
                        void write(const H5Selection &s,const T &value);
                    template<typename T,template<typename> class BT>
                        void write(const BT<T> &buffer);
                    template<typename T,template<typename> class BT>
                        void write(const H5Selection &s,const BT<T> &buffer);
                    template<typename T,template<typename> class BT>
                        void write(const Array<T,BT> &array);
                    template<typename T,template<typename> class BT>
                        void write(const H5Selection &s,const Array<T,BT>
                                &array);
                    template<typename T> 
                        void write(const Scalar<T> &scalar);
                    template<typename T>
                        void write(const H5Selection &s,const Scalar<T>
                                &scalar);


            };
            //==========implementation of private IO methods===================
            template<typename T>
                void H5Dataset::__write(const T *ptr){
                EXCEPTION_SETUP("template<typename T> void H5Dataset::"
                        "__wite(const T *ptr)");

                H5Datatype mem_type = H5Datatype::create<T>();
                herr_t err = H5Dwrite(id(),mem_type.id(),H5S_ALL,H5S_ALL,
                                      H5P_DEFAULT,(const void *)ptr);
                if(err<0){
                    EXCEPTION_INIT(H5DataSetError,
                            "Error writing data to dataset!");
                    EXCEPTION_THROW();
                }
            }

            //=============implementation of writing templates=================
            template<typename T>
                void H5Dataset::write(const T &value){
                EXCEPTION_SETUP("template<typename T> void H5Dataset::"
                        "write(const T &value)");

                if(!_space.is_scalar()){
                    EXCEPTION_INIT(ShapeMissmatchError,
                            "Dataset is not scalar!");
                    EXCEPTION_THROW();
                }
                __write(&value);
            }

            //-----------------------------------------------------------------
            template<typename T>
                void H5Dataset::write(const H5Selection &s,const T &value){
                EXCEPTION_SETUP("template<tyename T> void H5Dataset::"
                        "write(const H5Selection &s,const T &value)");
                
                if(!s.space().is_scalar()){
                    
                }
                
            }

            //-----------------------------------------------------------------
            template<typename T,template<typename> class BT>
                void H5Dataset::write(const BT<T> &buffer){
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

                __wite(buffer.ptr());
            }

            //-----------------------------------------------------------------
            template<typename T>
                void H5Dataset::write(const Scalar<T> &scalar){
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
                void H5Dataset::write(const Array<T,BT> &array){
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
