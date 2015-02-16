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
// Created on: Jan 10, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>

#include "object_imp.hpp"
#include "type_imp.hpp"
#include "hdf5_utilities.hpp"
#include "attribute_utils.hpp"
#include "attribute_imp.hpp"


namespace pni{
namespace io{
namespace nx{
namespace h5{

    using namespace pni::core;
    //avoid namespace collisions with std
    using pni::core::exception;
    using pni::core::string;
    //class forward declarations            
    
    //! 
    //! \ingroup nxh5_classes
    //! \brief HDF5 group object
    //!  
    //! Group objects are the fundamental structuring objects in the HDF5 
    //! world.  They can be identified by a path within the file and 
    //! attributes can be attached to them. 
    //!
    class group_imp
    {
        private:
            //! the HDF5 object representing the group
            object_imp _object;
        public:
            //==========constructors and destructors===========================
            //! 
            //! \brief default constructor
            //! 
            explicit group_imp() noexcept;

            //-----------------------------------------------------------------
            //! 
            //! \brief constructor from object_imp
            //! 
            //! \throws type_error if the object is not a group object
            //! \throws object_error in case of errors
            //! \throws invalid_object_error if the passed object is not valid
            //!
            //! \param o rvalue refernence to an HDF5 object 
            //!
            explicit group_imp(object_imp &&o);

            //-----------------------------------------------------------------
            //! 
            //! \brief constructor 
            //! 
            //! Create a new group below a parent group.
            //!
            //! \throws invalid_object_error if parent group is not valid
            //! \throws object_error in case of errors
            //!
            //! \param parent the parent group for the gnew group
            //! \param name the name of the new group
            //! 
            explicit group_imp(const group_imp &parent,const string &name);

            //=================methods to open objects==========================
            //! 
            //! \brief get child by name
            //!
            //! Opens an arbitrary object. The method takes a path to the 
            //! object and returns an H5Object. As all classes derived from 
            //! H5Object every other object can be constructed from such an 
            //! general H5Object. 
            //!
            //! The path can be either an absolute path or relative to the 
            //! group instance calling this method. Both methods work as 
            //! expected.
            //!
            //! \throws key_error if group has no child with this name
            //! \throws invalid_object_error if group is not valid
            //! \throws object_error in case of any other error
            //!
            //! \param name name of the child object
            //! \return object instance 
            //!
            object_imp at(const string &name) const;

            //-----------------------------------------------------------------
            //! 
            //! \brief open by index
            //! 
            //! Opens a child object below this group by its index. Unlike
            //! open(const String &n) only objects linked to this group can be
            //! opened with this method.
            //!
            //! \throws index_error if index exceeds number of childs
            //! \throws invalid_object_error if group is not valid
            //! \throws object_error in case of any other error
            //!
            //! \param i object index
            //! \return child object
            //!
            object_imp at(size_t i) const;

            //----------------------------------------------------------------
            //!
            //! \brief return object reference
            //! 
            const object_imp &object() const noexcept;

            //======================misc methods===============================
            //! 
            //! \brief remove an object
            //!
            //! This method removes an object of name n attached to this  
            //! group.
            //! 
            //! \throws invalid_object_error if group is not valid
            //! \throws key_error if group does not have a child n
            //! \throws object_error in case of any other error
            //!
            //! \param n name of the object to remove
            //!
            void remove(const string &n) const;

            //----------------------------------------------------------------
            //!
            //! \brief remove an object
            //!
            //! Remove the i-th object from the group. 
            //!
            //! \throws index_error if i exceeds the total number of children
            //! \throws invalid_object_error if the group is not valid
            //! \throws object_error  in case of any other error
            //!
            //! \param i the index of the child to remove
            //! 
            void remove(size_t i) const;
            //-----------------------------------------------------------------
            //! 
            //! \brief check for the existance of an object
            //!
            //! Checks whether or not an object determined by n exists.  n 
            //! can be either a path relative to this object or an absolute 
            //! path. 
            //!
            //! \throws invalid_object_error if the group instance is not valid
            //! \throws object_error if info about child nodes could not have
            //! been obtained 
            //!
            //! \param name of the child node
            //! \return true if an object of name n exists
            //!
            bool has_child(const string &name) const;

            //-----------------------------------------------------------------
            //!
            //! \brief number of child nodes
            //! 
            //! Returns the number of child nodes (groups and datasets) 
            //! linked below this group.
            //!
            //! \throws invalid_object_error if group is not valid
            //! \throws object_error in case of errors
            //!
            //! \return number of child nodes
            //!
            size_t size() const;

            //----------------------------------------------------------------
            //!
            //! \brief get name
            //! 
            //! Return the name of the group.
            //!
            //! \throws invalid_object_error if object is not valid
            //! \throws io_error if name of the group cannot be retrieved
            //! \throws object_error in case of any other err
            //! \throws type_error if the internal object is of wrong type
            //!
            //! \return name of the group
            //! 
            string name() const;

