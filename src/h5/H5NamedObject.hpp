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
 * Declaration of a general named HDF5 object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/Types.hpp>
#include "H5Object.hpp"


using namespace pni::core;

namespace pni{
namespace io{
namespace nx{
namespace h5{
    //forward declaration
    //class H5Group;

    /*! 
    \ingroup nxh5_classes            
    \brief base class for named objects

    Named objects are those objects in an HDF5 file that can be accessed by a
    path or which have a name (this includes Files and attributes). This class
    is used as a base class for such objects.  Due to the fact that such objects
    can be linked. 
    */
    class H5NamedObject:public H5Object
    {
        protected:
            /*! 
            \brief construct from HDF5 ID

            This protected constructor allows object construction form an HDF5
            ID. Only derived classes are supposed to use this constructor.
            The reference counter of the id passed will not be altered.
            \param id HDF5 id
            */
            explicit H5NamedObject(const hid_t &id);
        public:
            //==============constructors and destructors=======================
            //! default constructor
            explicit H5NamedObject();
            //! copy constructor
            H5NamedObject(const H5NamedObject &o);
            //! copy conversion constructor
            H5NamedObject(const H5Object &o);
            //! move constructor
            H5NamedObject(H5NamedObject &&o);
            //! move conversion constructor
            H5NamedObject(H5Object &&o);
            //! destructor
            virtual ~H5NamedObject();

            //==========assignment operators===================================
            //! copy assignment operator
            H5NamedObject &operator=(const H5NamedObject &o);
            //! copy conversion assignment operator
            H5NamedObject &operator=(const H5Object &o);
            //! move assignment operator
            H5NamedObject &operator=(H5NamedObject &&o);
            //! move conversion assignment operator
            H5NamedObject &operator=(H5Object &&o);


            //============name methods=========================================
            /*! 
            \brief return object name

            Returns the name of an object. Within an HDF5 file objects can be
            addressed by a UNIX like path.  This method returns the last part of
            the path.  So if an object would have the following path
            /scan_1/detector/data this method would return data.  The behavior
            of this method is slightly different for a file object.
            \return name of the object
            */
            virtual String name() const;

            //-----------------------------------------------------------------
            /*! 
            \brief return object base

            Return the the base part of the objects path.  If the object would
            have the path /scan_1/detector/data this method would return
            /scan_1/detector.
            \return base part of the objects path
            */
            virtual String base() const;

            //-----------------------------------------------------------------
            /*! 
            \brief return object path
            
            This method returns the full path of an object.
            \return full object path
            */
            virtual String path() const;


    };

//end of namespace
}
}
}
}
