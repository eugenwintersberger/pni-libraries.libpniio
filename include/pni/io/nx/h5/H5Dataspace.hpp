/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Declaration of a general HDF5 Dataspace object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <sstream>
#include <algorithm>
#include <pni/core/arrays.hpp>


#include "H5Object.hpp"

namespace pni{
namespace io{
namespace nx {
namespace h5 {

    using namespace pni::core;
    //avoid namespace collisions with std
    using pni::core::exception;
    using pni::core::string;

    /*!
    \ingroup nxh5_classes
    \brief dataspace object

    This class encapsulates an HDF5 dataspace. A dataspace describes the
    organization of dataelements within a dataset in the file or of data stored
    in memory. It basically describes a multidimensional array with a
    particular rank (number of dimensions) and a particular number of elements
    along each dimension. For each dimension there exists an actual number of
    elements which is the number of elements now allocated and a maximum number
    of elements. The later one gives the maximum number of elements along a
    dimension to which a dataset (not a dataspace) can grow. This number can be
    a finite one or can be set to H5Dataspace::UNLIMITED which allows the
    dataset to grow infinitely along this dimension. 
 
    At any time during the lifetime of a H5Dataspace object the dataspace it
    describes can be resized to any required shape (see the resize() and grow()
    methods).  This makes it easy to adopt the object to your needs.  There are
    many possibilities how to construct a dataspace.  

    A dataspace representing a scalar value has a rank of  0 and a size of 1. 
    */
    class H5Dataspace:public H5Object
    {
        private:
            typedef std::vector<hsize_t> size_vector_t;
            //! maximum number of elements dimensions
            size_vector_t _maxdims; 
            //! number of elements 
            size_vector_t _dims;    

            //-----------------------------------------------------------------
            /*!
            \brief setup dataspace

            This method will setup a dataspace according to the values of its
            member variables.
            \throws pni::io::nx::nxbackend_error in case of errors
            */
            void __setup_dataspace();

            //-----------------------------------------------------------------
            /*! 
            \brief set buffers from object

            Use this method if a dataspace is created from an HDF5 id. The
            method will fill the buffers according to the dataspace described by
            the ID. 
            */
            void __setup_buffers();
        public:
            //! static data member describing an unlimited dimension. 
            //static const hsize_t UNLIMITED = H5S_UNLIMITED;

            //==============constructors and destructor========================
            /*! 
            \brief default constructor

            By default a scalar dataspace is constructed. This constructor can
            always be used in order to store a scalar value.
            */
            explicit H5Dataspace();

            //-----------------------------------------------------------------
            //! copy constructor
            H5Dataspace(const H5Dataspace &o);

            //-----------------------------------------------------------------
            //! copy conversion constructor
            explicit H5Dataspace(const H5Object &o);

            //-----------------------------------------------------------------
            //! move constructor
            H5Dataspace(H5Dataspace &&o);

            //-----------------------------------------------------------------
            //! move conversion constructor
            explicit H5Dataspace(H5Object &&o);

            //-----------------------------------------------------------------
            //! construct from ID
            explicit H5Dataspace(hid_t id);
            
            //-----------------------------------------------------------------
            /*! 
            \brief construct form shape

            Constructor takes a container which holds the shape of the dataspace
            to create. The actual as well as the maximum number of dimensions
            will be set to these values.
            \code
            std::list<size_t> shape{4,5,19};
            H5Dataspace space(shape);
            \endcode
            \throws memory_allocation_error if buffer allocation fails
            \throws pni::io::nx::nxbackend_error if setup of the dataspace fails
            \tparam CTYPE container type for the shape
            \param s instance of CTYPE with the shape
            \sa H5Dataspace(const CTYPE1 &s,const CTYPE2 &ms)
            */
            template<typename CTYPE> explicit H5Dataspace(const CTYPE &s):
                H5Object(H5Screate(H5S_SCALAR)),
                _maxdims(s.size()),
                _dims(s.size())
            {
                std::copy(s.begin(),s.end(),_maxdims.begin());
                std::copy(s.begin(),s.end(),_dims.begin());

                __setup_dataspace();
            }

