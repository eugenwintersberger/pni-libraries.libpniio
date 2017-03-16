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
// ==========================================================================
//
// Created on: Jul 15, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once
#include <vector>

#include <pni/core/types.hpp>
#include "../../windows.hpp"

namespace pni{
namespace io{
namespace nx{
namespace h5{    

    //forward declaration of object_imp
    class object_imp;
    class h5dataspace;
    class h5datatype;

    //------------------------------------------------------------------------
    //! 
    //! \ingroup nxh5_classes
    //! \brief checks for an attributes existence
    //!
    //! Checks if an attribute exists and returns true if it does.
    //! Otherwise false will be returned.
    //!
    //! \throws invalid_object_error if parent object not valid
    //! \throws object_error in case of any other errors
    //!
    //! \param parent the parent object where we look for the attribute
    //! \param name the name of the attribute to look for
    //! \return true if exists, false otherwise
    //!
    PNIIO_EXPORT bool has_attribute(const object_imp &parent,
		                            const pni::core::string &name);
            
    //------------------------------------------------------------------------
    //! 
    //! \ingroup nxh5_classes
    //! \brief Deletes an attribute
    //!
    //! Deletes an attribute from the object. 
    //! 
    //! \throws invalid_object_error if the object is not a valid HDF5 object
    //! \throws object_error in case of all other errors 
    //! \throws key_error if attribute does not exist
    //!
    //! \param parent reference to the parent object
    //! \param name the name of the attribute to delete
    //!
    PNIIO_EXPORT void delete_attribute(const object_imp &parent,
		                               const pni::core::string &name);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief create a new attribute at parent
    //! 
    //! Create a new attribute attached to a parent. 
    //!
    //! \throws invalid_objet_error if the parent object is not valid
    //! \throws object_error in case of any errors
    //! 
    //! \param parent the parent object for the attribute
    //! \param name the name for the attribute
    //! \param type an HDF5 data type
    //! \param space the dataspace for the attribute
    //! \param overwrite if true overwrite an existing attribute
    //! \return the attribute as h5object
    //!
    PNIIO_EXPORT object_imp create_attribute(const object_imp &parent,
                                             const pni::core::string &name,
                                             const h5datatype &type,
                                             const h5dataspace &space,
                                             bool overwrite);
                     
    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief open attribute by name
    //! 
    //! Open an existing attribute and returns it to the callee. If the 
    //! object does not exist key_error is thrown. In case of any other error 
    //! oject_error;
    //!
    //! \throws invalid_object_error if the parent object is not valid
    //! \throws key_error if attribute does not exist 
    //! \throws object_error in case of other errors
    //!
    //! \param parent reference to the parent object of the attribute
    //! \param n name of the attribute
    //! \return attribute object
    //!
    PNIIO_EXPORT object_imp get_attribute_by_name(const object_imp &parent,
		                                          const pni::core::string &n);


    //-----------------------------------------------------------------
    //! 
    //! \ingroup nxh5_classes
    //! \brief get number of attributes
    //!
    //! Method returns the number of attributes attached to this object.
    //!
    //! \throws invalid_object_error if the parent is not valid
    //! \throws object_error in case of any other error
    //! 
    //! \param parent the parent object with attributes
    //! \return number of attributes
    //!
    PNIIO_EXPORT size_t get_number_of_attributes(const object_imp &parent) ;

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief open attribute by index
    //!
    //! Opens an attribute reference by index i. If i exceeds the number of 
    //! attributes attached to this object an exception will be thrown.
    //!
    //! \throws invalid_object_error if parent object is not valid
    //! \throws index_error if i exceeds the total number of attributes attached
    //! to the parent object
    //! \throws object_error in case of any other error
    //! 
    //! \param parent the parent object from which to retrieve the attribute
    //! \param i index of the attribute
    //! \returns instance of H5Attribute
    //!
    PNIIO_EXPORT object_imp get_attribute_by_index(const object_imp &parent,
		                                           size_t i);


//end of namespace
}
}
}
}
