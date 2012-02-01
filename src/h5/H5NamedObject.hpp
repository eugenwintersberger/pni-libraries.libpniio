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
 * Declaration of a general named HDF5 object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */



#ifndef __H5NAMEDOBJECT_HPP__
#define __H5NAMEDOBJECT_HPP__

#include "H5Object.hpp"


namespace pni{
    namespace nx{
        namespace h5{
            //! \ingroup nxh5_classes            
            //! \brief base class for named objects

            //! Named objects are those objects in an HDF5 file that can be 
            //! accessed by a path or which have a name (this includes Files 
            //! and attributes). This class is used as a base class for 
            //! such objects.
            class H5NamedObject:public H5Object{
                protected:
                    H5NamedObject(const hid_t &id);
                public:
                    //==============constructors and destructors===============
                    H5NamedObject();
                    H5NamedObject(const H5NamedObject &o);
                    H5NamedObject(const H5Object &o);
                    H5NamedObject(H5NamedObject &&o);
                    H5NamedObject(H5Object &&o);

                    virtual ~H5NamedObject();

                    //==========assignment operators===========================
                    H5NamedObject &operator=(const H5NamedObject &o);
                    H5NamedObject &operator=(const H5Object &o);
                    H5NamedObject &operator=(H5NamedObject &&o);
                    H5NamedObject &operator=(H5Object &&o);


                    //============name methods=================================
                    virtual String name() const;
                    virtual String base() const;
                    virtual String path() const;


            };

        //end of namespace
        }
    }
}

#endif
