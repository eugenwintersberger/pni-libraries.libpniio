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
 * Declaration of a general HDF5 Object.
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

namespace pni{
    namespace nx{
        namespace h5{
            //! \ingroup nxh5_classes
            //! \brief basic HDF5 object

            //! Each HDF5 object can be addressed by an unique ID. 
            //! This class is a wrapper around such an ID and provides basic
            //! inquery methods valid for all HDF5 objects.
            //! The class is inteded as a base class for other HDF5 objects 
            //! and thus cannot construct a valid HDF5 object by itself.
            //! 
            //! Each HDF5 ID has an id refernce counter. This reference counter
            //! can become important if objects are copied. 
            class H5Object{
                private:
                    hid_t _id; //!< ID of the object
                protected:
                    explicit H5Object(const hid_t &id);
                    //an HDF5 object cannot be created by itself - this 
                    //must be done by some other instance.
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
                    //! not incluence and IDs reference counter since the 
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
                    virtual bool is_valid() const;
                    //! return HDF5 id

                    //! Returns the HDF5 ID of the object. The ID is returned as 
                    //! a const reference and thus cannot be altered.
                    //! \return HDF5 ID
                    virtual const hid_t &id() const;
                    //! return the HDF5 type

                    //! Returns the HDF5 type of the object which can be used to 
                    //! identify the kind of object one is dealing with.
                    //! \return HDF type
                    virtual H5ObjectType type() const;
            };


//end of namespace
        }
    }
}

#endif
