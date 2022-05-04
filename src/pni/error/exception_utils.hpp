//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with lipniutils.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
// Created on: May 23, 2012
//     Author: Eugen Wintersberger
//
//
#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <boost/units/detail/utility.hpp>

#include <pni/error/exceptions.hpp>
#include <pni/utilities/service.hpp>
#include <pni/types.hpp>

#include <pni/windows.hpp>

namespace pni{

    //!
    //! \ingroup error_classes
    //! \brief print vector content
    //!
    //! Print the content of an interable as a vector. The output is  
    //! embraced by () and each element is separated by a comma.  
    //! 
    //! \tparam VectorT container type
    //! \param o output stream 
    //! \param v iterable instance
    //!
    template<typename VectorT>
    void print_vector(std::ostream &o,const VectorT &v)
    {
        o<<"( ";
        for(auto x: v) o<<x<<" ";
        o<<")";
    }

    //=====================Exception related helper functions==================
    //!
    //! \ingroup error_classes
    //! \brief check if two container have equal size
    //! 
    //! This helper function checks if two container instances have equal size
    //! and returns true if this is the case. Otherwise false will be returned.
    //! Both container types have to provide a size() method returning the 
    //! number of elements the container can hold. 
    //! 
    //! \tparam ContainerAT first container type
    //! \tparam ContainerBT second container type
    //! \param a reference to an instance of ContainerAT
    //! \param b reference to an instance of ContainerBT
    //! \return true if a and b have same size, false otherwise
    //! 
    template<
             typename ContainerAT,
             typename ContainerBT
            >
    bool check_equal_size(const ContainerAT &a,const ContainerBT &b) 
    {
        return a.size() == b.size();
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup error_classes
    //! \brief check if two objects have different size
    //! 
    //! This utilty function can be used to check for the equality of the size 
    //! of two objects. It is typically used to compare the size of a shape 
    //! and a buffer or any other container object. 
    //! If the sizes do not match an exception is thrown.
    //! 
    //! \throws size_mismatch_error if sizes do not match
    //! \tparam ContainerAT first container type
    //! \tparam ContainerBT second container type
    //! \param a instance of container type ContainerAT
    //! \param b instance of container type ContainerBT
    //! \param i exception_record for the location where to perform the check
    //! performed
    //!
    template<
             typename ContainerAT,
             typename ContainerBT
            > 
    void check_equal_size(const ContainerAT &a,const ContainerBT &b,const exception_record &i)
    {
        if(!check_equal_size(a,b))
        {
            std::stringstream ss;
            ss<<"Size of "<<boost::units::detail::demangle(typeid(ContainerAT).name())<<" (";
            ss<<a.size()<<") ";
            ss<<"does not match size of "<<boost::units::detail::demangle(typeid(ContainerBT).name())<<" (";
            ss<<b.size()<<")!";
            throw size_mismatch_error(i,string(ss.str()));
        }
    }

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup error_classes
    //! \brief check index in dim
    //!
    //! Check if an index resides within a dimension range. The index must be
    //! than the size of the dimension. If the index is within the dimension 
    //! size true is returned. false otherwise.
    //! 
    //! \param index the index to check
    //! \param dimsize size of the dimension
    //! \return true if index<dimsize, flase otherwise
    //! 
    bool PNINEXUS_EXPORT check_index_in_dim(size_t index,size_t dimsize);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup error_classes
    //! \brief check index in dim
    //!
    //! Throwing version of check_index_in_dim. Throws an index_error 
    //! exception if the index is not within the dimension range.
    //! 
    //! \throws index_error if i exceeds dimsize
    //! \param index actual index
    //! \param dimsize dimension size
    //! \param i exception_record for the location where to perform the check
    //! performed
    //!
    void PNINEXUS_EXPORT check_index_in_dim(size_t index,size_t dimsize,
                                           const exception_record &i);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup error_classes
    //! \brief check indexes
    //! 
    //! Check if all index values stored in a container do not exceed their
    //! dimensions limits. 
    //!
    //! \tparam IndexT index container type
    //! \tparam ShapeT shape container type
    //! \param index reference to an index container
    //! \param shape reference to a shape container
    //! \return true if all indexes are in their bounds
    //!
    template<
             typename IndexT,
             typename ShapeT
            >
    bool check_indexes(const IndexT &index,const ShapeT &shape)
    {
        if(!check_equal_size(index,shape)) return false;

        auto iiter = index.begin();
        auto siter = shape.begin();

        for(;iiter!=index.end();++iiter,++siter)
            if(*iiter>=*siter) return false;

        return true;
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup error_classes
    //! \brief check indexes
    //!
    //! Checks if all indexes stored in a container lie within a given range
    //! determined by the shape. In addition the function checks if the number 
    //! of indexes matches the number of elements in the shape. 
    //!
    //! \throws index_error if one of the indexes exceeds the number of 
    //! elements in its dimension
    //! \throws shape_mismatch_error if the number of indexes does not match 
    //! the number of dimensions (elements in the shape)
    //! \tparam IndexT index container type
    //! \tparam ShapeT shape container type
    //! \param index container with index data
    //! \param shape container with shape data
    //! \param record the exception record of the calling function
    //!
    template<
             typename IndexT,
             typename ShapeT
            >
    void check_indexes(const IndexT &index,const ShapeT &shape,
                       const exception_record &record)
    {
        //check size - if it does not match throw an exception
        if(!check_equal_size(index,shape))
        {
            std::stringstream ss;
            ss<<"Rank of index vector ("<<index.size()<<") does not match ";
            ss<<"the rank of the shape vector ("<<shape.size()<<")!";
            throw shape_mismatch_error(record,ss.str());
        }
       
        //if sizes of the vectors match check the individual ranges. 
        if(!check_indexes(index,shape))
        {
            std::stringstream ss;
            ss<<"Indexes ";
            print_vector(ss,index);
            ss<<" do not match shape ";
            print_vector(ss,shape);
            ss<<std::endl;

            throw index_error(record,ss.str());
        }

    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup error_classes
    //! \brief check equal rank
    //! 
    //! Return true of the two array like objects have an equal number of 
    //! dimensions. In any other case return false.
    //! 
    //! \tparam ContainerAT first array type
    //! \tparam ContainerBT second array type
    //! \param a reference to an instance of ContainerAT
    //! \param b reference to an instance of ContainerBT
    //! \return true if a and b have equal rank, false otherwise
    //! 
    template<
             typename ContainerAT,
             typename ContainerBT
            >
    bool check_equal_rank(const ContainerAT &a,const ContainerBT &b)
    {
        return a.rank() == b.rank();
    }

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup error_classes
    //! \brief check equal rank 
    //! 
    //! Throwing version of check_equal_rank. 
    //!
    //! \throws shape_mismatch_error if a and b have different rank
    //! \tparam ContainerAT first array type
    //! \tparam ContainerBT second array type
    //! \param a reference to an instance of ContainerAT
    //! \param b reference to an instance of ContainerBT
    //! \param i exception record of the calling function
    //!
    template<
             typename ContainerAT,
             typename ContainerBT
            >
    void check_equal_rank(const ContainerAT &a,const ContainerBT &b,const exception_record &i)
    {
        if(!check_equal_rank(a,b))
        {
            std::stringstream ss;
            ss<<"Rank of "<<boost::units::detail::demangle(typeid(a).name())<<" (";
            ss<<a.rank()<<") does not match that of ";
            ss<<boost::units::detail::demangle(typeid(b).name())<<" (";
            ss<<b.rank()<<")!";
            throw shape_mismatch_error(i,ss.str());
        }
    }

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup error_classes
    //! \brief check for shape equality 
    //! 
    //! 
    template<
             typename ContainerAT,
             typename ContainerBT
            >
    bool check_equal_shape(const ContainerAT &a,const ContainerBT &b)
    {
        //check if the sizes match
        if(!check_equal_size(a,b)) return false;
        if(!check_equal_rank(a,b)) return false;

        auto sa = a.template shape<std::vector<size_t> >();
        auto sb = b.template shape<std::vector<size_t> >();
        
        if(!std::equal(sa.begin(),sa.end(),sb.begin()))
            return false;

        return true;
    }


    //-------------------------------------------------------------------------
    //!
    //! \ingroup error_classes
    //! \brief check shape equality
    //! 
    //! Checks if two Shape objects are equal and throws an exception if they 
    //! are not.
    //! 
    //! \tparam ContainerAT container type for the first shape
    //! \tparam ContainerBT container type for the second shape
    //! \throws size_mismatch_error if array sizes do not match
    //! \throws shape_mismatch_error if shapes do not match
    //! \param a first shape
    //! \param b second shape
    //! \param i exception_record for the location where to perform the check
    //!
    template<typename ContainerAT,typename ContainerBT>
    void check_equal_shape(const ContainerAT &a,const ContainerBT &b,const exception_record &i)
    {
        check_equal_size(a,b,i);
        check_equal_rank(a,b,i);

        if(!check_equal_shape(a,b))
        {
            std::stringstream ss;
            ss<<"Shape of "<<boost::units::detail::demangle(typeid(a).name())<<" (";
            ss<<a.size()<<") does not match that of ";
            ss<<boost::units::detail::demangle(typeid(b).name())<<" (";
            ss<<b.size()<<")!";
            throw shape_mismatch_error(i,ss.str());
        }

    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief check allocation state

    Checks the allocation state of an allocateable object. If the object is not
    allocated an exception will be thrown.
    \throws memory_not_allocated_error if object not allocated
    \param o object to check
    \param i exception_record for the location where to perform the check
    */
    template<typename ObjectT> 
    void check_allocation_state(const ObjectT &o,const exception_record &i)
    {
        if(!o.size())
        {
            std::stringstream ss;
            ss<<"Instance of "<<boost::units::detail::demangle(typeid(ObjectT).name());
            ss<<" not allocated!";
            throw memory_not_allocated_error(i,ss.str());
        }
    }

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup error_classes
    //! \brief check pointer state
    //!
    //! Checks if a pointer is nullptr or not and throws an exception if it is.
    //! \throws memory_not_allocated_error if pointer is a nullptr
    //! \param ptr pointer to check
    //! \param i exception_record for the location where to perform the check
    //!
    template<typename GeneralT> 
    void check_ptr_state(const GeneralT *ptr,const exception_record &i)
    {
        if(!ptr)
        {
            std::stringstream ss;
            ss<<"Pointer is nullptr!";
            throw memory_not_allocated_error(i,ss.str());
        }
    }



//end of namespace
}
