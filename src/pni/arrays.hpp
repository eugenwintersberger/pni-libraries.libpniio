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
// Created on: Aug 5, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <vector>
#include <array>
#include <pni/arrays/mdarray.hpp>
#include <pni/arrays/array_view.hpp>
#include <pni/arrays/array_factory.hpp>
#include <pni/arrays/slice.hpp>
#include <pni/arrays/array_arithmetic.hpp>
#include <pni/arrays/index_iterator.hpp>
#include <boost/mpl/size_t.hpp>


namespace pni{

    //define here a new set of array templates using aliases
    //!
    //! \ingroup mdim_array_classes
    //! \brief a dynamic array template
    //!  
    //! This template creates a fully dynamic array type. Its rank as well as 
    //! its number of elements along each dimension (the shape) can be 
    //! created dynamically. Use this type if all decisions have to be made 
    //! at runtime. 
    //!
    //! \code
    //! typedef dynamic_array<float64> array_type; 
    //!
    //! array_type a = ...;
    //! \endcode
    //!
    //! \tparam T element type
    //!
    template<typename T> 
    using dynamic_array = mdarray<std::vector<T>,dynamic_cindex_map>;

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_classes
    //! \brief array template with fixed dimension 
    //!
    //! This array template fixes the number of dimensions for an array type 
    //! at compile time. It will be the appropriate type for most applications. 
    //! The following code defines an image type (we know that images have 
    //! always 2 dimensions): 
    //!
    //! \code
    //! typedef fixed_dim_array<uint32,2> image_type;
    //! \endcode
    //!
    //! \tparam T element data type
    //! \tparam D number of dimensions
    //!
    template<
             typename T,
             size_t   D
            >
    using fixed_dim_array = mdarray<std::vector<T>,fixed_dim_cindex_map<D>>;

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_classes
    //! \brief static array template 
    //!
    //! This template can be used for static array types. These are types where
    //! the number of dimensions as well as the total number of elements along 
    //! each dimension are known at compile time. A typical application would 
    //! be matrices and vectors for 3D operations. 
    //!
    //! \code
    //! typedef static_array<float64,3> vector_type;
    //! typedef static_array<float64,3,3> matrix_type; 
    //! typedef static_array<float64,6,6> elasticity_tensor;
    //! \endcode
    //! 
    //! Instances of such types usually reside on the stack which makes access 
    //! to their data elements extremely fast. 
    //! 
    //! \tparam T element data type
    //! \tparam NDimsT number of elements along each dimension
    //!
    template<
             typename  T,
             size_t... NDimsT>
    using static_array = mdarray<std::array<T,boost::mpl::times<
                                              boost::mpl::size_t<1>,
                                              boost::mpl::size_t<NDimsT>...
                                              >::value
                                           >,
                                 static_cindex_map<NDimsT...>
                                >;
   
//end of namespace
}
