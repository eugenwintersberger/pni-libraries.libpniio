//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
// Created on: Jun 9, 2011
//     Authors:
//             Eugen Wintersberger
//             Jan Kotanski
//
//
#pragma once

#include <iostream>
#include <array>

#include <pni/types.hpp>
#include <pni/arrays/scalar_iterator.hpp>
#include <pni/arrays/array_view.hpp>

namespace pni {

    //template<typename ArrayT> class array_view;

    //! 
    //! \ingroup mdim_array_classes
    //! \brief Scalar template for scalar values
    //! 
    //! This template is used in expression tempaltes. Its purpose is to give 
    //! scalar values an array like interface.
    //!
    //! \tparam ElementT scalar type of the data stored.
    //!
    template<typename ElementT> 
    class scalar
    {
        private:
            //! static buffer holding the data value
            std::array<ElementT,1> _data; 
        public:
            //================public data types================================
            //! native data type of the scalar
            typedef ElementT value_type;
            //! type of the scalar itself
            typedef scalar<ElementT> array_type;
            //! storage type
            typedef std::array<ElementT,1> storage_type;
            //! iterator
            typedef scalar_iterator<array_type> iterator;
            //! const iterator
            typedef scalar_iterator<const array_type> const_iterator;
            //! view type
            typedef array_view<array_type> view_type;
            
            //===============public members====================================
            //! type ID of the data type held by the scalar
            static const type_id_t type_id = type_id_map<ElementT>::type_id;

            //====================constructors and destructor==================
            //! default constructor
            scalar():_data() {}

            //-----------------------------------------------------------------
            //! copy constructor
            scalar(const array_type &s):_data(s._data) {}
            
            //-----------------------------------------------------------------
            //! constructor from a scalar value
            scalar(const value_type &r):_data(storage_type{{r}}) {}

            //-----------------------------------------------------------------

            //-----------------------------------------------------------------
            //! destructor
            ~scalar() {}

