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

#include <boost/filesystem.hpp>
#include "nxobject_traits.hpp"
#include "nxpath/nxpath.hpp"
#include "nxpath/utils.hpp"
#include "nxlink_type.hpp"
#include "algorithms/get_path.hpp"


namespace pni{
namespace io{
namespace nx{
  
    //internal function - should not show up in the official documentation
    //
    // This function throws value_error when the target path contains
    // intermediate ..!
    void __check_target_path(const nxpath &target);
   
    //------------------------------------------------------------------------
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
    //! \throws invalid_object_error if parent group is not valid
    //! \throws link_error if error during link-creation
    //! \throws value_error if the path contains any class-only elements
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
              const pni::core::string &name)
    {

        //determine the utility class perfroming linking
        using link_type = typename nxobject_trait<IMPID>::link_type;


        if(has_file_section(target))
        {
            __check_target_path(target);
            //create an external link
            link_type::create_external_link(target,g.imp(),name);
        }
        else
        {
            nxpath real_target = target;

            if(!is_absolute(real_target))
            {
                GTYPE<IMPID> parent = g;
                while(real_target.front().first=="..")
                {
                    parent = parent.parent();
                    real_target.pop_front();
                }

                real_target = join(nxpath::from_string(get_path(parent)),real_target);
            }
           
            //the target path must not contain any element with ..
            __check_target_path(real_target);

            //create an internal link
            link_type::create_internal_link(real_target,g.imp(),name);
        }
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief create a link
    //!
    //! Creates a link to an object referenced by target. The new link is 
    //! created below g with name. Here the target path is given by a string.
    //!
    //! \throws invalid_object_Error if g is not a valid group
    //! \throws link_error in case of errors during link creation
    //! \throws value_error if path contains class-only elements
    //!
    //! \tparam GTYPE group type
    //! \param target path to the object as a string
    //! \param g group where to create the link
    //! \param name the new name of the link
    //!
    template<typename GTYPE>
    void link(const pni::core::string &target,const GTYPE &g,
              const pni::core::string &name)
    {
        nxpath path = nxpath::from_string(target);
        link(path,g,name);
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief create a link
    //!
    //! Creates a link to an object referenced by target. The new link is 
    //! created below g with name. Here the target path is given by a string.
    //!
    //! \throws invalid_object_error when g is not a valid group
    //! \throws link_error in case of errors during link creation
    //! \throws value_error if path contains class-only elements
    //!
    //! \tparam GTYPE group type
    //! \param target path to the object as a string
    //! \param g group where to create the link
    //! \param name the new name of the link
    //!
    template<typename GTYPE>
    void link(const char *target,const GTYPE &g,const pni::core::string &name)
    {
        link(pni::core::string(target),g,name);
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
    //! \throws link_error in case of errors during link creation
    //! \throws invalid_object_error if either g or target are not valid 
    //! objects
    //! \throws invalid_object_error if one of the fields parents 
    //! could not be retrieved or the attribute itself is not valid
    //! \throws shape_mismatch_error if a possible class attribute is
    //! not scalar
    //! \throws io_error if class data retrieval failed
    //! \throws type_error if the class attribute exists but is of 
    //! the wrong type
    //! \throws object_error in case of any other error
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
    void link(const STYPE &target,const GTYPE &g,const pni::core::string &name)
    {
        link(get_path(target),g,name);
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief return link type
    //!
    //! Returns the type of link used for child name below parent. 
    //!
    //! \throws invalid_object_error if parent is not a valid group
    //! \throws key_error if parent has no child with name
    //! \throws link_error if link type could not be obtained
    //! \throws type_error if the link type is unkown
    //!
    //! \tparam GTYPE parent object type
    //! \param parent instance of GTYPE
    //! \param name of the child
    //! \return link type
    //!
    template<
             template<nximp_code> class GTYPE,
             nximp_code IMPID
            >
    auto link_type(const GTYPE<IMPID> &parent,const pni::core::string &name)
        -> nxlink_type 
    {
        using link_type =  typename nxobject_trait<IMPID>::link_type;

        return link_type::link_type(parent.imp(),name);
    }

    //-------------------------------------------------------------------------
    //!
    //! \brief get link name 
    //!
    //! Return the name of a link below parent. The link is determined by its
    //! index.
    //! 
    //! \throws invalid_object_error if parent is not a valid group
    //! \throws index_error if index exceeds the total number of links below
    //!                     parent
    //! \throws object_error in case of any other error
    //!
    //! \tparam GTYPE group type template
    //! \tparam IMPID iplementation ID template parameter
    //! \param parent reference to the parent group
    //! \param index the index of the link 
    //! 
    //! \return name of the link as string
    //!
    template<
             template<nximp_code> class GTYPE,
             nximp_code IMPID
            >
    auto link_name(const GTYPE<IMPID> &parent,size_t index)
        -> pni::core::string
    {
        using link_type = typename nxobject_trait<IMPID>::link_type;

        return link_type::link_name(parent.imp(),index);
    }

    //-------------------------------------------------------------------------
    //!
    //! \brief get link target
    //!
    //! Return the target of a link determined by index below group parent.
    //!
    //! \throws invalid_object_error if parent is not a valid group
    //! \throws index_error if index exceeds the total number of links below
    //!                     parent
    //! \throws link_error if the information cannot be retrieved
    //! \throws object_error in case of any other error
    //! 
    //! \tparam GTYPE group type template
    //! \tparam IMPID implemenation ID template parameter
    //! \param parent reference to the parent group
    //! \param index the numeric index of the link 
    //!
    //! \return target of the link as nxpath instance
    //!
    template<
             template<nximp_code> class GTYPE,
             nximp_code IMPID
            >
    auto link_target(const GTYPE<IMPID> &parent,size_t index) -> nxpath
    {
        using link_type = typename nxobject_trait<IMPID>::link_type;

        return link_type::link_target(parent.imp(),index);
    }

    //-------------------------------------------------------------------------
    //!
    //! \brief get link target
    //!
    //! Return the target of link lname below parent as instance of nxpath.
    //! 
    //! \throws invalid_object_error if parent is not a valid group
    //! \throws key_error if parent has not link lname
    //! \throws link_error if the information cannot be retrieved
    //! \throws object_error in case of any other error
    //!
    //! \tparam GTYPE group type template
    //! \tparam IMPID implemenation ID template parameter
    //! \param parent reference to the parent group
    //! \param lname name of the link
    //!
    //! \return target of the link as nxpath instance
    //!
    template<
             template<nximp_code> class GTYPE,
             nximp_code IMPID
            >
    auto link_target(const GTYPE<IMPID> &parent,const pni::core::string &lname)
        -> nxpath
    {
        using link_type = typename nxobject_trait<IMPID>::link_type;

        return link_type::link_target(parent.imp(),lname);
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief return true if link is external
    //!
    //! Returns true if the link used for child name below parent is an 
    //! external one. 
    //! 
    //! \throws invalid_object_error if parent is not a valid group
    //! \throws key_error if parent has no child with name
    //! \throws link_error if link type could not be obtained
    //! \throws type_error if the link type is unkown
    //! \throws object_error in case of any other error
    //!
    //! \tparam GTYPE parent type
    //! \param parent instance of GTYPE
    //! \param name child name
    //! \return true if link is external, false otherwise
    //!
    template<typename GTYPE>
    bool is_external_link(const GTYPE &parent,const pni::core::string &name)
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
    //! \throws invalid_object_error if parent is not a valid group
    //! \throws key_error if parent has no child with name
    //! \throws link_error if link type could not be obtained
    //! \throws type_error if the link type is unkown
    //! \throws object_error in case of any other error
    //!
    //! \tparam GTYPE parent type
    //! \param parent instance of GTYPE
    //! \param name child name
    //! \return true if link is soft, false otherwise
    //!
    template<typename GTYPE>
    bool is_soft_link(const GTYPE &parent,const pni::core::string &name)
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
    //!  
    //! \throws invalid_object_error if parent is not a valid group
    //! \throws key_error if parent has no child with name
    //! \throws link_error if link type could not be obtained
    //! \throws type_error if the link type is unkown
    //! \throws object_error in case of any other error
    //!
    //! \tparam GTYPE parent type
    //! \param parent instance of GTYPE
    //! \param name child name
    //! \return true if link is hard, false otherwise
    //!
    template<typename GTYPE>
    bool is_hard_link(const GTYPE &parent,const pni::core::string &name)
    {
        return link_type(parent,name) == nxlink_type::HARD;
    }

    //------------------------------------------------------------------------
    template<
             template<nximp_code> class GTYPE,
             nximp_code IMPID
            >
    auto link_status(const GTYPE<IMPID> parent,
                     const pni::core::string &lname)
        -> nxlink_status
    {
        using namespace boost::filesystem;
        using file_type = typename nxobject_trait<IMPID>::file_type;

        auto target = link_target(parent,lname);

        switch(link_type(parent,lname))
        {
            case nxlink_type::HARD: 
                return nxlink_status::VALID;
            case nxlink_type::SOFT:
                try
                {
                    auto object = get_object(parent,target);
                    return nxlink_status::VALID;
                }
                catch(...)
                {
                    return nxlink_status::INVALID;
                }
                break;
            case nxlink_type::EXTERNAL:
                //check if the file exists
                if(!exists(path(target.filename())))
                    return nxlink_status::INVALID;
                
                try
                {
                    //check if the referenced object exists
                    auto f = file_type::open_file(target.filename());
                    auto o = get_object(f.root(),target);
                    return nxlink_status::VALID;
                }
                catch(...)
                {
                    return nxlink_status::INVALID;
                }
                break;
            default:
                return nxlink_status::INVALID;
        }
    }

//end of namespace
}
}
}
