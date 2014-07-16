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
#include <pni/core/arrays.hpp>

#include "object_imp.hpp"
#include "h5dataspace.hpp"
#include "h5datatype.hpp"

#include "h5_error_stack.hpp"
#include "../nxexceptions.hpp"

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

            //------------------------------------------------------------------
            //!
            //! \brief read variable length string attributes       
            //! 
            //! Read an attribute with variable length strings. 
            //! \throws io_error in case of errors
            //! \param s pointer to target strings
            //! \param stype string type
            //!
            void _read_vl_strings(string *s) const; 

            //------------------------------------------------------------------
            //!
            //! \brief read static length string attribute
            //!
            //! Read an attribute with static string attributes (strings of 
            //! constant size).
            //!
            //! \param s pointer to target strings
            //! \param stype string type
            //!
            void _read_static_strings(string *s) const;


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

            //-----------------------------------------------------------------
            //!
            //! \brief copy constructor
            //! 
            //! \throws object_error in case of errors
            //!
            attribute_imp(const attribute_imp &o);

            //-----------------------------------------------------------------
            //!
            //! \brief move constructor
            //! 
            attribute_imp(attribute_imp &&o) noexcept;

           

            //=====================assignment operators========================
            //!
            //! \brief copy assignment operator
            //! 
            //! \ingroup object_error in case of assignment issues
            //!
            attribute_imp &operator=(const attribute_imp &a);

            //-----------------------------------------------------------------
            //!
            //! \brief move assignment operator
            //! 
            attribute_imp &operator=(attribute_imp &&o) noexcept;

            //===================reading and writting data=====================
            //!
            //! \brief pointer write
            //!
            //! Private method writing data from memory addressed by 
            //! ptr to the attribute.
            //! \tparam T data type in memory
            //! \throws io_error in case of IO errors
            //! \param ptr pointer to memory
            //!
            template<typename T> void write(const T *ptr) const
            {
                const h5datatype &mem_type = get_type(type_id_map<T>::type_id);
                herr_t err = H5Awrite(_object.id(),
                                      mem_type.object().id(),
                                      const_cast<void *>(ptr));
                if(err<0)
                    throw io_error(EXCEPTION_RECORD, 
                        "Error writing attribute ["+this->name()+"]!\n\n"+
                        get_h5_error_string());
            }

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


            //-----------------------------------------------------------------
            //!
            //! \brief write string attribute
            //!
            //! Write data to a string attribute.
            //! 
            //! \throws io_error in case of input output issues
            //! \param s string to write
            //!
            void write(const string *s) const;

            //-----------------------------------------------------------------
            //!
            //! \brief handle C-style strings
            //!
            //! This method is used as a string constant is not converted to 
            //! String but rather to const char *. This method is called in 
            //! the following example
            /*!
            \code
            H5Attribute a=...;
            a.write("hello word");
            \endcode
            */
            //! \param s pointer to the character string
            //!
            void write(const char *s) const 
            {
                string str(s);
                write(&str);
            }
          
            //-----------------------------------------------------------------
            //! 
            //! \brief pointer read
            //!
            //! Private method reading data form the attribute to a memory 
            //! region addressed by ptr. An exception is thrown if an error 
            //! occurs
            //!
            //! \tparam T type of data in memory
            //! \throws pni::io::nx::nxattribute_error in case of IO errors
            //! \param ptr pointer to memory
            //!
            template<typename T> void read(T *ptr) const
            {
                const h5datatype &mem_type = get_type(type_id_map<T>::type_id);
                herr_t err = H5Aread(_object.id(),
                                     mem_type.object().id(),
                                     const_cast<void *>(ptr));
                if(err < 0)
                    throw pni::io::nx::nxattribute_error(EXCEPTION_RECORD,
                            "Error reading attribute ["+this->name()+"]!\n\n"+
                            get_h5_error_string());
            }

            //----------------------------------------------------------------
            //!
            //! \brief read data to void 
            //! 
            //! Read data to a region of memory referenced by a void pointer.
            //! The memory type information relies entirely on the tid 
            //! argument
            //! 
            //! \param tid type id of memory
            //! \param ptr pointer to memory
            //!
            void read(type_id_t tid,void *ptr) const;

            //-----------------------------------------------------------------
            //! 
            //! \brief read to string
            //!
            //! Reads a string value from an attribute.
            //! \throws shape_mismatch_error if attribute is not scalar
            //! \throws H5AttributeError in case of general IO errors
            //! \param s string variable to which data will be written
            //!
            void read(string *s) const;
           
            //=================attribute inquery methods=======================
            //! 
            //! \brief obtain attribute shape
            //!
            //! Returns the shape of the attribute.
            //! \return shape object
            //!
            template<typename CTYPE> CTYPE shape() const
            {
                CTYPE s(_dspace.rank());
                std::copy(_dspace.current_begin(),
                          _dspace.current_end(),
                          s.begin());
                return s;
            }

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
            size_t size() const { return this->_dspace.size(); }

            //-----------------------------------------------------------------
            //!
            //! \brief get rank
            //!
            //! Get the number of dimensions.
            //! \return number of dimensions
            //!
            size_t rank() const { return this->_dspace.rank(); }


            //-----------------------------------------------------------------
            //! 
            //! \brief get name
            //!
            //! Return the name of the attribute as string.
            //! 
            //! \throws io_error in case of errors
            //! \return attribute name
            //!
            virtual string name() const;

            //-----------------------------------------------------------------
            //!
            //! \brief get parent
            //!
            //! Return an instance of H5Object with the parent object of the
            //! attribute.
            //!
            //! \throws object_error if parent object could not be retrieved
            //! \return H5Object instance
            //!
            object_imp parent() const;
    };


//end of namespace
}
}
}
}
