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
private:
	//! copy constructor
	NXFieldH5Implementation(const NXFieldH5Implementation &){}
protected:
	hid_t _type_id;	       //!< ID of the data type
	hid_t _space_id;       //!< ID of the data space
	hid_t _creation_plist; //!< ID creation property list
public:
	typedef boost::shared_ptr<NXFieldH5Implementation> sptr;
	//! default constructor
	NXFieldH5Implementation();
	//! default destructor
	virtual ~NXFieldH5Implementation();

	//! assignment operator
	NXFieldH5Implementation &operator=(const NXFieldH5Implementation &o);

	//setup chunk for the array
	void setChunkedLayout();
	void setChunkSize(int rank,hsize_t *dims);

	//setup the dataspace
	void setDataSpace(UInt32 rank,const UInt32 *dims);
	void setDataSpace();

	//setup the data type
	void setDataType(PNITypeID id);
	void setDataType(const String &n);

	virtual UInt32 getRank() const;
	virtual UInt32 getDimension(UInt32 i) const;
	virtual UInt32* getDimensions() const;
	virtual UInt64 getSize() const;
	virtual void getShape(ArrayShape &s) const;
	virtual PNITypeID getTypeID() const;
	virtual bool isScalar() const;
	virtual bool isArray() const;
	virtual bool isString() const;

	//! write data from a void pointer
	virtual void write(const void *ptr);

	//! read data to a void pointer
	virtual void read(void *ptr) const;

	//! close the data field
	virtual void close();

	//! create a field implementation
	virtual void create(const String &n);

	//! open a field implementation
	virtual void open(const String &n);

	friend class NXGroupH5Implementation;
};


//end of namespace
}
}
}

#endif /* NXFIELDH5IMPLEMENTATION_HPP_ */
