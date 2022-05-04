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
// Created on: May 14, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//


#pragma once

#include <memory>
#include <functional>
#include <pni/arrays/index_map/index_maps.hpp>
#include <pni/utilities.hpp>
#include <pni/arrays/array_selection.hpp>
#include <pni/arrays/index_utilities.hpp>
#include <pni/algorithms/math/inplace_arithmetics.hpp>
#include <pni/types/types.hpp>
#include <pni/types/container_trait.hpp>
#include <pni/types/type_id_map.hpp>

namespace pni{
    
    //! 
    //! \ingroup mdim_array_classes
    //! \brief provides a view on a part of an array
    //!
    //! The ArrayView class provides a view on the part of an array. No new 
    //! memory is allocated.  An array view can be obtained from an array 
    //! using the () operator. 
    //!
    //! \code
    //! darray<float32> a(std::vector<size_t>{3,4,10});
    //!
    //! //create a (4,10) view from the above array
    //! auto view = a(1,slice{0,4},Slice{0,10});
    //!
    //! //the view can now be used like any other array - however, no new
    //! //memory isallocated.
    //!
    //! //create an array from the view
    //! darray<float32> roi(view.shape<std::vector<size_t> >(),
    //!                 darray<float32>::storage_type(view));
    //! \endcode
    //!
    //! \tparam ArrayT array type for the view
    //!
    template<typename ArrayT> 
    class array_view
    {
        public:
            //====================public types=================================
            //! storage type
            using storage_type =  ArrayT;
            //! type of the data values
            using value_type = typename ArrayT::value_type;
            //! type of the view 
            using array_type =  array_view<storage_type>;
            //! shared pointer type
            using shared_ptr =  std::shared_ptr<array_type>;
            //! unique pointer type
            using unique_ptr =  std::unique_ptr<array_type>;
            //! iterator type
            using iterator = container_iterator<array_type>;
            //! const iterator type
            using const_iterator = container_iterator<const array_type>;
            //! view type
            using view_type = array_view<array_type>;
            //! index type
            using index_type = std::vector<size_t>;
            //! inplace arithetic type
            using inplace_arithmetic = typename ArrayT::inplace_arithmetic;
            //! map type
            using map_type =  index_map<index_type,typename ArrayT::map_type::implementation_type>;
            //========================public members===========================
            //! type id of the value_type
            static const type_id_t type_id = ArrayT::type_id;
        private:
            //! parent array from which to draw data
            std::reference_wrapper<ArrayT> _parray; 
            //! selection object for index transformation 
            array_selection _selection;
            //! local index map - only used internally, this map describes the
            //view not the original array.
            map_type _imap;
            //! local index buffer for index calculations
            mutable index_type _index;
            //! check if selection is contiguous
            bool _is_contiguous;

            //! offset of the first element
            size_t _start_offset;

        public:
            //-----------------------------------------------------------------
            //! 
            //! \brief constructor
            //!
            //! Constructs a new ArrayView from an existing array and some
            //! additional information.
            //! \param a reference to the original array
            //! \param s selection object defining the description dimension
            //!
            array_view(storage_type &a,const array_selection &s):
                _parray(std::ref(a)),
                _selection(s),
                _imap(map_utils<map_type>::create(_selection.shape<index_type>())),
                _index(a.rank()),
                _is_contiguous(pni::is_contiguous(a.map(),_selection)),
                _start_offset(start_offset(a.map(),_selection))
            { }

            //------------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! This constructor accepts an rvalue reference for the 
            //! selection. In some cases this might be more efficient than 
            //! copy construction. 
            //!
            //! \param a reference to the original array
            //! \param s rvalue reference to the selection object
            //!
            array_view(storage_type &a,array_selection &&s):
                _parray(std::ref(a)),
                _selection(std::move(s)),
                _imap(map_utils<map_type>::create(_selection.shape<index_type>())),
                _index(a.rank()),
                _is_contiguous(pni::is_contiguous(a.map(),_selection)),
                _start_offset(start_offset(a.map(),_selection))
            {}


            //-----------------------------------------------------------------
            //!
            //! \brief copy constructor
            //!
            array_view(const array_type &c):
                _parray(c._parray),
                _selection(c._selection),
                _imap(c._imap),
                _index(c._index),
                _is_contiguous(c._is_contiguous),
                _start_offset(c._start_offset)
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief move constructor
            //!
            array_view(array_type &&c):
                _parray(std::move(c._parray)),
                _selection(std::move(c._selection)),
                _imap(std::move(c._imap)),
                _index(std::move(c._index)),
                _is_contiguous(c._is_contiguous),
                _start_offset(c._start_offset)
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief copy assignment operator
            //!
            template<typename ElementT>
            array_type &operator=(const ElementT &e)
            {
                if((void*)this == (void*)&e) return *this;
               
                //for(size_t i=0;i<size();++i) (*this)[i] = e[i];
                std::copy(e.begin(),e.end(),this->begin());

                return *this;
            }


