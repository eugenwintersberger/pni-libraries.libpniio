//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jan 16, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/error/exceptions.hpp>
#include <pni/type_erasures/value.hpp>
#include <pni/type_erasures/value_ref.hpp>

namespace pni{

    class array;
   
    //=========================================================================
    //! 
    //! \ingroup type_erasure_classes_internal
    //! \brief type map for the array_iterator template
    //!
    //! Provides the types required by the array_iterator template depending 
    //! on the state of the const_flag template parameter. This is only a 
    //! stub. See the specialized versions for the concrete types used for 
    //! the iterator.
    //! 
    //! \sa array_iterator_types<0>
    //! \sa array_iterator_types<1>
    //! \tparam const_flag 1 if the iterator is a const iterator.
    //!
    template<int const_flag> struct array_iterator_types
    {};

    //=========================================================================
    //! 
    //! \ingroup type_erasure_classes_internal
    //! \brief type map for a non-const array_iterator instance
    //!
    //! Specialization of the array_iterator_types template for non-const 
    //! iterators.  IN the case of a non-const iterator the value_ref 
    //! instances are return which refere to the particular data values in 
    //! the array.
    //!
    //! \sa array_iterator_types<const_flag>
    //!
    template<> struct array_iterator_types<0>
    {
        //! container pointer
        typedef array *cont_ptr; 
        //! reference type of the element
        typedef value_ref value_type;
        //! return type for the dereferencing operator
        typedef value_ref return_type;
        //! pointer type for -> operator
        typedef value_ref* ptr_type;    
        //! reference type 
        typedef value_ref ref_type;
    };



    //=========================================================================
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief type map for const array_iterator instance
    //!
    //! Specialization of the array_iterator_types type map for const 
    //! array_iterator instances. For const iterators instances of value are 
    //! returned holding copies of the data values.
    //!
    //! \sa array_iterator_types<const_flag>
    //!
    template<> struct array_iterator_types<1>
    { 
        //! container pointer
        typedef const array *cont_ptr; 
        //! value type of the iterator
        typedef value value_type;
        //! return type for dereferencing operator
        typedef value return_type;    
        //! pointer type for -> operator
        typedef const value *ptr_type; 
        //! reference type
        typedef const value &ref_type;
    };
   

    //=========================================================================

