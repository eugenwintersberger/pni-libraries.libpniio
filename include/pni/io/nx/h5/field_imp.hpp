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

#include <pni/core/types.hpp>


#include "object_imp.hpp"
#include "type_imp.hpp"
#include "h5dataspace.hpp"
#include "h5datatype.hpp"
#include "h5filter.hpp"
#include "attribute_imp.hpp"
#include "selection.hpp"


namespace pni{
namespace io{
namespace nx{
namespace h5{

    using namespace pni::core;
    //avoid namespace collisions with std

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
            //! local selection object
            selection _selection;
            bool _selection_applied;


            //!
            //! \brief update internal parameters
            //! 
            //! This memberfunctions updates the datatype and the 
            //! dataspace of the field.
            //!
            //! \throws invalid_object_error if data space is invalid
            //! \throws type_error if the object is not a dataspace
            //! \throws object_error if update fails
            //! 
            void _update();

            //----------------------------------------------------------------
            //!
            //! \brief read data from file
            //! 
            //! Reads a data from the file and stores it in a memory location 
            //! refered to by ptr. 
            //! 
            //! \throws io_error in case of errors
            //! 
            //! \param memtye memory data type
            //! \param memspace memory data space
            //! \param filespace file data space
            //! \param xfer_list data transfer property list
            //! \param ptr pointer to memory region
            //! 
            void _read_data(const h5datatype &memtype,
                           const h5dataspace &memspace,
                           const h5dataspace &filespace,
                           const object_imp &xfer_list,
                           void *ptr) const;

            //----------------------------------------------------------------
            //!
            //! \brief write data to file
            //! 
            //! Write data from memory (referenced by ptr) to the dataset.
            //! 
            //! \throws io_error in case of Input-output-errors
            //!
            //! \param memtype memory data type
            //! \param memspace memory data space
            //! \param filespace file data space
            //! \param ptr pointer to the source region in memory
            //!
            void _write_data(const h5datatype &memtype,
                             const h5dataspace &memspace,
                             const h5dataspace &filespace,
                             const void *ptr) const;

            //-----------------------------------------------------------------
            //!
            //! \brief throw if not valid
            //! 
            //! Throws an exception if the field object is not valid. 
            //! 
            //! \throws invalid_object_error if field object is not valid
            //! \throws object_error if the validity of any of the objects
            //! cannot be determined
            //!
            //! \param record the exception record
            //! \param message the message which should be attached to the 
            //! exception
            //! 
            void _throw_if_not_valid(const exception_record &record,
                                     const string &message) const
            {
                if(!is_valid())
                    throw invalid_object_error(record,message);
            }

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
            //! \throws invalid_object_error if the object is not valid
            //! \throws object_error in case of any other error during object 
            //! construction
            //! 
            //! \param o move reference to an H5Object
            //!
            explicit field_imp(object_imp &&o);

            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! 
            //! \throws size_mismatch_error in case that either shape or chunk
            //! empty or their sizes do not match
            //! \throws object_error in case of any other failure 
            //! \throws type_error if tid has no corresponding HDF5 type
            //! \throws invalid_object_error if parent object is not valid
            //!
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


            //=================methods to modify the dataset===================
            //! 
            //! \brief extend the shape along a dimension
            //!
            //! Extends the size of the dataset along a single dimension.  This
            //! command can be quite useful for writing data sequentially. 
            //!
            //! \throws index_error if e exceeds the rank of the dataset
            //! \throws object_error in case of other errors
            //! \throws invalid_object_error if field is not valid
            //! 
            //! \param e index of the extend dimension
            //! \param n number of elements by which the dimension shall be
            //! extended
            //!
            void grow(const size_t &e=0,const size_t &n=1) ;

            //-----------------------------------------------------------------
            //! 
            //! \brief total number of elements
            //!
            //! Returns the total number of elements stored in the dataset.
            //!
            //! \throws invalid_object_error field object not valid
            //! \throws object_error in case of size retrieval failed
            //! 
            //! \return total number of elements
            //!
            size_t size() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief shape of dataset
            //!
            //! Returns a copy of the datasets shape. 
            //! 
            //! \throws invalid_object_error if field not valid
            //! \throws object_error in case of any other error
            //!
            //! \return dataset shape
            //!
            type_imp::index_vector_type shape() const;

            //-----------------------------------------------------------------
            //!
            //! \brief rank of the dataset
            //!
            //! Returns the number of dimensions of the dataset.
            //!
            //! \throws invalid_object_error if field object not valid
            //! \throws object_error in case of any other error
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
            //! \throws invalid_object_error if field object not valid
            //! \throws object_error in case of any other error
            //! \throws type_error if the type cannot be determined 
            //!
            //! \return type id of the datatype of the dataset
            //!
            type_id_t type_id() const ;

