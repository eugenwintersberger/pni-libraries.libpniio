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
           
            //---------------internal variables for selection state------------
            mutable type_imp::index_vector_type _offset;
            mutable type_imp::index_vector_type _stride;
            mutable type_imp::index_vector_type _count;


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
            //! \brief constructor
            //!
            //! \brief object_error in case of failure
            //! \brief type_error if the passed object is not a dataspace
            //! 
            //! \param id HDF5 id of the original object
            //!
            explicit h5dataspace(object_imp &&o);
            
            //-----------------------------------------------------------------
            //! 
            //! \brief constructor
            //!
            //! This constructor takes a const reference to a container with 
            //! the current shape of the dataspace. The maximum shape will be 
            //! equal to the current shape.
            //!
            //! \throws object_error in case of failure
            //! \param shape vector with shape data
            //!
            explicit h5dataspace(const type_imp::index_vector_type &shape);

            //----------------------------------------------------------------
            //! 
            //! \brief constructor
            //! 
            //! The constructors takes an rvalue reference to the current 
            //! shape of the dataspace. The maximum shape will have the same 
            //! value as the current shape.
            //! 
            //! \throws object_error in case of any failure
            //! \param shape rvalue reference to the current shape
            //!
            explicit h5dataspace(type_imp::index_vector_type  &&shape);

            //----------------------------------------------------------------- 
            //! 
            //! \brief constructor
            //!
            //! Constructor takes two const lvalue references to containers  
            //! holding the current and maximum shape of the dataspace.
            //!
            //! \throws shape_mismatch_error if actual and max dim containers 
            //!                              are of different size
            //! \throws object_error in case of any other failure
            //! \param shape current shape
            //! \param max_shape maximum shape
            //!
            explicit h5dataspace(const type_imp::index_vector_type &shape,
                                 const type_imp::index_vector_type &max_shape);

            //----------------------------------------------------------------- 
            //! 
            //! \brief constructor
            //!
            //! Constructor takes two rvalue references to containers  
            //! holding the current and maximum shape of the dataspace.
            //! This will improve performance in dataspace construction as no 
            //! new memory for the maximum and current shape must be 
            //! allocated.
            //!
            //! \throws shape_mismatch_error if actual and max dim containers 
            //!                              are of different size
            //! \throws object_error in case of any other failure
            //! \param shape current shape
            //! \param max_shape maximum shape
            //!
            explicit h5dataspace(type_imp::index_vector_type &&shape,
                                 type_imp::index_vector_type &&max_shape);

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
            //! 
            //! \throws invalid_object_error if dataspace is not valid
            //! \return number of dimension 
            //!
            size_t rank() const;

            //-----------------------------------------------------------------
            //!
            //! \brief get object reference
            //!
            const object_imp &object() const noexcept;

            //-----------------------------------------------------------------
            //!
            //! \brief total number of elements
            //!
            //! Returns the total number of elemenets that can be stored in the 
            //! dataspace.  For a scalar dataspace this method returns 1.
            //!
            //! \throws invalid_object_error if dataspace not valid
            //! \throws object_error if size could not be determined
            //!
            //! \return total number of elements 
            //!
            size_t size() const;

            //-----------------------------------------------------------------
            //!
            //! \brief true if scalar dataspace
            //!
            //! Returns true if the dataspace is scalar. 
            //! \throws invalid_object_error if dataspace is not valid
            //! \return true if dataspace is scalar 
            //!
            bool is_scalar() const;

            //----------------------------------------------------------------
            //!
            //! \brief true if selection is set on this dataspace
            //!
            //! Return true if a selection is applied to this dataspace.
            //!
            //! \throws object_error if selection space cannot be determined
            //!
            //! \return true if dataspace has selection
            //!
            bool has_selection() const;

            //----------------------------------------------------------------
            //! 
            //! \brief return reference to the current dimensions buffer
            //!
            const type_imp::index_vector_type &current_dims() const noexcept;

            //----------------------------------------------------------------
            //!
            //! \brief return reference to the maximum dimensions buffer
            //!
            const type_imp::index_vector_type &maximum_dims() const noexcept;
   
            //----------------------------------------------------------------
            //! 
            //! \brief iterator to first current dimension
            //!
            //! Return an interator to the first current dimension of the
            //! dataspace.
            //! 
            //! \return iterator 
            //! 
            iterator current_begin() const noexcept;

            //----------------------------------------------------------------
            //!
            //! \brief iterator to last current dimension
            //!
            //! Return an interator to the last current dimensions.
            //!
            //! \return iterator
            //!
            iterator current_end() const noexcept;

            //----------------------------------------------------------------
            //!
            //! \brief iterator to first maximum dimension
            //!
            //! Return an iterator to the first maximum dimension.
            //!
            //! \return iterator
            //!
            iterator maximum_begin() const noexcept;

            //----------------------------------------------------------------
            //!
            //! \brief iterator to last maximum dimension
            //!
            //! Return an iterator to the last maximum dimension
            //!
            //! \return iterator
            //!
            iterator maximum_end() const noexcept;

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
            //!
            //! \param dim dimension along which to grow
            //! \param ext extend by which to grow 
            //!
            void grow(size_t dim=0,size_t ext=1) ;

            //----------------------------------------------------------------
            //!
            //! \brief apply selection
            //!
            //! Apply a selection on this dataspace
            //!
            void apply_selection(const type_imp::selection_vector_type
                    &selection) const;

            void reset_selection() const;

            size_t selection_size() const;

            type_imp::index_vector_type selection_shape() const;

        };

        //--------------------------------------------------------------------
        //!
        //! \ingroup nxh5_classes
        //! \brief output operator
        //! 
        //! \throws invalid_object_error if dataspace is not valid
        //!
        std::ostream &operator<<(std::ostream &o,const h5dataspace &s);

//end of namespace
}
}
}
}
