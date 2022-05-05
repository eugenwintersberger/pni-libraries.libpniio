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
// Created on: Oct 28, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

//#include<memory>
#include<iostream>
#include<sstream>
#include<stdexcept>
#include<utility>
#include<complex>
#include<cstdarg>
#include<cstdio>
#include<memory>


#include <pni/error/exception_utils.hpp>
#include <pni/types/types.hpp>
#include <pni/utilities.hpp>
#include <pni/arrays/slice.hpp>
#include <pni/arrays/array_view.hpp>
#include <pni/arrays/array_factory.hpp>
#include <pni/arrays/array_view_utils.hpp>
#include <pni/arrays/index_map/index_maps.hpp>
#include <pni/types/type_id_map.hpp>
#include <pni/algorithms.hpp>


namespace pni {
    
    
    //! 
    //! \ingroup mdim_array_classes
    //! \brief template for a multi-dimensional array class
    //!
    //! \tparam StorageT storage object to use to keep the data
    //! \tparam IndexMapT the index map 
    //! \tparam InplaceArithmeticT unary (inplace) arithmetics implementation
    //!
    template<
             typename StorageT,
             typename IndexMapT=dynamic_cindex_map,
             typename InplaceArithmeticT =inplace_arithmetics
            > 
    class mdarray
    {
        public:
            //================public types=====================================
            //! type of the buffer object
            typedef StorageT storage_type;
            //! arrays element type
            typedef typename storage_type::value_type value_type;  
            //! index map type
            typedef IndexMapT map_type;
            //! type of the array
            typedef mdarray<storage_type,map_type,InplaceArithmeticT> array_type;
            //! iterator type
            typedef typename storage_type::iterator iterator;
            //! const iterator type
            typedef typename storage_type::const_iterator const_iterator; 
            //! reverse iterator
            typedef typename storage_type::reverse_iterator reverse_iterator;
            //! const reverse iterator
            typedef typename storage_type::const_reverse_iterator
                const_reverse_iterator;
            //! inplace arithmetics type
            typedef InplaceArithmeticT inplace_arithmetic;
            //! view type
            typedef array_view<array_type> view_type;
            //! const view type
            typedef array_view<const array_type> const_view_type;
            //! type used for size
            typedef size_t size_type;

            
            //==================public members=================================
            //! type ID of the element type
            static constexpr type_id_t type_id = type_id_map<value_type>::type_id;
        private:
            //! instance of StorageT
            StorageT _data;
            //! Index map of the array
            IndexMapT _imap;
        public:

            //=================constructors and destructor=====================
            //! default constructor
            mdarray():_data(),_imap() {}

            //-----------------------------------------------------------------
            //!
            //! \brief construct from map and storage
            //!
            //! Construct an array from an index map and a storage. 
            //! \param map the index map instance
            //! \param s array storage
            //!
            explicit mdarray(const map_type &map,const storage_type &s):
                _data(s),
                _imap(map)
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief move construct from map and storage 
            //!  
            //! Move construct an array from rvalue refernces to an index 
            //! map and a storage. 
            //!
            //! \param map rvalue reference to the index map
            //! \param s rvalue reference to the storage
            //!
            explicit mdarray(map_type &&map,storage_type &&s):
                _data(std::move(s)),
                _imap(std::move(map))
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief constrcut from a view
            //!
            //! This constructor creates a new array from an array view 
            //! instance.  The resulting array object has the same shape as 
            //! the view. 
            //! 
            //! \tparam ArrayT storage type of the view
            //! \param view reference to the view
            //!
            template<typename ArrayT>
            explicit mdarray(const array_view<ArrayT> &view):
                _data(container_utils<storage_type>::create(view.size())),
                _imap(map_utils<map_type>::create(view.template shape<shape_t>()))
            {
                std::copy(view.begin(),view.end(),_data.begin());
            }


