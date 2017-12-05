//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Jun 28, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <boost/variant.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <pni/io/nx/nximp_code.hpp>
#include <pni/io/nx/nximp_code_map.hpp>

namespace pni{
namespace io{
namespace nx{


    //!
    //! \ingroup nexus_lowlevel
    //! \brief nexus object traits
    //! 
    //! This traits maps a type to the Nexus low level object types. The most
    //! important application for this is to find for one Nexus object type the
    //! other types belonging to its implementation.
    //!
    template<nximp_code id> struct nxobject_trait;


    template<typename VTYPE,int i>
    using nxobject_element = boost::mpl::at<typename VTYPE::types,boost::mpl::int_<i>>;
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief get group type
    //!
    //! Obtains the group type of a variant type.
    //! \tparam VTYPE variant type
    //!
    template<typename VTYPE> struct nxobject_group
    {
        //! group type
        typedef typename nxobject_element<VTYPE,0>::type type;
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief get field type
    //!
    //! Obtains the field type of a variant type
    //! \tparam VTYPE variant type
    //!
    template<typename VTYPE> struct nxobject_field
    {
        //! field type
        typedef typename nxobject_element<VTYPE,1>::type type;
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief get attribute type
    //!
    //! Retrieves the attribute type from a varian type.
    //! \tparam VTYPE
    //!
    template<typename VTYPE> struct nxobject_attribute
    {
        //! attribute type
        typedef typename nxobject_element<VTYPE,2>::type type;
    };

}
}
}




