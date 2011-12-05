/*
 * Declaration Nexus implementation type maps
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
 * Declaration of Nexus implementation type maps
 *
 * Created on: Jul 3, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXIMPMAP_HPP_
#define NXIMPMAP_HPP_

#include "NXImpCode.hpp"

#include "h5/NXObjectH5Implementation.hpp"
#include "h5/NXFileH5Implementation.hpp"
#include "h5/NXGroupH5Implementation.hpp"
#include "h5/NXFieldH5Implementation.hpp"
#include "h5/NXSelectionH5Implementation.hpp"
#include "h5/NXNumericFieldH5Implementation.hpp"
#include "h5/NXStringFieldH5Implementation.hpp"

namespace pni{
namespace nx{
template<ImpCodes c>
class NXImpMap{
public:
	typedef void ObjectImplementation;
	typedef void GroupImplementation;
	typedef void FileImplementatoin;
	typedef void NumericFieldImplementation;
	typedef void StringFieldImplementation;
	typedef void FieldImplementation;
	typedef void SelectionImplementation;

};

template<> class NXImpMap<HDF5>{
public:
	typedef pni::nx::h5::NXObjectH5Implementation ObjectImplementation;
	typedef pni::nx::h5::NXFileH5Implementation FileImplementation;
	typedef pni::nx::h5::NXGroupH5Implementation GroupImplementation;
	typedef pni::nx::h5::NXFieldH5Implementation FieldImplementation;
	typedef pni::nx::h5::NXSelectionH5Implementation SelectionImplementation;
	typedef pni::nx::h5::NXNumericFieldH5Implementation NumericFieldImplementation;
	typedef pni::nx::h5::NXStringFieldH5Implementation StringFieldImplementation;
};

}
}


#endif /* NXIMPMAP_HPP_ */
