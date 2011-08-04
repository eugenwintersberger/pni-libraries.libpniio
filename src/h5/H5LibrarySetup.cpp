/*
 * H5LibrarySetup.cpp
 *
 *  Created on: Aug 4, 2011
 *      Author: Eugen Wintersberger
 */

#include "H5LibrarySetup.hpp"

#include "filters/lzf_filter.h"

namespace pni {
namespace nx {
namespace h5 {

H5LibrarySetup::H5LibrarySetup() {
	H5open();
	H5get_libversion(&_major_version_number,&_minor_version_number,&_release_number);

	//register custom filters to the library
	register_lzf();

}

H5LibrarySetup::~H5LibrarySetup() {
	H5garbage_collect();
	H5close();
}
String H5LibrarySetup::getVersionString() const{
	String vstr;

	return vstr;
}

UInt32 H5LibrarySetup::getMajorVersionNumber() const{
	return _major_version_number;
}

UInt32 H5LibrarySetup::getMinorVersionNumber() const{
	return _minor_version_number;
}

UInt32 H5LibrarySetup::getReleaseNumber() const{
	return _release_number;
}

//end of namespace
}
}
}
