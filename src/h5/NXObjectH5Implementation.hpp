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

namespace pni{
namespace nx{
namespace h5{

using namespace pni::utils;

class NXObjectH5Implementation {
private:
	void _create_and_write_attribute(hid_t pid,const char *n,hid_t type_id,
			                         hid_t space_id,void *ptr);
	void _open_attribute(hid_t pid,const char *n,hid_t &attr_id,hid_t &type_id,
			             hid_t &space_id);
	//! copy constructor
	NXObjectH5Implementation(const NXObjectH5Implementation &o){}
protected:
	hid_t  _id;    //!< ID of the object this class referes too
	hid_t  _pid;   //!< ID of the parent object owning this object
	//String _name;  //!< the name of the object
public:
	typedef boost::shared_ptr<NXObjectH5Implementation> sptr;
	static const ImpCodes IMPCODE = HDF5;
	//! default constructor
	NXObjectH5Implementation();

	//! destructor
	virtual ~NXObjectH5Implementation();

	//! assignment operator
	NXObjectH5Implementation &operator=(const NXObjectH5Implementation &o);

	//! write attribute data from an ArrayObject
	void setAttribute(const char *n,ArrayObject &a);
	//! write attribute data from a ScalarObject
	void setAttribute(const char *n,ScalarObject &s);
	//! write attribute data from a String object
	void setAttribute(const char *n,const String &);

	//! read attribute data to an ArrayObject
	void getAttribute(const char *n,ArrayObject &a);
	//! read attribute data to a ScalarObject
	void getAttribute(const char *n,ScalarObject &s);
	//! read attribute data to a String object
	void getAttribute(const char *n,String &s);

	virtual String getName() const;
	virtual void setParent(hid_t id);
	virtual hid_t getParent() const;
	virtual void create(const String &n){
	}
	virtual void open(const String &n){

	}
};


//end of namespace
}
}
}


/*
template<typename T> void NXObjectH5Implementation::setAttribute(const char *n,typename T::sptr d){
	//raise an exception that this method is not implemented for this data type
	std::cerr<<"Service not supported for this data type in HDF5 implementation!"<<std::endl;
}*/


/*
template<typename T> typename T::sptr getAttribute(const char *n){
	//raise an exception that this method is not implemented for this data type
	std::cerr<<"Service not supported for this data type in HDF5 implementation!"<<std::endl;
}*/



#endif /* NXOBJECTH5IMPLEMENTATION_HPP_ */
