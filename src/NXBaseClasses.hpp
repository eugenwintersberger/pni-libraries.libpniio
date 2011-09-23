/*
 * NXBaseClasses.hpp
 *
 *  Created on: Sep 23, 2011
 *      Author: eugen
 */

#ifndef NXBASECLASSES_HPP_
#define NXBASECLASSES_HPP_

#include "NX.hpp"
#include "base_classes/NXroot.hpp"
#include "base_classes/NXentry.hpp"

namespace pni{
namespace nx{
namespace h5{

typedef pni::nx::NXroot<NXFile> NXroot;
typedef pni::nx::NXentry<NXGroup> NXentry;

//end of namespace
}
}
}




#endif /* NXBASECLASSES_HPP_ */
