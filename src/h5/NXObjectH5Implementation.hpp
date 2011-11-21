/*
 * NXObjectH5Implementation.hpp
 *
 *  Created on: Jul 1, 2011
 *      Author: eugen
 */

#ifndef NXOBJECTH5IMPLEMENTATION_HPP_
#define NXOBJECTH5IMPLEMENTATION_HPP_

extern "C" {
#include <hdf5.h>
}

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/Scalar.hpp>
#include <pni/utils/ScalarObject.hpp>
#include <pni/utils/ArrayObject.hpp>
#include <pni/utils/Array.hpp>

#include "H5TypeFactory.hpp"
#include "../NXImpCode.hpp"
#include "../NXTypes.hpp"

namespace pni{
namespace nx{
namespace h5{


using namespace pni::utils;
//! \ingroup HDF5 Implementation
//! \brief Implementation of an NXObject

//! This object basically implements the basic functionality of an NXObject.
//! You can
//! - set and get attributes
//! - and obtain the name of an object

class NXObjectH5Implementation {
private:
	void _create_and_write_attribute(hid_t pid,const char *n,hid_t type_id,
			                         hid_t space_id,const void *ptr) const;
	void _open_attribute(const hid_t &pid,const char *n,hid_t &attr_id,
			             hid_t &type_id,hid_t &space_id) const;

	hid_t  _id;    //!< handler of the object this class referes too
protected:
	//! default constructor
	NXObjectH5Implementation();
public:
	typedef boost::shared_ptr<NXObjectH5Implementation> sptr;
	static const ImpCodes IMPCODE = HDF5;

	//! destructor
	virtual ~NXObjectH5Implementation();

	//! copy constructor
	NXObjectH5Implementation(const NXObjectH5Implementation &);
	//! move constructor
	NXObjectH5Implementation(NXObjectH5Implementation &&o);

	//! copy assignment operator

	//! HDF5 objects can be assigned to each other - the basic idea is that
	//! the new object holds a reference to an already existing object.
	NXObjectH5Implementation &operator=(const NXObjectH5Implementation &o);

	//! move assignment operator
	NXObjectH5Implementation &operator=(NXObjectH5Implementation &&o);

	//move here all char * arguments to String in order to
	//make the interfaces more homogeneous

	//! write attribute data from an ArrayObject
	void setAttribute(const String &n,const ArrayObject &a) const;
	//! write attribute data from a ScalarObject
	void setAttribute(const String &n,const ScalarObject &s) const;
	//! write attribute data from a String object
	void setAttribute(const String &n,const String &) const;

	//! read attribute data to an ArrayObject
	void getAttribute(const String &n,ArrayObject &a) const;
	//! read attribute data to a ScalarObject
	void getAttribute(const String &n,ScalarObject &s) const;
	//! read attribute data to a String object
	void getAttribute(const String &n,String &s) const;

	//! get object path
	virtual String getPath() const;
	//! get object path base
	virtual String getBase() const;
	//! get object name
	virtual String getName() const;
	//! close the object
	virtual void close();
	//! check if open
	virtual bool isOpen() const;
	//! return the object class
	virtual pni::nx::NXObjectClass getObjectClass() const;

	//! get object ID
	//should be moved to protected and thus not exposed to the public
	//interface of the class
	inline hid_t getId() const{
		return _id;
	}

	//! set object ID
	//should be moved to protected and thus not be exposed to the public
	//interface of the class
	inline void setId(hid_t id){
		//if the object has already a valid ID we need to decrement the
		//reference counter on this object - the object will be destroyed
		//if its reference counter approaches 0
		if(H5Iis_valid(_id)) H5Idec_ref(_id);

		//set _id to its new value
		//we need to check if we maybe must increment the reference counter
		//of the object refered to by id
		_id = id;
	}

	virtual void createLink(const NXObjectH5Implementation &pos,const String &n) const;
	virtual void createLink(const String &path) const;

};


//end of namespace
}
}
}




#endif /* NXOBJECTH5IMPLEMENTATION_HPP_ */
