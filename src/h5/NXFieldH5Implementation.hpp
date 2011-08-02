/*
 * NXFieldH5Implementation.hpp
 *
 *  Created on: Jul 3, 2011
 *      Author: eugen
 */

#ifndef NXFIELDH5IMPLEMENTATION_HPP_
#define NXFIELDH5IMPLEMENTATION_HPP_

#include <pni/utils/PNITypes.hpp>


#include "NXObjectH5Implementation.hpp"
#include "H5TypeFactory.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{
namespace h5{

class NXGroupH5Implementation;

class NXFieldH5Implementation : public NXObjectH5Implementation{
protected:
	hid_t _type_id;	  //!< ID of the data type
	hid_t _space_id;  //!< ID of the data space
public:
	typedef boost::shared_ptr<NXFieldH5Implementation> sptr;
	//! default constructor
	NXFieldH5Implementation();
	//! copy constructor
	NXFieldH5Implementation(const NXFieldH5Implementation &);
	//! default destructor
	virtual ~NXFieldH5Implementation();

	//! assignment operator
	NXFieldH5Implementation &operator=(const NXFieldH5Implementation &o);

	virtual UInt32 getRank();
	virtual UInt32 getDimension(UInt32 i);
	virtual UInt64 getSize();

	//! write scalar data to a field
	virtual void write(ScalarObject &s);
	//! write array data to a field
	virtual void write(ArrayObject &s);
	//! write a string to a field
	virtual void write(String &s);

	//! read a scalar object from a field
	virtual void read(ScalarObject &s);
	//! read array data from a field
	virtual void read(ArrayObject &s);
	//! read a string from a field
	virtual void read(String &s);

	//! close the data field
	virtual void close();

	friend class NXGroupH5Implementation;
};


//end of namespace
}
}
}

#endif /* NXFIELDH5IMPLEMENTATION_HPP_ */
