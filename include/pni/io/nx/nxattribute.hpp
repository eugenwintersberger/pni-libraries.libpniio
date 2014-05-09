/*
 * Declaration of Nexus object template.
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Definition of the NXAttribute class.
 *
 * Created on: Feb 11, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <pni/core/arrays.hpp>
#include <pni/core/types.hpp>
#include <pni/core/error.hpp>

#include "nxexceptions.hpp"
#include "nxobject_traits.hpp"
#include "utils/io_utils.hpp"


namespace pni{
namespace io{
namespace nx{

    using namespace pni::core;
    //need this here to avoid name collisions with tango headers.
    using pni::core::array;
    using pni::core::string;
    using pni::core::exception;

    //! 
    //! \ingroup nexus_lowlevel
    //! \brief attribute object
    //! 
    //! nxattribute represents an attribute which is attached to one of the 
    //! Nexus objects. Objects of this type can be used to read and write 
    //! attribute data from and to an object.
    //!
    template<typename Imp> 
    class nxattribute
    {
        public:
            //! define the actual type of this object
            typedef nxattribute<Imp> attribute_type;
        private:
            Imp _imp;  //!< implementation of the attribute object
           
            //-----------------------------------------------------------------
            //!
            //! \brief write data from array
            //!
            //! Read data from an array type and store it in the attribute.
            //! \throws memory_not_allocated_error if the array buffer is not allocated
            //! \throws shape_mismatch_error if the shapes of the array and the
            //! attribute do not match
            //! \tparam ATYPE array type
            //! \param a instance of ATYPE
            //!
            template<typename ATYPE> 
            void _write_array(const ATYPE &a) const
            {
                check_allocation_state(a,EXCEPTION_RECORD);
                check_equal_shape(a,*this,EXCEPTION_RECORD);

                this->_imp.write(pni::core::type_id(a),a.data());
            }
            
            //-----------------------------------------------------------------
            //!
            //! \brief read data to array
            //!
            //! Read attribute data from the file and store it to the array.
            //! \throws memory_not_allocated_error if the arrays buffer is not
            //! allocated
            //! \throws shape_mismatch_error if the shapes of the array and the
            //! attribute do not match
            //! 
            //! \tparam ATYPE array type
            //! \param a instance of ATYPE
            //!
            template<typename ATYPE> 
            void _read_array(ATYPE &a) const
            {
                check_allocation_state(a,EXCEPTION_RECORD);
                check_equal_shape(a,*this,EXCEPTION_RECORD);


                this->_imp.read(a.data());
            }

        public:
            //==========constructors and destructors============================
            //! default constructor
            explicit nxattribute():_imp(){}

            //------------------------------------------------------------------
            //! copy constructor
            nxattribute(const attribute_type &a): _imp(a._imp) { }

            //------------------------------------------------------------------
            //! move constructor
            nxattribute(attribute_type &&a):_imp(std::move(a._imp)) { }

            //------------------------------------------------------------------
            //! copy constructor from implementation
            explicit nxattribute(const Imp &i):_imp(i) { }

            //------------------------------------------------------------------
            //! move constructor from implementation
            explicit nxattribute(Imp &&i):_imp(std::move(i)) { }

            //------------------------------------------------------------------
            //!destructor
            ~nxattribute(){ _imp.close(); }

            //===================assignment operators===========================
            //! copy assignment operator
            attribute_type &operator=(const attribute_type &a)
            {
                if(this == &a) return *this;

                _imp = a._imp;
                return *this;
            }

            //------------------------------------------------------------------
            //! move assignment operator
            attribute_type &operator=(attribute_type &&a)
            {
                if(this == &a) return *this;
                _imp = std::move(a._imp);
                return *this;
            }

            //====================IO methods====================================
            //! 
            //! \brief write data from an mdarray instance
            //!
            //! Write data from an mdarray instance to the attribute object
            //!
            //! \throws memory_not_allocated_error if array buffer is not 
            //! allocated
            //! \throws shape_mismatch_errror if array and attribute shape 
            //! do not match
            //! \throws nxattribute_error in case of any other IO error
            //!
            //! \tparam STORAGE storage type of the mdarray
            //! \tparam IMAP index map type of the mdarray
            //! \tparam IPA inplace arithmetic type of the mdarray
            //! \param o instance of DArray from which to write data
            //!
            template<
                     typename STORAGE,
                     typename IMAP,
                     typename IPA
                    >
            void write(const mdarray<STORAGE,IMAP,IPA> &o) const
            {
                try
                {
                    this->_write_array(o);
                }
                catch(memory_not_allocated_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(shape_mismatch_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(nxattribute_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
            }

            //----------------------------------------------------------------
            template<typename T>
            void write(const T *data) const
            {
                static_assert(!std::is_pointer<T>::value,"no const pointer");
                try
                {
                    this->_imp.write(data);
                }
                catch(...)
                {
                    throw nxattribute_error(EXCEPTION_RECORD,
                            "Error writing attribute!");
                }
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief write a single scalar value
            //!
            //! Write a single scalar value. This throws an exception if the 
            //! field is not scalar (size=1).
            //!
            //! \throws shape_mismatch_error if field is not scalar
            //! \throws nxattribute_error in case of any other IO error
            //! \tparam T data type of the scalar to write
            //! \param value reference to the value to write
            //!
            template<typename T > 
            void write(const T &value) const
            {
                static_assert(!std::is_pointer<T>::value,"no const pointer");
                if(this->size()!=1)
                    throw shape_mismatch_error(EXCEPTION_RECORD,
                            "Field is not scalar!");

                try
                {
                    this->_imp.write(&value);
                }
                catch(...)
                {
                    throw nxattribute_error(EXCEPTION_RECORD,
                            "Error writing attribute!");
                }
            }


            //------------------------------------------------------------------
            //! 
            //! \brief write a C-string
            //!
            //! This is a special implementation of write for classical 
            //! C-strings.
            //! 
            //! \throws shape_mismatch_error if field is not scalar
            //! \throws nxattribute_error in case of any other IO error
            //! \param value pointer to a C-string
            //!
            void write(const char *value) const
            {
                try
                {
                    string s(value);
                    this->write(s);
                }
                catch(shape_mismatch_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(nxattribute_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
            }

            //-----------------------------------------------------------------
            //!
            //! \brief write array type erasure data
            //!
            //! \throws memory_not_allocated_error if array not allocated
            //! \throws type_error if data type not supported
            //! \throws shape_mismatch_error if array shape does not match
            //! \throws nxattribute_error in case of any other error
            //! \param a instance of array
            //!
            void write(const array &a) const
            {
                try
                {
                    write_array(_imp,a);
                }
                catch(...)
                {
                    throw nxattribute_error(EXCEPTION_RECORD,
                            "Error reading attribute!");
                }
            }

            //-----------------------------------------------------------------
            //!
            //! \brief read data to an array
            //!
            //! Read data to an DArray instance.
            //! \throws memory_not_allocated_error if array buffer is not 
            //! allocated
            //! \throws shape_mismatch_error if array and attribute shape do 
            //! not match
            //! \throws nxattribute_error in the case of any other IO error
            //! \tparam OTS template arguments to DArray
            //! \param o instance of DArray
            //!
            template<
                     typename STORAGE,
                     typename IMAP,
                     typename IPA
                    > 
            void read(mdarray<STORAGE,IMAP,IPA> &o) const
            {
                try
                {
                    this->_read_array(o);
                }
                catch(memory_not_allocated_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(shape_mismatch_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(nxattribute_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
            }
            
            //-----------------------------------------------------------------
            //!
            //! \brief read data to array
            //!
            //! \throws memory_not_allocated_error if array not allocated
            //! \throws type_error if data type is not supported
            //! \throws shape_mismatch_error if array shape does not match
            //! \throws nxattribute_error in case of any other IO error
            //! \param a instance of array 
            //!
            void read(array &a) const
            {
                check_allocation_state(a,EXCEPTION_RECORD);
                check_equal_shape(a,*this,EXCEPTION_RECORD);

                try
                {
                    read_array(_imp,a);
                }
                catch(...)
                {
                    throw nxattribute_error(EXCEPTION_RECORD,
                            "Error reading to array!");
                }
            }

            //-----------------------------------------------------------------
            //!
            //! \brief read a single scalar value
            //!
            //! Read a single scalar value.
            //! \throws shape_mismatch_error if the attribute is not scalar
            //! \throws nxattribute_error in case of any other IO error
            //! \tparam T type to read to
            //! \param value reference to an instance of T
            //!
            template<typename T> 
            void read(T &value) const
            {
                _imp.read(&value);
            }

            template<typename T>
            void read(T *value) const
            {
                _imp.read(value);
            }


            //============simple maintenance methods========================
            //! obtain attribute shape
            template<typename CTYPE> 
            CTYPE shape() const
            {
                return _imp.template shape<CTYPE>();
            }

            //--------------------------------------------------------------
            //! return attribute rank
            size_t rank() const { return this->_imp.rank(); }

            //--------------------------------------------------------------
            //! obtain attribute size
            size_t size() const { return _imp.size(); }

            //--------------------------------------------------------------
            //! 
            //! \brief obtain type id
            //!
            //! Returns the type ID of the data stored in the attribute.
            //! \return type id of the elements stored in the field
            //!
            type_id_t type_id() const { return _imp.type_id(); }

            //--------------------------------------------------------------
            //! close attribute
            void close() { _imp.close(); }

            //---------------------------------------------------------------
            //! check validity of the attribute
            bool is_valid() const { return _imp.is_valid(); }

            //---------------------------------------------------------------
            //! 
            //! \brief get attribute name
            //!
            //! Obtain the name of the attribute. With this name it can be
            //! identified at a particular object.
            //! \return string with the attributes name
            //!
            string name() const { return _imp.name(); }

            //---------------------------------------------------------------
            //! 
            //! \brief get attribute base
            //!
            //! This is basically the path to the parent object of an 
            //! attribute
            //!
            //! \return path to parent object
            //!
            string base() const { return _imp.base(); }

            //---------------------------------------------------------------
            //!
            //! \brief get attribute path
            //!
            //! Return the full path of an attribute. This is virtually the 
            //! base name and the attribute name concatenated by an "@" 
            //! sign.
            //! \return full path to the attribute
            //!
            string path() const { return _imp.path(); }

            //-----------------------------------------------------------------
            //!
            //! \brief return parent object
            //! 
            //! This method returns the parent object of a 
            //! \return parent object
            //!
            typename nxobject_traits<nximp_code_map<attribute_type>::icode>::object_type
            parent() const
            {
                typedef typename
                    nxobject_traits<nximp_code_map<attribute_type>::icode>::object_type
                    object_type;

                return object_type(_imp.parent());
            }

    };

//end of namespace
}
}
}
