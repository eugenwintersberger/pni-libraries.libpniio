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

#include "h5/H5AttributeObject.hpp"
#include "h5/H5File.hpp"
#include "h5/H5Group.hpp"
#include "h5/H5Dataset.hpp"
#include "h5/H5Selection.hpp"
#include "h5/H5Filter.hpp"
#include "h5/H5Attribute.hpp"

namespace pni{
    namespace nx{



        //! \ingroup util_classes
        //! \brief implementation map

        //! For each backend a particular class must be provided to implement 
        //! one of the low level nexus objects.
        template<ImpCode c> class NXImpMap{
            public:
                typedef void ObjectImpl;
                typedef void GroupImpl;
                typedef void FileImpl;
                typedef void FieldImpl;
                typedef void SelectionImpl;
                typedef void FilterImpl;
                typedef void AttributeImpl;
            };

        //! \cond NO_API_DOC

        //set implementation types for the HDF5 implementation
        template<> class NXImpMap<ImpCode::HDF5>{
            public:
                typedef pni::nx::h5::H5AttributeObject  ObjectImpl;
                typedef pni::nx::h5::H5File             FileImpl;
                typedef pni::nx::h5::H5Group            GroupImpl;
                typedef pni::nx::h5::H5Dataset          FieldImpl;
                typedef pni::nx::h5::H5Selection        SelectionImpl;
                typedef pni::nx::h5::H5Filter           FilterImpl;
                typedef pni::nx::h5::H5Attribute        AttributeImpl;
        };
        //! \endcond

    }
}


#endif /* NXIMPMAP_HPP_ */