            //----------------------------------------------------------------- 
            /*! 
            \brief constructor with actual and maximum shape

            Constructor takes two containers of arbitrary type which hold the
            actual and the maximum shape of the dataspace.

            \code
            std::list<size_t> shape{4,5,19};
            std::vector<size_t> mshape{100,100,100};
            H5Dataspace space(shape,mshape);
            \endcode

            \throws memory_allocation_error if buffer allocation fails
            \throws shape_mismatch_error if the two containers have a different
            size and thus represent different ranks
            \throws pni::io::nx::nxbackend_error if setup of the dataspace fails

            \tparam CTYPE1 container type for the actual shape
            \tparam CTYPE2 container type for the maximum shape
            \param s initial shape
            \param ms maximum shape

            \sa H5Dataspace(const CTYPE &s)
            */
            template<typename CTYPE1,typename CTYPE2>
            explicit H5Dataspace(const CTYPE1 &s,const CTYPE2 &ms):
                H5Object(H5Screate(H5S_SCALAR)),
                _maxdims(ms.size()),
                _dims(s.size())

            {
                //check if the ranks of the shapes is equal
                if(s.size() != ms.size())
                {
                    std::stringstream ss;
                    ss<<"Rank of actual shape ("<<s.size()<<") and of ";
                    ss<<"maximum shape ("<<ms.size()<<") do not match!";
                    throw shape_mismatch_error(EXCEPTION_RECORD,ss.str());
                }

                std::copy(ms.begin(),ms.end(),_maxdims.begin());
                std::copy(s.begin(),s.end(),_dims.begin());

                //resize the dataspace to a simple one
                __setup_dataspace();
            }

            //-----------------------------------------------------------------
            /*!
            \brief construction with an initializer list

            Use an initializer list to construct a dataspace. The dataspace
            created by this constructor is always a simple constructor and has
            constant size. 

            \code
            H5Dataspace space({1,2,3});
            \endcode

            \throws memory_allocation_error if buffer allocation fails
            \throws pni::io::nx::nxbackend_error if data-space creation fails

            \param list initializer list
            \sa H5Dataspace(const Shape &s)
            */
            explicit H5Dataspace(const std::initializer_list<hsize_t> &list);
          
            //-----------------------------------------------------------------
            /*! 
            \brief fixed size dataspace

            Create a fixed size dataspace from two initializer lists. The
            created dataspace is a simple dataspace in HDF5 terminilogy.

            \throws memory_allocation_error if buffer allocation fails
            \throws shape_mismatch_error if the two lists are of different size
            \throws pni::io::nx::nxbackend_error if dataspace setup fails

            \param dlist initializer list with actual shape values
            \param mlist initializer list with maximum shape values
            */
            explicit H5Dataspace(const std::initializer_list<hsize_t> &dlist,
                        const std::initializer_list<hsize_t> &mlist);
           

            //-----------------------------------------------------------------
            /*! 
            \brief destructor

            As the destructor is not virtual this class must not be used as a
            base class for other classes.
            */
            ~H5Dataspace();
            
            //=====================Assignment operators========================
            //! copy assignment operator
            H5Dataspace &operator=(const H5Dataspace &o);

            //-----------------------------------------------------------------
            //! copy conversion operator
            H5Dataspace &operator=(const H5Object &o);

            //-----------------------------------------------------------------
            //! move assignment operator
            H5Dataspace &operator=(H5Dataspace &&o);

            //-----------------------------------------------------------------
            //! move conversion assignment operator
            H5Dataspace &operator=(H5Object &&o);

            //=====================convenience  methods========================
            /*! 
            \brief get reference to the shape buffer
           
            This method returns a const reference to the internal buffer holding
            the actual number of elements along each dimension. For a dataspace
            representing a scalar value this will be an empty buffer. 
            The aim of this method is to provide a quick way to access the shape
            of a dataspace.
            \return const reference to shape buffer
            \sa CTYPE shape() const
            \sa void shape(CTYPE &c) const
            */
            const size_vector_t &shape() const { return _dims; }

