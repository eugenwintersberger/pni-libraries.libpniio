/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Definition of a general HDF5 Object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __H5OBJECT_HPP__
#define __H5OBJECT_HPP__

extern "C"{
#include <hdf5.h>
}

#include "H5ObjectType.hpp"
#include "../NXObjectType.hpp"

namespace pni{
    namespace nx{
        namespace h5{

            /*! \ingroup nxh5_classes
            \brief basic HDF5 object

            Each HDF5 object can be addressed by an unique ID. 
            This class is a wrapper around such an ID and provides basic
            inquiry methods valid for all HDF5 objects.
            The class is intended as a base class for other HDF5 objects 
            and thus cannot construct a valid HDF5 object by itself.
            
            Each HDF5 ID has an id reference counter. This reference counter
            can become important if objects are copied. 
            */
            class H5Object{
                private:
                    hid_t _id; //!< ID of the object
                protected:
                    /*! construct from HDF5 ID

                    This constructor can be used to construct an instance
                    of H5Object from an HDF5 ID. The constructor increases
                    the reference count to this id to avoid that the object
                    becomes invalid if the original id becomes destroyed.
                    Thus it is absolutely necessary that the original ID 
                    must be closed by the appropriate HDF5 API  function.
                    This can be seen in the example below:
                    \code
                    .....
                    hid_t id = H5Gopen(fid,"data",H5P_DEFAULT);
                    H5Object o(id);
                    H5Gclose(id); //destroy the original object will
                                  //decrement the reference count of id
                    ...
                    \endcode
                    The reason is simple: if the id is not closed properly
                    it remains open and prohibits the file it belongs to 
                    to become closed properly. 
                    \param id HDF5 object ID.
                    */
                    explicit H5Object(const hid_t &id);

                    /*! \brief set the object id

                    This method can be used to set the HDF5 id of an object. The
                    method does not take care about reference counting. The
                    original object from which the id value has been taken must
                    not be closed. This is done later by this class.
                    \param oid HDF5 object ID
                    */
                    void id(const hid_t &oid){
                        _id = oid;
                    }
                public:
                    //=============constructors and destructors================
                    //! default constructor
                    explicit H5Object();
                    //! copy constructor

                    //! Increments the ID reference counter for the ID wrapped
                    //! by this instance of H5Object. This constructor is not 
                    //! set "explicit" to allow copy construction from derived
                    //! classes of H5Object.
                    H5Object(const H5Object &o);
                    //! move constructor

                    //! Unlike for the copy constructor this constructor does 
                    //! not influence an IDs reference counter since the 
                    //! ID of the original object is set to 0. 
                    //! This constructor is not set "explicit" to allow 
                    //! move construction from derived classes of H5Object.
                    H5Object(H5Object &&o);
                    //! destructor
                    virtual ~H5Object();


                    //=============assignment operators========================
                    //!copy assignment operator
                    
                    //! Like the copy constructor this operator increments the 
                    //! IDs reference counter.
                    H5Object &operator=(const H5Object &o);

                    //!move assignment operator

                    //! Like the move constructor this operator has no influence
                    //! on the value of the IDs reference counter.
                    H5Object &operator=(H5Object &&o);


                    //================basic object maniuplation=================
                    //! close the object
                    virtual void close();
                    //! check validity 

                    //! This method returns true of the object refers to a valid 
                    //! HDF5 object. In other words this means that the object 
                    //! is valid and available. For a file object this would
                    //! mean that the file is open.
                    //! \returns true if valid HDF5 object
                    bool is_valid() const;
                    //! return HDF5 id

                    //! Returns the HDF5 ID of the object. The ID is returned as 
                    //! a const reference and thus cannot be altered.
                    //! \return HDF5 ID
                    const hid_t &id() const;
                    //! return the type of HDF5 object

                    //! Returns the HDF5 type of the object which can be used to 
                    //! identify the kind of object one is dealing with.
                    //! \return HDF type
                    H5ObjectType object_type() const;

                    //! return the Nexus object type

                    //! Returns the Nexus object type of an object.
                    //! This can be either NXObjecType::NXFIELD or
                    //! NXObjectType::NXGROUP. 
                    pni::nx::NXObjectType nxobject_type() const;

                    //! return the access time of the object

                    //! Returns the last time the object was accessed.
                    //! The time is returned as a time_t structure.
                    //! \return access time
                    time_t acc_time() const;

                    //! return modification time

                    //! Returns the time when the object was last mofified.
                    //! The time is returned as a time_t structure.
                    //! \return modification time
                    time_t mod_time() const;

                    //! return change time

                    //! Returns the time when the object was changed last.
                    //! The time value is returned as a time_t struct.
                    //! \return change time
                    time_t chng_time() const;

                    //! return birth time

                    //! Returns the time when the object was created. 
                    //! the time value is returned as time_t structure.
                    //! \return birth time
                    time_t birth_time() const;

            };

            //! equality operator

            //! Operator checks if two HDF5 object are equal. This check is
            //! done by comparing the address of the objects in the file.
            //! If they share the same address the objects should be equal.
            bool operator==(const H5Object &a,const H5Object &b);

            //! inequality operator

            //! Simply the inverse of the equality operator.
            bool operator!=(const H5Object &a,const H5Object &b);


//end of namespace
        }
    }
}

#endif
