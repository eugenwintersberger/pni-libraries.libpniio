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


namespace pni{
    namespace nx{
        namespace h5{

            class H5Selection{
                private:
                    Shape       _shape;      //!< shape of the selection
                    H5Dataspace _sspace;     //!< dataspace describing the selection
                    Buffer<hsize_t> _offset;  //!< selection offset
                    Buffer<hsize_t> _stride;  //!< selection stride
                    Buffer<hsize_t> _counts;  //!< number of elements along each dimension

                    void __update_shape();
                    void __update_dataspace();
                public:
                    //============constructors and destructor==================
                    //! default constructor
                    H5Selection();
                    //! copy constructor
                    H5Selection(const H5Selection &o);
                    //! move constructor
                    H5Selection(H5Selection &&o);
                    //! standard constructor
                    
                    //! The default constructor of a selection.
                    //! \param r rank of the dataset from which to pick data.
                    H5Selection(const size_t &r);
                    //! construction with shape
                    
                    //! Construct a selection object from a shape object. 
                    //! The shape object only defines the counts along each 
                    //! dimension. The stride and offset are set with default 
                    //! values and must be adjusted after object 
                    //! instantiation.
                    //! \param s shape (counts and rank) of the selection
                    //! \param offset default offset (0)
                    //! \param stride default stride (1)
                    H5Selection(const Shape &s,size_t offset=0,size_t stride=1);
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
                    const Shape &shape() const;

                    //! selection dataspace

                    //! Return a constant reference to the dataspace describing
                    //! the selection.
                    //! \return dataspace reference
                    const H5Dataspace &space() const;

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

                    //! get count buffer

                    //! Returns a constant reference to the buffer with the 
                    //! count values of the selection.
                    //! \return reference to the count buffer
                    const Buffer<hsize_t> &count() const;

            };

        //end of namespace
        }
    }
}

#endif

