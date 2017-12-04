//
// Declaration Nexus implementation type maps
//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 3, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include "nximp_code.hpp"

#include "h5/object_imp.hpp"
#include "h5/type_imp.hpp"
#include "h5/file_imp.hpp"
#include "h5/group_imp.hpp"
#include "h5/field_imp.hpp"
#include "h5/h5filter.hpp"
#include "h5/attribute_imp.hpp"
#include "h5/h5deflate_filter.hpp"

namespace pni{
namespace io{
namespace nx{

    //! 
    //! \ingroup nexus_lowlevel
    //! \brief implementation map
    //!
    //! For each backend a particular class must be provided to implement one 
    //! of the low level nexus objects.
    //!
    template<nximp_code c> struct nximp_map;

    //-------------------------------------------------------------------------
    //! \cond NO_API_DOC

    //set implementation types for the HDF5 implementation
    template<> struct nximp_map<nximp_code::HDF5>
    {
        typedef pni::io::nx::h5::type_imp         type_imp;
        typedef pni::io::nx::h5::object_imp       object_imp;
        typedef pni::io::nx::h5::file_imp         file_imp;
        typedef pni::io::nx::h5::group_imp        group_imp;
        typedef pni::io::nx::h5::field_imp        field_imp;
        typedef pni::io::nx::h5::h5filter         filter_imp;
        typedef pni::io::nx::h5::attribute_imp    attribute_imp;
        typedef pni::io::nx::h5::h5deflate_filter deflate_imp;
    };
    //! \endcond

}
}
}

