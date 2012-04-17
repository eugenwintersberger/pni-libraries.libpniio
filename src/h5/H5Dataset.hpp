/*
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
 * Definition of an HDF5 dataset class
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#ifndef __H5DATASET_HPP__
#define __H5DATASET_HPP__

#include <sstream>
#include <pni/utils/Types.hpp>

using namespace pni::utils;

#include "H5AttributeObject.hpp"
#include "H5Datatype.hpp"
#include "H5Dataspace.hpp"
#include "H5Group.hpp"
#include "H5ObjectType.hpp"
#include "H5Filter.hpp"


namespace pni{
    namespace nx{
        namespace h5{
            class H5Selection;

            //! \ingroup nxh5_classes
            //! \brief dataset object

            //! Datasets are the essential data holding objects in HDF5.
            class H5Dataset:public H5AttributeObject{
                private:
                    H5Dataspace _space; //!< local dataspace of the dataset

                    //---------some private IO templates----------------------
                    /*! \brief write data from memory

                    This private method writes data from a memory region
                    addressed by ptr to the HDF5 file. The allocated memory must
                    fit in size and type to the dataset.
                    \throws H5DataSetError in case of errors
                    \param ptr address to the memory region
                    */
                    template<typename T> void __write(const T *ptr) const;

                    //--------------------------------------------------------
                    /*! \brief read data from memory
                
                    Private method to read data from the dataset to a particular
                    region of memory addressed by ptr. The size of the
                    allocated memory must be large enough to store all the data
                    from the dataset.
                    \throws H5DataSetError in case of errors
                    \param ptr address of the memory region
                    */
                    template<typename T> void __read(T *ptr) const; 

                    //--------------------------------------------------------
                    H5Dataspace __obtain_dataspace() const{
                        return  H5Dataspace(H5Dget_space(id()));
                    }

                    //--------------------------------------------------------
                    H5Datatype __obtain_datatype() const{
                        return H5Datatype(H5Dget_type(id()));
                    }

                    //---------------------------------------------------------
                    /*! \brief throw exception if dataspace not scalar
                    
                    This private method throws an exception in a particular 
                    method if the dataset is not scalar (if the size of the
                    dataset is not 1).
                    \throws ShapeMissmatchError if dataset is not scalar
                    \param method name of the method where to error occurred 
                    */
                    void __throw_if_not_scalar(const String &method) const;

                    //---------------------------------------------------------
                    /*! \brief checks buffer compatibility
                    
                    Private method for checking the compatibility of a buffer
                    object with the dataset. If the buffer is not safe for IO
                    operations exceptions will be thrown.
                    \throws MemoryAllocationError if buffer not allocated
                    \throws SizeMissmatchError if buffer size does not match
                    dataset size
                    */
                    void __check_buffer(const String &method,
                                        const BufferObject &buffer
                                       ) const;

                    //----------------------------------------------------------
                    /*! \brief checks array compatibility
                    
                    Private method for checking array objects for IO
                    compatibility. In case of problems this method throws
                    exceptions.
                    \throw MemoryAllocationError array memory not allocated
                    \throw ShapeMissmatchError if dataset and array shape do not
                    match
                    */
                    void __check_array(const String &method,
                                       const ArrayObject &array
                                      ) const;
                public:
                    //===================Constructors and destructors==========
                    //! default constructor
                    explicit H5Dataset();
                    //! copy constructor
                    H5Dataset(const H5Dataset &o);

                    //----------------------------------------------------------
                    /*! \brief copy conversion constructor
                    
                    This constructor allows the conversion of a general H5Object
                    to a dataset. If the H5Object does not refer to an HDF5
                    dataset an exception will be thrown.
                    \throws H5DatasetError if H5Object is not a dataset
                    \param o reference to an H5Object
                    */
                    H5Dataset(const H5Object &o);

                    //----------------------------------------------------------
                    //! move constructor
                    H5Dataset(H5Dataset &&o);

                    //----------------------------------------------------------
                    /*! \brief move conversion constructor
                    
                    Allows move conversion from an HDF5Object to an HDF5
                    dataset. If the object does not refer to a dataset an
                    exception will be thrown.
                    \throws H5DatasetError if o does not refer to a dataset
                    \param o move reference to an H5Object
                    */
                    H5Dataset(H5Object &&o);

                    //----------------------------------------------------------
                    /*! constructor - contiguous dataset
    
                    Creates a contiguous array of shape s. The result is most 
                    probably the simplest form of a dataset. Such a dataset 
                    cannot be resized. The shape of the dataspace is 
                    determined by the argument s which is the intial as well 
                    as the maximum size of the dataspace.
                    \throws H5DatasetError in case of all kinds of errors
                    \param n name of the dataset
                    \param g parent group
                    \param t id of the data type
                    \param s shape of the dataset
                    */
                    explicit H5Dataset(const String &n, 
                                       const H5Group &g,
                                       const H5Datatype &t, 
                                       const H5Dataspace &s);

                    //----------------------------------------------------------
                    /*! \brief constructor - chunked dataset
                    
                    Constructor for a chunked dataset. Unlike contiguous 
                    datasets chunked datasets can be resized. Its content 
                    is subdivided into several chunks. Furthermore chunked 
                    datasets can be compressed. Where the compression
                    algorithm is applied to individual chunks not on the 
                    entire dataset.
                    \throws H5DatasetError in case of errors 
                    \param n dataset name
                    \param g parent group
                    \param t ID of the data type
                    \param s shape of the dataset
                    \param cs chunk shape
                    \sa H5Dataset(const String &n, const H5Group &g, 
                    const H5Datatype &t, const H5Dataspace &s)
                    \sa H5Dataset(const String &n,const H5Group &g, 
                    const H5Datatype &t, const H5Dataspace &s,const Shape &cs)
                    */
                    explicit H5Dataset(const String &n,
                                       const H5Group &g,
                                       const H5Datatype &t, 
                                       const H5Dataspace &s,
                                       const Shape &cs);

                    //---------------------------------------------------------
                    /*! \brief construct - chunked dataset with filter
                    
                    Constructor for a chunked dataset with a filter. Actually
                    only a deflate filter is supported. To use filters a dataset
                    must be a chunked dataset. Thus a proper chunk-size must be
                    provided.
                    \throws H5DatasetError in case of errors
                    \param n name of the dataset
                    \param g group below which to create the dataset
                    \param t datatype to use
                    \param s dataspace used for the dataset
                    \param cs chunk shape
                    \param filter H5Filter object describing the filter to use
                    \sa H5Dataset(const String &n,const H5Group &g, 
                    const H5Datatype &t, const H5Dataspace &s,const Shape &cs)
                    */
                    explicit H5Dataset(const String &n,
                                       const H5Group &g,
                                       const H5Datatype &t, 
                                       const H5Dataspace &s,
                                       const Shape &cs,
                                       const H5Filter &filter);

                    //---------------------------------------------------------
                    /*! \brief construct from an object ID
                    
                    Constructor can use an HDF5 object ID directly to
                    instantiate an HDF5 dataset. If the ID does not refer to a
                    dataset an exception will  be thrown.
                    \throws H5DatasetError if oid does not refer to a dataset
                    \param oid HDF5 object id
                    */
                    explicit H5Dataset(const hid_t &oid);

                    //---------------------------------------------------------
                    //! destructor
                    ~H5Dataset();

                    //=================factory methods=========================
                    /*! \brief static factory method

                    The constructors of H5Dataset use H5Datateyp and H5Dataspace
                    objects to describe the datatype and shape of the dataset.
                    In virtually all cases it is more convenient to use a shape
                    object and a native type instead. This static template
                    factory method allows the creation of a H5Dataset object
                    using the template parameter to determin the datatype to use
                    and a shape object to describe the dataspace. The dataspaces
                    created using this method are infinitely extensible in along
                    all dimensions.
                    \throws ShapeMissmatchError if chunk and field shape do not
                    have the same rank
                    \throws H5DatasetError in case of errors
                    \param n name of the dataset
                    \param g group below which the dataset will be created
                    \param s shape describing the dataset
                    \param cs chunk shape
                    \return H5Dataset object
                    */
                    template<typename T> static H5Dataset create(
                                         const String &n,
                                         const H5Group &g,
                                         const Shape &s,
                                         const Shape &cs)
                    {
                        //create the datatype
                        H5Datatype type = H5DatatypeFactory::create_type<T>();

                        if(s.rank() != cs.rank())
                        {
                            std::stringstream estr;
                            ShapeMissmatchError error;
                            error.issuer("template<typename T> static "
                                    "H5Dataset create( const String &n,"
                                    "const H5Group &g, const Shape &s,"
                                    "const Shape &cs)");
                            estr<<"Chunk shape and field shape must be";
                            estr<<" equal!"<<std::endl;
                            estr<<"Field shape: "<<s<<std::endl;
                            estr<<"Chunk shape: "<<cs<<std::endl;
                            error.description(estr.str());
                            throw(error);
                        }

                        //create the data space
                        Shape ms(s.rank());
                        for(size_t i=0;i<s.rank();i++){
                            ms.dim(i,H5Dataspace::UNLIMITED);
                        }
                        H5Dataspace space(s,ms);

                        //create the data type
                        return H5Dataset(n,g,type,space,cs);
                    }

                    //---------------------------------------------------------
                    /*! \brief create multidimensional dataset

                    Static factory template method to create a chunked dataset.
                    The method behaves exactly like static H5Dataset create(
                    const String &n,const H5Group &g,const Shape &s, const Shape
                    &cs) despite the fact that it requires an additional
                    argument describing the filter.
                    \throws H5DatasetError in case of errors
                    \throws ShapeMissmatchError if chunk and dataset shape do
                    not have equal rank
                    \param n name of the dataset
                    \param g group below which the dataset will be created
                    \param s shape describing the dataset
                    \param cs chunk shape
                    \param filter H5Filter object describing the filter
                    \param H5Dataset instance
                    */
                    template<typename T> static H5Dataset create(
                                         const String &n,
                                         const H5Group &g,
                                         const Shape &s,
                                         const Shape &cs,
                                         const H5Filter &filter)
                    {
                        //create the datatype
                        H5Datatype type = H5DatatypeFactory::create_type<T>();
                        
                        if(s.rank() != cs.rank())
                        {
                            std::stringstream estr;
                            ShapeMissmatchError error;
                            error.issuer("template<typename T> static "
                                    "H5Dataset create( const String &n,"
                                    "const H5Group &g, const Shape &s,"
                                    "const Shape &cs)");
                            estr<<"Chunk shape and field shape must be";
                            estr<<" equal!"<<std::endl;
                            estr<<"Field shape: "<<s<<std::endl;
                            estr<<"Chunk shape: "<<cs<<std::endl;
                            error.description(estr.str());
                            throw(error);
                        }

                        //create the data space
                        Shape ms(s.rank());
                        for(size_t i=0;i<s.rank();i++){
                            ms.dim(i,H5Dataspace::UNLIMITED);
                        }
                        H5Dataspace space(s,ms);

                        //create the data type
                        return H5Dataset(n,g,type,space,cs,filter);
                    }


                    //=================assignment operators====================
                    //! copy assignment operator
                    H5Dataset &operator=(const H5Dataset &o);

                    //---------------------------------------------------------
                    /*! \brief copy conversion assignment
                    
                    Allows the assignment conversion from a plain H5Object to a
                    dataset. If the object does not refer to a dataset an
                    exception will be thrown.
                    \throws H5DatasetError if H5Object is not a dataset
                    \param o H5Object to convert to H5Datatype
                    */
                    H5Dataset &operator=(const H5Object &o);

                    //---------------------------------------------------------
                    //! move assignment operator
                    H5Dataset &operator=(H5Dataset &&o);

                    //---------------------------------------------------------
                    /*! move conversion assignment

                    Allows move conversion assignment from a plain H5Object to a
                    H5Dataset object. If H5Object does not refer to a dataset an
                    exception will be thrown. 
                    \throws H5DatasetError if H5Object is not a dataset
                    \param o H5Object to convert to H5Dataset
                    */
                    H5Dataset &operator=(H5Object &&o);

                    //=================methods to modify the dataset===========
                    /*! \brief resize the dataset

                    Set the shape of the dataset to s. The new shape must
                    satisfy some restrictions: 

                    \li the rank of s must not exceed the rank of the orignal
                    dataset
                    \li the new number of elements of each dimension must not
                    exceed the maximum number of elements along each dimension
                    as set in the dataspace used to create the dataset.

                    If this requirements are not met by s an exception will be
                    thrown.
                    \throws ShapeMissmatchError if rank of s is not equal to the
                    rank of the dataset
                    \throws H5DataSetError in case of other errors during
                    resizeing
                    \param s shape object describing the new shape of the
                    dataset
                    */
                    void resize(const Shape &s);

                    //---------------------------------------------------------
                    /*! \brief extend the shape along a dimension

                    Extends the size of the dataset along a single dimension.
                    This command can be quite useful for writing data
                    sequentially. 
                    \throws IndexError if e exceeds the rank of the dataset
                    \throws H5DataSetError in case of other errors
                    \param e index of the extend dimension
                    \param n number of elements by which the dimension shall be
                    extended
                    */
                    void grow(const size_t &e=0,const size_t &n=1);

                    //---------------------------------------------------------
                    /*! \brief total number of elements

                    Returns the total number of elements stored in the dataset.
                    \return total number of elements
                    */
                    size_t size() const;

                    //---------------------------------------------------------
                    /*! \brief shape of dataset

                    Returns a copy of the datasets shape. 
                    \return dataset shape
                    */
                    Shape  shape() const;

                    //---------------------------------------------------------
                    //! rank of the dataset

                    //! Returns the number of dimensions of the dataset.
                    //! \return number of dimensions
                    size_t rank() const;

                    //---------------------------------------------------------
                    //! number of elements

                    //! Returns the number of elements along dimension i. 
                    //! \throws IndexError if i exceeds dataset rank
                    //! \param i index of the dimension
                    //! \return number of elements along i
                    size_t dim(const size_t &i) const;

                    //---------------------------------------------------------
                    //! datatype ID

                    //! Datatype ID of the dataset. 
                    //! \return type id of the datatype of the dataset
                    TypeID type_id() const;

                    //----------------------------------------------------------
                    /*! \brief return a selection 

                    Returns a selection offset for the dataset. The selection 
                    created by this method initially spans the entire dataset.
                    Restrictions to the selection must be made later by the
                    user. Selections can be only made on multidimensional
                    datasets. If the dataspace which was used to create the
                    dataset was scalar an exception will be thrown.
                    It is important to note that a selection object is always
                    bound to the dataset it belongs to. You cannot reconnect a
                    selection to a new dataset. Instead you always have to
                    produce a new one using this method.
                    \throws ShapeMissmatchError if dataset is scalar
                    \return instance of H5Selection bound to this dataset
                    */
                    H5Selection selection() const;

                    //----------------------------------------------------------
                    /*! \brief return dataspace

                    Returns a const. reference to the dataspace of the dataset.
                    \return const reference to the dataspace
                    */
                    const H5Dataspace &space() const{
                        return _space;
                    }

                    //---------------------------------------------------------- 
                    /*! \brief return parent group

                    Method returns the parent group of the dataset. 
                    \return parent group.
                    */
                    H5Group parent() const;

                    //===============reading data methods======================
                    /*! \brief reading simple data from the dataset

                    Read a single data value from the dataset. In order to 
                    succeed the dataset must be a scalar dataset or the total 
                    size of the dataset must be 1.
                    \throws ShapeMissmatchError if dataset is not scalar or the
                    size of the dataset is not 1
                    \throws H5DataSetError in all other error cases
                    \param value variable where to store the data
                    */
                    template<typename T> void read(T &value) const;

                    //---------------------------------------------------------
                    /*! \brief reading data to a buffer

                    Copy data from a dataset to the buffer. The size of the 
                    dataset and the buffer must match. In addition the buffer
                    must be allocated.
                    \throws MemoryAllocationError if the buffer is not 
                    allocated
                    \throws SizeMissmatchError if sizes do not match
                    \throws H5DataSetError in all other cases
                    \param buffer buffer where to store data
                    */
                    template<typename T,template<typename> class BT> 
                        void read(BT<T> &buffer) const;

                    //---------------------------------------------------------
                    /*! \brief read to array

                    Read data from the dataset to an array object of type T with
                    Buffer template BT. 
                    \throws ShapeMissmatchError if dataset and array shape do
                    not match
                    \throws MemoryAllocationError if the array is not allocated
                    \throws H5DataSetError in case of other IO errors
                    \param array array where to store the data from the dataset
                    */
                    template<typename T,template<typename> class BT>
                        void read(Array<T,BT> &array) const;

                    //---------------------------------------------------------
                    /*! \brief read to a scalar object

                    Read data to an instance of Scalar<T>. 
                    \throws ShapeMissmatchError if the dataset is not scalar
                    \throws H5DataSetErrors in case of other IO errors
                    \param data Scalar<T> instance where to store the data
                    */
                    template<typename T> 
                        void read(Scalar<T> &data) const;

                    //---------------------------------------------------------
                    /*! \brief read data to a complex scalar
       
                    Read data to an instance of std::complex<T> where T is
                    a floating point type.
                    \throws ShapeMissmatchError if the dataset is not scalar
                    \throws H5DataSetError in case of general IO errors
                    \param scalar instance of std::complex<T> where to store
                    data
                    */
                    template<typename T>
                        void read(std::complex<T> &scalar) const;

                    //---------------------------------------------------------
                    /*! \brief read binary scalar

                    Read data to a scalar variable of type Binary. This is an 
                    specialized version of read(T &value). It is necessary 
                    because the BinaryType<T> template would be resolved to 
                    a Buffer<T> type.
                    \throws ShapeMissmatchError if the dataset is not scalar\
                    \throws H5DataSetError in case of other IO errors
                    \param b variable of type Binary where to store the data
                    */
                    void read(Binary &b) const;

                    //---------------------------------------------------------
                    /*! \brief read a string scalar

                    Read data to a String variable. This is a specialized
                    version of the template method read(T &value). It is
                    necessary since strings are handled slightly different from
                    other objects.
                    \throws ShapeMissmatchError if the dataset is not scalar
                    \throws H5DataSetError in case of other IO errors
                    \param b String variable where to store the data
                    */
                    void read(String &b) const;

                    //---------------------------------------------------------
                    /*! \brief read to use specified type

                    This Method can be used to read data from the dataset
                    and specify the type to which the data shall be stored as a
                    template parameter. The method tries to configure the newly
                    created instance of this type that fits the needs of the 
                    dataset. If this was successful the data will be read to 
                    this new instance. If instantiation failed for instance 
                    because you try to store array data to a scalar type
                    exceptions will be raised.
                    This method is not yet implemented.
                    */
                    template<typename Object> Object read() const;

                    //===============writing data methods======================
                    /*! \brief write a single value

                    This method writes a single value of a particular type 
                    reading the data from variable value. This method works 
                    only if the dataspace of the dataset is scalar or the total 
                    dataspace size is 1.
                    \throws ShapeMissmatchError if the dataspace is not scalar
                    \throws H5DataSetError in case of other errors
                    \param value variable from which to write data
                    */
                    template<typename T> void write(const T &value) const;

                    //---------------------------------------------------------
                    /*! \brief write a buffer 

                    Write the content of a memory buffer to the dataset. The 
                    dataset must not be scalar. In order to succeed the size of 
                    the buffer must match the size of the dataset.
                    \throws MemoryAccessError if buffer is not allocated
                    \throws SizeMissmatchError sizes do not match
                    \throws H5DataSetError in cases of other errors
                    \param buffer reference to the buffer
                    */
                    template<typename T,template<typename> class BT>
                        void write(const BT<T> &buffer) const;

                    //---------------------------------------------------------
                    /*! \brief write an array

                    Write an array to the dataset. In order to succeed the 
                    shape of the array must match the shape of the dataset. In 
                    addition the dataset must not be scalar.
                    \throws MemoryAccessError if the array buffer is not
                    allocated
                    \throws ShapeMissmatchError if array and dataset shape do 
                    not match
                    \throws H5DataSetError in case of other errors
                    \param array array to write to disk
                    */
                    template<typename T,template<typename> class BT>
                        void write(const Array<T,BT> &array) const;

                    //---------------------------------------------------------
                    /*! \brief write a scalar

                    Write data from an instance of Scalar<T> to the dataset.
                    The dataset must be scalar in order for the method to
                    succeed.
                    \throws ShapeMissmatchError if not a scalar dataset
                    \throws H5DataSetError in case of all other errors
                    \param scalar instance of Scalar<T> from which to write data
                    */
                    template<typename T> 
                        void write(const Scalar<T> &scalar) const;

                    //---------------------------------------------------------
                    /*! \brief write a complex scalar

                    Write data from an instance of std::complex<T> where T
                    is a floating point type.
                    \throws ShapeMissmatchError if dataset is not scalar
                    \throws H5DataSetError in case of all other errors
                    \param scalar instance of std::complex<T> from which to read
                    data
                    */
                    template<typename T> 
                        void write(const std::complex<T> &scalar) const;

                    //---------------------------------------------------------
                    /*! \brief write a binary scalar
                    
                    Write data from a single Binary variable to the dataset.
                    \throws ShapeMissmatchError if dataset is not scalar
                    \throws H5DataSetError in case of all other errors
                    \param b variable of tyep Binary
                    */
                    void write(const Binary &b) const;

                    //---------------------------------------------------------
                    /*! \brief write a String value
                   
                    Write data from a String variable to the dataset.
                    \throws ShapeMissmatchError if the dataset is not scalar
                    \throws H5DataSetError in the case of all other errors
                    \param b String type variable
                    */
                    void write(const String &b) const;

                    //---------------------------------------------------------
                    //! create a new link to this dataset

                    //! This method creates a new link to this dataset.
                    //! With this method only a local link can be established.
                    //! \param path name of the new link to this object
                    void link(const String &path) const;

                    //---------------------------------------------------------
                    //! creates a new link to this dataset

                    //! This creates a new link to this dataset with name n
                    //! below group g. Like link(const String &n) this method 
                    //! can only produce file local links.
                    void link(const H5Group &g,const String &n) const;

            };
            //==========implementation of private IO methods===================
            //write template for a simple pointer
            template<typename T> void H5Dataset::__write(const T *ptr) const
            {
                EXCEPTION_SETUP("template<typename T> void H5Dataset::"
                        "__write(const T *ptr)");

                //select the proper memory data type
                H5Datatype mem_type = H5DatatypeFactory::create_type<T>();

                //write data to disk
                herr_t err = H5Dwrite(id(),mem_type.id(),H5S_ALL,H5S_ALL,
                                      H5P_DEFAULT,(const void *)ptr);
                if(err<0){
                    EXCEPTION_INIT(H5DataSetError,
                            "Error writing data to dataset ["+this->name()+
                            "]!");
                    EXCEPTION_THROW();
                }
            }

            //----------------------------------------------------------------
            //read template for a simple pointer
            template<typename T> void H5Dataset::__read(T *ptr) const
            {
                EXCEPTION_SETUP("template<typename T> void H5Dataset::"
                        "__read(const T *ptr");
               
                //select the proper memory data type
                H5Datatype mem_type = H5DatatypeFactory::create_type<T>();

                //write data to disk
                herr_t err = H5Dread(id(),mem_type.id(),H5S_ALL,H5S_ALL,
                                      H5P_DEFAULT,(void *)ptr);
                if(err<0){
                    EXCEPTION_INIT(H5DataSetError,
                            "Error writing data to dataset ["+this->name()+
                            "]!");
                    EXCEPTION_THROW();
                }
            }

            //=============implementation of writing templates=================
            //implementation of a simpel write template
            template<typename T> void H5Dataset::write(const T &value) const
            {
                __throw_if_not_scalar("template<typename T> void H5Dataset::"
                                      "write(const T &value)");
                __write(&value);
            }


            //-----------------------------------------------------------------
            //implementation of simple read template
            template<typename T> void H5Dataset::read(T &value) const
            {
                __throw_if_not_scalar("template<typename T> void H5Dataset::"
                                      "read(T &value) const");
                __read(&value);
            }

            //-----------------------------------------------------------------
            //implementation of writing data form a buffer
            template<typename T,template<typename> class BT>
                void H5Dataset::write(const BT<T> &buffer) const
            {
                __check_buffer("template<typename T,template<typename> "
                        "class BT> void H5Dataset::write(const BT<T> &buffer)"
                        " const",buffer);
                //write data
                __write(buffer.ptr());
            }
            
            //-----------------------------------------------------------------
            //implementation of reading data to a buffer
            template<typename T,template<typename> class BT>
                void H5Dataset::read(BT<T> &buffer) const
            {
                __check_buffer("template<typename T,template<typename> "
                        "class BT> void H5Dataset::read(BT<T> &buffer) const",
                        buffer);
                __read(buffer.ptr());
            }

            //-----------------------------------------------------------------
            //implementation of writing data from a scalar
            template<typename T>
                void H5Dataset::write(const Scalar<T> &scalar) const
            {
                __throw_if_not_scalar("template<typename T> void H5Dataset::"
                                      "write(const Scalar<T> &scalar) const");
                __write(scalar.ptr());
            }

            //-----------------------------------------------------------------
            //implementation writing complex data
            template<typename T>
                void H5Dataset::write(const std::complex<T> &scalar) const
            {
                __throw_if_not_scalar("template<typename T> void H5Dataset::"
                                      "write(const std::complex<T> &scalar) "
                                      "const");
                __write(&scalar);
            }

            //-----------------------------------------------------------------
            //implementation of reading data to a scalar
            template<typename T> void H5Dataset::read(Scalar<T> &scalar) const
            {
                __throw_if_not_scalar("template<typename T> void H5Dataset::"
                                      "read(Scalar<T> &scalar) const");
                __read(scalar.ptr());
            }

            //-----------------------------------------------------------------
            //read complex scalar
            template<typename T>
                void H5Dataset::read(std::complex<T> &scalar) const
            {
                __throw_if_not_scalar("template<typename T> void H5Dataset::"
                                      "read(std::complex<T> &scalar) const");
                __read(&scalar);
            }

            //-----------------------------------------------------------------
            //implementation of writting data from an array
            template<typename T,template<typename> class BT>
                void H5Dataset::write(const Array<T,BT> &array) const
            {
                __check_array("template<typename T,template<typename> "
                        "class BT> void H5Dataset::write(const Array<T,BT> "
                        "&array)",array);
                __write(array.ptr());
            }

            //-----------------------------------------------------------------
            //implementation of reading data to an array
            template<typename T,template<typename> class BT>
                void H5Dataset::read(Array<T,BT> &array) const
            {
                __check_array("template<typename T,template<typename> class B"
                        "T> void H5Dataset::readArray<T,BT> &array) const",
                        array);
                __read(array.ptr());
            }

        
        //end of namespace
        }
    }
}


#endif
