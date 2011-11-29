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
 *
 *  Created on: Aug 9, 2011
 *      Author: Eugen Wintersberger
 */

#include <pni/utils/Exceptions.hpp>


#include "H5Filter.hpp"

namespace pni {
namespace nx {
namespace h5 {

//----------------------------------------------------------------------------
H5Filter::H5Filter() {

}

//----------------------------------------------------------------------------
H5Filter::H5Filter(const H5Filter &o){
	EXCEPTION_SETUP("H5Filter::H5Filter(const H5Filter &o)");

}

//----------------------------------------------------------------------------
H5Filter::~H5Filter() {

}

//----------------------------------------------------------------------------
H5Filter &H5Filter::operator=(const H5Filter &f){
	EXCEPTION_SETUP("H5Filter &H5Filter::operator=(const H5Filter &f)");
	if( this != &f ){

	}

	return *this;
}

//----------------------------------------------------------------------------
void H5Filter::setup(hid_t id) const{
}


//end of namespace
}
}
}
