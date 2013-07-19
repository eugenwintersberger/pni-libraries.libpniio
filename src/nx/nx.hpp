/*
 * Declaration of types
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Declaration of types - the basic header file to use libpniio.
 *
 * Created on: Jul 1, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "nxobject.hpp"
#include "nxfile.hpp"
#include "nxgroup.hpp"
#include "nxfield.hpp"
#include "nxdeflate_filter.hpp"
#include "nxattribute.hpp"
#include "nximp_code.hpp"
#include "nximp_code_map.hpp"
#include "nxobject_traits.hpp"


#include "nx_hdf5_implementation.hpp"


namespace pni{
namespace io{
namespace nx{

    DECLARE_NXOBJECT_TRAITS(h5::nxobject,h5::nxobject,h5::nxgroup,
                            h5::nxfile,h5::nxfield,h5::nxattribute,
                            h5::nxselection);
    DECLARE_NXOBJECT_TRAITS(h5::nxgroup,h5::nxobject,h5::nxgroup,
                            h5::nxfile,h5::nxfield,h5::nxattribute,
                            h5::nxselection);
    DECLARE_NXOBJECT_TRAITS(h5::nxfile,h5::nxobject,h5::nxgroup,h5::nxfile,
                            h5::nxfield,h5::nxattribute,h5::nxselection);
    DECLARE_NXOBJECT_TRAITS(h5::nxfield,h5::nxobject,h5::nxgroup,h5::nxfile,
                            h5::nxfield,h5::nxattribute,h5::nxselection);
    DECLARE_NXOBJECT_TRAITS(h5::nxattribute,h5::nxobject,h5::nxgroup,
                            h5::nxfile,h5::nxfield,h5::nxattribute,
                            h5::nxselection);
    DECLARE_NXOBJECT_TRAITS(h5::nxselection,h5::nxobject,h5::nxgroup,
                            h5::nxfile,h5::nxfield,h5::nxattribute,
                            h5::nxselection);
//end of namespace
}
}
}
