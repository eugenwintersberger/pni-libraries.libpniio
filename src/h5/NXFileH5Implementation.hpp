/*
 * NXFileH5Implementation.hpp
 *
 *  Created on: Jun 30, 2011
 *      Author: eugen
 */

#ifndef NXFILEH5IMPLEMENTATION_HPP_
#define NXFILEH5IMPLEMENTATION_HPP_

extern "C"{
#include <hdf5.h>
}

#include "NXObjectH5Implementation.hpp"
#include "NXGroupH5Implementation.hpp"

namespace pni{
namespace nx{
namespace h5{


//! HDF5 implementation of a file
class NXFileH5Implementation:public NXGroupH5Implementation {
private:
	NXFileH5Implementation(const NXFileH5Implementation &){}
	NXFileH5Implementation &operator=(const NXFileH5Implementation &){
		return *this;
	}
protected:
	hid_t _create_plist; //!< property list for file creation
	hid_t _acc_plist;    //!< property list for file access
public:
	//! default constructor
	NXFileH5Implementation();
	//! move constructor
	NXFileH5Implementation(NXFileH5Implementation &&o);
	//! destructor
	virtual ~NXFileH5Implementation();

	//! move assignment
	NXFileH5Implementation &operator=(NXFileH5Implementation &&o);

	virtual NXObjectH5Implementation open(const String &n){
		return NXGroupH5Implementation::open(n);
	}
	virtual void open(const char *n,bool overwrite);
	virtual void create(const char *n,bool overwrite,UInt64 ssize);
	virtual void close();
	virtual void flush() const;
};


//end of namespace
}
}
}

#endif /* NXFILEH5IMPLEMENTATION_HPP_ */
