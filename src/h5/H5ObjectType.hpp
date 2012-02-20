/*
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
 * Enum type for HDF5 object type.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __H5OBJECTTYPE_HPP__
#define __H5OBJECTTYPE_HPP__

//! \ingroup nxh5_classes 
//! \brief HDF5 object type enumerations

//! This enumeration class defines type-codes for different kinds
//! of HDF5 objects. As all HDF5 objects are derived from H5Object
//! an thus can be convereted into such an object we need this
//! codes to identify the particular object type of an 
//! instance of H5Object.
enum class H5ObjectType {FILE,       //!< HDF5 file code
                         GROUP,      //!< HDF5 group code
                         DATATYPE,   //!< HDF5 datatype code
                         DATASPACE,  //!< HDF5 dataspace code
                         DATASET,    //!< HDF5 dataset code
                         ATTRIBUTE,  //!< HDF5 attribute
                         BADID       //!< unknown object
                        };

#endif