            //---------------------------------------------------------------
            //! 
            //! \brief get parent object
            //! 
            //! Return the parent of the current group. 
            //!
            //! \throws invalid_object_error if the group is not valid
            //! \throws type_error if object type is unkown
            //! \throws object_error in case of errors
            //! \return HDF5 object referring to the groups parent
            //! 
            object_imp parent() const;

            //----------------------------------------------------------------
            //!
            //! \brief get filename
            //! 
            //! Return the name of the file holding this group.
            //! 
            //! \throws io_error if filename cannot be retrieved
            //! \throws invalid_object_error if group is not valid
            //! \throws object_error in case of any other error
            //! \throws type_error in case of problems with the internal object
            //! type
            //! 
            //! \return filename
            string filename() const;

            //----------------------------------------------------------------
            //!
            //! \brief close the group
            //! 
            //! Close the current group. This member function is a delegate to
            //! the close method of the internal object implementation. 
            //! If the object is for some reason of unkown type and thus 
            //! cannot be closed a type_error exception is thrown.
            //! 
            //! \throws object_error if the object validity check failed
            //! \throws type_error if the type if the object could not be 
            //! determined.
            //! 
            void close();

            //----------------------------------------------------------------
            //!
            //! \brief check group validity
            //! 
            //! Returns true if the group is a valid object, false otherwise. 
            //! 
            //! \throws object_error if the validity of the object chould not be
            //! checked. 
            //! \return true if valid, false otherwise
            //!
            bool is_valid() const;

            //----------------------------------------------------------------
            //!
            //! \brief create scalar attribute
            //!
            //! Create a simple scalar attribute 
            //!
            //! \throws object_error if attribute creation fails
            //! \throws invalid_object_error if parent object is not valid
            //! \throws type_error if the requested type has no HDF5 equivalent
            //!
            //! \param name the name of the new attribute
            //! \param tid type id for the attribute
            //! \param overwrite if true overwrite an existing attribute
            //! \return instance of attribute_imp
            //!
            attribute_imp attr(const string &name,type_id_t tid,
                               bool overwrite=false) const;

            //----------------------------------------------------------------
            //! 
            //! \brief create multidimensional attribute
            //! 
            //! Create a multidimensional attribute.
            //!
            //! \throws object_error if attribute creation fails
            //! \throws invalid_object_error if parent object is not valid
            //! \throws type_error if the requested type has no HDF5 equivalent
            //!
            //! \param name the name for the attribute
            //! \param tid type id for the attribute
            //! \param shape container with number of elements
            //! \param overwrite when true overwrite existing attribute
            //! \return instance of attribute_imp
            //! 
            attribute_imp attr(const string &name,type_id_t tid,
                               const type_imp::index_vector_type &shape,
                               bool overwrite=false) const;

            //----------------------------------------------------------------
            //!
            //! \brief get attribute by name
            //!
            //! \throws invalid_object_error if group is not valid
            //! \throws key_error if attribute does not exist
            //! \throws object_error if attribute retrievel fails
            //!
            //! \param name name of the requested attribute
            //! \return instance of attribute_imp
            //! 
            attribute_imp attr(const string &name) const;

            //----------------------------------------------------------------
            //!
            //! \brief get attribute by index
            //! 
            //! \throws invalid_object_error if group is not valid
            //! \throws index_error if i exceeds the total number of attributes
            //! \throws object_error if attribute retrieval fails
            //!
            //! \param i attribute index
            //! \return instance of attribute_imp
            //! 
            attribute_imp attr(size_t i) const;

            //----------------------------------------------------------------
            //!
            //! \brief get number of attributes
            //! 
            //! Returns the total number of attribtues attached to this group.
            //!
            //! \throws invalid_object_error if group is not valid
            //! \throws object_error in case of any other error
            //!
            //! \returns number of attributes
            //!
            size_t nattr() const;

            //----------------------------------------------------------------
            //!
            //! \brief check if attribute exists
            //! 
            //! Returns true if the group has an attribute of the requested
            //! name, false otherwise.
            //!
            //! \throws invalid_object_error if group is not valid
            //! \throws object_error if attribute check fails
            //!
            //! \param name the name of the looked up attribute
            //! \return true if attribute exists, flase otherwise
            //!
            bool has_attr(const string &name) const;

            //----------------------------------------------------------------
            //!
            //! \brief delete an attribute
            //!
            //! Remove an attribute from this group. 
            //!
            //! \throws invalid_object_error if group is not valid
            //! \throws key_error if an attribute with the requested name does 
            //! not exist
            //! \throws object_error if attribute removal fails
            //!
            //! \param name the name of the attribute to delete
            //! 
            void del_attr(const string &name) const;


    };


        
//end of namespace
}
}
}
}
