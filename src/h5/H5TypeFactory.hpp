/*
 * H5TypeFactory.hpp
 *
 *  Created on: Jun 27, 2011
 *      Author: eugen
 */

#ifndef H5TYPEFACTORY_HPP_
#define H5TYPEFACTORY_HPP_

extern "C"{
#include <hdf5.h>
}

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/NumericObject.hpp>

namespace nx{
namespace h5{


class H5TypeFactory {
private:
	//from this class we would need a singleton - should be available only
	//once at runtime - most probably as a global object.
	typedef struct {
		pni::utils::Float32 r;
		pni::utils::Float32 i;

	} _struct_complex_32;  //!< C structure for a 32Bit complex type
	typedef struct {
		pni::utils::Float64 r;
		pni::utils::Float64 i;
	} _struct_complex_64;  //!< C structure for a 64Bit complex type

	typedef struct {
		pni::utils::Float128 r;
		pni::utils::Float128 i;
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
public:
	//! default constructor
	H5TypeFactory();
	//! destructor
	virtual ~H5TypeFactory();

	//! create a new type (based on an existing one)
	template<typename T> hid_t createType() const;
	//! get an already existing type object
	template<typename T> hid_t getType() const;
	//! create a type from an existing NumericObject
	hid_t createTypeFromObject(const pni::utils::NumericObject::sptr o);
	//! get the type from an existing NumericObject
	hid_t getTypeFromObject(const pni::utils::NumericObject::sptr o);

	//! get a type according to the type id
	hid_t getTypeFromID(pni::utils::PNITypeID id);
	//! create a new type according to its type id
	hid_t createTypeFromID(pni::utils::PNITypeID id);
	hid_t createStringType(pni::utils::UInt64 size);
};

static H5TypeFactory H5TFactory;

//end of namespace
}
}



#endif /* H5TYPEFACTORY_HPP_ */
