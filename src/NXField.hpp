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

#include <pni/utils/Types.hpp>
#include <pni/utils/ScalarObject.hpp>
#include <pni/utils/Scalar.hpp>
#include <pni/utils/Shape.hpp>
#include <pni/utils/ArrayObject.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/NumericObject.hpp>

#include "NXObject.hpp"
#include "NXExceptions.hpp"
#include "NXSelection.hpp"

using namespace pni::utils;

namespace pni{
    namespace nx{


        //! \ingroup nexus_lowlevel
        //! \brief NXfield base class

        //! NXField is the basic data holding object in a Nexus file. You 
        //! cannot create an instance of this object directly rather you 
        //! have to use one of the factory methods provided by NXGroup.
        //! NXField behaves like a container for data object which for the 
        //! time being can be either strings, Scalars, or Array objects.
        template<typename Imp> class NXField:public NXObject<Imp> {
            public:
                typedef std::shared_ptr<NXField<Imp> > sptr;
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
                //! copy constructor from implemenetation object
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


                //=============dataset inquery methods=========================
                //! field shape

                //! Returns the shape of the field
                //! \return Shape object
                Shape shape() const{
                    return this->imp().shape();
                }

                //-------------------------------------------------------------
                //! return size

                //! Return the size (number of elements) in the field.
                size_t size() const{
                    return this->imp().size();
                }

                //-------------------------------------------------------------
                //! get the type ID

                //! Return the ID of the data type stored in the field.
                //! \return data type ID
                TypeID type_id() const {
                    return this->imp().type_id();
                }
                
                //--------------------------------------------------------------
                void resize(const Shape &s)
                {
                    this->imp().resize(s);
                }

                //--------------------------------------------------------------
                void grow(const size_t &e,const size_t &n=1)
                {
                    this->imp().grow(e,n);
                }

                //--------------------------------------------------------------
                size_t rank() const{
                    return this->imp().rank();
                }

                //--------------------------------------------------------------
                size_t dim(size_t i) const{
                    return this->imp().dim(i);
                }


                //==========methods for reading data============================
                //! reading simple data from the dataset

                //! Read a single data value from the dataset. In order 
                //! to succeed the dataset must be a scalar dataset or 
                //! the total size of the dataset must be 1.
                //! \throws ShapeMissmatchError if dataset is not scalar
                //! \throws H5DataSetError in all other error cases
                //! \param value variable where to store the data
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
                //! reading data to a buffer

                //! Copy data from a dataset to the buffer. The size
                //! of the dataset and the buffer must match.
                //! \throws SizeMissmatchError if sizes do not match
                //! \throws H5DataSetError in all other cases
                //! \param buffer buffer where to store data
                template<typename T,template<typename> class BT> 
                    void read(BT<T> &buffer) const
                {
                    EXCEPTION_SETUP("template<typename T,template<typename> "
                            "class BT> void NXField<Imp>::read(BT<T> &buffer) const");

                    if(!buffer.is_allocated()){
                        EXCEPTION_INIT(MemoryAccessError,
                                "Buffer not allocated!");
                        EXCEPTION_THROW();
                    }

                    try{
                        this->imp().read(buffer);
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

                //--------------------------------------------------------------
                template<typename T,template<typename> class BT>
                    void read(Array<T,BT> &array) const
                {
                    EXCEPTION_SETUP("template<typename T,template<typename> "
                            "class BT> void read(Array<T,BT> &array) const");

                    if(!array.is_allocated()){
                        EXCEPTION_INIT(MemoryAccessError,
                                "Array not allocated!");
                        EXCEPTION_THROW();
                    }

                    try{
                        this->imp().read(array);
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

                //--------------------------------------------------------------
                template<typename T> void read(Scalar<T> &data) const
                {
                    EXCEPTION_SETUP("template<typename T> void NXField<Imp>::"
                            "read(Scalar<T> &data) const");
                    
                    try{
                        this->imp().read(data);
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
               
                //---------------------------------------------------------------
                template<typename T> void read(std::complex<T> &value) const
                {
                    EXCEPTION_SETUP("template<typename T> void NXField<Imp>::"
                            "read(std::complex<T> &value) const");

                    try{
                        this->imp().read(value);
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

                //--------------------------------------------------------------
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
                void read(Binary &value) const
                {
                    EXCEPTION_SETUP("void NXField<Imp>::read(Binary &value) "
                            "const");

                    try{
                        this->imp().read(value);
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
                void read(String &value) const
                {
                    EXCEPTION_SETUP("void NXField<Imp>::read(String &value) "
                            "const");

                    try{
                        this->imp().read(value);
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

                //=============methods for writing data========================
                //! write a single value

                //! This method writes a single value of a particular type
                //! reading the data from variable value. This method 
                //! works only if the dataspace of the dataset is scalar or 
                //! the total dataspace size is 1.
                //! \throws ShapeMissmatchError if the dataspace is not scalar
                //! \throws H5DataSetError in case of other errors
                //! \param value data source
                template<typename T> void write(const T &value) const
                {
                    EXCEPTION_SETUP("template<typename T> void NXField<Imp>::"
                            "write(const T &value) const");

                    try{
                        this->imp().write(value);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(SizeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error writing data to "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //-------------------------------------------------------------
                template<typename T> void write(const std::complex<T> &value)
                    const
                {
                    EXCEPTION_SETUP("template<typename T> void NXField<Imp>::"
                            "write(const std::complex<T> &value) const");

                    try{
                        this->imp().write(value);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(SizeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error writing data to "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //-------------------------------------------------------------
                void write(const Binary &value) const
                {
                    EXCEPTION_SETUP("void NXField<Imp>::write(const Binary "
                            "&value) const");

                    try{
                        this->imp().write(value);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(SizeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error writing data to "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //-------------------------------------------------------------
                void write(const String &value) const
                {
                    EXCEPTION_SETUP("void NXField<Imp>::write(const String "
                            "&value) const");

                    try{
                        this->imp().write(value);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(SizeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error writing data to "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //-------------------------------------------------------------
                void write(const char *value) const
                {
                    EXCEPTION_SETUP("void NXField<Imp>::write(const char "
                            "*value) const");

                    try{
                        this->imp().write(String(value));
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(SizeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error writing data to "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //-------------------------------------------------------------
                //! write a buffer 

                //! Write the content of a memory buffer to the dataset.
                //! The dataset must not be scalar. In order to succeed
                //! the size of the buffer must match the size of the 
                //! dataset.
                //! \throws SizeMissmatchError sizes do not match
                //! \throws H5DataSetError in cases of other errors
                //! \param buffer reference to the buffer
                template<typename T,template<typename> class BT>
                    void write(const BT<T> &buffer) const
                {
                    EXCEPTION_SETUP("template<typename T,template<typename> "
                            "class BT> void write(const BT<T> &buffer) const");

                    if(!buffer.is_allocated()){
                        EXCEPTION_INIT(MemoryAccessError,"Buffer not allocated!");
                        EXCEPTION_THROW();
                    }
                    try{
                        this->imp().write(buffer);
                    }catch(SizeMissmatchError &error){
                        throw(error);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error writing data to "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }

                }

                //--------------------------------------------------------------
                //! write an array

                //! Write an array to the dataset. In order to succeed
                //! The shape of the array must match the shape of the 
                //! dataset. In addtion the dataset must not be scalar.
                //! \throws ShapeMissmatchError if array and dataset shape do not match
                //! \throws H5DataSetError in case of other errors
                //! \param array array to write to disk
                template<typename T,template<typename> class BT>
                    void write(const Array<T,BT> &array) const
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
                    }catch(SizeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error writing data to "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }

                }

                //-------------------------------------------------------------
                //! write a scalar

                //! Write a single scalar object to disk. This can only 
                //! succeed if the dataset is a scalar.
                //! \throws ShapeMissmatchError if not a scalar dataset
                //! \throws H5DataSetError in case of all other errors
                //! \param scalar scalar object to write to disk
                template<typename T> void write(const Scalar<T> &scalar) const
                {
                    EXCEPTION_SETUP("template<typename T> void NXField<Imp>::"
                            "write(const Scalar<T> &scalar) const");

                    try{
                        this->imp().write(scalar);
                    }catch(ShapeMissmatchError &error){
                        throw(error);
                    }catch(SizeMissmatchError &error){
                        throw(error);
                    }catch(...){
                        EXCEPTION_INIT(NXFieldError,"Error writing data to "
                                "field ["+this->path()+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //---------------------------------------------------------------
                //! create a selection
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
