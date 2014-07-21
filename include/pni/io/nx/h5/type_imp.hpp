//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//
// Created on: Jul 17, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <vector>
#include <algorithm>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>

extern "C"{
#include <hdf5.h>
}

namespace pni{
namespace io{
namespace nx{
namespace h5{
   
    //!
    //! \ingroup nxh5_classes
    //! \brief provide implementation specific types
    //! 
    //! This struct provides types specific to the HDf5 implementation and some
    //! static conversion member functions which should be used by the frontend.
    //! 
    struct type_imp
    {
        //! index type
        typedef hsize_t index_type;

        //! container type for counters
        typedef std::vector<index_type> index_vector_type;

        //! container for selections
        typedef std::vector<pni::core::slice> selection_vector_type;

       
        //--------------------------------------------------------------------
        //! 
        //! \brief convert to index_vector_type
        //! 
        //! Conversion function taking an arbitrary container and converting 
        //! it to index_vector_type. This requires that the value_type of the 
        //! container is convertible to index_type.
        //! 
        //! \tparam CTYPE source container type
        //! \param container reference to the source container
        //! \return instance of index_vector_type
        //!
        template<typename CTYPE>
        static index_vector_type to_index_vector(const CTYPE &container)
        {
            index_vector_type v(container.size());
            std::copy(container.begin(),container.end(),v.begin());
            return v;
        }

        //--------------------------------------------------------------------
        //!
        //! \brief convert from index_vector_type
        //! 
        //! Conversion function taking an instance of index_vector_type and 
        //! converts it to CTYPE. It is required that index_type must be
        //! convertible to index_vector_type. 
        //! 
        //! \tparam CTYPE target container type
        //! \param v source index_vector_type instance
        //! \return instance of CTYPE
        //!
        template<typename CTYPE>
        static CTYPE from_index_vector(const index_vector_type &v)
        {
            CTYPE container(v.size());
            std::copy(v.begin(),v.end(),container.begin());
            return container;
        }

        //--------------------------------------------------------------------
        //!
        //! \brief convert to selection_vector_type
        //! 
        //! Takes an arbitrary container storing slices and converts it to a 
        //! selection_vector_type as required by this implementation. 
        //! A static assertion is used to check for the correct value type 
        //! of the user provided container.
        //! 
        //! \tparam CTYPE container type with slices
        //! \param container CTYPE instance with slices
        //! \return new instance of selection_vector_type
        //! 
        template<typename CTYPE>
        static selection_vector_type to_selection_vector(const CTYPE &container)
        {
            static_assert(std::is_same<typename CTYPE::value_type,
                                        slice>::value,
                         "Container must store values of slice!");

            selection_vector_type v(container.size());
            std::copy(container.begin(),container.end(),v.begin());
            return v;
        }

        //--------------------------------------------------------------------
        //!
        //! \brief convert selection to CTYPE
        //!
        //! Store the data from a selection_vector_type instance to a 
        //! container of type CTYPE whose value_type must be slice. 
        //! A static assertion is used to check the correctness of 
        //! CTYPE::value_type. 
        //! 
        //! \tparam CTYPE required container type 
        //! \param v reference to selection_vector_type 
        //! \return new instance of CTYPE
        //!
        template<typename CTYPE>
        static CTYPE from_selection_vector(const selection_vector_type &v)
        {
            static_assert(std::is_same<typename CTYPE::value_type,
                                       slice>::value,
                          "Container value type must be slice!");

            CTYPE container(v.size());
            std::copy(v.begin(),v.end(),container.begin());
            return container;
        }
        
    };

//end of namespace
}
}
}
}
