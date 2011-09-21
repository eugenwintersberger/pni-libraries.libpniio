/*
 * nx.hpp
 *
 *  Created on: Jul 1, 2011
 *      Author: eugen
 */

#ifndef NX_HPP_
#define NX_HPP_

#include "NXFile.hpp"
//#include "NXObject.hpp"
#include "NXGroup.hpp"
#include "NXFilter.hpp"
#include "h5/NXFileH5Implementation.hpp"
//#include "NXObjectH5Implementation.hpp"
//#include "NXFileXMLImplementation.hpp"
#include "h5/NXGroupH5Implementation.hpp"
#include "h5/NXFieldH5Implementation.hpp"
#include "h5/H5TypeFactory.hpp"
#include "h5/H5Exceptions.hpp"
#include "h5/H5LibrarySetup.hpp"
#include "h5/H5Filter.hpp"
#include "h5/H5LZFFilter.hpp"
#include "h5/H5DeflateFilter.hpp"
#include "h5/NXSelectionH5Implementation.hpp"

namespace pni{
namespace nx{
namespace h5{

typedef pni::nx::NXObject<NXObjectH5Implementation> NXObject;
typedef pni::nx::NXFile<NXFileH5Implementation> NXFile;
typedef pni::nx::NXGroup<NXGroupH5Implementation> NXGroup;
typedef pni::nx::NXField<NXFieldH5Implementation> NXField;
typedef pni::nx::NXFilter<H5LZFFilter> NXLZFFilter;
typedef pni::nx::NXFilter<H5DeflateFilter> NXDeflateFilter;
typedef pni::nx::NXSelection<NXSelectionH5Implementation> NXSelection;

}
}
}


#endif /* NX_HPP_ */
