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
 *
 * Created on: Jul 22, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include "nxpath.hpp"
#include "nximp_code_map.hpp"
#include "nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{

    
    /*!
    \ingroup nexus_lowlevel
    \brief create a link

    Creates a link to an object referenced by target. The new link is created
    below g with name. 
    \tparam GTYPE group type
    \param target path to the original object
    \param g group where to create the link
    \param name the new name of the link
    */
    template<typename GTYPE> 
    void link(const nxpath &target,const GTYPE &g,const string &name)
    {

        //determine the utility class perfroming linking
        typedef typename nximp_code_map<GTYPE> code_map;
        typedef typename nobject_traits<code_map::icode> object_traits;
        typedef object_traits::link_type link_type;

        if(!target.filename().empty())
        {
            //create an external link
            link_type::create_external_link(target,g.imp(),name);

        }
        else
        {
            //create an internal link
            link_type::create_internal_link(target,g.imp(),name);

        }

    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup nexus_lowlevel
    \brief create a link

    Creates a link to an object referenced by target. The new link is created
    below g with name. Here the target path is given by a string.
    \tparam GTYPE group type
    \param target path to the object as a string
    \param g group where to create the link
    \param name the new name of the link
    */
    template<typename GTYPE>
    void link(const string &target,const GTYPE &g,const string &name)
    {

    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup nexus_lowlevel
    \brief create a link

    Create a new link to the target object. The new link will be created below g
    with name name.
    \tparam STYPE type of the target object
    \tparam GTYPE group type
    \param target object to which the new link should point
    \param g group where to create the link
    \param name the new name of the link
    */
    template<typename STYPE,
             typename GTYPE>
    void link(const STYPE &target,const GTYPE &g,const string &name)
    {

    }

//end of namespace
}
}
}
