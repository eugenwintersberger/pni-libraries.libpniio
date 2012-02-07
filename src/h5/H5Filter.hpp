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
 * H5Filter.cpp
 *  Definition of the HDF5 filter base class.
 *
 *  Created on: Feb 7, 2012
 *      Author: Eugen Wintersberger
 */
#ifndef __H5FILTER_HPP__
#define __H5FILTER_HPP__

extern "C"{
#include<hdf5.h>
}

#include "H5Exceptions.hpp"


namespace pni{
    namespace nx {
        namespace h5{
            
            class H5Filter{
                private:
                public:
                    H5Filter();
                    H5Filter(const H5Filter &o);
                    H5Filter(H5Filter &&o);
                    virtual ~H5Filter();

                    H5Filter &operator=(const H5Filter &o);
                    H5Filter &operator=(H5Filter &&o);


                    virtual void setup(const hid_t &id) const;

            };

        }
    }
}

#endif
