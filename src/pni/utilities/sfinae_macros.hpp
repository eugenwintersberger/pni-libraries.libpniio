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
// Created on: Nov 07, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <type_traits>
#include <pni/types/traits.hpp>
#include <pni/types/complex_utils.hpp>

namespace pni{

    //!
    //! \ingroup utility_classes 
    //! \brief alias to invoke a metafunction
    //!
    //! Metafunction to retrieve the result type of another metafunction. 
    //!
    //! \tparam T metafunction type
    //! 
    template<typename T> using invoke = typename T::type;

    //------------------------------------------------------------------------
    //!
    //! \ingroup utility_classes
    //! \brief or type
    //! 
    //! Performs logical or operation on two metafunctions which both provide a
    //! public value member. The result can be obtained from a new boolean 
    //! public member.
    //! 
    //! \tparam Operand1T LHS of logical or
    //! \tparam Operand2T RHS of logical or
    //!
    template<
             typename Operand1T,
             typename Operand2T
            > 
    struct or_t
    {
        //! result of the operation
        static const bool value = Operand1T::value || Operand2T::value;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup utility_classes
    //! \brief and type
    //! 
    //! Performs logical 'and' operation on two metafunction types both 
    //! providing a publich value member. The result of the operation 
    //! can be obtained from a new public member.
    //! 
    //! \tparam Operand1T LHS of logical and
    //! \tparam Operand2T RHS of logical and
    //! 
    template<
             typename Operand1T,
             typename Operand2T
            >
    struct and_t
    {
        //! result of the operation
        static const bool value = Operand1T::value && Operand2T::value;
    };

    //------------------------------------------------------------------------
    //! 
    //! \ingroup utility_classes
    //! \brief logical not
    //!
    //! Applies a logical not to the result of a metafunction.
    //! 
    //! \tparam T function type
    //!
    template<typename T> struct not_t
    {
        //! result of the operation
        static const bool value = !T::value;
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup utility_classes
    //! \brief shortcut for std::enable_if
    //! 
#ifdef _MSC_VER
    template<typename C> using enable_if = std::enable_if_t<C::value>;
#else
	template<typename C> using enable_if = invoke<std::enable_if<C::value>>;
#endif
    
    //------------------------------------------------------------------------
    //!
    //! \ingroup utility_classes
    //! \brief shortcut for std::is_pod
    //! 
    template<typename T> using is_pod = std::is_pod<T>;

    //------------------------------------------------------------------------
    //!
    //! \ingroup utility_classes
    //! \brief shortcut for std::is_pointer
    //!
    template<typename T> using is_ptr = std::is_pointer<T>;

    //------------------------------------------------------------------------
    //!
    //! \ingroup utiltiy_classes
    //! \brief shortcut for is_complex
    //!
    template<typename T> using is_cmplx = is_complex_type<T>;

//end of namespace
}