            //-----------------------------------------------------------------
            //!
            //! \brief move assignment operator
            //!
            array_type &operator=(array_type &&a)
            {
                if(this == &a) return *this;

                _parray = std::move(a._parray);
                _selection = std::move(a._selection);
                _imap = std::move(a._imap);
                _index = std::move(a._index);
                _is_contiguous = a._is_contiguous;
                _start_offset  = a._start_offset;

                return *this;
            }

            //==================public member functions========================
            //! 
            //! \brief access with container index 
            //!
            //! Using a container object to hold the multidimensional indices 
            //! to access view data. 
            //! 
            //! \throws shape_mismatch_error if size of container does not 
            //! match view rank
            //! \tparam ContainerT container type for index values
            //! \param index container with multidimensional index
            //! \return reference to value at index
            //!
            template<
                     typename ContainerT,
                     typename = typename enable_element_cont<ContainerT>::type
                    >
            value_type &operator()(const ContainerT &index)
            {
                typedef typename ArrayT::map_type omap_type;
                auto &ref = _parray.get();

                if(_is_contiguous)
                    return ref[_start_offset + _imap.offset(index)];
                else
                {
                    auto  map = const_cast<omap_type&>(ref.map());
                    size_t o = map.offset(_selection,index);
                    return ref[o];
                }
            }

            //-----------------------------------------------------------------
            //!
            //! \brief access with container index 
            //!
            //! Using a container object to hold the multidimensional indices 
            //! to access view data. 
            //! 
            //! \throws shape_mismatch_error if size of container does not 
            //! match view rank
            //! \tparam ContainerT container type for index values
            //! \param index container with multidimensional index
            //! \return value at index
            //!
            template<
                     typename ContainerT,
                     typename = typename enable_element_cont<ContainerT>::type
                    >
            value_type operator()(const ContainerT &index) const
            {
                typedef typename ArrayT::map_type omap_type;
                auto &ref = _parray.get();

                if(_is_contiguous)
                    return ref[_start_offset + _imap.offset(index)];
                else
                {
                    auto  map = const_cast<omap_type&>(ref.map());
                    size_t o = map.offset(_selection,index);
                    return ref[o];
                }
            }


            //-----------------------------------------------------------------
            //! 
            //! \brief multidimensional access to data
            //!
            //! () operator allows access to the data using a multidimensional
            //! index represented by the arguments of the operator. 
            /*!
            \code 
            darray<Float32> data({100,200,100});
            auto view = data(slice(50,75),slice(0,200),slice(25,41));
            std::cout<<view(3,34,10)<<std::endl;
            \endcode
            !*/
            //! This works essentially the same as for the Array template.
            //! \tparam ITypes index types
            //! \param indices instances of ITypes determining the index
            //! \return reference to the value at multidimensional index
            //!
            template<typename ...ITypes> 
            value_type & operator()(ITypes ...indices)
            {
                typedef typename ArrayT::map_type omap_type;
                auto &ref = _parray.get();

                if(_is_contiguous)
                    return ref[_start_offset +
                               _imap.offset(IDX_ARRAY(ITypes,indices))];
                else
                {
                    auto  map = const_cast<omap_type&>(ref.map());
                    size_t o = map.offset(_selection,IDX_ARRAY(ITypes,indices));
                    return ref[o];
                }

            }

