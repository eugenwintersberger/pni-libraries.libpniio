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
#include "h5object.hpp"

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
            h5object _object;
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
            explicit h5datatype(h5object &&o);

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
            const h5object &object() const noexcept;

            //==========Assignment operators==================================
            //! copy assignment operator
            h5datatype &operator=(const h5datatype &o);
            //! move assignment operator
            h5datatype &operator=(h5datatype &&o);

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
    //!
    type_id_t type_id(const h5datatype &o);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief get reference to type
    //!
    //! \throws std::out_of_range  if no type for the ID value exists
    //!
    //! \return reference to a predefined data type
    //!
    const h5datatype &get_type(type_id_t id);

    h5datatype make_type(type_id_t id);


//end of namespace
}
}
}
}
