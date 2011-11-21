/*
 * Declaration and instantiation of Nexus base classes
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Declaration and instantiation of Nexus base classes.
 *
 * Created on: Sep 23, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXBASECLASSES_HPP_
#define NXBASECLASSES_HPP_

#include "NX.hpp"
#include "base_classes/NXroot.hpp"
#include "base_classes/NXStandardGroup.hpp"
#include "base_classes/NXentry.hpp"

namespace pni{
namespace nx{
namespace h5{

typedef pni::nx::NXroot<NXFile> NXroot;
typedef pni::nx::NXStandardGroup<NXGroup> NXStandardGroup;
typedef pni::nx::NXentry<NXStandardGroup> NXentry;


//end of namespace
}
}
}




#endif /* NXBASECLASSES_HPP_ */
