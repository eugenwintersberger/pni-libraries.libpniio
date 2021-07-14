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
// ===========================================================================
//
//  Created on: Dec 19, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/types/type_conversion.hpp>
#include <pni/types/unchecked_convertible.hpp>

#include <map>

#include "utils.hpp"

namespace pni{

    

    static const std::map<type_id_t,type_id_vector> conversion_map{
        generate_map_element<uint8,unchecked_type_vectors>(),
        generate_map_element<uint16,unchecked_type_vectors>(),
        generate_map_element<uint32,unchecked_type_vectors>(),
        generate_map_element<uint64,unchecked_type_vectors>(),
        generate_map_element<int8,unchecked_type_vectors>(),
        generate_map_element<int16,unchecked_type_vectors>(),
        generate_map_element<int32,unchecked_type_vectors>(),
        generate_map_element<int64,unchecked_type_vectors>(),
        generate_map_element<float32,unchecked_type_vectors>(),
        generate_map_element<float64,unchecked_type_vectors>(),
        generate_map_element<float128,unchecked_type_vectors>(),
        generate_map_element<complex32,unchecked_type_vectors>(),
        generate_map_element<complex64,unchecked_type_vectors>(),
        generate_map_element<complex128,unchecked_type_vectors>()
    };


    //------------------------------------------------------------------------
    bool is_unchecked_convertible(type_id_t source_tid,type_id_t target_tid)
    {
        type_id_vector types = conversion_map.at(source_tid);
        
        return std::count(types.begin(),types.end(),target_tid)!=0;
    }


//end of namespace
}

