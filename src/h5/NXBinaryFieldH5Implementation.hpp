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
 * NXBinaryFieldH5Implementation.hpp
 *
 *  Created on: Dec 2, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef NXBINARYFIELDH5IMPLEMENTATION_HPP_
#define NXBINARYFIELDH5IMPLEMENTATION_HPP_

#include "NXFieldH5Implementation.hpp"

namespace pni {
namespace nx {
namespace h5 {

class NXBinaryFieldH5Implementation:public NXFieldH5Implementation {
public:
	//! default constructor
	NXBinaryFieldH5Implementation();
	//! copy conversion constructor
	NXBinaryFieldH5Implementation(const NXFieldH5Implementation &o);
	//! move conversion constructor
	NXBinaryFieldH5Implementation(NXFieldH5Implementation &&o);
	//! copy constructor
	NXBinaryFieldH5Implementation(const NXBinaryFieldH5Implementation &o);
	//! move constructor
	NXBinaryFieldH5Implementation(NXBinaryFieldH5Implementation &&o);
	//! destructor
	virtual ~NXBinaryFieldH5Implementation();

	//! copy assignment operator
	NXBinaryFieldH5Implementation &operator=(const NXBinaryFieldH5Implementation &o);
	//! move assignment operator
	NXBinaryFieldH5Implementation &operator=(NXBinaryFieldH5Implementation &&o);
	//! copy conversion assignment
	NXBinaryFieldH5Implementation &operator=(const NXFieldH5Implementation &o);
	//! move conversion assignment
	NXBinaryFieldH5Implementation &operator=(NXFieldH5Implementation &&o);
};

} /* namespace h5 */
} /* namespace nx */
} /* namespace pni */
#endif /* NXBINARYFIELDH5IMPLEMENTATION_HPP_ */
