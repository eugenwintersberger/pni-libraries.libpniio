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

#include "NXObject.hpp"
#include "NXFile.hpp"
#include "NXGroup.hpp"
#include "NXField.hpp"
#include "NXDeflateFilter.hpp"
#include "NXAttribute.hpp"

#include "h5/H5AttributeObject.hpp"
#include "h5/H5File.hpp"
#include "h5/H5Group.hpp"
#include "h5/H5Dataset.hpp"
#include "h5/H5Exceptions.hpp"
#include "h5/H5Attribute.hpp"
#include "h5/H5LibrarySetup.hpp"
#include "h5/H5Filter.hpp"
#include "h5/H5DeflateFilter.hpp"

namespace pni{
namespace nx{
namespace h5{

            typedef pni::nx::NXObject<H5AttributeObject>    NXObject;
            typedef pni::nx::NXFile<H5File>                 NXFile;
            typedef pni::nx::NXGroup<H5Group>               NXGroup;
            typedef pni::nx::NXField<H5Dataset>             NXField;
            typedef pni::nx::NXFilter<H5Filter>             NXFilter;
            typedef pni::nx::NXDeflateFilter<H5DeflateFilter> NXDeflateFilter;
            typedef pni::nx::NXAttribute<H5Attribute>  NXAttribute;

//end of namespace
}
}
}


#endif /* NX_HPP_ */
