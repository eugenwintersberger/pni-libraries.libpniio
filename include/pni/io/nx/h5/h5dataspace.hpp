//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Jul 15, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <vector>
#include <sstream>
#include <algorithm>
#include <pni/core/error.hpp>

#include "object_imp.hpp"
#include "type_imp.hpp"

namespace pni{
namespace io{
namespace nx {
namespace h5 {

    using namespace pni::core;
    //avoid namespace collisions with std
    using pni::core::exception;
    using pni::core::string;

    //!
    //! \ingroup nxh5_classes
    //! \brief dataspace object
    //!
    //! This class encapsulates an HDF5 dataspace. A dataspace describes the
    //! organization of dataelements within a dataset in the file or of data 
    //! stored in memory. A dataspace in HDF5 can either be
    //! \li scalar 
    //! \li or \c simple - which is in fact a simple multidimensional array.
    //! 
    //! A dataspace object provides information items which are necessary 
    //! to describe the data organization
    //! \li the \b rank - which is the number of dimensions
    //! \li the \b shape - which is the number of elements along each dimension
    //! \li and the \b maximum \b shape - which is the maximum number of elements
    //! along each dimension.
    //!
    //! The object encapsulates two buffers (instances of std::vector) which
    //! provide this information.  
    //! (not a dataspace) can grow. This number can be a finite one or can 
    //! be set to H5Dataspace::UNLIMITED which allows the dataset to grow 
    //! infinitely along this dimension. 
    //! 
    //! At any time during the lifetime of a H5Dataspace object the 
    //! dataspace it describes can be resized to any required shape (see the 
    //! resize() and grow() methods).  This makes it easy to adopt the 
    //! object to your needs.  There are many possibilities how to construct 
    //! a dataspace.  
    //!
    //! A dataspace representing a scalar value has a rank of  0 and a 
    //! size of 1. 
    //!
    class h5dataspace
    {
        public:
            //! value type for buffers
            typedef type_imp::index_type value_type;
            //! buffer type for array parameters
            typedef type_imp::index_vector_type buffer_type;
            //! buffer iterator
            typedef buffer_type::const_iterator iterator;
        private:
            //! The HDF5 object representing the dataspace
            object_imp _object;
            //! maximum number of elements dimensions
            buffer_type _maxdims; 
            //! number of elements 
            buffer_type _dims;    

            //-----------------------------------------------------------------
            //!
            //! \brief setup dataspace
            //!
            //! This method will update a dataspace according to the values 
            //! stored in the two internal buffers.
            //!
            //! \throws object_error if dataspace extent could not have been
            //!                      set
            //!
            void __update_dataspace();

            //-----------------------------------------------------------------
            //! 
            //! \brief set buffers from object
            //!
            //! Update buffers according to the underlying dataspace.
            //!
            //! \brief object_error if dataspace extent could not have been 
            //!                     retrieved
            //!
            void __update_buffers();
        public:
            //==============constructors and destructor========================
            //! 
            //! \brief default constructor
            //!
            //! By default a scalar dataspace is constructed. This 
            //! constructor can always be used in order to store a scalar 
            //! value. Consequently even a default constructed H5Dataspace is 
            //! always a valid HDF5 object.
            //!
            explicit h5dataspace() noexcept;

            //-----------------------------------------------------------------
            //!
            //! \brief copy constructor
            //! 
            //! \throws object_error in case of failure
            //!
            h5dataspace(const h5dataspace &o);

            //-----------------------------------------------------------------
            //!
            //! \brief move constructor
            //! 
            h5dataspace(h5dataspace &&o) noexcept;

            //-----------------------------------------------------------------
            //!
            //! \brief construct from ID
            //!
            //! \brief object_error in case of failure
            //! \brief type_error if the passed object is not a dataspace
            //! 
            //! \param id HDF5 id of the original object
            //!
            explicit h5dataspace(object_imp &&o);
            
            //-----------------------------------------------------------------
            //! 
            //! \brief construct form shape
            //!
            //! Constructor takes a container which holds the shape of the 
            //! dataspace to create. The actual as well as the maximum number 
            //! of dimensions will be set to these values.
            /*!
            \code
            type_imp::index_vector_type shape{4,5,19};
            h5dataspace space(shape);
            \endcode
            */
            //! \throws object_error in case of failure
            //! \param s vector with shape data
            //!
            explicit h5dataspace(const type_imp::index_vector_type &s);

