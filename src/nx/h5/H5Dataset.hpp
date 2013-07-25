/*
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
 * Definition of an HDF5 dataset class
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#pragma once

#include <sstream>
#include <pni/core/types.hpp>
#include <pni/core/slice.hpp>
#include <pni/core/array_selection.hpp>


#include "H5AttributeObject.hpp"
#include "H5Datatype.hpp"
#include "H5Dataspace.hpp"
#include "H5Group.hpp"
#include "H5ObjectType.hpp"
#include "H5Filter.hpp"
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

    /*! 
    \ingroup nxh5_classes
    \brief dataset object

    Datasets are the essential data holding objects in HDF5.
    */
    class H5Dataset:public H5AttributeObject
    {
        private:
            H5Dataspace _fspace; //!< file dataspace of the dataset
            mutable H5Dataspace _mspace; //!< memory dataspace

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
            \throws shape_mismatch_error if dataset is not scalar
            \param rec exception record
            */
            void __throw_if_not_scalar(const exception_record &rec) const;


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
            \throws pni::io::nx::nxfield_error if H5Object is not a dataset
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
            \throws pni::io::nx::nxfield_error if o does not refer to a dataset
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
            \throws pni::io::nx::nxfield_error in case of all kinds of errors
            \param n name of the dataset
            \param g parent group
            \param t id of the data type
            \param s shape of the dataset
            */
            explicit H5Dataset(const string &n, 
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
            \throws pni::io::nx::nxfield_error in case of errors 
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
            explicit H5Dataset(const string &n,
                               const H5Group &g,
                               const H5Datatype &t, 
                               const H5Dataspace &s,
                               const CTYPE<OTS...> &cs)
            {
                
                //create the link creation property list
                hid_t lpl = H5Pcreate(H5P_LINK_CREATE);
                if(lpl == -1)
                    throw pni::io::nx::nxfield_error(EXCEPTION_RECORD,
                            "Error creating link property list for dataset ["+
                            n+"] below ["+g.path()+"]!\n\n"+
                            get_h5_error_string());


                if(H5Pset_create_intermediate_group(lpl,1)<0)
                    throw pni::io::nx::nxfield_error(EXCEPTION_RECORD,
                            "Error setting intermediate group property for "
                            "dataset ["+n+"] below ["+g.path()+"]!\n\n"+
                            get_h5_error_string());
                
                //create the dataset creation property list
                hid_t cpl = H5Pcreate(H5P_DATASET_CREATE);
                if(cpl == -1)
                    throw pni::io::nx::nxfield_error(EXCEPTION_RECORD,
                            "Error creating dataset create property list for ["+
                            n+"] below ["+g.path()+"]!\n\n"+
                            get_h5_error_string());

                if(cs.size() != 0)
                {
                    if(H5Pset_layout(cpl,H5D_CHUNKED)<0)
                        throw pni::io::nx::nxfile_error(EXCEPTION_RECORD,
                        "Error setting dataset layout for ["+n+"] below "
                        "["+g.path()+"] to chunked!\n\n"+
                        get_h5_error_string());

                    dbuffer<hsize_t> cdims(cs.size());
                    std::copy(cs.begin(),cs.end(),cdims.begin());
                    if(H5Pset_chunk(cpl,cs.size(),cdims.ptr())<0)
                        throw pni::io::nx::nxfile_error(EXCEPTION_RECORD,
                        "Error setting chunk size for ["+n+"] below "
                        "["+g.path()+"]!\n\n"+ get_h5_error_string());
                }

                //create the datase
                hid_t did = H5Dcreate2(g.id(),n.c_str(),t.id(),s.id(),
                        lpl,cpl,H5P_DEFAULT);
                if(did<0)
                {
                    //close property lists before throw exceptions
                    H5Pclose(lpl);
                    H5Pclose(cpl);
                    throw pni::io::nx::nxfield_error(EXCEPTION_RECORD, 
                          "Cannot create dataset ["+n+"] below ["+g.path()+
                          "]!\n\n"+ get_h5_error_string());
                };

                
                *this = H5Dataset(did);
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
            \throws pni::io::nx::nxfield_error in case of errors
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
            explicit H5Dataset(const string &n,
                               const H5Group &g,
                               const H5Datatype &t, 
                               const H5Dataspace &s,
                               const CTYPE<OTS...> &cs,
                               const H5Filter &filter)
            {

                //create the link creation property list
                hid_t lpl = H5Pcreate(H5P_LINK_CREATE);
                if(lpl == -1)
                    throw pni::io::nx::nxfield_error(EXCEPTION_RECORD,
                            "Error creating link property list for dataset ["+
                            n+"] below ["+g.path()+"]!\n\n"+
                            get_h5_error_string());

                if(H5Pset_create_intermediate_group(lpl,1)<0)
                    throw pni::io::nx::nxfield_error(EXCEPTION_RECORD,
                            "Error setting intermediate group property for "
                            "dataset ["+n+"] below ["+g.path()+"]!\n\n"+
                            get_h5_error_string());
                
                //create the dataset creation property list
                hid_t cpl = H5Pcreate(H5P_DATASET_CREATE);
                if(cpl == -1)
                    throw pni::io::nx::nxfield_error(EXCEPTION_RECORD,
                            "Error creating dataset create property list for ["+
                            n+"] below ["+g.path()+"]!\n\n"+
                            get_h5_error_string());

                if(cs.size() != 0)
                {
                    if(H5Pset_layout(cpl,H5D_CHUNKED)<0)
                        throw pni::io::nx::nxfile_error(EXCEPTION_RECORD,
                        "Error setting dataset layout for ["+n+"] below "
                        "["+g.path()+"] to chunked!\n\n"+
                        get_h5_error_string());

                    dbuffer<hsize_t> cdims(cs.size());
                    std::copy(cs.begin(),cs.end(),cdims.begin());
                    if(H5Pset_chunk(cpl,cs.size(),cdims.ptr())<0)
                        throw pni::io::nx::nxfile_error(EXCEPTION_RECORD,
                        "Error setting chunk size for ["+n+"] below "
                        "["+g.path()+"]!\n\n"+ get_h5_error_string());

                }

                //setup the filter
                filter.setup(cpl);

                //create the datase
                hid_t did = H5Dcreate2(g.id(),n.c_str(),t.id(),s.id(),
                        lpl,cpl,H5P_DEFAULT);
                if(did<0)
                {
                    //close property lists before throw exceptions
                    H5Pclose(lpl);
                    H5Pclose(cpl);
                    throw pni::io::nx::nxfield_error(EXCEPTION_RECORD, 
                         "Cannot create dataset ["+n+"] below ["+g.path()+"]!"+
                         get_h5_error_string());
                }

                *this = H5Dataset(did);
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
            \throws pni::io::nx::nxfield_error if oid does not refer to a dataset
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
            \throws shape_mismatch_error if chunk and field shape do not have the
            same rank
            \throws pni::io::nx::nxfield_error in case of errors
            \param n name of the dataset
            \param g group below which the dataset will be created
            \param s shape describing the dataset
            \param cs chunk shape
            \return H5Dataset object
            */
            template<typename T,typename SCTYPE,typename CSCTYPE>
            static H5Dataset create(const string &n,const H5Group &g,
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
#ifdef NOFOREACH
                    for(auto iter = s.begin();iter!=s.end();++iter)
                    {
                        auto v = *iter;
#else
                    for(auto v: s)
                    {
#endif 
                        estr<<v<<" ";
                    }
                    estr<<std::endl;
                    estr<<"Chunk shape: ";
#ifdef NOFOREACH
                    for(auto iter = cs.begin();iter!=cs.end();++iter)
                    {
                        auto v = *iter;
#else
                    for(auto v: cs) 
                    {
#endif
                        estr<<v<<" ";
                    }
                    estr<<std::endl;
                    throw shape_mismatch_error(EXCEPTION_RECORD,estr.str());
                }

                //create the container with the maximum number of elements
                dbuffer<hsize_t> ms(s.size());                 
                std::fill(ms.begin(),ms.end(),H5S_UNLIMITED);
                /*
                SCTYPE ms(s.size());
                std::fill(ms.begin(),ms.end(),(typename SCTYPE::value_type)H5Dataspace::UNLIMITED);
                */

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
            \throws pni::io::nx::nxfield_error in case of errors
            \throws shape_mismatch_error if chunk and dataset shape do not have
            equal rank
            \param n name of the dataset
            \param g group below which the dataset will be created
            \param s shape describing the dataset
            \param cs chunk shape
            \param filter H5Filter object describing the filter
            \return H5Dataset instance
            */
            template<typename T,typename SCTYPE,typename CSCTYPE>
            static H5Dataset create(const string &n,const H5Group &g,
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
#ifdef NOFOREACH
                    for(auto iter = s.begin();iter!=s.end();++iter)
                    {
                        auto v = *iter;
#else
                    for(auto v: s) 
                    {
#endif
                        estr<<v<<" ";
                    }
                    estr<<std::endl;
                    estr<<"Chunk shape: ";
#ifdef NOFOREACH
                    for(auto iter = cs.begin();iter!=cs.end();++iter)
                    {
                        auto v = *iter;
#else
                    for(auto v: cs) 
                    {
#endif
                        estr<<v<<" ";
                    }
                    estr<<std::endl;
                    throw shape_mismatch_error(EXCEPTION_RECORD,estr.str());
                }

                //create the container with the maximum number of elements
                dbuffer<hsize_t> ms(s.size());
                std::fill(ms.begin(),ms.end(),H5S_UNLIMITED);
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
            \throws pni::io::nx::nxfield_error if H5Object is not a dataset
            \param o H5Object to convert to H5Datatype
            \return instance of H5Dataset
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
            \throws pni::io::nx::nxfield_error if H5Object is not a dataset
            \param o H5Object to convert to H5Dataset
            \return instance of H5Dataset
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
            \throws shape_mismatch_error if rank of s is not equal to the rank of
            the dataset
            \throws pni::io::nx::nxfield_error in case of other errors during resizeing
            \param s shape object describing the new shape of the dataset
            */
            template<typename CTYPE> void resize(const CTYPE &s)
            {
                if(s.size() != _fspace.rank())
                    throw shape_mismatch_error(EXCEPTION_RECORD,
                          "New shape does not have the same rank!");

                dbuffer<hsize_t> b(s.size());
                std::copy(s.begin(),s.end(),b.begin());

                herr_t err = H5Dset_extent(id(),b.ptr());
                if(err < 0)
                    throw pni::io::nx::nxfield_error(EXCEPTION_RECORD, 
                         "Resizing of dataset ["+name()+"] failed!\n\n"+
                         get_h5_error_string());

                //re-fetch data space
                _fspace = __obtain_dataspace();
                _mspace = _fspace;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief extend the shape along a dimension

            Extends the size of the dataset along a single dimension.  This
            command can be quite useful for writing data sequentially. 
            \throws index_error if e exceeds the rank of the dataset
            \throws pni::io::nx::nxfield_error in case of other errors
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
            size_t size() const { return _mspace.size(); }

            //-----------------------------------------------------------------
            /*! 
            \brief shape of dataset

            Returns a copy of the datasets shape. 
            \return dataset shape
            */
            template<typename CTYPE> CTYPE shape() const
            {
                return _mspace.shape<CTYPE>();
            }

            //-----------------------------------------------------------------
            /*!
            \brief rank of the dataset

            Returns the number of dimensions of the dataset.
            \return number of dimensions
            */
            size_t rank() const { return _mspace.rank(); }

            //-----------------------------------------------------------------
            /*! 
            \brief number of elements

            Returns the number of elements along dimension i. 
            \throws index_error if i exceeds dataset rank
            \param i index of the dimension
            \return number of elements along i
            */
            size_t dim(const size_t &i) const { return _mspace.dim(i); }

            //-----------------------------------------------------------------
            /*! 
            \brief datatype ID

            Datatype ID of the dataset. 
            \return type id of the datatype of the dataset
            */
            type_id_t type_id() const { return __obtain_datatype().type_id(); }


            //-----------------------------------------------------------------
            //! apply a selection
            template<typename CTYPE> void apply_selection(const CTYPE &s) 
            {
                std::vector<slice> sel(s.size());
                std::copy(s.begin(),s.end(),sel.begin());

                //create an array selection
                array_selection asel = array_selection::create(sel);

                //create buffers
                auto offset = asel.offset<dbuffer<hsize_t> >();
                auto stride = asel.stride<dbuffer<hsize_t> >();
                auto count = asel.full_shape<dbuffer<hsize_t> >();

                //apply the selection
                herr_t err = H5Sselect_hyperslab(_fspace.id(),
                        H5S_SELECT_SET,offset.ptr(),stride.ptr(),count.ptr(),
                        nullptr);
                if(err<0)
                    throw pni::io::nx::nxfield_error(EXCEPTION_RECORD,
                            "Error applying selection to dataset!\n\n"+
                            get_h5_error_string());

                //need to set the memory dataspace to the effective shape of the
                //selection
                _mspace = H5Dataspace(asel.shape());

            }

            //----------------------------------------------------------------
            //! remove a selection
            void clear_selections() const
            {
                //this should be quite easy - there is nothing special we have
                ///to do.
                if(_fspace.is_valid())
                {
                    H5Sselect_all(_fspace.id());
                    _mspace = _fspace;
                }
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
            \throws shape_mismatch_error if dataset is not scalar or the size of
            the dataset is not 1
            \throws pni::io::nx::nxfield_error in all other error cases
            \param ptr pointer to memory where the data should be stored.
            */
            template<typename T> void read(T *ptr) const
            {
                //select the proper memory data type
                const H5Datatype &mem_type = H5TFactory.get_type<T>();

                //write data to disk
                herr_t err = H5Dread(id(),mem_type.id(),_mspace.id(),_fspace.id(),
                                      H5P_DEFAULT,(void *)ptr);
                if(err<0)
                {
                    std::stringstream ss;
                    ss<<"Error writing data to dataset ["+this->name()+"]!";
                    ss<<std::endl<<"HDF5 error report:"<<std::endl;
                    throw pni::io::nx::nxfield_error(EXCEPTION_RECORD, 
                          ss.str()+get_h5_error_string());
                }
            }

            //-----------------------------------------------------------------
            /*! 
            \brief read a string scalar

            Read data to a String variable. This is a specialized version of the
            template method read(T &value). It is necessary since strings are
            handled slightly different from other objects.
            \throws shape_mismatch_error if the dataset is not scalar
            \throws pni::io::nx::nxfield_error in case of other IO errors
            \param sptr pointer to String objects
            */
            void read(string *sptr) const;

            //===============writing data methods==============================
            /*! 
            \brief write a single value

            This method writes a single value of a particular type reading the
            data from variable value. This method works only if the dataspace of
            the dataset is scalar or the total dataspace size is 1.
            \throws shape_mismatch_error if the dataspace is not scalar
            \throws pni::io::nx::nxfield_error in case of other errors
            \param ptr pointer to the memory region from which to read
            */
            template<typename T> void write(const T *ptr) const
            {
                //select the proper memory data type
                const H5Datatype &mem_type = H5TFactory.get_type<T>();

                //write data to disk
                herr_t err = H5Dwrite(id(),mem_type.id(),_mspace.id(),_fspace.id(),
                                      H5P_DEFAULT,(const void *)ptr);
                if(err<0)
                    throw pni::io::nx::nxfield_error(EXCEPTION_RECORD, 
                        "Error writing data to dataset ["+this->name()+"]!\n\n"+
                        get_h5_error_string());
            }

            //-----------------------------------------------------------------
            /*! 
            \brief write a String value
           
            Write data from a String variable to the dataset.
            \throws shape_mismatch_error if the dataset is not scalar
            \throws pni::io::nx::nxfield_error in the case of all other errors
            \param sptr pointer to String objects.
            */
            void write(const string *sptr) const;


            //-----------------------------------------------------------------
            /*!
            \brief close the dataset

            Method closing the dataset.
            */
            virtual void close();

    };


//end of namespace
}
}
}
}
