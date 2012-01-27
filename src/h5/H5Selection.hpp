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
                    H5Dataspace _sspace; //!< dataspace describing the selection
                    Buffer<size_t> _offset; //!< selection offset
                    Buffer<size_t> _stride; //!< selection stride
                    Buffer<size_t> _counts; //!< number of elements along each dimension
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
                    //! destructor
                    virtual ~H5Selection();

                    //===========assignment operators==========================
                    //! copy assignment operator
                    H5Selection &operator=(const H5Selection &o);
                    //! move assignment operator
                    H5Selection &operator=(H5Selection &&o);

                    size_t size() const;
                    Shape shape() const;
                    void shape(const Shape &s);
                    const H5Dataspace &space() const;

                    //set offset values
                    size_t &offset(size_t i);
                    size_t offset(size_t i) const;
                    void offset(size_t i,...) const;
                    
                    size_t &stride(size_t i);
                    size_t stride(size_t i) const;
                    void stride(size_t i,...) const;

                    size_t &count(size_t i);
                    size_t count(size_t i) const;
                    void count(size_t i,...) const;

            };

        //end of namespace
        }
    }
}

#endif