            //-----------------------------------------------------------------
            //!
            //! \brief multidimensional access to data
            //!
            //! () operator allows access to the data using a multidimensional
            //! index represented by the arguments of the operator. 
            /*!
            \code 
            darray<float32> data({100,200,100});
            auto view = data(slice(50,75),slice(0,200),slice(25,41));
            std::cout<<view(3,34,10)<<std::endl;
            \endcode
            !*/
            //! This works essentially the same as for the Array template.
            //! \tparam ITypes index types
            //! \param indices instances of ITypes determining the 
            //! multidimensional index
            //! \return value at multidimensional index
            //!
            template<typename ...ITypes> 
            value_type operator()(ITypes ...indices) const
            {
                typedef typename ArrayT::map_type omap_type;
                auto &ref = _parray.get();

                if(_is_contiguous)
                    return ref[_start_offset + 
                               _imap.offset(IDX_ARRAY(ITypes,indices))];
                else
                {
                    //have to do some more work here
                    auto map = const_cast<omap_type&>(ref.map());
                    return ref[map.offset(_selection,IDX_ARRAY(ITypes,indices))];
                }
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief get shape of the view
            //! 
            //! This returns the shape of the array view. This shape includes 
            //! only those dimensions where the number of elements along the 
            //! original array is not equal 1. 
            //! 
            //! \return Shape object
            //!
            template<typename ContainerT> ContainerT shape() const
            {
                return _selection.template shape<ContainerT>();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief linearzed access
            //!
            //! Provides access to the linearized data. With this operator
            //! linear access is provided to the elements of the view.
            //! \throws memory_access_error if some of the involved objects 
            //! is not allocated
            //! \param i linear index of the element
            //! \return reference to the value at index i 
            //!
            value_type &operator[](size_t i)
            {
#ifdef DEBUG
                check_index_in_dim(i,size(),EXCEPTION_RECORD);
#endif
                //compute the multidimensional index in the original array for
                //the linear index i in the view
                if(_is_contiguous) return _parray.get()[i+_start_offset];
                else
                {
                    auto index = _imap.template index<index_type>(i);
                    return (*this)(index); 
                }
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief linearized access
            //!
            //! Provides const access to the linearized data. With this 
            //! operator linear access is provided to the elements of the 
            //! view.
            //! 
            //! \throws memory_access_error if some of the involved objects 
            //! is not allocated
            //! \param i linear index of the element
            //! \return value at index i 
            
            value_type operator[](size_t i) const
            {
#ifdef DEBUG
                check_index_in_dim(i,size(),EXCEPTION_RECORD);
#endif
                if(_is_contiguous) return _parray.get()[i+_start_offset];
                else
                {
                    //compute the multidimensional index in the original array for
                    //the linear index i in the view
                    auto index = _imap.template index<index_type>(i);
                    return (*this)(index); 
                }
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get pointer to data
            //! 
            //! This method returns a pointer to the storage covered by the 
            //! view. However, this is only possible if the selection on which
            //! the view is passed is contiguous. 
            //! In the case of a non contiguous view an exception will be 
            //! thrown. 
            //! 
            //! \throw shape_mismatch_error if selection not contiguous
            //! \return const pointer to data
            //! 
            const value_type *data() const
            {
                if(_is_contiguous) 
                    return &_parray.get()[_start_offset];
                else
                    throw shape_mismatch_error(EXCEPTION_RECORD,
                            "Selection view is not contiguous!");
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get pointer to data
            //! 
            //! This method returns a pointer to the storage covered by the 
            //! view. However, this is only possible if the selection on which
            //! the view is passed is contiguous. 
            //! In the case of a non contiguous view an exception will be 
            //! thrown. 
            //! 
            //! \throw shape_mismatch_error if selection not contiguous
            //! \return const pointer to data
            //! 
            value_type *data() 
            {
                if(_is_contiguous) 
                    return &_parray.get()[_start_offset];
                else
                    throw shape_mismatch_error(EXCEPTION_RECORD,
                            "Selection view is not contiguous!");
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get value at index i
            //!
            //! Return a reference to the element at linear index i within 
            //! the view.  Unlike the [] operators this member function will 
            //! throw an exception if the index exceeds the size of the view.  
            //! 
            //! \throws index_error in case that the index exceeds the size 
            //! of the view
            //! \param i index at which to get the data
            //! \return reference to the element at index i
            //!
            value_type &at(size_t i) 
            { 
                check_index_in_dim(i,size(),EXCEPTION_RECORD); 
                return (*this)[i]; 
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get value at index i
            //!
            //! Return the value of the element at linear index i within the 
            //! view.  Unlike the [] operators this member function will 
            //! throw an exception if the index exceeds the size of the view.
            //!
            //! \throws index_error in case that the index exceeds the size of the
            //! view
            //! \param i index at which to get the data
            //! \return reference to the element at index i
            //!
            value_type at(size_t i) const 
            { 
                check_index_in_dim(i,size(),EXCEPTION_RECORD);
                return (*this)[i]; 
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief insert value at i
            //! 
            //! Insert a new value at the linear index i of the view. 
            //! 
            //! \throws index_error if i exceeds total size
            //! \param i linear index
            //! \param v new value to insert
            //! 
            void insert(size_t i,const value_type &v) { at(i) = v; }

            //-----------------------------------------------------------------
            //! 
            //! \brief return reference to the first element
            //!
            value_type &front() { return at(0); }

            //-----------------------------------------------------------------
            //! 
            //! \brief return value of first element
            //!
            value_type front() const { return at(0); }

            //-----------------------------------------------------------------
            //! 
            //! \brief return reference ot the last vlaue  
            //!
            value_type &back() { return at(size()-1); }

            //-----------------------------------------------------------------
            //! 
            //! \brief return value of last element
            //! 
            value_type back() const { return at(size()-1); }

            //-----------------------------------------------------------------
            //!
            //! \brief get size
            //!
            //! Return the total number of elements referenced by this view. 
            //! \return total number of elements
            //!
            size_t size() const
            {
                return _selection.size();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get rank of the view
            //!
            //! Returns the number of dimensions of the array.
            //!
            //! \return number of dimensions
            //! 
            size_t rank()  const 
            { 
                return _selection.rank(); 
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief iterator to first element
            //!
            //! Return an interator to the first element of the array view. 
            //! \return iterator to the first element
            //!
            iterator begin() { return iterator(this,0); }

            //-----------------------------------------------------------------
            //! 
            //! \brief iterator to last element
            //!
            //! Return an iterator to the last element of the array view.
            //! \return iterator to last element
            //!
            iterator end() { return iterator(this,this->size()); }
           
            //-----------------------------------------------------------------
            //! 
            //! \brief const iterator to first element
            //!
            //! Return an const interator to the first element of the array 
            //! view. 
            //! 
            //! \return iterator to the first element
            //!
            const_iterator begin() const { return const_iterator(this,0); }

            //-----------------------------------------------------------------
            //! 
            //! \brief const iterator to last element
            //!
            //! Return an const iterator to the last+1 element of the array 
            //! view.
            //! The iterator is thus invalid.
            //! 
            //! \return iterator to last element
            //!
            const_iterator end() const { return const_iterator(this,size()); }
            
            //==========implementation of unary arithmetic operators===========
            //!
            //!
            //! \brief unary addition of a scalar
            //!
            /*!
            \code
            array_type a = ...;
            array_type::value_type s = ...;
            auto view = a(0,slice(0,100),slice(3,23));
            
            view += s;
            \endcode
            !*/
            //! \param s the scalar value to add
            //! \return view reference
            //!
            array_type &operator+=(value_type s) 
            { 
                storage_type::inplace_arithmetic::add(*this,s); 
                return *this;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief unary addition of an array 
            //!
            /*!
            \code
            array_type1 a = ...;
            array_tyep2 b = ...;
            auto view = a(1,slice(0,100),slice(3,23));
            
            view += b;
            \endcode
            !*/
            //!
            //! \tparam RightT type of the array to add
            //! \param v reference to the array to add 
            //! \return reference to the original view
            //!
            template<typename RightT> 
            array_type &operator+=(const RightT &v) 
            { 
                storage_type::inplace_arithmetic::add(*this,v); 
                return *this;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief unary subtraction of a scalar
            //!
            /*!
            \code
            array_type a = ...;
            array_type::value_type s = ...;
            auto view = a(0,slice(0,100),slice(3,23));
            
            view -= s;
            \endcode
            !*/
            //! \param s the scalar value to subtract
            //! \return view reference
            //!
            array_type &operator-=(value_type s) 
            { 
                storage_type::inplace_arithmetic::sub(*this,s); 
                return *this;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief unary subtraction of an array
            //!
            /*!
            \code
            array_type1 a = ...;
            array_tyep2 b = ...;
            
            auto view = a(0,slice(0,100),slice(2,23));
            
            view -= b;
            \endcode
            !*/
            //!
            //! \tparam RightT type of the array to subtract
            //! \param v reference to the array to subtract 
            //! \return reference to the original view
            //!
            template<typename RightT> 
            array_type &operator-=(const RightT &v) 
            { 
                storage_type::inplace_arithmetic::sub(*this,v); 
                return *this;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief unary multiplication of a scalar
            //!
            /*!
            \code
            array_type a = ...;
            array_type::value_type s = ...;
            auto view = a(slice(0,100),10,slice(2,23));
            
            view *= s;
            \endcode
            !*/
            //! \param s the scalar value to multiply with
            //! \return view reference
            //!
            array_type &operator*=(value_type s) 
            { 
                storage_type::inplace_arithmetic::mult(*this,s); 
                return *this;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief unary multiplication of an array
            //!
            /*!
            \code
            array_type1 a = ...;
            array_tyep2 b = ...;
            auto view = a(slice(0,100),100,slice(2,102));
            
            view *= b;
            \endcode
            !*/
            //!
            //! \tparam RightT type of the array to multiply 
            //! \param v reference to the array to multiply 
            //! \return reference to the original view
            //!
            template<typename RightT>
            array_type &operator*=(const RightT &v) 
            { 
                storage_type::inplace_arithmetic::mult(*this,v); 
                return *this;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief unary division of a scalar
            //!
            /*!
            \code
            array_type a = ...;
            array_type::value_type s = ...;
            auto view = a(slice(0,100),slice(2,3),slice(4,10));
            
            view /= s;
            \endcode
            !*/
            //! \param s the scalar value to divide by
            //! \return array reference
            //!
            array_type &operator/=(value_type s) 
            {
                storage_type::inplace_arithmetic::div(*this,s); 
                return *this;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief unary division of an array
            //!
            /*!
            \code
            array_type1 a = ...;
            array_tyep2 b = ...;
            auto view = a(slice(0,100),10,10);
            
            view /= b;
            \endcode
            !*/
            //!
            //! \tparam RightT type of the array to divide by  
            //! \param v reference to the array to divide by 
            //! \return reference to the original view
            //!
            template<typename RightT>
            array_type &operator/=(const RightT &v) 
            { 
                storage_type::inplace_arithmetic::div(*this,v); 
                return *this;
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief return reference to index map
            //!
            const map_type &map() const
            {
                return _imap;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief check if contiguous
            //! 
            //! Returns true if the view is contiguous. Otherweise false. 
            //! 
            //! \return true if contiguous selection, false otherwise
            bool is_contiguous() const
            {
                return _is_contiguous;
            }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief specialization for type_id 
    //! 
    //! This function returns the type ID of the elements of the array 
    //! referenced by an array view instance.
    //! 
    //! \tparam ArrayT array type
    //! \return type id of element type
    template<typename ArrayT>
    type_id_t type_id(const array_view<ArrayT> &)
    {
        return type_id_map<typename ArrayT::value_type>::type_id;
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief container_trait for an array_view
    //!
    //! Specialization of the container_trait for instances of array_view. 
    //!
    //! \param ArrayT array type of the view
    //!
    template<typename ArrayT> 
    struct container_trait<array_view<ArrayT>>
    {
        //! array_view is a random access container
        static const bool is_random_access = true;
        //! array_view is iterable
        static const bool is_iterable = true;
        //! array view is not by default contiguous
        static const bool is_contiguous = false;
        //! array view is multidimensional
        static const bool is_multidim = true;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_classes
    //! \brief compare two array views
    //! 
    //! Returns true if all elements of a an b are equal. The two views 
    //! must have equal size. Otherwise a size_mismatch_excpetion is thrown.
    //!
    //! \tparam ArrayT array type for the view
    //! \param a lhs value of the operator
    //! \param b rhs value of the operator
    //! \return true if all elements are equal, flase otherwise
    //!
    template<typename ArrayT>
    bool operator==(const array_view<ArrayT> &a,const array_view<ArrayT> &b)
    {
        if(a.size()!=b.size())
            throw size_mismatch_error(EXCEPTION_RECORD,
                    "Array view sizes do not match!");

        return std::equal(a.begin(),a.end(),b.begin());
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_classes
    //! \brief compare two array views
    //! 
    //! Returns false if all elements in a an b are equal. a and b must have
    //! equal size, otherwise a size_mismatch_error exception is thrown. 
    //!
    //! \tparam ArrayT array type for the view
    //! \param a lhs value of the operator
    //! \param b rhs value of the operator
    //! \return false if all values are equal, true otherwise
    //!
    template<typename ArrayT>
    bool operator!=(const array_view<ArrayT> &a,const array_view<ArrayT> &b)
    {
        return !(a==b);
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_classes
    //! \brief output operator for view
    //!
    //! Output a view instance to a stream. 
    //!
    //! \tparam ArrayT array type of the view
    //! \param stream reference to output stream
    //! \param v view instance
    //! \return reference to the modified stream
    //!
    template<typename ArrayT>
    std::ostream &operator<<(std::ostream &stream,const array_view<ArrayT> &v)
    {
        for(auto x: v) stream<<x<<" ";

        return stream;
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_classes
    //! \brief input operator for view
    //!
    //! Write data from a stream to a view.
    //!
    //! \tparam ArrayT array type of the view
    //! \param stream reference to the input stream
    //! \param v reference to the view
    //! \return reference to the modified input stream
    //!
    template<typename ArrayT>
    std::istream &operator>>(std::istream &stream,array_view<ArrayT> &v)
    {
        for(auto &x: v) stream>>x;

        return stream;
    }

//end of namespace
}
