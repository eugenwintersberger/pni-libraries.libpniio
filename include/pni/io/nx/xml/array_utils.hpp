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
// Created on: Nov 28, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/error.hpp>
#include <pni/core/type_erasures.hpp>

#include "node.hpp"
#include "io_object.hpp"

namespace pni{
namespace io{
namespace nx{
namespace xml{

    //!
    //! \ingroup xml_classes
    //! \brief generate an array 
    //!
    //! This function template generates an instance of an mdarray 
    //! from a data node and stores the data in this array. The data type
    //! is determined by the user and must match the data type stored in the 
    //! array. 
    //!
    //! 
    template<typename ATYPE> ATYPE make_array(const node &data)
    {
        typedef typename ATYPE::storage_type storage_type;
        shape_t      shape;

        //determine the shape of the array
        if(io_object::rank(data)==0)
            shape = shape_t{1};
        else
            shape = io_object::shape(data);
       
        //read the daata
        auto buffer = io_object::data_from_xml<storage_type>(data);

        return ATYPE::create(std::move(shape),std::move(buffer));
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief generate an array type erasure
    //! 
    //! This specialization of the make_array function template returns an 
    //! array type erasure. This function is particularly useful in situations
    //! where we only need to transfer data and the data type is of no further 
    //! importants. 
    //!
    template<> array make_array(const node &data);



//end of namespace
}
}
}
}
