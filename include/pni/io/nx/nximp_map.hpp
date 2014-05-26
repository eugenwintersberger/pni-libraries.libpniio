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

#include "h5/H5AttributeObject.hpp"
#include "h5/H5File.hpp"
#include "h5/H5Group.hpp"
#include "h5/H5Dataset.hpp"
#include "h5/H5Filter.hpp"
#include "h5/H5Attribute.hpp"
#include "h5/H5DeflateFilter.hpp"

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
        typedef pni::io::nx::h5::H5AttributeObject  object_imp;
        typedef pni::io::nx::h5::H5File             file_imp;
        typedef pni::io::nx::h5::H5Group            group_imp;
        typedef pni::io::nx::h5::H5Dataset          field_imp;
        typedef pni::io::nx::h5::H5Filter           filter_imp;
        typedef pni::io::nx::h5::H5Attribute        attribute_imp;
        typedef pni::io::nx::h5::H5DeflateFilter    deflate_imp;
    };
    //! \endcond

}
}
}

