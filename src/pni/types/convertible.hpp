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
//  Created on: Dec 20, 2014
//      Author: Eugen Wintersberger
//
#pragma once

#include <pni/types/unchecked_convertible.hpp>
#include <pni/types/checked_convertible.hpp>

namespace pni{

    //!
    //! \ingroup type_classes
    //! \brief check if two types are convertible
    //!
    //! Use this template to check whether two types are convertible or not. 
    //! The types can be either checked or unchecked convertible. 
    //!
    //! \tparam SourceT source type
    //! \tparam TargetT target type
    //!
    template< 
             typename SourceT,
             typename TargetT
            >
    struct convertible
    {
        //! true if checked conversion is possible 
        static const bool checked = checked_convertible<SourceT,TargetT>::value;
        //! true if unchecked conversion is possible 
        static const bool unchecked = unchecked_convertible<SourceT,TargetT>::value;
        //! true if a conversion can be done at all
        static const bool value = checked || unchecked;
    };

//end of namespace
}
