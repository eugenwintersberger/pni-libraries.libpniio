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

#pragma once

#include "../nxobject_type.hpp"

namespace pni{
namespace io{
namespace nx{
namespace h5{
   
    //forward declaration
    class object_imp;

    //!
    //! \ingroup nxh5_classes 
    //! \brief HDF5 object type enumerations
    //!
    //! This enumeration class defines type-codes for different kinds
    //! of HDF5 objects. As all HDF5 objects are derived from H5Object
    //! an thus can be convereted into such an object we need this
    //! codes to identify the particular object type of an 
    //! instance of H5Object.
    enum class h5object_type {FILE,       //!< HDF5 file code
                              GROUP,      //!< HDF5 group code
                              DATATYPE,   //!< HDF5 datatype code
                              DATASPACE,  //!< HDF5 dataspace code
                              DATASET,    //!< HDF5 dataset code
                              ATTRIBUTE,  //!< HDF5 attribute
                              PLIST,      //!< HDF5 property list
                              BADID       //!< unknown object
                            };

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief return HDF5 type
    //! 
    //! Returns the HDF5 type of an instance of h5object. Currently this can 
    //! be 
    //! \li an HDF5 file
    //! \li an HDF5 group
    //! \li an HDF5 dataspace
    //! \li an HDF5 dataset
    //! \li an HDF5 attribute
    //! \li an HDF5 property list
    //!
    //! An exception is thrown in case of an unknown type.
    //!
    //! \throws type_error in case of an unkown object type
    //! \throws invalid_object_error if the object is not valid
    //!
    //! \param o reference to h5object
    //! \return HDF5 object type
    //! 
    h5object_type get_hdf5_type(const object_imp &o);

    //------------------------------------------------------------------------
    //! 
    //! \ingroup hdf5_classes
    //! \brief return Nexus type
    //! 
    //! Return the Nexus type of an instance of h5object. This can be either a
    //! \li Nexus group
    //! \li Nexus field
    //! \li Nexus attribute
    //! \li Nexus file
    //!
    //! An exception is thrown if the type is unkown. 
    //! \throws type_error in the case of an unkown object type
    //! \throws invalid_object_error if the object is not valid
    //! \param o reference to h5object instance
    //! \return Nexus type
    //!
    pni::io::nx::nxobject_type get_nexus_type(const object_imp &o);


//end of namespace
}
}
}
}

