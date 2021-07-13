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
// Created on: Apr 14, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/types.hpp>

namespace pni{
namespace core{
    
    std::ostream &operator<<(std::ostream &stream,const bool_t &b)
    {
        if(b) stream<<"True";
        else stream<<"False";

        return stream;
    }

    std::istream &operator>>(std::istream &stream,bool_t &b)
    {
        string value;
        stream>>value;
        if(value == "True") b = true;
        else if(value == "False") b = false;

        return stream;
    }


//end of namespace
}
}
