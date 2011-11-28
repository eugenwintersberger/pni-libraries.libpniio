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
 * H5Filter.hpp
 *
 *  Created on: Aug 9, 2011
 *      Author: eugen
 */

#ifndef H5FILTER_HPP_
#define H5FILTER_HPP_

extern "C"{
#include <hdf5.h>
}

#include <pni/utils/PNITypes.hpp>

using namespace pni::utils;

namespace pni {
namespace nx {
namespace h5 {

//! \ingroup HDF5-Implementation
//! \brief HDF5 filter base class

//! Base class for all HDF5 compression filter implementations.
class H5Filter {
public:
	//! default constructor
	H5Filter();
	//! copy constructor
	H5Filter(const H5Filter &o);
	//! destructor
	virtual ~H5Filter();

	//! copy assignment operator
	H5Filter &operator=(const H5Filter &o);

	//! setup method

	//! This method applies the filter to a particular 
	//! dataset which is given by _id. This method 
	//! must be overridden by all descendants of this class.
	void setup(hid_t _id);
};


//end of namespace
}
}
}

#endif /* H5FILTER_HPP_ */
