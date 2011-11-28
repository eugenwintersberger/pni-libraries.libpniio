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
 * H5DeflateFilter.cpp
 *
 *  Created on: Aug 10, 2011
 *      Author: Eugen Wintersberger
 */

#include "H5DeflateFilter.hpp"
#include "H5Exceptions.hpp"

namespace pni {
namespace nx {
namespace h5 {

//-----------------------------------------------------------------------------
H5DeflateFilter::H5DeflateFilter():H5Filter() {
	_comp_rate = 0;
}

//-----------------------------------------------------------------------------
H5DeflateFilter::~H5DeflateFilter() {
}

//-----------------------------------------------------------------------------
H5DeflateFilter::H5DeflateFilter(const H5DeflateFilter &o){
	_comp_rate = o._comp_rate;
}

//-----------------------------------------------------------------------------
H5DeflateFilter &H5DeflateFilter::operator=(const H5DeflateFilter &o){
	if(this != &o){
		_comp_rate = o._comp_rate;
	}

	return *this;
}

//-----------------------------------------------------------------------------
void H5DeflateFilter::setup(hid_t id){
	EXCEPTION_SETUP("void H5DeflateFilter::setup(hid_t id)");

	if((H5Pset_deflate(id,_comp_rate))<0){
		EXCEPTION_INIT(H5FilterError,"Cannot setup deflate filter!");
		EXCEPTION_THROW();
	}
}

//-----------------------------------------------------------------------------
UInt32 H5DeflateFilter::getCompressionRate() const{
	return _comp_rate;
}

//-----------------------------------------------------------------------------
void H5DeflateFilter::setCompressionRate(UInt32 r){
	EXCEPTION_SETUP("void H5DeflateFilter::setCompressionRate(UInt32 r)");

	if(r<=9){
		_comp_rate = r;
	}else{
		EXCEPTION_INIT(H5FilterError,"Compression level for deflate filter must be between 0 and 9!");
		EXCEPTION_THROW();
	}
}

//end of namespace
}
}
}