            //----------------------------------------------------------------- 
            //! 
            //! \brief constructor with actual and maximum shape
            //!
            //! Constructor takes two containers of arbitrary type which 
            //! hold the actual and the maximum shape of the dataspace.
            //!
            /*! 
            \code
            type_imp::index_vector_type shape{4,5,19};
            type_imp::index_vector_type mshape{100,100,100};
            h5dataspace space(shape,mshape);
            \endcode
            */
            //!
            //! \throws shape_mismatch_error if actual and max dim containers 
            //!                              are of different size
            //! \throws object_error in case of any other failure
            //! \param s initial shape
            //! \param ms maximum shape
            //!
            //! \sa H5Dataspace(const CTYPE &s)
            //!
            explicit h5dataspace(const type_imp::index_vector_type &s,
                                 const type_imp::index_vector_type &ms);

            //-----------------------------------------------------------------
            //!
            //! \brief construction with an initializer list
            //!
            //! Use an initializer list to construct a dataspace. The 
            //! dataspace created by this constructor is always a simple 
            //! constructor and has constant size. 
            /*!
            \code
            h5dataspace space({1,2,3});
            \endcode
            */
            //!
            //! \throws object_error in case of any error
            //! \param list initializer list
            //! \sa H5Dataspace(const Shape &s)
            //!
            explicit h5dataspace(const std::initializer_list<hsize_t> &list);
          
            //-----------------------------------------------------------------
            //! 
            //! \brief fixed size dataspace
            //!
            //! Create a fixed size dataspace from two initializer lists. The
            //! created dataspace is a simple dataspace in HDF5 terminilogy.
            //!
            //! \throws shape_mismatch_error if the size of the two initializer
            //!                              lists do not match
            //! \throws object_error in case of any other error
            //! \param dlist initializer list with actual shape values
            //! \param mlist initializer list with maximum shape values
            //!
            explicit h5dataspace(const std::initializer_list<hsize_t> &dlist,
                                 const std::initializer_list<hsize_t> &mlist);

            //=====================Assignment operators========================
            //!
            //! \brief copy assignment operator
            //! 
            //! \throws object_error in case of errors 
            //! 
            h5dataspace &operator=(const h5dataspace &o);

            //-----------------------------------------------------------------
            //!
            //! \brief move assignment operator
            //! 
            h5dataspace &operator=(h5dataspace &&o) noexcept;

            //=====================convenience  methods========================
            //-----------------------------------------------------------------
            //!
            //! \brief rank of dataset
            //!
            //! Returns the rank (the number of dimensions) of the dataset. 
            //! For a scalar dataspace this method returns 0.
            //! \return number of dimension 
            //!
            size_t rank() const;

