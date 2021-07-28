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
    
    template<typename ATYPE> class array_view;

    //! 
    //! \ingroup mdim_array_internal_classes
    //! \brief subtraction expression template
    //!
    //! Expression template for subtraction of array templates.
    //! \tparam OP1T left operand type
    //! \tparam OP2T right operand type
    //!
    template<
             typename OP1T,
             typename OP2T
            > 
    class sub_op
    {
        private:
            //! reference to the left operand
            typename op_trait<OP1T>::ref_type _op1;
            //! reference to the right operand
            typename op_trait<OP2T>::ref_type _op2;
        public:
            //--------------------public types---------------------------------
            //! type of the element 
            typedef typename OP1T::value_type value_type;
            //! type of the template
            typedef sub_op<OP1T,OP2T> array_type;
            //! storage type - not used for this
            typedef void storage_type;
            //! iterator type
            typedef container_iterator<array_type> iterator;
            //! const iterator type
            typedef container_iterator<const array_type> const_iterator;

            //! reverse iterator
            typedef container_iterator<array_type> reverse_iterator;
            //! const reverse iterator
            typedef container_iterator<const array_type> const_reverse_iterator;
            //! view type
            typedef array_view<array_type> view_type;

            //! index map type
            typedef typename array_trait<OP1T,OP2T>::map_type map_type;
            //! inplace arithmetic type
            typedef typename array_trait<OP1T,OP2T>::inplace_arithmetic
                inplace_arithmetic;

            //===================constructors==================================
            //! 
            //! \brief constructor
            //! 
            //! \param o1 operator left handside
            //! \param o2 operator right handside
            //!
            sub_op(const OP1T &o1,const OP2T &o2):
                _op1(o1),
                _op2(o2)
            {}

            //====================public methods===============================
            //! 
            //! \brief get value i
            //!
            value_type operator[](size_t i) const
            {
                return this->_op1[i]-this->_op2[i];
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get result at i
            //!
            //! Return the result of the operation computed at index i.
            //! 
            //! \brief index_error if i exceeds the size
            //! \param i index for which to compute the operation
            //! \return result of operation
            //!
            value_type at(size_t i) const
            {
                if(i>=size())
                    throw index_error(EXCEPTION_RECORD,"Index exceeds size!");

                return (*this)[i];
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief get size of the expression
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
            //! \brief get const iterator to the last element
            //! 
            const_iterator end() const
            {
                return const_iterator(this,this->size());
            }

    };


//end of namespace
}
