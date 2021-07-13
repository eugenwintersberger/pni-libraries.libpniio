//
// Declaration of template class TypeInfo
//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Dec 10, 2011
//      Author: Eugen Wintersberger
//
#pragma once

#include <pni/types/type_id_map.hpp>
#include <boost/static_assert.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <pni/error/exceptions.hpp>
#include <pni/error/exception_utils.hpp>
#include <pni/types/type_info.hpp>

#include <pni/windows.hpp>


namespace pni{
namespace core{
    
    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief check if two types are unchecked convertible
    //!
    //! Returns true if two types, determined by their type ID, are unchecked 
    //! convertible. 
    //!
    //! \param source_tid ID of the source type
    //! \param target_tid ID of the target type
    //! \return true if types are unchecked convertible, false otherwise
    //! 
    PNICORE_EXPORT 
	bool is_unchecked_convertible(type_id_t source_tid,type_id_t target_tid);

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief check if two types are checked convertible
    //!
    //! Returns true if two types, determined by their type ID, are checked 
    //! convertible. 
    //!
    //! \param source_tid ID of the source type
    //! \param target_tid ID of the target type
    //! \return true if types are checked convertible, false otherwise
    //! 
	PNICORE_EXPORT
    bool is_checked_convertible(type_id_t source_tid,type_id_t target_tid);

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief check if two types are unchecked convertible
    //!
    //! Returns true if two types, determined by their type ID, are 
    //! convertible. 
    //!
    //! \param source_tid ID of the source type
    //! \param target_tid ID of the target type
    //! \return true if types are , false otherwise
    //! 
	PNICORE_EXPORT
    bool is_convertible(type_id_t source_tid,type_id_t target_tid);


//end of namespace
}
}
