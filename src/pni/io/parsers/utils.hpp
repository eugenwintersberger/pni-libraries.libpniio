//
// (c) Copyright 2017 DESY
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
// Created on: Jun 7, 2017
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <pni/core/types.hpp>

namespace pni {
namespace io {

    //!
    //! \ingroup parser_classes
    //! \brief check if input is an integer
    //!
    //! Checks if the input string could be interpreted as a single integer
    //! number. If this is the case the function returns true, false otherwise.
    //! The function assumes that the input string is trimmed, meaning that
    //! all leading and trailing white-space charachters have been removed.
    //!
    //! \param input input string to check
    //! \return true if integer, false otherwise
    bool is_integer(const pni::core::string &input);

    //!
    //! \ingroup parser_classes
    //! \brief check if input is a floating pointer number
    //!
    //! Checks if the input string could be interpreted as a single float
    //! number. If this is the case the function returns true, false otherwise.
    //! The function assumes that the input string is trimmed, meaning that
    //! all leading and trailing white-space charachters have been removed.
    //!
    //! \param input input string to check
    //! \return true if float, false otherwise
    bool is_float(const pni::core::string &input);

    //!
    //! \ingroup parser_classes
    //! \brief check if input is a boolean value
    //!
    //! Checks if the input string could be interpreted as a single boolean
    //! value. If this is the case the function returns true, false otherwise.
    //! The function assumes that the input string is trimmed, meaning that
    //! all leading and trailing white-space charachters have been removed.
    //!
    //! \param input input string to check
    //! \return true if boolean, false otherwise
    bool is_boolean(const pni::core::string &input);

    //!
    //! \ingroup parser_classes
    //! \brief check if input is a complex value
    //!
    //! Checks if the input string could be interpreted as a complex number.
    //! If this is the case the function returns true, false otherwise.
    //! The function assumes that the input string is trimmed, meaning that
    //! all leading and trailing white-space charachters have been removed.
    //!
    //! \param input input string to check
    //! \return true if complex, false otherwise
    bool is_complex(const pni::core::string &input);

    //!
    //! \ingroup parser_classes
    //! \brief check if input is a slice value
    //!
    //! Checks if the input string could be interpreted as a slice.
    //! If this is the case the function returns true, false otherwise.
    //! The function assumes that the input string is trimmed, meaning that
    //! all leading and trailing white-space charachters have been removed.
    //!
    //! \param input input string to check
    //! \return true if slice, false otherwise
    bool is_slice(const pni::core::string &input);
}
}
