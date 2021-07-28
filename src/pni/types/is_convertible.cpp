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
// Created on: Dec 22, 2014
//     Author: Eugen Wintersberger
//

#include <pni/types/type_conversion.hpp>

namespace pni{
    
    bool is_convertible(type_id_t source_tid,type_id_t target_tid)
    {
        return (is_checked_convertible(source_tid,target_tid)||
               is_unchecked_convertible(source_tid,target_tid));
    }
//end of namespace
}
