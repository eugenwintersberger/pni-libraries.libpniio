/*
 * NXGroupH5Implementation.hpp
 *
 *  Created on: Jul 1, 2011
 *      Author: eugen
 */

#ifndef NXGROUPH5IMPLEMENTATION_HPP_
#define NXGROUPH5IMPLEMENTATION_HPP_

#include <pni/utils/Types.hpp>
#include <pni/utils/Shape.hpp>
#include <pni/utils/Exceptions.hpp>

#include "NXObjectH5Implementation.hpp"
#include "NXFieldH5Implementation.hpp"
#include "NXNumericFieldH5Implementation.hpp"
#include "NXStringFieldH5Implementation.hpp"
#include "NXBinaryFieldH5Implementation.hpp"
#include "H5Filter.hpp"
#include "H5Exceptions.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{
namespace h5{


class NXGroupH5Implementation:public NXObjectH5Implementation {
private:

public:
	typedef boost::shared_ptr<NXGroupH5Implementation> sptr;
	//! default constructor
	NXGroupH5Implementation();
	//! copy constructor
	NXGroupH5Implementation(const NXGroupH5Implementation &o);
	//! copy conversion constructor
	NXGroupH5Implementation(const NXObjectH5Implementation &o);
	//! move conversion constructor
	NXGroupH5Implementation(NXObjectH5Implementation &&o);
	//! move constructor
	NXGroupH5Implementation(NXGroupH5Implementation &&o);

	//! default destructor
	virtual ~NXGroupH5Implementation();

	//! copy assignment operator
	NXGroupH5Implementation &operator=(const NXGroupH5Implementation &o);
	//! copy conversion assignment
	NXGroupH5Implementation &operator=(const NXObjectH5Implementation &o);
	//! move assignment operator
	NXGroupH5Implementation &operator=(NXGroupH5Implementation &&o);
	//! move conversion assignment
	NXGroupH5Implementation &operator=(NXObjectH5Implementation &&o);

	//! create a new group below this group
	virtual NXGroupH5Implementation createGroup(const String &n) const;

	//! create a field

	//! create a field
	NXNumericFieldH5Implementation createNumericField(const String &n, TypeID tid,const Shape &s) const;

	NXNumericFieldH5Implementation createNumericField(const String &n, TypeID tid,const Shape &s,const H5Filter &f) const;

	//! method to create a field for a single scalar value
	NXNumericFieldH5Implementation createNumericField(const String &n,TypeID) const;
	//! create a field to store string data
	NXStringFieldH5Implementation createStringField(const String &n) const;
	//! create a field to store binary data
	NXBinaryFieldH5Implementation createBinaryField(const String &n) const;

	//! open an existing object
	virtual NXObjectH5Implementation open(const String &n) const;

	//! remove an object from the HDF5 tree
	virtual void remove(const String &n) const;
	//! check for the existence of an object
	virtual bool exists(const String &n) const;

};


//end of namespace
}
}
}


#endif /* NXGROUPH5IMPLEMENTATION_HPP_ */
