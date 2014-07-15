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

#include <pni/core/error.hpp>
#include <pni/core/types.hpp>

#include "h5object.hpp"
#include "h5dataspace.hpp"
#include "h5datatype.hpp"
#include "../../exceptions.hpp"
#include "hdf5_utilities.hpp"


namespace pni{
namespace io{
namespace nx{
namespace h5{
    using namespace pni::core;
    //avoid namespace collisions with std
    using pni::core::exception;
    using pni::core::string;
    using pni::io::object_error;
    using pni::core::key_error;

    //------------------------------------------------------------------------
    //! 
    //! \ingroup nxh5_classes
    //! \brief checks for an attributes existence
    //!
    //! Checks if an attribute exists and returns true if it does.
    //! Otherwise false will be returned.
    //!
    //! \throws pni::io::object_error in case of errors
    //! \param n name of the attribute to check for
    //! \return true if exists, false otherwise
    //!
    bool has_attribute(const h5object &parent,const string &n);
            
    //------------------------------------------------------------------------
    //! 
    //! \ingroup nxh5_classes
    //! \brief Deletes an attribute
    //!
    //! Deletes an attribute from the object. 
    //! 
    //! \throws pni::io::object_error in case of errors 
    //! \param n name of the attribute
    //!
    void delete_attribute(const h5object &parent,const string &name);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief create a new attribute at parent
    //! 
    //! Create a new attribute attached to a parent. 
    //!
    //! \throws pni::io::object_error in case of any errors
    //! \param parent the parent object for the attribute
    //! \param name the name for the attribute
    //! \param type an HDF5 data type
    //! \param space the dataspace for the attribute
    //! \param overwrite if true overwrite an existing attribute
    //! \return the attribute as h5object
    //!
    h5object create_attribute(const h5object &parent,
                              const string &name,
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
    //! \throws pni::core::key_error if attribute does not exist 
    //! \throws pni::io::object_error in case of other errors
    //! exist or creation error
    //! \param n name of the attribute
    //! \return attribute object
    //!
    h5object get_attribute_by_name(const h5object &parent,const string &n);


    //-----------------------------------------------------------------
    //! 
    //! \ingroup nxh5_classes
    //! \brief get number of attributes
    //!
    //! Method returns the number of attributes attached to this object.
    //! \return number of attributes
    //!
    size_t get_number_of_attributes(const h5object &parent);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief open attribute by index
    //!
    //! Opens an attribute reference by index i. If i exceeds the number of 
    //! attributes attached to this object an exception will be thrown.
    //!
    //! \throws pni::core::index_error if i exceeds 
    //! \throws pni::io::object_error in case of any other error
    //! \param i index of the attribute
    //! \returns instance of H5Attribute
    //!
    h5object get_attribute_by_index(const h5object &parent,size_t i);


//end of namespace
}
}
}
}
