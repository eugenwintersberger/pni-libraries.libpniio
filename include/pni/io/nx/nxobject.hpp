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
// Created on: Jun 28, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <boost/variant.hpp>
#include "link.hpp"

namespace pni{
namespace io{
namespace nx{
    
    //!
    //! \ingroup nexus_lowlevel
    //!
    //! nxobject is an alias to a boost::variant template which can hold an 
    //! instance of a group, a field, or an attribute. It can be thus 
    //! used as a general container for all kind of Nexus objects.
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            >
    using nxobject = boost::variant<GTYPE,FTYPE,ATYPE,pni::io::nx::nxlink>;

//end of namespace
}
}
}
