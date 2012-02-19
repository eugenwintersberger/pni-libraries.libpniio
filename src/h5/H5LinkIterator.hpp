/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Declaration of an HDF5 group object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#ifndef __H5LINKITERATOR_HPP__
#define __H5LINKITERATOR_HPP__

extern "C"{
#include<hdf5.h>
}


namespace pni{
    namespace nx{
        namespace h5{

            //! \ingroup nxh5_classes
            //! \brief Group iterator
    
            //! This is a forward iterator that runs through all the objects
            //! linked below a group. 
            template<typename H5ObjectT,typename ItemT> class H5LinkIterator
            {
                private:
                    const H5ObjectT *_parent; //!< parent object of the interator
                    size_t     _nlinks; //!< total number of links
                    size_t     _index;  //!< actual index 
                    ItemT      _item;   //!< the actual object to which the 
                                        //!< interator referes
                public:
                    typedef H5ObjectT iterable_type;
                    typedef ItemT     item_type;
                    //===========constructors and destructor===================
                    //! default constructor
                    H5LinkIterator():
                        _parent(nullptr),
                        _nlinks(0),
                        _index(0),
                        _item()
                    {}   
                    //! copy constructor
                    H5LinkIterator(const H5LinkIterator<H5ObjectT,ItemT> &i):
                        _parent(i._parent),
                        _nlinks(i._nlinks),
                        _index(i._index),
                        _item(i._item)
                    {}

                    //! move constructor
                    H5LinkIterator(H5LinkIterator<H5ObjectT,ItemT> &&i):
                        _parent(i._parent),
                        _nlinks(i._nlinks),
                        _index(i._index),
                        _item(std::move(i._item))
                    {
                        i._parent = nullptr;
                        i._nlinks = 0;
                        i._index  = 0;
                    }

                    //! constructor from group object
                    H5LinkIterator(const H5ObjectT &g,size_t start_index=0):
                        _parent(&g),
                        _nlinks(g.nchilds()),
                        _index(start_index),
                        _item()
                    {
                        if(_index < _nlinks) _item = _parent->open(_index);
                    }

                    //! destructor
                    virtual ~H5LinkIterator(){
                        _parent = nullptr;
                        _nlinks = 0;
                        _index  = 0;
                        _item.close();
                    }

                    //=============assignment operators========================
                    //! copy assignment operator
                    H5LinkIterator<H5ObjectT,ItemT> &
                        operator=(const H5LinkIterator<H5ObjectT,ItemT> &i)
                    {
                        if(this != &i){
                            _parent = i._parent;
                            _nlinks = i._nlinks;
                            _index  = i._index;
                            _item   = i._item;
                        }
                        return *this;
                    }

                    //! move assignment operator
                    H5GroupIterator<H5ObjectT,ItemT> &
                        operator=(H5GroupIterator<H5ObjectT,ItemT> &&i)
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

                    //! conversion to bool 
                    operator bool() 
                    {
                        if(_index >= _nlinks) return false;
                        return true;
                    }

                    //! pointer access operator
                    ItemT  *operator->()
                    {
                        return &_item;
                    }
                    
                    //! pointer access operator
                    const ItemT *operator->() const
                    {
                        return &_item;
                    }
                    
                    //! dereferencing operator
                    ItemT & operator*()
                    {
                        return _item;
                    }

                    const ItemT &operator*() const
                    {
                        return _item;
                    }

                    //! increment operator
                    H5LinkIterator<H5ObjectT,ItemT> &operator++()
                    {
                        EXCEPTION_SETUP("H5GroupIterator<ItemT> &operator++()");

                        //if the actual index is equal to the total number
                        //of links no increment is possible
                        _index++;
                        if(_index < _nlinks){
                            _item = _parent->open(_index);
                        }


                        return *this;
                    }

                    H5LinkIterator<H5ObjectT,ItemT> &operator++(int i)
                    {
                        EXCEPTION_SETUP("H5GroupIterator<ItemT> &operator++(int i)");
                        
                        //if the actual index is equal to the total number
                        //of links no increment is possible
                        _index++;
                        if(_index < _nlinks){
                            _item = _parent->open(_index);
                        }


                        return *this;
                    }

                    bool operator==(const H5LinkIterator<H5ObjectT,ItemT> &o)
                        const
                    {
                        if(_parent != o._parent) return false;
                        if(_index  != o._index)  return false;
                        if(_nlinks != o._nlinks) return false;
                        return true;
                    }

                    bool operator!=(const H5LinkIterator<H5ObjectT,ItemT> &o)
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

#endif
