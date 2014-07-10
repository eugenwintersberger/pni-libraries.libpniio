//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jan 10, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

extern "C"{
#include <hdf5.h>
}

#include <pni/core/types.hpp>
#include "H5ObjectType.hpp"
#include "../nxobject_type.hpp"
#include "../../exceptions.hpp"

namespace pni{
namespace io{
namespace nx{
namespace h5{
    //avoid namespace collisions with std
    using pni::core::string;

    //! 
    //! \ingroup nxh5_classes
    //! \brief basic HDF5 object
    //! 
    //! Each object within an HDF5 file is identified by a unique ID. With 
    //! each ID a reference counter is associated indicating the number of 
    //! copies of an object in a running instance. The H5Object class is a 
    //! wrapper around an HDF5 ID.  Its primary purpose is to manage 
    //! reference counting for an object.  One can consider H5Object as a 
    //! guard object around an HDF5 ID. It takes care that the reference 
    //! counter gets decreased when an instance of H5Object gets destroyed. 
    //! In addition it provides access to the basic properties of an
    //! object (properties common to all objects in the HDF5 universe).
    //!
    //! H5Object cannot be constructed directly but only through the 
    //! constructors of its child classes implementing a concrete HDF5 type. 
    //!
    class H5Object
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
        public:
            //================constructors and destructors=====================
            //! 
            //! \brief construct from HDF5 ID
            //!
            //! This constructor can be used to construct an instance of 
            //! H5Object from an HDF5 ID. The constructor does not increase 
            //! the reference counter of the ID used for the construction. In 
            //! other words the objects takes ownership of the object
            /*!
            \code
            .....
            H5Object o(H5Gopen(fid,"data",H5P_DEFAULT));
            ...
            \endcode
            */
            //! An exception is thrown if the ID passed is negative.
            //! \throws pni::io::nx::nxbackend_error if id<0
            //! \param id HDF5 object ID.
            //!
            explicit H5Object(const hid_t &id);

            //-----------------------------------------------------------------
            //! 
            //! \brief default constructor
            //! 
            //! The default constructor does not throw
            //!
            explicit H5Object() noexcept;

            //-----------------------------------------------------------------
            //! 
            //! \brief copy constructor
            //!
            //! Copies the ID of the o and increments its reference counter.
            //!
            //! \throws object_error in cases where object validity could not 
            //!                      be determined
            //! \param o object which to cpy
            //!
            H5Object(const H5Object &o);

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
            H5Object(H5Object &&o) noexcept;

            //-----------------------------------------------------------------
            //!
            //! \brief destructor
            //! 
            //! \throws object_error if closing object failed or its validity
            //!                      could not be determined
            //!
            virtual ~H5Object();


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
            H5Object &operator=(const H5Object &o);

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
            H5Object &operator=(H5Object &&o);


            //=====================basic object maniuplation====================
            //! 
            //! \brief close the object
            //! 
            //! This will decrement the reference counter of the ID held by this
            //! object or close it if the reference counter approaches 0. It is
            //! important to note that this method uses internally the 
            //! \c H5Oclose function from the HDf5 API. As this function works 
            //! only for groups, datasets, and types all other objects must 
            //! implement their own close method using the appropriate HDF5 
            //! function call.
            //! 
            //! \throws object_error if object validity could not be determined
            //! or closing the object failed
            //!
            virtual void close();

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
            //! \brief return the type of HDF5 object
            //! 
            //! Returns the HDF5 type of the object which can be used to 
            //! identify the kind of object one is dealing with. If the object 
            //! is not valid an exception will be thrown.
            //!
            //! \throws invalid_object_error if object is not valid
            //! \throws type_error if object is of unkown type
            //! \return HDF type
            //!
            H5ObjectType object_type() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief return the Nexus object type
            //!
            //! Returns the Nexus object type of an object.  This can be 
            //! either nxobject_type::NXFIELD or nxobject_type::NXGROUP. 
            //! 
            //! \throws invalid_object_error if the object is not valid
            //! \throws type_error if object type is unknown
            //! \return Nexus object type
            //!
            pni::io::nx::nxobject_type nxobject_type() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief return the access time of the object
            //!
            //! Returns the last time the object was accessed. The time is 
            //! returned as a time_t structure.
            //! \warning  THIS METHOD WILL BE REMOVED IN ONE OF THE FUTURE RELEASES
            //! \throws pni::io::nx::nxbackend_error if cannot obtain time
            //! \return access time
            //!
            time_t acc_time() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief return modification time
            //!
            //! Returns the time when the object was last mofified. The time is
            //! returned as a time_t structure.
            //! \warning  THIS METHOD WILL BE REMOVED IN ONE OF THE FUTURE RELEASES
            //! \throws pni::io::nx::nxbackend_error if cannot obtain time
            //! \return modification time
            //!
            time_t mod_time() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief return change time
            //!
            //! Returns the time when the object was changed last.  The time value
            //! is returned as a time_t struct.
            //! \warning THIS METHOD WILL BE REMOVED IN ONE OF THE FUTURE RELEASES
            //! \throws pni::io::nx::nxbackend_error if cannot obtain time
            //! \return change time
            //!
            time_t chng_time() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief return birth time
            //!
            //! Returns the time when the object was created. The time value is
            //! returned as time_t structure.
            //! \warning THIS METHOD WILL BE REMOVED IN ONE OF THE FUTURE RELEASES
            //! \throws pni::io::nx::nxbackend_error if cannot obtain time
            //! \return birth time
            //!
            time_t birth_time() const;

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
    //! \throws object_error if object addresses could not be obtained
    //! \param a lhs value of the operator
    //! \param b rhs value of the operator
    //! \return true if equal, false otherwise
    //!
    bool operator==(const H5Object &a,const H5Object &b);

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup nxh5_classes
    //! \brief inequality operator
    //!
    //! Simply the inverse of the equality operator.
    //!
    //! \throws object_error if object addresses could not be obtained
    //! \param a lhs value of the operator
    //! \param b rhs value of the operator
    //! \return true if not equal, false otherwise
    //!
    bool operator!=(const H5Object &a,const H5Object &b);


//end of namespace
}
}
}
}
