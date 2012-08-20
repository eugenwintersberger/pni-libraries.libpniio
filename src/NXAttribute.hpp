/*
 * Declaration of Nexus object template.
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Definition of the NXAttribute class.
 *
 * Created on: Feb 11, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __NXATTRIBUTE_HPP__
#define __NXATTRIBUTE_HPP__

#include <pni/utils/Array.hpp>
#include <pni/utils/DBuffer.hpp>
#include <pni/utils/SBuffer.hpp>
#include <pni/utils/Types.hpp>

#include "NXExceptions.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{

#define ATTRIBUTE_WRITE_BUFFER(buffer)\
    try\
    {\
        this->_write_buffer(buffer);\
    }\
    catch(MemoryNotAllocatedError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(SizeMissmatchError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(NXAttributeError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }
       
#define ATTRIBUTE_READ_BUFFER(buffer)\
    try\
    {\
        this->_read_buffer(buffer);\
    }\
    catch(MemoryNotAllocatedError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(SizeMissmatchError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(NXAttributeError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }
#define ATTRIBUTE_WRITE_ARRAY(array)\
    try\
    {\
        this->_write_array(o);\
    }\
    catch(MemoryNotAllocatedError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(ShapeMissmatchError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(NXAttributeError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }

#define ATTRIBUTE_READ_ARRAY(array)\
    try\
    {\
        this->_read_array(o);\
    }\
    catch(MemoryNotAllocatedError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(ShapeMissmatchError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(NXAttributeError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }

    /*! 
    \ingroup nexus_lowlevel
    \brief attribute object

    NXAttribute represents an attribute which is attached to one of the Nexus 
    objects. Objects of this type can be used to read and write attribute data 
    from and to an object.
    */
    template<typename Imp> class NXAttribute
    {
        private:
            Imp _imp;  //!< implementation of the attribute object

            //------------------------------------------------------------------
            /*! 
            \brief write attribute from a buffer

            Write attribute from a buffer type. 
            \throws MemoryNotAllocatedError if the buffer is not allocated
            \throws SizeMissmatchError if the buffer and the attribute size do
            not match
            \tparam BTYPE buffer type
            \param b instance of BTYPE with the data
            */
            template<typename BTYPE> void _write_buffer(const BTYPE &b) const
            {
                if(b.size() == 0)
                    throw MemoryNotAllocatedError(EXCEPTION_RECORD,
                            "Source buffer not allocated!");

                if(this->size()!=b.size())
                {
                    std::stringstream ss;
                    ss<<"Buffer size ("<<b.size()<<") and attribute size (";
                    ss<<this->size()<<") do not match!";
                    throw SizeMissmatchError(EXCEPTION_RECORD,ss.str());
                }

                this->_imp.write(b.ptr());
            }
            
            //------------------------------------------------------------------
            /*! 
            \brief read attribute to buffer

            Read attribute data from the file and store it to a buffer object.
            \throws MemoryNotAllocatedError if buffer is not allocated
            \throws SizeMissmatchError if attribute and buffer size do not match
            \tparam BTYPE buffer type 
            \param b instance of BTYPE
            */
            template<typename BTYPE> void _read_buffer(BTYPE &b) const
            {
                if(b.size() == 0)
                    throw MemoryNotAllocatedError(EXCEPTION_RECORD,
                            "Target buffer not allocated!");

                if(this->size()!=b.size())
                {
                    std::stringstream ss;
                    ss<<"Buffer size ("<<b.size()<<") and attribute size (";
                    ss<<this->size()<<") do not match!";
                    throw SizeMissmatchError(EXCEPTION_RECORD,ss.str());
                }

                this->_imp.read(const_cast<typename BTYPE::value_type *>
                               (b.ptr()));
            }

            //-----------------------------------------------------------------
            /*!
            \brief write data from array

            Read data from an array type and store it in the attribute.
            \throws MemoryNotAllocatedError if the array buffer is not allocated
            \throws ShapeMissmatchError if the shapes of the array and the
            attribute do not match
            \tparam ATYPE array type
            \param a instance of ATYPE
            */
            template<typename ATYPE> void _write_array(const ATYPE &a) const
            {
                if(a.size()==0)
                    throw MemoryNotAllocatedError(EXCEPTION_RECORD,
                            "Array storage not allocated!");

                auto ashape = a.template shape<shape_t>();
                auto shape = this->template shape<shape_t>();
                if(!std::equal(ashape.begin(),ashape.end(),shape.begin()))
                {
                    std::stringstream ss;
                    ss<<"Array shape ( ";
                    for(auto v: ashape) ss<<v<<" ";
                    ss<<") and attribute shape ( ";
                    for(auto v: shape) ss<<v<<" ";
                    ss<<") do not match!";
                    throw ShapeMissmatchError(EXCEPTION_RECORD,ss.str());
                }

                this->_imp.write(a.storage().ptr());
            }
            
            //-----------------------------------------------------------------
            /*!
            \brief read data to array

            Read attribute data from the file and store it to the array.
            \throws MemoryNotAllocatedError if the arrays buffer is not
            allocated
            \throws ShapeMissmatchError if the shapes of the array and the
            attribute do not match
            \tparam ATYPE array type
            \param a instance of ATYPE
            */
            template<typename ATYPE> void _read_array(ATYPE &a) const
            {
                if(a.size()==0)
                    throw MemoryNotAllocatedError(EXCEPTION_RECORD,
                            "Array storage not allocated!");

                auto ashape = a.template shape<shape_t>();
                auto shape = this->template shape<shape_t>();
                if(!std::equal(ashape.begin(),ashape.end(),shape.begin()))
                {
                    std::stringstream ss;
                    ss<<"Array shape ( ";
                    for(auto v: ashape) ss<<v<<" ";
                    ss<<") and attribute shape ( ";
                    for(auto v: shape) ss<<v<<" ";
                    ss<<") do not match!";
                    throw ShapeMissmatchError(EXCEPTION_RECORD,ss.str());
                }

                this->_imp.write(const_cast<typename ATYPE::value_type*>
                                 (a.storage().ptr()));
            }

        public:
            //==========constructors and destructors============================
            //! default constructor
            explicit NXAttribute():_imp(){}

            //------------------------------------------------------------------
            //! copy constructor
            NXAttribute(const NXAttribute<Imp> &a): _imp(a._imp) { }

            //------------------------------------------------------------------
            //! move constructor
            NXAttribute(NXAttribute<Imp> &&a):_imp(std::move(a._imp)) { }

            //------------------------------------------------------------------
            //! copy constructor from implementation
            explicit NXAttribute(const Imp &i):_imp(i) { }

            //------------------------------------------------------------------
            //! move constructor from implementation
            explicit NXAttribute(Imp &&i):_imp(std::move(i)) { }

            //------------------------------------------------------------------
            //!destructor
            ~NXAttribute(){ _imp.close(); }

            //===================assignment operators===========================
            //! copy assignment operator
            NXAttribute<Imp> &operator=(const NXAttribute<Imp> &a)
            {
                if(this == &a) return *this;

                _imp = a._imp;
                return *this;
            }

            //------------------------------------------------------------------
            //! move assignment operator
            NXAttribute<Imp> &operator=(NXAttribute<Imp> &&a)
            {
                if(this == &a) return *this;
                _imp = std::move(a._imp);
                return *this;
            }

            //====================IO methods====================================
            /*! 
            \brief write data from a DBuffer template

            Write data from an instance of the DBuffer template.
            \throws MemoryNotAllocated if buffer memory is not allocated
            \throws SizeMissmatchError if buffer and attribute size do not match
            \throws NXAttributeError in case of any other IO error
            \tparam OTS template argumens to the DBuffer template
            \param buffer buffer from which to write data
            */
            template<typename ...OTS> 
                void write(const DBuffer<OTS...> &buffer) const
            {
                ATTRIBUTE_WRITE_BUFFER(buffer);
            }

            //-----------------------------------------------------------------
            /*!
            \brief write data from a SBuffer template

            Write the data from a static buffer type. 
            \throws MemoryNotAllocated if buffer memory is not allocated
            \throws SizeMissmatchError if buffer and attribute size do not match
            \throws NXAttributeError in case of any other IO error
            \tparam OTS template arguments to SBuffer
            \param buffer buffer from which to write data
            */
            template<typename ...OTS>
                void write(const SBuffer<OTS...> &buffer) const
            {
                ATTRIBUTE_WRITE_BUFFER(buffer);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief write data from reference buffer

            Write the data from a reference buffer template.
            \throws MemoryNoAllocated if buffer memory is not allocated
            \throws SizeMissmatchError if buffer and attribute size do not match
            \throws NXAttributeError in case of any other IO error
            \tparam OTS template arguments to RBuffer
            \param buffer buffer from which to write data
            */
            template<typename ...OTS>
                void write(const RBuffer<OTS...> &buffer) const
            {
                ATTRIBUTE_WRITE_BUFFER(buffer);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief write data from a DArray template

            Write data from a dynamic array template. 
            \throws MemoryNotAllocated if array buffer is not allocated
            \throws ShapeMissmatchError if array and attribute shape do not
            match
            \throws NXAttributeError in case of any other IO error
            \tparam OTS template arguments to DArray
            \param o instance of DArray from which to write data
            */
            template<typename ...OTS>
                void write(const DArray<OTS...> &o) const
            {
                ATTRIBUTE_WRITE_ARRAY(o);
            }

            //-----------------------------------------------------------------
            /*!
            \brief write data from a static array

            Write data form a static array template.
            \throws MemoryNotAllocated if array buffer is not allocated
            \throws ShapeMissmatchError if array and attribute shape do not
            match
            \throws NXAttributeError in case of any other IO error
            \tparam OTS template arguments to SArray template
            \param o instance SArray from which to write data
            */
            template<typename ...OTS>
                void write(const SArray<OTS...> &o) const
            {
                ATTRIBUTE_WRITE_ARRAY(o);
            }


            //-----------------------------------------------------------------
            /*! 
            \brief write a single scalar value

            Write a single scalar value. This throws an exception if the field
            is not scalar (size=1).
            \throws ShapeMissmatchError if field is not scalar
            \throws NXAttributeError in case of any other IO error
            \tparam T data type of the scalar to write
            \param value reference to the value to write
            */
            template<typename T> void write(const T &value) const
            {
                if(this->size()!=1)
                    throw ShapeMissmatchError(EXCEPTION_RECORD,
                            "Field is not scalar!");

                try
                {
                    _imp.write(&value);
                }
                catch(...)
                {
                    throw NXFieldError(EXCEPTION_RECORD,
                            "Error writing attribute!");
                }
            }

            //-----------------------------------------------------------------
            /*! 
            \brief write a C-string

            This is a special implementation of write for classical C-strings.
            \throws ShapeMissmatchError if field is not scalar
            \throws NXAttributeError in case of any other IO error
            \param value pointer to a C-string
            */
            void write(const char *value) const
            {
                try
                {
                    String s(value);
                    this->write(s);
                }
                catch(ShapeMissmatchError &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(NXFieldError &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
            }

            //-----------------------------------------------------------------
            /*!
            \brief read data to a buffer

            Read data to a DBuffer instance.
            \throws MemoryNotAllocated if buffer is not allocated
            \throws SizeMissmatchError if buffer and attribute size do not match
            \throws NXAttributeError in case of any other IO error
            \tparam OTS template arguments to the DBuffer template
            \param buffer instance of DBuffer in which to store the data
            */
            template<typename ...OTS> void read(DBuffer<OTS...> &buffer) const
            {
                ATTRIBUTE_READ_BUFFER(buffer);
            }

            //-----------------------------------------------------------------
            /*!
            \brief read data to a buffer

            Read data to a SBuffer instance.
            \throws MemoryNotAllocated if buffer is not allocated
            \throws SizeMissmatchError if buffer and attribute size do not match
            \throws NXAttributeError in case of any other IO error
            \tparam OTS template arguments to the SBuffer template
            \param buffer instance of SBuffer in which to store the data
            */
            template<typename ...OTS> void read(SBuffer<OTS...> &buffer) const
            {
                ATTRIBUTE_READ_BUFFER(buffer);
            }

            //-----------------------------------------------------------------
            /*!
            \brief read data to a buffer

            Read data to a RBuffer instance.
            \throws MemoryNotAllocated if buffer is not allocated
            \throws SizeMissmatchError if buffer and attribute size do not match
            \throws NXAttributeError in case of any other IO error
            \tparam OTS template arguments to the RBuffer template
            \param buffer instance of RBuffer in which to store the data
            */
            template<typename ...OTS> void read(RBuffer<OTS...> &buffer) const
            {
                ATTRIBUTE_READ_BUFFER(buffer);
            }

            //-----------------------------------------------------------------
            /*!
            \brief read data to an array

            Read data to an DArray instance.
            \throws MemoryNotAllocated if array buffer is not allocated
            \throws ShapeMissmatchError if array and attribute shape do not
            match
            \throws NXAttributeError in the case of any other IO error
            \tparam OTS template arguments to DArray
            \param o instance of DArray
            */
            template<typename ...OTS> void read(DArray<OTS...> &o) const
            {
                ATTRIBUTE_READ_ARRAY(o);
            }

            //-----------------------------------------------------------------
            /*!
            \brief read data to an array

            Read data to an SArray instance.
            \throws MemoryNotAllocated if array buffer is not allocated
            \throws ShapeMissmatchError if array and attribute shape do not
            match
            \throws NXAttributeError in the case of any other IO error
            \tparam OTS template arguments to SArray
            \param o instance of SArray
            */
            template<typename ...OTS> void read(SArray<OTS...> &o) const
            {
                ATTRIBUTE_READ_ARRAY(o);
            }


            //-----------------------------------------------------------------
            /*!
            \brief read a single scalar value

            Read a single scalar value.
            \throws ShapeMissmatchError if the attribute is not scalar
            \throws NXAttributeError in case of any other IO error
            \tparam T type to read to
            \param value reference to an instance of T
            */
            template<typename T> void read(T &value) const
            {
                _imp.write(&value);
            }

            //============simple maintenance methods========================
            //! obtain attribute shape
            template<typename CTYPE> CTYPE shape() const
            {
                return _imp.template shape<CTYPE>();
            }

            //--------------------------------------------------------------
            //! obtain attribute size
            size_t size() const
            {
                return _imp.size();
            }

            //--------------------------------------------------------------
            //! obtain type id

            //! Returns the type ID of the data stored in the attribute.
            TypeID type_id() const
            {
                return _imp.type_id();
            }

            //--------------------------------------------------------------
            //! close attribute
            void close()
            {
                _imp.close();
            }

            //---------------------------------------------------------------
            //! check validity of the attribute
            bool is_valid() const
            {
                return _imp.is_valid();
            }

            //---------------------------------------------------------------
            //! get attribute name
            String name() const
            {
                return _imp.name();
            }

    };

//end of namespace
}
}

#endif
