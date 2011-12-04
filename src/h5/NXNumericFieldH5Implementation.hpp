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
 * NXNumericFieldH5Implementation.hpp
 *
 *  Created on: Dec 2, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef NXNUMERICFIELDH5IMPLEMENTATION_HPP_
#define NXNUMERICFIELDH5IMPLEMENTATION_HPP_

#include "NXFieldH5Implementation.hpp"

namespace pni {
namespace nx {
namespace h5 {

class NXNumericFieldH5Implementation:public NXFieldH5Implementation {
private:

public:
	//! default constructor
	NXNumericFieldH5Implementation();
	//! copy conversion constructor
	NXNumericFieldH5Implementation(const NXFieldH5Implementation &o);
	//! move conversion constructor
	NXNumericFieldH5Implementation(NXFieldH5Implementation &&o);
	//! copy constructor
	NXNumericFieldH5Implementation(const NXNumericFieldH5Implementation &o);
	//! move constructor;
	NXNumericFieldH5Implementation(NXNumericFieldH5Implementation &&o);
	//! destructor
	virtual ~NXNumericFieldH5Implementation();

	//! copy assignment operator
	NXNumericFieldH5Implementation &operator=(const NXNumericFieldH5Implementation &o);
	//! move assignment operator
	NXNumericFieldH5Implementation &operator=(NXNumericFieldH5Implementation &&o);
	//! copy conversion assignment
	NXNumericFieldH5Implementation &operator=(const NXFieldH5Implementation &o);
	//! move conversion assignment
	NXNumericFieldH5Implementation &operator=(NXFieldH5Implementation &&o);

	//! get the type ID

	//! Returns the ID of the type used.
	//! \return type ID
	//virtual PNITypeID getTypeID() const;

	//! append data
	virtual void append(const NumericObject &o,bool block);


	//! set an element
	virtual void set(const UInt64 &i,const NumericObject &o,bool block);

	//! get an element
	virtual void get(const UInt64 &i,NumericObject &o,bool block);

	//! get an element

	//! A move semantics is used in order to avoid performance propblems for
	//! arrays.
	//virtual NumericObject &&get(const UInt64 &i);

	//! get total data

	//! Fetches the entire content of the field and stores it into
	//! the numeric object o. In order to succeed the target object must be
	//! preallocated.
	//! \param o object where to store the data
	virtual void get(NumericObject &o);

	//! get total data

	//! The object is created directly by the method and returned using a
	//! move construction in order to avoid performance problems.
	//! \return data object
	//virtual NumericObject &&get();


};

} /* namespace h5 */
} /* namespace nx */
} /* namespace pni */
#endif /* NXNUMERICFIELDH5IMPLEMENTATION_HPP_ */
