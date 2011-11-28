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
 * H5TypeFactory.hpp
 *
 *  Created on: Jun 27, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef H5TYPEFACTORY_HPP_
#define H5TYPEFACTORY_HPP_

extern "C"{
#include <hdf5.h>
}

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/NumericObject.hpp>

using namespace pni::utils;

namespace pni{
namespace nx{
namespace h5{

//! \ingroup HDF5-Implementation
//! \brief type factory

//! This class provides HDF5 type objects for all data-types supported by the 
//! library. The aim of this class is that types are only created once and 
//! afterwards are copied if needed. A user can request either a const reference 
//! to an existing type or obtain a new copy of this type. 
//! In both cases the type must not be created from scratch but is rather copied 
//! from its prototype.
class H5TypeFactory {
private:
	//from this class we would need a singleton - should be available only
	//once at runtime - most probably as a global object.
	typedef struct {
		Float32 r;
		Float32 i;

	} _struct_complex_32;  //!< C structure for a 32Bit complex type
	typedef struct {
		Float64 r;
		Float64 i;
	} _struct_complex_64;  //!< C structure for a 64Bit complex type

	typedef struct {
		Float128 r;
		Float128 i;
	} _struct_complex_128; //!< C structure for a 128Bit complex type

	hid_t _int8_type;    //!< handler to a 8Bit signed integer type
	hid_t _uint8_type;   //!< handler to a 8Bit unsigned integer type
	hid_t _int16_type;   //!< handler to a 16Bit signed integer type
	hid_t _uint16_type;  //!< handler to a 16Bit unsigned integer type
	hid_t _int32_type;   //!< handler to a 32Bit signed integer type
	hid_t _uint32_type;  //!< handler to a 32Bit unsigned integer type
	hid_t _int64_type;   //!< handler to a 64Bit signed integer type
	hid_t _uint64_type;  //!< handler to a 64Bit unsigned integer type
	hid_t _float32_type; //!< handler to a 32Bit IEEE floating point type
	hid_t _float64_type; //!< handler to a 64Bit IEEE floating point type
	hid_t _float128_type;    //!< handler to a 128Bit IEEE floating point type
	hid_t _complex32_type;   //!< handler to a 32Bit IEEE complex type
	hid_t _complex64_type;   //!< handler to a 64Bit IEEE complex type
	hid_t _complex128_type;  //!< handler to a 128Bit IEEE complex type
	hid_t _string_type;      //!< type to handle Strings in HDF5

	//! private method to create the complex types
	template<typename T> hid_t _create_complex_type();
	//! private method for string type creation
	hid_t _create_string_type();
public:
	//! default constructor
	H5TypeFactory();
	//! destructor
	virtual ~H5TypeFactory();

	//! create a new type 

	//! Return a new copy of the requested type.
	//! \return ID to a new HDF5 type object
	template<typename T> hid_t createType() const;
	//! get a type reference

	//! Returns a reference to an existing instance of the 
	//! requested type.
	//! \return ID to an existing HDF5 type object
	template<typename T> hid_t getType() const;
	//! create a type from an existing NumericObject
	hid_t createTypeFromObject(const NumericObject &o);
	//! get the type from an existing NumericObject
	hid_t getTypeFromObject(const NumericObject &o);

	//! get a type according to the type id
	hid_t getTypeFromID(PNITypeID id);
	//! create a new type according to its type id
	hid_t createTypeFromID(PNITypeID id);
};

//! static and global instance of H5TypeFactory
static H5TypeFactory H5TFactory;

//end of namespace
}
}
}


#endif /* H5TYPEFACTORY_HPP_ */
