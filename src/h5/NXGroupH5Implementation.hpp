/*
 * NXGroupH5Implementation.hpp
 *
 *  Created on: Jul 1, 2011
 *      Author: eugen
 */

#ifndef NXGROUPH5IMPLEMENTATION_HPP_
#define NXGROUPH5IMPLEMENTATION_HPP_

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/ArrayShape.hpp>

#include "NXObjectH5Implementation.hpp"
#include "NXFieldH5Implementation.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{
namespace h5{


class NXGroupH5Implementation:public NXObjectH5Implementation {
private:
	//! copy constructor
	NXGroupH5Implementation(const NXGroupH5Implementation &o){}
protected:
	hid_t _gcreate_plist;
public:
	typedef boost::shared_ptr<NXGroupH5Implementation> sptr;
	//! default constructor
	NXGroupH5Implementation();

	//! default destructor
	virtual ~NXGroupH5Implementation();

	//! assignment operator
	NXGroupH5Implementation &operator=(const NXGroupH5Implementation &o);

	//! create a group
	virtual void createGroup(const char *n, NXGroupH5Implementation &imp);
	//! open a group
	virtual void openGroup(const char *n, NXGroupH5Implementation &imp);
	//! create a field
	virtual void createField(const char *n, PNITypeID tid, const ArrayShape &s,
			                 NXFieldH5Implementation &imp);
	//! create a field
	virtual void createField(const char *n,PNITypeID tid,
			                 const ArrayShape::sptr s,
			                 NXFieldH5Implementation &imp);
	//! create a field
	virtual void createField(const char *n, PNITypeID tid, UInt32 rank,
			                 const UInt32 *dims, NXFieldH5Implementation &imp);
	//! method to create a field for a single scalar value
	virtual void createField(const char *n,PNITypeID,
			                 NXFieldH5Implementation &imp);
	//! create a field to store string data
	virtual void createStringField(const char *n,UInt64 size,
			                       NXFieldH5Implementation &imp);
	//! open an existing field
	virtual void openField(const char *n,NXFieldH5Implementation &imp);
	void close();

	virtual void create(const String &name);
	virtual void open(const String &name);

};




//end of namespace
}
}
}


#endif /* NXGROUPH5IMPLEMENTATION_HPP_ */
