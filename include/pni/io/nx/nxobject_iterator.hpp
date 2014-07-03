//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// a long with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Feb 12, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <iterator>
#include "algorithms/close.hpp"


namespace pni{
namespace io{
namespace nx{
    //need this here to avoid name collisions with tango headers.
    using pni::core::array;
    using pni::core::string;
    using pni::core::exception;


    /*! 
    \ingroup nexus_lowlevel
    \brief Group iterator

    This is a forward iterator that runs through all the objects linked below a
    group. 
    */
    template<typename IterableT,typename ItemT> class nxobject_iterator
    {
        private:
            const IterableT *_parent; //!< parent object of the interator
            size_t     _nlinks; //!< total number of links
            size_t     _index;  //!< actual index 
            ItemT      _item;   //!< the actual object to which the 
                                //!< interator referes
        public:
            typedef IterableT   iterable_type; //!< type of iterable
            typedef ItemT       item_type;     //!< item type
            typedef ItemT       value_type;
            typedef size_t      difference_type;
            typedef value_type* pointer;
            typedef value_type& reference;
            typedef std::forward_iterator_tag iterator_category;
            //================constructors and destructor======================
            //! default constructor
            nxobject_iterator():
                _parent(nullptr),
                _nlinks(0),
                _index(0),
                _item()
            {}   

            //-----------------------------------------------------------------
            //! copy constructor
            nxobject_iterator(const nxobject_iterator<IterableT,ItemT> &i):
                _parent(i._parent),
                _nlinks(i._nlinks),
                _index(i._index),
                _item(i._item)
            {}

            //-----------------------------------------------------------------
            //! move constructor
            nxobject_iterator(nxobject_iterator<IterableT,ItemT> &&i):
                _parent(i._parent),
                _nlinks(i._nlinks),
                _index(i._index),
                _item(std::move(i._item))
            {
                i._parent = nullptr;
                i._nlinks = 0;
                i._index  = 0;
            }

            //-----------------------------------------------------------------
            //! constructor from group object
            nxobject_iterator(const IterableT &g,size_t start_index=0):
                _parent(&g),
                _nlinks(g.nchildren()),
                _index(start_index),
                _item()
            {
                if(_index < _nlinks) _item = _parent->open(_index);
            }

            //-----------------------------------------------------------------
            //! destructor
            virtual ~nxobject_iterator()
            {
                _parent = nullptr;
                _nlinks = 0;
                _index  = 0;
                close(_item);
            }

            //=================assignment operators============================
            //! copy assignment operator
            nxobject_iterator<IterableT,ItemT> &
                operator=(const nxobject_iterator<IterableT,ItemT> &i)
            {
                if(this != &i){
                    _parent = i._parent;
                    _nlinks = i._nlinks;
                    _index  = i._index;
                    _item   = i._item;
                }
                return *this;
            }

            //-----------------------------------------------------------------
            //! move assignment operator
            nxobject_iterator<IterableT,ItemT> &
                operator=(nxobject_iterator<IterableT,ItemT> &&i)
            {
                if(this != &i){
                    _parent = i._parent;
                    i._parent = nullptr;
                    _nlinks = i._nlinks;
                    i._nlinks = 0;
                    _index  = i._index;
                    i._index = 0;
                    _item   = std::move(i._item);
                }
                return *this;
            }

            //-----------------------------------------------------------------
            //! conversion to bool 
            operator bool() 
            {
                if(_index >= _nlinks) return false;
                return true;
            }

            //-----------------------------------------------------------------
            //! pointer access operator
            ItemT  *operator->()
            {
                return &_item;
            }
           
            //-----------------------------------------------------------------
            //! pointer access operator
            const ItemT *operator->() const
            {
                return &_item;
            }
           
            //-----------------------------------------------------------------
            //! dereferencing operator
            ItemT & operator*()
            {
                return _item;
            }

            //-----------------------------------------------------------------
            //! const dereferenceing operator
            const ItemT &operator*() const
            {
                return _item;
            }

            //-----------------------------------------------------------------
            //! increment operator
            nxobject_iterator<IterableT,ItemT> &operator++()
            {
                //if the actual index is equal to the total number
                //of links no increment is possible
                _index++;
                if(_index < _nlinks) _item = _parent->open(_index);


                return *this;
            }

            //-----------------------------------------------------------------
            //! iterator increment
            nxobject_iterator<IterableT,ItemT> &operator++(int i)
            {
                //if the actual index is equal to the total number
                //of links no increment is possible
                _index++;
                if(_index < _nlinks){
                    _item = _parent->open(_index);
                }


                return *this;
            }

            //-----------------------------------------------------------------
            //! iterator comparison for equality
            bool operator==(const nxobject_iterator<IterableT,ItemT> &o) const
            {
                if(_parent != o._parent) return false;
                if(_index  != o._index)  return false;
                if(_nlinks != o._nlinks) return false;
                return true;
            }

            //-----------------------------------------------------------------
            //! iterator comparison for inequality
            bool operator!=(const nxobject_iterator<IterableT,ItemT> &o) const
            {
                if(*this == o) return false;
                return true;
            }


    };

//end of namespace
}
}
}
