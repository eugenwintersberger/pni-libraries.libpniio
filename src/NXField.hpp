/*
 * Declaration of the NXfield template
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
 * Declaration of the NXfield template
 *
 * Created on: Jul 3, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXFIELD_HPP_
#define NXFIELD_HPP_

#include <sstream>

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/SBuffer.hpp>
#include <pni/utils/RBuffer.hpp>
#include <pni/utils/DBuffer.hpp>
#include <pni/utils/Slice.hpp>

#include "NXObject.hpp"
#include "NXExceptions.hpp"

using namespace pni::utils;

namespace pni{
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

    /*! \ingroup nexus_lowlevel
    \brief NXfield base class

    NXField is the basic data holding object in a Nexus file. You cannot create
    an instance of this object directly rather you have to use one of the
    factory methods provided by NXGroup.  NXField behaves like a container for
    data object which for the time being can be either strings, Scalars, or
    Array objects.
    */
    template<typename Imp> class NXField:public NXObject<Imp> 
    {
        private:
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
                    SizeMissmatchError error(EXCEPTION_RECORD,ss.str());
                    throw error;
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

                //clear selections if there  are some
                this->imp().clear_selections();
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
                    throw NXFieldError(EXCEPTION_RECORD,
                            "Cannot write buffer!");
                }

                //clear selection if there is one
                this->imp().clear_selections();
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
                if(!std::equal(ashape.begin(),ashape.end(),fshape.begin()))
                {
                    std::stringstream ss;
                    ss<<"Array shape ( ";
                    for(auto v: ashape) ss<<v<<" ";
                    ss<<") and field shape ( ";
                    for(auto v: fshape) ss<<v<<" ";
                    ss<<") do not match!";
                    throw ShapeMissmatchError(EXCEPTION_RECORD,ss.str());
                }

                try
                {
                    this->imp().read(const_cast<typename ATYPE::value_type*>(
                                a.storage().ptr()));
                }
                catch(...)
                {
                    throw NXFieldError(EXCEPTION_RECORD,
                            "Cannt read data to array!");
                }

                //clear selections
                this->imp().clear_selections();

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
                if(!std::equal(ashape.begin(),ashape.end(),fshape.begin()))
                {
                    std::stringstream ss;
                    ss<<"Source array shape ( ";
                    for(auto v: ashape) ss<<v<<" ";
                    ss<<") and field shape ( ";
                    for(auto v: fshape) ss<<v<<" ";
                    ss<<") do not match!";
                    throw ShapeMissmatchError(EXCEPTION_RECORD,ss.str());
                }

                try
                {
                    this->imp().write(a.storage().ptr());
                }
                catch(...)
                {
                    throw NXFieldError(EXCEPTION_RECORD,
                            "Cannt write data from array!");
                }

                //clear selections
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
            ~NXField(){ }

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
            template<typename CTYPE>
            CTYPE shape() const { return this->imp().template shape<CTYPE>(); }

            //-----------------------------------------------------------------
            /*! 
            \brief return size

            Return the size (number of elements) in the field.
            */
            size_t size() const { return this->imp().size(); }

            //-----------------------------------------------------------------
            /*! 
            \brief get the type ID

            Return the ID of the data type stored in the field.
            \return data type ID
            */
            TypeID type_id() const { return this->imp().type_id(); }
            
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
            size_t rank() const{ return this->imp().rank(); }

            //-----------------------------------------------------------------
            /*! \brief number of elements along dimension

            Returns the number of elements along dimension i. An exception is
            thrown if i exceeds the rank of the field.
            \throws IndexError if i exceeds the rank of the field
            \return number of elements
            */
            size_t dim(size_t i) const{ return this->imp().dim(i); }

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
                    "Error reading data from field ["+this->path()+"]!");
                }

                this->imp().clear_selections();
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
            template<typename ...OTYPES> 
                void read(SBuffer<OTYPES...> &buffer) const
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
            template<typename ...OTYPES>
                void read(RBuffer<OTYPES...> &buffer) const
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
            template<typename ...OTYPES>
                void read(DBuffer<OTYPES...> &buffer) const
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
            template<typename ...OTS>
                void read(DArray<OTS...> &array) const
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
            template<typename ...OTS>
                void read(SArray<OTS...> &array) const
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
            template<typename ...OTS>
                void read(NumArray<OTS...> &array) const
            {
                try
                {
                    //this should virtually call the appropriate read method
                    //according to the storage type of the NumArray template
                    this->read(array.storage());
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
                    "Error writing data to field ["+this->path()+"]!");
                }

                this->imp().clear_selections();
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
            template<typename ...OTS> void write(const DBuffer<OTS...> &b) const
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
            template<typename ...OTS> void write(const SBuffer<OTS...> &b) const
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
            template<typename ...OTS> void write(const RBuffer<OTS...> &b) const
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
            template<typename ...OTS> void write(const DArray<OTS...> &a) const
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
            template<typename ...OTS> void write(const SArray<OTS...> &a) const
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
            template<typename ...OTS> void write(const NumArray<OTS...> &a)
                const
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
            */
            template<typename ...ITYPES>
            NXField<Imp> &operator()(ITYPES ...indices)
            {

                this->imp().apply_selection(std::vector<Slice>({Slice(indices)...}));

                return *this; 
            }


    };

//end of namespace
}
}

#endif /* NXFIELD_HPP_ */
