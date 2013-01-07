/*
 * Declaration of the NXfield template
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
 * Declaration of the NXfield template
 *
 * Created on: Jul 3, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <sstream>

#include <pni/core/Types.hpp>
#include <pni/core/Array.hpp>
#include <pni/core/SBuffer.hpp>
#include <pni/core/DBuffer.hpp>
#include <pni/core/Slice.hpp>

#include "NXObject.hpp"
#include "NXExceptions.hpp"
#include "NXSelection.hpp"

using namespace pni::core;

namespace pni{
namespace io{
namespace nx{

#define READ_BUFFER(buffer)\
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
    catch(NXFieldError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }

#define WRITE_BUFFER(buffer)\
    try\
    {\
        this->_write_buffer(b);\
    }\
    catch(MemoryNotAllocatedError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(SizeMissmatchError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(NXFieldError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }

#define READ_ARRAY(array)\
    try\
    {\
        this->_read_array(array);\
    }\
    catch(MemoryNotAllocatedError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(ShapeMissmatchError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(NXFieldError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }

#define WRITE_ARRAY(array)\
    try\
    {\
        this->_write_array(array);\
    }\
    catch(MemoryNotAllocatedError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(ShapeMissmatchError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }\
    catch(NXFieldError &error)\
    {\
        error.append(EXCEPTION_RECORD); throw error;\
    }

    /*! 
    \ingroup nexus_lowlevel
    \brief NXfield base class

    NXField is a type used to store multidimensional data in a file. The IO
    methods it provides support all the array templates provided by \c
    libpnicore. Partial IO is provided by the () operator (see below). 
    The interface of NXField is quite similar to those of the array templates
    provided by \c libpnicore. Like them it provides a shape() and  a size()
    method returning the number of elements along each dimension and the total
    number of elements in the field. rank() returns the number of dimensions of
    the field. 
    Unlike the array templates which provide the ID of their element type via a
    static member variable the method type_id() is provided by NXField for the
    same purpose.

    \section nxfield_resize_and_grow resize and grow
    <div align="right"
    style="width:500;float:right;border-width:20px;margin-left:20px">
    <table>
    <tr>
    <td> 
    \image html array_grow.svg 
    </td>
    <td> 
    \image html array_resize.svg 
    </td>
    </tr>
    <tr>
    <td> <center> Grow operation </center> </td>
    <td> <center> Resize operation </center> </td>
    </tr>
    </table>
    </div>
    The number of dimensions a field provides is fixed at the time it is
    created. However, the number of elements along each of these dimensions can
    be altered at runtime. Two methods of the class are responsible for resizing
    a field: resize() and grow(). 
    The difference between resize and grow is shown in the figure below. 
    While the grow() operation resizes the field by a fixed amount of elements
    along a particular dimension a resize operation can enlarge multiple
    dimensions at the same time. 
    The latter one is useful in situations where the number of elements along
    each dimension is unknown at the time the field is created. 
    The grow() operation is however very useful in situations where the number
    of elements to store in an element is not known at the time the field is
    created. One can use this to append data along one dimensions. 
    Consider for instance this example that shows a very common situation during
    experiments. Data should be stored in a field but the total number of points
    is not known when the field is created
    \code
    //we start with a field of size 0 - no element
    NXField field = group.create_field<Float32>("motor",shape_t{0}); 

    size_t np = 0;
    while(true)
    {
        field.grow(0);
        field(np++).write(get_data());
        if(get_break_condition()) break;
    }
    \endcode
    The above loop runs until get_break_condition() return true. In no case we
    can no in advance when the loop will exit and thus how many elements should
    be stored. The grow() method offers an easy way to handle such situations.

    \section nxfield_partial_io Partial IO
    <div align="right"
    style="width:500;float:right;border-width:20px;margin-left:20px">
    <table>
    <tr>
    <td> \image html selection_1.png </td>
    <td> \image html selection_2.png </td>
    <td> \image html selection_3.png </td>
    </tr>
    <tr>
    <td><center> Selection 1 </center></td>
    <td><center> Selection 2 </center></td>
    <td><center> Selection 3 </center></td>
    </table>
    </div>

    As HDF5 datasets, NXField objects provide the possibility to read or write
    only a part of the data.  The mechanism works pretty much as the array view
    selection in \c libpnicore. 
    Compare the following code with the figures on the right side
    \code
    DArray<UInt32> strip(shape_t{1024});

    //selection 1
    field1(3,Slice(0,1024)).read(strip);

    //selection 2
    DArray<UInt32> block(shape_t{4,6});
    field2(Slice(3,7),Slice(2,8)).read(block);

    //selection 3
    DArray<UInt32> block2(shape_t{4,5});
    field3(Slice(2,6),Slice(2,10,2)).read(block2);

    \endcode
    Under the hood the () operator of NXField applies a selection to the
    underlying HDF5 dataset according to the arguments passed to it. 
    Every call to read or write immediately after reading or writing the data
    removes this selections.
    */
    template<typename Imp> class NXField:public NXObject<Imp> 
    {
        private:
            /*!
            \brief gernerate error message

            Generate the error message for a shape missmatch error between a
            field and an array type. 
            \param ashape array shape
            \param fshape field shape
            \return error message
            */
            static String _shape_missmatch_error_message(const shape_t
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
                ss<<") and field shape ( ";
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

            //-----------------------------------------------------------------
            /*!
            \brief read data to buffer

            \throws MemoryNotAllocatedError if buffer size is 0
            \throws SizeMissmatchError if buffer and field size do not match
            \throws NXFieldError in case of any other IO error
            \tparam BTYPE buffer type
            \param b reference to an instance of BTYPE
            */
            //------------------read buffer-----------------------------------
            template<typename BTYPE> void _read_buffer(BTYPE &b) const
            {
                if(b.size() == 0)
                    throw MemoryNotAllocatedError(EXCEPTION_RECORD,
                                           "Target buffer not allocated!");

                if(b.size() != this->imp().size())
                {
                    std::stringstream ss;
                    ss<<"Buffer size ("<<b.size()<<") and field size (";
                    ss<<this->size()<<") do not match!";
                    throw SizeMissmatchError(EXCEPTION_RECORD,ss.str());
                }
                
                try
                {
                    this->imp().read(const_cast<typename BTYPE::value_type
                            *>(b.ptr()));
                }
                catch(...)
                {
                    throw NXFieldError(EXCEPTION_RECORD,
                                       "Cannot read to buffer!");
                }
            }

            //-----------------------------------------------------------------
            /*! 
            \brief write data from buffer

            Write data from a buffer to the file
            \throws MemoryNotAllocatedError if buffer is not allocated
            \throws SizeMissmatchError if field and buffer size do not match
            \throws NXFieldError in case of any other error
            \tparam BTYPE buffer type
            \param b reference to an instance of BTYPE
            */
            template<typename BTYPE> void _write_buffer(const BTYPE &b) const
            {
                if(b.size() == 0)
                    throw MemoryNotAllocatedError(EXCEPTION_RECORD,
                                     "Source buffer not allocated!");

                if(b.size() != this->size())
                {
                    std::stringstream ss;
                    ss<<"Source buffer size ("<<b.size()<<") does not match";
                    ss<<"target field size ("<<this->size()<<")!";
                    throw SizeMissmatchError(EXCEPTION_RECORD,ss.str());
                }

                try
                {
                    this->imp().write(b.ptr());
                }
                catch(...)
                {
                    throw NXFieldError(EXCEPTION_RECORD,"Cannot write buffer!");
                }
            }

            //-----------------------------------------------------------------
            /*!
            \brief read data to array

            \throws MemoryNotAllocatedError if array buffer not allocated
            \throws ShapeMissmatchError if shapes do not match
            \throws NXFieldError in case of other errors
            \tparam ATYPE array type
            \param a reference to an instance fo ATYPE
            */
            template<typename ATYPE> void _read_array(ATYPE &a) const
            {
                if(a.size() == 0)
                    throw MemoryNotAllocatedError(EXCEPTION_RECORD,
                                     "Target array buffer not allocated!");

                auto ashape = a.shape<shape_t>();
                auto fshape = this->shape<shape_t>();
                
                if(ashape.size() == fshape.size())
                {
                    //if array and field have the same rank we need to check the
                    //shape of each of the objects
                    if(!std::equal(ashape.begin(),ashape.end(),fshape.begin()))
                        throw ShapeMissmatchError(EXCEPTION_RECORD,
                                _shape_missmatch_error_message(ashape,fshape));
                }
                else
                {
                    //if the two components are of different size we have to
                    //throw an exception in any case
                    if(this->size() != a.size())
                        throw ShapeMissmatchError(EXCEPTION_RECORD,
                                _shape_missmatch_error_message(ashape,fshape));
                }

                //finally we read the data
                try
                {
                    this->imp().read(const_cast<typename ATYPE::value_type*>(
                                a.storage().ptr()));
                }
                catch(pni::io::nx::NXFileError &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }

            }


            //-----------------------------------------------------------------
            /*!
            \brief write data from array

            \throws MemoryNotAllocatedError if array buffer not allocated
            \throws ShapeMissmatchError if shapes do not match
            \throws NXFieldError in case of other errors
            \tparam ATYPE array type
            \param a reference to an instance fo ATYPE
            */
            template<typename ATYPE> void _write_array(ATYPE &a) const
            {
                if(a.size() == 0)
                    throw MemoryNotAllocatedError(EXCEPTION_RECORD,
                                     "Source array buffer not allocated!");

                auto ashape = a.shape<shape_t>();
                auto fshape = this->shape<shape_t>();

                if(ashape.size() == fshape.size())
                {
                    if(!std::equal(ashape.begin(),ashape.end(),fshape.begin()))
                        throw ShapeMissmatchError(EXCEPTION_RECORD,
                                _shape_missmatch_error_message(ashape,fshape));
                }
                else
                {
                    if(this->size() != a.size())
                        throw ShapeMissmatchError(EXCEPTION_RECORD,
                               _shape_missmatch_error_message(ashape,fshape));
                }


                try { this->imp().write(a.storage().ptr()); }
                catch(...)
                {
                    throw NXFieldError(EXCEPTION_RECORD,
                                     "Cannt write data from array!");
                }
            }

            //-----------------------------------------------------------------
            void apply_selection(const std::vector<Slice> &s) 
            {
                this->imp().apply_selection(s);
            }

            //-----------------------------------------------------------------
            void reset_selection() 
            {
                this->imp().clear_selections();
            }

        public:
            //! shared pointer type for the field object
            typedef std::shared_ptr<NXField<Imp> > shared_ptr; 
            //============constructors and destructors=========================
            //! default constructor
            explicit NXField():NXObject<Imp>() { }

            //-----------------------------------------------------------------
            //! copy constructor
            NXField(const NXField<Imp> &o):NXObject<Imp>(o) { }

            //-----------------------------------------------------------------
            //! move constructor
            NXField(NXField<Imp> &&o):NXObject<Imp>(std::move(o)) { }

            //-----------------------------------------------------------------
            //! copy constructor from implementation object
            explicit NXField(const Imp &o):NXObject<Imp>(o) { }

            //-----------------------------------------------------------------
            //! move constructor from implementation object
            explicit NXField(Imp &&o):NXObject<Imp>(std::move(o)){}

            //-----------------------------------------------------------------
            //! copy conversion constructor
            template<typename ObjImp> NXField(const NXObject<ObjImp> &o)
                :NXObject<Imp>(o)
            { }

            //-----------------------------------------------------------------
            //!destructor
            ~NXField()
            { 
                this->imp().clear_selections();
            }

            //====================assignment operators=========================
            //! copy assignment
            NXField<Imp> &operator=(const NXField<Imp> &o)
            {
                if(this == &o) return *this;
                NXObject<Imp>::operator=(o);
                return *this;
            }

            //-----------------------------------------------------------------
            //! copy conversion assignment
            template<typename ObjImp>
            NXField<Imp> &operator=(const NXObject<ObjImp> &o)
            {
                if((void *)this == (void *)&o) return *this;
                NXObject<Imp>::operator=(o);
                return *this;
            }

            //-----------------------------------------------------------------
            //! move assignment
            NXField<Imp> &operator=(NXField<Imp> &&o)
            {
                if(this == &o) return *this;
                NXObject<Imp>::operator=(std::move(o));
                return *this;
            }


            //=================dataset inquiry methods=========================
            /*! 
            \brief field shape

            Returns the shape of the field
            \return Shape object
            */
            template<typename CTYPE> CTYPE shape() const 
            { 
                auto shape = this->imp().template shape<CTYPE>(); 
                return shape;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief return size

            Return the size (number of elements) in the field.
            \return total number of elements in the field
            */
            size_t size() const 
            { 
                size_t s = this->imp().size(); 
                return s;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief get the type ID

            Return the ID of the data type stored in the field.
            \return data type ID
            */
            TypeID type_id() const 
            {
                TypeID id = this->imp().type_id(); 
                return id;
            }

            //-----------------------------------------------------------------
            /*!
            \brief get parent object

            Returns the parent object of the field.
            \return parent object
            */
            NXObject<MAPTYPE(Imp,ObjectImpl)> parent() const
            {
                return NXObject<MAPTYPE(Imp,ObjectImpl)>(this->imp().parent());
            }
            
            //-----------------------------------------------------------------
            /*! 
            \brief resize field

            Resize the field to a new shape determined by s.  The rank of the
            old and the new shape must coincide otherwise an exception will be
            thrown.
            \throws ShapeMissmatchError if ranks do not match
            \throws NXFieldError in case of other errors
            \param s describing the new shape of the field
            */
            template<typename CTYPE> void resize(const CTYPE &s)
            {
                try
                {
                    this->imp().resize(s);
                }
                catch(ShapeMissmatchError &e)
                {
                    e.append(EXCEPTION_RECORD); throw e;
                }
                catch(...)
                {
                    throw NXFieldError(EXCEPTION_RECORD,
                            "Error resizing field!");
                }
            }

            //-----------------------------------------------------------------
            /*! 
            \brief grow field along a particular dimension

            Grows the field by n elements along dimension e. This method is
            pretty useful in cases where an arbitrary number of points shall be
            stored in a field and their number is not known when the field was
            created.
            \throws IndexError if e exceeds the rank of the field
            \throws NXFieldError in case of other errors
            \param e index of dimension along which to grow
            \param n number of elements by which to grow
            */
            void grow(const size_t &e,const size_t &n=1)
            {
                try
                {
                    this->imp().grow(e,n);
                }
                catch(IndexError &e)
                {
                    e.append(EXCEPTION_RECORD); throw e;
                }
                catch(...)
                {
                    std::stringstream ss;
                    ss<<"Growing field ["<<this->path();
                    ss<<"] along dimension"<<e<<" by "<<n<<" elements ";
                    ss<<"failed!";
                    throw NXFieldError(EXCEPTION_RECORD,ss.str());
                }
            }

            //-----------------------------------------------------------------
            /*! 
            \brief number of dimensions

            Returns the number of dimensions of the field.
            \return number of dimensions
            */
            size_t rank() const
            { 
                size_t r = this->imp().rank(); 
                return r;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief number of elements along dimension

            Returns the number of elements along dimension i. An exception is
            thrown if i exceeds the rank of the field.
            \throws IndexError if i exceeds the rank of the field
            \param i index of the dimension
            \return number of elements
            */
            size_t dim(size_t i) const
            { 
                size_t d = this->imp().dim(i); 
                return d;
            }

            //=============methods for reading data============================
            /*! 
            \brief reading simple data from the dataset

            Read a single data value from the dataset. In order to succeed the
            dataset must be a scalar dataset or the total size of the dataset
            must be 1.
            \code
            UInt32 scalar;
            field.read(scalar);
            \endcode
            \throws ShapeMissmatchError if dataset is not scalar
            \throws NXFieldError in all other error cases
            \param value variable where to store the data
            */
            template<typename T> void read(T &value) const
            {
                if(this->imp().size() != 1)
                    throw ShapeMissmatchError(EXCEPTION_RECORD,
                                              "Field is not scalar!");

                try
                {
                    this->imp().read(&value);
                }
                catch(...)
                {
                    throw NXFieldError(EXCEPTION_RECORD,
                                       "Error reading data from field ["
                                       +this->path()+"]!");
                }
            }

            //-----------------------------------------------------------------
            /*! 
            \brief reading data to a static buffer

            Copy data from a dataset to the buffer. The size of the dataset and
            the buffer must match. An exception will be thrown if the buffer
            object is not allocated.

            \code
            SBuffer<UInt16> buffer(field.size());
            field.read(buffer);

            \endcode
            \throws MemoryAccessError if the buffer is not allocated
            \throws SizeMissmatchError if sizes do not match
            \throws NXFieldError in all other cases
            \param buffer buffer where to store data
            */
            template<typename T,size_t SIZE> 
                void read(SBuffer<T,SIZE> &buffer) const
            {
                READ_BUFFER(buffer);
            }

            //-----------------------------------------------------------------
            /*!
            \brief read data to a reference buffer

            \throws MemoryNotAllocatedError if buffer not allocated
            \throws SizeMissmatchError if buffer and field size do not match
            \throws NXFieldError in case of any other errors
            \param buffer reference to an RBuffer instance
            */
            template<typename T> void read(RBuffer<T> &buffer) const
            {
                READ_BUFFER(buffer);
            }

            //-----------------------------------------------------------------
            /*!
            \brief read data to a dynamic buffer

            \throws MemoryNotAllocatedError if buffer not allocated
            \throws SizeMissmatchError if buffer and field size do not match
            \throws NXFieldError in case of any other errors
            \param buffer reference to an RBuffer instance
            */
            template<typename T,typename ALLOCATOR>
                void read(DBuffer<T,ALLOCATOR> &buffer) const
            {
                READ_BUFFER(buffer);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief read data to array

            Copy the data stored in the field to an array object.
            An exception is thrown if the buffer holding the arrays data is
            not allocated or the shape of the array does not match the shape
            of the field.
            
            \code
            DArray<Float32> a(field.shape<shape_t>());
            field.read(a);
            \endcode

            \throws ShapeMissmatchError if field and array-shape do not
            match
            \throws MemoryAccessError if array buffer not allocated
            \throws NXFieldError in case of all other errors.
            \param array Array instance where to store the data
            */
            template<typename T,typename STORAGE,typename IMAP>
                void read(DArray<T,STORAGE,IMAP> &array) const
            {
                READ_ARRAY(array);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief read data to a static array

            Copy the field data to a static array. 

            \throws ShapeMissmatchError if field and array-shape do not match
            \throws MemoryNotAllocatedError if array-buffer is not allocated
            \throws NXFieldError in acase of any other IO error
            \tparam OTS template arguments for SArray
            \param array  instance of SArray
            */
            template<typename T,size_t ...INDICES>
                void read(SArray<T,INDICES...> &array) const
            {
                READ_ARRAY(array);
            }

            //-----------------------------------------------------------------
            /*!
            \brief read data to a numeric array

            \throws MemoryNotAllocated if array buffer is not allocated
            \throws ShapeMissmatchError if array and field shape do not match
            \throws NXFieldError in case of any other IO error
            \tparam OTS template parameters for NumArray template
            \param array instance of NumArray
            */
            template<typename ATYPE>
                void read(NumArray<ATYPE> &array) const
            {
                try
                {
                    //this should virtually call the appropriate read method
                    //according to the storage type of the NumArray template
                    this->read(const_cast<ATYPE&>(array.storage()));
                }
                //we do not need to explicitely release the selections here as
                //this is already done by the read method when it throw an
                //exception
                catch(MemoryNotAllocatedError &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
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

           
            //=================methods for writing data========================
            /*! write a single value

            Writs a single value of type T to the field. This method will 
            succeed only if the field can hold only a single value.
            
            \code
            Float64 data = 1.2340;
            field.write(data);
            \endcode

            \throws ShapeMissmatchError if the dataspace is not scalar
            \throws NXFieldError in case of other errors
            \param value value to write
            */
            template<typename T> void write(const T &value) const
            {
                if(this->imp().size()!=1) 
                    throw ShapeMissmatchError(EXCEPTION_RECORD,
                                              "Field is not scalar!");

                try
                {
                    this->imp().write(&value);
                }
                catch(...)
                {
                    throw NXFieldError(EXCEPTION_RECORD,
                            "Error writing data to field ["
                            +this->path()+"]!");
                }

            }

            //-----------------------------------------------------------------
            /*! 
            \brief write old style string

            Writes a C-style string to disk. This method is a specialization of
            the write(const T &value) template mathod.

            \throws ShapeMissmatchError if the field is not scalar
            \throws NXFieldError in case of other errors
            \param value pointer to string data
            */
            void write(const char *value) const
            {
                try
                {
                    String s(value);
                    this->read(s);
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

            //------------------------------------------------------------------
            /*! 
            \brief write field from a DBuffer

            Write data form a DBuffer instance to the field.
            \throws MemoryNotAllocatedError if buffer is not allocated
            \throws SizeMissmatchError if buffer and field size do not match
            \throws NXFieldError in case of any other IO error
            \tparam OTS template arguments to DBuffer
            \param b instance of DBuffer from which to write data
            */
            template<typename T,typename ALLOCATOR> 
                void write(const DBuffer<T,ALLOCATOR> &b) const
            {
                WRITE_BUFFER(b);
            }

            //------------------------------------------------------------------
            /*! 
            \brief write field from a SBuffer

            Write data form a SBuffer instance to the field.
            \throws MemoryNotAllocatedError if buffer is not allocated
            \throws SizeMissmatchError if buffer and field size do not match
            \throws NXFieldError in case of any other IO error
            \tparam OTS template arguments to SBuffer
            \param b instance of SBuffer from which to write data
            */
            template<typename T,size_t SIZE> 
                void write(const SBuffer<T,SIZE> &b) const
            {
                WRITE_BUFFER(b);
            }

            //------------------------------------------------------------------
            /*! 
            \brief write field from a RBuffer

            Write data form a RBuffer instance to the field.
            \throws MemoryNotAllocatedError if buffer is not allocated
            \throws SizeMissmatchError if buffer and field size do not match
            \throws NXFieldError in case of any other IO error
            \tparam OTS template arguments to RBuffer
            \param b instance of RBuffer from which to write data
            */
            template<typename T> void write(const RBuffer<T> &b) const
            {
                WRITE_BUFFER(b);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief write data form a DArray

            Write data from an instance of DArray. 
            \throws MemoryNotAllocatedError if array-buffer is not allocated
            \throws ShapeMissmatchError if field and array shape do not match
            \throws NXFieldError in case of any other IO error
            \tparam OTS template arguments to DArray
            \param a instance of DArray
            */
            template<typename T,typename STORAGE,typename IMAP> 
                void write(const DArray<T,STORAGE,IMAP> &a) const
            {
                WRITE_ARRAY(a);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief write data form a SArray

            Write data from an instance of SArray. 
            \throws MemoryNotAllocatedError if array-buffer is not allocated
            \throws ShapeMissmatchError if field and array shape do not match
            \throws NXFieldError in case of any other IO error
            \tparam OTS template arguments to SArray
            \param a instance of SArray
            */
            template<typename T,size_t ...INDICES> 
                void write(const SArray<T,INDICES...> &a) const
            {
                WRITE_ARRAY(a);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief write data from a NumArray instance

            Write data form an instance of NumArray.
            \throws MemoryNotAllocatedError if array-buffer is not allocated
            \throws ShapeMissmatchError if field and array shape do not match
            \throws NXFieldError in case of any other IO error
            \tparam OTS template arguments to NumArray
            \param a instance of NumArray
            */
            template<typename ATYPE> 
                void write(const NumArray<ATYPE> &a) const
            {
                try
                {
                    this->write(a.storage());
                }
                catch(MemoryNotAllocatedError &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
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


            //---------------------------------------------------------------
            /*! 
            \brief set a selection on the field

            This method applies a selection to the field and return a reference
            to this field. This can now be used to write data only to the
            selection of the array.
            \code
            NXField f = g.create_field<UInt16>("frame",shape_t{1024,1024});
            DArray<UInt16> spec(shape_t{1024});

            f(100,Slice(0,1024)).read(spec)

            \endcode
            The selection will be reset with every call to the read() or write
            methods. 
            \tparam ITYPES index types
            \param indices instances of ITYPES
            \return field object with selection set
            */
            template<typename ...ITYPES>
            NXSelection<NXField<Imp> > operator()(ITYPES ...indices)
            {
                typedef NXSelection<NXField<Imp> > sel_type;
                typedef typename sel_type::selection_type container_type;

                return sel_type(container_type({Slice(indices)...}),*this);
            }

            //---------------------------------------------------------------
            /*!
            \brief set a selection on the field

            Operator to set a selection to the field. The selection is given by
            a vector container of Slice objects.
            The selection will be reset with each call to the read() or write()
            methods.
            \param selection container with instances of Slice
            \return instance of NXField with selection set
            */
            NXSelection<NXField<Imp> > operator()(const std::vector<Slice> &selection) 
            {
                typedef NXSelection<NXField<Imp> > sel_type;

                return sel_type(selection,*this);
            }
        
            friend class NXSelection<NXField<Imp> >;

    };

//end of namespace
}
}
}
