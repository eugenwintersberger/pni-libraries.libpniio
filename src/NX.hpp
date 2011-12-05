/*
 * Declaration of types
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
 * Declaration of types - the basic header file to use libpninx.
 *
 * Created on: Jul 1, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NX_HPP_
#define NX_HPP_

#include "NXFile.hpp"
//#include "NXObject.hpp"
#include "NXGroup.hpp"
#include "NXFilter.hpp"
#include "NXNumericField.hpp"
#include "h5/NXFileH5Implementation.hpp"
#include "h5/NXGroupH5Implementation.hpp"
#include "h5/NXFieldH5Implementation.hpp"
#include "h5/H5TypeFactory.hpp"
#include "h5/H5Exceptions.hpp"
#include "h5/H5LibrarySetup.hpp"
#include "h5/H5Filter.hpp"
#include "h5/H5LZFFilter.hpp"
#include "h5/H5DeflateFilter.hpp"
#include "h5/NXSelectionH5Implementation.hpp"

#include "h5/NXNumericFieldH5Implementation.hpp"
#include "h5/NXStringFieldH5Implementation.hpp"
#include "h5/NXBinaryFieldH5Implementation.hpp"

//#include "utils/Record.hpp"

namespace pni{
namespace nx{
namespace h5{

typedef pni::nx::NXObject<NXObjectH5Implementation> NXObject;
typedef pni::nx::NXFile<NXFileH5Implementation> NXFile;
typedef pni::nx::NXGroup<NXGroupH5Implementation> NXGroup;
typedef pni::nx::NXField<NXFieldH5Implementation> NXField;
typedef pni::nx::NXNumericField<NXNumericFieldH5Implementation> NXNumericField;
typedef pni::nx::NXStringField<NXStringFieldH5Implementation> NXStringField;
typedef pni::nx::NXBinaryField<NXBinaryFieldH5Implementation> NXBinaryField;
typedef pni::nx::NXFilter<H5LZFFilter> NXLZFFilter;
typedef pni::nx::NXFilter<H5DeflateFilter> NXDeflateFilter;
typedef pni::nx::NXSelection<NXSelectionH5Implementation> NXSelection;
//typedef pni::nx::Record<NXField> Record;

}
}
}


#endif /* NX_HPP_ */
