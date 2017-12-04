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
// Created on: May 11, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "../../pni/io/nx/h5/string_formatter_factory.hpp"

#include <pni/core/error.hpp>
#include "string_utils.hpp"

#include "../../pni/io/nx/h5/charpad_formatter.hpp"
#include "../../pni/io/nx/h5/nullterm_formatter.hpp"
#include "../../pni/io/nx/h5/string_utils.hpp"

namespace pni{
namespace io{
namespace nx{
namespace h5{
    
    using namespace pni::core;
   
    formatter_ptr string_formatter_factory::create(const h5datatype &type)
    {
        if(!is_string_type(type))
            throw type_error(EXCEPTION_RECORD,
                "Cannot create a formatter for a non-string type!");
                
        if(is_vl_string(type))
            return formatter_ptr(new string_formatter());
        else if(is_static_string(type))
        {
            if(is_nullpad_str(type))
                return formatter_ptr(new charpad_formatter('0'));
            else if(is_spacepad_str(type))
                return formatter_ptr(new charpad_formatter(' '));
            else if(is_nullterm_str(type))
                return formatter_ptr(new nullterm_formatter());
        }
        
        throw type_error(EXCEPTION_RECORD,
            "Cannot create formatter for this particular string type!");
        
    }

    
}
}
}
}
