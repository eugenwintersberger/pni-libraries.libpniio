//
// Declaration of types
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
// Declaration of types - the basic header file to use libpniio.
//
// Created on: Jul 1, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/io/nx/nxfile.hpp>
#include <pni/io/nx/nxgroup.hpp>
#include <pni/io/nx/nxfield.hpp>
#include <pni/io/nx/link.hpp>
#include <pni/io/nx/nxdeflate_filter.hpp>
#include <pni/io/nx/nxattribute.hpp>
#include <pni/io/nx/nximp_code.hpp>
#include <pni/io/nx/nximp_code_map.hpp>
#include <pni/io/nx/nxobject_traits.hpp>
#include <pni/io/nx/nxobject.hpp>

#include <pni/io/nx/h5/h5link.hpp>

namespace pni{
namespace io{
namespace nx{
namespace h5{
    //========need to define the implementation types==========================

    using nxfile   = pni::io::nx::nxfile<nximp_code::HDF5>;
    using nxgroup  = pni::io::nx::nxgroup<nximp_code::HDF5>;
    using nxfield  = pni::io::nx::nxfield<nximp_code::HDF5>;
    using nxfilter = pni::io::nx::nxfilter<nximp_map<nximp_code::HDF5>::filter_imp>;
    using nxdeflate_filter = pni::io::nx::nxdeflate_filter<nximp_map<nximp_code::HDF5>::deflate_imp>;
    using nxattribute =  pni::io::nx::nxattribute<nximp_code::HDF5>;
    using nxlink = pni::io::nx::nxlink<nximp_code::HDF5>;
    using nxobject    = pni::io::nx::nxobject<nxgroup,nxfield,nxattribute,nxlink>;
//end of namespace
}
}
}
}

namespace pni{
namespace io{
namespace nx{

    //!
    //! \brief object trait for the HDF5 implementation
    //! 
    template<> struct nxobject_trait<nximp_code::HDF5>
    {
        //! file type for the HDF5 implementation
        using file_type  = h5::nxfile;
        //! group type for the HDF5 implementation
        using group_type  = h5::nxgroup;
        //! field type for the HDF5 implementation 
        using field_type = h5::nxfield;
        //! attribute type for the HDF5 implementation
        using attribute_type =  h5::nxattribute;
        //! link type for the HDF5 implementation
        using link_imp_type =  h5::h5link;
        //! filter type for the HDF5 implementation
        using filter_type  =  h5::nxfilter;
        //! deflate filter type for the HDF5 implementation
        using deflate_type  =  h5::nxdeflate_filter;
        //! object type for the HDF5 implementation
        using object_type  =  h5::nxobject;

        using link_type = h5::nxlink;
    };

    NXIMPCODEMAPDECL(h5::nxfile,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::nxgroup,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::nxfield,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::nxattribute,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::nxlink,nximp_code::HDF5);



//need to setup the implementation code maps
}
}
}
  
