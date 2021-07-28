//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
// Created on: 11 08, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include <pni/type_erasures/value.hpp>
#include <pni/type_erasures/value_ref.hpp>

namespace pni{

    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief array holder interface 
    //!
    //! Internal class that defines the interface of the holder class
    //!
    class array_holder_interface
    {
        public:
            //! single element index type
            typedef std::vector<size_t> element_index; 
            //! view index type
            typedef std::vector<slice>  view_index;
            //!
            //! \brief return type id 
            //! 
            //! Return the type ID of the held object.
            //! \return type id
            //!
            virtual type_id_t type_id() const = 0;
            
            //-----------------------------------------------------------------
            //!
            //! \brief get rank
            //!
            //! Return the rank of the data stored. If the rank is 0 the data 
            //! is a scalar. In all other cases we assume the data to be a
            //! multidimensional array.
            //! 
            //! \return rank (number of dimensions)
            //!
            virtual size_t rank() const = 0;

            //-----------------------------------------------------------------
            //!
            //! \brief get shape
            //!
            //! Return the shape of the data. This is the number of elements 
            //! along each dimension. In the case of a scalar the shape is 
            //! empty (size() == 0).
            //! 
            //! \return shape of data
            //!
            virtual shape_t shape() const = 0;

            //-----------------------------------------------------------------
            //!
            //! \brief get size
            //!
            //! Return the size of the original data. This is the number of 
            //! elements of a particular type (determined by the type id).  
            //! 
            //! \return size
            //!
            virtual size_t size() const = 0;

            //-----------------------------------------------------------------
            //!
            //! \brief write data 
            //!
            //! Write data to a standard  C++ stream.
            //!
            //! \param os reference to output stream
            //! \return reference to output stream
            //!
            virtual std::ostream &write(std::ostream &os) const = 0;

            //-----------------------------------------------------------------
            //!
            //! \brief read data
            //!
            //! Read data from a standard C++ stream.
            //!
            //! \param is reference to input stream
            //! \return reference to input stream
            //!
            virtual std::istream &read(std::istream &is) = 0;

            //-----------------------------------------------------------------
            //!
            //! \brief clone yourself
            //!
            //! This member function clones the wrapped object. This is 
            //! particullary important when the resulting type earsure shall 
            //! be copied.
            //! 
            //! \return pointer to new interface instance
            //!
            virtual array_holder_interface *clone() const = 0;

            //-----------------------------------------------------------------
            //!
            //! \brief get type name 
            //! 
            //! Return the mangled name of the original type wrapped by the 
            //! type erasure.
            //!
            //! \return type name
            //!
            virtual string type_name() const = 0;

            //-----------------------------------------------------------------
            //! get element at linear index i
            virtual value operator[](size_t i) const = 0;

            //-----------------------------------------------------------------
            //! get reference to element at linear index i
            virtual value_ref operator[](size_t i) = 0;

            //-----------------------------------------------------------------
            //! get value at linear index i
            virtual value at(size_t i) const = 0;

            //-----------------------------------------------------------------
            //! get reference to value at linear index i
            virtual value_ref at(size_t i) = 0;

            //-----------------------------------------------------------------
            //! get pointer to data
            virtual const void *ptr() const = 0;

            //-----------------------------------------------------------------
            //! get element value
            virtual value operator()(const element_index &index) const = 0;

            //-----------------------------------------------------------------
            //! get element reference
            virtual value_ref operator()(const element_index &index)  = 0;

    };


//end of namespace
}
