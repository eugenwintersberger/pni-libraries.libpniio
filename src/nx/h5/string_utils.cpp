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

#include <pni/io/nx/h5/string_utils.hpp>


namespace pni{
namespace io{
namespace nx{
namespace h5{


    void copy_from_vector(const char_vector_type &vector,size_t nstrs,size_t strsize,
                          string *strings)
    {
        for(size_t i = 0;i<nstrs;++i)
            strings[i] = string(vector.data()+i*strsize,strsize);
    }

    void copy_from_vector(const char_ptr_vector_type &vector,string *strings)
    {
        std::copy_if(vector.begin(),vector.end(),strings,
                     [](const char *v) { return v!=nullptr; });
    }

//end of namespace
}
}
}
}