            //-----------------------------------------------------------------
            //!
            //! \brief get object reference
            //!
            const object_imp &object() const 
            {
                return _object;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief number of elements
            //!
            //! Returns the number of elements along dimension i. If the 
            //! dataspace is scalar 0 is returned independent of the value 
            //! of i.
            //! \throws index_error if i exceeds the dataspace rank
            //! \param i dimension index
            //! \return number of elements along i */
            //!
            size_t current_dim(size_t i) const;

            //-----------------------------------------------------------------
            //!
            //! \brief max.elements along dimension
            //!
            //! Returns the maximum number of dimension along dimension i. 
            //! If the dataspace is scalar 0 is returned independent of the 
            //! value of i.
            //!
            //! \throws index_error if i exceeds dataspace rank
            //! \param i index of dimension
            //! \return maximum number of elements along dimension i 
            //!
            size_t maximum_dim(size_t i) const;

            //-----------------------------------------------------------------
            //!
            //! \brief total number of elements
            //!
            //! Returns the total number of elemenets that can be stored in the 
            //! dataspace.  For a scalar dataspace this method returns 1.
            //!
            //! \return total number of elements */
            //!
            size_t size() const;

            //-----------------------------------------------------------------
            //!
            //! \brief true if scalar dataspace
            //!
            //! Returns true if the dataspace is scalar. 
            //! \return true if dataspace is scalar 
            //!
            bool is_scalar() const;
   
            //----------------------------------------------------------------
            //! 
            //! \brief iterator to first current dimension
            //!
            //! Return an interator to the first current dimension of the
            //! dataspace.
            //! 
            //! \return iterator 
            //! 
            iterator current_begin() const noexcept 
            {
                return _dims.begin();
            }

            //----------------------------------------------------------------
            //!
            //! \brief iterator to last current dimension
            //!
            //! Return an interator to the last current dimensions.
            //!
            //! \return iterator
            //!
            iterator current_end() const noexcept
            {
                return _dims.end();
            }

            //----------------------------------------------------------------
            //!
            //! \brief iterator to first maximum dimension
            //!
            //! Return an iterator to the first maximum dimension.
            //!
            //! \return iterator
            //!
            iterator maximum_begin() const noexcept
            {
                return _maxdims.begin();
            }

            //----------------------------------------------------------------
            //!
            //! \brief iterator to last maximum dimension
            //!
            //! Return an iterator to the last maximum dimension
            //!
            //! \return iterator
            //!
            iterator maximum_end() const noexcept
            {
                return _maxdims.end();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief resize dataspace
            //!
            //! Resizes the dataspace to a new shape determined by s. If the 
            //! dataspace was originally scalar the new dataspace becomes simple. 
            //! In this case the maximum number of elements along each 
            //! dimension will be determined by s too.  Using this datspace for 
            //! the construction of a dataset will lead to an dataset of 
            //! constant size.
            //!
            //! \throws object_error in case of errors
            //! \param s new dataspace shape 
            //!
            template<typename CTYPE> void resize(const CTYPE &s)
            {
                _dims = buffer_type(s.size());
                _maxdims = buffer_type(s.size());
                
                std::copy(s.begin(),s.end(),_dims.begin());
                std::copy(s.begin(),s.end(),_maxdims.begin());

                __update_dataspace();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief resize dataspace
            //!
            //! This method does basically what resize(const Shape &s) is
            //! doing. However, an initializer list is used instead of a 
            //! shape object. This method exists for convenience as it makes 
            //! typing code easier.
            //!
            //! \throws object_error if dataspace update fails
            //! \param list initializer list 
            //!
            void resize(const std::initializer_list<hsize_t> &list);

            //-----------------------------------------------------------------
            //!
            //! \brief resize dataspace
            //!
            //! With this version of the resize method the actual and maximum 
            //! number of elements along each dimension can be configured 
            //! individually.  Using such a dataspace for dataset 
            //! construction will lead to an resizeable dataset.
            //!
            //! \throws shape_mismatch_error if the ranks of the two shapes 
            //! do not match
            //! \throws object_error if dataspace update fails
            //!
            //! \param s initial shape of the dataspace
            //! \param ms maximum shape of the dataspace 
            //!
            template<
                     typename CTYPE1,
                     typename CTYPE2
                    >
            void resize(const CTYPE1 &s,const CTYPE2 &ms)
            {
                if(s.size() != ms.size())
                {
                    std::stringstream ss;
                    ss<<"Rank of actual shape ("<<s.size()<<") and of ";
                    ss<<"maximum shape ("<<ms.size()<<") do not match!";
                    throw shape_mismatch_error(EXCEPTION_RECORD,ss.str());
                }

                _dims = buffer_type(s.size());
                _maxdims = buffer_type(ms.size());

                std::copy(s.begin(),s.end(),_dims.begin());
                std::copy(ms.begin(),ms.end(),_maxdims.begin());

                __update_dataspace();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief resize dataspace
            //!
            //! Like resize(const Shape&, const Shape &) but using 
            //! initializer lists instead of shape objects. This is again a 
            //! convenience method to reduce typing work.  The rank of the 
            //! resized dataspace is determined by the size of the tow lists. 
            //! Both lists must be of equal size.
            //!
            //! \throws shape_mismatch_error if list sizes are not equal
            //! \throws object_error if dataspace update fails
            //!
            //! \param dlist list with actual number of elements
            //! \param mlist list with maximum number of elements 
            //!
            void resize(const std::initializer_list<hsize_t> &dlist,
                        const std::initializer_list<hsize_t> &mlist);

            //-----------------------------------------------------------------
            //!
            //! \brief grow dataspace
            //!
            //! Grow the dataspace along dimension dim by ext elements.  This 
            //! is a very simple method to enlarge a dataspace along a 
            //! particular dimension. If dim is larger than the rank of the 
            //! dataspace an exception will be thrown.
            //!
            //! \throws index_error if dim exceeds rank of dataspace
            //! \throws object_error if dataspace update fails
            //! \param dim dimension along which to grow
            //! \param ext extend by which to grow 
            //!
            void grow(size_t dim=0,size_t ext=1) ;

        };

        //--------------------------------------------------------------------
        //!
        //! \ingroup nxh5_classes
        //! \brief output operator
        //!
        std::ostream &operator<<(std::ostream &o,const h5dataspace &s);

//end of namespace
}
}
}
}
