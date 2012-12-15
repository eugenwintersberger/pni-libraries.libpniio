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
 * H5LZFFilter.hpp
 * 
 * Definition of the LZF Filter class.
 *
 *  Created on: Aug 10, 2011
 *      Author: Eugen Wintersberger
 */

#pragma once

extern "C"{
#include <hdf5.h>
}

#include <pni/utils/Types.hpp>

#include "H5Filter.hpp"

using namespace pni::utils;

namespace pni {
namespace nx {
namespace h5 {

//! \ingroup nxh5_classes
//! \brief LZF filter implementation

//! Implementation of the LZF filter for HDF5. This filter 
//! was taken from the H5PY project which uses this filter 
//! in its Python code.
class H5LZFFilter:public H5Filter {
public:
	//! default constructor
	H5LZFFilter();
	//! copy constructor
	H5LZFFilter(const H5LZFFilter &o);
	//! destructor
	virtual ~H5LZFFilter();
	
	//! copy assignment operator
	H5LZFFilter &operator=(const H5LZFFilter &o);
	
	//! setup filter
	virtual void setup(hid_t id) const;
};


//end of namespace
}
}
}
