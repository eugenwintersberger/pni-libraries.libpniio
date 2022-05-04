//!
//! (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of libpninexus.
//!
//! libpninexus is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! libpninexus is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
//! 
//! ===========================================================================
//! 
//! Created on: Oct 22, 2013
//!     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!

#pragma once
#include <algorithm>
#include <numeric>

#include <pni/utilities/container_utils.hpp>

namespace pni{

    class array_selection;

    //!
    //! \ingroup index_mapping_classes
    //! \brief dynamic general index map template 
    //! 
    //! Index maps provide all the data and functionality to vector of 
    //! multidimensional indexes onto a linear memory offset and vica verse.  
    //! The index map behaves like an STL container whose elements are the 
    //! number of elements along a particular dimension of a multidimensional 
    //! array. This shape information is stored in an internal linear storage. 
    //! An index map type requires two template parameters
    //!
    //! \li the storage container type 
    //! \li the implementation type
    //! 
    /*!
    \code
    typedef std::vector<size_t>  dyn_storage_type;
    typedef std::array<size_t,3> fix_storage_type;
    
    typedef index_map<dyn_storage_type,c_index_map_imp> dyn_index_map;
    typedef index_map<fix_storage_type,c_index_map_imp> fix_index_map; 
    
    //maps can be constructed from their storage type
    dyn_index_map dmap1(dstorage{3,4,2});
    fix_index_map smap1(fix_storage_type{{3,4,5}});
    \endcode
    !*/
    //!  
    //! This index map template should be used for index maps who are either
    //! entirely dynamic or which have a fixed number of dimensions but the 
    //! number of elements can be changed at runtime.  There is a special 
    //! type for index map which are entirly static (fixed number of 
    //! dimensions, fixed number of elements along each dimensions): 
    //! static_index_map.
    //!
    //! \tparam ShapeStoreT type storing the shape information
    //! \tparam MapImpT map implementation type
    //! \sa static_index_map
    //! \sa c_index_map_imp
    //! 
    template<
             typename ShapeStoreT,
             typename MapImpT
            > 
    class index_map
    {
        public:
            //=================public types====================================
            //! storage type
            typedef ShapeStoreT storage_type;
            //! index type
            typedef typename storage_type::value_type value_type;
            //! policy type
            typedef MapImpT     implementation_type;
            //! read write iterator
            typedef typename storage_type::iterator iterator;
            //! constant iterator over the map
            typedef typename storage_type::const_iterator const_iterator;
            //! map type
            typedef index_map<storage_type,implementation_type> map_type;
        private:
            //! storage for shape information
            storage_type _shape;
        public:
            //-----------------------------------------------------------------
            //! 
            //! \brief default constructor
            //! 
            index_map():_shape() {}

            //-----------------------------------------------------------------
            //!
            //! \brief copy constructor
            //! 
            //! \param m const reference to the original index map
            //!
            index_map(const map_type &m):_shape(m._shape) {}

            //-----------------------------------------------------------------
            //!
            //! \brief move constructor
            //!
            //! \param m rvalue reference to the original index map.
            //!
            index_map(map_type &&m):_shape(std::move(m._shape)) 
            {
                std::fill(m._shape.begin(),m._shape.end(),0); 
            }

            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! This constructor does copy construction from a storage type
            //! instance. This constructor would be called in the following
            //! situation
            /*!
            \code
            typedef std::vector<size_t> storage_type;
            typedef index_map<storage_type,c_index_map_imp> index_map;
            
            storage_type shape{3,3,2};
            index_map map(shape);
            \endcode
            !*/
            //! \param s instance of storage_type
            //!
            explicit index_map(const storage_type &s):_shape(s) {}

            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //! 
            //! Performs move construction from an rvalue reference to an 
            //! instance of storage_type. A typical application would be 
            //! like this
            /*!
            \code
            typedef std::vector<size_t> storage_type;
            typedef index_map<storage_type,c_index_map_imp> index_map;
            
            index_map map(storage_type{3,3,2});
            \endcode
            !*/
            //! \param s rvalue reference to storage_type
            //! 
            explicit index_map(storage_type &&s):_shape(std::move(s)) {}