            //=================assignment operators============================
            //! 
            //! \brief assignment from ElementT value
            //!
            //! Assigns a value of type ElementT to the scalar.
            //! \param v value to assign
            //! \return reference to array_type
            //!
            array_type &operator=(const value_type &v)
            {
                this->_data[0] = v;
                return *this;
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief assignment from Scalar<ElementT>
            //!
            //! This is the most trivial case. An object of type Scalar<ElementT> is 
            //! assigned to an other object of type Scalar<ElementT>.
            //! \param v value of scalar<ElementT> to assign
            //! \return reference to array_type
            //!
            array_type &operator=(const array_type &v)
            {
                if(this == &v) return *this;
                this->_data = v._data;
                return *this;
            }

            //=======================conversion operator========================
            //!
            //! \brief conversion operator
            //!
            //! Allows conversion from an instance of scalar<ElementT> to a variable 
            //! of type ElementT.
            //! 
            //! \return value of type ElementT
            //!
            operator ElementT() const { return this->_data[0]; }

            //===================linear access operators========================
            //!
            //! \brief get data
            //!
            //! Return the single data value independent of what value of i 
            //! is given.
            //! 
            //! \param i linear index of the value
            //! \return value of the scalar
            //!
            ElementT operator[](size_t i) const {
	      (void)i;  // UNUSED
	      return this->_data[0];
	    }

            //-----------------------------------------------------------------
            //!
            //! \brief get reference to data
            //!  
            //! Return a reference to the data stored in the scalar. No 
            //! matter what value of i is passed to this operator - it will 
            //! always return the same reference.
            //! 
            //! \param i index
            //! \return reference to the scalar data
            //!
            ElementT &operator[](size_t i) {
	      (void)i;  // UNUSED
	      return this->_data[0];
	    }

            //-----------------------------------------------------------------
            //! 
            //! \brief get data value
            //!
            //! Return the value of the data stored in the instance no matter 
            //! of the value of the index.
            //! 
            //! \param i index
            //! \return data value
            //!
            ElementT at(size_t i) const {
	      (void)i;  // UNUSED
	      return this->_data[0];
	    }

            //-----------------------------------------------------------------
            //! 
            //! \brief get data reference
            //!
            //! Return a reference to the data stored in the scalar no matter 
            //! what index is passed to the method.
            //! 
            //! \param i index
            //! \return reference to data
            //!
            ElementT &at(size_t i) {
	      (void)i;  // UNUSED
	      return this->_data[0];
	    }

            //-----------------------------------------------------------------
            //! 
            //! \brief set data value
            //!
            //! Method to set a data value. The index does not matter. 
            //! \param i index
            //! \param v value
            //!
            void insert(size_t i,const ElementT &v) { this->_data[0] = v; }
            
            //-----------------------------------------------------------------
            //! 
            //! \brief get reference to the storage object
            //!
            //! Return a const reference to the static buffer that holds the 
            //! scalar data. 
            //! 
            //! \return reference to buffer object
            //!
            const storage_type &storage() const { return this->_data; }

            //==================methods for multidim data access===============
            //! 
            //! \brief get reference to the data
            //!
            //! Returns the reference to the data value no matter how many or 
            //! what indices are passed.
            //! 
            //! \tparam IndicesT index types
            //! \param indices multidimensional index
            //! \return reference to data
            //!
            template<typename ...IndicesT> 
            ElementT &operator()(IndicesT ... indices)
            {
                return this->_data[0];
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get value of data
            //!
            //! Return the value of the scalar. The number of indices or 
            //! their type do not matter.
            //! 
            //! \tparam IndicesT index types
            //! \param indices multidimensional index
            //! \return data value
            //!
            template<typename ...IndicesT> 
            ElementT operator()(IndicesT ... indices) const
            {
                return this->_data[0];
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get reference to data
            //!
            //! Return a reference to the data. The multidimensional index is 
            //! passed by a container. The number of indices or their value 
            //! are ignored. 
            //!
            //! \tparam ContainerT container template
            //! \tparam ContainerTemplateArgumentsT template arguments for the container template
            //! \return reference to the data
            //!
            template<
                     template<typename ...> class ContainerT,
                     typename ...ContainerTemplateArgumentsT
                    >
            ElementT &operator()(const ContainerT<ContainerTemplateArgumentsT...> &)
            {
                return this->_data[0];
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get data value
            //!  
            //! Return the data value. The multidimensional index is passed 
            //! by a container. The number of indices or their value are 
            //! ignored.
            //! \tparam ContainerT container template
            //! \tparam ContainerTemplateArgumentsT template arguments of the container template
            //!
            //! \return data value
            //!
            template<template<typename ...> class ContainerT,typename ...ContainerTemplateArgumentsT>
            ElementT operator()(const ContainerT<ContainerTemplateArgumentsT...> &) const
            {
                return this->_data[0];
            }

            //===================inquery methods===============================
            //!
            //! \brief get size
            //!
            //! For a scalar object this method always returns 1. This is due 
            //! to the fact that one needs to allocate only one block of 
            //! memory of sizeof(ElementT) bytes to hold the scalar data.
            //! 
            //! \return 1
            //!
            size_t size() const { return 1; }

            //-----------------------------------------------------------------
            //!
            //! \brief get rank
            //!
            //! Return the number of dimensions of the scalar. 
            //! This is always 0.
            //! \return 0
            //!
            size_t rank() const { return 0; }

            //------------------------------------------------------------------
            //! 
            //! \brief get shape
            //!
            //! Returns the shape of the scalar - this is a container with a 
            //! single value 1.
            //! 
            //! \return container with 1
            //!
            template<typename ContainerT> 
            ContainerT shape() const { return ContainerT(); }

            //------------------------------------------------------------------
            //! get iterator to first element
            iterator begin() { return iterator(this,0); }

            //------------------------------------------------------------------
            //! get iterator to last+1 element
            iterator end() { return iterator(this,0); }

            //------------------------------------------------------------------
            //! get const iterator to first element
            const_iterator begin() const { const_iterator(this,0); }

            //------------------------------------------------------------------
            //! get const iterator to last+1 element
            const_iterator end() const { return const_iterator(this,0); }
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_classes
    //! \brief == operator for scalar 
    //!
    //! Returns true if the two value of a and b are equal. 
    //!
    //! \tparam ElementT data type for the scalar instance
    //! \param a lhs value of the operator
    //! \param b rhs value of the operator
    //! \return true if both are equal, false otherwise
    //! 
    template<typename ElementT>
    bool operator==(const scalar<ElementT> &a,const scalar<ElementT> &b)
    {
        return ElementT(a)==ElementT(b);
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_classes
    //! \brief != operator for scalar 
    //!
    //! Returns true if the two value of a and b are not equal. 
    //!
    //! \tparam ElementT data type for the scalar instance
    //! \param a lhs value of the operator
    //! \param b rhs value of the operator
    //! \return false if both are equal, true otherwise
    //! 
    template<typename ElementT>
    bool operator!=(const scalar<ElementT> &a,const scalar<ElementT> &b)
    {
        return !(a==b);
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_classes 
    //! \brief stream output operator
    //! 
    //! Write content to output stream.
    //! \param os output stream
    //! \param s scalar value
    //! \return reference to output stream
    //!
    template<typename ElementT>
    std::ostream &operator<<(std::ostream &os,const scalar<ElementT> &s)
    {
        ElementT value = s[0]; 
        os<<value;
        return os;
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_classes
    //! \brief input strema data
    //!
    //! Read content from input stream
    //! \param is input stream
    //! \param s scalar 
    //! \return reference to input stream
    //!
    template<typename ElementT>
    std::istream &operator>>(std::istream &is,scalar<ElementT> &s)
    {
        ElementT value;
        is>>value;
        s = value;
        return is;
    }

//end of namespace
}
