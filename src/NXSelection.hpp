/*
 * Declaration of Nexus selection template
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
 * Declaration of Nexus selection template.
 *
 * Created on: Sep 21, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXSELECTION_HPP_
#define NXSELECTION_HPP_

#include<pni/utils/Types.hpp>
#include<pni/utils/ArrayObject.hpp>

using namespace pni::utils;

namespace pni{
    namespace nx{

        //! \ingroup nexus_lowlevel
        //! \brief Selection object for partial IO

        //! A selection object can be considered a view on a 
        //! particular region of an NXField. This allows to 
        //! perform partial IO as implemented in HDF5.
        template<typename Imp> class NXSelection:public Imp{
            private:
                Imp _imp;
            public:
                //=============constructors and destructors====================
                //!default constructor
                explicit NXSelection():_imp(){}
                
                //! copy constructor
                NXSelection(const NXSelection<Imp> &s):_imp(s._imp){}

                //! move constructor
                NXSelection(NXSelection<Imp> &&s):_imp(std::move(s._imp)){}

                //! copy construct form implementation
                explicit NXSelection(const Imp &i):_imp(i){}

                //! move construct from implementation
                explicit NXSelection(Imp &&i):_imp(std::move(i)){}

                //! destructor
                virtual ~NXSelection(){}

                //================assignment operators=========================
                //! copy assignment operator
                NXSelection<Imp> &operator=(const NXSelection<Imp> &s)
                {
                    if(this != &s) _imp = s._imp;
                    return *this;
                }

                //--------------------------------------------------------------
                //! move assignment operator
                NXSelection<Imp> &operator=(NXSelection<Imp> &&s)
                {
                    if(this != &s) _imp = std::move(s._imp);
                    return *this;
                }

                //================inquery methods==============================
                //! get selection rank

                //! Returns the rank (number of dimensions) of the selection.
                //! The rank of a selection is typically equal to the rank
                //! of the field form which the selection has been taken.
                //! \return number of dimension
                size_t rank() const
                {
                    return this->_imp.rank();
                }

                //-------------------------------------------------------------
                //! get selection size

                //! Returns the number of elements in the selection.
                //! \return number of elements
                size_t size() const
                {
                    return this->_imp.size();
                }

                //-------------------------------------------------------------
                //! get selection shape

                //! Shape of the selection holding the rank and the number of 
                //! elements along each dimension.
                //! \return shape of the selection
                Shape shape() const
                {
                    return this->_imp.shape();
                }

                //-------------------------------------------------------------
                //! get selection offset
                
                //! Return the offset value of the selection along dimension i.
                //! If i exceeds the rank of the selection IndexError exception
                //! will be thrown.
                //! \throws IndexError if i exceeds selection rank
                //! \param i index of dimension
                //! \return number of elements along i
                size_t offset(size_t i) const
                {
                    return this->_imp.offset(i);
                }

                //--------------------------------------------------------------
                //! set selection offset

                //! Set the offset value of the selection along dimension i.
                //! \throws IndexError if i exceeds selection rank
                //! \param i index of dimension
                //! \param o offset value for dimension i
                void offset(size_t i,size_t o)
                {
                    this->_imp.offset(i,o);
                }

                //--------------------------------------------------------------
                //! set all offsets

                //! Allows setting all offset values along each dimension 
                //! in a single call using an initializer list. 
                //! \throws  ShapeMissmatchError if list length  exceeds rank
                //! \param l initializer list
                void offset(const std::initializer_list<size_t> &l)
                {
                    EXCEPTION_SETUP("void NXSelection::offset("
                            "const std::initializer_list<size_t> &l)");

                    if(l.size() != this->rank())
                    {
                        EXCEPTION_INIT(ShapeMissmatchError,
                                "Selection rank and initializer list size do"
                                " not match!");
                        EXCEPTION_THROW();
                    }

                    size_t cnt = 0;
#ifdef NOFOREACH
                    for(auto iter = l.begin(); iter != l.end(); iter++){
                        const size_t &i = *iter;
#else
                    for(const size_t &i: l){
#endif
                        this->_imp.offset(cnt,i);
                        cnt++;
                    }
                }

                //-------------------------------------------------------------
                //! get selection stride

                //! Returns the stride value along dimension i. 
                //! \throws IndexError if i exceeds selection rank
                //! \param i dimension index
                //! \return stride value along dimension i
                size_t stride(size_t i) const
                {
                    return this->_imp.stride(i);
                }

                //--------------------------------------------------------------
                //! set selection stride

                //! Sets the selections stride value along dimension i to s.
                //! \throws IndexError if i exceeds selection rank
                //! \param i index of the dimension
                //! \param s stride value
                void stride(size_t i,size_t s)
                {
                    this->_imp.stride(i,s);
                }

                //--------------------------------------------------------------
                //! set all strides

                //! All stride values for the selection can be set by a single 
                //! call using an initializer list.
                //! \throws ShapeMissmatchError if list size does not match rank
                //! \param l initializer list with stride values
                void stride(const std::initializer_list<size_t> &l)
                {
                    EXCEPTION_SETUP("void NXSelection::stride("
                            "const std::initializer_list<size_t> &l)");

                    if(l.size() != this->rank())
                    {
                        EXCEPTION_INIT(ShapeMissmatchError,
                                "Selection rank and initializer list size do"
                                " not match!");
                        EXCEPTION_THROW();
                    }
                    
                    size_t cnt = 0;
#ifdef NOFOREACH
                    for(auto iter = l.begin(); iter!=l.end();iter++){
                        const size_t &i = *iter;
#else
                    for(const size_t &i: l){
#endif
                        this->_imp.stride(cnt,i);
                        cnt++;
                    }
                }
            
                //-------------------------------------------------------------
                //! get selection count

                //! Returns the count value (number of elements) along dimension i. 
                //! \throws IndexError if i exceeds selection rank
                //! \param i dimension index
                //! \return count value along dimension i
                size_t count(size_t i) const
                {
                    return this->_imp.count(i);
                }

                //--------------------------------------------------------------
                //! set selection count

                //! Sets the selections count value along dimension i to s.
                //! \throws IndexError if i exceeds selection rank
                //! \param i index of the dimension
                //! \param s count value
                void count(size_t i,size_t s)
                {
                    this->_imp.count(i,s);
                }

                //--------------------------------------------------------------
                //! set all count

                //! All count values for the selection can be set by a single 
                //! call using an initializer list.
                //! \throws ShapeMissmatchError if list size does not match rank
                //! \param l initializer list with count values
                void count(const std::initializer_list<size_t> &l)
                {
                    EXCEPTION_SETUP("void NXSelection::count("
                            "const std::initializer_list<size_t> &l)");

                    if(l.size() != this->rank())
                    {
                        EXCEPTION_INIT(ShapeMissmatchError,
                                "Selection rank and initializer list size do"
                                " not match!");
                        EXCEPTION_THROW();
                    }
                    
                    size_t cnt = 0;
#ifdef NOFOREACH
                    for(auto iter = l.begin(); iter!=l.end();iter++){
                        const size_t &i = *iter;
#else
                    for(const size_t &i: l){
#endif
                        this->_imp.count(cnt,i);
                        cnt++;
                    }
                }



                //=================methods for reading data====================
                //! read a simple value from the selection
                template<typename T> void read(T &value) const
                {
                    EXCEPTION_SETUP("template<typename T> void "
                                    "NXSelection::read(T &value) const");
                    this->_imp.read(value);
                }

                //--------------------------------------------------------------
                //! read a complex value
                template<typename T> void read(std::complex<T> &value) const
                {
                    this->_imp.read(value);
                }

                //-------------------------------------------------------------
                //! read a binary value
                void read(Binary &value) const
                {
                    this->_imp.read(value);
                }

                //-------------------------------------------------------------
                //! read a string value 

                //! Read a string value from the selection. This works only
                //! if the size of the selection is 1. 
                //! \param value variable where to store the data
                void read(String &value) const
                {
                    EXCEPTION_SETUP("void NXSelection::read(String &value) const");
                    this->_imp.read(value);
                }
                
                //-------------------------------------------------------------
                //! read a buffer from selection

                //! Write the content of the selection into the buffer
                //! buffer object. This operation will only succeed if the 
                //! size of the selection matches the size of the buffer.
                //! \param buffer Buffer object where to store the data
                template<typename T,template<typename> class BT>
                    void read(BT<T> &buffer) const
                {
                    EXCEPTION_SETUP("template<typename T,template<typename> "
                            "class BT> void NXSelection::read(BT<T> &buffer) const");

                    this->_imp.read(buffer);
                }
                
                //-------------------------------------------------------------
                //! read an array

                //! Read an array from the selection. This method will 
                //! only succeed if the size of the selection matches
                //! that of the array. 
                //! \throws SizeMissmatchError if sizes do not match
                //! \throws H5DataSetError in cases of other errors
                //! \param array array where to store the data
                template<typename T,template<typename> class BT>
                    void read(Array<T,BT> &array) const
                {
                    EXCEPTION_SETUP("template<typename T,template<typename> "
                            "class BT> void NXSelection::read(Array<T,BT> &array) const");

                    this->_imp.read(array);
                }
                

                //-------------------------------------------------------------
                //! read a selection to a scalar

                //! Write the content of a selection to a scalar. This 
                //! methhod succeeds only if the size of the selection 
                //! is 1. If this is not the case a SizeMissmatchError 
                //! will be thrown.
                //! \throws SizeMissmatchError if selection size not 1
                //! \throws H5DatasetError in case of other errors
                //! \param scalar object where to store data
                template<typename T> void read(Scalar<T> &scalar) const
                {
                    EXCEPTION_SETUP("template<typename T> void "
                            "NXSelection::read(Scalar<T> &scalar) const");

                    this->_imp.read(scalar);

                }

                //=================methods for writing data====================
                //! write a single value with selection

                //! write a single value at the location specified by 
                //! selection. To use a selection the dataset must not
                //! be scalar. 
                //! \throws ShapeMissmatchError if the dataset is scalar
                //! \throws H5DataSetError in cases of other errors
                //! \param s selection object
                //! \param value object from which to read data
                template<typename T> void write(const T &value) const
                {
                    EXCEPTION_SETUP("template<typename T> void "
                            "NXSelection::write(const T &value) const");

                    this->_imp.write(value);
                }

                //--------------------------------------------------------------
                //! write a single string value

                //! Stings need a slightly different handling than all 
                //! other data. Thats why this method was overloaded.
                //! \param value the string to write
                void write(const String &value) const
                {
                    EXCEPTION_SETUP("void NXSelection::"
                            "write(const String &value) const");

                    this->_imp.write(value);
                }

                //--------------------------------------------------------------
                //! write a binary value
                void write(const Binary &value) const
                {
                    this->_imp.write(value);
                }

                //--------------------------------------------------------------
                //! write a complex value
                template<typename T> void write(const std::complex<T> &value)
                    const
                {
                    this->_imp.write(value);
                }
               
                //--------------------------------------------------------------
                //! write a scalar with selection

                //! Write a scalar value in the region defined by the
                //! selection. In order to succeed the dataset must not be 
                //! scalar. 
                //! \throws ShapeMissmatchError if the dataset is scalar
                //! \throws H5DataSetError in case of all other errors
                //! \param s selection object
                //! \param scalar the scalar object which to write to disk
                template<typename T> void write(const Scalar<T> &scalar) const
                {
                    EXCEPTION_SETUP("template<typename T> void "
                            "NXSelection::write(const Scalar<T> &scalar)"
                            "const");

                    this->_imp.write(scalar);
                }
               
                //--------------------------------------------------------------
                //! write a buffer with selection

                //! Writes teh content of a memory buffer to the dataset
                //! in the region defined by the selection s. 
                //! For this purpose the size of the selection must match
                //! the size of the buffer.
                //! \throws SizeMissmatchBuffer selection and buffer sizes do not match
                //! \throws H5DataSetError in case of other errors
                //! \param s selection object
                //! \param buffer reference to the buffer object
                template<typename T,template<typename> class BT>
                    void write(const BT<T> &buffer) const
                {
                    EXCEPTION_SETUP("template<typename T,template<typename> "
                            "class BT> void NXSelection::write(const BT<T> "
                            "&buffer) const");

                    this->_imp.write(buffer);

                }
               
                //---------------------------------------------------------------
                //! write an array with selection

                //! 
                template<typename T,template<typename> class BT>
                    void write(const Array<T,BT> &array) const
                {
                    EXCEPTION_SETUP("template<typename T,template<typename> "
                            "class BT> void NXSelection::write(const "
                            "Array<T,BT> &array) const");

                    this->_imp.write(array);

                }


        };



        //end of namespace
    }
}


#endif /* NXSELECTION_HPP_ */
