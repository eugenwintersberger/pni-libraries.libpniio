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
// Created on: Jul 21, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "string_utils.hpp"
#include <pni/core/error.hpp>


namespace pni{
namespace io{
namespace nx{
namespace h5{
    using namespace pni::core;

    //------------------------------------------------------------------------
    void copy_from_vector(const char_vector_type &vector,size_t nstrs,
                          size_t strsize,string *strings)
    {
        if(vector.size()!=nstrs*strsize)
            throw size_mismatch_error(EXCEPTION_RECORD,
                    "The vector size does not match the total number of "
                    "required characater!");

        for(size_t i = 0;i<nstrs;++i)
            strings[i] = string(vector.data()+i*strsize,strsize);
    }

    //------------------------------------------------------------------------
    void copy_from_vector(const char_ptr_vector_type &vector,
                          size_t nstrs,string *strings)
    {
        if(nstrs!=vector.size())
            throw size_mismatch_error(EXCEPTION_RECORD,
                    "Number of strings does not match vector size!");

        std::copy_if(vector.begin(),vector.end(),strings,
                     [](const char *v) { return v!=nullptr; });
    }

//end of namespace
}
}
}
}
