/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: Jun 7, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "nxobject_traits.hpp"

#include <boost/variant.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

namespace pni{
namespace io{
namespace nx{

    /*!
    \ingroup variant_code
    \brief nexus object variants

    This traits provides different boost::variant types for data IO. The template
    can be instantiated from any nexus low level type. Internally nxobject_traits is
    used to obtain all related nexus objects.  

    Consider the following code snippet where different variants are created
    using h5::nxfile as the initial Nexus object.
    \code{.cpp}
    typedef nxvariant_traits<h5::nxfile>::object_types object_types;
    typedef nxvariant_traits<h5::nxfile>::child_types  child_types;
    typedef nxvariant_traits<h5::nxfile>::io_types     io_types;
    \endcode

    \tparam OTYPE object type
    */
    template<typename OTYPE> struct nxvariant_traits
    {
        //! local group type
        typedef typename nxobject_traits<OTYPE>::group_type group_type;
        //! local field type
        typedef typename nxobject_traits<OTYPE>::field_type field_type;
        //! local attribute type
        typedef typename nxobject_traits<OTYPE>::attribute_type attribute_type;

        //---------------------------------------------------------------------
        /*!
        \brief general object types

        This variant collates all relevant Nexus types. These types are 

        \li groups
        \li fields
        \li and attributes

        With this type one can write a general procedure to retrieve objects
        from the file. 
        \sa get_object
        */
        typedef boost::variant<group_type,
                               field_type,
                               attribute_type> object_types;

        //--------------------------------------------------------------------
        /*!
        \brief child types

        The primary container in a Nexus file is a group. This variant consists
        of a group and a field type as the only possible child types of a group.
        */
        typedef boost::variant<group_type,field_type> child_types;

        //---------------------------------------------------------------------
        /*!
        \brief IO types

        Finally this variant collates all types in the Nexus universe that are
        capable of doing data IO. This are fields and attributes. 
        */
        typedef boost::variant<field_type,attribute_type> io_types;
    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup variant_code
    \brief retrieve variant type

    This template can be used to retrieve the i-th type of a variant type. 

    \tparam VTYPE variant type
    \tparam i type index
    */
    template<typename VTYPE,int i> struct nxvariant_member_type
    {
        typedef typename boost::mpl::at<typename VTYPE::types,boost::mpl::int_<0> >::type type; 
    };

//end of namespace
}
}
}

