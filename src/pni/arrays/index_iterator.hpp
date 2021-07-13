//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
// Created on: Jan 8, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <algorithm>
#include <vector>
#include <pni/arrays/index_map/index_maps.hpp>

namespace pni{
namespace core{

    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief index iterator
    //! 
    //! This iterator runs over a set of multidimensional indices where each of
    //! these indices is identified by its linear offset. 
    //! Via the template parameters the user can control what container type he
    //! wants to use for the index and which index map he wants to use. By 
    //! setting the index map one can be sure that the indices are iterated in 
    //! a way so that the number of chache misses during memory access is 
    //! minimal.
    //! 
    //! In C++ terminology this iterator is a random access input iterator 
    //! (one can only read from the elements the iterator points to).
    //!
    //! \tparam INDEXT type of the index container
    //! \tparam IMT index map type
    //!
    template<
             typename INDEXT,
             typename IMT
            > 
    class index_iterator
    {
        public:
            //===================public types==================================
            //! local index map type
            typedef IMT map_type;
            //! local index type
            typedef INDEXT index_type;
            //! type to store the index
            typedef index_type value_type;
            //! pointer type to an index
            typedef const value_type* pointer;
            //! reference type to an index
            typedef const value_type& reference;
            //! container pointer type
            typedef const value_type* cptr_type;
            //! iterator difference type
            typedef ssize_t difference_type;
            //! type of the iterator
            typedef index_iterator<index_type,map_type> iterator_type;
        private:
            //! the index map used to compute the indices
            map_type _index_map;
            //! the actual state of the iterator
            ssize_t _state;
            //! index buffer
            index_type _index;

        public:
            //===================constructors and destructor===================
            //! default constructor
            index_iterator();

            //-----------------------------------------------------------------
            //! 
            //! \brief constructor
            //! 
            //! Construct an index_iterator from a shape object.
            //! 
            //! \tparam CTYPE container type for shape
            //! \param shape shape for which to iterate over indices
            //! \param state iterator state at creation
            //!
            template<typename CTYPE>
            index_iterator(const CTYPE &shape,size_t state=0):
                _index_map(map_utils<map_type>::create(shape)),
                _state(state),
                _index(shape.size())
            {}

            //====================factory to create an index iterator==========
            //!
            //! \brief static creation function
            //! 
            //! Function to create an iterator to the first index of a 
            //! particular shape.
            //! 
            //! \param shape the shape of the array for which we want to create 
            //! the index iterator
            //! 
            //! \return iterator to first index
            //!
            template<typename CTYPE>
            static iterator_type begin(const CTYPE &shape)
            {
                return index_iterator(shape);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief static creation function
            //! 
            //! Create iterator to the last index of an particular shape.
            //! \param shape the shape of the array for which the index should 
            //! be created.
            //! 
            //! \return iterator
            //!
            template<typename CTYPE>
            static iterator_type end(const CTYPE &shape)
            {
                size_t size=std::accumulate(shape.begin(),shape.end(),size_t(1),
                            std::multiplies<size_t>());;

                return index_iterator(shape,size);
            }

            //===================public member functions=======================
            //!
            //! \brief dereferencing operator
            //! 
            //! Returns the actual index. 
            //! \return index value
            //!
            value_type operator*()
            {
                return _index;
            }

            //-----------------------------------------------------------------
            //! pointer access operator
            pointer operator->()
            {
                return &_index;
            }

            //-----------------------------------------------------------------
            //! increment operator
            iterator_type &operator++()
            {
                _state++;
                if(_state < ssize_t(_index_map.max_elements()))
                    _index = _index_map.template index<index_type>(_state);
                return *this;
            }

            //-----------------------------------------------------------------
            //! postfix increment operator
            iterator_type operator++(int )
            {
                iterator_type temp = *this;
                ++(*this);
                return temp;
            }

            //-----------------------------------------------------------------
            //! decrement operator
            iterator_type &operator--()
            {
                _state--;
                if(this->_state>=0)
                    _index = _index_map.template index<index_type>(_state);

                return *this;
            }

            //-----------------------------------------------------------------
            //! postfix decrement operator
            iterator_type operator--(int )
            {
                iterator_type temp = *this;
                --(*this);
                return temp;
            }

            //-----------------------------------------------------------------
            //! equality operator
            bool operator==(const iterator_type &a)
            {
                return this->_state==a._state;
            }

            //-----------------------------------------------------------------
            //! inequality operator
            bool operator!=(const iterator_type &a)
            {
                if(*this == a) return false;
                return true;
            }
    };


//end of namespace 
}
}
