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
//
// Created on: Jul 22, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <iostream>

namespace pni{
namespace io{
namespace nx{
    
    //!
    //! \ingroup nexus_lowlevel
    //! \brief Nexus link type
    //! 
    //! This enumeration characterizes a particular type of a link. There are 
    //! three kinds of links possible
    //!
    //! \li hard links - this is the most common case. In most cases this 
    //! link is established when an object is first created
    //! \li soft links - a secondary link pointing to an object, created 
    //! after the original object has been set up
    //! \li external link - a link pointing to an object in an external 
    //! file
    //!
    //! Attributes to not have a link type. However, we define one to make 
    //! the interfaces more consistent. The link type ATTRIBUTE thus tells a 
    //! user that the object he is dealing with is an attribute attached to 
    //! an object.
    //!
    enum class nxlink_type { HARD,    //!< denotes a hard link
                             SOFT,    //!< denotes a soft link
                             EXTERNAL,//!< denotes an external link
                             ATTRIBUTE //!< returned by attributes
                           };
                           
    std::ostream &operator<<(std::ostream &stream,const nxlink_type &ltype);
//end of namespace
}
}
}
