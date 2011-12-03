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
 * NXBinaryFieldH5Implementation.cpp
 *
 *  Created on: Dec 2, 2011
 *      Author: Eugen Wintersberger
 */

#include "NXBinaryFieldH5Implementation.hpp"

namespace pni {
namespace nx {
namespace h5 {

NXBinaryFieldH5Implementation::NXBinaryFieldH5Implementation()
:NXFieldH5Implementation(){

}

NXBinaryFieldH5Implementation::~NXBinaryFieldH5Implementation() {

}

//------------------------------------------------------------------------------
size_t NXBinaryFieldH5Implementation::size() const{
	EXCEPTION_SETUP("size_t NXBinaryFieldH5Implementation::size() const");
	hid_t dataset = getId();

}

//------------------------------------------------------------------------------
void NXBinaryFieldH5Implementation::append(const Buffer<Binary> &b){
	EXCEPTION_SETUP("void NXBinaryFieldH5Implementation::append(const Buffer<Binary> &b)");

	if(!b.isAllocated()){
		//raise an exception if the buffer is not allocated
	}

	hid_t dataset = getId(); //get the dataset ID



}

} /* namespace h5 */
} /* namespace nx */
} /* namespace pni */
