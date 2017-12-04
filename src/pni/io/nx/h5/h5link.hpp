//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Feb 10, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

extern "C"{
#include <hdf5.h>
}

#include <pni/core/types.hpp>
#include <pni/core/error.hpp>

#include <pni/io/nx/nxlink_type.hpp>
#include <pni/io/nx/nxpath/nxpath.hpp>
#include <pni/io/windows.hpp>

namespace pni{
namespace io {
namespace nx{
namespace h5{    

    class group_imp;
   
    //! 
    //! \ingroup nxh5_classes
    //!
    //! This class holds only static methods which can be used to create 
    //! internal and external links. 
    //!
    class PNIIO_EXPORT h5link
    {
        private:
            //!
            //! \brief convert a Nexus path to an HDF5 path
            //!
            //! This static method converts a Nexus path to an HDF5 path. HDF5
            //! requires that all group and field names are given. Thus, one 
            //! cannot use just the groups class to identify a group. 
            //! If the name of a group or field is not given a
            //! pni::core::value_error is thrown.
            //!
            //! \throws pni::core::value_error if element name is missing
            //!
            //! \param p Nexus path object
            //! \return HDF5 path as a string
            //!
            static pni::core::string _nx2hdf5path(const nxpath &p);

            //----------------------------------------------------------------
            //!
            //! \brief check if parent is valid
            //! 
            //! Static member function checking if the parent object is valid. 
            //! Otherwise pni::io::invalid_object_error will be thrown. 
            //!
            //! \throws invalid_object_error if loc is not valid
            //! 
            //! \param loc reference to the parent object
            //! \param record exception record at the location where the test
            //!               should be performed
            //! \param message error message
            //!
            static void check_if_valid(const group_imp &loc,
                                       const pni::core::exception_record &record,
                                       const pni::core::string &message);

            //----------------------------------------------------------------
            //!
            //! \brief check if link exists
            //!
            //! Checks if a link of name lname exists below group loc. This 
            //! function assumes that loc is a valid HDF5 group. In case of 
            //! doubts check_if_valid should be called before.
            //!
            //! \throws key_error if link does not exist
            //!
            //! \param loc the parent group for the link
            //! \param lname the name of the link
            //! \param record the exception record at the position of the check
            //! \param message a custom error message that will be added to 
            //!                the default message
            //!
            static void check_if_exists(const group_imp &loc,
                                        const pni::core::string &lname,
                                        const pni::core::exception_record
                                        &record,
                                        const pni::core::string &message="");

            //----------------------------------------------------------------
            //!
            //! \brief check if link exists
            //!
            //! Checks if a link with a particular index exists. This function 
            //! does nothing else than checking if index does not exceed the 
            //! total number of links below the parent group. The function 
            //! asssumes that loc is a valid HDF5 group. In case of doubts 
            //! call check_if_valid before. 
            //!
            //! \throws index_error if index exceeds the total number of links
            //! 
            //! \param loc parent HDF5 group
            //! \param index the index of the link
            //! \param record exception record of the check
            //! \param message optional message which will be added to the 
            //!                default error message
            //! 
            static void check_if_exists(const group_imp &loc,size_t index,
                                        const pni::core::exception_record
                                        &record,
                                        const pni::core::string &message="");
                                    

            //----------------------------------------------------------------
            //!
            //! \brief get link info by name
            //!
            //! Returns the info structure for a link of anme name. 
            //! 
            //! \throws invalid_object_error if loc is not a valid group
            //! \throws key_error if a link fo name name does not exist
            //! \throws object_error in case of any other error
            //! 
            //! \param loc parent group of the link
            //! \param name the name of the link
            //! 
            //! \return HDF5 link info structure
            //! 
            static H5L_info_t get_link_info(const group_imp &loc,
                                            const pni::core::string &name);

            //----------------------------------------------------------------
            //!
            //! \brief get link info by index
            //!
            //! Returns the info structure for the link determined by index.
            //! 
            //! \throws invalid_object_error if loc is not a valid group
            //! \throws index_error if index exceeds the total number of links
            //!                     below the parent group
            //! \throws object_error in case of any other error
            //! 
            //! \param loc parent group of the link
            //! \param index link index
            //! 
            //! \return HDF5 link info structure
            //! 
            static H5L_info_t get_link_info(const group_imp &loc,
                                            size_t index);

            //----------------------------------------------------------------
            //!
            //! \brief return the link value
            //!
            //! Return the link value. In HDF5 the link value is the target
            //! to which a link referes to.
            //!
            //! \throw invalid_object_error if loc is not a valid group
            //! \throw key_error if a linke lname does not exist
            //! \throw link_error in case that the value cannot be retrieved
            //! \throw object_error in case of any other error
            //! 
            //! \return link value as string
            //!
            static auto get_link_value(const group_imp &loc,const
                                       pni::core::string &lname)
                -> pni::core::string;

    
            //----------------------------------------------------------------
            //!
            //! \brief return external target
            //! 
            //! Return the target of an external link as an instance of nxpath.
            //! 
            //! \throw invalid_object_error if loc is not a valid group
            //! \throw key_error if a linke lname does not exist
            //! \throw link_error in case that the value cannot be retrieved
            //! \throw object_error in case of any other error
            //! 
            //! \param loc parent group
            //! \param lname name of the link
            //! 
            //! \return link target as nxpath
            //!
            static auto get_external_link_target(const group_imp &loc,
                                                 const pni::core::string &lname)
                -> pni::io::nx::nxpath;

