//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
// Created on: Jan 11, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include<iostream>
#include<memory>

#include <pni/error/exceptions.hpp>
#include <pni/error/exception_utils.hpp>
#include <pni/types/types.hpp>
#include <pni/type_erasures/array_holder.hpp>
#include <pni/type_erasures/array_iterator.hpp>
#include <pni/windows.hpp>


namespace pni{
namespace core{

    //!
    //! \ingroup type_erasure_classes
    //! \brief type erasure array types
    //!
    //! This type erasure can hold all kind of array types provides by 
    //! libpnicore.  It takes entire ownership over the array it holds.
    //! The construction is fairly easy
    /*!
    \code 
    array a = array_type::create({104,200});
    \endcode
    !*/
    //! as the array_type instance is a temporary move construction will 
    //! be used. 
    //! 
    //! Alternatively, copy construction can be done with
    /*!
    \code
    auto data = array_type::create({104,200});
    array a = data;
    \endcode
    !*/
    //! in which case the copy constructor is used to copy the array's data. 
    //! It is clear that in this latter case the two objects are entirely 
    //! decoupled.  Changing a value in a will not influence the original 
    //! instance data. 
    //!
    //! Like any other array in libpnicore an instance of array can be 
    //! considered as a one dimensional container providing linear access to 
    //! the data stored in it by means of iterators, the [] operator, and the 
    //! at() method. Like standard C++ container only the latter method 
    //! ensures index checking.  See code examples at the various member 
    //! functions for more detail about the methods.
    //!
    class PNIIO_EXPORT array //the type erasure
    {
        private:
            //! local pointer type used to hold the array
            typedef std::unique_ptr<array_holder_interface> pointer_type;
            
            //----------------------------------------------------------------
            //!
            //! \brief throw exception
            //!
            //! Static helper method that throws a MemoryNotAllcatedError if 
            //! the type erasure holds no data and data access is requested 
            //! by the user.
            //! 
            //! \throw MemoryNotAllocatedError
            //! \param r exception record where the error occured.
            //!
            static void _throw_not_allocated_error(const exception_record &r)
            {
                throw memory_not_allocated_error(r,
                        "Instance of data_object holds no data!");
            }

            //----------------------------------------------------------------
            //!
            //! \brief check pointer
            //! 
            //! Check the internal pointer for validity. If the pointer is not
            //! valid an exception is thrown. 
            //! 
            //! \throws memory_not_allocated if pointer is not valid
            //! \param ptr the pointer to check
            //! \param r the exception record
            //! 
            static void _check_pointer(const pointer_type &ptr,
                                  const exception_record &r)
            {
                if(!ptr)
                    _throw_not_allocated_error(r);
            }

            //! pointer to an instance of array_holder
#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif
            pointer_type _ptr; 
#ifdef _MSC_VER
#pragma warning(default:4251)
#endif
        public:
            //====================public types=================================
            typedef value value_type; //!< value type of the array
            typedef array_iterator<0> iterator; //!< read/write iterator
            typedef array_iterator<1> const_iterator; //!< read only iterator
            //! element index type
            typedef array_holder_interface::element_index element_index;
            //! view index type
            typedef array_holder_interface::view_index view_index;
            typedef size_t size_type; //!< type used for array size
            //===================constructors and destructor===================
            //! default constructor
            array():_ptr(nullptr) {}

            //-----------------------------------------------------------------
            //!
            //! \brief copy original object
            //! 
            //! This constructor creates a type erasure by copying the 
            //! original data to the internal object. This constructor is 
            //! called in a situation as this one
            /*!
            \code 
            array_type data;
            ....
            array a(data);
            \endcode
            !*/
            //! the content of the original array data is copied to the 
            //! internal array of type array_type encapsulated by the type 
            //! erasure.
            //! 
            //! \tparam T type of the object. 
            //! \param o const reference to the original object
            //!
            template<typename T,
                     //this template expression is necessary to avoid that this
                     //constructor is callend when data_object itself is to be
                     //copied (see below for the correct copy constructor)
                     typename  = typename std::enable_if<
                                       !std::is_same<array,typename
                                       std::remove_reference<T>::type >::value 
                                       >::type
                    > 
            explicit array(const T &o):_ptr(new array_holder<T>(o))
            { }

            //------------------------------------------------------------------
            //!
            //! \brief move original object
            //!
            //! Constructor moves the original object to the type erasure
            /*!
            \code
            array a = DArray<UInt16>(shape_t{1024,1024});
            \endcode
            !*/
            //! \tparam T original type
            //! \param o rvalue reference to the original object
            //!
            template<typename T,
                     //this template expression is necessary to avoid that this
                     //constructor is used when a data_object by itself is to be
                     //moved (seel below for the correct move constructor)
                     typename = typename std::enable_if<
                                       !std::is_same<array,typename
                                       std::remove_reference<T>::type >::value 
                                       >::type
                    > 
            explicit array(T &&o):
                _ptr(new array_holder<typename std::remove_cv<
                                typename std::remove_reference<T>::type>::type>
                                (std::forward<T>(o)))
            { }


