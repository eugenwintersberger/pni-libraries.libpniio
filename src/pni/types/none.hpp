//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Nov 4, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>

#include <pni/windows.hpp>

namespace pni{
namespace core{

    //!
    //! \ingroup type_classes
    //! \brief none type
    //!
    //! This type is used in situations where a type for initialization is
    //! required but not provided (or at the moment not available). 
    //! It thus denotes the absence of type information.
    //!
    struct PNICORE_EXPORT none {};

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief output stream for none
    //!
    //! Using the none type with the output stream operator has no effect
    //! and does not modify the stream. 
    //!
    //! \param stream reference the output stream
    //! \param n none instance
    //! \return reference to the output stream
    //!
    PNICORE_EXPORT std::ostream &operator<<(std::ostream &stream,const none &n);

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief input stream for none
    //!
    //! Using the none type with the input stream operator has no effect
    //! and does not modify the stream. 
    //!
    //! \param stream reference the input stream
    //! \param n none instance
    //! \return reference to the input stream
    //!
    PNICORE_EXPORT std::istream &operator>>(std::istream &stream,none &n);

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief equality operator for none
    //! 
    //! Two instance of none are always considered equal. 
    //! 
    //! \param a instance on the lhs of the operator
    //! \param b instance on the rhs of the operator
    //! \return always true
    //! 
    PNICORE_EXPORT bool operator==(const none &a,const none &b);

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief inquality operator for none
    //! 
    //! Two instances of none are always equal and thus this will always 
    //! return false. 
    //! 
    //! \param a instance on the lhs of the operator
    //! \param b instnace on the rhs of the operator
    //! \return always false
    //!
    PNICORE_EXPORT bool operator!=(const none &a,const none &b);

//end of namespace
}
}