            //-----------------------------------------------------------------
            //!
            //! \brief construction from an other array
            //!
            //! This constructor can be used for instance along with 
            //! expression templates in order to construct an array from an 
            //! expression. 
            //! 
            //! \tparam MDArrayArgsT template parameters of mdarray
            //! \param array reference to the source array
            //!
            template<typename ...MDArrayArgsT>
            explicit mdarray(const mdarray<MDArrayArgsT...> &array):
                _data(container_utils<storage_type>::create(array.size())),
                _imap(map_utils<map_type>::create(array.template shape<shape_t>()))
            {
                //copy data
                for(size_t i=0;i<array.size();++i) (*this)[i] = array[i];
                //std::copy(array.begin(),array.end(),this->begin());
            }

            //====================static methods to create arrays==============
            //!
            //! \brief generic construction function
            //! 
            //! This function can be used for easy array construction. It uses 
            //! the array_factory template in the background. 
            //!
            //! \tparam ArrayArgsT variadic argument types
            //! \param arguments variadic argument list
            //! \return array instance
            //!
            template<typename ...ArrayArgsT>
            static array_type create(ArrayArgsT... arguments)
            {
                typedef array_factory<array_type> factory_type;

                return factory_type::create(std::forward<ArrayArgsT>(arguments)...);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief construction from initializer list
            //!
            //! This version of the static create function uses an initializer 
            //! list. The first initializer list holds shape information while
            //! the second holds the data which will be stored in the array.
            //!
            //! \tparam Element1T element type of shape list
            //! \tparam Element2T element type of data list
            //! \param l1 instance of shape list
            //! \param l2 instance of data list
            //! \return instance of array_type
            template<
                     typename Element1T,
                     typename Element2T
                    >
            static array_type create(const std::initializer_list<Element1T> &l1,
                                     const std::initializer_list<Element2T> &l2)
            {
                typedef array_factory<array_type> factory_type;

                return factory_type::create(l1,l2);
            }



            //====================assignment operations========================
            //!
            //! \brief assignment from a different array type
            //!
            //! Assign the data from a different array type to this one. 
            //! 
            //! \throws size_mismatch_error if array sizes do not match
            //! \throws shape_mismatch_error if shapes do not match
            //! \tparam MDArrayArgsT template parameters of the source type
            //! \param array reference to the source array
            //! \return reference to the updated array
            //!
            template<typename ...MDArrayArgsT>
            array_type &operator=(const mdarray<MDArrayArgsT...> &array)
            {
                if((void*)this == (void*)&array) return *this;
    
                size_t s = array.size();
                for(size_t i=0;i<s;++i) (*this)[i] = array[i];

                return *this;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief assignment from an initializer list
            //! 
            //! Assigns the values given by an initializer list to an allocated
            //! array. If the number of elements in the list does not match
            //! the number of elements in the array an exception is thrown. 
            //!
            //! \throws size_mismatch_error if list size and array size do not 
            //! match
            //! \param l reference to an initializer list
            //! \return reference to the array
            //!
            array_type &operator=(const std::initializer_list<value_type> &l)
            {
                if(l.size() != this->size())
                    throw size_mismatch_error(PNINEXUS_EXCEPTION_RECORD,
                            "Size of array and initializer list do not match");

                std::copy(l.begin(),l.end(),this->begin());
                return *this;
            }
            

            //================public methods===================================
            //! 
            //! \brief get index map
            //!
            //! Returns a const reference to the index map of the array.
            //! \return reference to index map
            //!
            const map_type &map() const { return this->_imap; }

            //----------------------------------------------------------------
            //! 
            //! \brief shape to container
            //! 
            //! This returns a container of type ContainerT with the number of
            //! elements stored in the array. 
            //! 
            //! \tparam ContainerT container type 
            //! \return instance of ContainerT with shape data
            //!
            template<typename ContainerT> ContainerT shape() const
            {
                auto c = container_utils<ContainerT>::create(_imap.rank());
                std::copy(_imap.begin(),_imap.end(),c.begin());
                return c;
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief get size of array
            //!
            //! Returns the total number of elements stored in the array.
            //! \return total number of elements
            //!
            size_t size() const 
            { 
                return _data.size(); 
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief get number of dimensions 
            //! 
            //! Returns the number of dimensions of the array. 
            //!
            //! \return number of dimensions
            //!
            size_t rank() const 
            { 
                return _imap.rank(); 
            }

            //=============operators and methods to access array data==========
            //!
            //! \brief get referece to element i
            //!
            //! Returns a reference to the element at linear index i. No index
            //! checking is done! Thus use this operator with care.
            //!
            //! \param i linear index 
            //! \return reference to the element at linear index i
            //!
            value_type& operator[](size_t i) 
            { 
#ifdef DEBUG
                return at(i);
#else
                return _data[i]; 
#endif
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief get value at i
            //!
            //! Returns the value of the element at the linar array index i. 
            //! No index checking is done! Thus use this operator with care.
            //! 
            //! \param i linear index of the element
            //! \return value of the element at linear index i
            //!
            value_type operator[](size_t i) const 
            { 
#ifdef DEBUG
                return at(i);
#else
                return _data[i]; 
#endif
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief get value at i
            //!
            //! Return a reference to the value at linear index i. This method
            //! performs index checking. 
            //!
            //! \throws index_error if i exceeds array size
            //! \param i linear index of element
            //! \return reference to the value at i
            //!
            value_type &at(size_t i) 
            { 
                try
                {
                    return _data.at(i); 
                }
                catch(std::out_of_range &)
                {
                    std::stringstream ss;
                    ss<<"Index "<<i<<" is out of range ("<<size()<<")!";
                    throw index_error(PNINEXUS_EXCEPTION_RECORD,ss.str());
                }
            
            } 

            //-----------------------------------------------------------------
            //! 
            //! \brief get value at i
            //!
            //! Return the value of element i. This method
            //! performs index checking. 
            //! \throws index_error if i exceeds array size
            //! \param i linear index of element
            //! \return value at i
            //! 
            value_type at(size_t i) const 
            { 
                try
                {
                    return _data.at(i); 
                }
                catch(std::out_of_range &)
                {
                    std::stringstream ss;
                    ss<<"Index "<<i<<" is out of range ("<<size()<<")!";
                    throw index_error(PNINEXUS_EXCEPTION_RECORD,ss.str());
                }
            
            } 

            //-----------------------------------------------------------------
            //!
            //! \brief insert value at index i
            //!
            //! Insert value at index i. 
            //! 
            //! \throws index_error if i exceeds the size of the array
            //! \param i linear index of the element
            //! \param value the value to store at index i
            //!
            void insert(size_t i,const value_type &value)
            {
                at(i)=value;
            }
            //-----------------------------------------------------------------
            //!
            //! \brief return element reference
            //!
            //! Returns the reference to a single elemnt of the array 
            //! determined by a multidimensional index of unsigned integers 
            //! stored in a container of type ContainerT. This method performs no 
            //! range checking. 
            //!
            //! \tparam ContainerT index container type
            //! \param index reference to index container
            //! \return reference to the element
            //!
            template<
                     typename ContainerT,
                     typename = typename enable_element_cont<ContainerT>::type
                    >
            value_type &operator()(const ContainerT &index)
            {
               return _data[_imap.offset(index)]; 
            }
            
            //-----------------------------------------------------------------
            //!
            //! \brief return element value
            //!
            //! Returns the value of a single elemnt of the array determined 
            //! by a multidimensional index of unsigned integers stored in a
            //! container of type ContainerT. This method performs no range 
            //! checking. 
            //!
            //! \tparam ContainerT index container type
            //! \param index reference to index container
            //! \return value of the element
            //!
            template<
                     typename ContainerT,
                     typename = typename enable_element_cont<ContainerT>::type
                    >
            value_type operator()(const ContainerT &index) const
            {
                return _data[_imap.offset(index)];
            }
            
            //-----------------------------------------------------------------
            //!
            //! \brief return array view
            //!
            //! Return a view on the array determined by a set of slices 
            //! stored in a container type ContainerT. 
            //!
            //! \tparam ContainerT slice container type
            //! \param slices reference to the container
            //! \return array_view instance
            //!
            template<
                     typename ContainerT,
                     typename = typename enable_view_cont<ContainerT>::type
                    >
            array_view<const array_type> 
            operator()(const ContainerT &slices) const
            {
                typedef array_view<const array_type> view_type;

                return view_type(*this,array_selection::create(slices));
                
            }

            //-----------------------------------------------------------------
            //!
            //! \brief return array view
            //!
            //! Return a view on the array determined by a set of slices 
            //! stored in a container type ContainerT. 
            //!
            //! \tparam ContainerT slice container type
            //! \param slices reference to the container
            //! \return array_view instance
            //!
            template<
                     typename ContainerT,
                     typename = typename enable_view_cont<ContainerT>::type
                    >
            array_view<array_type> 
            operator()(const ContainerT &slices)
            {
                typedef array_view<array_type> view_type;

                return view_type(*this, array_selection::create(slices));
                
            }

            //-----------------------------------------------------------------
            //!
            //! \brief multiindex access
            //!
            //! The () operator allows multindex access to the data stored in 
            //! the array. Like the [] operator it does not perform any checks 
            //! of index ranges and should thus be used with care. However, 
            //! due to the missign checks it is extremely fast. If index 
            //! checking is required have a look the corresponding at() 
            //! member function.
            //!
            //! \tparam IndicesT index types
            //! \param indexes list of index values
            //! \return reference to the value at the given index
            //!
            template<
                     typename... IndicesT,
                     typename = typename enable_valid_index<IndicesT...>::type
                    >
            typename view_type_trait<array_type,IndicesT...>::type 
            operator()(IndicesT... indexes)
            {
                typedef view_provider<array_type,is_view_index<IndicesT...>::value>
                    provider_type;
                return provider_type::get_reference(*this,_imap,indexes...);
            }


            //-----------------------------------------------------------------
            //!
            //! \brief multiindex access
            //!
            //! The () operator allows multindex access to the data stored 
            //! in the array. Like the [] operator it does not perform any 
            //! checks of index ranges and should thus be used with care. 
            //! However, due to the missign checks it is extremely fast. If 
            //! index checking is required have a look the corresponding at() 
            //! member function.
            //!
            //! \tparam IndicesT index types
            //! \param indexes list of index values
            //! \return value at the given index
            //!
            template<
                     typename... IndicesT,
                     typename = typename enable_valid_index<IndicesT...>::type
                    >
            typename view_type_trait<const array_type,IndicesT...>::const_type
            operator()(IndicesT ...indexes) const
            {
                typedef view_provider<array_type,is_view_index<IndicesT...>::value>
                    provider_type;
                return provider_type::get_value(*this,_imap,indexes...);
            }


            
            //-----------------------------------------------------------------
            //!
            //! \brief return const pointer 
            //! 
            //! Return a const pointer to the data stored in the array. 
            //!
            //! \return pointer to data
            //!
            const value_type *data() const
            {
                return _data.data();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief return  pointer 
            //! 
            //! Return a  pointer to the data stored in the array. 
            //!
            //! \return pointer to data
            //!
            value_type *data()
            {
                return _data.data();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief reference to first element
            //!
            //! Return a reference to the first element in the linear view of 
            //! the array.
            //! 
            //! \return reference to first element
            //!
            value_type &front() { return _data.front(); }

            //-----------------------------------------------------------------
            //!
            //! \brief value of first element
            //!
            //! Return the value of the first element in the linear view of 
            //! the array.
            //! 
            //! \return value of the first element
            //!
            value_type front() const { return _data.front(); }

            //-----------------------------------------------------------------
            //!
            //! \brief reference to last element
            //!
            //! Return a reference to the last element in the linear view of 
            //! the array.
            //! 
            //! \return reference to last element
            //!
            value_type &back() { return _data.back(); }

            //-----------------------------------------------------------------
            //!
            //! \brief value of last element
            //!
            //! Return the value of the last element in the linear view of 
            //! the array. 
            //! 
            //! \return value of last element
            //!
            value_type back() const { return _data.back(); }

            //-----------------------------------------------------------------
            //! 
            //! \brief iterator to first element
            //!
            //! Returns a non-const iterator to the first element in the array.
            //! \return iterator to first element
            //!
            iterator begin() { return _data.begin(); }

            //-----------------------------------------------------------------
            //! 
            //! \brief iterator to last element
            //!
            //! Returns a non-const iterator to the last element in the array. 
            //! 
            //! \return iterator to last element
            //!
            iterator end() { return _data.end(); }

            //-----------------------------------------------------------------
            //! 
            //! \brief const-iterator to first element
            //! 
            //! Returns a const-iterator to the first element in the array.
            //! \return iterator to first element
            //!
            const_iterator begin() const { return _data.begin(); }

            //-----------------------------------------------------------------
            //!
            //! \brief const-iterator to last element
            //!
            //! Returns a const-iterator to the last element in the array.
            //! 
            //! \return iterator to last element
            //!
            const_iterator end() const { return _data.end(); }

            //-----------------------------------------------------------------
            //! 
            //! \brief return reverse iterator to last element
            //! 
            reverse_iterator rbegin() { return _data.rbegin(); }

            //-----------------------------------------------------------------
            //!
            //! \brief return const reverse iterator to last element
            //! 
            const_reverse_iterator rbegin() const { return _data.rbegin(); }

            //-----------------------------------------------------------------
            //! 
            //! \brief return reverse iterator to 0-1 element
            //! 
            reverse_iterator rend() { return this->_data.rend(); }

            //-----------------------------------------------------------------
            //! 
            //! \brief return const reverse iterator to 0-1 element
            //! 
            const_reverse_iterator rend() const { return _data.rend(); }

            //==========implementation of unary arithmetic operators===========
            //!
            //! \brief unary addition of a scalar
            /*!
            \code
            array_type a = ...;
            array_type::value_type s = ...;
            
            a += s;
            \endcode
            !*/ 
            //! \param s the scalar value to add
            //! \return array reference
            //!
            array_type &operator+=(value_type s) 
            { 
                InplaceArithmeticT::add(*this,s); 
                return *this;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief unary addition of an array 
            /*!
            \code
            array_type1 a = ...;
            array_tyep2 b = ...;
            
            a += b;
            \endcode
            !*/
            //! \tparam ArrayT type of the array to add
            //! \param v reference to the array to add 
            //! \return reference to the original array
            //!
            template<typename ArrayT> 
            array_type &operator+=(const ArrayT &v) 
            { 
                InplaceArithmeticT::add(*this,v); 
                return *this;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief unary subtraction of a scalar
            /*!
            \code
            array_type a = ...;
            array_type::value_type s = ...;
            
            a -= s;
            \endcode
            !*/ 
            //! \param s the scalar value to subtract
            //! \return array reference
            //!
            array_type &operator-=(value_type s) 
            { 
                InplaceArithmeticT::sub(*this,s); 
                return *this;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief unary subtraction of an array
            /*!
            \code
            array_type1 a = ...;
            array_tyep2 b = ...;
            
            a -= b;
            \endcode
            !*/
            //! \tparam ArrayT type of the array to subtract
            //! \param v reference to the array to subtract 
            //! \return reference to the original array
            //!
            template<typename ArrayT> 
            array_type &operator-=(const ArrayT &v) 
            { 
                InplaceArithmeticT::sub(*this,v); 
                return *this; 
            }

            //-----------------------------------------------------------------
            //!
            //! \brief unary multiplication of a scalar
            /*!
            \code
            array_type a = ...;
            array_type::value_type s = ...;
            
            a *= s;
            \endcode
            !*/ 
            //! \param s the scalar value to multiply with
            //! \return array reference
            //!
            array_type &operator*=(value_type s) 
            { 
                InplaceArithmeticT::mult(*this,s); 
                return *this; 
            }

            //-----------------------------------------------------------------
            //!
            //! \brief unary multiplication of an array
            /*!
            \code
            array_type1 a = ...;
            array_tyep2 b = ...;
            
            a *= b;
            \endcode
            !*/
            //! \tparam ArrayT type of the array to multiply 
            //! \param v reference to the array to multiply 
            //! \return reference to the original array
            //!
            template<typename ArrayT>
            array_type &operator*=(const ArrayT &v) 
            { 
                InplaceArithmeticT::mult(*this,v); 
                return *this;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief unary division of a scalar
            /*!
            \code
            array_type a = ...;
            array_type::value_type s = ...;
            
            a /= s;
            \endcode
            !*/ 
            //! \param s the scalar value to divide by
            //! \return array reference
            //!
            array_type &operator/=(value_type s) 
            { 
                InplaceArithmeticT::div(*this,s); 
                return *this;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief unary division of an array
            /*!
            \code
            array_type1 a = ...;
            array_tyep2 b = ...;
            
            a /= b;
            \endcode
            !*/ 
            //! \tparam ArrayT type of the array to divide by  
            //! \param v reference to the array to divide by 
            //! \return reference to the original array
            //!
            template<typename ArrayT>
            array_type &operator/=(const ArrayT &v) 
            { 
                InplaceArithmeticT::div(*this,v); 
                return *this;
            }


    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief container trait mdarray
    //! 
    //! Specialization of the container_trait for mdarray.
    //!
    //! \tparam StorageT array storage type
    //! \tparam IndexMapT index map type
    //! \tparam InplaceArithmeticT inplace arithmetic type
    //! 
    template<
             typename StorageT,
             typename IndexMapT,
             typename InplaceArithmeticT
            >
    struct container_trait<mdarray<StorageT,IndexMapT,InplaceArithmeticT>>
    {
        //! mdarray provides random access
        static const bool is_random_access = true;
        //! mdarray is iterable
        static const bool is_iterable = true;
        //! whether or not an mdarray has contiguous memory depends on the
        //! underlying storage type
        static const bool is_contiguous =
            container_trait<StorageT>::is_contiguous;
        //! mdarray is a multidimensional container
        static const bool is_multidim = true;
    };

    //need a declaration for the static constexpr attribute
    template<typename StorageT,typename IndexMapT,typename InplaceArithmeticT>
    constexpr type_id_t mdarray<StorageT,IndexMapT,InplaceArithmeticT>::type_id;
    
    //=====================non-member operators================================

    //!
    //! \ingroup mdim_array_classes
    //! \brief output operator
    //! 
    //! Writes content of a DArray to an output stream. 
    //! \param o output stream
    //! \param a array to output
    //! \return output stream
    //!
    template<
             typename StorageT,
             typename IndexMapT,
             typename InplaceArithmeticT
            >
    std::ostream &operator<<(std::ostream &o,const mdarray<StorageT,IndexMapT,InplaceArithmeticT> &a)
    {
        for(auto iter = a.begin();iter!=a.end();++iter)
            o<<*iter<<" ";

        return o;
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_classes
    //! \brief input stream operator
    //!
    //! Read data from an input stream. 
    //! \param is input stream
    //! \param a array where to store the data
    //! \return reference to input stream
    //!
    template<
             typename StorageT,
             typename IndexMapT,
             typename InplaceArithmeticT
            >
    std::istream &operator>>(std::istream &is,mdarray<StorageT,IndexMapT,InplaceArithmeticT> &a)
    {
        for(auto iter=a.begin();iter!=a.end();++iter)
            is>>*iter;

        return is;
    }
   
    //-------------------------------------------------------------------------
    //! 
    //! \ingroup mdim_array_classes
    //! \brief equality comparison operator
    //! 
    //! Returns true if thwo arrays are equal. This is the case when all
    //! element stored in the arrays are equal. 
    //! 
    //! \param b1 array on the lhs of the comparison
    //! \param b2 array on the rhs of the comparison
    //! 
    //! \return true if all elements are equal, false otherwise
    //!
    template<
             typename StorageT,
             typename IndexMapT,
             typename InplaceArithmeticT
            >
    bool operator==(const mdarray<StorageT,IndexMapT,InplaceArithmeticT> &b1, 
                    const mdarray<StorageT,IndexMapT,InplaceArithmeticT> &b2) 
    {
        return std::equal(b1.begin(),b1.end(),b2.begin());
    }

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup mdim_array_classes
    //! \brief inequality comparison operator
    //! 
    //! Returns true if thwo arrays are not equal. 
    //! 
    //! \param b1 array on the lhs of the comparison
    //! \param b2 array on the rhs of the comparison
    //! 
    //! \return true if not equal, false otherwise
    //!
    template<
             typename StorageT,
             typename IndexMapT,
             typename InplaceArithmeticT
            >
    bool operator!=(const mdarray<StorageT,IndexMapT,InplaceArithmeticT> &b1, 
                    const mdarray<StorageT,IndexMapT,InplaceArithmeticT> &b2) 
    {
        return !(b1==b2);
    }

    
}
