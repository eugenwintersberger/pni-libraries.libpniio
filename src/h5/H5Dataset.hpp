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
 * Implementation of a general named HDF5 object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#ifndef __H5DATASET_HPP__
#define __H5DATASET_HPP__

#include <pni/utils/Types.hpp>

using namespace pni::utils;

#include "H5Object.hpp"
#include "H5Datatype.hpp"
#include "H5Dataspace.hpp"
#include "H5Group.hpp"


namespace pni{
    namespace nx{
        namespace h5{
            

            class H5Dataset:public H5NamedObject{
                public:
                    //===================Constructors and destructors==========
                    H5Dataset();
                    H5Dataset(const H5Dataset &o);
                    H5Dataset(H5Dataset &&o);
                    H5Dataset(const String &n, const H5Group &g,
                            const H5Datatype &t,const H5Dataspace &s);
                    virtual ~H5Dataset();


                    //=================assignment operators====================
                    //! copy assignment operator
                    H5Dataset &operator=(const H5Dataset &o);

                    //! move assignment operator
                    H5Dataset &operator=(H5Dataset &&o);


            };

        
        //end of namespace
        }
    }
}


#endif
