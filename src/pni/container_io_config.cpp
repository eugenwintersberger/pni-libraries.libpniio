//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// ImageInfo class implementation
//
// Created on: Apr 28, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//

#include <pni/container_io_config.hpp>

namespace pni{
namespace io{
       
    container_io_config::container_io_config():
        _start(),
        _stop(),
        _sep(' ')
    {}
    
    //-------------------------------------------------------------------------
    container_io_config::container_io_config(char start,char stop):
        _start(start),
        _stop(stop),
        _sep(' ')
    {}
    
    //-------------------------------------------------------------------------
    container_io_config::container_io_config(char sep):
        _start(),
        _stop(),
        _sep(sep)
    {}
    
    //-------------------------------------------------------------------------
    container_io_config::container_io_config(char start,char stop,char sep):
        _start(start),
        _stop(stop),
        _sep(sep)
    {}
    
    //-------------------------------------------------------------------------
    char container_io_config::separator() const
    {
        return _sep;
    }
    
    //-------------------------------------------------------------------------
    char container_io_config::start_symbol() const
    {
        return _start;
    }
    
    //-------------------------------------------------------------------------
    char container_io_config::stop_symbol() const
    {
        return _stop;
    }


//end of namespace
}
}