            //-----------------------------------------------------------------
            //!
            //! \brief copy assignment operator
            //! 
            //! \param m const reference to the original map
            //! \return reference ot the new map
            //! 
            map_type &operator=(const map_type &m)
            {
                if(this == &m) return *this;
                _shape = m._shape;

                return *this;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief move assignment operator
            //! 
            //! \param m rvalue reference to the original index map
            //! \return reference to the new map
            //!
            map_type &operator=(map_type &&m)
            {
                if(this == &m) return *this;
                _shape = std::move(m._shape);
                std::fill(m._shape.begin(),m._shape.end(),0);

                return *this;
            }

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
                if(_shape.size() == 0) return 0;
                else
                    return std::accumulate(_shape.begin(),_shape.end(),1,
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
            size_t rank() const { return _shape.size(); }

            //----------------------------------------------------------------
            //!
            //! \brief get number of dimensions
            //!  
            //! This function is a synonym for rank() and returns the total 
            //! number of dimensions.
            //! 
            //! \return number of dimensions
            //! 
            size_t size() const { return rank(); }

            //-----------------------------------------------------------------
            //!
            //! \brief compute the offset
            //!
            //! This method is used in the case where the index is passed as 
            //! an lvalue reference. 
            /*!
            \code
            index_map map(...);
            size_t offset = map.offset(std::list<size_t>{3,2,1});
            \endcode
            !*/
            //! \tparam ContainerT container type for index data
            //! \param index instance of ContainerT with container data
            //! \return linear offset
            //! 
            template<
                     typename ContainerT,
                     typename = typename std::enable_if<
                     std::is_compound<
                     typename std::remove_reference<ContainerT>::type
                     >::value
                     >::type
                    >
            size_t offset(const ContainerT &index) const
            {
                return implementation_type::template offset(_shape,index);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief compute offset with selection
            //! 
            //! Compute the offset in the case of a selection. 
            //!
            /*!
            \code   
            typedef index_map<....> map_type;
            typedef ....            index_type;
              
            array_selection s(....);
            index_type index{...};
            size_t offset = map.offset(s,index);
            \endcode
            !*/
            //! \tparam ContainerT container type for the index
            //! \param s lvalue reference to the selection 
            //! \param index lvalue reference to the index 
            //! \return linear offset to the element
            //! 
            template<typename ContainerT,
                     typename = typename std::enable_if<
                     std::is_compound<
                     typename std::remove_reference<ContainerT>::type
                     >::value
                     >::type
                    >
            size_t offset(const array_selection &s,const ContainerT &index) const
            {
                return implementation_type::template offset(s,_shape,index);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief compute index
            //! 
            //! Return the index stored in a container determined by the user 
            //! as a template parameter.
            /*!
            \code
            typedef index_map<...> map_t;
            map_t map(...)
            auto index = map.index<shape_t>(3);
            \endcode
            !*/
            //! \tparam ContainerT container type for the index
            //! \param offset linear offset for which to compute the index
            //! \return instance of ContainerT with index values
            //! 
            template<typename ContainerT> ContainerT index(size_t offset) const
            {
                ContainerT index = container_utils<ContainerT>::create(rank()); 
                implementation_type::template index(_shape,index,offset);
                return index;

            }

            //-----------------------------------------------------------------
            //! 
            //! \brief return iterator to first element
            //! 
            iterator begin() { return _shape.begin(); }

            //-----------------------------------------------------------------
            //! 
            //! \brief return iterator to last+1 element
            //! 
            iterator end()   { return _shape.end(); }

            //-----------------------------------------------------------------
            //! 
            //! \brief return const iterator to first element
            //! 
            const_iterator begin() const { return _shape.begin(); }

            //-----------------------------------------------------------------
            //! 
            //! \brief return const iterator to last+1 element
            //! 
            const_iterator end() const { return _shape.end(); }

    };
//end of namespace
}
