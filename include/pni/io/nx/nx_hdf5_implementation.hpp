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

#include "nxfile.hpp"
#include "nxgroup.hpp"
#include "nxfield.hpp"
#include "nxdeflate_filter.hpp"
#include "nxattribute.hpp"
#include "nximp_code.hpp"
#include "nximp_code_map.hpp"
#include "nxobject_traits.hpp"
#include "nxobject.hpp"

#include "h5/h5link.hpp"

namespace pni{
namespace io{
namespace nx{
namespace h5{
    //========need to define the implementation types==========================

    typedef pni::io::nx::nxfile<nximp_code::HDF5>                 nxfile;
    typedef pni::io::nx::nxgroup<nximp_code::HDF5>               nxgroup;
    typedef pni::io::nx::nxfield<nximp_code::HDF5>             nxfield;
    typedef pni::io::nx::nxfilter<nximp_map<nximp_code::HDF5>::filter_imp>             nxfilter;
    typedef pni::io::nx::nxdeflate_filter<nximp_map<nximp_code::HDF5>::deflate_imp> nxdeflate_filter;
    typedef pni::io::nx::nxattribute<nximp_code::HDF5>  nxattribute;
    typedef pni::io::nx::nxobject<nxgroup,nxfield,nxattribute> nxobject;
//end of namespace
}
}
}
}

namespace pni{
namespace io{
namespace nx{

    template<> struct nxobject_trait<nximp_code::HDF5>
    {
        typedef h5::nxfile file_type;
        typedef h5::nxgroup group_type;
        typedef h5::nxfield field_type;
        typedef h5::nxattribute attribute_type;
        typedef h5::h5link link_type;
        typedef h5::nxfilter filter_type;
        typedef h5::nxdeflate_filter deflate_type;
        typedef h5::nxobject object_type;
    };

    NXIMPCODEMAPDECL(h5::nxfile,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::nxgroup,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::nxfield,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::nxattribute,nximp_code::HDF5);



//need to setup the implementation code maps
}
}
}
  
