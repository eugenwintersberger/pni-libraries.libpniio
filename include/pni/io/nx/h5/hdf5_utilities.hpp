//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Aug 20, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

extern "C" { 
#include <hdf5.h>
}

#include <pni/core/types.hpp>

namespace pni{
namespace io{
namespace nx{
namespace h5{

    class object_imp;   
    
    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief get object filename
    //! 
    //! Returns the name of the file an HDF5 object belongs too. 
    //! This function works with the following objects
    //! \li an HDF5 dataset
    //! \li an HDF5 group
    //! \li or an HDF5 attribute
    //!
    //! \throw invalid_object_error if the object is not valid
    //! \throw io_error if object data cannot be retrieveda
    //! \throw object_error if validity check fails for some other reason
    //! \throw type_error if the passed object is of inappropriate type
    //!
    //! \param object HDF5 object
    //! \return string with the file name
    //!
    pni::core::string get_filename(const object_imp &object);
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief get object path
    //!
    //! Return the path of an HDF5 object as a string. This function works
    //! for the following HDF5 object types
    //! \li group
    //! \li dataset
    //!
    //! \throws object_error if object validity cannot be verified
    //! \throws invalid_object_error if the object is not valid
    //! \throws io_error in case of any IO related error.
    //! \throws type_error object is not a group or dataset
    //!
    //! \param object reference to the object from which to retrieve the path
    //! \return path as string
    //!
    pni::core::string get_path(const object_imp &object);

    //------------------------------------------------------------------------
    //! 
    //! \ingroup nxh5_classes
    //! \brief return object name
    //!
    //! Returns the name of an object. This function works for the following
    //! HDF5 types
    //! \li groups
    //! \li datasets
    //! \li attributes
    //!
    //! \throws object_error if validity check fails
    //! \throws invalid_object_error if obj is not valid
    //! \throws io_error in case of data retrieval issues
    //! \throws type_error if object type cannot be determined
    //!
    //! \param obj reference to the object from which to retrieve the name
    //! \return name of the object
    //!
    pni::core::string get_name(const object_imp &obj);

    //------------------------------------------------------------------------
    //! 
    //! \ingroup nxh5_classes
    //! \brief get parent path
    //! 
    //! Return the path to the parent of a particular object. Supported HDf5 
    //! types are
    //! \li groups
    //! \li datasets
    //! 
    //! \throws invalid_object_error if object is not valid
    //! \throws io_error  in case of errors
    //! \throws object_error if validity check fails
    //! \throws type_error if the object is of an inappropriate type
    //!
    //! \param object the HDF5 object from which to retrieve the parent path
    //! \return path to the parent
    //! 
    pni::core::string get_parent_path(const object_imp &object);
        
    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief return the parent object
    //!
    //! Returns the parent object. If the current object is  group or a field
    //! the returned object is always a group. In the case of an attribute the
    //! parent can be either a group or a field.
    //!
    //! \throws invalid_object_error if object not valid
    //! \throws object_error in case of any other error
    //! \throws type_error if the type of the object is unkown or could not be 
    //! determined
    //! \throws io_error in case of any IO related errors
    //!
    //! \param obj reference to the object from which to retrieve the parent
    //! \return object instance of the parent
    //!
    object_imp get_parent(const object_imp &obj);


//end of namespace
}
}
}
}
