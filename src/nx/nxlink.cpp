//!
//! (c) Copyright 2015 Eugen Wintersberger <eugen.wintersberger@gmail.com>
//!
//! This file is part of <PROJECT>.
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

#include <pni/io/nx/nxlink.hpp>

namespace pni{
namespace io{
namespace nx{
    
    void __check_target_path(const nxpath &target)
    {
        for(auto e: target)
            if(e.first == "..")
                throw value_error(EXCEPTION_RECORD,
                        "Target path contains intermediate ..!");

    }

//end of namespace
}
}
}
