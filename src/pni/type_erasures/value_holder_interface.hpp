//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jan 11, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include <pni/types/types.hpp>

namespace pni{

    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief abstract interface for data holder
    //!
    //! Internal class defining the abstract interface for a data value 
    //! holder. 
    //!
    class value_holder_interface
    {
        public:
            //-----------------------------------------------------------------
            //!
            //! \brief get type id
            //!
            //! \return type ID of the stored value
            //! 
            virtual type_id_t type_id() const = 0;

            //-----------------------------------------------------------------
            //!
            //! \brief clone 
            //!
            //! Clone the actual holder object. 
            //! \return pointer to new holder instance 
            //!
            virtual value_holder_interface *clone() const = 0;

            //-----------------------------------------------------------------
            //!
            //! \brief check for reference
            //!
            //! \return true if a reference is stored, false otherwise
            //! 
            virtual bool holds_reference() const = 0;
    };

//end of namespace
}
