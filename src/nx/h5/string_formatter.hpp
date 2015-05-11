//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: May 11, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <memory>

namespace pni{
namespace io{
namespace nx{
namespace h5{
   
    //!
    //! \ingroup hdf5_internal_classes
    //! \brief abstract string reader class
    //!
    //! This abstract class provides an interface for a string reader. 
    class string_formatter
    {
        public:
            virtual ~string_formatter();
            virtual pni::core::string operator()(const pni::core::string &input) const;
    };    

    typedef std::unique_ptr<string_formatter> formatter_ptr;
}
}
}
}
