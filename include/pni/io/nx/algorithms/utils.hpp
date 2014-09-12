//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Aug 20, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>

namespace pni{
namespace io{
namespace nx{

    using namespace pni::core;

    //forward declaration of path
    class nxpath;

    //!
    //! \ingroup algorithm_internal_code
    //! \brief get path
    //!
    //! This function does nothgin at all. It just returns a copy of the 
    //! path passed as an argument.
    //! 
    //! \param p reference to a path
    //! \return copy of the input path
    //!
    nxpath get_path(const nxpath &p) noexcept;

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get path 
    //! 
    //! Convert the input string to a path object.
    //!
    //! \throws parser_error if string parsing fails
    //!
    //! \param p string representation of a path
    //! \return path object generated from the input string
    //!
    nxpath get_path(const string &p);

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get attribute path
    //!
    //! Convert a string with an attribute name to an attribute path. This is 
    //! done by adding the prefix ".@" to the input string.
    //!
    //! \throws parser_error in case of any syntax errors
    //!
    //! \param p name of the attribute
    //!
    //! \return path referening to the attribute
    //!
    nxpath get_attribute_path(const string &p);

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get attribute path
    //! 
    //! This function does nothing it just passes through the input path. 
    //!
    //! \param p input path
    //! 
    //! \return unchanged input path
    //!
    nxpath get_attribute_path(const nxpath &p) noexcept;


//end of namespace
}
}
}
