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
#include <pni/core/dbuffer.hpp>
#include <pni/core/sbuffer.hpp>
#include <pni/core/types.hpp>
#include <pni/core/array.hpp>

#include "nxexceptions.hpp"
#include "utils/io_utils.hpp"


namespace pni{
namespace io{
namespace nx{

    using namespace pni::core;
    //need this here to avoid name collisions with tango headers.
    using pni::core::array;
    using pni::core::string;
    using pni::core::exception;

#define ATTRIBUTE_WRITE_BUFFER(buffer)\
    try\
    {\
        this->_write_buffer(buffer);\
    }\
    catch(memory_not_allocated_error &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(size_mismatch_error &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(nxattribute_error &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }
       
#define ATTRIBUTE_READ_BUFFER(buffer)\
    try\
    {\
        this->_read_buffer(buffer);\
    }\
    catch(memory_not_allocated_error &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(size_mismatch_error &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(nxattribute_error &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }
#define ATTRIBUTE_WRITE_ARRAY(array)\
    try\
    {\
        this->_write_array(o);\
    }\
    catch(memory_not_allocated_error &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(shape_mismatch_error &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(nxattribute_error &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }

#define ATTRIBUTE_READ_ARRAY(array)\
    try\
    {\
        this->_read_array(o);\
    }\
    catch(memory_not_allocated_error &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(shape_mismatch_error &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(nxattribute_error &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }

    /*! 
    \ingroup nexus_lowlevel
    \brief attribute object

    nxattribute represents an attribute which is attached to one of the Nexus 
    objects. Objects of this type can be used to read and write attribute data 
    from and to an object.
    */
    template<typename Imp> class nxattribute
    {
        private:
            Imp _imp;  //!< implementation of the attribute object
           
            //-----------------------------------------------------------------
            /*!
            \brief gernerate error message

            Generate the error message for a shape mismatch error between a
            field and an array type. 
            \param ashape array shape
            \param fshape field shape
            \return error message
            */
            static string _shape_mismatch_error_message(const shape_t
                    &ashape,const shape_t &fshape) 
            {
                std::stringstream ss;
                ss<<"Array shape ( ";
#ifdef NOFOREACH
                for(auto iter = ashape.begin();iter!=ashape.end();++iter)
                {
                    auto v = *iter;
#else
                for(auto v: ashape) 
                {
#endif
                    ss<<v<<" ";
                }
                ss<<") and attribute shape ( ";
#ifdef NOFOREACH
                for(auto iter = fshape.begin();iter!=fshape.end();++iter)
                {
                    auto v = *iter;
#else
                for(auto v: fshape) 
                {
#endif 
                    ss<<v<<" ";
                }
                ss<<") do not match!";

                return ss.str();
            }

            //------------------------------------------------------------------
            /*! 
            \brief write attribute from a buffer

            Write attribute from a buffer type. 
            \throws memory_not_allocated_error if the buffer is not allocated
            \throws size_mismatch_error if the buffer and the attribute size do
            not match
            \tparam BTYPE buffer type
            \param b instance of BTYPE with the data
            */
            template<typename BTYPE> void _write_buffer(const BTYPE &b) const
            {
                if(b.size() == 0)
                    throw memory_not_allocated_error(EXCEPTION_RECORD,
                            "Source buffer not allocated!");

                if(this->size()!=b.size())
                {
                    std::stringstream ss;
                    ss<<"Buffer size ("<<b.size()<<") and attribute size (";
                    ss<<this->size()<<") do not match!";
                    throw size_mismatch_error(EXCEPTION_RECORD,ss.str());
                }

                this->_imp.write(b.ptr());
            }
            
            //------------------------------------------------------------------
            /*! 
            \brief read attribute to buffer

            Read attribute data from the file and store it to a buffer object.
            \throws memory_not_allocated_error if buffer is not allocated
            \throws size_mismatch_error if attribute and buffer size do not match
            \tparam BTYPE buffer type 
            \param b instance of BTYPE
            */
            template<typename BTYPE> void _read_buffer(BTYPE &b) const
            {
                if(b.size() == 0)
                    throw memory_not_allocated_error(EXCEPTION_RECORD,
                            "Target buffer not allocated!");

                if(this->size()!=b.size())
                {
                    std::stringstream ss;
                    ss<<"Buffer size ("<<b.size()<<") and attribute size (";
                    ss<<this->size()<<") do not match!";
                    throw size_mismatch_error(EXCEPTION_RECORD,ss.str());
                }

                this->_imp.read(const_cast<typename BTYPE::value_type *>
                               (b.ptr()));
            }

            //-----------------------------------------------------------------
            /*!
            \brief write data from array

            Read data from an array type and store it in the attribute.
            \throws memory_not_allocated_error if the array buffer is not allocated
            \throws shape_mismatch_error if the shapes of the array and the
            attribute do not match
            \tparam ATYPE array type
            \param a instance of ATYPE
            */
            template<typename ATYPE> void _write_array(const ATYPE &a) const
            {
                if(a.size()==0)
                    throw memory_not_allocated_error(EXCEPTION_RECORD,
                            "Array storage not allocated!");

                //get the shape of the array to write
                auto ashape = a.template shape<shape_t>();

                //get the shape of this attribute
                auto s = this->shape<shape_t>();

                if(s.size() == ashape.size())
                {
                    if(!std::equal(ashape.begin(),ashape.end(),s.begin()))
                        throw shape_mismatch_error(EXCEPTION_RECORD,
                                _shape_mismatch_error_message(ashape,s));
                }
                else
                {
                    if(a.size() != this->size())
                        throw shape_mismatch_error(EXCEPTION_RECORD,
                                _shape_mismatch_error_message(ashape,s));
                }


                this->_imp.write(a.storage().ptr());
            }
            
            //-----------------------------------------------------------------
            /*!
            \brief read data to array

            Read attribute data from the file and store it to the array.
            \throws memory_not_allocated_error if the arrays buffer is not
            allocated
            \throws shape_mismatch_error if the shapes of the array and the
            attribute do not match
            \tparam ATYPE array type
            \param a instance of ATYPE
            */
            template<typename ATYPE> void _read_array(ATYPE &a) const
            {
                if(a.size()==0)
                    throw memory_not_allocated_error(EXCEPTION_RECORD,
                            "Array storage not allocated!");

                auto ashape = a.template shape<shape_t>();
                auto shape = this->template shape<shape_t>();
                if(shape.size() == ashape.size())  
                {
                    if(!std::equal(ashape.begin(),ashape.end(),shape.begin()))
                        throw shape_mismatch_error(EXCEPTION_RECORD,
                                _shape_mismatch_error_message(ashape,shape));
                }
                else
                {
                    if(this->size() != a.size())
                        throw shape_mismatch_error(EXCEPTION_RECORD,
                                _shape_mismatch_error_message(ashape,shape));
                }


                this->_imp.read(const_cast<typename ATYPE::value_type*>
                                 (a.storage().ptr()));
            }

        public:
            //==========constructors and destructors============================
            //! default constructor
            explicit nxattribute():_imp(){}

            //------------------------------------------------------------------
            //! copy constructor
            nxattribute(const nxattribute<Imp> &a): _imp(a._imp) { }

            //------------------------------------------------------------------
            //! move constructor
            nxattribute(nxattribute<Imp> &&a):_imp(std::move(a._imp)) { }

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
            nxattribute<Imp> &operator=(const nxattribute<Imp> &a)
            {
                if(this == &a) return *this;

                _imp = a._imp;
                return *this;
            }

            //------------------------------------------------------------------
            //! move assignment operator
            nxattribute<Imp> &operator=(nxattribute<Imp> &&a)
            {
                if(this == &a) return *this;
                _imp = std::move(a._imp);
                return *this;
            }

            //====================IO methods====================================
            /*! 
            \brief write data from a DBuffer template

            Write data from an instance of the DBuffer template.
            \throws memory_not_allocated_error if buffer memory is not allocated
            \throws size_mismatch_error if buffer and attribute size do not match
            \throws nxattribute_error in case of any other IO error
            \tparam OTS template argumens to the DBuffer template
            \param buffer buffer from which to write data
            */
            template<typename T,typename ALLOCATOR> 
                void write(const dbuffer<T,ALLOCATOR> &buffer) const
            {
                ATTRIBUTE_WRITE_BUFFER(buffer);
            }

            //-----------------------------------------------------------------
            /*!
            \brief write data from a SBuffer template

            Write the data from a static buffer type. 
            \throws memory_not_allocated_error if buffer memory is not allocated
            \throws size_mismatch_error if buffer and attribute size do not match
            \throws nxattribute_error in case of any other IO error
            \tparam OTS template arguments to SBuffer
            \param buffer buffer from which to write data
            */
            template<typename T,size_t SIZE>
                void write(const sbuffer<T,SIZE> &buffer) const
            {
                ATTRIBUTE_WRITE_BUFFER(buffer);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief write data from reference buffer

            Write the data from a reference buffer template.
            \throws memory_not_allocated_error if buffer memory is not allocated
            \throws size_mismatch_error if buffer and attribute size do not match
            \throws nxattribute_error in case of any other IO error
            \tparam OTS template arguments to RBuffer
            \param buffer buffer from which to write data
            */
            template<typename T> void write(const rbuffer<T> &buffer) const
            {
                ATTRIBUTE_WRITE_BUFFER(buffer);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief write data from a DArray template

            Write data from a dynamic array template. 
            \throws memory_not_allocated_error if array buffer is not allocated
            \throws shape_mismatch_errror if array and attribute shape do not
            match
            \throws nxattribute_error in case of any other IO error
            \tparam OTS template arguments to DArray
            \param o instance of DArray from which to write data
            */
            template<typename T,typename STORAGE,typename IMAP>
                void write(const darray<T,STORAGE,IMAP> &o) const
            {
                ATTRIBUTE_WRITE_ARRAY(o);
            }

            //-----------------------------------------------------------------
            /*!
            \brief write data from a static array

            Write data form a static array template.
            \throws memory_not_allocated_error if array buffer is not allocated
            \throws shape_mismatch_error if array and attribute shape do not
            match
            \throws nxattribute_error in case of any other IO error
            \tparam OTS template arguments to SArray template
            \param o instance SArray from which to write data
            */
            template<typename T,size_t ...INDICES>
                void write(const sarray<T,INDICES...> &o) const
            {
                ATTRIBUTE_WRITE_ARRAY(o);
            }


            //-----------------------------------------------------------------
            /*! 
            \brief write a single scalar value

            Write a single scalar value. This throws an exception if the field
            is not scalar (size=1).
            \throws shape_mismatch_error if field is not scalar
            \throws nxattribute_error in case of any other IO error
            \tparam T data type of the scalar to write
            \param value reference to the value to write
            */
            template<typename T> void write(const T &value) const
            {
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
            /*! 
            \brief write a C-string

            This is a special implementation of write for classical C-strings.
            \throws shape_mismatch_error if field is not scalar
            \throws nxattribute_error in case of any other IO error
            \param value pointer to a C-string
            */
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
            /*!
            \brief write array type erasure data

            \throws memory_not_allocated_error if array not allocated
            \throws type_error if data type not supported
            \throws shape_mismatch_error if array shape does not match
            \throws nxattribute_error in case of any other error
            \param a instance of array
            */
            void write(const array &a) const
            {
                if(a.size()==0)
                    throw memory_not_allocated_error(EXCEPTION_RECORD,
                            "Array storage not allocated!");

                //get the shape of the array to write
                shape_t ashape = a.shape();

                //get the shape of this attribute
                auto s = this->shape<shape_t>();

                if(s.size()==ashape.size())
                {
                    if(!std::equal(ashape.begin(),ashape.end(),s.begin()))
                        throw shape_mismatch_error(EXCEPTION_RECORD,
                                _shape_mismatch_error_message(ashape,s));
                }
                else
                {
                    if(a.size() != this->size())
                        throw shape_mismatch_error(EXCEPTION_RECORD,
                                _shape_mismatch_error_message(ashape,s));
                }
                        

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
            /*!
            \brief read data to a buffer

            Read data to a DBuffer instance.
            \throws memory_not_allocated_error if buffer is not allocated
            \throws size_mismatch_error if buffer and attribute size do not match
            \throws nxattribute_error in case of any other IO error
            \tparam OTS template arguments to the DBuffer template
            \param buffer instance of DBuffer in which to store the data
            */
            template<typename T,typename ALLOCATOR> 
                void read(dbuffer<T,ALLOCATOR> &buffer) const
            {
                ATTRIBUTE_READ_BUFFER(buffer);
            }

            //-----------------------------------------------------------------
            /*!
            \brief read data to a buffer

            Read data to a SBuffer instance.
            \throws memory_not_allocated_error if buffer is not allocated
            \throws size_mismatch_error if buffer and attribute size do not match
            \throws nxattribute_error in case of any other IO error
            \tparam OTS template arguments to the SBuffer template
            \param buffer instance of SBuffer in which to store the data
            */
            template<typename T,size_t SIZE> 
                void read(sbuffer<T,SIZE> &buffer) const
            {
                ATTRIBUTE_READ_BUFFER(buffer);
            }

            //-----------------------------------------------------------------
            /*!
            \brief read data to a buffer

            Read data to a RBuffer instance.
            \throws memory_not_allocated_error if buffer is not allocated
            \throws size_mismatch_error if buffer and attribute size do not match
            \throws nxattribute_error in case of any other IO error
            \tparam OTS template arguments to the RBuffer template
            \param buffer instance of RBuffer in which to store the data
            */
            template<typename T> void read(rbuffer<T> &buffer) const
            {
                ATTRIBUTE_READ_BUFFER(buffer);
            }

            //-----------------------------------------------------------------
            /*!
            \brief read data to an array

            Read data to an DArray instance.
            \throws memory_not_allocated_error if array buffer is not allocated
            \throws shape_mismatch_error if array and attribute shape do not
            match
            \throws nxattribute_error in the case of any other IO error
            \tparam OTS template arguments to DArray
            \param o instance of DArray
            */
            template<typename T,typename STORAGE,typename IMAP> 
                void read(darray<T,STORAGE,IMAP> &o) const
            {
                ATTRIBUTE_READ_ARRAY(o);
            }

            //-----------------------------------------------------------------
            /*!
            \brief read data to an array

            Read data to an SArray instance.
            \throws memory_not_allocated_error if array buffer is not allocated
            \throws shape_mismatch_error if array and attribute shape do not
            match
            \throws nxattribute_error in the case of any other IO error
            \tparam OTS template arguments to SArray
            \param o instance of SArray
            */
            template<typename T,size_t ...INDICES> 
                void read(sarray<T,INDICES...> &o) const
            {
                ATTRIBUTE_READ_ARRAY(o);
            }
            
            //-----------------------------------------------------------------
            /*!
            \brief read data to array

            \throws memory_not_allocated_error if array not allocated
            \throws type_error if data type is not supported
            \throws shape_mismatch_error if array shape does not match
            \throws nxattribute_error in case of any other IO error
            \param a instance of array 
            */
            void read(array &a) const
            {
                if(a.size()==0)
                    throw memory_not_allocated_error(EXCEPTION_RECORD,
                            "Array storage not allocated!");

                auto ashape = a.template shape<shape_t>();
                auto shape = this->template shape<shape_t>();

                if(shape.size()==ashape.size())
                {
                    if(!std::equal(ashape.begin(),ashape.end(),shape.begin()))
                        throw shape_mismatch_error(EXCEPTION_RECORD,
                                _shape_mismatch_error_message(ashape,shape));
                }
                else
                {
                    if(a.size() != this->size())
                        throw shape_mismatch_error(EXCEPTION_RECORD,
                                _shape_mismatch_error_message(ashape,shape));
                }

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
            /*!
            \brief read a single scalar value

            Read a single scalar value.
            \throws shape_mismatch_error if the attribute is not scalar
            \throws nxattribute_error in case of any other IO error
            \tparam T type to read to
            \param value reference to an instance of T
            */
            template<typename T> void read(T &value) const
            {
                _imp.read(&value);
            }


            //============simple maintenance methods========================
            //! obtain attribute shape
            template<typename CTYPE> CTYPE shape() const
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
            /*! 
            \brief obtain type id

            Returns the type ID of the data stored in the attribute.
            \return type id of the elements stored in the field
            */
            type_id_t type_id() const { return _imp.type_id(); }

            //--------------------------------------------------------------
            //! close attribute
            void close() { _imp.close(); }

            //---------------------------------------------------------------
            //! check validity of the attribute
            bool is_valid() const { return _imp.is_valid(); }

            //---------------------------------------------------------------
            //! get attribute name
            string name() const { return _imp.name(); }

    };

//end of namespace
}
}
}
