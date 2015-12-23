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
// Created on: Dec 23, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nx/h5/object_imp.hpp>
#include <pni/io/nx/h5/h5object_types.hpp>
#include <pni/io/nx/nxobject_type.hpp>
#include "h5_imp_test_utils.hpp"

namespace std{
    
    ostream &operator<<(ostream &stream,
                        const pni::io::nx::h5::object_imp &imp)
    {
        stream<<imp.id();
        return stream;
    }

    ostream &operator<<(ostream &stream,const 
                        pni::io::nx::nxobject_type &type)
    {
        using namespace pni::io::nx;
        switch(type)
        {
            case nxobject_type::NXFIELD:
                stream<<"NeXus field"; break;
            case nxobject_type::NXGROUP:
                stream<<"NeXus group"; break;
            case nxobject_type::NXFILE:
                stream<<"NeXus file"; break;
            case nxobject_type::NXATTRIBUTE:
                stream<<"NeXus attribute"; break;
            case nxobject_type::NXNONE:
                stream<<"Undefined NeXus object"; break;
            default:
                stream<<"Unkown type";
        }
        return stream;
    }

    ostream &operator<<(ostream &stream,
                        const pni::io::nx::h5::h5object_type &type)
    {
        using namespace pni::io::nx;
        switch(type)
        {
            case h5::h5object_type::FILE: 
                stream<<"HDF5 File"; break;
            case h5::h5object_type::GROUP: 
                stream<<"HDF5 group"; break;
            case h5::h5object_type::DATATYPE: 
                stream<<"HDF5 data type"; break;
            case h5::h5object_type::DATASPACE: 
                stream<<"HDF5 data space"; break;
            case h5::h5object_type::DATASET:
                stream<<"HDF5 dataset"; break;
            case h5::h5object_type::ATTRIBUTE:
                stream<<"HDF5 attribute"; break;
            case h5::h5object_type::PLIST:
                stream<<"HDF5 property list"; break;
            default:
                stream<<"unkown HDF5 object";
        }
        return stream;
    }
}
