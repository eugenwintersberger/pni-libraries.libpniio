//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 2, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>

#include "../nxobject_traits.hpp"
#include "get_parent.hpp"

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief get root 
    //!
    //! Return the root group of an object. This is quite usefull in cases 
    //! where an absolute path is used. 
    //!
    //! This function throws no exceptions.
    //!
    //! \tparam VTYPE variant type
    //! \param p reference to an instance of VTYPE
    //! \return an instance of nxobject with the root group
    //!
    template<typename OTYPE> 
    auto get_root(const OTYPE &p) -> decltype(get_parent(p))
    {
        //if the object is already the root group we can return immediately
        if(get_name(p)=="/") return p;

        decltype(get_parent(p)) root = p;
        do
            root = get_parent(root);
        while(get_name(root)!="/");

        return root;

    }

//end of namespace
}}}
