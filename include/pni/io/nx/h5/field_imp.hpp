//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 16, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <vector>
#include <sstream>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/error.hpp>


#include "object_imp.hpp"
#include "type_imp.hpp"
#include "attribute_imp.hpp"
#include "h5dataspace.hpp"
#include "h5_error_stack.hpp"
#include "../nxexceptions.hpp"
#include "hdf5_utilities.hpp"
#include "attribute_utils.hpp"
#include "h5filter.hpp"


namespace pni{
namespace io{
namespace nx{
namespace h5{

    using namespace pni::core;
    //avoid namespace collisions with std
    using pni::core::exception;
    using pni::core::shape_mismatch_error;
    using pni::core::string;

    //forward declarations
    class group_imp;

    //! 
    //! \ingroup nxh5_classes
    //! \brief dataset object
    //! 
    //! Datasets are the essential data holding objects in HDF5.
    //!
    class field_imp
    {
        private:
            //! object guard
            object_imp _object;
            //! dataspace on file
            h5dataspace _file_space;
            //! dataspace in memory - used for selections
            mutable h5dataspace _memory_space;
            //! datatype on file
            h5datatype  _type;

            //!
            //! \brief update internal parameters
            //! 
            //! This memberfunctions updates the datatype and the 
            //! dataspace of the field.
            //! \throws object_error if update fails
            //! 
            void _update();

            //-----------------------------------------------------------------
            //!
            //! \brief read variable length strings
            //!
            //! Read a dataset with variable length strings.
            //!
            //! \throws nxfield_error in case of IO errors
            //! \param s pointer to targe strings
            //! \param stype file data type
            //!
            void _read_vl_strings(string *s,h5datatype &stype) const;

            //-----------------------------------------------------------------
            //!
            //! \brief read static length strings
            //!
            //! Read array with static length strings. This function is 
            //! mainly to support legacy files which do not use variable 
            //! length strings.
            //!
            //! \throws nxfield_error in case of IO errors
            //! \param s pointer to target strings
            //! \param stype file data type
            //!
            void _read_static_strings(string *s,h5datatype &stype) const;

        public:
            //===================Constructors and destructors==================
            //!
            //! \brief default constructor
            //! 
            explicit field_imp() noexcept;
            
            //-----------------------------------------------------------------
            //! 
            //! \brief move conversion constructor
            //! 
            //! Allows move conversion from an HDF5Object to an HDF5 dataset. 
            //! If the object does not refer to a dataset an exception will 
            //! be thrown.
            //!
            //! \throws type_error if o does not refer to a dataset
            //! \param o move reference to an H5Object
            //!
            explicit field_imp(object_imp &&o);

            //-----------------------------------------------------------------
            //!
            //! \brief create field
            //!
            //! 
            //! \throws size_mismatch_error in case that either shape or chunk
            //! empty or their sizes do not match
            //! \throws object_error in case of any other failure 
            //! \param parent the parent group for the field
            //! \param name the name of the field
            //! \param shape the number of elements along each dimension
            //! \param chunk the chunk shape
            //! \param filter reference to an optional filter 
            //! 
            explicit field_imp(const group_imp &parent,const string &name,
                               type_id_t tid,
                               const type_imp::index_vector_type &shape,
                               const type_imp::index_vector_type &chunk,
                               const h5filter &filter = h5filter());

            //-----------------------------------------------------------------
            //!
            //! \brief copy constructor
            //! 
            //! \throws object_error if copy operation fails
            //!
            field_imp(const field_imp &o);

            //-----------------------------------------------------------------
            //!
            //! \brief move constructor
            //!
            field_imp(field_imp &&o) noexcept;

            //======================assignment operators=======================
            //!
            //! \brief copy assignment operator
            //!
            field_imp &operator=(const field_imp &o);

            //-----------------------------------------------------------------
            //! 
            //! \brief move assignment operator
            //! 
            field_imp &operator=(field_imp &&o) noexcept;

