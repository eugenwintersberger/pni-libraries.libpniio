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
// Created on: Jul 25,2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/algorithms/math/op_traits.hpp>
#include <pni/utilities/container_iterator.hpp>

namespace pni{

    template<typename ArrayT> class array_view;


    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief addition expression template
    //!    
    //! \tparam Operand1T type of left operand
    //! \tparam Operand2T type of right operand
    //!
    template<
             typename Operand1T,
             typename Operand2T
            >
    class add_op
    {
        private:
            //! reference to the left operand
            typename op_trait<Operand1T>::ref_type _op1;
            //! reference to the right operand
            typename op_trait<Operand2T>::ref_type _op2;
        public:
            //--------------------public types---------------------------------
            //! result type of the operation
            typedef typename Operand1T::value_type value_type;
            //! type of the expression template
            typedef add_op<Operand1T,Operand2T> array_type;
            //! storage type
            typedef void storage_type;
            //! non-const iterator type - just for interface
            typedef container_iterator<array_type> iterator;
            //! const iterator type
            typedef container_iterator<const array_type> const_iterator;

            //! reverse iterator type
            typedef container_iterator<array_type> reverse_iterator;
            //! const reverse iterator type
            typedef container_iterator<const array_type> const_reverse_iterator;
            //! view type
            typedef array_view<array_type> view_type;

            //! index map type
            typedef typename array_trait<Operand1T,Operand2T>::map_type map_type;
            //! inplace arithmetic type
            typedef typename array_trait<Operand1T,Operand2T>::inplace_arithmetic
                inplace_arithmetic;

            //===================constructors==================================
            //!
            //! \brief constructor
            //! 
            //! \param o1 left operand
            //! \param o2 right operand
            //!
            add_op(const Operand1T &o1,const Operand2T &o2):
                _op1(o1),
                _op2(o2)
            { }

            //====================public methods===============================
            //!
            //! \brief get result at i
            //!
            //! Return the result of a[i]+b[i]. 
            //! \param i index at which to perform the operation
            //! \return result of the operation
            //!
            value_type operator[](size_t i) const
            {
                return this->_op1[i]+this->_op2[i];
      
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get result at i
            //! 
            //! Like with STL containers this method throws index_error if the 
            //! user provided index exceeds the size of the array. 
            //! 
            //! \throws index_errr if i>=size()
            //! \param i index for which to compute the result
            //! \return result of operation
            //! 
            value_type at(size_t i) const
            {
                if(i>=size())
                    throw index_error(PNINEXUS_EXCEPTION_RECORD,"array index exceeded!");

                return (*this)[i];
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief get size
            //!
            //! Return the maximum of a.size() and b.size().
            //! \return number of elements of result
            //!
            size_t size() const 
            { 
                return _op1.size() > _op2.size() ? _op1.size() : _op2.size();
            }

            //=====================iterators===================================
            //! 
            //! \brief get const iterator to the first element
            //! 
            const_iterator begin() const
            {
                return const_iterator(this,0);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get const iterator to last+1 element
            //!
            const_iterator end() const
            {
                return const_iterator(this,this->size());
            }

    };


//end of namespace
}
