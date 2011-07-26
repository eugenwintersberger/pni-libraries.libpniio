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

namespace nx{
namespace h5{


//! HDF5 implementation of a file
class NXFileH5Implementation:public NXGroupH5Implementation {
protected:
	hid_t _create_plist; //!< property list for file creation
	hid_t _acc_plist;    //!< property list for file access
	//hid_t _fid;           //!< ID of the file

public:
	NXFileH5Implementation();
	virtual ~NXFileH5Implementation();

	void open(const char *n,bool overwrite);
	void create(const char *n,bool overwrite);
	void close();
};


//end of namespace
}
}


#endif /* NXFILEH5IMPLEMENTATION_HPP_ */
