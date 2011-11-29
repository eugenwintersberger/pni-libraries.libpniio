/*
 * NXFieldH5Implementation.hpp
 *
 *  Created on: Jul 3, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef NXFIELDH5IMPLEMENTATION_HPP_
#define NXFIELDH5IMPLEMENTATION_HPP_

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/NumericObject.hpp>


#include "NXObjectH5Implementation.hpp"
#include "H5TypeFactory.hpp"


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

	void _get_dataset_parameters(hid_t id);
	void _increment_growth_dimension();
protected:
	//parameters of the total dataset
	hid_t _type_id;	          //!< ID of the data type
	hid_t _space_id;          //!< ID of the data space
	ArrayShape _space_shape;  //!< shape of the total dataset

	//the object should act like a container - this we need a default
	//selection to read and write elements to this container
	hid_t _elem_mem_space;   //!< memory data space of the container elements
	hsize_t *_elem_offset;   //!< container offset
	hsize_t *_elem_count;    //!< size of the container elements
	ArrayShape _elem_shape;  //!< shape of the element

	//resize buffer
	hsize_t *_resize_buffer; //!< an internal buffer for resizing the array
public:
	//! a shared pointer to a field object
	//typedef boost::shared_ptr<NXFieldH5Implementation> sptr;
	//! default constructor
	NXFieldH5Implementation();
	//! copy constructor
	NXFieldH5Implementation(const NXFieldH5Implementation &);
	//! move constructor
	NXFieldH5Implementation(NXFieldH5Implementation &&o);
	//! default destructor
	virtual ~NXFieldH5Implementation();

	//! copy assignment operator
	NXFieldH5Implementation &operator=(const NXFieldH5Implementation &o);
	//! move assignment operator
	NXFieldH5Implementation &operator=(NXFieldH5Implementation &&o);

	//! get the total shape of the container
	virtual const ArrayShape &getShape() const;

	//! element shape
	virtual const ArrayShape &getElementShape() const;

	//! return the type ID of the field
	virtual PNITypeID getTypeID() const;

	//! true if scalar field
	virtual bool isScalar() const;
	//! true if array field
	virtual bool isArray() const;
	//! true if a string field
	virtual bool isString() const;

	//! append a numeric object
	virtual void append(const NumericObject &o);
	//! append a string
	virtual void append(const String &s);

	//! insert a numeric object
	virtual void insert(const UInt64 &i,const NumericObject &a);
	//! insert a string object
	virtual void insert(const UInt64 &i,const String &s);

	//! get a numeric object
	virtual void get(const UInt64 &i,NumericObject &s);
	//! get a string object
	virtual void get(const UInt64 &i,String &s);


	//! close the data field
	virtual void close();

	//! set HDF5 object ID
	virtual void setId(const hid_t &id);

	friend class NXGroupH5Implementation;
};


//end of namespace
}
}
}

#endif /* NXFIELDH5IMPLEMENTATION_HPP_ */
