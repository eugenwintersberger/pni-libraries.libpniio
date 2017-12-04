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
//************************************************************************
//
// Created on: Jul 14, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/core/types.hpp>
#include <pni/core/error.hpp>
#include <pni/io/exceptions.hpp>

#include <pni/io/nx/h5/h5object_types.hpp>
#include <pni/io/nx/h5/object_imp.hpp>


namespace pni{
namespace io{
namespace nx{
namespace h5{
    using pni::io::invalid_object_error;
    using pni::core::type_error;

    //------------------------------------------------------------------------
    h5object_type get_hdf5_type(const object_imp &o)
    {
        if(!o.is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Invalid HDF5 object!");

        H5I_type_t tid = H5Iget_type(_id);
        switch(tid)
        {
            case H5I_FILE:      return h5object_type::FILE;
            case H5I_GROUP:     return h5object_type::GROUP;
            case H5I_DATASET:   return h5object_type::DATASET;
            case H5I_DATATYPE:  return h5object_type::DATATYPE;
            case H5I_DATASPACE: return h5object_type::DATASPACE;
            case H5I_ATTR:      return h5object_type::ATTRIBUTE;
            default: 
                throw type_error(EXCEPTION_RECORD,
                        "HDF5 object is of invalid type!");
        };
    }
    
    //------------------------------------------------------------------------
    pni::nx::nexus_type get_nexus_type(const object_imp &o)
    {
        if(get_hdf5_type(o) == h5object_type::GROUP) 
            return pni::io::nx::nxobject_type::NXGROUP;
        else if(get_hdf5_type(o) == h5_object_type::FILE)
            return pni::io::nx::nxobject_type::NXGROUP;
        else if(get_hdf5_type(o) == h5object_type::DATASET)
            return pni::io::nx::nxobject_type::NXFIELD;
        else
            throw type_error(EXCEPTION_RECORD,"Unkown Nexus type!");

    }

//end of namespace
}
}
}
}
