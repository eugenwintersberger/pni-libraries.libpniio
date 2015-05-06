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
// Created on: Jul 4, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include "get_parent.hpp"

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief get root 
    //!
    //! Return the root group of an object. 
    //!
    //! \throws invalid_object_error if the object is not valid
    //! \throws type_error if the implementation does not support this operation
    //! \throws io_error in the case that name retrieval fails
    //! \throws object_error in case of any other error
    //!
    //! \tparam OTYPE object type
    //! \param p reference an instance of OTYPE
    //! \return an instance of nxobject with the root group
    //!
    template<typename OTYPE> 
    auto get_root(const OTYPE &p) -> decltype(get_parent(p))
    {
        decltype(get_parent(p)) root = p;
        do
            root = get_parent(root);
        while(get_name(root)!="/");

        return root;

    }

//end of namespace
}}}
