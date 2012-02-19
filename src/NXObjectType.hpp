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
 * Definition of a enum class for object types.
 *
 * Created on: Feb 19, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __NXOBJECTYPE_HPP__
#define __NXOBJECTYPE_HPP__

namespace pni{
    namespace nx{

        //! \ingroup nx_utilities
        //! \brief Nexus typd ids

        //! This enumeration class provides identifiers for 
        //! different Nexus types. Basically there are only two 
        //! types: fields and groups. 
        enum class NXObjectType { NXFIELD, //!< NXField identifier
                                  NXGROUP, //!< NXGroup identifier
                                  NXNONE   //!< no valid Nexus object
                                };

        //end of namespace
    }
}

#endif
