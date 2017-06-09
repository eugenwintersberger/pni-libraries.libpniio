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
// Created on: Jun 10, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include "nxpath.hpp"
#include "insert.hpp"
#include "../../windows.hpp"
#include <utility>


namespace pni{
namespace io{
namespace nx{

//add here an additional namespace to avoid namespace polution from the boost
//spirit framework.
namespace parsers{

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxpath_internal_code
    //! \brief parser string to path
    //!
    //! Parse a string input and generate a path instance from it.
    //!
    //! \throws parser_error in case of a parser problem
    //!
    //! \param input string from which to construct the path
    //! \return nxpath instance
    //!
    PNIIO_EXPORT nxpath parse_path(const pni::core::string &input);

//end of parser namespace
}

//end of namespace
}
}
}
