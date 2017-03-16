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
// ===========================================================================
//
// Created on: Jul 14, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <pni/core/types.hpp>
#include "object_imp.hpp"
#include "../../windows.hpp"

namespace pni{
namespace io{
namespace nx{
namespace h5{

    //!
    //! \ingroup nxh5_classes            
    //! \brief HDF5 type wrapper
    //! 
    //! This class provides a thin wrapper around an h5object instance
    //! representing an HDF5 data type. The only reason why this class is used 
    //! is to ensure that during object construction only h5object instances 
    //! will succeed which indeed represent a data type.
    //!
    class PNIIO_EXPORT h5datatype
    {
        private:
            //! HDF5 object representing the data type
            object_imp _object;
        public:
            //======================Constructors and destructors===============
            //!
            //! \brief default constructor
            //!
            explicit h5datatype() noexcept;

            //----------------------------------------------------------------
            //!
            //! \brief object construction
            //!
            //! \throws type_error if the passed object is not an HDF5 
            //! data type 
            //! \throws invalid_object_error if the object is not valid
            //! \throws object_error in case of any other error
            //!
            //! \param o rvalue reference to an existing object instance
            //!
            explicit h5datatype(object_imp &&o);

            //----------------------------------------------------------------
            //!
            //! \brief obtain reference to object
            //!
            const object_imp &object() const noexcept;
    };
            
    //==========comparison operators==========================================
    //! 
    //! \ingroup nxh5_classes
    //! \brief equality comparison
    //!
    //! \throws object_error if comparison fails
    //!
    //! \param a lhs value of the operator
    //! \param b rhs value of the operator
    //! \return true if types are equal
    //!
    PNIIO_EXPORT bool operator==(const h5datatype &a,const h5datatype &b);
        
    //------------------------------------------------------------------------
    //! 
    //! \ingroup nxh5_classes
    //! \brief inequality 
    //!
    //! \throws object_error if comparison fails
    //!
    //! \param a lhs value of the operator
    //! \param b rhs value of the operator
    //! \return true if not equal
    //!
    PNIIO_EXPORT bool operator!=(const h5datatype &a,const h5datatype &b);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief get type code
    //!
    //! Obtain the type code of a datatype object
    //!
    //! \throws type_error if the passed datatype is not known
    //! \throws invalid_object_error if the data type instance is not valid
    //! \throws object_error in case of any other error
    //!
    //! \param o instance of an HDF5 datat type
    //! \return type_id_t value for the data type
    //!
    PNIIO_EXPORT pni::core::type_id_t type_id(const h5datatype &o);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief get reference to type
    //!
    //! \throws type_error if id has no corresponding HDF5 data type
    //!
    //! \param id type id for which to requeste an HDF5 datatype
    //! \return reference to a predefined data type
    //!
    PNIIO_EXPORT const h5datatype &get_type(pni::core::type_id_t id);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief create new type
    //! 
    //! \throws type_error if the ID has no HDF5 counterpart
    //!
    //! \param id type id
    //! \return h5datatype instance
    //!
    PNIIO_EXPORT h5datatype make_type(pni::core::type_id_t id);

    

//end of namespace
}
}
}
}
