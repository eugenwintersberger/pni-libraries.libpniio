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

            class H5Object{
                private:
                    hid_t _id; //!< ID of the object
                protected:
                    H5Object(const hid_t &id);
                    //an HDF5 object cannot be created by itself - this 
                    //must be done by some other instance.
                    void id(const hid_t &oid){
                        _id = oid;
                    }
                public:
                    //=============constructors and destructors============================
                    H5Object();
                    H5Object(const H5Object &o);
                    H5Object(H5Object &&o);
                    virtual ~H5Object();


                    //=============assignment operators====================================
                    //!copy assignment operator
                    H5Object &operator=(const H5Object &o);

                    //!move assignment operator
                    H5Object &operator=(H5Object &&o);


                    //================basic object maniuplation=================
                    void close();
                    bool is_valid() const;
                    const hid_t &id() const;

                    H5ObjectType type() const;
            };


//end of namespace
        }
    }
}

#endif