            //------------------------------------------------------------------
            //!copy constructor
            array(const array &e);
            //------------------------------------------------------------------
            //!move constructor
            array(array &&e);

            //==============assignment operators===============================
            //! copy assignment operator
            array &operator=(const array &a);

            //-----------------------------------------------------------------
            //! move assignment operator
            array &operator=(array &&a);

            //=====================public member functions=====================
            //!
            //! \brief get type id
            //!
            //! Return the type id of the data held by an instance of array.
            //! \return type id.
            //!
            type_id_t type_id() const;
            
            //-----------------------------------------------------------------
            //! 
            //! \brief return rank of array 
            //!
            //! Return the number of dimensions the multidimensional array 
            //! spans.  In the case of a scalar the return value of this 
            //! method is 0. 
            //! 
            //! \return number of dimensions
            //!
            size_t rank() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief return shape 
            //!
            //! Return the number of elements along each dimension of the 
            //! array as an instance of shape_t. In the case of a scalar value 
            //! the return value is empty (size=0).
            //!
            //! \return shape of the array
            //!
            shape_t shape() const;

            //-----------------------------------------------------------------
            //!
            //! \brief return shape in an arbitrary container
            //!
            //! Return the number of dimensions along each dimension as a 
            //! container type specified by the user. 
            /*! 
            \code
            auto s = array.shape<std::list<size_t> >();
            \endcode
            !*/
            //! If the wrapped type is a scalar an empty instance of CTYPE is
            //! returned.
            //!
            //! \tparam CTYPE container type
            //! \return instance of CTYPE
            //!
            template<typename CTYPE> CTYPE shape() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief return number of elements
            //!
            //! Returns the total number of elements stored in the array. 
            //! In the case of a scalar the size is 1. 
            //! 
            //! \return number of elements
            //!
            size_t size() const; 


            //-----------------------------------------------------------------
            //!
            //! \brief get value at index i
            //!
            //! This operator returns the content of the element with linear 
            //! index i as an instance of value by which one cannot alter the 
            //! data stored in the array. 
            //! This operator performs no index checking. 
            //!
            //! \param i linear index of the element
            //! \return value holding the content of element i
            //!
            value operator[](size_t i) const;

            //-----------------------------------------------------------------
            //!
            //! \brief get value at index i 
            //! 
            //! Return the content of the array at linear index i as an 
            //! instance of value (thus only read only access). This method 
            //! performs index checking. 
            //!
            //! \throws IndexError if i exceeds the size of the array
            //! \param i linear index of the element
            //! \return element at index i as instance of value
            //!
            value at(size_t i) const;

            //-----------------------------------------------------------------
            //!
            //! \brief get a reference to index i
            //!
            //! Return a reference to the element at linear index i. The 
            //! reference is provided as an instance of value_ref via which 
            //! the content of the array can be altered. This operator 
            //! performs no index checking. 
            //!
            //! \param i linear index i 
            //! \return reference to element i
            //!
            value_ref operator[](size_t i);

            //-----------------------------------------------------------------
            /*!
            \brief get element at index i

            */
            value_ref at(size_t i);

            //-----------------------------------------------------------------
            //! 
            //! \brief get reference to element
            //! 
            //! Returns a reference to an array element. The reference is 
            //! represented by an instance of value_ref.
            //! 
            //! \param index the index of the element
            //! \return value_ref with reference to the element
            //! 
            value_ref operator()(const element_index &index);

            //-----------------------------------------------------------------
            //! 
            //! \brief get element value
            //! 
            //! Returns the value of an element as an instance of value. 
            //! 
            //! \param index the element index
            //! \return the value as an instance of value
            //! 
            value operator()(const element_index &index) const;

            //-----------------------------------------------------------------
            //! return the type name
            string type_name() const;

            //-----------------------------------------------------------------
            //! get iterator to first element
            iterator begin() { return iterator(this,0); }

            //-----------------------------------------------------------------
            //! get iterator to last+1 element
            iterator end() { return iterator(this,size()); }

            //-----------------------------------------------------------------
            //! get const iterator to first element
            const_iterator begin() const { return const_iterator(this,0); }

            //-----------------------------------------------------------------
            //! get const iterator to last+1 element
            const_iterator end() const { return const_iterator(this,size()); }

            //-----------------------------------------------------------------
            //! get const pointer to data
            const void *data() const;

            //-----------------------------------------------------------------
            //! get pointer to data
            void *data() ;
            
    };

    //======================implementation of template members=================
    template<typename CTYPE> CTYPE array::shape() const
    {
        shape_t s = this->shape();
        CTYPE c(s.size());
        std::copy(s.begin(),s.end(),c.begin());
        return c;
    }

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup type_erasure_classes
    //! \brief get type id
    //! 
    //! Get the type ID of the array stored in an array type erasure.
    //! 
    //! \param a reference to the array 
    //! \return the type ID 
    //! 
    PNIIO_EXPORT type_id_t type_id(const array &a);

//end of namespace
}
}
        
