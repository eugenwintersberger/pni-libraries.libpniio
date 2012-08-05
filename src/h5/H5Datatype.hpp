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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Definition of a general HDF5 datatype object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __H5DATATYPE_HPP__
#define __H5DATATYPE_HPP__

#include <pni/utils/Types.hpp>

using namespace pni::utils;

#include "H5Object.hpp"


namespace pni{
namespace nx{
namespace h5{
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
            TypeID type_id() const;
            
            //! close the datatype
            virtual void close();


            //!==========comparison operators==================================
            //! equality comparison
            friend bool operator==(const H5Datatype &a,const H5Datatype &b);
            //! inequality 
            friend bool operator!=(const H5Datatype &a,const H5Datatype &b);
    };


//end of namespace
}
}
}


#endif