            //=================methods to modify the dataset===================
            //! 
            //! \brief resize the dataset
            //!
            //! Set the shape of the dataset to s. The new shape must satisfy 
            //! some restrictions: 
            //!
            //! \li the rank of s must not exceed the rank of the orignal 
            //! dataset
            //! \li the new number of elements of each dimension must not 
            //! exceed the maximum number of elements along each dimension as 
            //! set in the dataspace used to create the dataset.
            //!
            //! If this requirements are not met by s an exception will be
            //! thrown.
            //!
            //! \throws shape_mismatch_error if rank of s is not equal to 
            //! the rank of the dataset
            //! \throws object_error in case of other errors during resizeing
            //! \param s shape object describing the new shape of the dataset
            //!
            void resize(const type_imp::index_vector_type &s);

            //-----------------------------------------------------------------
            //! 
            //! \brief extend the shape along a dimension
            //!
            //! Extends the size of the dataset along a single dimension.  This
            //! command can be quite useful for writing data sequentially. 
            //!
            //! \throws index_error if e exceeds the rank of the dataset
            //! \throws pni::io::nx::nxfield_error in case of other errors
            //! \param e index of the extend dimension
            //! \param n number of elements by which the dimension shall be
            //! extended
            //!
            void grow(const size_t &e=0,const size_t &n=1);

            //-----------------------------------------------------------------
            //! 
            //! \brief total number of elements
            //!
            //! Returns the total number of elements stored in the dataset.
            //! \return total number of elements
            //!
            size_t size() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief shape of dataset
            //!
            //! Returns a copy of the datasets shape. 
            //! \return dataset shape
            //!
            type_imp::index_vector_type shape() const;

            //-----------------------------------------------------------------
            //!
            //! \brief rank of the dataset
            //!
            //! Returns the number of dimensions of the dataset.
            //!
            //! \return number of dimensions
            //!
            size_t rank() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief datatype ID
            //!
            //! Datatype ID of the dataset. 
            //!
            //! \return type id of the datatype of the dataset
            //!
            type_id_t type_id() const ;


            //-----------------------------------------------------------------
            //!
            //! \brief apply a selection
            //! 
            void apply_selection(const type_imp::selection_vector_type &s) const;

            //----------------------------------------------------------------
            //! remove a selection
            void clear_selections() const;

