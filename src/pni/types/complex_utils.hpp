//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Sep 9, 2011
//     Author: Eugen Wintersberger
//
//

#pragma once

#include <pni/types/types.hpp>
#include <pni/windows.hpp>


namespace pni{

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief complex number equality operator
    //! 
    //! Comparison of 32- and 64-Bit complex numbers. The operator returns 
    //! true if real and imaginary part of the two numbers are equal.
    //! 
    //! \param a 32-Bit complex value
    //! \param b 64-Bit complex value
    //! \return true if equal.
    //!
    PNINEXUS_EXPORT bool operator==(const complex32 &a,const complex64 &b);
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief complex number equality operator
    //! 
    //! Comparison of 32- and 128-Bit complex numbers. The operator returns 
    //! true if real and imaginary part of the two numbers are equal.
    //! 
    //! \param a 32-Bit complex value
    //! \param b 128-Bit complex value
    //! \return true if equal.
    //!
    PNINEXUS_EXPORT bool operator==(const complex32 &a,const complex128 &b);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief complex number equality operator
    //! 
    //! Comparison of 64- and 32-Bit complex numbers. The operator returns 
    //! true if real and imaginary part of the two numbers are equal.
    //! 
    //! \param a 64-Bit complex value
    //! \param b 32-Bit complex value
    //! \return true if equal.
    //!
    PNINEXUS_EXPORT bool operator==(const complex64 &a,const complex32 &b);
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief complex number equality operator
    //! 
    //! Comparison of 64- and 128-Bit complex numbers. The operator returns 
    //! true if real and imaginary part of the two numbers are equal.
    //! 
    //! \param a 64-Bit complex value
    //! \param b 128-Bit complex value
    //! \return true if equal.
    //!
    PNINEXUS_EXPORT bool operator==(const complex64 &a,const complex128 &b);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief complex number equality operator
    //! 
    //! Comparison of 128- and 32-Bit complex numbers. The operator returns 
    //! true if real and imaginary part of the two numbers are equal.
    //! 
    //! \param a 128-Bit complex value
    //! \param b 32-Bit complex value
    //! \return true if equal.
    //!
    PNINEXUS_EXPORT bool operator==(const complex128 &a,const complex32 &b);
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief complex number equality operator
    //!
    //! Comparison of 128- and 64-Bit complex numbers. The operator returns 
    //! true if real and imaginary part of the two numbers are equal.
    //! 
    //! \param a 128-Bit complex value
    //! \param b 64-Bit complex value
    //! \return true if equal.
    //!
    PNINEXUS_EXPORT bool operator==(const complex128 &a,const complex64 &b);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief complex number inequality operator
    //! 
    //! Comparison of 32- and 64-Bit complex numbers. The operator returns 
    //! true if either real or imaginary part or both of the two numbers 
    //! differ.
    //!
    //! \param a 32-Bit complex value
    //! \param b 64-Bit complex value
    //! \return true if equal.
    //!
    PNINEXUS_EXPORT bool operator!=(const complex32 &a,const complex64 &b);
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief complex number inequality operator
    //!
    //! Comparison of 32- and 128-Bit complex numbers. The operator returns 
    //! true if either real or imaginary part or both of the two numbers 
    //! differ.
    //! 
    //! \param a 32-Bit complex value
    //! \param b 128-Bit complex value
    //! \return true if equal.
    //!
    PNINEXUS_EXPORT bool operator!=(const complex32 &a,const complex128 &b);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief complex number inequality operator
    //!
    //! Comparison of 64- and 32-Bit complex numbers. The operator returns 
    //! true if either real or imaginary part or both of the two numbers 
    //! differ.
    //!
    //! \param a 64-Bit complex value
    //! \param b 32-Bit complex value
    //! \return true if equal.
    //!
    PNINEXUS_EXPORT bool operator!=(const complex64 &a,const complex32 &b);
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief complex number inequality operator
    //!
    //! Comparison of 64- and 128-Bit complex numbers. The operator returns 
    //! true if either real or imaginary part or both of the two numbers 
    //! differ.
    //!
    //! \param a 64-Bit complex value
    //! \param b 128-Bit complex value
    //! \return true if equal.
    //!
    PNINEXUS_EXPORT bool operator!=(const complex64 &a,const complex128 &b);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief complex number inequality operator
    //! 
    //! Comparison of 128- and 32-Bit complex numbers. The operator returns 
    //! true if either real or imaginary part or both of the two numbers 
    //! differ.
    //!
    //! \param a 128-Bit complex value
    //! \param b 32-Bit complex value
    //! \return true if equal.
    //!
    PNINEXUS_EXPORT bool operator!=(const complex128 &a,const complex32 &b);
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief complex number inequality operator
    //!
    //! Comparison of 128- and 64-Bit complex numbers. The operator returns 
    //! true if either real or imaginary part or both of the two 
    //! numbers differ.
    //!
    //! \param a 128-Bit complex value
    //! \param b 64-Bit complex value
    //! \return true if equal.
    //!
    PNINEXUS_EXPORT bool operator!=(const complex128 &a,const complex64 &b);

//end of namespace
}
