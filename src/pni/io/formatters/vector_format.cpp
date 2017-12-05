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
// Created on: Sep 08, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//

#include <pni/io/formatters/vector_format.hpp>

namespace pni{
namespace io{

    using namespace pni::core;

    pni::core::string format(const pni::core::array &v,
                             const container_io_config &config)
    {
        using namespace pni::core;

        string output;
        if(config.start_symbol())
            output+=string(1,config.start_symbol());

        for(const auto &value: v)
            output+=format(value)+string(1,config.separator());

        if(config.stop_symbol())
            output[output.size()-1]=config.stop_symbol();
        else
            output = string(output.begin(),--output.end());

        return output;
    }
}
}
