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

namespace nx{
namespace h5{


class NXGroupH5Implementation:public NXObjectH5Implementation {
protected:
	hid_t _gcreate_plist;
public:
	typedef boost::shared_ptr<NXGroupH5Implementation> sptr;
	//! default constructor
	NXGroupH5Implementation();
	//! copy constructor
	NXGroupH5Implementation(const NXGroupH5Implementation &o);
	//! default destructor
	virtual ~NXGroupH5Implementation();

	//! assignment operator
	NXGroupH5Implementation &operator=(const NXGroupH5Implementation &o);

	//! create a group
	virtual void createGroup(const char *n,NXGroupH5Implementation &imp);
	//! open a group
	virtual void openGroup(const char *n,NXGroupH5Implementation &imp);
	//! create a field
	virtual void createField(const char *n,pni::utils::PNITypeID tid,
			                 const pni::utils::ArrayShape &s,
			                 NXFieldH5Implementation &imp);
	//! create a field
	virtual void createField(const char *n,pni::utils::PNITypeID tid,
			                 const pni::utils::ArrayShape::sptr s,
			                 NXFieldH5Implementation &imp);
	//! create a field
	virtual void createField(const char *n,pni::utils::PNITypeID tid,
			                 pni::utils::UInt32 rank,
			                 const pni::utils::UInt32 *dims,
			                 NXFieldH5Implementation &imp);
	//! method to create a field for a single scalar value
	virtual void createField(const char *n,pni::utils::PNITypeID,
			                 NXFieldH5Implementation &imp);
	//! create a field to store string data
	virtual void createStringField(const char *n,pni::utils::UInt64 size,
			                       NXFieldH5Implementation &imp);
	//! open an existing field
	virtual void openField(const char *n,NXFieldH5Implementation &imp);
	void close();

};




//end of namespace
}
}


#endif /* NXGROUPH5IMPLEMENTATION_HPP_ */
