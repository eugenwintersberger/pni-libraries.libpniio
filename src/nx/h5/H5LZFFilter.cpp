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
 * H5LZFFilter.cpp
 *
 *  Created on: Aug 10, 2011
 *      Author: Eugen Wintersberger
 */

#include <pni/io/nx/h5/H5LZFFilter.hpp>
extern "C"{
#include "filters/lzf_filter.h"
}

namespace pni {
namespace io {
namespace nx {
namespace h5 {

    //--------------------------------------------------------------------------
    H5LZFFilter::H5LZFFilter():H5Filter() { }

    //--------------------------------------------------------------------------
    H5LZFFilter::H5LZFFilter(const H5LZFFilter &o){ } 

    //--------------------------------------------------------------------------
    H5LZFFilter::~H5LZFFilter() { } 

    //--------------------------------------------------------------------------
    H5LZFFilter &H5LZFFilter::operator=(const H5LZFFilter &o)
    {
        if(this != &o){ }

        return *this;
    }

    //--------------------------------------------------------------------------
    void H5LZFFilter::setup(hid_t id) const
    {
        H5Pset_filter(id, H5PY_FILTER_LZF, H5Z_FLAG_OPTIONAL, 0, NULL);
    }

//end of namespace
}
}
}
}