            //----------------------------------------------------------------
            //!
            //! \brief return internal target
            //! 
            //! Return the target of an internal link as an instance of nxpath.
            //! 
            //! \throw invalid_object_error if loc is not a valid group
            //! \throw key_error if a linke lname does not exist
            //! \throw link_error in case that the value cannot be retrieved
            //! \throw object_error in case of any other error
            //! 
            //! \param loc parent group
            //! \param lname name of the link
            //! 
            //! \return link target as nxpath
            //!
            static auto get_soft_link_target(const group_imp &loc,
                                             const pni::core::string &lname)
                -> pni::io::nx::nxpath;
                                            
        public:
            
            //!
            //! \brief get link name
            //!
            //! Return the name of the link with index index.
            //!
            //! \throws invalid_object_error if loc is not a valid group
            //! \throws index_error if index exceeds the total number of links
            //!                     below loc
            //! \throws object_error in case of any other error
            //!
            //! \param loc the parent group object
            //! \param index the index of the link
            //! \return the name of link index
            //!
            static auto link_name(const group_imp &loc,size_t index)
                -> pni::core::string;

            //----------------------------------------------------------------
            //!
            //! \brief get link target
            //!
            //! Return the target for the link with index index in group loc.
            //! 
            //! \throw invalid_object_error if loc is not a valid group
            //! \throw index_error if index exceeds the total number of links
            //! \throw link_error in case that the value cannot be retrieved
            //! \throw object_error in case of any other error
            //! 
            //! \param loc parent group of the link
            //! \param index link index
            //!
            //! \return link target as nxpath instance
            //!
            static auto link_target(const group_imp &loc,size_t index)
                -> pni::io::nx::nxpath;

            //----------------------------------------------------------------
            //!
            //! \brief get link target
            //!
            //! Return the target for the link lname in group loc.
            //! 
            //! \throw invalid_object_error if loc is not a valid group
            //! \throw key_error if a linke lname does not exist
            //! \throw link_error in case that the value cannot be retrieved
            //! \throw object_error in case of any other error
            //! 
            //! \param loc parent group of the link
            //! \param lname the name of the link
            //!
            //! \return link target as nxpath instance
            //!
            static auto link_target(const group_imp &loc,
                                    const pni::core::string &name)
                -> pni::io::nx::nxpath;

            //----------------------------------------------------------------
            //! 
            //! \brief create an external link
            //!
            //! The target path for an external link must be a full Nexus path
            //! including a filename. If it does not contain a filename 
            //! nxlink_error will be thrown. name determines the name of the 
            //! link as a child of loc. The target path must not contain 
            //! element without a name (HDF5 cannot handle such situations) 
            //! otherwise a value_error exception will be thrown.
            //! 
            //! \throws invalid_object_error if loc is not valid
            //! \throws link_error if link creation fails
            //! \throws value_error for malformed paths 
            //! \throws object_error in case of any other error
            //!
            //! \param target path of the links target
            //! \param loc location where the link should be created
            //! \param name linkname below loc
            //!
            static void create_external_link(const nxpath &target,
                                             const group_imp &loc,
                                             const pni::core::string &name);

            //-----------------------------------------------------------------
            //!
            //! \brief create an internal link
            //!
            //! Unlike for external links in the target path can be either 
            //! absolute in the file or relative to loc. name determines the 
            //! name of the link below loc. target_path must not have elements 
            //! without a name. In such a case a value_error will be thrown. 
            //! In addition the target_path Nexus path must not contain a 
            //! file name.
            //!
            //! \throws invalid_object_error if loc is not valid
            //! \throws value_error in case of a malformed path
            //! \throws link_error if link creation fails
            //! \throws object_error in case of any other error
            //!
            //! \param target path to the links target
            //! \param loc location for the new link
            //! \param name name of the object below loc
            //!
            static void create_internal_link(const nxpath &target,
                                             const group_imp &loc,
                                             const pni::core::string &name);

            //-----------------------------------------------------------------
            //!
            //! \brief get link type
            //!
            //! Returns the link type of a child of loc identified by its name. 
            //!
            //! \throws invalid_object_error if loc is not valid
            //! \throws key_error if the child could not be found
            //! \throws link_error if the link type could not be retrieved 
            //! \throws type_error if the link type is unkown
            //! \throws object_error in case of any other error
            //!
            //! \param loc parent group
            //! \param name the name of the child 
            //! \return link type
            //!
            static auto link_type(const group_imp &loc, 
                                  const pni::core::string &name)
                -> pni::io::nx::nxlink_type;

    };
//end of namespace
}
}
}
}