    //! 
    //! \ingroup type_erasure_classes_internal   
    //! \brief array iterator
    //!
    //! This is a special iterator template for the array type erasure. The 
    //! template parameter decides whether or not the iterator is const. The 
    //! major difference between this template and the default 
    //! array_iterator<IterableT,const_flag> template is the fact that it 
    //! stores the actual value of the iterator as a member variable. This is 
    //! necessary as the array type erasure does not provide direct access to 
    //! the array type it hides but rather creates new objects providing 
    //! access to this data.
    //!
    template<int const_flag> class array_iterator
    {
        private:
            //! iterator type
            typedef array_iterator_types<const_flag> iterator_types;
            
            //! pointer to the container object
            typename array_iterator_types<const_flag>::cont_ptr _container; 

            //! actual position state of the iterator
            ssize_t _state;                    
        public:
            //====================public types==================================
            //! value type of the container
            typedef typename iterator_types::value_type value_type;
            //! pointer type the iterator provides
            typedef typename iterator_types::ptr_type pointer;
            //! reference type the iterator provides
            typedef typename iterator_types::ref_type reference;
            //! pointer type of the container
            typedef typename iterator_types::cont_ptr cptr_type;
            //! difference type of the iterator
            typedef ssize_t difference_type;
            //! type of iterator
            typedef std::random_access_iterator_tag iterator_category;
            //! iterator type
            typedef array_iterator<const_flag> iterator_type;
            //================constructor and destructor========================
            //! default constructor
            array_iterator():_container(nullptr),_state(0) {}

            //------------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! This constructor takes a pointer to the container and an 
            //! initial position.
            //!
            //! \param container pointer to the container object
            //! \param state initial position of the iterator
            //!
            explicit array_iterator(cptr_type container,size_t state=0):
                _container(container),
                _state(state)
            { }

            //------------------------------------------------------------------
            //! copy constructor
            array_iterator(const iterator_type &i):
                _container(i._container),
                _state(i._state)
            { }

            //------------------------------------------------------------------
            //! move constructor
            array_iterator(iterator_type &&i):
                _container(i._container),
                _state(i._state)
            {
                i._container = nullptr;
                i._state = 0;
            }

            //====================public methods and operators==================
            //! 
            //! \brief conversion operator
            //!
            //! This operator allows the conversion of an iterator to bool. It 
            //! will return true if the iterator is valid and false otherwise.
            //! The iterator is consideres as invalid if its internal state is 
            //! at least one after the last element or smaller than 0. It is 
            //! important that this conversion operator is set \c explicit. 
            //! Otherwise the iterator would be implicitly convertible to 
            //! integer (via bool).
            //! 
            //! \return boolean value
            //!
            explicit operator bool() const
            {
                //if(!this->_container) return false;
                //ssize_t size = (ssize_t)(this->_container->size());
                return !((!_container)||
                         (_state >= ssize_t(_container->size()))||
                         (_state<0));
            }

            //------------------------------------------------------------------
            //!
            //! \brief dereferencing operator
            //!
            //! Returns a reference on the object the iterator is actually 
            //! pointer or the object by value. The return type depends if the 
            //! iterator is used as a standard iterator or a const iterator.
            //!
            //! \throws iterator_error if the iterator is invalid
            //! \return reference or value of the actual object
            //!
            typename array_iterator_types<const_flag>::return_type operator*()
            {
                if(!(*this))
                    throw iterator_error(EXCEPTION_RECORD,"Iterator invalid!");
            
                return (*_container)[_state];
            }

            //------------------------------------------------------------------
            //!
            //! \brief dereferencing operator
            //!
            //! Returns a const reference on the object the iterator is actually 
            //! pointer or the object by value. The return type depends if the 
            //! iterator is used as a standard iterator or a const iterator.
            //!
            //! \throws iterator_error if the iterator is invalid
            //! \return reference or value of the actual object
            //!
            typename array_iterator_types<const_flag>::return_type operator*()
                const
            {
                if(!(*this))
                    throw iterator_error(EXCEPTION_RECORD,"Iterator invalid!");
            
                return (*_container)[_state];
            }
            //------------------------------------------------------------------
            //! increment iterator position
            iterator_type &operator++()
            {
                _state++;
                return *this;
            }

            //------------------------------------------------------------------
            //! increment iterator position
            iterator_type operator++(int)
            {
                iterator_type temp = *this;
                ++(*this);
                return temp;
            }

            //------------------------------------------------------------------
            //! decrement operators
            iterator_type &operator--()
            {
                _state--;
                return *this;
            }

            //------------------------------------------------------------------
            //! decrement operators
            iterator_type operator--(int)
            {
                iterator_type tmp = *this;
                --(*this);
                return tmp;
            }

            //------------------------------------------------------------------
            //! compound assignment with +=
            iterator_type &operator+=(ssize_t i)
            {
                _state += i;
                return *this;
            }

            //------------------------------------------------------------------
            //! compound assignment with -=
            iterator_type &operator-=(ssize_t i)
            {
                _state -= i;
                return *this;
            }
            //------------------------------------------------------------------
            //! comparsion operator - equality
            bool operator==(const iterator_type &a)
            {
                //check if the iterators point to the same container
                if(_container != a._container) return false;
                //check if the iterators point to the same element
                //within the container
                if(_state != a._state) return false;

                return true;
            }

            //------------------------------------------------------------------
            //! comparison operator - inequality
            bool operator!=(const iterator_type &a)
            {
                if((*this)==a) return false;
                return true;
            }

            //===============comparison operators==============================
            //! lesser than operator
            bool operator<(const iterator_type &b) 
            { 
                return _state < b._state; 
            }

            //-----------------------------------------------------------------
            //! lesser than equal operator
            bool operator<=(const iterator_type &b)
            {
                return _state <= b._state;
            }

            //-----------------------------------------------------------------
            //! greater than operator
            bool operator>(const iterator_type &b)
            {
                return _state > b._state;
            }

            //-----------------------------------------------------------------
            //! greater equal than operator
            bool operator>=(const iterator_type &b)
            {
                return _state >= b._state;
            }

            //! get state of the iterator
            ssize_t state() const { return this->_state; }

    };

    //================binary arithmetic operators===============================
    //! 
    //! \ingroup type_erasure_classes_internal
    //! \brief add scalar to iterator
    //!
    //! Add an offset to the iterator and thus increment its internal state by 
    //! this offset.
    //!
    /*!
    \code
    array_iterator<...> iter = ...'
    array_iteator<...> iter2 = iter+2;
    \endcode
    !*/
    //!
    //! \param a original iterator
    //! \param b offset to add
    //! \return new iterator 
    //!
    template<int const_flag> 
    array_iterator<const_flag> operator+(const array_iterator<const_flag> &a, 
                                         ssize_t b)
    {
        array_iterator<const_flag> iter = a;
        iter += b;
        return iter;
    }

    //--------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief add offset to iterator
    //! 
    //! Add an offset to the iterator and thus increment its internal state by 
    //! this offset.
    //!
    //! \param a offset to add
    //! \param b original iterator
    //! \return new iterator
    //!
    template<int const_flag> 
    array_iterator<const_flag> operator+(ssize_t a, 
                                         const array_iterator<const_flag> &b)
    {
        return b+a;
    }

    //--------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief subtract offset from iterator
    //!
    //! Subtract an integer offset from the iterator and thus decrement the 
    //! internal state of the iterator by this value. 
    //! 
    //! \param a original iterator
    //! \param b offset
    //! \return new iterator to new position
    //!
    template<int const_flag> 
    array_iterator<const_flag> operator-(const array_iterator<const_flag> &a, 
                                          ssize_t b)
    {
        array_iterator<const_flag> iter = a;
        iter -= b;
        return iter;
    }

    //--------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief subtract two iterators
    //! 
    //! Subtract to iterators and return the offset difference between this
    //! two iterators.
    //!
    //! \param a first iterator
    //! \param b second iterator
    //! \return offset difference
    //!
    template<int const_flag>
    ssize_t operator-(const array_iterator<const_flag> &a, 
                      const array_iterator<const_flag> &b)
    {
        return a.state() - b.state();
    }

//end of namespace
}
