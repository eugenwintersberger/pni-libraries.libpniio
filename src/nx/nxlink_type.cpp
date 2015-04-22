//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Apr 23, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nx/nxlink_type.hpp>

namespace pni{
namespace io{
namespace nx{
    
    std::ostream &operator<<(std::ostream &stream,const nxlink_type &ltype)
    {
        switch(ltype)
        {
            case nxlink_type::HARD: return stream<<"hard link";
            case nxlink_type::SOFT: return stream<<"soft link";
            case nxlink_type::EXTERNAL: return stream<<"external link";
            default:
                return stream;
        }                
        
    }
 
// end of namespace
}
}
}
