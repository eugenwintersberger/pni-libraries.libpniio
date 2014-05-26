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
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include "nximp_code.hpp"
#include "nximp_code_map.hpp"

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
    /*!
    \ingroup variant_code
    \brief get group type

    Obtains the group type of a variant type.
    \tparam VTYPE variant type
    */
    template<typename VTYPE> struct nxobject_group
    {
        //! group type
        typedef typename nxobject_element<VTYPE,0>::type type;
    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup variant_code
    \brief get field type

    Obtains the field type of a variant type
    \tparam VTYPE variant type
    */
    template<typename VTYPE> struct nxobject_field
    {
        //! field type
        typedef typename nxobject_element<VTYPE,1>::type type;
    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup variant_code
    \brief get attribute type

    Retrieves the attribute type from a varian type.
    \tparam VTYPE
    */
    template<typename VTYPE> struct nxobject_attribute
    {
        //! attribute type
        typedef typename nxobject_element<VTYPE,2>::type type;
    };

    /*
template<typename OTYPE>
using trait_type = nxobject_traits<nximp_code_map<OTYPE>::icode>;

template<typename OTYPE>
using object_type = typename trait_type<OTYPE>::object_type;

template<typename OTYPE>
using group_type  = typename trait_type<OTYPE>::group_type;

template<typename OTYPE>
using file_type  = typename trait_type<OTYPE>::file_type;

template<typename OTYPE>
using field_type = typename trait_type<OTYPE>::field_type;

template<typename OTYPE>
using attribute_type = typename trait_type<OTYPE>::attribute_type;

template<typename OTYPE>
using selection_type = typename trait_type<OTYPE>::selection_type;

template<typename OTYPE>
using deflate_type = typename trait_type<OTYPE>::deflate_type;
*/

    //!
    //! \ingroup nexus_lowlevel 
    //! \brief define a Nexus object type
    //!
    /*
#define DEFINE_NXOBJECT(otype) \
        typedef typename pni::io::nx::nxobject_traits<nximp_code_map<otype>::idcode>::object_type

#define DEFINE_NXGROUP(otype) \
        typedef typename nxobject_traits<nximp_code_map<otype>::idcode>::group_type

#define DEFINE_NXFILE(otype) \
        typedef typename nxobject_traits<nximp_code_map<otype>::idcode>::file_type

#define DEFINE_NXFIELD(otype) \
        typedef typename nxobject_traits<nximp_code_map<otype>::idcode>::field_type

#define DEFINE_NXATTRIBUTE(otype) \
        typedef typename nxobject_traits<nximp_code_map<otype>::idcode>::attribute_type

#define DEFINE_NXSELECTION(otype) \
        typedef typename nxobject_traits<nximp_code_map<otype>::idcode>::selection_type

#define DEFINE_NXDEFLATE(otype)\
        typedef typename nxobject_traits<nximp_code_map<otype>::idcode>::deflate_type


#define DEFINE_NEXUS_TYPES(otype)\
        DEFINE_NXOBJECT(otype) object_type;\
        DEFINE_NXGROUP(otype)  group_type;\
        DEFINE_NXFILE(otype)   file_type;\
        DEFINE_NXFIELD(otype)  field_type;\
        DEFINE_NXATTRIBUTE(otype) attribute_type;\
        DEFINE_NXSELECTION(otype) selection_type
*/
//end of namespace
}
}
}




