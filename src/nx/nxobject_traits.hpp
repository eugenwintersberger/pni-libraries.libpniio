/*
 * Declaration of Nexus implementation codes.
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
 * Created on: Jun 28, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

namespace pni{
namespace io{
namespace nx{


    /*!
    \ingroup common_devel
    \brief nexus object traits

    This traits maps a type to the Nexus low level object types. The most
    important application for this is to find for one Nexus object type the
    other types belonging to its implementation.
    */
    template<typename OTYPE> struct nxobject_traits {};

    /*!
    \ingroup common_devel
    \brief macro for nxobject_traits declaration

    This macro helps in the declaration of a single nxobject_trait.
    \param otype the original type
    \param object_t the Nexus object type
    \param group_t  the Nexus group type
    \param file_t   the Nexus file type
    \param field_t  the Nexus field type
    \param attr_t   the Nexus attribute type
    \param sel_t    the Nexus selection type
    */
#define DECLARE_NXOBJECT_TRAITS(otype,object_t,group_t,file_t,field_t,attr_t,sel_t)\
        template<> struct nxobject_traits<otype>\
        {\
            typedef object_t object_type;\
            typedef group_t  group_type; \
            typedef file_t   file_type;  \
            typedef field_t  field_type; \
            typedef attr_t   attribute_type; \
            typedef sel_t    selection_type;\
        }

    /*!
    \ingroup common_devel 
    \brief define a Nexus object type
    */
#define DEFINE_NXOBJECT(otype) \
        typedef typename nxobject_traits<otype>::object_type

#define DEFINE_NXGROUP(otype) \
        typedef typename nxobject_traits<otype>::group_type

#define DEFINE_NXFILE(otype) \
        typedef typename nxobject_traits<otype>::file_type

#define DEFINE_NXFIELD(otype) \
        typedef typename nxobject_traits<otype>::field_type

#define DEFINE_NXATTRIBUTE(otype) \
        typedef typename nxobject_traits<otype>::attribute_type

#define DEFINE_NXSELECTION(otype) \
        typedef typename nxobject_traits<otype>::selection_type


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




