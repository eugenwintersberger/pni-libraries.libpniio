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

#include<sstream>

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>


#include "H5NamedObject.hpp"
#include "H5Dataspace.hpp"
#include "H5Datatype.hpp"
#include "H5DatatypeFactory.hpp"

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
    //! \brief HDF5 attribute object
    //! 
    //! An HDF5 attribute behaves basically like a dataset with the exception 
    //! that (for obvious reasons) no other attributes can be attached to it. 
    //! In addition attributes cannot use compression nor can they be used 
    //! along with a chunked layout.  Attribute objects are derived from 
    //! H5NamedObject. However, the semantics of the name(), base(), and 
    //! path() methods is slightly different.  name() returns the name of 
    //! the attribute while base() and path() return emtpy strings as an 
    //! attribute
    //!  
    class H5Attribute:public H5NamedObject
    {
        private:
            H5Dataspace _dspace; //!< dataspace of the attribute
            H5Datatype _dtype;   //!< data type of the attribute

            //-----------------------------------------------------------------
            //! 
            //! \brief set dataspace and datatype
            //!
            //! This ethod uses the HDF5 ID of an attribute object to obtain 
            //! the dataspace and the datatype.  Thus it sets the internal 
            //! state of the class.
            //!
            void __set_space_type();

            //------------------------------------------------------------------
            //!
            //! \brief read variable length string attributes       
            //! 
            //! Read an attribute with variable length strings. 
            //! \param s pointer to target strings
            //! \param stype string type
            //!
            void _read_vl_strings(string *s,H5Datatype &stype) const; 

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
            void _read_static_strings(string *s,H5Datatype &stype) const;


        public:
            //==============-====constructors and destructors===================
            //! default constructor
            explicit H5Attribute();

            //-----------------------------------------------------------------
            //! copy constructor
            H5Attribute(const H5Attribute &o);

            //-----------------------------------------------------------------
            //! move constructor
            H5Attribute(H5Attribute &&o);

            //-----------------------------------------------------------------
            //! 
            //! \brief construct from HDF5 type ID
            //!
            //! This constructor takes the ID to an attribute object
            //! and initializes the class. The ID can be obtained 
            //! with HDF5s C interface.
            //! \param id HDF5 id of the attribute object.
            //!
            explicit H5Attribute(const hid_t &id);
           
            //-----------------------------------------------------------------
            //! destructor
            ~H5Attribute();

            //=====================assignment operators========================
            //! copy assignment operator
            H5Attribute &operator=(const H5Attribute &a);

            //-----------------------------------------------------------------
            //! move assignment operator
            H5Attribute &operator=(H5Attribute &&o);

            //===================reading and writting data=====================
            //!
            //! \brief pointer write
            //!
            //! Private method writing data from memory addressed by 
            //! ptr to the attribute.
            //! \tparam T data type in memory
            //! \throws pni::io::nx::nxattribute_error in case of IO errors
            //! \param ptr pointer to memory
            //!
            template<typename T> void write(const T *ptr) const
            {
                const H5Datatype &mem_type = H5TFactory.get_type<T>();
                herr_t err = H5Awrite(id(),mem_type.id(),(void *)ptr);
                if(err<0)
                    throw pni::io::nx::nxattribute_error(EXCEPTION_RECORD, 
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
            //! \param tid type id of allocated memory
            //! \param ptr pointer to the region of memory
            //!
            void write(type_id_t tid,const void *ptr) const;


            //-----------------------------------------------------------------
            //!
            //! \brief write string attribute
            //!
            //! Write data to a string attribute.
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
                const H5Datatype &mem_type = H5TFactory.get_type<T>();
                herr_t err = H5Aread(id(),mem_type.id(),(void *)ptr);
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
                CTYPE s(_dspace.current_shape().size());
                std::copy(_dspace.current_shape().begin(),
                          _dspace.current_shape().end(),
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
            //! \brief close attribute
            //!
            //! This method closes the attribute object.
            //!
            virtual void close();

            //-----------------------------------------------------------------
            //! 
            //! \brief return base name
            //!
            //! Returns an empty string since an attribute has no base name.
            //! \return empty string
            //!
            virtual string base() const;

            //-----------------------------------------------------------------
            //! 
            //!\brief return path
            //!
            //! Returns an empty string as an attribute has no path.
            //! \return empty string
            //!
            virtual string path() const; 

            //-----------------------------------------------------------------
            //! 
            //! \brief get name
            //!
            //! Return the name of the attribute as string.
            //! \return attribute name
            //!
            virtual string name() const;

            //-----------------------------------------------------------------
            //!
            //! \brief get parent
            //!
            //! Return an instance of H5Object with the parent object of the
            //! attribute.
            //! \return H5Object instance
            //!
            virtual H5Object parent() const;
    };


//end of namespace
}
}
}
}
