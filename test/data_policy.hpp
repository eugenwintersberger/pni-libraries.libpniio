//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
#pragma once

#include <algorithm>
#include <vector>
#include <pni/types.hpp>
#include <pni/arrays.hpp>
#include "uniform_distribution.hpp"

//!
//! \brief data generator policy
//!
//! This policy class provides static template methods to create scalar and 
//! multidimensional random data. 
//! 
struct data_policy 
{
    
    virtual ~data_policy() {}

    //! 
    //! \brief create a multidimensional array
    //! 
    //! Create a multidimensional array of type T and shape s. The data 
    //! in the array is not initialized. 
    //! 
    //! \tparam T data type of the array elements
    //! \pararm s shape of the array
    //! \return instance of pni::core::dynamic_array<T> 
    //! 
    template<typename T> 
    static pni::core::dynamic_array<T> 
    create_array(const pni::core::shape_t &s) 
    {
        return pni::core::dynamic_array<T>::create(s);
    }

    //------------------------------------------------------------------------
    //!
    //! \brief create a multidimensional array with random data
    //! 
    //! Create a multidimensional array of type T and shape s, initialized 
    //! with uniform random data.
    //! 
    //! \tparam T data type of the array elements
    //! \param s shape of the array
    //! \return instance of pni::core::dynamic_array<T> with random data
    //! 
    template<typename T>
    static pni::core::dynamic_array<T> 
    create_random_array(const pni::core::shape_t &s)
    {
        auto a = create_array<T>(s);
        std::generate(a.begin(),a.end(),uniform_distribution<T>());
        return a;
    }

    //------------------------------------------------------------------------
    //!
    //! \brief create a random scalar
    //!
    //! Return a random scalar value. The random value is drawn from a uniform
    //! distribution.
    //!
    //! \tparam T data type for the value
    //! \return instance of T with a random value. 
    //!
    template<typename T>
    static T create_random_scalar() 
    {
        uniform_distribution<T> rand_dist;
        return rand_dist();
    }

    //------------------------------------------------------------------------
    //!
    //! \brief create a buffer 
    //!
    //! Create a buffer of size size. The data in the buffer is not 
    //! initialized. 
    //! 
    //! \tparam T data type of the buffer elements
    //! \param size the number of elements in the buffer
    //! \return instance of std::vector<T> of size size
    //! 
    template<typename T> 
    static std::vector<T> create_buffer(size_t size) 
    {
        return std::vector<T>(size);
    }

    //------------------------------------------------------------------------
    //!
    //! \brief create buffer with random data
    //!
    //! Create a buffer of size size and element type T initialized with 
    //! random data drawn from a uniform distribution. 
    //!
    //! \tparam  T data type of the buffer elements
    //! \param size number of elements in the buffer
    //! \return instance of std::vector<T> of size size with random data
    //!
    template<typename T> 
    static std::vector<T> create_random_buffer(size_t size) 
    {
        auto b = create_buffer<T>(size);
        std::generate(b.begin(),b.end(),uniform_distribution<T>());
        return b;
    }

};
