//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//
// ============================================================================
//
//  Created on: Dec 29, 2014
//      Author: Eugen Wintersberger
//

#include <algorithm>
#include <pni/types/traits.hpp>
#include "utils.hpp"

namespace pni{
    

    static const type_id_vector numeric_ids =
        build_type_id_container<type_id_vector,numeric_types>();

    static const type_id_vector integer_ids = 
        build_type_id_container<type_id_vector,integer_types>();

    static const type_id_vector float_ids = 
        build_type_id_container<type_id_vector,float_types>();

    static const type_id_vector complex_ids = 
        build_type_id_container<type_id_vector,complex_types>();

    //------------------------------------------------------------------------
    bool contains_type_id(const type_id_vector &v,type_id_t &value)
    {
        auto result = std::find(v.begin(),v.end(),value);
        return result != v.end();
    }
   
    //------------------------------------------------------------------------
    bool is_numeric(type_id_t tid)
    {
        return contains_type_id(numeric_ids,tid);
    }

    //------------------------------------------------------------------------
    bool is_integer(type_id_t tid)
    {
        return contains_type_id(integer_ids,tid);
    }

    //------------------------------------------------------------------------
    bool is_complex(type_id_t tid)
    {
        return contains_type_id(complex_ids,tid);
    }

    //------------------------------------------------------------------------
    bool is_float(type_id_t tid)
    {
        return contains_type_id(float_ids,tid);
    }


//end of namespace
}
