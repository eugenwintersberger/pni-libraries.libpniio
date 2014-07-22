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
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Jul 14, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

extern "C"{
#include <hdf5.h>
}

#include <pni/core/types.hpp>
#include "../../exceptions.hpp"
#include "h5object_types.hpp"
#include "../nxobject_type.hpp"

namespace pni{
namespace io{
namespace nx{
namespace h5{
    //avoid namespace collisions with std
    using pni::core::string;

    //! 
    //! \ingroup nxh5_classes
    //! \brief basic HDF5 ID wrapper
    //! 
    //! Every object in HDF5 is identified by a unique ID within a file. This
    //! is a wrapper around such an ID. It is thus the most basic implementation
    //! of an HDF5 object. It provides no functionality but 
    //! \li copy or move an ID
    //! \li destroy the object refered to by the ID
    //! 
    //! This is the basic brickstone for the construction of implementation
    //! classes for Nexus objects. Unlike the original HDF5 C++ interface we use 
    //! composition instead of inheritance which should make maintenance of the 
    //! class much easier. 
    //!
    //! Alternatively one can consider this class as a guard for hid_t. 
    //! The descructor calls the close() method and thus ensures that an an 
    //! object represented by hid_t is closed when it looses scope.
    //!
    class object_imp
    {
        private:
            hid_t _id; //!< ID of the object
        protected:

            //-----------------------------------------------------------------
            //! 
            //! \brief reset the ID
            //!
            //! Reset the ID of the object to zero and thus renders it as 
            //! invalid.
            //!
            void reset_id() noexcept { _id = 0; }

            //----------------------------------------------------------------
            //!
            //! \brief increments reference counter
            //!
            //! This memeber method increments the reference counter of the 
            //! internal HDF5 object ID. This is in particular important for
            //! all kinds of copy operations.
            //! 
            //! \throws object_error if increment fails
            //! 
            void inc_ref();

        public:
            //================constructors and destructors=====================
            //! 
            //! \brief construct from HDF5 ID
            //!
            //! This constructor can be used to construct an instance of 
            //! h5object from an HDF5 ID. 
            //! h5object takes full control over the constructed object. Thus
            //! the constructor has move semantics and does not allow to use 
            //! const & or & to the hid_t argument.
            //! A typical usage example would look like this
            /*!
            \code
            .....
            h5object o(H5Gopen(fid,"data",H5P_DEFAULT));
            ...
            \endcode
            */
            //! Due to move semantics the following construction would cause a 
            //! compile time error
            /*!
            \code
            hid_t type = H5Tcopy(H5T_NATIVE_FLOAT);
            h5object o(type);
            \endcode
            */
            //! An exception is thrown if the ID passed is negative.
            //! \throws object_error if id<0
            //! \param id HDF5 object ID.
            //!
            explicit object_imp(hid_t &&id);

            //-----------------------------------------------------------------
            //! 
            //! \brief default constructor
            //! 
            //! The default constructor does not throw. However, after default 
            //! construction the object will be in an invalid state. 
            //!
            explicit object_imp() noexcept;

            //-----------------------------------------------------------------
            //! 
            //! \brief copy constructor
            //!
            //! Copies the ID of the o and increments its reference counter if 
            //! the object is valid.
            //!
            //! \throws object_error in cases where object validity could not 
            //!                      be determined
            //! \param o object which to cpy
            //!
            object_imp(const object_imp &o);

            //-----------------------------------------------------------------
            //! 
            //! \brief move constructor
            //!
            //! Copies the ID of the original object and sets the ID of the 
            //! original object to 0. As this is a move process the reference 
            //! counter of the ID will not be incremented.
            //!
            //! \param o object to move
            //!
            object_imp(object_imp &&o) noexcept;

            //-----------------------------------------------------------------
            //!
            //! \brief destructor
            //! 
            //! \throws object_error if closing object failed or its validity
            //!                      could not be determined
            //!
            ~object_imp();


            //================assignment operators=============================
            //!
            //! \brief copy assignment operator
            //! 
            //! Just like for the copy constructor the reference counter for 
            //! the original ID is incremented.
            //!
            //! \throws object_error if reference counter increment fails or 
            //!                      object validity could not be determined
            //! \param o object to assign
            //! \return refence to object
            //!
            object_imp &operator=(const object_imp &o);

            //-----------------------------------------------------------------
            //!
            //! \brief move assignment operator
            //!
            //! Like the move constructor this operator has no influence on the
            //! value of the IDs reference counter.
            //!
            //! \throws object_error if closing the original object fails
            //! \param o object form which to move data
            //! \return reference to object
            //!
            object_imp &operator=(object_imp &&o) noexcept;


            //=====================basic object maniuplation====================
            //! 
            //! \brief close the object
            //! 
            //! This will decrement the reference counter of the ID held by this
            //! object or close it if the reference counter approaches 0. 
            //! The close method runs an object introspection by means of the 
            //! HDF5 library and calls the appropriate close function. 
            //! 
            //! \throws object_error if object validity could not be determined
            //! \throws type_error if the type of the object could not be
            //!         determined
            //! or closing the object failed
            //!
            void close();

            //------------------------------------------------------------------
            //! 
            //! \brief check validity 
            //!
            //! This method returns true of the object refers to a valid HDF5
            //! object. In other words this means that the object is valid and
            //! available. For a file object this would mean that the file is 
            //! open.
            //! 
            //! \throws object_error if querying the object validity fails
            //! \returns true if valid HDF5 object
            //!
            bool is_valid() const;

            //------------------------------------------------------------------
            //! 
            //! \brief return HDF5 id
            //!
            //! Returns the HDF5 ID of the object. The ID is returned as a 
            //! const reference and thus cannot be altered.
            //! \return HDF5 ID
            //!
            const hid_t &id() const noexcept;

            //-----------------------------------------------------------------
            //!
            //! \brief get nexus object type
            //!
            //! \throws type_error in case of an unkown type
            //! \throws invalid object_error if object is not valid
            //! \return Nexus type of the object
            //!
            pni::io::nx::nxobject_type nxobject_type() const; 
    };

    //===================equality operators for H5Object instances=============
    //! 
    //! \ingroup nxh5_classes
    //! \brief equality operator
    //! 
    //! Operator checks if two HDF5 object are equal. This check is done by
    //! comparing the address of the objects in the file.  If they share the 
    //! same address the objects should be equal. Invalid objects are considered 
    //! as not equal.
    //!
    //! \throws object_error in case of errors
    //! \param a lhs value of the operator
    //! \param b rhs value of the operator
    //! \return true if equal, false otherwise
    //!
    bool operator==(const object_imp &a,const object_imp &b);

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup nxh5_classes
    //! \brief inequality operator
    //!
    //! Simply the inverse of the equality operator.
    //!
    //! \throws object_error in case of errors
    //! \param a lhs value of the operator
    //! \param b rhs value of the operator
    //! \return true if not equal, false otherwise
    //!
    bool operator!=(const object_imp &a,const object_imp &b);


//end of namespace
}
}
}
}
