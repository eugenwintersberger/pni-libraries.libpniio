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

#include "nximp_map.hpp"
#include "nxobject_traits.hpp"
#include "nxexceptions.hpp"
#include "nxselection.hpp"
#include "utils/io_utils.hpp"
#include "nxattribute.hpp"
#include "nxattribute_iterator.hpp"
#include "algorithms.hpp"


namespace pni{
namespace io{
namespace nx{

    using namespace pni::core;
    //need this here to avoid name collisions with tango headers.
    using pni::core::array;
    using pni::core::string;
    using pni::core::exception;

    /*! 
    \ingroup nexus_lowlevel
    \brief nxfield base class

    nxfield is a type used to store multidimensional data in a file. The IO
    methods it provides support all the array templates provided by \c
    libpnicore. Partial IO is provided by the () operator (see below). 
    The interface of nxfield is quite similar to those of the array templates
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
    nxfield field = group.create_field<float32>("motor",shape_t{0}); 

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

    As HDF5 datasets, nxfield objects provide the possibility to read or write
    only a part of the data.  The mechanism works pretty much as the array view
    selection in \c libpnicore. 
    Compare the following code with the figures on the right side
    \code
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
    Under the hood the () operator of NXField applies a selection to the
    underlying HDF5 dataset according to the arguments passed to it. 
    Every call to read or write immediately after reading or writing the data
    removes this selections.
    */
    template<nximp_code IMPID> class nxfield
    {
        public:
            typedef typename nximp_map<IMPID>::field_imp imp_type;
            typedef nxfield<IMPID>              field_type;
            typedef typename nxobject_trait<IMPID>::attribute_type
                attribute_type;
            typedef nxattribute_iterator<field_type,attribute_type>
                attr_iterator;
        private:
            //! field implementation
            imp_type _imp;
            /*!
            \brief gernerate error message

            Generate the error message for a shape mismatch error between a
            field and an array type. 
            \param ashape array shape
            \param fshape field shape
            \return error message
            */
            static string _shape_mismatch_error_message(const shape_t
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
            \brief read data to array

            \throws memory_not_allocated_error if array buffer not allocated
            \throws shape_mismatch_error if shapes do not match
            \throws nxfield_error in case of other errors
            \tparam ATYPE array type
            \param a reference to an instance fo ATYPE
            */
            template<typename ATYPE> void _read_array(ATYPE &a) const
            {
                if(a.size() == 0)
                    throw memory_not_allocated_error(EXCEPTION_RECORD,
                                     "Target array buffer not allocated!");

                auto ashape = a.shape<shape_t>();
                auto fshape = this->shape<shape_t>();
                
                if(ashape.size() == fshape.size())
                {
                    //if array and field have the same rank we need to check the
                    //shape of each of the objects
                    if(!std::equal(ashape.begin(),ashape.end(),fshape.begin()))
                        throw shape_mismatch_error(EXCEPTION_RECORD,
                                _shape_mismatch_error_message(ashape,fshape));
                }
                else
                {
                    //if the two components are of different size we have to
                    //throw an exception in any case
                    if(this->size() != a.size())
                        throw shape_mismatch_error(EXCEPTION_RECORD,
                                _shape_mismatch_error_message(ashape,fshape));
                }

                //finally we read the data
                try
                {
                    _imp.read( a.data());
                }
                catch(nxfield_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }

            }


            //-----------------------------------------------------------------
            /*!
            \brief write data from array

            \throws memory_not_allocated_error if array buffer not allocated
            \throws shape_mismatch_error if shapes do not match
            \throws nxfield_error in case of other errors
            \tparam ATYPE array type
            \param a reference to an instance fo ATYPE
            */
            template<typename ATYPE> void _write_array(ATYPE &a) const
            {
                if(a.size() == 0)
                    throw memory_not_allocated_error(EXCEPTION_RECORD,
                                     "Source array buffer not allocated!");

                auto ashape = a.shape<shape_t>();
                auto fshape = this->shape<shape_t>();

                if(ashape.size() == fshape.size())
                {
                    if(!std::equal(ashape.begin(),ashape.end(),fshape.begin()))
                        throw shape_mismatch_error(EXCEPTION_RECORD,
                                _shape_mismatch_error_message(ashape,fshape));
                }
                else
                {
                    if(this->size() != a.size())
                        throw shape_mismatch_error(EXCEPTION_RECORD,
                               _shape_mismatch_error_message(ashape,fshape));
                }


                try { _imp.write(a.data()); }
                catch(...)
                {
                    throw nxfield_error(EXCEPTION_RECORD,
                                     "Cannt write data from array!");
                }
            }

            //-----------------------------------------------------------------
            /*!
            \brief apply selection

            Apply a selection to the field.
            \param s selection container
            */
            void apply_selection(const std::vector<slice> &s) 
            {
                _imp.apply_selection(s);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief remove a selection

            Removes a selection previously applied with apply_selection.
            */
            void reset_selection() 
            {
                _imp.clear_selections();
            }

        public:
            //============constructors and destructors=========================
            //! default constructor
            explicit nxfield(){ }

            //-----------------------------------------------------------------
            //! copy constructor
            nxfield(const field_type &o):_imp(o._imp) { }

            //-----------------------------------------------------------------
            //! move constructor
            nxfield(field_type &&o):_imp(std::move(o._imp)) { }

            //-----------------------------------------------------------------
            //! copy constructor from implementation object
            explicit nxfield(const imp_type &o):_imp(o) { }

            //-----------------------------------------------------------------
            //! move constructor from implementation object
            explicit nxfield(imp_type &&o):_imp(std::move(o)){}

            //-----------------------------------------------------------------
            nxfield(const typename nxobject_trait<IMPID>::object_type &o):
                _imp()
            {
                *this = o;
            }


            //-----------------------------------------------------------------
            //!destructor
            ~nxfield() { _imp.clear_selections(); }
            
            //===============assignment operator===============================
            field_type &operator=(const field_type &f)
            {
                if(this == &f) return *this;

                _imp = f._imp;
                return *this;
            }

            field_type &operator=(field_type &&f)
            {
                if(this == &f) return *this;
                
                _imp = std::move(f._imp);
                return *this;
            }

            //-----------------------------------------------------------------
            field_type &operator=(const typename nxobject_trait<IMPID>::object_type &o)
            {
                *this = as_field(o);
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
                return _imp.template shape<CTYPE>(); 
            }

            //-----------------------------------------------------------------
            /*! 
            \brief return size

            Return the size (number of elements) in the field.
            \return total number of elements in the field
            */
            size_t size() const { return _imp.size(); }

            //-----------------------------------------------------------------
            /*! 
            \brief get the type ID

            Return the ID of the data type stored in the field.
            \return data type ID
            */
            type_id_t type_id() const { return _imp.type_id(); }

            //-----------------------------------------------------------------
            /*!
            \brief get parent object

            Returns the parent object of the field.
            \return parent object
            */
            typename nxobject_trait<IMPID>::object_type parent() const
            {
                typedef typename nxobject_trait<IMPID>::group_type group_type;
                typedef typename nximp_map<IMPID>::group_imp group_imp_type;

                return group_type(group_imp_type(_imp.parent()));
            }
            
            //-----------------------------------------------------------------
            /*! 
            \brief resize field

            Resize the field to a new shape determined by s.  The rank of the
            old and the new shape must coincide otherwise an exception will be
            thrown.
            \throws shape_mismatch_error if ranks do not match
            \throws nxfield_error in case of other errors
            \param s describing the new shape of the field
            */
            template<typename CTYPE> void resize(const CTYPE &s)
            {
                try
                {
                    _imp.resize(s);
                }
                catch(shape_mismatch_error &e)
                {
                    e.append(EXCEPTION_RECORD); throw e;
                }
                catch(...)
                {
                    throw nxfield_error(EXCEPTION_RECORD,
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
            \throws index_error if e exceeds the rank of the field
            \throws nxfield_error in case of other errors
            \param e index of dimension along which to grow
            \param n number of elements by which to grow
            */
            void grow(const size_t &e,const size_t &n=1)
            {
                try
                {
                    _imp.grow(e,n);
                }
                catch(index_error &e)
                {
                    e.append(EXCEPTION_RECORD); throw e;
                }
                catch(...)
                {
                    std::stringstream ss;
                    ss<<"Growing field ["<<this->path();
                    ss<<"] along dimension"<<e<<" by "<<n<<" elements ";
                    ss<<"failed!";
                    throw nxfield_error(EXCEPTION_RECORD,ss.str());
                }
            }

            //-----------------------------------------------------------------
            /*! 
            \brief number of dimensions

            Returns the number of dimensions of the field.
            \return number of dimensions
            */
            size_t rank() const { return _imp.rank(); }

            //=============methods for reading data============================
            /*! 
            \brief reading simple data from the dataset

            Read a single data value from the dataset. In order to succeed the
            dataset must be a scalar dataset or the total size of the dataset
            must be 1.
            \code
            uint32 scalar;
            field.read(scalar);
            \endcode
            \throws shape_mismatch_error if dataset is not scalar
            \throws nxfield_error in all other error cases
            \param value variable where to store the data
            */
            template<typename T> void read(T &value) const
            {
                if(_imp.size() != 1)
                    throw shape_mismatch_error(EXCEPTION_RECORD,
                                              "Field is not scalar!");

                try
                {
                    _imp.read(&value);
                }
                catch(...)
                {
                    throw nxfield_error(EXCEPTION_RECORD,
                                       "Error reading data from field ["
                                       +this->path()+"]!");
                }
            }
           
            //----------------------------------------------------------------
            template<typename T> 
            void read(T *values) const
            {
                try
                {
                    _imp.read(values);
                }
                catch(...)
                {
                    throw nxfield_error(EXCEPTION_RECORD,
                                       "Error reading data from field ["
                                       +this->path()+"]!");
                }
            }


            //-----------------------------------------------------------------
            /*! 
            \brief read data to array

            Copy the data stored in the field to an array object.
            An exception is thrown if the buffer holding the arrays data is
            not allocated or the shape of the array does not match the shape
            of the field.
            
            \code
            darray<float32> a(field.shape<shape_t>());
            field.read(a);
            \endcode

            \throws shape_mismatch_error if field and array-shape do not
            match
            \throws memory_not_allocated_error if array buffer not allocated
            \throws nxfield_error in case of all other errors.
            \param array Array instance where to store the data
            */
            template<
                     typename STORAGE,
                     typename IMAP,
                     typename IPA
                    >
            void read(mdarray<STORAGE,IMAP,IPA> &array) const
            {
                try
                {
                    this->_read_array(array);
                }
                catch(memory_not_allocated_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(shape_mismatch_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(nxfield_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
            }

            //-----------------------------------------------------------------
            /*!
            \brief read data to a array instance

            This method reads data to an array type erasure. 
            \throws shape_mismatch_error if field and array-shape do not match
            \throws memory_not_allocated_error if array-buffer is not allocated
            \throws nxfield_error in case of any other IO error
            \param a instance of the array
            */
            void read(array &a) const;

           
            //=================methods for writing data========================
            /*! 
            \brief write a single value

            Writs a single value of type T to the field. This method will 
            succeed only if the field can hold only a single value.
            
            \code
            float64 data = 1.2340;
            field.write(data);
            \endcode

            \throws shape_mismatch_error if the dataspace is not scalar
            \throws nxfield_error in case of other errors
            \param value value to write
            */
            template<typename T> void write(const T &value) const
            {
                static_assert(!std::is_pointer<T>::value,"no pointer");
                if(_imp.size()!=1) 
                    throw shape_mismatch_error(EXCEPTION_RECORD,
                                              "Field is not scalar!");

                try
                {
                    _imp.write(&value);
                }
                catch(...)
                {
                    throw nxfield_error(EXCEPTION_RECORD,
                            "Error writing data to field ["
                            +this->path()+"]!");
                }

            }

            //----------------------------------------------------------------
            template<typename T> void write(const T *value) const
            {

                try
                {
                    _imp.write(value);
                }
                catch(...)
                {
                    throw nxfield_error(EXCEPTION_RECORD,
                            "Error writing data to field ["
                            +this->path()+"]!");
                }

            }

            //----------------------------------------------------------------
            template<
                     typename STORAGE,
                     typename IMAP,
                     typename IPA
                    >
            void write(const mdarray<STORAGE,IMAP,IPA> &a)
            {
                _write_array(a);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief write old style string

            Writes a C-style string to disk. This method is a specialization of
            the write(const T &value) template mathod.

            \throws shape_mismatch_error if the field is not scalar
            \throws nxfield_error in case of other errors
            \param value pointer to string data
            */
            void write(const char *value) const
            {
                try
                {
                    string s(value);
                    this->write(s);
                }
                catch(shape_mismatch_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(nxfield_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }

            }

            //-----------------------------------------------------------------
            /*! 
            \brief write data form a DArray

            Write data from an instance of darray. 
            \throws memory_not_allocated_error if array-buffer is not allocated
            \throws shape_mismatch_error if field and array shape do not match
            \throws nxfield_error in case of any other IO error
            \tparam OTS template arguments to DArray
            \param a instance of DArray
            */
            template<
                     typename STORAGE,
                     typename IMAP,
                     typename IPA
                    > 
            void write(const mdarray<STORAGE,IMAP,IPA> &a) const
            {
                try
                {
                    this->_write_array(a);
                }
                catch(memory_not_allocated_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(shape_mismatch_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
                catch(nxfield_error &error)
                {
                    error.append(EXCEPTION_RECORD); throw error;
                }
            }

            //-----------------------------------------------------------------
            /*!
            \brief write array erasure

            Write the data stored by an array erasure. 
            \throws memory_not_allocated_error array instance nof allocated
            \throws shape_mismatch_error shapes do not match
            \param a reference to array erasure
            */
            void write(const array &a) const;

            //---------------------------------------------------------------
            /*! 
            \brief set a selection on the field

            This method applies a selection to the field and return a reference
            to this field. This can now be used to write data only to the
            selection of the array.
            \code
            nxfield f = g.create_field<uint16>("frame",shape_t{1024,1024});
            darray<uint16> spec(shape_t{1024})k

            f(100,slice(0,1024)).read(spec)

            \endcode
            The selection will be reset with every call to the read() or write
            methods. 
            \tparam ITYPES index types
            \param indices instances of ITYPES
            \return field object with selection set
            */
            template<typename ...ITYPES>
            nxselection<field_type> operator()(ITYPES ...indices)
            {
                typedef nxselection<field_type> sel_type;
                typedef typename sel_type::selection_type container_type;

                return sel_type(container_type({slice(indices)...}),*this);
            }

            //---------------------------------------------------------------
            /*!
            \brief set a selection on the field

            Operator to set a selection to the field. The selection is given by
            a vector container of slice objects.
            The selection will be reset with each call to the read() or write()
            methods.
            \param selection container with instances of slice
            \return instance of NXField with selection set
            */
            nxselection<field_type> operator()(const std::vector<slice> &selection) 
            {
                typedef nxselection<field_type> sel_type;

                return sel_type(selection,*this);
            }
        
            friend class nxselection<field_type>;

            //----------------------------------------------------------------
            string path() const { return _imp.path(); }

            //----------------------------------------------------------------
            string base() const { return _imp.base(); }

            //---------------------------------------------------------------
            string name() const { return _imp.name(); }

            //---------------------------------------------------------------
            void close() { _imp.close(); }

            //---------------------------------------------------------------
            bool is_valid() const noexcept { return _imp.is_valid(); }

            //---------------------------------------------------------------
            const imp_type &imp() const { return _imp; }

            //---------------------------------------------------------------
            nxobject_type object_type() const { return _imp.nxobject_type(); }

            //=================attribute management methods====================
            /*! 
            \brief create an array attribute

            Template method creating a multidimensional attribute of type T and
            shape s. By default an exception will be thrown if an attribute of
            same name already exists. If ov=true an existing attribute will be
            overwritten
            \throws nxattribute_error in case of errors
            \param n name of the attribute
            \param s shape of the array
            \param ov overwrite flag
            \return instance of nxattribute
            */
            template<
                     typename T,
                     typename CTYPE
                    > 
            attribute_type attr(const string &n, const CTYPE &s,bool ov=true) const
            {
                attribute_type attr;

                try
                {
                    attr = attribute_type(_imp.template attr<T>(n,s,ov));
                }
                catch(...)
                {
                    throw nxattribute_error(EXCEPTION_RECORD,
                            "Cannot create attribute ["+n+"] for object "
                            "["+this->path()+"]!");
                }
                return attr;
            }

            //-----------------------------------------------------------------
            /*! \brief create scalar attribute

            Template method creating a scalar atribute of type T. By default an
            exception is raised if an attribute of same name already exists. If
            ov=true the existing attribute will be overwritten and no exeption
            will be thrown.
            \throws nxattribute_error in case of attribute related errors
            \throws nxbackend_error in case of any other error
            \param n name of the attribute
            \param ov overwrite flag
            \return an instance of nxattribute
            */
            template<typename T> 
            attribute_type attr(const string &n,bool ov=false) const
            {
                return attr<T>(n,shape_t{1},ov);
            }




            //-----------------------------------------------------------------
            /*! 
            \brief open an existing attribute by name
           
            Opens an existing attribute of name n and returns an instance of
            nxattribute<> to the callee. An exception will be thrown if the
            attribute does not exist.
            \throws nxattribute_error in case of problems
            \param n name of the attribute
            \return instance of nxattribute
            */
            attribute_type attr(const string &n) const
            {
                attribute_type attr;

                try
                {
                    attr = attribute_type(_imp.attr(n));
                }
                catch(...)
                {
                    throw nxattribute_error(EXCEPTION_RECORD,
                            "Cannot open attribute ["+n+"] from object ["
                            +this->path()+"]!");
                }
                return attr;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief open an attribute by index
           
            Opens an existing attribute by its index. If the index exceeds the
            total number of attributes attached to this object an exception will
            be thrown.
            \throws nxattribute_error in case of errors
            \param i index of the attribute
            \return instance of nxattribute
            */
            attribute_type attr(size_t i) const
            {
                attribute_type attr;

                try
                {
                    attr = attribute_type(_imp.attr(i));
                }
                catch(...)
                {
                    std::stringstream istr;
                    istr<<"Cannot open attribute ["<<i<<"] from object [";
                    istr<<this->path()+"]!";
                    throw nxattribute_error(EXCEPTION_RECORD,istr.str());
                }

                return attr;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief delete an attribute

            Deletes an attribute attached to this object.
            \throws nxattribute_error in case of errors
            \param n name of the attribute
            */
            void del_attr(const string &n) const
            {
                try
                {
                    _imp.del_attr(n);
                }
                catch(...)
                {
                    throw nxattribute_error(EXCEPTION_RECORD,
                            "Error deleting attribute ["+n+"]!");
                }
            }

            //-----------------------------------------------------------------
            /*! 
            \brief checks for attribute existance

            Checks whether or not an attribute with a particular name exits. If
            it does true is returned otherwise false.
            \throws nxattribute_error in case of errors
            \param n name of the attribute
            \return true if n exists otherwise false
            */
            bool has_attr(const string &n) const
            {
                try
                {
                    return _imp.has_attr(n);
                }
                catch(...)
                {
                    throw nxattribute_error(EXCEPTION_RECORD,
                            "Error checking for attribute ["+n+"]!");
                }
                return false;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief get number of attributes

            Returns the number of attributes attached to this object.
            \return number of attributes
            */
            size_t nattr() const { return _imp.nattr(); }

            //-----------------------------------------------------------------
            /*! 
            \brief iterator to frist attribute

            Return an iterator to the first attribute attached to the object.
            \return iterator to first attribute
            */
            attr_iterator attr_begin() const { return attr_iterator(*this); }

            //-----------------------------------------------------------------
            /*! 
            \brief iterator to last attribute

            Return an iterator to the last attribute attached to the object.
            \return iterator to last attribute
            */
            attr_iterator attr_end() const
            {
                return attr_iterator(*this,this->nattr());
            }




    };

    //-------------------------------------------------------------------------
    template<nximp_code IMPID> void nxfield<IMPID>::read(array &a) const
    {
        if(a.size() == 0)
            throw memory_not_allocated_error(EXCEPTION_RECORD,
                             "Target array buffer not allocated!");

        shape_t ashape = a.shape();
        auto fshape = this->shape<shape_t>();
        
        if(ashape.size() == fshape.size())
        {
            //if array and field have the same rank we need to check the
            //shape of each of the objects
            if(!std::equal(ashape.begin(),ashape.end(),fshape.begin()))
                throw shape_mismatch_error(EXCEPTION_RECORD,
                        _shape_mismatch_error_message(ashape,fshape));
        }
        else
        {
            //if the two components are of different size we have to
            //throw an exception in any case
            if(this->size() != a.size())
                throw shape_mismatch_error(EXCEPTION_RECORD,
                        _shape_mismatch_error_message(ashape,fshape));
        }

        //finally we read the data
        try
        {
            read_array(_imp,a);
        }
        catch(nxfield_error &error)
        {
            error.append(EXCEPTION_RECORD); throw error;
        }
    }

    //-------------------------------------------------------------------------
    template<nximp_code IMPID> void nxfield<IMPID>::write(const array &a) const
    {

        if(a.size() == 0)
            throw memory_not_allocated_error(EXCEPTION_RECORD,
                             "Source array buffer not allocated!");

        shape_t ashape = a.shape();
        auto fshape = this->shape<shape_t>();

        if(ashape.size() == fshape.size())
        {
            if(!std::equal(ashape.begin(),ashape.end(),fshape.begin()))
                throw shape_mismatch_error(EXCEPTION_RECORD,
                        _shape_mismatch_error_message(ashape,fshape));
        }
        else
        {
            if(this->size() != a.size())
                throw shape_mismatch_error(EXCEPTION_RECORD,
                       _shape_mismatch_error_message(ashape,fshape));
        }


        try 
        { 
            write_array(_imp,a);            
        }
        catch(type_error &error)
        {
            //in case of a type error we propagate the error to the next level
            error.append(EXCEPTION_RECORD);
            throw error;
        }
        catch(...)
        {
            throw nxfield_error(EXCEPTION_RECORD,
                             "Cannt write data from array!");
        }
    }

//end of namespace
}
}
}
