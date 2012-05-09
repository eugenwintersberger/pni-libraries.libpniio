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
#include <pni/utils/Scalar.hpp>
#include <pni/utils/Shape.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/NumericObject.hpp>

#include "NXObject.hpp"
#include "NXExceptions.hpp"
#include "NXSelection.hpp"

using namespace pni::utils;

namespace pni{
    namespace nx{


        /*! \ingroup nexus_lowlevel
        \brief NXfield base class

        NXField is the basic data holding object in a Nexus file. You 
        cannot create an instance of this object directly rather you 
        have to use one of the factory methods provided by NXGroup.
        NXField behaves like a container for data object which for the 
        time being can be either strings, Scalars, or Array objects.
        */
        template<typename Imp> class NXField:public NXObject<Imp> {
            public:
                typedef std::shared_ptr<NXField<Imp> > 
                    shared_ptr; //!< shared pointer type for the field object
                //============constructors and destructors=====================
                //! default constructor
                explicit NXField():NXObject<Imp>()
                {
                }

                //-------------------------------------------------------------
                //! copy constructor
                NXField(const NXField<Imp> &o):NXObject<Imp>(o)
                {
                }

                //-------------------------------------------------------------
                //! move constructor
                NXField(NXField<Imp> &&o):NXObject<Imp>(std::move(o))
                {
                }

                //-------------------------------------------------------------
                //! copy constructor from implementation object
                explicit NXField(const Imp &o):NXObject<Imp>(o)
                {
                }
                //-------------------------------------------------------------
                //! move constructor from implementation object
                explicit NXField(Imp &&o):NXObject<Imp>(std::move(o)){}

                //-------------------------------------------------------------
                //! copy conversion constructor
                template<typename ObjImp> NXField(const NXObject<ObjImp> &o)
                    :NXObject<Imp>(o)
                {
                }


                //-------------------------------------------------------------
                //!destructor
                ~NXField(){
                }

                //=================assignment operators========================
                //! copy assignment
                NXField<Imp> &operator=(const NXField<Imp> &o)
                {
                    if(this == &o) return *this;
                    NXObject<Imp>::operator=(o);
                    return *this;
                }

                //-------------------------------------------------------------
                //! copy conversion assignment
                template<typename ObjImp>
                NXField<Imp> &operator=(const NXObject<ObjImp> &o)
                {
                    NXObject<Imp>::operator=(o);
                    return *this;
                }

                //-------------------------------------------------------------
                //! move assignment
                NXField<Imp> &operator=(NXField<Imp> &&o)
                {
                    if(this == &o) return *this;
                    NXObject<Imp>::operator=(std::move(o));
                    return *this;
                }


                //=============dataset inquiry methods=========================
                /*! \brief field shape

                Returns the shape of the field
                \return Shape object
                */
                Shape shape() const{
                    return this->imp().shape();
                }

                //-------------------------------------------------------------
                /*! \brief return size

                Return the size (number of elements) in the field.
                */
                size_t size() const{
                    return this->imp().size();
                }

                //-------------------------------------------------------------
                /*! \brief get the type ID

                Return the ID of the data type stored in the field.
                \return data type ID
                */
                TypeID type_id() const {
                    return this->imp().type_id();
                }
                
                //--------------------------------------------------------------
                /*! \brief resize field

                Resize the field to a new shape determined by s. 
                The rank of the old and the new shape must coincide otherwise 
                an exception will be thrown.
                \throws ShapeMissmatchError if ranks do not match
                \throws NXFieldError in case of other errors
                \param s describing the new shape of the field
                */
                void resize(const Shape &s)
                {
                    EXCEPTION_SETUP("void resize(const Shape &s)");
                    try{
                        this->imp().resize(s);
                    }catch(ShapeMissmatchError &e){
                        throw e;
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error resizing field!");
                        EXCEPTION_THROW();
                    }
                }

                //--------------------------------------------------------------
                /*! \brief grow field along a particular dimension

                Grows the field by n elements along dimension e. This method
                is pretty useful in cases where an arbitrary number of points
                shall be stored in a field and their number is not known 
                when the field was created.
                \throws IndexError if e exceeds the rank of the field
                \throws NXFieldError in case of other errors
                \param e index of dimension along which to grow
                \param n number of elements by which to grow
                */
                void grow(const size_t &e,const size_t &n=1)
                {
                    EXCEPTION_SETUP("void grow(const size_t &e,"
                            "const size_t &n=1)");

                    try{
                        this->imp().grow(e,n);
                    }catch(IndexError &e){
                        throw(e);
                    }catch(...){
                        std::stringstream ss;
                        ss<<"Growing field ["<<this->path();
                        ss<<"] along dimension"<<e<<" by "<<n<<" elements ";
                        ss<<"failed!";
                        EXCEPTION_INIT(NXFieldError,ss.str());
                        EXCEPTION_THROW();
                    }
                }

                //--------------------------------------------------------------
                /*! \brief number of dimensions

                Returns the number of dimensions of the field.
                \return number of dimensions
                */
                size_t rank() const{
                    return this->imp().rank();
                }

                //--------------------------------------------------------------
                /*! \brief number of elements along dimension

                Returns the number of elements along dimension i. An exception
                is thrown if i exceeds the rank of the field.
                \throws IndexError if i exceeds the rank of the field
                \return number of elements
                */
                size_t dim(size_t i) const{
                    return this->imp().dim(i);
                }

                //==========methods for reading data============================
                /*! reading simple data from the dataset

                Read a single data value from the dataset. In order 
                to succeed the dataset must be a scalar dataset or 
                the total size of the dataset must be 1.
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
                    EXCEPTION_SETUP("template<typename T> void NXField<Imp>::"
                            "read(T &value) const");

                    try{
                        this->imp().read(value);
                    }catch(SizeMissmatchError &error){
                        throw(error);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error reading data from "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //-------------------------------------------------------------
                /*! reading data to a buffer

                Copy data from a dataset to the buffer. The size
                of the dataset and the buffer must match. An exception will be
                thrown if the buffer object is not allocated.

                \code
                Buffer<UInt16> buffer(field.size());
                field.read(buffer);

                \endcode
                \throws MemoryAccessError if the buffer is not allocated
                \throws SizeMissmatchError if sizes do not match
                \throws NXFieldError in all other cases
                \param buffer buffer where to store data
                */
                template<typename T,template<typename,typename> class BT,
                         typename Allocator> 
                    void read(BT<T,Allocator> &buffer) const
                {
                    EXCEPTION_SETUP("template<typename T,template<typename> "
                            "class BT> void NXField<Imp>::read(BT<T> &buffer) const");

                    if(!buffer.is_allocated()){
                        std::stringstream ss;
                        ss<<"Buffer object not allocated - cannot write data";
                        ss<<" to field ["<<this->path()<<"]!";
                        EXCEPTION_INIT(MemoryAccessError,ss.str());
                        EXCEPTION_THROW();
                    }

                    try{
                        this->imp().read(buffer);
                    }catch(SizeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error reading data from "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //--------------------------------------------------------------
                /*! \brief read data to array

                Copy the data stored in the field to an array object.
                An exception is thrown if the buffer holding the arrays data is
                not allocated or the shape of the array does not match the shape
                of the field.
                
                \code
                Float32Array a(field.shape,field.name(),
                               field.attr("units").read<String>(),
                               field.attr("long_name").read<String>());
                field.read(a);
                \endcode

                \throws ShapeMissmatchError if field and array-shape do not
                match
                \throws MemoryAccessError if array buffer not allocated
                \throws NXFieldError in case of all other errors.
                \param array Array instance where to store the data
                */
                template<typename T,template<typename,typename> class BT,
                         typename Allocator>
                    void read(Array<T,BT,Allocator> &array) const
                {
                    EXCEPTION_SETUP("template<typename T,template<typename> "
                            "class BT> void read(Array<T,BT> &array) const");

                    if(!array.is_allocated()){
                        std::stringstream ss;
                        ss<<"Array buffer not allocated - cannot write data";
                        ss<<" to field ["<<this->path()<<"]!";
                        EXCEPTION_INIT(MemoryAccessError,ss.str());
                        EXCEPTION_THROW();
                    }

                    try{
                        this->imp().read(array);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error reading data from "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //--------------------------------------------------------------
                /*! \brief read data to scalar

                Copy data from the field to a simple scalar object. An exception
                will be thrown if the field is not scalar. 
                
                \code 
                Scalar<Float32> s(field.name(),
                                  field.attr("units").read<String>(),
                                  field.attr("long_name").read<String>());
                field.read(s);
                \endcode

                \throws ShapeMissmatchError if the field is not scalar
                \throws NXFieldError in case of other errors
                \param data instance of Scalar<T> where to store the data
                */
                template<typename T> void read(Scalar<T> &data) const
                {
                    EXCEPTION_SETUP("template<typename T> void NXField<Imp>::"
                            "read(Scalar<T> &data) const");
                    
                    try{
                        this->imp().read(data);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error reading data from "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }
               
                //---------------------------------------------------------------
                /*! \brief read data to a complex value

                Copy data to a value of type std::complex<T> where T is a
                floating point type. An exception is thrown in the field is not
                scalar.
                
                \code
                std::complex<Float32> value;
                field.read(value);
                \endcode

                \throws ShapeMissmatchError if field is not scalar
                \throws NXFieldError in case of other errors
                \param value instance of std::complex<T>
                */
                template<typename T> void read(std::complex<T> &value) const
                {
                    EXCEPTION_SETUP("template<typename T> void NXField<Imp>::"
                            "read(std::complex<T> &value) const");

                    try{
                        this->imp().read(value);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error reading data from "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //--------------------------------------------------------------
                /*! \brief read data to a user defined typ

                This is a special method which allows the user to select which
                object to use for reading data.
                The advantage of this method is that a user must not take care
                about allocating an object of appropriate size. This is done by
                the method automatically. The only thing the user must know is
                which object he wants and the data-type which should be used.
                A ShapeMissmatchError is thrown if, for instance Object can only
                hold scalar data but the field is a multidimensional array (the
                same holds the other way around). SizeMissmatchErrors are hardly
                possible as the method is doing all memory allocation by itself.
                In the case of Buffer<T> this means, for instance, that the
                buffer is always of sufficient size. 

                Clearly this method has the disadvantage that with each call a
                new instance of an object is created. This might no be a problem
                for scalar types. However, for large array types the expenses
                for memory allocation can be come critical.
                
                \code
                auto data = field.read<Buffer<Float32> >();
                \endcode

                \throws ShapeMissmatchError in case of shape issues
                \throws NXFieldError in case of an arbitrary error.
                \return instance of Object with the data
                */
                template<typename Object> Object read() const
                {
                    EXCEPTION_SETUP("template<typename Object> Object"
                            "NXField<Imp>::read() const");
                    
                    try{
                        return this->imp().read<Object>();                    
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(SizeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error reading data from "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }
               
                //-------------------------------------------------------------
                /*! \brief read binary data

                Copy data as binary from the field. This is a specialization of
                the read(T &value) template. 
                
                \code
                Binary bin;
                field.read(bin);
                \endcode

                \throws ShapeMissmatchError if field is not scalar
                \throws NXFieldError in case of other errors
                \param value instance of Binary
                */
                void read(Binary &value) const
                {
                    EXCEPTION_SETUP("void NXField<Imp>::read(Binary &value) "
                            "const");

                    try{
                        this->imp().read(value);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error reading data from "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //-------------------------------------------------------------
                /*! \brief read string value

                Read a String value from a field. This is a specialization of
                the read(T &value) template method.
            
                \code
                String s;
                field.read(s);
                \endcode

                \throws ShapeMissmatchError if the field is not scalar
                \throws NXFieldError in case of other errors
                \param value string value where to copy data
                */
                void read(String &value) const
                {
                    EXCEPTION_SETUP("void NXField<Imp>::read(String &value) "
                            "const");

                    try{
                        this->imp().read(value);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error reading data from "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //=============methods for writing data========================
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
                    EXCEPTION_SETUP("template<typename T> void NXField<Imp>::"
                            "write(const T &value) const");

                    try{
                        this->imp().write(value);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error writing data to "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //-------------------------------------------------------------
                /*! \brief write complex value

                Writes a complex data value to the field. This is a
                specialization of the write(T &value) template method.

                \code
                Complex32 value(1.2,-134.20);
                field.write(value);
                \endcode

                \throws ShapeMissmatchError if the field is not scalar
                \throws NXFieldError in case of other errors
                \param value complex data value to write
                */
                template<typename T> void write(const std::complex<T> &value)
                    const
                {
                    EXCEPTION_SETUP("template<typename T> void NXField<Imp>::"
                            "write(const std::complex<T> &value) const");

                    try{
                        this->imp().write(value);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error writing data to "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //-------------------------------------------------------------
                /*! \brief write binary value

                Writes a single binary value. This is a specialization of the
                write(const T &value) template method.

                \code
                Binary bin;
                ...
                field.write(bin);
                \endcode

                \throws ShapeMissmatchError if field is not scalar
                \throws NXFieldError in case of other errors
                \param value binary value to write.
                */
                void write(const Binary &value) const
                {
                    EXCEPTION_SETUP("void NXField<Imp>::write(const Binary "
                            "&value) const");

                    try{
                        this->imp().write(value);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error writing data to "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //-------------------------------------------------------------
                /*! \brief write String value

                Writes a single string to the field. This method is a
                specialization of the write(const T &value) template. 

                \code
                String s = "hello world";
                field.write(s);
                \endcode

                \throws ShapeMissmatchError if the field is not scalar
                \throws NXFieldError in case of other errors
                \param value string to write to disk
                */
                void write(const String &value) const
                {
                    EXCEPTION_SETUP("void NXField<Imp>::write(const String "
                            "&value) const");

                    try{
                        this->imp().write(value);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error writing data to "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //-------------------------------------------------------------
                /*! \brief write old style string

                Writes a C-style string to disk. This method is a specialization
                of the write(const T &value) template mathod.

                \throws ShapeMissmatchError if the field is not scalar
                \throws NXFieldError in case of other errors
                \param value pointer to string data
                */
                void write(const char *value) const
                {
                    EXCEPTION_SETUP("void NXField<Imp>::write(const char "
                            "*value) const");

                    try{
                        this->imp().write(String(value));
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error writing data to "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //-------------------------------------------------------------
                /*! \brief write buffer content

                Writes the content of a buffer object to the field. In order for
                this method to succeed the buffer must be allocated and its size
                must match the size of the field. 

                \code
                Buffer<Binary> image_data;
                ...
                field.write(image_data);
                \endcode
                
                \throws SizeMissmatchError field and buffer size do not match
                \throws MemoryAccessError buffer is not allocated
                \throws NXFieldError in cases of other errors
                \param buffer buffer object whose data to write
                */
                template<typename T,template<typename,typename> class BT,
                         typename Allocator>
                    void write(const BT<T,Allocator> &buffer) const
                {
                    EXCEPTION_SETUP("template<typename T,template<typename> "
                            "class BT> void write(const BT<T> &buffer) const");

                    if(!buffer.is_allocated()){
                        String estr = "Buffer not allocated - cannot write data"
                                      " to field ["+this->path()+"]!";
                        EXCEPTION_INIT(MemoryAccessError,estr);
                        EXCEPTION_THROW();
                    }
                    try{
                        this->imp().write(buffer);
                    }catch(SizeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error writing data to "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }

                }

                //--------------------------------------------------------------
                /*! \brief write an array

                Write the content of an array to the field.

                \code
                UInt32Array det({1024,1024},"image","cps","reference image data");
                ...
                field.write(det);
                \endcode

                \throws ShapeMissmatchError if array and dataset shape do not match
                \throws MemoryAccessError array buffer not allocated
                \throws NXFieldError in case of other errors
                \param array array to write to disk
                */
                template<typename T,template<typename,typename> class BT,
                         typename Allocator>
                    void write(const Array<T,BT,Allocator> &array) const
                {
                    EXCEPTION_SETUP("template<typename T,template<typename> "
                            "class BT> void write(const Array<T,BT> &array)"
                            "const");

                    if(!array.is_allocated()){
                        EXCEPTION_INIT(MemoryAccessError,
                                "Array not allocated!");
                        EXCEPTION_THROW();
                    }
                    try{
                        this->imp().write(array);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error writing data to "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }

                }

                //-------------------------------------------------------------
                /*! \brief write a scalar to disk

                Write a single scalar object to disk. 

                \code 
                Int32Scalar s("counter","cps","a simple counter");
                s = 10230;
                field.write(s);
                \endcode 

                \throws ShapeMissmatchError if not a scalar dataset
                \throws NXFieldError in case of all other errors
                \param scalar scalar object to write to disk
                */
                template<typename T> void write(const Scalar<T> &scalar) const
                {
                    EXCEPTION_SETUP("template<typename T> void NXField<Imp>::"
                            "write(const Scalar<T> &scalar) const");

                    try{
                        this->imp().write(scalar);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error writing data to "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //---------------------------------------------------------------
                /*! \brief create a selection

                Create a new selection object for the field. 
                \return selection object
                \sa NXSelection
                */
                NXSelection<MAPTYPE(Imp,SelectionImpl)> selection() const
                {
                    typedef MAPTYPE(Imp,SelectionImpl) SelectionImpl;
                    typedef NXSelection<SelectionImpl> Selection;

                    return Selection(this->imp().selection());
                }



        };

//end of namespace
    }
}

#endif /* NXFIELD_HPP_ */
