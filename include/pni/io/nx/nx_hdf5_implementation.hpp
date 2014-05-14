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

#include "nxobject.hpp"
#include "nxfile.hpp"
#include "nxgroup.hpp"
#include "nxfield.hpp"
#include "nxdeflate_filter.hpp"
#include "nxattribute.hpp"
#include "nximp_code.hpp"
#include "nximp_code_map.hpp"
#include "nxobject_traits.hpp"

#include "h5/h5link.hpp"
#include "h5/H5AttributeObject.hpp"
#include "h5/H5File.hpp"
#include "h5/H5Group.hpp"
#include "h5/H5Dataset.hpp"
#include "h5/H5Attribute.hpp"
#include "h5/H5LibrarySetup.hpp"
#include "h5/H5Filter.hpp"
#include "h5/H5DeflateFilter.hpp"

namespace pni{
namespace io{
namespace nx{
namespace h5{
    //========need to define the implementation types==========================

    typedef pni::io::nx::nxobject<H5AttributeObject>    nxobject;
    typedef pni::io::nx::nxfile<H5File>                 nxfile;
    typedef pni::io::nx::nxgroup<H5Group>               nxgroup;
    typedef pni::io::nx::nxfield<H5Dataset>             nxfield;
    typedef pni::io::nx::nxfilter<H5Filter>             nxfilter;
    typedef pni::io::nx::nxdeflate_filter<H5DeflateFilter> nxdeflate_filter;
    typedef pni::io::nx::nxattribute<H5Attribute>  nxattribute;
    typedef pni::io::nx::nxselection<nxfield> nxselection;
//end of namespace
}
}
}
}

namespace pni{
namespace io{
namespace nx{

    //-------------------------------------------------------------------------
    //map all relevant types belonging to the HDF5 implementation to the
    //appropriate implementation code
    //-------------------------------------------------------------------------
    NXIMPCODEMAPDECL(h5::H5AttributeObject,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::H5File,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::H5Group,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::H5Dataset,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::H5Filter,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::H5Attribute,nximp_code::HDF5);

    NXIMPCODEMAPDECL(h5::nxobject,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::nxfile,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::nxgroup,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::nxfield,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::nxdeflate_filter,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::nxattribute,nximp_code::HDF5);
    NXIMPCODEMAPDECL(h5::nxselection,nximp_code::HDF5);

    //declare the central type trait for the HDF5 implementation
    DECLARE_NXOBJECT_TRAITS(nximp_code::HDF5,h5::nxobject,h5::nxgroup,
                            h5::nxfile,h5::nxfield,h5::nxattribute,
                            h5::nxselection,h5::h5link,h5::nxdeflate_filter);

//need to setup the implementation code maps
}
}
}
  