            //-----------------------------------------------------------------
            //!
            //! \brief apply a selection
            //!
            //! \throw invalid_object_error if object not valid
            //! \throw shape_mismatch_error if selection size and rank of the
            //! field do not match
            //! \throw object_error in case of any other error
            //!
            //! \param s vector with slices describing the selection
            //! 
            void apply_selection(const type_imp::selection_vector_type &s);

            //----------------------------------------------------------------
            //!
            //! \brief remove a selection
            //!
            //! \throw object_error in case of any error
            //!
            void clear_selections() ;

            //===================reading data methods==========================
            //! 
            //! \brief reading simple data from the dataset
            //!
            //! Read a single data value from the dataset. In order to 
            //! succeed the dataset must be a scalar dataset or the total size 
            //! of the dataset must be 1.
            //!
            //! \throws invalid_object error if field is not valid
            //! \throws object_error in case of a general error
            //! \throws type_error if tid has no corresponding HDF5 type
            //! \throws io_error in case of IO failure
            //!
            //! \param tid type id of the original data type in memory
            //! \param ptr pointer to memory where the data should be stored.
            //!
            void read(type_id_t tid,const type_imp::index_vector_type &shape,
                      void *ptr) const;

            //===============writing data methods==============================
            //! 
            //! \brief write a single value
            //!
            //! This method writes a single value of a particular type reading 
            //! the data from variable value. This method works only if the 
            //! dataspace of the dataset is scalar or the total dataspace size 
            //! is 1.
            //! 
            //! \throws invalid_object_error in case of IO errors
            //! \throws io_error in case of IO errors
            //! \throws object_error  in case of all other errors
            //! \throws type_error if tid does not have a corresponding HDF5
            //! data type
            //!
            //! \param tid type id for the strings
            //! \param ptr pointer to the memory region from which to read
            //!
            void write(type_id_t tid,const type_imp::index_vector_type &shape,
                       const void *ptr) const;


            //=================================================================
            // DEFAULT OBJECT METHODS
            //=================================================================
            //!
            //! \brief get name
            //! 
            //! Return the name of the group.
            //!
            //! \throws invalid_object_error if object is not valid
            //! \throws io_error if name of the group cannot be retrieved
            //! \throws object_error in case of any other error
            //! \throws type_error if object type is not known
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
            //! \throws invalid_object_error if field is not valid
            //! \throws object_error in case of errors
            //! \throws type_error if the type of the object could not be 
            //! determined
            //! 
            //! \return parent object as object_imp
            //! 
            object_imp parent() const;

            //----------------------------------------------------------------
            //!
            //! \brief get filename
            //! 
            //! Return the name of the file holding this group.
            //! 
            //! \throws invalid_object_error if field object not valid
            //! \throws io_error if filename cannot be retrieved
            //! \throws object_error in case of any other error
            //! \throws type_error if object is of wrong type
            //! 
            //! \return name of the file the field belongs to
            //!
            string filename() const;

            //-----------------------------------------------------------------
            //!
            //! \brief close the dataset
            //!
            //! Method closing the dataset.
            //!
            //! \throw type_error if type is not supported
            //! \throw object_error in case of any other error
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
            //! 
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
            //!
            //! \throws object_error if attribute creation fails
            //! \throws invalid_object_error if parent field not valid
            //! \throws type_error if tid has no corresponding HDF5 type
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
            //! \throws object_error if attribute reation fails
            //! \throws invalid_object_error if parent field not valid
            //! \throws type_error if tid has no corresponding HDF5 type
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
            //! \throws key_error if attribute does not exist
            //! \throws object_error if attribute retrievel fails
            //! \throws invalid_object_error if parent field not valid
            //!
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
            //! \throws invalid_object_error if parent field not valid
            //!
            //! \param i attribute index
            //! \return instance of attribute_imp
            //! 
            attribute_imp attr(size_t i) const;

            //----------------------------------------------------------------
            //!
            //! \brief get number of attributes
            //!
            //! \throws invalid_object_error if parent field not valid
            //! \throws object_error in case of of any other error
            //! 
            //! Returns the total number of attribtues attached to this group.
            //! \returns number of attributes
            //!
            size_t nattr() const ;

            //----------------------------------------------------------------
            //!
            //! \brief check if attribute exists
            //! 
            //! Returns true if the group has an attribute of the requested
            //! name, false otherwise.
            //!
            //! \throws object_error if attribute check fails
            //! \throws invalid_object_error if parent field not valid
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
            //! \throws object_error if attribute removal fails
            //! \throws key_error if attribute name does not exist
            //! \throws invalid_object_error if parent field does not exist
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
