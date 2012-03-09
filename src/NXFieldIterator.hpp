#ifndef __NXFIELDITERATOR_HPP__
#define __NXFIELDITERATOR_HPP__

#include<pni/utils/Types.hpp>
#include<pni/utils/Shape.hpp>

template<typename IterableT,typename ItemT> class NXFieldIterator
{
    private:
        const IterableT *_parent;
        Shape _shape;
    public:
        typedef IterableT iterable_type;
        typedef ItemT     item_type;
        //==============constructors and destructors===========================
        //! default constructor
        NXFieldIterator():
            _parent(nullptr)
        {}

        //! copy constructor
        NXFieldIterator(const NXFieldIterator<IterableT,ItemT> &iter):
            _parent(iter._parent) 
        {}

        //! move constructor
        NXFieldIterator(NXFieldIterator<IterableT,ItemT> &&iter):
            _parent(iter._parent)
        
        {
            iter._parent = nullptr;
        }



        //! destructor
        ~NXFieldIterator()
        {
            this->_parent = nullptr; 
        }

        //=================assignment operators=================================
        //! copy assignemnt
        NXFieldIterator<IterableT,ItemT> &
            operator=(const NXFieldIterator<IterableT,ItemT> &o){}

        //! move constructor
        NXFieldIterator<IteableT,ItemT> &
            operator=(NXFieldIterator<IterableT,ItemT> &&o){}

        //======================================================================


};

#endif
