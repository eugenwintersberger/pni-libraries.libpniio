/*
 * NXFieldH5Implementation.hpp
 *
 *  Created on: Jul 3, 2011
 *      Author: eugen
 */

#ifndef NXFIELDH5IMPLEMENTATION_HPP_
#define NXFIELDH5IMPLEMENTATION_HPP_

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/NumericObject.hpp>


#include "NXObjectH5Implementation.hpp"
#include "H5TypeFactory.hpp"
#include "../NXFilter.hpp"
#include "../NXSelection.hpp"


using namespace pni::utils;


namespace pni{
namespace nx{
namespace h5{

class NXGroupH5Implementation;

//! \ingroup HDF5 implementation
//! \brief HDF5 implementation of a NXField object

//! A dataset can be treated as a standard STL container where the
//! first dimension runs over the element index.
//! If data of a rank r should be stored a dataset of rank r+1
//! is created where the first dimension if of size H5S_UNLIMITED and
//! thus can be extended along this dimension arbitrarily.


class NXFieldH5Implementation : public NXObjectH5Implementation{
private:
	//! copy constructor
	NXFieldH5Implementation(const NXFieldH5Implementation &){}
	void _get_dataset_parameters(hid_t id);
	void _increment_growth_dimension();
protected:
	//parameters of the total dataset
	hid_t _type_id;	       //!< ID of the data type
	hid_t _space_id;       //!< ID of the data space
	ArrayShape _space_shape;    //!< shape of the total dataset

	//the object should act like a container - this we need a default
	//selection to read and write elements to this container
	hid_t _elem_mem_space; //!< memory data space of the container elements
	hsize_t *_elem_offset;   //!< container offset
	hsize_t *_elem_count;    //!< size of the container elements
	ArrayShape _elem_shape; //!< shape of the element

	//resize buffer
	hsize_t *_resize_buffer; //!< an internal buffer for resizing the array
public:
	typedef boost::shared_ptr<NXFieldH5Implementation> sptr;
	//! default constructor
	NXFieldH5Implementation();
	//! default destructor
	virtual ~NXFieldH5Implementation();

	//! assignment operator
	NXFieldH5Implementation &operator=(const NXFieldH5Implementation &o);

	//! total field rank
	virtual UInt32 getRank() const;
	//! total field dimensions
	virtual UInt32 getDimension(UInt32 i) const;
	//! total field number of elements
	virtual UInt64 getSize() const;
	//! total field shape
	virtual const ArrayShape &getShape() const;

	//! rank of field element
	virtual UInt32 getElementRank() const;
	//! dimension of field element
	virtual UInt32 getElementDimension(UInt32 i) const;
	//! number of elements in element
	virtual UInt64 getElementSize() const;
	//! element shape
	virtual const ArrayShape &getElementShape() const;


	virtual PNITypeID getTypeID() const;
	virtual bool isScalar() const;
	virtual bool isArray() const;
	virtual bool isString() const;

	virtual void append(const NumericObject &o);
	virtual void append(const String &s);

	virtual void insert(const UInt64 &i,const NumericObject &a);
	virtual void insert(const UInt64 &i,const String &s);

	virtual void get(const UInt64 &i,NumericObject &s);
	virtual void get(const UInt64 &i,String &s);


	//! close the data field
	virtual void close();


	virtual void setId(const hid_t &id);

	friend class NXGroupH5Implementation;
};


//end of namespace
}
}
}

#endif /* NXFIELDH5IMPLEMENTATION_HPP_ */
