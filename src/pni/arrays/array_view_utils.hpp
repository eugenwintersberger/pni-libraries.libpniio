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
// Created on: Nov 20, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <vector>
#include <array>

#include <functional>
#include <pni/arrays/slice.hpp>
#include <pni/arrays/array_view.hpp>

namespace pni{
  
    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief view trait
    //!
    //! Depending on the index types the ()-operator of mdarray has to either 
    //! return an instance of array_view or a single value or a reference to 
    //! a particular element of the array. 
    //! This template provides the return types for view indexes or and 
    //! single element indexes.
    //! There are two specializations of this template available: one for 
    //! views and one for single elements. 
    //!
    //! \tparam ArrayT array type
    //! \tparam is_view true if the index represents a view, false otherwise
    //!
    template<
             typename ArrayT,
             bool is_view
            > 
    struct array_view_trait;

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief view trait for views 
    //!
    //! This is the specialization of array_view_trait provides the view 
    //! types in case that the indexes passed to the ()-operator represent 
    //! a view. 
    //!
    //! \tparam ArrayT array type
    //!
    template<typename ArrayT> 
    struct array_view_trait<ArrayT,true>    
    {
        //! non-const view type
        using type = array_view<ArrayT>;
        //! const view type
        using const_type = array_view<const ArrayT>;
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief trait for single elements 
    //!
    //! This is the specialization of array_view_trait for single element 
    //! access.
    //!
    template<typename ArrayT> 
    struct array_view_trait<ArrayT,false>
    {
        //! single element reference
        using type = typename ArrayT::value_type&;
        //! single element value 
        using const_type = typename ArrayT::value_type;

    };



    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \ingroup provides views 
    //!
    //! A limitation of variadic template expansion in gcc 4.7 makes this 
    //! template necessary. Its purpose is to provide static functions that 
    //! extract 
    //!
    template<
             typename RightT,
             bool is_view
            > 
    struct view_provider;

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief single value view_provider 
    //!
    //! Specialization of the view_provider template for single element 
    //! access.  This is the case when all indices passed to the () operator of
    //! original array are of an unsinged integer type.
    //!
    //! \tparam ArrayT array type
    //! 
    template<typename ArrayT> 
    struct view_provider<ArrayT,false>
    {
        //! reference type
        using ref_type = typename array_view_trait<ArrayT,false>::type;
        //! const type (value type)
        using type = typename array_view_trait<ArrayT,false>::const_type;
       
        //---------------------------------------------------------------------
        //!
        //! \brief get reference
        //!
        //! Return the reference to a single element. The function computes 
        //! the offset for a particular container by means of an index map. 
        //! This overload works with indexes passed as variadic arguments.
        //!
        //! \tparam ContainerT container type 
        //! \tparam MAP index map type
        //! \tparam IndicesT indices of the element
        //! \param c reference to the data container 
        //! \param map reference to the index map
        //! \param indexes index values
        //! \return reference to the single element
        //!
        template<
                 typename ContainerT,
                 typename MAP,
                 typename... IndicesT
                > 
        static ref_type get_reference(ContainerT &c,MAP &map,IndicesT ...indexes)
        {
            using array_type = std::array<size_t,sizeof...(IndicesT)>;
#ifdef DEBUG
            array_type buffer{{size_t(indexes)...}};
            check_indexes(buffer,map,EXCEPTION_RECORD);
#endif

            size_t offset = map.offset(array_type{{size_t(indexes)...}});
            return c[offset];
        }

        //---------------------------------------------------------------------
        //!
        //! \brief get value
        //!
        //! Return a single value from a container. The function computes 
        //! the linear offset. Here the indexes are passed as variadic
        //! arguments.
        //!
        //! \tparam ContainerT data container type
        //! \tparam MAP index map type
        //! \tparam IndicesT index types
        //! \param c reference to the data container
        //! \param map reference to the index map
        //! \param indexes index values as variadic arguments
        //! \return value of the referenced data element.
        //!
        template<
                 typename ContainerT,
                 typename MAP,
                 typename ...IndicesT
                >
        static type get_value(const ContainerT &c,MAP &map,IndicesT ...indexes)
        {
            using array_type = std::array<size_t,sizeof...(IndicesT)>;
#ifdef DEBUG
            array_type buffer{{size_t(indexes)...}};
            check_indexes(buffer,map,EXCEPTION_RECORD);
#endif

            size_t offset = map.offset(array_type{{size_t(indexes)...}});
            return c[offset];
        }

    };
  
    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief array view view_provider
    //!
    //! This overload of the view_provider template returns array_view
    //! instances. 
    //! 
    //! \tparam ArrayT array type
    //!
    template<typename ArrayT> 
    struct view_provider<ArrayT,true>
    {
        //! reference type
        using ref_type = typename array_view_trait<ArrayT,true>::type;
        //! const reference type
        using type = typename array_view_trait<ArrayT,true>::const_type;
       
        //---------------------------------------------------------------------
        //!
        //! \brief get view object
        //!
        //! Return a non-const view instance on the array. The indexes (slices) 
        //! determining the view are passed as variadic arguments. 
        //!
        //! \tparam ContainerT array type
        //! \tparam MAP index map type
        //! \tparam IndicesT index types
        //! \param c reference to the data container
        //! \param indexes variadic argument list
        //! \return array view on array
        //!
        template<
                 typename ContainerT,
                 typename MAP,
                 typename... IndicesT
                > 
        static ref_type get_reference(ContainerT &c,MAP &,IndicesT ...indexes)
        {
            using array_type = std::array<slice,sizeof...(IndicesT)>;

            return ref_type(c,array_selection::create(
                            array_type{{slice(indexes)...}}));
        }


        //---------------------------------------------------------------------
        //!
        //! \brief get const view
        //! 
        //! This overload returns a const view of an array. The indexes and
        //! slices are passed as variaidc templates to the function.
        //!
        //! \tparam ContainerT array type
        //! \tparam MAP index map type
        //! \tparam IndicesT index and slice types
        //! \param c reference to the data container
        //! \param indexes variadic argument list
        //! \return const array view
        //! 
        template<
                 typename ContainerT,
                 typename MAP,
                 typename ...IndicesT
                >
        static type get_value(const ContainerT &c,MAP &,IndicesT ...indexes)
        {
            using array_type = std::array<slice,sizeof...(IndicesT)>;

            return type(c,array_selection::create(
                        array_type{{slice(indexes)...}}));
        }

    };

template<typename ArrayT,
         typename ...IndicesT
        >
    using view_type_trait = array_view_trait<ArrayT,
                                       is_view_index<IndicesT...>::value>;

template<typename ...IndicesT>
    using enable_valid_index = std::enable_if<is_index_types<IndicesT...>::value>;
//end of namespace
}
