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
// Created on: Jul 21, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <vector>

namespace pni{
namespace io{
namespace nx{
namespace h5{
    
    using namespace pni::core;
   
    //!
    //! \nxh5_classes
    //! \brief vector type for individual characters
    //!
    //! This type is mainly used for reading strings of static size from a field 
    //! or attribute. 
    //! 
    typedef std::vector<char> char_vector_type;

    //!
    //! \ingroup nxh5_classes
    //! \brief vector tyep for char pointers
    //!
    //! Mainly used for reading strings of variable length from a field or
    //! attribute.
    //! 
    typedef std::vector<char*> char_ptr_vector_type;

    typedef std::vector<const char*> char_const_ptr_vector_type;

    void copy_from_vector(const char_vector_type &vector,size_t nstrs,size_t strsize,
                          string *strings);

    void copy_from_vector(const char_ptr_vector_type &vector,string *strings);

}
}
}
}
