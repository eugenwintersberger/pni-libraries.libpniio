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
 * H5LibrarySetup.cpp
 *
 *  Created on: Aug 4, 2011
 *      Author: Eugen Wintersberger
 */

#include "H5LibrarySetup.hpp"

#include "filters/lzf_filter.h"

namespace pni {
namespace io {
namespace nx {
namespace h5 {

    //-------------------------------------------------------------------------
    H5LibrarySetup::H5LibrarySetup() 
    {
        H5open();
        H5Eset_auto2(H5E_DEFAULT,0,NULL);
        H5get_libversion(&_major_version_number,&_minor_version_number,
                         &_release_number);

        //register custom filters to the library
        register_lzf();
    }

    //--------------------------------------------------------------------------
    H5LibrarySetup::~H5LibrarySetup() 
    {
        H5garbage_collect();
        H5close();
    }

    //--------------------------------------------------------------------------
    string H5LibrarySetup::version_string() const
    {
        string vstr;
        return vstr;
    }

    //--------------------------------------------------------------------------
    uint32 H5LibrarySetup::major_number() const
    {
        return _major_version_number;
    }

    //--------------------------------------------------------------------------
    uint32 H5LibrarySetup::minor_number() const
    {
        return _minor_version_number;
    }

    //--------------------------------------------------------------------------
    uint32 H5LibrarySetup::release_number() const
    {
        return _release_number;
    }

//end of namespace
}
}
}
}
