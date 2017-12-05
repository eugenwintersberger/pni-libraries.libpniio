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
// Created on: Feb 11, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once
#include <pni/io/nx/nximp_code.hpp>

namespace pni{
namespace io{
namespace nx{
       
    //! 
    //! \ingroup nexus_lowlevel
    //!\brief implementation code type map
    //!
    //! This type map maps a particular implementation type to a type code.
    //!
    template<typename T> struct nximp_code_map;
        /*
    {
            static const nximp_code icode; //!< implementation code
    };*/

#define NXIMPCODEMAPDECL(type,impcode)\
    template<> struct nximp_code_map<type>\
    {\
        static const nximp_code icode = impcode;\
    }

//end of namespace
}
}
}
