/*
 * Declaration Nexus implementation type maps
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Definition of the implementation code map.
 *
 * Created on: Feb 11, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once
#include "NXImpCode.hpp"

#include "h5/H5AttributeObject.hpp"
#include "h5/H5File.hpp"
#include "h5/H5Group.hpp"
#include "h5/H5Dataset.hpp"
#include "h5/H5Filter.hpp"
#include "h5/H5Attribute.hpp"

namespace pni{
namespace nx{
       
    /*! 
    \ingroup nexus_lowlevel
    \brief implementation code type map

    This type map maps a particular implementation type to a type code.
    */
    template<typename T> class NXImpCodeMap
    {
        public:
            static const ImpCode icode; //!< implementation code
    };

#define NXIMPCODEMAPDECL(type,icode)\
    template<> class NXImpCodeMap<type>\
    {\
        public:\
            static const ImpCode icode = icode;\
    }

    //! \cond NO_API_DOC
    //specialization for the HDF5 Implementation
    NXIMPCODEMAPDECL(pni::nx::h5::H5AttributeObject,ImpCode::HDF5);
    NXIMPCODEMAPDECL(pni::nx::h5::H5File,ImpCode::HDF5);
    NXIMPCODEMAPDECL(pni::nx::h5::H5Group,ImpCode::HDF5);
    NXIMPCODEMAPDECL(pni::nx::h5::H5Dataset,ImpCode::HDF5);
    NXIMPCODEMAPDECL(pni::nx::h5::H5Filter);
    NXIMPCODEMAPDECL(pni::nx::h5::H5Attribute);
    //! \endcond

//end of namespace
}
}
