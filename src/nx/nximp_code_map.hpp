/*
 * Declaration Nexus implementation type maps
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Definition of the implementation code map.
 *
 * Created on: Feb 11, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once
#include "nximp_code.hpp"

#include "h5/H5AttributeObject.hpp"
#include "h5/H5File.hpp"
#include "h5/H5Group.hpp"
#include "h5/H5Dataset.hpp"
#include "h5/H5Filter.hpp"
#include "h5/H5Attribute.hpp"

namespace pni{
namespace io{
namespace nx{
       
    /*! 
    \ingroup nexus_lowlevel
    \brief implementation code type map

    This type map maps a particular implementation type to a type code.
    */
    template<typename T> struct nximp_code_map
    {
            static const nximp_code icode; //!< implementation code
    };

#define NXIMPCODEMAPDECL(type,impcode)\
    template<> class nximp_code_map<type>\
    {\
        public:\
            static const nximp_code icode = impcode;\
    }

    //! \cond NO_API_DOC
    //specialization for the HDF5 Implementation
    NXIMPCODEMAPDECL(pni::io::nx::h5::H5AttributeObject,nximp_code::HDF5);
    NXIMPCODEMAPDECL(pni::io::nx::h5::H5File,nximp_code::HDF5);
    NXIMPCODEMAPDECL(pni::io::nx::h5::H5Group,nximp_code::HDF5);
    NXIMPCODEMAPDECL(pni::io::nx::h5::H5Dataset,nximp_code::HDF5);
    NXIMPCODEMAPDECL(pni::io::nx::h5::H5Filter,nximp_code::HDF5);
    NXIMPCODEMAPDECL(pni::io::nx::h5::H5Attribute,nximp_code::HDF5);
    //! \endcond

//end of namespace
}
}
}
