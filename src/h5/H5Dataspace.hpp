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

            //! \ingroup nxh5_classes
            //! \brief dataspace object

            //! This class encapsulates an HDF5 dataspace. A dataspace describes
            //! the organization of dataelements within a dataset. 
            //! A dataspace can be resized in the sense that the number of 
            //! elements along each dimension can be changed. However, the
            //! number of dimensions itself remains fixed.
            class H5Dataspace:public H5Object{
                private:

                    Buffer<hsize_t> _maxdims; //!< maximum number of elements dimensions
                    Buffer<hsize_t> _dims;    //!< number of elements 

                    //a private method to compute the shape object describing
                    //the dataspace

                    //! create a dataspace from buffers

                    //! This method will create dataspace according to the 
                    //! values stored in the buffer objects. The resulting 
                    //! dataspace will always be simple
                    void __create_dataspace();

                    //! set buffers from object

                    //! Use this method if a dataspace is created from an 
                    //! HDF5 id. The method will fill the buffers according
                    //! to the dataspace described by the ID. 
                    void __set_buffers();
                public:
                    //! static data member describing an unlimited 
                    //! dimension. 
                    static const hsize_t UNLIMITED = H5S_UNLIMITED;

                    //! default constructor

                    //! By default a scalar dataspace is constructed. This 
                    //! constructor can always be used in order to store a
                    //! scalar value.
                    explicit H5Dataspace();
                    //! copy constructor
                    H5Dataspace(const H5Dataspace &o);
                    //! copy conversion constructor
                    H5Dataspace(const H5Object &o);
                    //! move constructor
                    H5Dataspace(H5Dataspace &&o);
                    //! move conversion constructor
                    H5Dataspace(H5Object &&o);
                    //! shape constructor

                    //! This is the most simple constructor for a non-trivial
                    //! dataspace. It constructs a dataspace of constant size 
                    //! using a shape object for its description. 
                    //! \param s shape object determining the shape
                    explicit H5Dataspace(const Shape &s);

                    //! construct an unlimited array from an init. list

                    //! Use an initializer list to construct a dataspace.
                    //! The dataspace created by this constructor is always a 
                    //! simple constructor and has constant size. 
                    //! \param list initializer list
                    //! \sa H5Dataspace(cosnt Shape &s)
                    H5Dataspace(const std::initializer_list<hsize_t> &list);
                   
                    //! fixed size datasset
                    
                    //! Creates a dataspace of fixed size. The dataspace 
                    //! created by this constructor is always a simple 
                    //! dataspace.
                    //! \param s initial shape
                    //! \param mx maximum shape
                    explicit H5Dataspace(const Shape &s,const Shape &ms);

                    //! fixed size dataspace

                    //! Create a fixed size dataspace from two initializer 
                    //! lists. The created dataspace is a simple dataspace in 
                    //! HDF5 terminilogy.
                    H5Dataspace(const std::initializer_list<hsize_t> &dlist,
                                const std::initializer_list<hsize_t> &mlist);
                    //! create object from HDF5 id

                    //! Constructor creating an object directly from its HDF5
                    //! ID. k
                    explicit H5Dataspace(const hid_t &id);

                    //! destructor

                    //! As the destructor is not virtual this class must not 
                    //! be used as a base class for other classes.
                    ~H5Dataspace();

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
                    Shape shape() const;

                    //! obtain the maximum shape
                    Shape maxshape() const;

                    //! rank of dataset

                    //! Returns the rank (the number of dimensions) of the
                    //! dataset.
                    //! \return number of dimension
                    size_t rank() const;
                    //! number of elements

                    //! Returns the number of elements along dimension i.
                    //! \throws IndexError if i exceeds the dataspace rank
                    //! \param i dimension index
                    //! \return number of elements along i
                    size_t dim(size_t i) const;

                    //! max.elements along dimension

                    //! Returns the maximum number of dimension along 
                    //! dimension i.
                    //! \param i index of dimension
                    //! \return maximum number of elements along dimension i
                    size_t max_dim(size_t i) const;

                    //! total number of elements

                    //! Returns the total number of elemenets that can be
                    //! stored in the dataspace.
                    //! \return total number of elements
                    size_t size() const;
                    //! number of elements
                    
                    //! Returns the number of elements along dimension i.
                    //! \throws IndexError if i exceeds dataspace rank
                    //! \param i dimension index
                    //! \return number of elements along i
                    size_t operator[](size_t i) const;

                    //! true if scalar dataset

                    //! Returns true if the dataspace is scalar. 
                    bool is_scalar() const;

                    //! resize dataset

                    //! Resizes the dataspace to a new shape determined by 
                    //! s. If the dataspace was originally scalar the 
                    //! new dataspace becomes simple. In this case the 
                    //! maximum number of elements along each dimension 
                    //! will be determined by s too. 
                    //! 
                    //! 
                    //! \param s new dataspace shape
                    void resize(const Shape &s);
                    void resize(const std::initializer_list<hsize_t> &list);

                    //! resize the dataset

                    //! resize dataset

                    //! Resizes the dataspace to a simple dataspace with 
                    //! initial shape s and maximum shape ms. In this 
                    //! case the datspace is of fixed size. 
                    //! \param s initial shape of the dataspace
                    //! \param ms maximum shape of the dataspace
                    void resize(const Shape &s,const Shape &ms);
                    void resize(const std::initializer_list<hsize_t> &dlist,
                                const std::initializer_list<hsize_t> &mlist);
                    void grow(size_t dim=0,size_t ext=1) ;

                    //! close the dataspace
                    virtual void close();

                    friend std::ostream &operator<<(std::ostream &o,
                            const H5Dataspace &s);

            };

        }
    }
}



#endif

