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
 * Created on: May 7, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <pni/core/types.hpp>
#include "nxobject_type.hpp"
#include "nxpath.hpp"

namespace pni{
namespace io{
namespace nx{

    using namespace pni::core;

    /*!
    \ingroup nexus_utility_functions
    \brief search for group by class

    Search for a child group below p for a group with a particular class name
    and return the group if found. The function returs false if not successful
    and true otherwise. 

    \code
    nxgroup g = file["/"];
    nxgroup e;

    if(!find_group_by_class(g,"NXentry",e))
    {
        //no entry found - do something here.
    }

    \endcode

    \tparam PTYPE parent type 
    \tparam GTYPE group type
    \param p parent group whose childs to search
    \param gclass name of the class
    \param g resulting group
    \return true if group has been found, false otherwise
    */
    template<typename PTYPE, typename GTYPE> 
    bool find_group_by_class(const PTYPE &p,const string &gclass,GTYPE &g)
    {
        for(auto iter=p.begin();iter!=p.end();++iter)
        {
            //continue the loop if the object is not a group
            if(iter->object_type() != nxobject_type::NXGROUP) continue;

            //if the group object has no NX_class attribute just go ahead
            if(!iter->has_attr("NX_class")) continue;

            //here we can do the check
            string buffer;
            iter->attr("NX_class").read(buffer);
            if(buffer == gclass) 
            {
                g = *iter;
                return true;
            }
        }

        return false;
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup nexus_utility_functions
    \brief search for group names

    Search for a child group with a particular name. The function returns true
    if the search was successful, false otherwise. 
    A typical application would look like this:
    \code
    nxgroup inst = file["/entry/instrument"];
    nxgruop detector;
    if(!find_group_by_name(inst,"detector_channel_1",detector))
    {
        std::cerr<<"Cannot find detector!"<<std::endl;
        return -1;
    }
    \endcode

    \tparam PTYPE parent group type
    \tparam GTYPE target group type
    \param p parent group 
    \param gname name of the group to look for
    \param g target group
    \return true if group has been found, false otherwise
    */
    template<typename PTYPE,typename GTYPE>
    bool find_group_by_name(const PTYPE &p,const string &gname,GTYPE &g)
    {
        auto iter = p.begin();
        for(auto iter=p.begin();iter!=p.end();++iter)
        {
            //continue with the loop of the object is not a group
            if(iter->object_type() != nxobject_type::NXGROUP) continue;

            //check name
            if(iter->name() == gname) 
            {
                g = *iter;
                return true;
            }
        }

        return false;
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup nexus_utility_functions
    \brief find group by class and name

    Find a child group with a particular name and class. If the search succeeds 
    the function returns true, false otherwise. 

    \tparam PTYPE parent type
    \tparam GTYPE target group type
    \param p parent instance
    \param gname group name
    \param gclass class name
    \param g target group
    \return true if found, false otherwise
    */
    template<typename PTYPE,typename GTYPE>
    bool find_group_by_name_and_class(const PTYPE &p,const string &gname,
                                      const string &gclass,GTYPE &g)
    {
        if(!find_group_by_name(p,gname,g))
            return false;

        if(g.has_attr("NX_class"))
        {
            string buffer;
            g.attr("NX_class").read(buffer);
            if(buffer == gclass) return true;
        }

        return false;
    }

    //-------------------------------------------------------------------------
    /*!
    \brief create a group

    Creates a group of type GTYPE below a group of type GTYPE. 
    
    \throws pni::io::nx::nxgroup_error 
    \throws pni::io::nx::nxattribute_error
    \tparam PTYPE type of parent group
    \tparam GTYPE type of target group
    \param p parent groupt
    \param gname name of the new group
    \param gclass class of the new group
    \param g target group
    */
    template<typename PTYPE,typename GTYPE>
    void create_group(const PTYPE &p,const string &gname,const string &gclass,
                      GTYPE &g)
    {
        g=p.create_group(gname,gclass);
    }

    //-------------------------------------------------------------------------
    template<typename PTYPE,typename GTYPE>
    void create_group(const PTYPE &p,const string &spath,GTYPE &g)
    {
        nxpath path = path_from_string(spath);


    }
//end of namespace
}
}
}
