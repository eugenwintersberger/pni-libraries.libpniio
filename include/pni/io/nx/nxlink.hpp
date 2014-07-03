//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 22, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include "nxobject_traits.hpp"
#include "nxpath.hpp"
#include "nxlink_type.hpp"

namespace pni{
namespace io{
namespace nx{

    
    //!
    //! \ingroup nexus_lowlevel
    //! \brief create a link
    //!
    //! Creates a link to an object referenced by target. The new link is 
    //! created below g with name. If the location and the target reside 
    //! within the same file or the target path has no filename set an 
    //! internal link will be created.  
    //! Consider the following example. Here we want to create a link from 
    //! the data stored in a detector field (all within the same file).
    /*!
    \code
    nxpath path = path_from_string("/entry/instrument/detector/data");
    nxgroup data_group = ....;
    link(path,data_group,"data"); 
    \endcode
    */ 
    //! In the next example the same link should be created but this time 
    //! the detector data is stored in an external file.
    /*!
    \code
    nxpath path =
    path_from_string("detector_file.nxs://entry/instrument/detector/data");
    nxgroup data_group = ...;
    link(path,data_group,"data");
    \endcode
    */
    //! The sequence of calls is the same as in the latter examples except 
    //! that the path includes a file name.
    //!
    //! \tparam GTYPE group type
    //! \param target path to the original object
    //! \param g group where to create the link
    //! \param name the new name of the link
    //!
    template<
             template<nximp_code> class GTYPE,
             nximp_code IMPID
            > 
    void link(const nxpath &target,const GTYPE<IMPID> &g,
              const string &name)
    {

        //determine the utility class perfroming linking
        typedef typename nxobject_trait<IMPID>::link_type link_type;

        if(!target.filename().empty())
            //create an external link
            link_type::create_external_link(target,g.imp(),name);
        else
            //create an internal link
            link_type::create_internal_link(target,g.imp(),name);
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief create a link
    //!
    //! Creates a link to an object referenced by target. The new link is 
    //! created below g with name. Here the target path is given by a string.
    //!
    //! \tparam GTYPE group type
    //! \param target path to the object as a string
    //! \param g group where to create the link
    //!\param name the new name of the link
    //!
    template<typename GTYPE>
    void link(const string &target,const GTYPE &g,const string &name)
    {
        nxpath path = nxpath::from_string(target);
        link(path,g,name);
    }

    template<typename GTYPE>
    void link(const char *target,const GTYPE &g,const string &name)
    {
        link(string(target),g,name);
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief create a link
    //! 
    //! Create a new link to the target object. The new link will be created 
    //! below g with name name. This function can currently only create 
    //! internal links as it assumes that the target and g reside within the 
    //! same file.
    //! 
    //! \tparam STYPE type of the target object
    //! \tparam GTYPE group type
    //! \param target object to which the new link should point
    //! \param g group where to create the link
    //! \param name the new name of the link
    //!
    template< 
             typename STYPE,
             typename GTYPE
            >
    void link(const STYPE &target,const GTYPE &g,const string &name)
    {
        link(target.path(),g,name);
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief return link type
    //!
    //! Returns the type of link used for child name below parent. 
    //!
    //! \throws pni::core::key_error if parent has no child with name
    //! \throws pni::io::nx::nxlink_error if link type could not be obtained
    //! \throws pni::core::type_error if the link type is unkown
    //! \tparam GTYPE parent object type
    //! \param parent instance of GTYPE
    //! \param name of the child
    //! \return link type
    //!
    template<
             template<nximp_code> class GTYPE,
             nximp_code IMPID
            >
    nxlink_type link_type(const GTYPE<IMPID> &parent,const string &name)
    {
        typedef typename nxobject_trait<IMPID>::link_type link_type;

        return link_type::link_type(parent.imp(),name);
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief return true if link is external
    //!
    //! Returns true if the link used for child name below parent is an 
    //! external one. 
    //!
    //! \tparam GTYPE parent type
    //! \param parent instance of GTYPE
    //! \param name child name
    //! \return true if link is external, false otherwise
    //!
    template<typename GTYPE>
    bool is_external_link(const GTYPE &parent,const string &name)
    {
        return link_type(parent,name)==nxlink_type::EXTERNAL;
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief return true if link is soft
    //! 
    //! Returns true if the link used for child name below parent is an soft
    //! one. 
    //!
    //! \tparam GTYPE parent type
    //! \param parent instance of GTYPE
    //! \param name child name
    //! \return true if link is soft, false otherwise
    //!
    template<typename GTYPE>
    bool is_soft_link(const GTYPE &parent,const string &name)
    {
        return link_type(parent,name) == nxlink_type::SOFT;
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief return true if link is hard
    //! 
    //! Returns true if the link used for child name below parent is an hard
    //! one. 
    //! \tparam GTYPE parent type
    //! \param parent instance of GTYPE
    //! \param name child name
    //! \return true if link is hard, false otherwise
    //!
    template<typename GTYPE>
    bool is_hard_link(const GTYPE &parent,const string &name)
    {
        return link_type(parent,name) == nxlink_type::HARD;
    }

//end of namespace
}
}
}
