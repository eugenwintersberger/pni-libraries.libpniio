//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// ===========================================================================
//
// Created on: May 14, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include <utility>

#include <pni/error/exceptions.hpp>
#include <pni/windows.hpp>

namespace pni{

    //! 
    //! \ingroup mdim_array_classes
    //! \brief index slice
    //!
    //! This types represents an index slice for an array. A slice can be 
    //! used to identify an index range along a single dimensions. 
    //! slice objects are of particular importance for creating array_view 
    //! from mdarray instancers.
    //!
    //! A slice includes all indices between the the first and last index 
    //! of the slice where the last index is not included. A stride can 
    //! be passed during construction which determines the number of 
    //! steps between each subsequent element. If the stride is not 1 
    //! the last index will be adopted so that the 
    //!
    class PNINEXUS_EXPORT slice
    {
        private:
            size_t _first;  //!< first index in the slice
            size_t _last;   //!< last index in the slice
            size_t _stride; //!< distance between indices

            //!
            //! \brief check first and last index
            //!
            //! This private method throws an exception if the first 
            //! index of the range exceeds the last one. 
            //!
            //! \throws range_error if first > last
            //! \param o signature of the origin where the error occured
            //!
            void _check_start_stop(const exception_record &o) const;

            //-----------------------------------------------------------------
            //!
            //! \brief check stride
            //!
            //! Checks if the stride does not exceed the span of the slice. 
            //! If it does an exception will be thrown. 
            //! 
            //! \throws range_error if stride exceeds span
            //! \param o signature of the origin where the error occured 
            //!
            void _check_stride(const exception_record &o) const;
        public:
            //==============constructors and destructor========================
            //! default constructor
            slice() {}

            //-----------------------------------------------------------------
            //! 
            //! \brief standard constructor
            //!
            //! This is the default constructor for a Slice object. 
            //! 
            //! \throws range_error if the first index exceeds the last
            //! \param first first index
            //! \param last index 
            //! \param stride steps between subsequent elements
            //!
            explicit slice(size_t first,size_t last,size_t stride=1);

            //-----------------------------------------------------------------
            //! 
            //! \brief construction from a initializer list
            //!
            //! This can be used for implicit conversion which is sometimes 
            //! quite useful for the creation fo array views. 
            /*!
            \code 
            mdarray<...>  a({10,100});
            
            //default construction of a view
            auto v1 = a(slice(1,4),slice(50,100));
            
            //one can also use initializer lists
            auto v2 = a({1,4},{50,100});
            \endcode
            !*/
            //! If the initializer list has only two elements they are treated 
            //! as first and last element of the slice and the stride is 
            //! set to 1.  In the case of a three element initializer list 
            //! the last element is considered as the stride of the slice.
            //!
            //! \throws range_error if the first element is larger than the last
            //! \param l initializer list
            //!
            explicit slice(const std::initializer_list<size_t> &l);

            //-----------------------------------------------------------------
            //! 
            //! \brief construction from a single index
            //!
            //! Constructor uses a single index. This constructor is 
            //! equivalent to use slice(index,index+1,1). 
            //! 
            //! \param index single index from which to create the slice
            //!
            explicit slice(size_t index);

            //-----------------------------------------------------------------
            //! destructor
            ~slice(){}

            //===============assignment operators==============================
            //! copy assignment operator
            slice &operator=(const slice &s);
	    slice(const slice&) = default;

            //=================public member methods===========================
            //! 
            //! \brief return the first element
            //!
            //! \return first element of slice
            //!
            size_t first() const { return _first; }

            //-----------------------------------------------------------------
            //! 
            //! \brief return last element 
            //!
            //! \return last element of slice
            //!
            size_t last() const { return _last; }

            //-----------------------------------------------------------------
            //! 
            //! \brief return stride
            //!
            //! \return stride of the slice
            //!
            size_t stride() const { return _stride; }
    }; 

    //! output operator
    PNINEXUS_EXPORT std::ostream &operator<<(std::ostream &o,const slice &s);

    PNINEXUS_EXPORT bool operator==(const slice &lhs,const slice &rhs);

    PNINEXUS_EXPORT bool operator!=(const slice &lhs,const slice &rhs);

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup mdim_array_classes   
    //! \brief compute slice size
    //!
    //!
    //! Computes the number of elements spanned by a slice. 
    /*! 
    \f[
       size=\frac{last-first+stride-1}{stride}
    \f]
    */ 
    //! \param s slice object 
    //! \return number of spanned elements
    //!
    PNINEXUS_EXPORT size_t size(const slice &s);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_classes
    //! \brief compute total elements spanned
    //!
    //! Computes the total number of elements spanned by the slice. 
    /*!
    \f[
         span = last-first
    \f] 
    */
    //! \param s slice for which to compute the span
    //! \return total number of elements
    //!
    PNINEXUS_EXPORT size_t span(const slice &s);

//end of namespace
}
