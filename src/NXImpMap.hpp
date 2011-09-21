/*
 * NXImpMap.hpp
 *
 *  Created on: Jul 3, 2011
 *      Author: eugen
 */

#ifndef NXIMPMAP_HPP_
#define NXIMPMAP_HPP_

#include "NXImpCode.hpp"

#include "h5/NXObjectH5Implementation.hpp"
#include "h5/NXFileH5Implementation.hpp"
#include "h5/NXGroupH5Implementation.hpp"
#include "h5/NXFieldH5Implementation.hpp"
#include "h5/NXSelectionH5Implementation.hpp"

namespace pni{
namespace nx{
template<ImpCodes c>
class NXImpMap{
public:
	typedef void ObjectImplementation;
	typedef void GroupImplementation;
	typedef void FileImplementatoin;
	typedef void FieldImplementation;
	typedef void SelectionImplementation;

};

template<> class NXImpMap<HDF5>{
public:
	typedef nx::h5::NXObjectH5Implementation ObjectImplementation;
	typedef nx::h5::NXFileH5Implementation FileImplementation;
	typedef nx::h5::NXGroupH5Implementation GroupImplementation;
	typedef nx::h5::NXFieldH5Implementation FieldImplementation;
	typedef nx::h5::NXSelectionH5Implementation SelectionImplementation;
};

}
}


#endif /* NXIMPMAP_HPP_ */