            //-----------------------------------------------------------------
            /*! 
            \brief get actual shape

            Returns the actual number of elements along each dimension in a
            user definied container as shown in the example below where a list
            container is used
            \code
            H5Dataspace space({1,2,3});

            auto adims = space.shape<std::list<hsize_t> >();
            \endcode
            Though this method provides a high degree of flexibility it has a
            major disadvantage: as it needs to allocate new memory for the
            container every time it is called this method may not be suitable
            for situations where high performance is required.
            \tparam CTYPE container type
            \return instance of CTYPE with elements along each dimension
            \sa shape() 
            \sa void shape(CTYPE &c) 
            */
            template<typename CTYPE> CTYPE shape() const
            {
                CTYPE c(_dims.size());
                std::copy(_dims.begin(),_dims.end(),c.begin());
                return c;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief get actual shape

            Copy the actual shape to an existing container object. The container
            can be any STL compliant type. 
            \code 
            H5Dataspace s{1,2,3};
            std::vector<size_t> shape(s.rank());
            s.shape(shape);
            \endcode
            The method does not reallocate the container and thus assumes that
            it has the appropriate size. If this is not the case an exception
            will be thrown. Since no memory must be allocated this method should
            be sufficiently quite fast.
            \throw shape_mismatch_error if size of container does not match the
            rank of the dataspace
            \tparam CTYPE type of the container
            \param c reference to the container
            */
            template<typename CTYPE> void shape(CTYPE &c) const
            {
                if(c.size() != rank())
                {
                    std::stringstream ss;
                    ss<<"Container size ("<<c.size()<<") does not match the ";
                    ss<<"dataspace rank ("<<rank()<<")!";
                    throw shape_mismatch_error(EXCEPTION_RECORD,ss.str());
                }

                std::copy(this->shape().begin(),this->shape().end(),c.begin());
            }


            //-----------------------------------------------------------------
            /*! \brief obtain the maximum shape

            Returns the maximum shape of the dataspace. 
            \return shape object 
             
            */
            const size_vector_t &maxshape() const { return _maxdims; }

            //----------------------------------------------------------------
            /*!
            \brief get maximum shape

            Get the maximum shape of the dataspace (the maximum number of
            elements to which a dataset initialized with this shape can grow). 
            \code
            H5Dataspace space({1,2,3,4},{100,100,100,100});
            auto shape = space<std::vector<size_t> >();
            \endcode
            Like for CTYPE shape() this method allocates the requested container
            and thus is maybe not the best choice if performance is an issue. 
            \tparam CTYPE container type
            \return instance of CTYPE with the maximum shape of the dataspace
            */
            template<typename CTYPE> CTYPE maxshape() const
            {
                CTYPE c(_maxdims.size());
                std::copy(_maxdims.begin(),_maxdims.end(),c.begin());
                return c;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief get maximum shape

            Store the maximum shape of the dataspace to an already existing
            container. 
            \code
            H5Dataspace space({1,2,3,4},{100,100,100,100});
            std::vector<size_t> shape(space.rank());
            space.shape(shape);
            \endcode
            The method assumes that the container is of appropriate size. If
            this is not the case an exception will be thrown.
            \throw shape_mismatch_error if container size does not match the rank
            of the dataspace
            \tparam CTYPE container type
            \param c reference to container instance
            */
            template<typename CTYPE> void maxshape(CTYPE &c) const
            {
                if(c.size() != rank())
                {
                    std::stringstream ss;
                    ss<<"Container size ("<<c.size()<<") does not match the ";
                    ss<<"dataspace rank ("<<rank()<<")!";
                    throw shape_mismatch_error(EXCEPTION_RECORD,ss.str());
                }

                std::copy(this->shape().begin(),this->shape().end(),c.begin());
            }


            //-----------------------------------------------------------------
            /*! \brief rank of dataset

            Returns the rank (the number of dimensions) of the dataset. 
            For a scalar dataspace this method returns 0.
            \return number of dimension */
            size_t rank() const;

            //-----------------------------------------------------------------
            /*! \brief number of elements

            Returns the number of elements along dimension i. If the 
            dataspace is scalar 0 is returned independent of the value 
            of i.
            \throws index_error if i exceeds the dataspace rank
            \param i dimension index
            \return number of elements along i */
            size_t dim(size_t i) const;

            //-----------------------------------------------------------------
            /*! \brief max.elements along dimension

            Returns the maximum number of dimension along dimension i. 
            If the dataspace is scalar 0 is returned independent of 
            the value of i.
            \throws index_error if i exceeds dataspace rank
            \param i index of dimension
            \return maximum number of elements along dimension i */
            size_t max_dim(size_t i) const;

            //-----------------------------------------------------------------
            /*! \brief total number of elements

            Returns the total number of elemenets that can be stored 
            in the dataspace.  For a scalar dataspace this method 
            returns 1.
            \return total number of elements */
            size_t size() const;

            //-----------------------------------------------------------------
            /*! \brief number of elements
            
            Returns the number of elements along dimension i.
            \throws index_error if i exceeds dataspace rank
            \param i dimension index
            \return number of elements along i */
            size_t operator[](size_t i) const;

            //-----------------------------------------------------------------
            /*! \brief true if scalar dataspace

            Returns true if the dataspace is scalar. 
            \return true if dataspace is scalar */
            bool is_scalar() const;

            //-----------------------------------------------------------------
            /*! \brief resize dataspace

            Resizes the dataspace to a new shape determined by s. If 
            the dataspace was originally scalar the new dataspace 
            becomes simple. In this case the maximum number of 
            elements along each dimension will be determined by s too. 
            Using this datspace for the construction of a dataset
            will lead to an dataset of constant size.
            \param s new dataspace shape */
            template<typename CTYPE> void resize(const CTYPE &s)
            {
                _dims = size_vector_t(s.size());
                _maxdims = size_vector_t(s.size());
                
                std::copy(s.begin(),s.end(),_dims.begin());
                std::copy(s.begin(),s.end(),_maxdims.begin());

                __setup_dataspace();
            }

            //-----------------------------------------------------------------
            /*! \brief resize dataspace

            This method does basically what resize(const Shape &s) is
            doing. However, an initializer list is used instead 
            of a shape object. This method exists for convenience 
            as it makes typing code easier.
            \param list initializer list */
            void resize(const std::initializer_list<hsize_t> &list);

            //-----------------------------------------------------------------
            /*! \brief resize dataspace

            With this version of the resize method the actual and maximum number
            of elements along each dimension can be configured individually.
            Using such a dataspace for dataset construction will lead to an
            resizeable dataset.

            \throws memory_allocation_error if buffer allocation fails
            \throws shape_mismatch_error if the ranks of the two shapes do not match
            \throws pni::io::nx::nxbackend_error if dataspace setup fails

            \param s initial shape of the dataspace
            \param ms maximum shape of the dataspace 
            */
            template<typename CTYPE1,typename CTYPE2>
            void resize(const CTYPE1 &s,const CTYPE2 &ms)
            {
                if(s.size() != ms.size())
                {
                    std::stringstream ss;
                    ss<<"Rank of actual shape ("<<s.size()<<") and of ";
                    ss<<"maximum shape ("<<ms.size()<<") do not match!";
                    throw shape_mismatch_error(EXCEPTION_RECORD,ss.str());
                }

                _dims = size_vector_t(s.size());
                _maxdims = size_vector_t(ms.size());

                std::copy(s.begin(),s.end(),_dims.begin());
                std::copy(ms.begin(),ms.end(),_maxdims.begin());

                __setup_dataspace();
            }

            //-----------------------------------------------------------------
            /*! \brief resize dataspace

            Like resize(const Shape&, const Shape &) but using initializer lists
            instead of shape objects. This is again a convenience method to
            reduce typing work.  The rank of the resized dataspace is determined
            by the size of the tow lists. Both lists must be of equal size.

            \throws memory_allocation_error if buffer allocation fails
            \throws pni::io::nx::nxbackend_error if dataspace setup fails
            \throws shape_mismatch_error if list sizes are not equal

            \param dlist list with actual number of elements
            \param mlist list with maximum number of elements */
            void resize(const std::initializer_list<hsize_t> &dlist,
                        const std::initializer_list<hsize_t> &mlist);

            //-----------------------------------------------------------------
            /*! \brief grow dataspace

            Grow the dataspace along dimension dim by ext elements.  This is a
            very simple method to enlarge a dataspace along a particular
            dimension. If dim is larger than the rank of the dataspace an
            exception will be thrown.
            \throws index_error if dim exceeds rank of dataspace
            \param dim dimension along which to grow
            \param ext extend by which to grow */
            void grow(size_t dim=0,size_t ext=1) ;

            //-----------------------------------------------------------------
            //! close the dataspace
            virtual void close();

            //-----------------------------------------------------------------
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                    const H5Dataspace &s);

        };


//end of namespace
}
}
}
}
