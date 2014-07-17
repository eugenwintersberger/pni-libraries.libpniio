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
#include "attribute_imp.hpp"
#include "h5dataspace.hpp"
#include "h5_error_stack.hpp"
#include "../nxexceptions.hpp"
#include "hdf5_utilities.hpp"


namespace pni{
namespace io{
namespace nx{
namespace h5{

    using namespace pni::core;
    //avoid namespace collisions with std
    using pni::core::exception;
    using pni::core::shape_mismatch_error;
    using pni::core::string;

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

            typedef std::vector<hsize_t> size_vector_t;

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
            //! \throws pni::io::nx::nxfield_error in case of other errors 
            //! during resizeing
            //! \param s shape object describing the new shape of the dataset
            //!
            template<typename CTYPE> void resize(const CTYPE &s)
            {
                if(s.size() != _file_space.rank())
                    throw shape_mismatch_error(EXCEPTION_RECORD,
                          "New shape does not have the same rank!");

                std::vector<hsize_t> b(s.size());
                std::copy(s.begin(),s.end(),b.begin());

                herr_t err = H5Dset_extent(_object.id(),b.data());
                if(err < 0)
                    throw pni::io::nx::nxfield_error(EXCEPTION_RECORD, 
                         "Resizing of dataset ["+get_object_path(_object.id())
                         +"] failed!\n\n"+ get_h5_error_string());

                _update();
            }

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
            template<typename CTYPE> CTYPE shape() const
            {
                CTYPE s(_memory_space.rank());
                std::copy(_memory_space.current_begin(),
                          _memory_space.current_end(),
                          s.begin());
                return s;
            }

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
            //! \brief number of elements
            //!
            //! Returns the number of elements along dimension i. 
            //!
            //! \throws index_error if i exceeds dataset rank
            //! \param i index of the dimension
            //! \return number of elements along i
            //!
            size_t dim(const size_t &i) const;

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
            //! apply a selection
            template<typename CTYPE> void apply_selection(const CTYPE &s) 
            {
                std::vector<slice> sel(s.size());
                std::copy(s.begin(),s.end(),sel.begin());

                //create an array selection
                array_selection asel = array_selection::create(sel);
                
                //create buffers
                auto offset = asel.offset<std::vector<hsize_t> >();
                auto stride = asel.stride<std::vector<hsize_t> >();
                auto count = asel.full_shape<std::vector<hsize_t> >();

                //need to throw an exception if the rank of the selection and
                //that of the 
                if(offset.size() != _file_space.rank())
                    throw shape_mismatch_error(EXCEPTION_RECORD,
                            "Selection and field rank do not match!");

                //apply the selection
                herr_t err = H5Sselect_hyperslab(_file_space.object().id(),
                        H5S_SELECT_SET,offset.data(),stride.data(),count.data(),
                        nullptr);
                if(err<0)
                    throw pni::io::nx::nxfield_error(EXCEPTION_RECORD,
                            "Error applying selection to dataset!\n\n"+
                            get_h5_error_string());

                //need to set the memory dataspace to the effective shape of the
                //selection
                _memory_space = h5dataspace(asel.shape<std::vector<size_t>>());

            }

            //----------------------------------------------------------------
            //! remove a selection
            void clear_selections() const
            {
                //this should be quite easy - there is nothing special we have
                ///to do.
                if(_file_space.object().is_valid())
                {
                    H5Sselect_all(_file_space.object().id());
                    _memory_space = _file_space;
                }
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief return dataspace
            //!
            //! Returns a const. reference to the dataspace of the dataset.
            //!
            //! \return const reference to the dataspace
            //!
            const h5dataspace &space() const
            {
                return _file_space;
            }


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


            //-----------------------------------------------------------------
            //!
            //! \brief close the dataset
            //!
            //! Method closing the dataset.
            //!
            virtual void close();

    };


//end of namespace
}
}
}
}
