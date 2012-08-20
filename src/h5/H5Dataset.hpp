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
#include <pni/utils/Slice.hpp>
#include <pni/utils/ArraySelection.hpp>

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

    /*! 
    \ingroup nxh5_classes
    \brief dataset object

    Datasets are the essential data holding objects in HDF5.
    */
    class H5Dataset:public H5AttributeObject
    {
        private:
            H5Dataspace _fspace; //!< file dataspace of the dataset
            H5Dataspace _mspace; //!< memory dataspace

            //---------some private IO templates----------------------
            //! obtain the dataspace from an existing object
            H5Dataspace __obtain_dataspace() const
            {
                return  H5Dataspace(H5Dget_space(id()));
            }

            //--------------------------------------------------------
            //! obtain the datatype from an existing object
            H5Datatype __obtain_datatype() const
            {
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
            void __throw_if_not_scalar(const ExceptionRecord &rec) const;


        public:
            //===================Constructors and destructors==================
            //! default constructor
            explicit H5Dataset();

            //-----------------------------------------------------------------
            //! copy constructor
            H5Dataset(const H5Dataset &o);

            //-----------------------------------------------------------------
            /*! \brief copy conversion constructor
            
            This constructor allows the conversion of a general H5Object to a
            dataset. If the H5Object does not refer to an HDF5 dataset an
            exception will be thrown.
            \throws H5DatasetError if H5Object is not a dataset
            \param o reference to an H5Object
            */
            H5Dataset(const H5Object &o);

            //-----------------------------------------------------------------
            //! move constructor
            H5Dataset(H5Dataset &&o);

            //-----------------------------------------------------------------
            /*! 
            \brief move conversion constructor
            
            Allows move conversion from an HDF5Object to an HDF5 dataset. If the
            object does not refer to a dataset an exception will be thrown.
            \throws H5DatasetError if o does not refer to a dataset
            \param o move reference to an H5Object
            */
            H5Dataset(H5Object &&o);

            //-----------------------------------------------------------------
            /*! 
            \brief constructor - contiguous dataset

            Creates a contiguous array of shape s. The result is most probably
            the simplest form of a dataset. Such a dataset cannot be resized.
            The shape of the dataspace is determined by the argument s which is
            the intial as well as the maximum size of the dataspace.
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

            //-----------------------------------------------------------------
            /*! 
            \brief constructor - chunked dataset
            
            Constructor for a chunked dataset. Unlike contiguous datasets
            chunked datasets can be resized. Its content is subdivided into
            several chunks. Furthermore chunked datasets can be compressed.
            Where the compression algorithm is applied to individual chunks not
            on the entire dataset.
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
            template<template<typename ...> class CTYPE,typename ...OTS>
            explicit H5Dataset(const String &n,
                               const H5Group &g,
                               const H5Datatype &t, 
                               const H5Dataspace &s,
                               const CTYPE<OTS...> &cs)
            {
                
                //create the link creation property list
                hid_t lpl = H5Pcreate(H5P_LINK_CREATE);
                H5Pset_create_intermediate_group(lpl,1);
                
                //create the dataset creation property list
                hid_t cpl = H5Pcreate(H5P_DATASET_CREATE);
                if(cs.size() != 0){
                    H5Pset_layout(cpl,H5D_CHUNKED);
                    DBuffer<hsize_t> cdims(cs.size());
                    std::copy(cs.begin(),cs.end(),cdims.begin());
                    H5Pset_chunk(cpl,cs.size(),cdims.ptr());
                }

                //create the datase
                hid_t did = H5Dcreate2(g.id(),n.c_str(),t.id(),s.id(),
                        lpl,cpl,H5P_DEFAULT);
                if(did<0)
                    throw H5DataSetError(EXCEPTION_RECORD, 
                          "Cannot create dataset ["+n+"] below ["+g.path()+"]!");

                H5Object::id(did);

                //when we create a dataset the file and memory dataspace
                //coincide
                _fspace = __obtain_dataspace();
                _mspace = _fspace;
                //construction done - close property lists
                H5Pclose(lpl);
                H5Pclose(cpl);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief construct - chunked dataset with filter
            
            Constructor for a chunked dataset with a filter. Actually only a
            deflate filter is supported. To use filters a dataset must be a
            chunked dataset. Thus a proper chunk-size must be provided.
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
            template<template<typename ...> class CTYPE,typename ...OTS>
            explicit H5Dataset(const String &n,
                               const H5Group &g,
                               const H5Datatype &t, 
                               const H5Dataspace &s,
                               const CTYPE<OTS...> &cs,
                               const H5Filter &filter)
            {

                //create the link creation property list
                hid_t lpl = H5Pcreate(H5P_LINK_CREATE);
                H5Pset_create_intermediate_group(lpl,1);
                
                //create the dataset creation property list
                hid_t cpl = H5Pcreate(H5P_DATASET_CREATE);
                if(cs.size() != 0)
                {
                    H5Pset_layout(cpl,H5D_CHUNKED);
                    DBuffer<hsize_t> cdims(cs.size());
                    std::copy(cs.begin(),cs.end(),cdims.begin());
                    H5Pset_chunk(cpl,cs.size(),cdims.ptr());
                }

                //setup the filter
                filter.setup(cpl);

                //create the datase
                hid_t did = H5Dcreate2(g.id(),n.c_str(),t.id(),s.id(),
                        lpl,cpl,H5P_DEFAULT);
                if(did<0)
                    throw H5DataSetError(EXCEPTION_RECORD, 
                         "Cannot create dataset ["+n+"] below ["+g.path()+"]!");

                H5Object::id(did);
                //file and memory dataspace are equal after creation
                _fspace = __obtain_dataspace();
                _mspace = _fspace;
                //construction done - close property lists
                H5Pclose(lpl);
                H5Pclose(cpl);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief construct from an object ID
            
            Constructor can use an HDF5 object ID directly to instantiate an
            HDF5 dataset. If the ID does not refer to a dataset an exception
            will  be thrown.
            \throws H5DatasetError if oid does not refer to a dataset
            \param oid HDF5 object id
            */
            explicit H5Dataset(const hid_t &oid);

            //-----------------------------------------------------------------
            //! destructor
            ~H5Dataset();

            //=======================factory methods===========================
            /*! 
            \brief static factory method

            The constructors of H5Dataset use H5Datateyp and H5Dataspace objects
            to describe the datatype and shape of the dataset.  In virtually all
            cases it is more convenient to use a shape object and a native type
            instead. This static template factory method allows the creation of
            a H5Dataset object using the template parameter to determin the
            datatype to use and a shape object to describe the dataspace. The
            dataspaces created using this method are infinitely extensible in
            along all dimensions.
            \throws ShapeMissmatchError if chunk and field shape do not have the
            same rank
            \throws H5DatasetError in case of errors
            \param n name of the dataset
            \param g group below which the dataset will be created
            \param s shape describing the dataset
            \param cs chunk shape
            \return H5Dataset object
            */
            template<typename T,typename SCTYPE,typename CSCTYPE>
            static H5Dataset create(const String &n,const H5Group &g,
                                    const SCTYPE &s,const CSCTYPE &cs)
            {
                //create the datatype
                H5Datatype type = H5DatatypeFactory::create_type<T>();

                if(s.size() != cs.size())
                {
                    std::stringstream estr;
                    estr<<"Chunk shape and field shape must be";
                    estr<<" equal!"<<std::endl;
                    estr<<"Field shape: ";
                    for(auto v: s) estr<<v<<" ";
                    estr<<std::endl;
                    estr<<"Chunk shape: ";
                    for(auto v: cs) estr<<v<<" ";
                    estr<<std::endl;
                    throw ShapeMissmatchError(EXCEPTION_RECORD,estr.str());
                }

                //create the container with the maximum number of elements
                SCTYPE ms(s.size());
                std::fill(ms.begin(),ms.end(),(typename SCTYPE::value_type)H5Dataspace::UNLIMITED);

                //create the dataspace
                H5Dataspace space(s,ms);

                //create the data type
                return H5Dataset(n,g,type,space,cs);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief create multidimensional dataset

            Static factory template method to create a chunked dataset.  The
            method behaves exactly like static H5Dataset create( const String
            &n,const H5Group &g,const Shape &s, const Shape &cs) despite the
            fact that it requires an additional argument describing the filter.
            \throws H5DatasetError in case of errors
            \throws ShapeMissmatchError if chunk and dataset shape do not have
            equal rank
            \param n name of the dataset
            \param g group below which the dataset will be created
            \param s shape describing the dataset
            \param cs chunk shape
            \param filter H5Filter object describing the filter
            \return H5Dataset instance
            */
            template<typename T,typename SCTYPE,typename CSCTYPE>
            static H5Dataset create(const String &n,const H5Group &g,
                                    const SCTYPE &s,const CSCTYPE &cs,
                                    const H5Filter &filter)
            {
                //create the datatype
                H5Datatype type = H5DatatypeFactory::create_type<T>();
                
                if(s.size() != cs.size())
                {
                    std::stringstream estr;
                    estr<<"Chunk shape and field shape must be";
                    estr<<" equal!"<<std::endl;
                    estr<<"Field shape: ";
                    for(auto v: s) estr<<v<<" ";
                    estr<<std::endl;
                    estr<<"Chunk shape: ";
                    for(auto v: cs) estr<<v<<" ";
                    estr<<std::endl;
                    throw ShapeMissmatchError(EXCEPTION_RECORD,estr.str());
                }

                //create the container with the maximum number of elements
                SCTYPE ms(s.size());
                std::fill(ms.begin(),ms.end(),(typename SCTYPE::value_type)H5Dataspace::UNLIMITED);
                //create the dataspace
                H5Dataspace space(s,ms);

                //create the dataset
                return H5Dataset(n,g,type,space,cs,filter);
            }


            //======================assignment operators=======================
            //! copy assignment operator
            H5Dataset &operator=(const H5Dataset &o);

            //-----------------------------------------------------------------
            /*! \brief copy conversion assignment
            
            Allows the assignment conversion from a plain H5Object to a dataset.
            If the object does not refer to a dataset an exception will be
            thrown.
            \throws H5DatasetError if H5Object is not a dataset
            \param o H5Object to convert to H5Datatype
            */
            H5Dataset &operator=(const H5Object &o);

            //-----------------------------------------------------------------
            //! move assignment operator
            H5Dataset &operator=(H5Dataset &&o);

            //-----------------------------------------------------------------
            /*! 
            \brief move conversion assignment

            Allows move conversion assignment from a plain H5Object to a
            H5Dataset object. If H5Object does not refer to a dataset an
            exception will be thrown. 
            \throws H5DatasetError if H5Object is not a dataset
            \param o H5Object to convert to H5Dataset
            */
            H5Dataset &operator=(H5Object &&o);

            //=================methods to modify the dataset===================
            /*! 
            \brief resize the dataset

            Set the shape of the dataset to s. The new shape must satisfy some
            restrictions: 

            \li the rank of s must not exceed the rank of the orignal dataset
            \li the new number of elements of each dimension must not exceed the
            maximum number of elements along each dimension as set in the
            dataspace used to create the dataset.

            If this requirements are not met by s an exception will be
            thrown.
            \throws ShapeMissmatchError if rank of s is not equal to the rank of
            the dataset
            \throws H5DataSetError in case of other errors during resizeing
            \param s shape object describing the new shape of the dataset
            */
            template<typename CTYPE> void resize(const CTYPE &s)
            {
                if(s.size() != _fspace.rank())
                    throw ShapeMissmatchError(EXCEPTION_RECORD,
                          "New shape does not have the same rank!");

                DBuffer<hsize_t> b(s.size());
                std::copy(s.begin(),s.end(),b.begin());

                herr_t err = H5Dset_extent(id(),b.ptr());
                if(err < 0)
                    throw H5DataSetError(EXCEPTION_RECORD, 
                         "Resizing of dataset ["+name()+"] failed!");

                //re-fetch data space
                _fspace = __obtain_dataspace();
            }

            //-----------------------------------------------------------------
            /*! 
            \brief extend the shape along a dimension

            Extends the size of the dataset along a single dimension.  This
            command can be quite useful for writing data sequentially. 
            \throws IndexError if e exceeds the rank of the dataset
            \throws H5DataSetError in case of other errors
            \param e index of the extend dimension
            \param n number of elements by which the dimension shall be
            extended
            */
            void grow(const size_t &e=0,const size_t &n=1);

            //-----------------------------------------------------------------
            /*! 
            \brief total number of elements

            Returns the total number of elements stored in the dataset.
            \return total number of elements
            */
            size_t size() const { return _fspace.size(); }

            //-----------------------------------------------------------------
            /*! 
            \brief shape of dataset

            Returns a copy of the datasets shape. 
            \return dataset shape
            */
            template<typename CTYPE> CTYPE shape() const
            {
                return _fspace.shape<CTYPE>();
            }

            //-----------------------------------------------------------------
            /*!
            \brief rank of the dataset

            Returns the number of dimensions of the dataset.
            \return number of dimensions
            */
            size_t rank() const { return _fspace.rank(); }

            //-----------------------------------------------------------------
            /*! 
            \brief number of elements

            Returns the number of elements along dimension i. 
            \throws IndexError if i exceeds dataset rank
            \param i index of the dimension
            \return number of elements along i
            */
            size_t dim(const size_t &i) const { return _fspace.dim(i); }

            //-----------------------------------------------------------------
            /*! 
            \brief datatype ID

            Datatype ID of the dataset. 
            \return type id of the datatype of the dataset
            */
            TypeID type_id() const { return __obtain_datatype().type_id(); }

            //----------------------------------------------------------------
            /*! 
            \brief return a selection 

            Returns a selection offset for the dataset. The selection created by
            this method initially spans the entire dataset.  Restrictions to the
            selection must be made later by the user. Selections can be only
            made on multidimensional datasets. If the dataspace which was used
            to create the dataset was scalar an exception will be thrown.  It is
            important to note that a selection object is always bound to the
            dataset it belongs to. You cannot reconnect a selection to a new
            dataset. Instead you always have to produce a new one using this
            method.
            \throws ShapeMissmatchError if dataset is scalar
            \return instance of H5Selection bound to this dataset
            */
            H5Selection selection() const;

            //-----------------------------------------------------------------
            //! apply a selection
            template<typename CTYPE> void apply_selection(const CTYPE &s) 
            {
                std::vector<Slice> sel(s.size());
                std::copy(s.begin(),s.end(),sel.begin());

                //create an array selection
                ArraySelection asel = ArraySelection::create(sel);

                //create buffers
                auto offset = asel.offset<DBuffer<hsize_t> >();
                auto stride = asel.stride<DBuffer<hsize_t> >();
                auto count = asel.full_shape<DBuffer<hsize_t> >();

                //apply the selection
                herr_t err = H5Sselect_hyperslab(_fspace.id(),
                        H5S_SELECT_SET,offset.ptr(),stride.ptr(),count.ptr(),
                        NULL);
                if(err<0)
                    throw H5DataSetError(EXCEPTION_RECORD,
                            "Error applying selection to dataset!");

                //need to set the memory dataspace to the effective shape of the
                //selection
                _mspace = H5Dataspace(asel.shape());

            }

            //----------------------------------------------------------------
            //! remove a selection
            void clear_selections() const
            {
                H5Sselect_all(_fspace.id());
            }

            //-----------------------------------------------------------------
            /*! 
            \brief return dataspace

            Returns a const. reference to the dataspace of the dataset.
            \return const reference to the dataspace
            */
            const H5Dataspace &space() const
            {
                return _fspace;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief return parent group

            Method returns the parent group of the dataset. 
            \return parent group.
            */
            H5Group parent() const;


            //===================reading data methods==========================
            /*! 
            \brief reading simple data from the dataset

            Read a single data value from the dataset. In order to succeed the
            dataset must be a scalar dataset or the total size of the dataset
            must be 1.
            \throws ShapeMissmatchError if dataset is not scalar or the size of
            the dataset is not 1
            \throws H5DataSetError in all other error cases
            \param value variable where to store the data
            */
            template<typename T> void read(T *ptr) const
            {
                //select the proper memory data type
                H5Datatype mem_type = H5DatatypeFactory::create_type<T>();

                //write data to disk
                herr_t err = H5Dread(id(),mem_type.id(),_mspace.id(),_fspace.id(),
                                      H5P_DEFAULT,(void *)ptr);
                if(err<0)
                    throw H5DataSetError(EXCEPTION_RECORD, 
                          "Error writing data to dataset ["+this->name()+"]!");
            }

            //-----------------------------------------------------------------
            /*! 
            \brief read a string scalar

            Read data to a String variable. This is a specialized version of the
            template method read(T &value). It is necessary since strings are
            handled slightly different from other objects.
            \throws ShapeMissmatchError if the dataset is not scalar
            \throws H5DataSetError in case of other IO errors
            \param b String variable where to store the data
            */
            void read(String *sptr) const;

            //===============writing data methods==============================
            /*! 
            \brief write a single value

            This method writes a single value of a particular type reading the
            data from variable value. This method works only if the dataspace of
            the dataset is scalar or the total dataspace size is 1.
            \throws ShapeMissmatchError if the dataspace is not scalar
            \throws H5DataSetError in case of other errors
            \param value variable from which to write data
            */
            template<typename T> void write(const T *ptr) const
            {
                //select the proper memory data type
                H5Datatype mem_type = H5DatatypeFactory::create_type<T>();

                //write data to disk
                herr_t err = H5Dwrite(id(),mem_type.id(),_mspace.id(),_fspace.id(),
                                      H5P_DEFAULT,(const void *)ptr);
                if(err<0)
                    throw H5DataSetError(EXCEPTION_RECORD, 
                        "Error writing data to dataset ["+this->name()+"]!");
            }

            //-----------------------------------------------------------------
            /*! 
            \brief write a String value
           
            Write data from a String variable to the dataset.
            \throws ShapeMissmatchError if the dataset is not scalar
            \throws H5DataSetError in the case of all other errors
            \param b String type variable
            */
            void write(const String *sptr) const;

            //-----------------------------------------------------------------
            /*! create a new link to this dataset

            This method creates a new link to this dataset.  With this method
            only a local link can be established.
            \param path name of the new link to this object
            */
            void link(const String &path) const;

            //-----------------------------------------------------------------
            /*! 
            \brief creates a new link to this dataset

            This creates a new link to this dataset with name n below group g.
            Like link(const String &n) this method can only produce file local
            links.
            */
            void link(const H5Group &g,const String &n) const;

    };


//end of namespace
}
}
}


#endif
