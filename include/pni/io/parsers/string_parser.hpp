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
// Created on: Jan 23, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//

#pragma once

#include "parser.hpp"

namespace pni{
namespace io{

    //------------------------------------------------------------------------
    //!
    //! \ingroup parser_internal_classes
    //! \brief string parser
    //! 
    //! This spcialization of the parser template is for string types. 
    //! 
    //! \param ITERT input iterator type
    //!
    template<typename ITERT>
    class parser<pni::core::string,ITERT>
    {
        public:
            //! the output type of the parser
            typedef pni::core::string value_type;
            //! the input iterator type
            typedef ITERT        iterator_type;

            //----------------------------------------------------------------
            //! 
            //! \brief parser a string
            //! 
            //! This function does virtually nothing elsen than just pass 
            //! the input argument through.
            //!
            //! \param data input string
            //! \return unchanged input string
            //! 
            pni::core::string operator()(const pni::core::string &data) const
            {
                return data;
            }
    };


//end of namespace
}
}
