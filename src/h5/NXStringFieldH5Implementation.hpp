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
 * NXStringFieldH5Implementation.hpp
 *
 *  Created on: Dec 2, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef NXSTRINGFIELDH5IMPLEMENTATION_HPP_
#define NXSTRINGFIELDH5IMPLEMENTATION_HPP_

#include "NXFieldH5Implementation.hpp"

namespace pni {
namespace nx {
namespace h5 {

class NXStringFieldH5Implementation:public NXFieldH5Implementation {
public:
	//! default constructor
	NXStringFieldH5Implementation();
	//! copy conversion constructor
	NXStringFieldH5Implementation(const NXFieldH5Implementation &o);
	//! copy conversion constructor
	NXStringFieldH5Implementation(const NXObjectH5Implementation &o);
	//! move conversion constructor
	NXStringFieldH5Implementation(NXFieldH5Implementation &&o);
	//! move conversion constructor
	NXStringFieldH5Implementation(NXObjectH5Implementation &&o);
	//! copy constructor
	NXStringFieldH5Implementation(const NXStringFieldH5Implementation &o);
	//! move constructor
	NXStringFieldH5Implementation(NXStringFieldH5Implementation &&o);
	//! destructor
	virtual ~NXStringFieldH5Implementation();

	//! copy assignment operator
	NXStringFieldH5Implementation &operator=(const NXStringFieldH5Implementation &o);
	//! move assignment operator
	NXStringFieldH5Implementation &operator=(NXStringFieldH5Implementation &&o);
	//! copy conversion assignment
	NXStringFieldH5Implementation &operator=(const NXFieldH5Implementation &o);
	//! copy conversion assignment
	NXStringFieldH5Implementation &operator=(const NXObjectH5Implementation &o);
	//! move conversion assignment
	NXStringFieldH5Implementation &operator=(NXFieldH5Implementation &&o);
	//! move conversion assignment
	NXStringFieldH5Implementation &operator=(NXObjectH5Implementation &&o);

	//! get number of strings
	virtual UInt64 size() const;

	//! append a string
	virtual void append(const String &o);

	//! set a string
	virtual void set(const UInt64 &i,const String &o);

	//! get a string
	virtual void get(const UInt64 &i,String &o);

	//! get a string
	virtual String get(const UInt64 &i);

	//! get all strings

	//! Returns all strings in the field separated by the separator character
	//! sep.
	//! \param sep separator character
	//! \return all strings stored separated by sep
	virtual String get(const char &sep);

};

} /* namespace h5 */
} /* namespace nx */
} /* namespace pni */
#endif /* NXSTRINGFIELDH5IMPLEMENTATION_HPP_ */
