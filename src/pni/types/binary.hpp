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
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// 
// ============================================================================
//
// Created on: Feb 8, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once
#include <iostream>


namespace pni{

    //! 
    //! \ingroup  type_classes
    //! \brief Binary data type
    //! 
    //! This class represents a binary data type. Typically binary data is
    //! represented by a typedef to an unsigned char type.  However, this has 
    //! an inconvenience: the unsigned char and the typedef for binary are 
    //! indistinguishable by the compiler. Thus, such a binary type cannot be used
    //! for function overloading or for template specialization - it would always
    //! be treated by the compiler as the underlying unsigned char type.    
    //! 
    //! To circumvent this problem \c libpninexus defines this binary type which can
    //! be used instead of a simple typedef to unsigned char. The BinaryType
    //! template has several advantages: 
    //! 
    //! \li it can be distinguished from the type used to store binary data
    //! \li all arithmetic operators are stripped from the type.
    //!  
    //! Thus this type cannot be used for arithmetic operations directly. Its
    //! primary purpose is to hold uninterpreted binary data for transfer. 
    //! However it can be converted to the native type used to hold the data. 
    //! Stream operators are provided for IO operations using binary data. 
    //! 
    //! \tparam NTYPE native type used to store binary data
    //!
    template<typename NTYPE> class binary_t
    {
        public:
            //=================public data types===============================
            //! native type that is used for binary data
            typedef NTYPE storage_type;
        private:
            //! data value
            storage_type _value; 

            //! unary addition operator - deleted
            const binary_t<storage_type> & 
                operator+=(const binary_t<storage_type> &b) = delete;
            //! unary subtraction operator - delete
            const binary_t<storage_type> & 
                operator-=(const binary_t<storage_type> &b) = delete;
            //! unary multiplication operator
            const binary_t<storage_type> & 
                operator*=(const binary_t<storage_type> &b) = delete;
            //! unary division operator - delete
            const binary_t<storage_type> & 
                operator/=(const binary_t<storage_type> &b) = delete;
        public:

            //=============constructors and destructor=========================
            //! default constructor
            explicit binary_t():_value(storage_type(0)) {}

            //-----------------------------------------------------------------
            //! constructor
            binary_t(const storage_type &value):_value(value) {}

            //-----------------------------------------------------------------
            //! copy constructor
            binary_t(const binary_t<storage_type> &o):
                _value(o._value)
            {}
            binary_t<storage_type>& operator=(const binary_t<storage_type>&) = default;
            //-----------------------------------------------------------------
            //! conversion operator
            //! 
            //! Allows a conversion from BinaryType<NTYPE> to the underlying 
            //! NTYPE. 
            //!
            operator NTYPE() const
            {
                return _value;
            }

    };


    //! binary addition is deleted for BinaryType<NTYPE>
    template<typename NTYPE> binary_t<NTYPE> 
        operator+(const binary_t<NTYPE> &a,const binary_t<NTYPE> &b)
        = delete;

    //! binary subtraction is deleted for BinaryType<NTYPE>
    template<typename NTYPE> binary_t<NTYPE>
        operator-(const binary_t<NTYPE> &a,const binary_t<NTYPE> &b)
        =delete;

    //! binary multiplication is deleted for binary_t<NTYPE>
    template<typename NTYPE> binary_t<NTYPE>
        operator*(const binary_t<NTYPE> &a,const binary_t<NTYPE> &b)
        =delete;

    //! binary division is deleted for binary_t<NTYPE>
    template<typename NTYPE> binary_t<NTYPE>
        operator/(const binary_t<NTYPE> &a,const binary_t<NTYPE> &b)
        =delete;

    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief output stream operator for binary data
    //! 
    //! This is the overloaded output stream operator for binary data. 
    //! 
    //! \tparam NTYPE basic type for binary
    //! \param os reference to the output stream
    //! \param o reference to the binary object
    //! \return reference to the modified output stream
    //!
    template<typename NTYPE>
    std::ostream &operator<<(std::ostream &os,const binary_t<NTYPE> &o)
    {
        NTYPE b = o;
        os<<b;
        return os;
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief input stream operator for binary data
    //! 
    //! This is the overloaded input stream operator for binary data. 
    //! 
    //! \tparam NTYPE basic type for binary
    //! \param is reference to the input  stream
    //! \param o reference to the binary object
    //! \return reference to the modified input stream
    //!
    template<typename NTYPE>
    std::istream &operator>>(std::istream &is,binary_t<NTYPE> &o)
    {
        NTYPE b;
        is>>b;
        o = b;
        return is;
    }

//end of namespace
}
