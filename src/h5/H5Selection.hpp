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
 * Definition of a HDF5 selection class.
 *
 * Created on: Jan 16, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#ifndef __H5SELECTION_HPP__
#define __H5SELECTION_HPP__

#include <pni/utils/DBuffer.hpp>

using namespace pni::utils;

#include "H5Dataspace.hpp"
#include "H5Dataset.hpp"
#include "H5DatatypeFactory.hpp"

namespace pni{
namespace nx{
namespace h5{

    /*! 
    \ingroup nxh5_classes
    \brief selection object

    A selection allows to read only a part of the data stored in a dataset. In
    other words one can read only a strip or a single frame from a 3D dataset.
    This implies a simple problem: how to describe the shape of the selection.
    For obvious reasons to define a selection with respect to the target HDF5
    dataset the rank of the selections shape must be equal to that of the
    dataset. However, the array (in general it will be an array) which will hold
    the data can have a different shape (think of a 2D slice from a 3D block of
    data). This implies that we have to manage to kinds of shapes: the selection
    shape (the shape with respect to the HDF5 dataset) and the memory shape
    which describes the shape of the object in memory holding the data.
    */
    class H5Selection
    {
        private:
            //! selection offset
            DBuffer<hsize_t> _offset;    
            //! selection stride
            DBuffer<hsize_t> _stride;   
            //! number of elements along each dimension 
            DBuffer<hsize_t> _counts;   
            //! local reference to the dataset to which the selection belongs
            const H5Dataset *_dataset;  


        public:
            //=================constructors and destructor=====================
            //! default constructor
            H5Selection() {}

            //-----------------------------------------------------------------
            //! copy constructor
            H5Selection(const H5Selection &o):
                _offset(o._offset),
                _stride(o._stride),
                _counts(o._counts),
                _dataset(o._dataset)
            { }

            //-----------------------------------------------------------------
            //! move constructor
            H5Selection(H5Selection &&o): 
                _offset(std::move(o._offset)),
                _stride(std::move(o._stride)),
                _counts(std::move(o._counts)),
                _dataset(o._dataset)
            { }

            //-----------------------------------------------------------------
            /*! 
            \brief construction with shape
            
            Construct a selection object from a shape object.  The shape object
            only defines the counts along each dimension.  The stride and offset
            are set with default values and must be adjusted after object
            instantiation. The rank of the dataset and the shape object must be
            equal.
            \throws ShapeMissmatchError if selection and dataset rank do not
            match
            \param ds dataset from which to draw the selection
            \param s shape (counts and rank) of the selection
            \param offset default offset (0)
            \param stride default stride (1)
            */
            template<typename CTYPE>
            H5Selection(const H5Dataset &ds,const CTYPE &s,size_t offset,
                        size_t stride):
                _offset(s.size()),
                _stride(s.size()),
                _counts(s.size()),
                _dataset(&ds)
            {

                if(s.size() != ds.rank()) 
                {
                    std::stringstream ss;
                    ss<<"Rank of selection ("<<s.size()<<") does not match";
                    ss<<" dataset rank ("<<ds.rank()<<")!";
                    throw ShapeMissmatchError(EXCEPTION_RECORD,ss.str());
                }

                //set offset and stride
                std::fill(_offset.begin(),_offset.end(),offset);
                std::fill(_stride.begin(),_stride.end(),stride);
                std::copy(s.begin(),s.end(),_counts.begin());
            }


            //-----------------------------------------------------------------
            //! destructor
            virtual ~H5Selection();

            //===================assignment operators==========================
            //! copy assignment operator
            H5Selection &operator=(const H5Selection &o);

            //-----------------------------------------------------------------
            //! move assignment operator
            H5Selection &operator=(H5Selection &&o);

            //====================inquery methods==============================
            /*! 
            \brief number of elements in the selection

            Returns the number of elements in the selection. 
            \return number of elements
            */
            size_t size() const;

            //-----------------------------------------------------------------
            /*! 
            \brief rank of the selection

            Return the rank (number of dimensions) of the selection.
            \return number of dimensions
            */
            size_t rank() const
            {
                return _counts.size();
            }

