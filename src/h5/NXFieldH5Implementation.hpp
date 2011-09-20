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
#include "../NXFilter.hpp"

using namespace pni::utils;


namespace pni{
namespace nx{
namespace h5{

class NXGroupH5Implementation;

//! \ingroup HDF5 implementation
//! \brief HDF5 implementation of a NXField object

//! This class provides an interface to an HDF5 dataset structure.
//! While a group object can be easily constructed during instantiation,
//! a data set object cannot. There are a lot of things that must be set up
//! at runtime before object construction is finished.


class NXFieldH5Implementation : public NXObjectH5Implementation{
private:
	//! copy constructor
	NXFieldH5Implementation(const NXFieldH5Implementation &){}
protected:
	hid_t _type_id;	       //!< ID of the data type
	hid_t _space_id;       //!< ID of the data space
	hid_t _creation_plist; //!< ID creation property list

	//the following tow data spaces are required to make use
	//of selections
	hid_t _mem_space; //!< data space in memory
	hsize_t *_offset;
	hsize_t *_count;

	void _allocate_selection_buffers(UInt32 n);
	void _free_selection_buffers();

	virtual void create(const String &n,const NXObjectH5Implementation &o);
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
	void setChunkSize(UInt32 rank,const UInt32 *dims);
	void setChunkSize(const ArrayShape &s);

	//setup the dataspace
	void setDataSpace(UInt32 rank,const UInt32 *dims);
	//set array data space
	void setDataSpace(const ArrayShape &s);
	//set scalar data space
	void setDataSpace();

	//setup the data type for PNITypes
	void setDataType(PNITypeID id);
	//setup the data type for strings
	void setDataType(UInt64 size);

	template<typename Imp> void setFilter(pni::nx::NXFilter<Imp> &f){
		f.setup(_creation_plist);
	}

	void setShuffle(){
		H5Pset_shuffle(_creation_plist);
	}

	void setSelection(const Selection &s);
	void resetSelection();

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

	//! open a field implementation
	virtual void open(const String &n,NXObjectH5Implementation &imp);

	friend class NXGroupH5Implementation;
};


//end of namespace
}
}
}

#endif /* NXFIELDH5IMPLEMENTATION_HPP_ */
