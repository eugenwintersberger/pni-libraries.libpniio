//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// ===========================================================================
//
// Created on: Apr 11, 2014
//     Author: Eugen Wintersberger
//
//
#pragma once
#include <vector>
#include <array>
#include <list>


namespace pni{
namespace core{
   
    //!
    //! \ingroup type_classes
    //! \brief container trait
    //!
    //! This type trait collects some information about container types. It can
    //! be used for instance in the SFINAE pattern for overloading functions and 
    //! methods. 
    //! The information collected includes
    //!
    //! \li \c is_random_access - if true the container provides [] and at() to
    //! access data elements
    //! \li \c is_iterable - if true the container provides an iterator
    //! \li \c is_contiguous - the data is stored contiguous in memory (for such 
    //! containers it makes sense to provide a data() method to access this
    //! memory
    //! \li \c is_multidim - the contianer is multidimensional (basically this is 
    //! only the case for mdarray and array_view.
    //!
    //! If a user provides a new container type an overload for this trait
    //! be provided along with the implementation.
    //! 
    //! \tparam CTYPE container type 
    //!
    template<typename CTYPE> struct container_trait
    {
        //! by default false
        static const bool is_random_access = false;
        //! by default false
        static const bool is_iterable   = false;
        //! by default false
        static const bool is_contiguous = false;
        //! by default false
        static const bool is_multidim   = false;
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief container trait for std::vector
    //! 
    //! Specialization of the container_trait for std::vector. 
    //!
    //! \tparam ARGS all possible types passed to std::vector as template
    //! parameters
    //! 
    template<typename ...ARGS> struct container_trait<std::vector<ARGS...>>
    {
        //! std::vector provides random access
        static const bool is_random_access = true;
        //! std::vector is iterable
        static const bool is_iterable   = true;
        //! std::vector is contiguous
        static const bool is_contiguous = true;
        //! std::vector is linear and not multidimensional
        static const bool is_multidim   = false;
    };

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup type_classes
    //! \brief container trait for std::array
    //! 
    //! Specialization of container_trait for std::array
    //! 
    //! \tparam T data type of std::array
    //! \tparam N number of elements
    //! 
    template<
             typename T,
             size_t N
            >
    struct container_trait<std::array<T,N>>
    {
        //! std::array provides random access
        static const bool is_random_access = true;
        //! std::array is iterable
        static const bool is_iterable   = true;
        //! std::array is contiguous
        static const bool is_contiguous = true;
        //! std::array is not multidimensional
        static const bool is_multidim   = false;
    };

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup type_classes
    //! \brief container trait for std::list
    //! 
    //! Specialization of container_trait for std::list
    //! 
    //! \tparam ARGS types passed as template parameters to std::list
    //! 
    template<typename ...ARGS> struct container_trait<std::list<ARGS...>>
    {
        //! std::list does not provide random access
        static const bool is_random_access = false;
        //! std::list is iterable
        static const bool is_iterable   = true;
        //! std::list is not contiguous
        static const bool is_contiguous = false;
        //! std::list is not multidimensional
        static const bool is_multidim   = false;
    };




//end of namespace
}
}
