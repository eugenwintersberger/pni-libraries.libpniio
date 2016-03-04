//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Mar 04, 2016
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include "nxpath.hpp"
#include "nxlink_type.hpp"

namespace pni{
namespace io{
namespace nx{

    class link
    {
        private:
            pni::core::string _name;
            nxpath _target;
            nxlink_status _status;
            nxlink_type _type;
        public:
            link();
            link(const pni::core::string &name,
                 const nxpath &target,
                 nxlink_status status, nxlink_type type);


            pni::core::string name() const noexcept;
            nxpath target() const noexcept ;
            nxlink_status status() const noexcept ;
            nxlink_type type() const noexcept ;

    };


//end of namespace
}
}
}
