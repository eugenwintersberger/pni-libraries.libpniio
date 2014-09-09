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
// Created on: Aug 22, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

namespace pni{
namespace io{
namespace nx{

    //! 
    //! \ingroup nexus_lowlevel
    //! \brief recursive iterator 
    //! 
    //! This is the most generic iterator provided by libpnicore. It can be 
    //! used with all container types provided by the library. A container 
    //! that wants to use this iterator must implement the following 
    //! interface
    //!
    //! \code
    //! template<typename T> class Iterable<T>
    //! {
    //!     public:
    //!         typedef T value_type;
    //!         size_t size() const;
    //!         T &operator[](size_t i);
    //!         T operator[](size_t i) const;
    //! };
    //! \endcode
    //! 
    //! This template implements a simple forward iterator. Unlike STL 
    //! iterators an exception is thrown if one tries to dereference an invalid 
    //! iterator
    //! 
    //! \tparam ITERT iterator type
    //!
    template<typename ITERT> class recursive_iterator
    {
        public:
            typedef ITERT child_iterator_type;
            typedef std::pair<ITERT,ITERT> range_type;
            typedef typename child_iterator_type::value_type value_type;
        private:
            range_type _parent_range;
            child_iterator_type _current;
            child_iterator_type _end;
        public:
            //====================public types==================================

            explicit recursive_iterator(const parent_range &parent,
                                        const child_iterator_type &begin,
                                        const child_iterator_type &end):
                _parent_range(parent),
                _current(begin),
                _end(end)
            { }


            //====================public methods and operators==================
            explicit operator bool() const
            {
                return _current;
            }
            //------------------------------------------------------------------
            //! 
            //! \brief dereferencing operator
            //!
            //! Returns a reference on the object the iterator is actually 
            //! pointer or the object by value. The return type depends if the 
            //! iterator is used as a standard iterator or a const iterator.
            //!
            //! \throws IteratorError if the iterator is invalid
            //! \return reference or value of the actual object
            //!
            value_type &operator*()
            {
                return *_current;
            }

            //------------------------------------------------------------------
            //!
            //! \brief pointer access operator
            //!
            //! Returns a const or non-const pointer to the object the iterator
            //! actually points to. 
            //!
            //! \throws IteratorError if the iterator is invalid
            //! \return pointer to actual object
            //!
            value_type* operator->()
            {
                return &(*_current);
            }

            //------------------------------------------------------------------
            //! increment iterator position
            recursive_iterator<child_iterator_type> operator++()
            {
                if(is_group(*_current))
                    return recursive_iterator<child_iterator_type>(range_type(_current,_end),*_current->begin(),*_current->end());

                //not finished with this level
                _current++;
                if(_current == _end)
                    return _parent++;
                else
                    return *this;

            }

            //------------------------------------------------------------------
            //! increment iterator position
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            recursive_iterator<child_iterator_type> operator++(int i)
            {
                recursive_iterator<child_iterator_type> temp = *this;
                ++(*this);
                return temp;
            }
#pragma GCC diagnostic pop

            //------------------------------------------------------------------
            //! comparsion operator - equality
            bool operator==(const recursive_iterator<child_iterator_type> &a)
            {
                return _current==a._current && _end == a._end;
            }

            //------------------------------------------------------------------
            //! comparison operator - inequality
            bool operator!=(const recursive_iterator<child_iterator_type> &a)
            {
                return !((*this)==a);
            }

    };


//end of namespace
}
}
}
