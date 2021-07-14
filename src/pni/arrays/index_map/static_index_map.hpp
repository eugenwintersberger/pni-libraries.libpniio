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
// Created on: Oct 25, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once
#include <algorithm>
#include <numeric>
#include <pni/utilities/container_utils.hpp>

namespace pni{

#ifdef _MSC_VER

	template<typename CTYPE> class reverse_iterator
	{
		public:
			typedef typename CTYPE::value_type value_type;
			typedef reverse_iterator<CTYPE> iterator_type;
		private:
			const CTYPE *_container;
			ssize_t _state;
		public:
			//default constructor
			reverse_iterator() :
				_container(nullptr),
				_state(-1)
			{}

			//copy constructor - default implementation should be enough
			reverse_iterator(const reverse_iterator &i) = default;

			//initialize with container
			reverse_iterator(const CTYPE &c) :
				_container(&c),
				_state(_container->size() - 1)
			{}

			//copy assignment - the default implementation is good enough
			reverse_iterator &operator=(const reverse_iterator &i) = default;

			operator bool() const
			{
				return !((!_container) || (_state == -1) || (_state >= _container->size()));
			}

			value_type operator*() const
			{
				return (*_container)[_state];
			}

			value_type *operator->() const
			{
				return &(*this);
			}

			iterator_type &operator++()
			{
				_state--;
				return *this;
			}

			iterator_type operator++(int)
			{
				iterator_type temp = *this;
				++(*this);
				return temp;
			}

			iterator_type &operator--()
			{
				_state++;
				return *this;
			}

			iterator_type operator--(int)
			{
				iterator_type temp = *this;
				--(*this);
				return temp;
			}

			bool operator==(const iterator_type &i)
			{
				if (_container != i._container) return false;
				else if (_state != i._state) return false;
				return true;
			}

			bool operator!=(const iterator_type &i)
			{
				return !(*this == i);
			}

	};
	

	template<size_t N,size_t... DIMS>	class win_storage
	{
		public:
			typedef size_t value_type; 
			typedef const size_t *const_iterator;
			typedef win_storage<N, DIMS...> container_type;
			typedef reverse_iterator<container_type> const_reverse_iterator;
		private:
			constexpr static value_type _data[N] = { DIMS... };
		public:
			
			constexpr size_t size() const {	return N; }

			const_iterator begin() const { return _data; }

			size_t operator[](size_t index) const {	return _data[index]; }

			const_iterator end() const { return &_data[N]; }

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(*this);
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator();
			}
	};
