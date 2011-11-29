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
 * H5DeflateFilter.hpp
 *
 *  Created on: Aug 10, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef H5DEFLATEFILTER_HPP_
#define H5DEFLATEFILTER_HPP_

#include "H5Filter.hpp"

namespace pni {
namespace nx {
namespace h5 {

//! \defgroup HDF5-Implementation

//! \ingroup HDF5-Implementation
//! HDF5 deflate filter

//! Implementation of the deflate (ZLIB) filter for HDF5.
class H5DeflateFilter:public H5Filter {
private:
	UInt32 _comp_rate;   //!< compression rate
public:
	//! default constructor
	H5DeflateFilter();
	//! copy constructor
	H5DeflateFilter(const H5DeflateFilter &);
	//! destructor
	virtual ~H5DeflateFilter();
	
	//! copy assignment operator
	H5DeflateFilter &operator=(const H5DeflateFilter &o);
	
	//! setup the filter
	virtual void setup(hid_t id) const;
	
	//! get compression rate
	virtual UInt32 getCompressionRate() const;
	//! set compression rate
	virtual void setCompressionRate(UInt32 r);


};


//end of namespace
}
}
}

#endif /* H5DEFLATEFILTER_HPP_ */
