//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//************************************************************************
// Created on: Apr 22, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "data_node.hpp"
#include "../nxlink.hpp"

namespace pni{
namespace io{
namespace nx{
namespace xml{
    
    //!
    //! \ingroup xml_classes
    //! \brief manages links in XML 
    //!
    //! This class provides a static method to create a link described by 
    //! XML. There is no method to generate a link from an existing NeXus 
    //! object as this is beyond the scope of libpniio's XML stack.
    //! 
   
    class link
    {
        private:
            //!
            //! \brief get name of link
            //! 
            //! Return the name of the link from the link node. 
            //! 
            //! \throws key_error if the name attribute does not exist
            //! \throws parser_error in case of any other XML parsing error
            //! 
            //! \param link_node the XML node describing the link
            //! \return string with the name of the link
            static string get_link_name(const node &link_node);
            
            //-----------------------------------------------------------------
            //!
            //! \brief get link target
            //!
            //! Return the path to the target from the link node.
            //!
            //! \throws key_error if the target attribute does not exist
            //! \throws parser_error in case of any other XML parsing error
            //!
            //! \param link_node XML node describing the link
            //! \return string with the path to the link target
            static string get_link_target(const node &link_node);
            
        public:
        
            //! \brief generate HDF5 link
            //!
            //! Generate an HDF5 link within a NeXus file according to the 
            //! information provided by the link node. 
            //!
            //! \throws parser_error in case of XML parsing problems
            //! \throws invalid_object_error if the parent object is not valid
            //! \throws io_error if data or metadata write failed
            //! \throws type_error if the parent object is not a group type
            //! \throws key_error if one of the required attribute tags does 
            //!                   not exist
            //! \throws object_error in case of any other error
            //! 
            //! \tparam GTYPE group type
            //! \tparam FTYPE field type
            //! \tparam ATYPE attribute type
            //!
            //! \param parent the parent below which the link should be 
            //!               established
            //! \param link_node reference the the XML node providing the 
            //!                  link information
            //!
            template<
                     typename GTYPE,
                     typename FTYPE,
                     typename ATYPE
                    >
            static void object_from_xml(const nxobject<GTYPE,FTYPE,ATYPE> &parent,
                                        const node &link_node);
                      
    };
    
    //-------------------------------------------------------------------------
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            >
    void link::object_from_xml(const nxobject<GTYPE,FTYPE,ATYPE> &parent,
                               const node &link_node)
    {
        //will throw key error if name attribute does not exist
        string link_name = get_link_name(link_node);
        //will thorw key_error if target attribute does not exist
        string link_target = get_link_target(link_node);
        
        //will throw type_error if the parent is not a group
        GTYPE parent_group = as_group(parent);
        
        pni::io::nx::link(link_target,parent_group,link_name);
    }            
    
 
//end of namespace
}
}
}
}