            //-----------------------------------------------------------------
            /*! 
            \brief shape of the selection

            Returns the shape of the selection which contains the rank and the
            count values along each dimension.
            \return selection shape
            */
            template<typename CTYPE> CTYPE shape() const
            {
                if(rank() == 0 ) return CTYPE();

                CTYPE d(rank());
                std::copy(_counts.begin(),_counts.end(),d.begin());

                return d;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief selection dataspace

            Returns a copy of the dataspace descriping the selection.  This
            dataspace can be used as a memory dataspace for IO operations on the
            selection.
            \return selection dataspace
            */
            H5Dataspace space() const;

            //-----------------------------------------------------------------
            /*! 
            \brief read offset 

            Returns a copy of offset value i. 
            \throws IndexError if i exceeds selection rank
            \param i index of the requested offset value
            \return offset value
            */
            hsize_t offset(size_t i) const { return _offset.at(i); }

            //-----------------------------------------------------------------
            /*! 
            \brief set offset

            Set the offset value for dimension i.
            \throws IndexError if i exceeds selection rank
            \param i dimension index
            \param o offset value along i
            */
            void offset(size_t i,hsize_t o) { _offset.at(i) = o; }

            //-----------------------------------------------------------------
            /*!
            \brief set offset with initializer list

            Use this method to set the offset of the selection using an
            initialzer list.
            \throws SizeMissmatchError if list length and selection rank
            do not match
            \param l initializer list with offset values
            */
            void offset(const std::initializer_list<hsize_t> &l);

            //-----------------------------------------------------------------
            /*!
            \brief get offset buffer

            This method must be used to obtain a reference to the 
            offset buffer of the selection.
            \return reference to the offset buffer
            */
            const DBuffer<hsize_t> &offset() const { return _offset; }
          
            //-----------------------------------------------------------------
            /*! 
            \brief copy of stride along i

            Returns a copy of the stride value along dimension i.
            \throws IndexError if i exceeds selection rank
            \param i dimension index
            \return stride value along dimension i
            */
            hsize_t stride(size_t i) const { return _stride.at(i); }

            //-----------------------------------------------------------------
            /*! 
            \brief set stride along i

            Set the stride value along dimension i to s.
            \throws IndexError if i exceeds selection rank
            \param i dimension index
            \param s stride along i
            */
            void stride(size_t i,hsize_t s) { _stride.at(i) = s; }

            //-----------------------------------------------------------------
            /*! 
            \brief set stride with initializer list

            Set the stride values using an initializer list.
            \throws SizeMissmatchError if list length and selection rank
            do not match
            \param l initializer list with stride values
            */
            void stride(const std::initializer_list<hsize_t> &l);

            //-----------------------------------------------------------------
            /*! 
            \brief get stride buffer

            Return a constant reference to the buffer with the stride values of
            the selection.
            \return reference to the stride buffer
            */
            const DBuffer<hsize_t> &stride() const { return _stride; }


            //-----------------------------------------------------------------
            /*! 
            \brief copy of count along i

            Returns a copy of the count value along dimension i.
            \throws IndexError if i exceeds selection rank
            \param i dimension index
            \return count along dimension i
            */
            hsize_t count(size_t i) const { return _counts.at(i); } 

            //-----------------------------------------------------------------
            /*! 
            \brief set count value

            Sets the count value along dimension i to c.
            \throws IndexError if i exceeds selection rank
            \param i dimension index
            \param c count value
            */
            void count(size_t i,hsize_t c) { _counts.at(i) = c; }

            //-----------------------------------------------------------------
            /*! 
            \brief set count with initializer list

            Set the count values using an initializer list.
            \throw SizeMissmatchError if list length and selection rank
            do not match
            \param l initializer list with count values
            */
            void count(const std::initializer_list<hsize_t> &l);

            //-----------------------------------------------------------------
            /*! 
            \brief get count buffer

            Returns a constant reference to the buffer with the count values of
            the selection.
            \return reference to the count buffer
            */
            const DBuffer<hsize_t> &count() const { return _counts; }

            //-----------------------------------------------------------------
            /*! 
            \brief get type id 

            Return the typeid of the dataset connected to the selection.  This
            makes it possible to make all information important 
            for data IO also accessible via the selection object.
            \return TypeID value
            */
            TypeID type_id() const { return _dataset->type_id(); }
           
            //-----------------------------------------------------------------
            /*! 
            \brief write a single value with selection

            write a single value at the location specified by selection.  To use
            a selection the dataset must not be scalar. 
            \throws ShapeMissmatchError if the dataset is scalar
            \throws H5DataSetError in cases of other errors
            \param value object from which to read data
            */
            template<typename T,typename CTYPE> 
                void write(const CTYPE s,const T *ptr) const
            {
                herr_t err;
                //create memory data type
                H5Datatype mt(H5DatatypeFactory::create_type<T>());
                //create memory data space
                H5Dataspace ms(s);
                
                //set selection to the file datasets original dataset
                err = H5Sselect_hyperslab(_dataset->space().id(),
                        H5S_SELECT_SET,
                        this->offset().ptr(), //set the offset pointer
                        this->stride().ptr(), //set the stride pointer
                        this->count().ptr(),  //set the count pointer
                        NULL);
                if(err<0)
                    throw H5DataSetError(EXCEPTION_RECORD,
                            "Error applying selection!");

                //write data to disk
                err = H5Dwrite(_dataset->id(),
                        mt.id(),          //set memory data type
                        ms.id(),           //set selection data space
                        _dataset->space().id(),  //set file data space
                        H5P_DEFAULT,
                        (const void *)ptr);
                if(err<0)
                    throw H5DataSetError(EXCEPTION_RECORD,
                            "Error writing data via selection to dataset"
                            " ["+_dataset->name()+"]!");

                //remove selection from the dataspace
                H5Sselect_none(_dataset->space().id());
            
            } 

            //-----------------------------------------------------------------
            /*! 
            \brief write a single string value

            Stings need a slightly different handling than all other data. Thats
            why this method was overloaded.  The selection must be scalar in
            order for this operation to succeed.
            \throws ShapeMissmatchError if selection is not scalar
            \throws H5DataSetError in case of other IO errors
            \param value the string to write
            */
            void write(const String &value) const;

            //-----------------------------------------------------------------
            /*! 
            \brief read a simple value from the selection

            Read a simple POD value from the selection. 
            \throws ShapeMissmatchValue if selection is not scalar
            \throws H5DataSetError in case of other IO errors
            \param value variable where to store the data
            */
            template<typename T,typename CTYPE> 
                void read(const CTYPE s,T *ptr) const
            {
                herr_t err;
                //create memory data type
                H5Datatype mt = H5DatatypeFactory::create_type<T>();
                //create memory data space
                H5Dataspace ms(s);
                
                //set selection to the file datasets original dataset
                err = H5Sselect_hyperslab(_dataset->space().id(),
                        H5S_SELECT_SET,
                        this->offset().ptr(), //set the offset pointer
                        this->stride().ptr(), //set the stride pointer
                        this->count().ptr(),  //set the count pointer
                        NULL);
                if(err<0)
                    throw H5DataSetError(EXCEPTION_RECORD,
                            "Error applying selection!");

                //write data to disk
                err = H5Dread(_dataset->id(),
                        mt.id(),         //set memory data type
                        ms.id(),          //set the selection data space
                        _dataset->space().id(), //set the file data space
                        H5P_DEFAULT,
                        (void *)ptr);
                if(err<0)
                    throw H5DataSetError(EXCEPTION_RECORD,
                            "Error reading data via selection to dataset"
                            " ["+_dataset->name()+"]!");

                //remove selection from the dataspace
                H5Sselect_none(_dataset->space().id());
            } 

            //----------------------------------------------------------
            /*! \brief read a string value 

            Read a string value from the selection. This works only
            if the size of the selection is 1. 
            \throws ShapeMissmatchError if selection is not scalar
            \throws H5DataSetError in case of other IO errors
            \param value variable where to store the data
            */
            void read(String &value) const;

    };



//end of namespace
}
}
}

#endif

