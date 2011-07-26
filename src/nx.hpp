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
#include "h5/NXFileH5Implementation.hpp"
//#include "NXObjectH5Implementation.hpp"
//#include "NXFileXMLImplementation.hpp"
#include "h5/NXGroupH5Implementation.hpp"
#include "h5/NXFieldH5Implementation.hpp"
#include "h5/H5TypeFactory.hpp"
#include "h5/H5Exceptions.hpp"

namespace pni{
namespace nx{
namespace h5{

typedef nx::NXObject<NXObjectH5Implementation> NXObject;
typedef nx::NXFile<NXFileH5Implementation> NXFile;
typedef nx::NXGroup<NXGroupH5Implementation> NXGroup;
typedef nx::NXField<NXFieldH5Implementation> NXField;




}
}
}


#endif /* NX_HPP_ */
