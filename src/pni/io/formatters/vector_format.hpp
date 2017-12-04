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
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/type_erasures.hpp>
#include <vector>
#include <pni/io/container_io_config.hpp>
#include <pni/io/windows.hpp>
#include <pni/io/formatters/scalar_format.hpp>


namespace pni{
namespace io{

    template<typename T>
    pni::core::string format(const std::vector<T> &v,
                             const container_io_config &config=container_io_config())
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

    //-------------------------------------------------------------------------
    //!
    //! \ingroup formatter_internal_classes
    //! \brief formatter for mdarray instances
    //!
    //! Specialization of the formatter template for instances of the mdarray
    //! template.
    //!
    //! \tparam OTYPES template parameters for mdarray
    //!
    template<typename ...OTYPES>
    pni::core::string format(const pni::core::mdarray<OTYPES...> &v,
                             const container_io_config &config=container_io_config())
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

    pni::core::string PNIIO_EXPORT format(const pni::core::array &v,
                             const container_io_config &config=container_io_config());

}
}
