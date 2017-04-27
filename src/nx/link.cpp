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
   
    nxlink::nxlink():
        _link_path{},
        _target_path{},
        _status{nxlink_status::INVALID},
        _type{nxlink_type::HARD}
    {}

    //------------------------------------------------------------------------
    nxlink::nxlink(const nxpath &link_path,const nxpath &target_path,
               nxlink_status status,nxlink_type type):
        _link_path{link_path},
        _target_path{target_path},
        _status{status},
        _type{type}
    {}

    //------------------------------------------------------------------------
    string nxlink::name() const noexcept 
    {
        return _target_path.front().first;
    }

    //------------------------------------------------------------------------
    const nxpath &nxlink::link_path() const noexcept
    {
        return _target_path;
    }

    //------------------------------------------------------------------------
    const nxpath &nxlink::target_path() const noexcept 
    {
        return _target_path;
    }

    //------------------------------------------------------------------------
    nxlink_status nxlink::status() const noexcept
    {
        return _status;
    }

    //------------------------------------------------------------------------
    nxlink_type nxlink::type() const noexcept
    {
        return _type;
    }


//end of namespace
}
}
}
