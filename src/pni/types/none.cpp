//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
// 
// ============================================================================
//
// Created on: Nov 4, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/types/none.hpp>

namespace pni{
namespace core{

    std::ostream &operator<<(std::ostream &stream,const none &)
    {
        return stream;
    }

    //------------------------------------------------------------------------
    std::istream &operator>>(std::istream &stream,none &)
    {
        return stream;
    }

    //------------------------------------------------------------------------
    bool operator==(const none &,const none &)
    {
        return true;
    }

    //------------------------------------------------------------------------
    bool operator!=(const none &a,const none &b)
    {
        return !(a==b);
    }

//end of namespace
}
}
