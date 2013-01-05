/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * H5Filter.cpp
 *
 *  Created on: Aug 9, 2011
 *      Author: Eugen Wintersberger
 */

#include <pni/core/Exceptions.hpp>


#include "H5Filter.hpp"

namespace pni {
namespace io {
namespace nx {
namespace h5 {

    //-------------------------------------------------------------------------
    H5Filter::H5Filter() { }

    //-------------------------------------------------------------------------
    H5Filter::H5Filter(const H5Filter &o) { }

    //-------------------------------------------------------------------------
    H5Filter::H5Filter(H5Filter &&o){ }

    //-------------------------------------------------------------------------
    H5Filter::~H5Filter() { }

    //-------------------------------------------------------------------------
    H5Filter &H5Filter::operator=(const H5Filter &o)
    {
        return *this;
    }

    //-------------------------------------------------------------------------
    H5Filter &H5Filter::operator=(H5Filter &&o)
    {
        return *this;
    }

//end of namespace
}
}
}
}
