//
// (c) Copyright 2017 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
// Created on: Nov 29, 2017
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <type_traits>
#include <vector>
#include <array>

#include <functional>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/count_if.hpp>
#include <boost/mpl/size.hpp>
#include <pni/arrays/slice.hpp>

namespace pni {
namespace core {

#define IDX_ARRAY(IT,i)\
    std::array<size_t,sizeof...(IT)>{{size_t(i)...}}

//!
//! \ingroup mdim_array_internal_classes
//! \brief check if an index type is a valid index type
//!
//! Index types are all integer types and slice.
//!
//! \tparam T type to check
//!
template<typename T>
struct is_index_type
{
	//! true if T is integer or a slice type, false otherwise
	static const bool value = std::is_integral<T>::value ||
			                  std::is_same<T,slice>::value;
};


//-------------------------------------------------------------------------
//!
//! \ingroup mdim_array_internal_classes
//! \brief check a set of types for index
//!
//! This template checks a range of types whether or not they are index
//! types. If all of the types are index types the member value is true.
//! Otherwise it is false.
//!
//! \tparam ITYPES variadic set of types to check
//!
template<typename ...ITYPES>
struct is_index_types
{
    //!
    //! \brief predicate type for count_if
    //!
    //! This internal type implements a predicate to be used in connection
    //! with count_if from MPL.
    //!
    //! \tparam T input type
    //!
    template<typename T>
    struct is_index_type_pred
    {
        //! result type
        typedef is_index_type<T> type;
    };

    //! load the _ placeholder from boost::mpl
    using _ = boost::mpl::placeholders::_;
    //! list of types passed by the user
    typedef typename boost::mpl::vector<ITYPES...> types;

    //! count all index types
    typedef boost::mpl::count_if<types,is_index_type_pred<_>> n_index_types;

    //! if the number of index types is equal to the number of types passed
    //! by the user, all passed types are valid index types
    static const bool value = n_index_types::value ==
        int(boost::mpl::size<types>::value);
};

//-------------------------------------------------------------------------
//!
//! \ingroup mdim_array_internal_classes
//! \brief check if valid index
//!
//! Checks if a list of variadic arguments are a valid view or element
//! index. This is the case if the arguments are either of an unsigned
//! integer type or instances of slice.
//!
//! \code
//! is_valid_index<size_t,size_t,slice>::value;  //would be true
//! is_valid_index<size_t,size_t,size_t>::value; //would be true
//! is_valid_index<slice,slice>::value;          //true either
//! is_valid_index<slice,string>::value;         //definitely false
//! \endcode
//!
//! \tparam ITYPES index types
//!
template<typename ...ITYPES>
struct is_valid_index
{
	//! result type of MPL exrepssion
	typedef typename boost::mpl::contains<
			typename boost::mpl::vector<ITYPES...>::type,slice>::type has_slice;
	//! result type of MPL expression
	typedef typename boost::mpl::contains<
			typename boost::mpl::vector<ITYPES...>::type,size_t>::type
			has_size_t;

	//! true if the types are valid index types
	static const bool value = has_slice::value || has_size_t::value;
};

//-------------------------------------------------------------------------
//!
//! \ingroup mdim_array_internal_classes
//! \brief checks for view index
//!
//! This type checks if the types passed by a variadic index represent a
//! view or a single data item. While for a single element index the
//! individual index values must all be of integer type
//! (typically size_t), a view index contains at least one instance of
//! slice.
//!
//! \code
//! is_view_index<size_t,size_t,size_t>::value; //this would be false
//! is_view_index<size_t,size_t,slice>::value;  //this would be true
//! \endcode
//!
//! \tparam ITYPES index types
//!
template<typename ...ITYPES>
struct is_view_index
{
    //! result type of MPL expression
    typedef typename boost::mpl::contains<
                               typename boost::mpl::vector<ITYPES...>::type,
                               slice
                              >::type type;

    //! true if ITYPES represent a view
    static const bool value = type::value;
};

//-------------------------------------------------------------------------
//!
//! \ingroup mdim_array_internal_classes
//! \brief check if view index
//!
//! This template checks if a container identifies a view. This is the
//! case if its value_type is slice.
//!
template<typename CTYPE> struct is_view_cont
{
    //! by default CTYPE is no view container
    static const bool value = false;
};

//-------------------------------------------------------------------------
//!
//! \ingroup mdim_array_internal_classes
//! \brief check if view index
//!
//! Specialization of the is_view_cont template for std::vector.
//!
//! \tparam T element type of the vector
//!
template<typename T> struct is_view_cont<std::vector<T>>
{
    //! true if T is a slice type, false otherwise
    static const bool value = std::is_same<T,slice>::value;
};

//------------------------------------------------------------------------
//!
//! \ingroup mdim_array_internal_classes
//! \brief check if view index
//!
//! Sepcialization of the is_view_cont tempalte for std::array.
//!
//! \tparam T element type of the array
//! \tparam N number of elements
//!
template<typename T,size_t N> struct is_view_cont<std::array<T,N>>
{
    //! true if T is a slice type, false otherwise
    static const bool value = std::is_same<T,slice>::value;
};

//!
//! \brief SFINA - use for element access
//!
template<typename CTYPE>
    using enable_element_cont = std::enable_if<!is_index_type<CTYPE>::value &&
                                               !is_view_cont<CTYPE>::value >;

//!
//! \brief SFINA - use for view access
//!
template<typename CTYPE>
    using enable_view_cont = std::enable_if<!is_index_type<CTYPE>::value &&
                                            is_view_cont<CTYPE>::value >;


} // namespace core
} // namespace pni
