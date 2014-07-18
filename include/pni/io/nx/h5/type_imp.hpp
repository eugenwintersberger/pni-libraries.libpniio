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
    
    struct type_imp
    {
        //! index type
        typedef hsize_t index_type;

        //! container type for counters
        typedef std::vector<index_type> index_vector_type;

        //! container for selections
        typedef std::vector<pni::core::slice> selection_vector_type;

         

        template<typename CTYPE>
        static index_vector_type to_index_vector(const CTYPE &container)
        {
            index_vector_type v(container.size());
            std::copy(container.begin(),container.end(),v.begin());
            return v;
        }

        template<typename CTYPE>
        static CTYPE from_index_vector(const index_vector_type &v)
        {
            CTYPE container(v.size());
            std::copy(v.begin(),v.end(),container.begin());
            return container;
        }

        template<typename CTYPE>
        static selection_vector_type to_selection_vector(const CTYPE &container)
        {
            selection_vector_type v(container.size());
            std::copy(container.begin(),container.end(),v.begin());
            return v;
        }

        template<typename CTYPE>
        static CTYPE from_selection_vector(const selection_vector_type &v)
        {
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
