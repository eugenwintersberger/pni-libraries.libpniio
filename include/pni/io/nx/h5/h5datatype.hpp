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

namespace pni{
namespace io{
namespace nx{
namespace h5{


    using namespace pni::core;
    //avoid namespace collisions with std
    using pni::core::string;
    //!
    //! \ingroup nxh5_classes            
    //! \brief HDF5 type wrapper
    //! 
    //! This class provides a thin wrapper around an h5object instance
    //! representing an HDF5 data type. The only reason why this class is used 
    //! is to ensure that during object construction only h5object instances 
    //! will succeed which indeed represent a data type.
    //!
    class h5datatype
    {
        private:
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
            //!
            explicit h5datatype(object_imp &&o);

            //----------------------------------------------------------------
            //!
            //! \brief copy constructor
            //!
            //! \throws object_error in case of errors
            //!
            h5datatype(const h5datatype &o);

            //----------------------------------------------------------------
            //!
            //! \brief move constructor
            //!
            h5datatype(h5datatype &&o) noexcept;

            //----------------------------------------------------------------
            //!
            //! \brief obtain reference to object
            //!
            const object_imp &object() const noexcept;

            //==========Assignment operators==================================
            //! 
            //! \brief copy assignment operator
            //!
            //! \throws object_error in case of errors
            //!
            h5datatype &operator=(const h5datatype &o);

            //----------------------------------------------------------------
            //! 
            //! \brief move assignment operator
            //!  
            h5datatype &operator=(h5datatype &&o) noexcept;

    };
            
    //==========comparison operators==========================================
    //! 
    //! \ingroup nxh5_classes
    //! \brief equality comparison
    //!
    //! \throws object_error if comparison fails
    //! \param a lhs value of the operator
    //! \param b rhs value of the operator
    //! \return true if types are equal
    //!
    bool operator==(const h5datatype &a,const h5datatype &b);
        
    //------------------------------------------------------------------------
    //! 
    //! \ingroup nxh5_classes
    //! \brief inequality 
    //!
    //! \throws object_error if comparison fails
    //! \param a lhs value of the operator
    //! \param b rhs value of the operator
    //! \return true if not equal
    //!
    bool operator!=(const h5datatype &a,const h5datatype &b);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief get type code
    //!
    //! Obtain the type code of a datatype object
    //! \throws type_error if the passed datatype is not known
    //! \throws invalid_object_error if the data type instance is not valid
    //! \param o instance of an HDF5 datat type
    //! \return type_id_t value for the data type
    //!
    type_id_t type_id(const h5datatype &o);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief get reference to type
    //!
    //! \throws std::out_of_range  if no type for the ID value exists
    //!
    //! \param id type id for which to requeste an HDF5 datatype
    //! \return reference to a predefined data type
    //!
    const h5datatype &get_type(type_id_t id);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief create new type
    //! 
    //! \throws std::out_of_range if the ID has no HDF5 counterpart
    //! \param id type id
    //! \return h5datatype instance
    h5datatype make_type(type_id_t id);

    //------------------------------------------------------------------------
    //! 
    //! \ingroup nxh5_classes
    //! \brief check variable length string 
    //! 
    //! Returns true if the data type represents a variable length string 
    //! type.
    //! 
    //! \throws object_error if type inquery fails
    //! \throws invalid_object_error if type is not valid
    //! 
    //! \param type a type instance
    //! \return true if VL string type, false otherwise
    //!
    bool is_vl_string(const h5datatype &type);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief check if static length string
    //! 
    //! Returns true if the data type represents a static length string. 
    //! If type is not a string type at all false will be returned. 
    //!
    //! \throw object_error if information retrieval fails
    //! \throw invalid_object_error if object not valid
    //!
    //! \param type instance of h5datatype
    //! \return true if static string type, false otherwise
    //!
    bool is_static_string(const h5datatype &type);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief get static string size
    //! 
    //! Return the size of the strings for a static string size type. 
    //! 
    //! \throws type_error if type is not a static string type
    //! \throws invalid_type_error if the type is not valid
    //! \throws object_error in any other case
    //!
    //! \param type the datatype from which to retrieve the string size
    //! \return number of characters in each string
    //! 
    size_t static_string_size(const h5datatype &type);


//end of namespace
}
}
}
}
