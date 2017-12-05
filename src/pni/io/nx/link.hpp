//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Mar 04, 2016
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <pni/io/nx/nxpath/nxpath.hpp>
#include <pni/io/nx/nxlink_type.hpp>
#include <pni/io/nx/nxlink.hpp>
#include <pni/io/nx/nxobject_traits.hpp>
#include <pni/io/exceptions.hpp>

namespace pni{
namespace io{
namespace nx{
   
    //!
    //! \ingroup nexus_lowlevel
    //! \brief representation of a NeXus link
    //!
    //! The nxlink template represents a single NeXus link. It stores the 
    //! parent object (group) of the link and its name. 
    //! 
    //! \tparam IMPID implementation ID
    //! 
    template<nximp_code IMPID> class nxlink
    {
        public:
            //! parent type
            using parent_type = typename nxobject_trait<IMPID>::group_type;
            //! object type
            using object_type = typename nxobject_trait<IMPID>::object_type;
            //! link type
            using link_type = nxlink<IMPID>;
        private:
            //! parent object
            parent_type _parent;
            //! name of the link below the parent
            pni::core::string  _name;
        public:
            //! default constructor
            nxlink():
                _parent{},
                _name{}
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //! 
            //! \param parent reference to the parent object
            //! \param name the name of the link
            //! 
            nxlink(const parent_type &parent,
                   const pni::core::string &name):
                _parent(parent),
                _name(name)
            {}

            //----------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! \param parent reference to the parent object
            //! \param index numeric index of the link
            //! 
            nxlink(const parent_type &parent,size_t index):
                _parent(parent),
                _name(link_name(parent,index))
            {}
                   
   
            //-----------------------------------------------------------------
            //! 
            //! \brief get filename
            //! 
            //! Returns the name of the file where the link is stored. 
            //!
            //! \return filename as string
            pni::core::string filename() const noexcept
            {
                return _parent.filename();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief return the links name
            //! 
            //! \return name of the link as string
            //!
            pni::core::string name() const noexcept
            {
                return _name;
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief return parent object
            //! 
            //! Return a copy of the parent object below which the link is 
            //! stored.
            //!
            //! \return parent object as instance of nxobject
            //!
            object_type parent() const noexcept
            {
                return _parent;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief path to the link target
            //!
            //! Full path to the target to which the link points to. 
            //!
            //! \return target path as instance of nxpath
            //!
            nxpath target_path() const
            {
                return link_target(_parent,_name);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief return link status
            //!
            //! Return the current status of the link which can be either 
            //! VALID or INVALID. 
            //!
            //! \return link status
            //!
            nxlink_status status() const
            {
                return pni::io::nx::link_status(_parent,_name);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief return link type
            //! 
            //! \return type of the link
            //!
            nxlink_type type() const 
            {
                return pni::io::nx::link_type(_parent,_name);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief checks if a link is valid
            //!
            //! Simple wrapper around status(). If the link is valid this 
            //! method returns true, false otherwise. 
            //!
            //! \return true if valid, false otherwise
            //!
            bool is_valid() const
            {
                if(status() == nxlink_status::VALID)
                    return true;
                else
                    return false;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief resolve the link
            //!
            //! Resolve the link and return the object referenced by it. 
            //! If the link is invalid a link_error exception will be thrown.
            //!
            //! \throw link_error if link cannot be resolved
            //! 
            //! \return instance of nxobject
            //!
            object_type resolve() const 
            {
                if(!is_valid())
                    throw pni::io::link_error(EXCEPTION_RECORD,
                            "Cannot resolve link!");

                return _parent.at(_name);
            }

    };

    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief get list of links
    //!
    //! Appends the links below a parent group to a given container. 
    //! Only the direct links are taken into account.
    //! 
    //! \tparam CTYPE container type for the link
    //! \tparam GTYPE NeXus group template
    //! \tparam IMPID implementation ID
    //! \param parent the parent group 
    //! \param container reference to the target container
    //! 
    template<
             typename CTYPE,
             template<nximp_code> class GTYPE,
             nximp_code IMPID
            >
    void get_links(const GTYPE<IMPID> &parent,CTYPE &container)
    {
        using value_type = typename CTYPE::value_type;
        using link_type  = typename nxobject_trait<IMPID>::link_type;
        static_assert( std::is_same<link_type,value_type>::value,
                      "Container must store nxobject or nxlink objects!");

        for(size_t i=0;i<parent.size();++i)
            container.push_back(nxlink<IMPID>(parent,link_name(parent,i)));
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief get links below a group
    //! 
    //! Create a new container of type CTYPE and store all links below a 
    //! parent group in it. 
    //!
    //! \tparam CTYPE container type
    //! \tparam GTYPE Nexus group template
    //! \tparam IMPID implementation ID
    //! \param parent the parent group for which to store the links
    //! \return instance of CTYPE with the links 
    //! 
    template<
             typename CTYPE,
             template<nximp_code> class GTYPE,
             nximp_code IMPID
            >
    CTYPE get_links(const GTYPE<IMPID> &parent)
    {
        CTYPE container;
        get_links(parent,container);

        return container;
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief get links recursively 
    //!
    //! Recursively iterate over a tree starting from a particular parent 
    //! group and store all links in a container of type CTYPE. 
    //! If the container already contains links the new ones are appended.
    //! 
    //! \tparam CTYPE container type
    //! \tparam GTYPE NeXus container template
    //! \tparam IMPID NeXus implementation ID
    //! \param parent starting point for the recursive iteration
    //! \param container reference to the target container
    //! 
    template<
             typename CTYPE,
             template<nximp_code> class GTYPE,
             nximp_code IMPID
            >
    void get_links_recursive(const GTYPE<IMPID> &parent,CTYPE &container)
    {
        for(size_t index=0;index<parent.size();++index)
        {
            nxlink<IMPID> l(parent,link_name(parent,index));
            container.push_back(l);

            if(l.status() == nxlink_status::VALID)
            {
                auto object = parent[l.name()];
                if(is_group(object))
                    get_links_recursive(as_group(object),container);
            }
        }
    }
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief get links recursively 
    //!
    //! 
    //! \tparam CTYPE container type
    //! \tparam GTYPE group template
    //! \tparam IMPID implementation ID
    //! \param parent root group for iteration
    //! \return instance of CTYPE with links
    //! 
    template<
             typename CTYPE,
             template<nximp_code> class GTYPE,
             nximp_code IMPID
            >
    CTYPE get_links_recursive(const GTYPE<IMPID> &parent)
    {
        CTYPE container;
        get_links_recursive(parent,container);
        return container;
    }


//end of namespace
}
}
}
