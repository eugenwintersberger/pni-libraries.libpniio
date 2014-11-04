//
// Declaration of the NXfield template
//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
//************************************************************************
//
// Declaration of the NXfield template
//
// Created on: Jul 3, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <sstream>

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>

#include "nxattribute_manager.hpp"
#include "nxobject_traits.hpp"
#include "algorithms/get_path.hpp"


namespace pni{
namespace io{
namespace nx{

    using namespace pni::core;
    //need this here to avoid name collisions with tango headers.
    using pni::core::array;
    using pni::core::string;
    using pni::core::exception;

    //! 
    //! \ingroup nexus_lowlevel
    //! \brief nxfield base class
    //!
    //! nxfield is a type used to store multidimensional data in a file. The IO
    //! methods it provides support all the array templates provided by \c
    //! libpnicore. Partial IO is provided by the () operator (see below). 
    //! The interface of nxfield is quite similar to those of the array 
    //! templates provided by \c libpnicore. Like them it provides a shape() 
    //! and  a size() method returning the number of elements along each 
    //! dimension and the total number of elements in the field. rank() 
    //! returns the number of dimensions of the field. 
    //! 
    //! Unlike the array templates which provide the ID of their element type 
    //! via a static member variable the method type_id() is provided by 
    //! NXField for the same purpose.
    //! The number of dimensions a field provides is fixed at the time it is
    //! created. However, the number of elements along each of these 
    //! dimensions can be altered at runtime. Two methods of the class are 
    //! responsible for resizing a field: resize() and grow(). 
    //! The difference between resize and grow is shown in the figure below. 
    //! While the grow() operation resizes the field by a fixed amount of 
    //! elements along a particular dimension a resize operation can enlarge 
    //! multiple dimensions at the same time. 
    //! The latter one is useful in situations where the number of elements 
    //! along each dimension is unknown at the time the field is created. 
    //! The grow() operation is however very useful in situations where the 
    //! number of elements to store in an element is not known at the time the 
    //! field is created. One can use this to append data along one dimensions.
    //! Consider for instance this example that shows a very common situation 
    //! during experiments. Data should be stored in a field but the total 
    //! number of points is not known when the field is created
    /*!\code
    //we start with a field of size 0 - no element
    nxfield field = group.create_field<float32>("motor",shape_t{0}); 

    size_t np = 0;
    while(true)
    {
        field.grow(0);
        field(np++).write(get_data());
        if(get_break_condition()) break;
    }
    \endcode
    */
    //! The above loop runs until get_break_condition() return true. In no 
    //! case we can no in advance when the loop will exit and thus how many 
    //! elements should be stored. The grow() method offers an easy way to 
    //! handle such situations.
    //!
    //! As HDF5 datasets, nxfield objects provide the possibility to read or 
    //! write only a part of the data.  The mechanism works pretty much as 
    //! the array view selection in \c libpnicore. 
    //! Compare the following code with the figures on the right side
    /*!\code
    darray<uint32> strip(shape_t{1024});

    //selection 1
    field1(3,slice(0,1024)).read(strip);

    //selection 2
    darray<uint32> block(shape_t{4,6});
    field2(slice(3,7),slice(2,8)).read(block);

    //selection 3
    darray<uint32> block2(shape_t{4,5});
    field3(slice(2,6),slice(2,10,2)).read(block2);

    \endcode
    */
    //! Under the hood the () operator of NXField applies a selection to the
    //! underlying HDF5 dataset according to the arguments passed to it. 
    //! Every call to read or write immediately after reading or writing the 
    //! data removes this selections.
    //!
    //! \tparam IMPID implementation id
    //!
    template<nximp_code IMPID> class nxfield
    {
        public:
            //! implementation type
            typedef typename nximp_map<IMPID>::field_imp imp_type;
            //! type implementation type
            typedef typename nximp_map<IMPID>::type_imp  type_type;
            //! typedef for this type
            typedef nxfield<IMPID>              field_type;
            //! attribute type
            typedef typename nxobject_trait<IMPID>::attribute_type
                attribute_type;
        private:
            //! field implementation
            imp_type _imp;

            //!
            //! \brief gernerate error message
            //!
            //! Generate the error message for a shape mismatch error 
            //! between a field and an array type. 
            //!
            //! \param ashape array shape
            //! \param fshape field shape
            //! \return error message
            //!
            static string _shape_mismatch_error_message(const shape_t
                    &ashape,const shape_t &fshape) 
            {
                std::stringstream ss;
                ss<<"Array shape ( ";
                for(auto v: ashape) ss<<v<<" ";
                ss<<") and field shape ( ";
                for(auto v: fshape) ss<<v<<" ";
                ss<<") do not match!";

                return ss.str();
            }


            //-----------------------------------------------------------------
            //!
            //! \brief read data to array
            //! 
            //! Read data from the field and store its content into an array.
            //!
            //! \throws memory_not_allocated_error if array buffer not 
            //! allocated
            //! \throws size_mismatch_error if array and field size do not 
            //! match
            //! \throws invalid_object_error if field is not valid
            //! \throws object_error in case of any other error
            //! \throws type_error if array data type cannot be handled
            //! \throws io_error in case of IO errors
            //!
            //! \tparam ATYPE array type
            //! \param a reference to an instance fo ATYPE
            //!
            template<typename ATYPE> 
            void _read_array(ATYPE &a) const
            {
                typedef typename type_type::index_vector_type index_vector_type;
                if(a.size() == 0)
                    throw memory_not_allocated_error(EXCEPTION_RECORD,
                                     "Target array buffer not allocated!");

                if(a.size()!=size())
                    throw size_mismatch_error(EXCEPTION_RECORD,
                            "Array and field size do not match!");

                _imp.read(pni::core::type_id(a),
                          a.template shape<index_vector_type>(),a.data());

            }

            //-----------------------------------------------------------------
            //!
            //! \brief write data from array
            //!
            //! Write the content of an array to a field.
            //!
            //! \throws memory_not_allocated_error if array buffer not 
            //! allocated
            //! \throws size_mismatch_error if array and field size do not 
            //! match
            //! \throws invalid_object_error if field is not valid
            //! \throws object_error in case of any other error
            //! \throws type_error if array type cannot be handled
            //! \throws io_error in case of IO errors
            //!
            //! \tparam ATYPE array type
            //! \param a reference to an instance fo ATYPE
            //!
            template<typename ATYPE> 
            void _write_array(const ATYPE &a) const
            {
                typedef typename type_type::index_vector_type index_vector_type;
                if(a.size() == 0)
                    throw memory_not_allocated_error(EXCEPTION_RECORD,
                                     "Source array buffer not allocated!");

                if(a.size()!=size())
                    throw size_mismatch_error(EXCEPTION_RECORD,
                            "Array and field size do not match!");

                _imp.write(pni::io::type_id(a),
                           a.template shape<index_vector_type>(),a.data()); 
            }


        public:
            //===================public attributes=============================
            //!
            //! \brief attribute manager
            //!
            //! This public attribute provides access to the attribute manager
            //! instance of this field. 
            //! \sa nxattribute_manager
            //!
            nxattribute_manager<field_type> attributes;
            //============constructors and destructors=========================
            //!
            //! \brief default constructor
            //!
            explicit nxfield():
                _imp(),
                attributes(_imp)
            { }

            //-----------------------------------------------------------------
            //!
            //! \brief copy constructor
            //!
            nxfield(const field_type &o):
                _imp(o._imp),
                attributes(_imp)
            { }

            //-----------------------------------------------------------------
            //!
            //! \brief move constructor
            //!
            nxfield(field_type &&o):
                _imp(std::move(o._imp)),
                attributes(_imp)
            { }

            //-----------------------------------------------------------------
            //!
            //! \brief move constructor from implementation object
            //!
            explicit nxfield(imp_type &&o):
                _imp(std::move(o)),
                attributes(_imp)
            {}

            //-----------------------------------------------------------------
            nxfield(const typename nxobject_trait<IMPID>::object_type &o):
                _imp(),
                attributes(_imp)
            {
                *this = o;
            }


            //-----------------------------------------------------------------
            //!
            //! \brief destructor
            //!
            ~nxfield() 
            { 
                _imp.clear_selections(); 
            }
            
            //===============assignment operator===============================
            //!
            //! \brief copy assignment operator
            //!
            field_type &operator=(const field_type &f)
            {
                if(this == &f) return *this;

                _imp = f._imp;
                return *this;
            }

            //----------------------------------------------------------------
            //!
            //! \brief move assignment operator
            //!
            field_type &operator=(field_type &&f)
            {
                if(this == &f) return *this;
                
                _imp = std::move(f._imp);
                return *this;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief conversion assignment
            //!
            //! \throws type_error if object is not a field
            //!
            field_type &operator=(const typename nxobject_trait<IMPID>::object_type &o)
            {
                *this = as_field(o);
                return *this;
            }


            //=================dataset inquiry methods=========================
            //!
            //! \brief field shape
            //!
            //! Returns the shape of the field
            //!
            //! \throws invalid_object_error if field is not valid
            //! \throws object_error in case of any other error
            //!
            //! \return container with elements per dimension
            //!
            template<typename CTYPE> CTYPE shape() const 
            {
                return type_type::template from_index_vector<CTYPE>(_imp.shape()); 
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief return size
            //!
            //! Return the size (number of elements) in the field.
            //!
            //! \throws invalid_object_error if field is not valid
            //! \throws objecct_error in case of any other error
            //!
            //! \return total number of elements in the field
            //!
            size_t size() const 
            { 
                return _imp.size(); 
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief get the type ID
            //!
            //! Return the ID of the data type stored in the field.
            //!
            //! \throws invalid_object_error if field is not valid
            //! \throws object_error in case of any other error
            //! \throws type_error if data type is not supported
            //! 
            //! \return data type ID
            //!
            type_id_t type_id() const 
            { 
                return _imp.type_id(); 
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get parent object
            //!
            //! Returns the parent object of the field.
            //!
            //! \throws invalid_object_error if field is not valid
            //! \throws type_error if the interal type of the field object could 
            //! not be determined
            //! \throws objet_error in case of any other error
            //!
            //! \return parent object
            //!
            typename nxobject_trait<IMPID>::object_type parent() const
            {
                typedef typename nxobject_trait<IMPID>::group_type group_type;
                typedef typename nximp_map<IMPID>::group_imp group_imp_type;

                return group_type(group_imp_type(_imp.parent()));
            }
            
            //-----------------------------------------------------------------
            //! 
            //! \brief grow field along a particular dimension
            //!
            //! Grows the field by n elements along dimension e. This method 
            //! is pretty useful in cases where an arbitrary number of points 
            //! shall be stored in a field and their number is not known when 
            //! the field was created.
            //!
            //! \throws index_error if e exceeds the rank of the field
            //! \throws object_error in case of any other error
            //! \throws invalid_object_error if field not valid
            //!
            //! \param e index of dimension along which to grow
            //! \param n number of elements by which to grow
            //!
            void grow(const size_t &e,const size_t &n=1) 
            {
                    _imp.grow(e,n);
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief number of dimensions
            //!
            //! Returns the number of dimensions of the field.
            //!
            //! \throws invalid_object_error if field is not valid
            //! \throws object_error in case of any other error
            //!
            //! \return number of dimensions
            //!
            size_t rank() const 
            { 
                return _imp.rank(); 
            }

            //=============methods for reading data============================
            //! 
            //! \brief reading simple data from the dataset
            //!
            //! Read a single data value from the dataset. In order to succeed 
            //! the dataset must be a scalar dataset or the total size of the 
            //! dataset must be 1.
            /*!
            \code
            uint32 scalar;
            field.read(scalar);
            \endcode
            */
            //!
            //! \throws shape_mismatch_error if dataset is not scalar
            //! \throws invalid_object_error if field is not valid
            //! \throws type_error if argument type cannot be handled
            //! \throws io_error in case of IO failure
            //! \throws object_error in case of any other error
            //!
            //! \tparam T data type of the argument
            //! \param value variable where to store the data
            //!
            template<typename T> void read(T &value) const
            {
                typedef typename type_type::index_vector_type index_vector_type;
                if(size() != 1)
                    throw shape_mismatch_error(EXCEPTION_RECORD,
                                              "Field is not scalar!");

                _imp.read(type_id_map<T>::type_id,index_vector_type{1},&value);
            }
           
            //----------------------------------------------------------------
            //!
            //! \brief reading data to memory
            //! 
            //! Read data from a field to a region in memory referedn to by 
            //! poitner values. This method does not check any shape or 
            //! size bounds. 
            //! 
            //! \throws invalid_object_error if field is not valid
            //! \throws type_error if argument type cannot be handled
            //! \throws io_error in case of IO failure
            //! \throws object_error in case of any other error
            //! 
            //! \tparam T data type to read (in memory)
            //! \param values pointer to memory reagion
            //!
            template<typename T> 
            void read(size_t n,T *values) const
            {
                typedef typename type_type::index_vector_type index_vector_type;

                _imp.read(type_id_map<T>::type_id,index_vector_type{n},values);
            }


            //-----------------------------------------------------------------
            //! 
            //! \brief read data to array
            //!
            //! Copy the data stored in the field to an array object.
            //! An exception is thrown if the buffer holding the arrays data is
            //! not allocated or the shape of the array does not match the shape
            //! of the field.
            /*! 
            \code
            darray<float32> a(field.shape<shape_t>());
            field.read(a);
            \endcode
            */
            //! \throws memory_not_allocated_error if array buffer not 
            //! allocated
            //! \throws size_mismatch_error if array and field size do not 
            //! match
            //! \throws invalid_object_error if field is not valid
            //! \throws object_error in case of any other error
            //! \throws type_error if array data type cannot be handled
            //! \throws io_error in case of IO errors
            //!
            //! \tparam STORAGE storage type of the mdarray template
            //! \tparam IMAP index map type of the array type
            //! \tparam IPA inplace arithmetic policy 
            //! \param array Array instance where to store the data
            //!
            template<
                     typename STORAGE,
                     typename IMAP,
                     typename IPA
                    >
            void read(mdarray<STORAGE,IMAP,IPA> &array) const
            {
                _read_array(array);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief read data to a array instance
            //! 
            //! This method reads data to an array type erasure. 
            //! 
            //! \throws memory_not_allocated_error if array buffer not 
            //! allocated
            //! \throws size_mismatch_error if array and field size do not 
            //! match
            //! \throws invalid_object_error if field is not valid
            //! \throws object_error in case of any other error
            //! \throws type_error if array data type cannot be handled
            //! \throws io_error in case of IO errors
            //! 
            //! \param a instance of the array
            //! 
            void read(array &a) const
            {
                _read_array(a);
            }

           
            //=================methods for writing data========================
            //! 
            //! \brief write a single value
            //!
            //! Writes a single value of type T to the field. This method will 
            //! succeed only if the field can hold only a single value.
            /*! 
            \code
            float64 data = 1.2340;
            field.write(data);
            \endcode
            */
            //! \throws size_mismatch_error if the dataspace is not scalar
            //! \throws invalid_object_error in case of IO errors
            //! \throws io_error in case of IO errors
            //! \throws object_error  in case of all other errors
            //! \throws type_error if tid does not have a corresponding HDF5
            //! data type
            //!
            //! \tparam T memory data type of the source
            //! \param value value to write
            //! 
            template<typename T> void write(const T &value) const
            {
                typedef typename type_type::index_vector_type index_vector_type;
                static_assert(!std::is_pointer<T>::value,"no pointer");
                if(_imp.size()!=1) 
                    throw size_mismatch_error(EXCEPTION_RECORD,
                                              "Field is not scalar!");

                _imp.write(type_id_map<T>::type_id,index_vector_type({1}),&value);
            }

            //----------------------------------------------------------------
            //! 
            //! \brief write data from memory
            //! 
            //! Write data from a memory region referend to by value to the
            //! field. The method does not perform any size or shape 
            //! checking. It assumes that the region of memory is large 
            //! enough. 
            //! 
            //! \throws invalid_object_error in case of IO errors
            //! \throws io_error in case of IO errors
            //! \throws object_error  in case of all other errors
            //! \throws type_error if tid does not have a corresponding HDF5
            //! data type
            //! 
            //! \tparam T memory data type of the source
            //! \param value pointer to memory region
            //! 
            template<typename T> void write(size_t n,const T *value) const
            {
                typedef typename type_type::index_vector_type index_vector_type;

                _imp.write(type_id_map<T>::type_id,index_vector_type{{n}},
                           static_cast<const void*>(value));
            }

            //----------------------------------------------------------------
            //! 
            //! \brief write data from mdarray
            //! 
            //! Write data stored in an instance of mdarray. 
            //! 
            //! \throws memory_not_allocated_error if array buffer not 
            //! allocated
            //! \throws size_mismatch_error if array and field size do not 
            //! match
            //! \throws invalid_object_error if field is not valid
            //! \throws object_error in case of any other error
            //! \throws type_error if array type cannot be handled
            //! \throws io_error in case of IO errors
            //! 
            //! \tparam STORAGE storage type for mdarray
            //! \tparam IMAP index map type for mdarray
            //! \tparam IPA inplance arithmetic type
            //! 
            //! \param a instance of mdarray
            //!
            template<
                     typename STORAGE,
                     typename IMAP,
                     typename IPA
                    >
            void write(const mdarray<STORAGE,IMAP,IPA> &a) const
            {
                _write_array(a);
            }

           
            //-----------------------------------------------------------------
            //! 
            //! \brief write old style string
            //! 
            //! Writes a C-style string to disk. This method is a 
            //! specialization of the write(const T &value) template mathod.
            //!
            //! \throws size_mismatch_error if the dataspace is not scalar
            //! \throws invalid_object_error in case of IO errors
            //! \throws io_error in case of IO errors
            //! \throws object_error  in case of all other errors
            //! \throws type_error if tid does not have a corresponding HDF5
            //! data type
            //! 
            //! \param value pointer to string data
            //!
            void write(const char *value) const
            {
                string s(value);
                write(s);

            }

            //-----------------------------------------------------------------
            //!
            //! \brief write array erasure
            //!
            //! Write the data stored by an array erasure. 
            //!
            //! \throws memory_not_allocated_error if array buffer not 
            //! allocated
            //! \throws size_mismatch_error if array and field size do not 
            //! match
            //! \throws invalid_object_error if field is not valid
            //! \throws object_error in case of any other error
            //! \throws type_error if array type cannot be handled
            //! \throws io_error in case of IO errors
            //!
            //! \param a reference to array erasure
            //!
            void write(const array &a) const
            {
                _write_array(a);
            }

            //---------------------------------------------------------------
            //! 
            //! \brief set a selection on the field
            //!
            //! This method applies a selection to the field and return a 
            //! reference to this field. This can now be used to write data 
            //! only to the selection of the array.
            /*!
            \code
            nxfield f = g.create_field<uint16>("frame",shape_t{1024,1024});
            darray<uint16> spec(shape_t{1024})k

            f(100,slice(0,1024)).read(spec)

            \endcode
            */
            //! The selection will be reset with every call to the read() or 
            //! write methods. 
            //!
            //! \throws invalid_object_error if field is not valid
            //! \throws shape_missmatch_error if selection and field rank do 
            //! not match
            //! \throws object_error in case of any other error
            //!
            //! \tparam ITYPES index types
            //! \param indices instances of ITYPES
            //! \return field object with selection set
            //!
            template<typename ...ITYPES>
            field_type operator()(ITYPES ...indices) const
            {
                typedef std::vector<slice> container_type;
                field_type new_field(*this);

                new_field._imp.apply_selection(container_type({slice(indices)...}));

                return new_field;
            }

            //---------------------------------------------------------------
            //! 
            //! \brief clear a selection
            //!
            //! Clears a selection applied to the field.
            //! 
            //! \throws object_error in case of failure
            //!
            //! \return new field instance with clearn selection
            //!
            field_type operator()() 
            {
                _imp.clear_selections();
                return *this;
            }


            //---------------------------------------------------------------
            //!
            //! \brief set a selection on the field
            //!
            //! Operator to set a selection to the field. The selection is 
            //! given by a vector container of slice objects.
            //! The selection will be reset with each call to the read() or 
            //! write() methods.
            //! 
            //! \throws invalid_object_error if field is not valid
            //! \throws shape_missmatch_error if selection and field rank do 
            //! not match
            //! \throws object_error in case of any other error
            //!
            //! \param selection container with instances of slice
            //! \return instance of NXField with selection set
            //!
            field_type operator()(const std::vector<slice> &selection)  const
            {
                field_type new_field(*this);
                new_field._imp.apply_selection(selection);
                return new_field;
            }

            //---------------------------------------------------------------
            //! 
            //! \brief return field name
            //!
            //! \throws invalid_object_error if field is not valid
            //! \throws io_error if name could not be read
            //! \throws type_error in case of an internal type issue
            //! \throws object_error in case of any other error
            //!
            //! \return name of the field
            //!
            string name() const 
            { 
                return _imp.name(); 
            }

            //---------------------------------------------------------------
            //!
            //! \brief return filename
            //! 
            //! Returns the name of the file the field belongs too.
            //!
            //! \throws invalid_object_error if the field is not valid
            //! \throws io_error if the filename information retrieval fails
            //! \throws type_error if the internal object type does not 
            //! support filename retrieval
            //! \throws object_error in case of any other error
            //!
            //! \return name of the file
            //!
            string filename() const 
            {
                return _imp.filename();
            }

            //---------------------------------------------------------------
            //!
            //! \brief close field
            //!
            //! \throws type_error if object type could not be determined 
            //! during closing
            //! \throws object_error in case of any other error
            //!
            void close() 
            { 
                _imp.close(); 
            }

            //---------------------------------------------------------------
            //!
            //! \brief check validity
            //!
            //! \throws object_error validity check fails
            //!
            bool is_valid() const noexcept 
            { 
                return _imp.is_valid(); 
            }

    };


//end of namespace
}
}
}
