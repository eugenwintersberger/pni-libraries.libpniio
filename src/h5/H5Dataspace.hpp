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
 * Declaration of a general HDF5 Dataspace object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __H5DATASPACE_HPP__
#define __H5DATASPACE_HPP__

#include <pni/utils/Shape.hpp>

using namespace pni::utils;

#include "H5Object.hpp"

namespace pni{
    namespace nx {
        namespace h5 {
            
            class H5Dataspace:public H5Object{
                private:
                    Shape _shape; //!< shape object describing the dataspace

                    Buffer<hsize_t> _maxdims; //!< maximum number of elements dimensions
                    Buffer<hsiye_t> _dims;    //!< number of elements 

                    //a private method to compute the shape object describing
                    //the dataspace
                    void __set_shape_object();
                public:
                    //! default constructor

                    //! By default a scalar dataspace is constructed.
                    H5Dataspace();
                    //! copy constructor
                    H5Dataspace(const H5Dataspace &o);
                    //! copy conversion constructor
                    H5Dataspace(const H5Object &o);
                    //! move constructor
                    H5Dataspace(H5Dataspace &&o);
                    //! move conversion constructor
                    H5Dataspace(H5Object &&o);
                    //! shape constructor

                    //! Constructs a dataspace according to the shape
                    //! object passed to the constructor.
                    //! \param s shape object determining the shape
                    H5Dataspace(const Shape &s,int extdim=0);
                    H5Dataspace(const Shape &s,const Shape &ms,int extdim=0);
                    //! create object from HDF5 id

                    //! Constructor creating an object directly from its HDF5
                    //! ID.
                    H5Dataspace(const hid_t &id);

                    virtual ~H5Dataspace();

                    //================Assignment operators=====================
                    //! copy assignment operator
                    H5Dataspace &operator=(const H5Dataspace &o);
                    //! copy conversion operator
                    H5Dataspace &operator=(const H5Object &o);
                    //! move assignment operator
                    H5Dataspace &operator=(H5Dataspace &&o);
                    //! move conversion assignment operator
                    H5Dataspace &operator=(H5Object &&o);

                    //! obtain current shape
                    const Shape &shape() const;
                    //! rank of dataset
                    size_t rank() const;
                    //! dimension of the dataset
                    size_t dim(size_t i) const;
                    //! number of elements 
                    size_t size() const;
                    size_t operator[](size_t i) const;
                    //! true if scalar dataset
                    bool is_scalar() const;

                    //! resize dataset
                    void resize(const Shape &s,int extdim=0);
                    void resize(const Shape &s,const Shape &ms,int extdim=0);

            };

        }
    }
}



#endif

