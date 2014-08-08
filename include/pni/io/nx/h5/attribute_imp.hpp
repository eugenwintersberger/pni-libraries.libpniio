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

#include<sstream>

#include <pni/core/types.hpp>

#include "object_imp.hpp"
#include "type_imp.hpp"
#include "h5dataspace.hpp"
#include "h5datatype.hpp"

namespace pni{
namespace io{
namespace nx{
namespace h5{
    using namespace pni::core;
    //avoid namespace collisions with std
    using pni::core::exception;
    using pni::core::string;

    //! 
    //! \ingroup nxh5_classes
    //! \brief attribute implementation
    //! 
    class attribute_imp
    {
        private:
            //! handler to the undlying attribute object
            object_imp    _object;
            //! handler to the dataspace object of the attribute
            h5dataspace _dspace; 
            //! handler to the datatype object of the attribute
            h5datatype  _dtype;   

            //-----------------------------------------------------------------
            //! 
            //! \brief set dataspace and datatype
            //!
            //! This ethod uses the HDF5 ID of an attribute object to obtain 
            //! the dataspace and the datatype.  Thus it sets the internal 
            //! state of the class.
            //! 
            //! \throws object_error in case of any error
            //! \throws type_error in case of errors when retrieving dataspace
            //! and datatype
            //!
            void __update();
            
            //----------------------------------------------------------------
            //! 
            //! \brief read data to void
            //! 
            //! Read attribute data from disk using memtype memory
            //! representation.
            //!
            //! \throws io_error in case of read problems
            //!
            //! \param memtype type of data in memory
            //! \param ptr pointer to the target location in memory
            //!
            void _read_data(const h5datatype &memtype,void *ptr) const;

            //-----------------------------------------------------------------
            //! 
            //! \brief write data from memory
            //! 
            //! Write data from a memory location denoted by ptr. 
            //! 
            //! \throws io_error in case of write problems
            //!
            //! \param memtype memory datatype 
            //! \param ptr pointer to the source region in memory
            //!
            void _write_data(const h5datatype &memtype,const void *ptr) const;
        
        public:
            //==============-====constructors and destructors===================
            //!
            //! \brief default constructor
            //! 
            explicit attribute_imp() noexcept;
            
            //-----------------------------------------------------------------
            //! 
            //! \brief construct from HDF5 type ID
            //!
            //! Construct the attribute object form an existing instance of 
            //! h5object. 
            //! 
            //! \throws type_error if object is not an attribute type
            //! \param id HDF5 id of the attribute object.
            //!
            explicit attribute_imp(object_imp &&object);

            //===================reading and writting data=====================
            //----------------------------------------------------------------
            //!
            //! \brief write data from void
            //!
            //! The memory data type relies entirely on the tid argument passed
            //! to this function. 
            //! 
            //! \throws io_error in case of errors
            //! \param tid type id of allocated memory
            //! \param ptr pointer to the region of memory
            //!
            void write(type_id_t tid,const void *ptr) const;

            //----------------------------------------------------------------
            //!
            //! \brief read data to void 
            //! 
            //! Read data to a region of memory referenced by a void pointer.
            //! The memory type information relies entirely on the tid 
            //! argument
            //! 
            //! \throws io_error in case of read errors
            //! \throws invalid_object_error if the attribute is not valid
            //! \throws object_error in any other case of failure
            //! 
            //! \param tid type id of memory
            //! \param ptr pointer to memory
            //!
            void read(type_id_t tid,void *ptr) const;

            //=================attribute inquery methods=======================
            //! 
            //! \brief obtain attribute shape
            //!
            //! Returns the shape of the attribute.
            //! \return shape object
            //!
            type_imp::index_vector_type shape() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief return type_id
            //!
            //! Return the ID of the datatype used for the attribute.
            //! \return type ID
            //!
            type_id_t type_id() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief get size
            //!
            //! Return  the total number of elements stored in the attribute.
            //! \return number of elements
            //!
            size_t size() const;

            //-----------------------------------------------------------------
            //!
            //! \brief get rank
            //!
            //! Get the number of dimensions.
            //! \return number of dimensions
            //!
            size_t rank() const;

            //-----------------------------------------------------------------
            //!
            //! \brief check validity
            //! 
            //! Returns true if the attribute is a valid object, false
            //! otherwise.
            //!
            //! \throws object_error if validity check fails
            //! \return true if valid, false otherwise
            //! 
            bool is_valid() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief get name
            //!
            //! Return the name of the attribute as string.
            //! 
            //! \throws io_error in case of errors
            //! \return attribute name
            //!
            string name() const;

            //----------------------------------------------------------------
            //! 
            //! \brief get filename
            //! 
            //! Return the name of the file where this attribute is stored.
            //!
            //! \throws io_error if the filename cannot be retrieved
            //! 
            //! \return file name
            //! 
            string filename() const;

            //-----------------------------------------------------------------
            //!
            //! \brief get parent
            //!
            //! Return an instance of H5Object with the parent object of the
            //! attribute.
            //!
            //! \throws invalid_object_error if attribute is not valid
            //! \throws type_error if parent type could not be determined
            //! \throws object_error if parent object could not be retrieved
            //! \return H5Object instance
            //!
            object_imp parent() const;

            //-----------------------------------------------------------------
            //!
            //! \brief close object
            //! 
            void close();
    };


//end of namespace
}
}
}
}
