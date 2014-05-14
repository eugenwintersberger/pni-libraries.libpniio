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
    template<nximp_code id> struct nxobject_traits {};

    //!
    //! \ingroup nexus_lowlevel
    //! \brief macro for nxobject_traits declaration
    //!
    //! This macro helps in the declaration of a single nxobject_trait.
    //! \param id       the ID code of the implementation
    //! \param object_t the Nexus object type
    //! \param group_t  the Nexus group type
    //! \param file_t   the Nexus file type
    //! \param field_t  the Nexus field type
    //! \param attr_t   the Nexus attribute type
    //! \param sel_t    the Nexus selection type
    //! \param link_t   the Nexus link type
    //!
#define DECLARE_NXOBJECT_TRAITS(id,object_t,group_t,file_t,field_t,attr_t,\
                                sel_t,link_t,deflate_t)\
        template<> struct nxobject_traits<id>\
        {\
            typedef object_t object_type;\
            typedef group_t  group_type; \
            typedef file_t   file_type;  \
            typedef field_t  field_type; \
            typedef attr_t   attribute_type; \
            typedef sel_t    selection_type;\
            typedef link_t   link_type;\
            typedef deflate_t deflate_type;\
        }


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


    //!
    //! \ingroup nexus_lowlevel 
    //! \brief define a Nexus object type
    //!
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

//end of namespace
}
}
}




