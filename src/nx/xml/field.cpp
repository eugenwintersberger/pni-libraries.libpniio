//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Nov 27, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/core/error.hpp>
#include <pni/io/nx/xml/field.hpp>


namespace pni{
namespace io{
namespace nx{
namespace xml{


    //------------------------------------------------------------------------
    string field::unit(const node &field_node)
    {
        return string_attribute::read(field_node,"units");
    }

    //------------------------------------------------------------------------
    string field::long_name(const node &field_node)
    {
        return string_attribute::read(field_node,"long_name");
    }


//end of namespace
}
}
}
}
