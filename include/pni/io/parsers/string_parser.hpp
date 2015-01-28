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

#include "primitive_type_parser.hpp"

namespace pni{
namespace io{

    using namespace boost::spirit;
    using namespace pni;


    //------------------------------------------------------------------------
    template<typename ITERT>
    class parser<ITERT,core::string,true>
    {
        public:
            typedef core::string value_type;
            typedef ITERT        iterator_type;


            core::string parse(const string &data)
            {
                return data;
            }
    };


//end of namespace
}
}
