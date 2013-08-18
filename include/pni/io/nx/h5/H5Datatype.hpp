/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Definition of a general HDF5 datatype object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <pni/core/types.hpp>


#include "H5Object.hpp"


namespace pni{
namespace io{
namespace nx{
namespace h5{

    using namespace pni::core;
    //avoid namespace collisions with std
    using pni::core::string;
    /*! 
    \ingroup nxh5_classes            
    \brief HDF5 type wrapper

    The class wraps around an HDF5 type object. One will hardly 
    ever construct this class by oneself. This is usually done 
    using the H5DatatypeFactory which provides convenient methods
    for this purpose.
    */
    class H5Datatype:public H5Object
    {
        public:
            //======================Constructors and destructors===============
            //! default constructor
            explicit H5Datatype();
            //! copy constructor
            H5Datatype(const H5Datatype &o);
            //! copy conversion operator
            H5Datatype(const H5Object &o);
            //! move constructor
            H5Datatype(H5Datatype &&o);
            //! move conversion operator
            H5Datatype(H5Object &&o);
            //! constructor form HDF5 id
            explicit H5Datatype(const hid_t &tid);
            //! destructor
            ~H5Datatype();


            //==========Assignment operators===================================
            //! copy assignment operator
            H5Datatype &operator=(const H5Datatype &o);
            //! copy conversion assignment operator
            H5Datatype &operator=(const H5Object &o);
            //! move assignment operator
            H5Datatype &operator=(H5Datatype &&o);
            //! move conversion assignment operator
            H5Datatype &operator=(H5Object &&o);

            //==========some inquery methods===================================
            //! type ID

            //! Return the type id of the datatype. 
            //! \return type code
            type_id_t type_id() const;
            
            //! close the datatype
            virtual void close();


            //!==========comparison operators==================================
            /*! 
            \brief equality comparison

            \throws pni::io::nx::nxbackend_error if comparison fails
            \param a lhs value of the operator
            \param b rhs value of the operator
            \return true if types are equal
            */
            friend bool operator==(const H5Datatype &a,const H5Datatype &b);

            //-----------------------------------------------------------------
            /*! 
            \brief inequality 

            \throws pni::io::nx::nxbackend_error if comparison fails
            \param a lhs value of the operator
            \param b rhs value of the operator
            \return true if not equal
            */
            friend bool operator!=(const H5Datatype &a,const H5Datatype &b);
    };


//end of namespace
}
}
}
}
