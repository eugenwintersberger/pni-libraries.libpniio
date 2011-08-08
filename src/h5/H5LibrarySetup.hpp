/*
 * H5LibrarySetup.hpp
 *
 *  Created on: Aug 4, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef H5LIBRARYSETUP_HPP_
#define H5LIBRARYSETUP_HPP_

extern "C"{
#include <hdf5.h>
}

#include <pni/utils/PNITypes.hpp>

using namespace pni::utils;

namespace pni {
namespace nx {
namespace h5 {

class H5LibrarySetup {
private:
	UInt32 _major_version_number;
	UInt32 _minor_version_number;
	UInt32 _release_number;

	bool _verbose;

public:
	H5LibrarySetup();
	virtual ~H5LibrarySetup();

	String getVersionString() const;
	UInt32 getMajorVersionNumber() const;
	UInt32 getMinorVersionNumber() const;
	UInt32 getReleaseNumber() const;
	void setVerbose(bool f) { _verbose = f; }
	bool isVerbose() const { return _verbose; }
};

//global setup of the library - should be implemented as a singleton in future
static H5LibrarySetup H5Setup;


//end of namespace
}
}
}


#endif /* H5LIBRARYSETUP_HPP_ */
