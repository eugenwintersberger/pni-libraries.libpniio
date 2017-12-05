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

    //------------------------------------------------------------------------
    h5object_type get_hdf5_type(const object_imp &o)
    {
        using namespace pni::core;
        //we obviously cannot retrieve the HDF5 type from an invalid object
        if(!o.is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                                       "Invalid HDF5 object!");

        H5I_type_t tid = H5Iget_type(o.id());
        switch(tid)
        {
            case H5I_FILE:      return h5object_type::FILE;
            case H5I_GROUP:     return h5object_type::GROUP;
            case H5I_DATASET:   return h5object_type::DATASET;
            case H5I_DATATYPE:  return h5object_type::DATATYPE;
            case H5I_DATASPACE: return h5object_type::DATASPACE;
            case H5I_ATTR:      return h5object_type::ATTRIBUTE;
            case H5I_GENPROP_LST: return h5object_type::PLIST;
            default:
                throw type_error(EXCEPTION_RECORD,
                        "HDF5 object is of invalid type!");
        };
    }
    
    //------------------------------------------------------------------------
    pni::io::nx::nxobject_type get_nexus_type(const object_imp &o)
    {
        using namespace pni::core;
        //if the object is not valid get_hdf5_object_type will 
        //throw invalid_object_error - do not have to do this here
        if(get_hdf5_type(o) == h5object_type::GROUP) 
            return pni::io::nx::nxobject_type::NXGROUP;
        else if(get_hdf5_type(o) == h5object_type::FILE)
            return pni::io::nx::nxobject_type::NXFILE;
        else if(get_hdf5_type(o) == h5object_type::DATASET)
            return pni::io::nx::nxobject_type::NXFIELD;
        else if(get_hdf5_type(o) == h5object_type::ATTRIBUTE)
            return pni::io::nx::nxobject_type::NXATTRIBUTE;
        else
            throw type_error(EXCEPTION_RECORD,"Unkown Nexus type!");

    }

//end of namespace
}
}
}
}