#endif

    //!
    //! \ingroup index_mapping_classes
    //! \brief the static general index map template 
    //! 
    //! This is the basic static index map. In comparision to index_map its 
    //! number of elements along each dimensions as well as the number of 
    //! dimensions cannot be changed after the type has been defined. As all 
    //! data is static this type is rather efficient as everything resides 
    //! on the stack. Thus it is perfectly suited for small objects like 
    //! vectors and matrices. 
    //!
    //! To create an index map for a 3x3 matrix one could use something 
    //! like this
    /*!
    \code
    typedef static_index_map<c_index_map_imp,3,3> c_matrix_map;
    \endcode
    !*/
    //! This class has no special constructors as it is ready to use just be 
    //! using the default constructor. Unlike index_map this template 
    //! provides only const iterators (as its dimensions cannot be changed 
    //! once declared).
    //! 
    //! \tparam MAP_IMP policy to compute the index and offset data
    //! \tparam DIMS number of elements along each dimension
    //!
    template<
             typename MAP_IMP,
             size_t... DIMS
            > 
    class static_index_map
    {
        public:
            //=================public types====================================
            //! storage type
#ifdef _MSC_VER
			typedef win_storage<sizeof...(DIMS),DIMS...> storage_type;
#else
            typedef std::array<size_t,sizeof...(DIMS)> storage_type;
#endif
            //! policy type
            typedef MAP_IMP     implementation_type;
            //! index type 
            typedef storage_type index_type;
            //! constant iterator over the map
            typedef typename storage_type::const_iterator const_iterator;
        private:
            //! storage for shape information
#ifdef _MSC_VER
			static storage_type _shape;
#else
            constexpr static storage_type _shape = {{DIMS...}};
#endif
        public:

            //-----------------------------------------------------------------
            //!
            //! \brief get number of elements
            //! 
            //! Returns the total number of elements that can be addressed by 
            //! this map. This can be used to allocate some linear storage on 
            //! which the index map can work. 
            //!
            //! \return number of allocatable elements
            //! 
            size_t max_elements() const
            {
                return std::accumulate(_shape.begin(),_shape.end(),size_t(1),
                                       std::multiplies<size_t>()); 
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get number of dimensions
            //! 
            //! Returns the total number of dimensions currently manged by 
            //! this index map. 
            //! 
            //! \return number of dimensions
            //!
            constexpr size_t rank() const { return sizeof...(DIMS); }

            //-----------------------------------------------------------------
            //!
            //! \brief get number of elements
            //!
            //! This is just a synonym for rank(). 
            //! 
            //! \return the number of dimensions
            //!
            constexpr size_t size() const { return rank(); }


            //-----------------------------------------------------------------
            //!
            //! \brief compute the offset
            //! 
            //! This method is used in the case where the index is passed as 
            //! an rvalue reference. 
            /*! 
            \code
            typedef static_index_map<...> static_map;
            typedef std::vector<size_t>   index_t;
            static_map map;
             
            size_t offset = map.offset(index_t{1,2,3});
            
            //or alternatively 
            index_t index;
            ....
            offset = map.offset(std::move(index));
            \endcode
            !*/ 
            //! \tparam CTYPE container type for index data
            //! \param index instance of CTYPE with container data
            //! \return linear offset
            //!
            template<typename CTYPE,
                     typename = typename std::enable_if<
                     std::is_compound<
                     typename std::remove_const<
                     typename std::remove_reference<CTYPE>::type
                     >::type
                     >::value
                         >::type
                    > 
            size_t offset(const CTYPE &index) const
            {
                return implementation_type::template offset(_shape,index);
            }
            
            //-----------------------------------------------------------------
            //!
            //! \brief compute offset with selection
            //! 
            //! Compute the linear offset for an index with a selection. 
            //! \tparam CTYPE index container type
            //! \param s lvalue reference to the selection instance
            //! \param index lvalue reference to the index 
            //! \return linear offset
            template<typename CTYPE,
                     typename = typename std::enable_if<
                     std::is_compound<
                     typename std::remove_const<
                     typename std::remove_reference<CTYPE>::type 
                     >::type
                     >::value
                        >::type
                     >
            size_t offset(const array_selection &s,const CTYPE &index) 
            const
            {
                return implementation_type::template offset(s,_shape,index);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief compute index
            //!
            //! Compute the index that belongs to a particular linear offset. 
            //! The index can be stored in any STL compliant container type
            //! determined by the template parameter CTYPE. 
            /*! 
            \code
            typedef ... static_map;
            typedef std::vector<size_t> index_type;
              
            static_map map;
            auto index = map.index<index_type>(100);
            \endcode
            !*/
            //! \tparam CTYPE index container type
            //! \param offset linear offset
            //! \return CTYPE instance with index values
            //!
            template<typename CTYPE> CTYPE index(size_t offset) const
            {
                CTYPE index = container_utils<CTYPE>::create(rank()); 
                implementation_type::template index(_shape,index,offset);
                return index;
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief get a const iterator to the first element
            //! 
            const_iterator begin() const { return _shape.begin(); }

            //-----------------------------------------------------------------
            //! 
            //! \brief get a const iterator to the last+1 element
            //!
            const_iterator end() const { return _shape.end(); }

    };
    
#ifdef _MSC_VER
	template<typename MAP_IMP, size_t... DIMS>
	typename static_index_map<MAP_IMP, DIMS...>::storage_type
		static_index_map<MAP_IMP, DIMS...>::_shape;
#else
template<typename MAP_IMP,size_t... DIMS> 
    constexpr typename static_index_map<MAP_IMP,DIMS...>::storage_type 
    static_index_map<MAP_IMP,DIMS...>::_shape;

#endif
//end of namespace
}
