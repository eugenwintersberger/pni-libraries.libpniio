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
	NXFileH5Implementation();
	virtual ~NXFileH5Implementation();

	virtual void open(const char *n,bool overwrite);
	virtual void create(const char *n,bool overwrite);
	virtual void close();
	void flush();
};


//end of namespace
}
}
}

#endif /* NXFILEH5IMPLEMENTATION_HPP_ */
