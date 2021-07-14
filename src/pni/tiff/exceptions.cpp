//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Sep 26, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//


#include <pni/tiff/exceptions.hpp>

namespace pni{
namespace tiff{

    //implementation of the output operator
    std::ostream &operator<<(std::ostream &o,const tiff_read_error &e)
    {
        return e.print(o);
    }

//end of namespace
}
}