            //===================reading data methods==========================
            //! 
            //! \brief reading simple data from the dataset
            //!
            //! Read a single data value from the dataset. In order to 
            //! succeed the dataset must be a scalar dataset or the total size 
            //! of the dataset must be 1.
            //!
            //! \throws shape_mismatch_error if dataset is not scalar or the 
            //! size of the dataset is not 1
            //! \throws pni::io::nx::nxfield_error in all other error cases
            //! \param ptr pointer to memory where the data should be stored.
            //!
            template<typename T> void read(T *ptr) const
            {
                //select the proper memory data type
                const h5datatype &mem_type = get_type(type_id_map<T>::type_id);

                //write data to disk
                herr_t err = H5Dread(_object.id(),
                                     mem_type.object().id(),
                                     _memory_space.object().id(),
                                     _file_space.object().id(),
                                      H5P_DEFAULT,
                                      (void *)ptr);
                if(err<0)
                    throw pni::io::nx::nxfield_error(EXCEPTION_RECORD, 
                          "Error writing data to dataset ["
                          +get_object_path(_object.id())+"]!\n\n"
                          +get_h5_error_string());
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief read a string scalar
            //!
            //! Read data to a String variable. This is a specialized version 
            //! of the template method read(T &value). It is necessary since 
            //! strings are handled slightly different from other objects.
            //! 
            //! \throws shape_mismatch_error if the dataset is not scalar
            //! \throws pni::io::nx::nxfield_error in case of other IO errors
            //! \param sptr pointer to String objects
            //!
            void read(string *sptr) const;

            //===============writing data methods==============================
            //! 
            //! \brief write a single value
            //!
            //! This method writes a single value of a particular type reading 
            //! the data from variable value. This method works only if the 
            //! dataspace of the dataset is scalar or the total dataspace size 
            //! is 1.
            //!
            //! \throws shape_mismatch_error if the dataspace is not scalar
            //! \throws pni::io::nx::nxfield_error in case of other errors
            //! \param ptr pointer to the memory region from which to read
            //!
            template<typename T> void write(const T *ptr) const
            {
                //select the proper memory data type
                const h5datatype &mem_type = get_type(type_id_map<T>::type_id);

                //write data to disk
                herr_t err = H5Dwrite(_object.id(),
                                      mem_type.object().id(),
                                      _memory_space.object().id(),
                                      _file_space.object().id(),
                                      H5P_DEFAULT,
                                      (const void *)ptr);
                if(err<0)
                    throw pni::io::nx::nxfield_error(EXCEPTION_RECORD, 
                        "Error writing data to dataset ["
                        +get_object_path(_object.id())+"]!\n\n"+
                        get_h5_error_string());
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief write a String value
            //! 
            //! Write data from a String variable to the dataset.
            //!
            //! \throws shape_mismatch_error if the dataset is not scalar
            //! \throws pni::io::nx::nxfield_error in the case of all other 
            //! errors
            //! \param sptr pointer to String objects.
            //!
            void write(const string *sptr) const;

            //=================================================================
            // DEFAULT OBJECT METHODS
            //=================================================================
            //----------------------------------------------------------------
            //!
            //! \brief get name
            //! 
            //! Return the name of the group.
            //!
            //! \throws invalid_object_error if object is not valid
            //! \throws io_error if name of the group cannot be retrieved
            //! \return name of the group
            //! 
            string name() const;

            //---------------------------------------------------------------
            //! 
            //! \brief get parent object
            //! 
            //! Return the parent of the current group. 
            //!
            //! \throws object_error in case of errors
            //! 
            object_imp parent() const;

            //----------------------------------------------------------------
            //!
            //! \brief get filename
            //! 
            //! Return the name of the file holding this group.
            //! 
            //! \throws io_error if filename cannot be retrieved
            //! 
            //! \return filename
            //!
            string filename() const;

            //-----------------------------------------------------------------
            //!
            //! \brief close the dataset
            //!
            //! Method closing the dataset.
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

            //=================================================================
            //ATTRIBUTE INTERFACE
            //=================================================================

            //----------------------------------------------------------------
            //!
            //! \brief create scalar attribute
            //!
            //! Create a simple scalar attribute 
            //! \throws object_error if attribute creation fails
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
            //! \throws object_error if attribute reation fails
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
            //! \throws key_error if attribute does not exist
            //! \throws object_error if attribute retrievel fails
            //! \param name name of the requested attribute
            //! \return instance of attribute_imp
            //! 
            attribute_imp attr(const string &name) const;

            //----------------------------------------------------------------
            //!
            //! \brief get attribute by index
            //! 
            //! \throws index_error if i exceeds the total number of attributes
            //! \throws object_error if attribute retrieval fails
            //! \param i attribute index
            //! \return instance of attribute_imp
            //! 
            attribute_imp attr(size_t i) const;

            //----------------------------------------------------------------
            //!
            //! \brief get number of attributes
            //! 
            //! Returns the total number of attribtues attached to this group.
            //! \returns number of attributes
            //!
            size_t nattr() const noexcept;

            //----------------------------------------------------------------
            //!
            //! \brief check if attribute exists
            //! 
            //! Returns true if the group has an attribute of the requested
            //! name, false otherwise.
            //! \throws object_error if attribute check fails
            //! \param name the name of the looked up attribute
            //! \return true if attribute exists, flase otherwise
            //!
            bool has_attr(const string &name) const;

            //----------------------------------------------------------------
            //!
            //! \brief delete an attribute
            //!
            //! Remove an attribute from this group. 
            //! \throws object_error if attribute removal fails
            //! \param name the name of the attribute to delete
            //! 
            void del_attr(const string &name) const;
    };


//end of namespace
}
}
}
}
