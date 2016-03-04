//!
//! (c) Copyright 2016 DESY,Eugen Wintersberger <eugen.wintersberger@gmail.com>
//!
//! This file is part of libpniio.
//!
//! libpniio is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! libpniio is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
//! 
//! ===========================================================================

#include <pni/io/nx/link.hpp>

namespace pni{
namespace io{
namespace nx{

    using namespace pni::core;
   
    link::link():
        _name{},
        _target{},
        _status{nxlink_status::INVALID},
        _type{nxlink_type::HARD}
    {}

    //------------------------------------------------------------------------
    link::link(const string &name,const nxpath &target,
               nxlink_status status,nxlink_type type):
        _name{name},
        _target{target},
        _status{status},
        _type{type}
    {}

    //------------------------------------------------------------------------
    string link::name() const noexcept 
    {
        return _name;
    }

    //------------------------------------------------------------------------
    nxpath link::target() const noexcept 
    {
        return _target;
    }

    //------------------------------------------------------------------------
    nxlink_status link::status() const noexcept
    {
        return _status;
    }

    //------------------------------------------------------------------------
    nxlink_type link::type() const noexcept
    {
        return _type;
    }


//end of namespace
}
}
}
