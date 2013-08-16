/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Attribute iterator for all objects.
 *
 * Created on: Feb 20, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

namespace pni{
namespace io{
namespace nx{
    //need this here to avoid name collisions with tango headers.
    using pni::core::array;
    using pni::core::string;
    using pni::core::exception;

    /*! 
    \ingroup nexus_lowlevel
    \brief Attribute iterator

    This is a forward iterator that runs through all the attributes attached to
    an object.
    */
    template<typename IterableT,typename ItemT> class nxattribute_iterator
    {
        private:
            const IterableT *_parent; //!< parent object of the interator
            size_t     _nattrs; //!< total number of links
            size_t     _index;  //!< actual index 
            ItemT      _item;   //!< the actual object to which the 
                                //!< interator referes
        public:
            //===============public types======================================
            typedef IterableT iterable_type; //!< iteratble type
            typedef ItemT     item_type;     //!< item type
            //=============constructors and destructor=========================
            //! default constructor
            nxattribute_iterator():
                _parent(nullptr),
                _nattrs(0),
                _index(0),
                _item()
            {}   

            //-----------------------------------------------------------------
            //! copy constructor
            nxattribute_iterator(const nxattribute_iterator<IterableT,ItemT> &i):
                _parent(i._parent),
                _nattrs(i._nattrs),
                _index(i._index),
                _item(i._item)
            {}

            //-----------------------------------------------------------------
            //! move constructor
            nxattribute_iterator(nxattribute_iterator<IterableT,ItemT> &&i):
                _parent(i._parent),
                _nattrs(i._nattrs),
                _index(i._index),
                _item(std::move(i._item))
            {
                i._parent = nullptr;
                i._nattrs = 0;
                i._index  = 0;
            }

            //-----------------------------------------------------------------
            //! constructor from group object
            nxattribute_iterator(const IterableT &g,size_t start_index=0):
                _parent(&g),
                _nattrs(g.nattr()),
                _index(start_index),
                _item()
            {
                if(_index < _nattrs) _item = _parent->attr(_index);
            }

            //-----------------------------------------------------------------
            //! destructor
            virtual ~nxattribute_iterator()
            {
                _parent = nullptr;
                _nattrs = 0;
                _index  = 0;
                _item.close();
            }

            //==================assignment operators===========================
            //! copy assignment operator
            nxattribute_iterator<IterableT,ItemT> &
                operator=(const nxattribute_iterator<IterableT,ItemT> &i)
            {
                if(this != &i)
                {
                    _parent = i._parent;
                    _nattrs = i._nattrs;
                    _index  = i._index;
                    _item   = i._item;
                }
                return *this;
            }

            //-----------------------------------------------------------------
            //! move assignment operator
            nxattribute_iterator<IterableT,ItemT> &
                operator=(nxattribute_iterator<IterableT,ItemT> &&i)
            {
                if(this != &i)
                {
                    _parent = i._parent;
                    i._parent = nullptr;
                    _nattrs = i._nattrs;
                    i._nattrs = 0;
                    _index  = i._index;
                    i._index = 0;
                    _item   = std::move(i._item);
                }
                return *this;
            }

            //-----------------------------------------------------------------
            //! conversion to bool 
#ifdef NOEXPLICITCONV
            operator bool()
#else
            explicit operator bool() 
#endif
            {
                if(_index >= _nattrs) return false;
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
            //! pointer operator
            const ItemT &operator*() const
            {
                return _item;
            }

            //-----------------------------------------------------------------
            //! postfix increment operator 
            nxattribute_iterator<IterableT,ItemT> &operator++()
            {
                //if the actual index is equal to the total number
                //of links no increment is possible
                _index++;
                if(_index < _nattrs) _item = _parent->attr(_index);

                return *this;
            }

            //-----------------------------------------------------------------
            //! prefix increment operator
            nxattribute_iterator<IterableT,ItemT> &operator++(int i)
            {
                //if the actual index is equal to the total number
                //of links no increment is possible
                _index++;
                if(_index < _nattrs) _item = _parent->attr(_index);

                return *this;
            }

            //-----------------------------------------------------------------
            //! equality operator
            bool operator==(const nxattribute_iterator<IterableT,ItemT> &o)
                const
            {
                if(_parent != o._parent) return false;
                if(_index  != o._index)  return false;
                if(_nattrs != o._nattrs) return false;
                return true;
            }

            //-----------------------------------------------------------------
            //! in-equalty operator
            bool operator!=(const nxattribute_iterator<IterableT,ItemT> &o)
                const
            {
                if(*this == o) return false;
                return true;
            }


    };
//end of namespace
}
}
}
