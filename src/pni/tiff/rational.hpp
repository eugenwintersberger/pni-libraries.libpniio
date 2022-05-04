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
// ===========================================================================
//
// Created on: Jun 17, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <iostream>
#include <pni/types.hpp>

namespace pni{
namespace tiff{


    //!
    //! \ingroup image_io_tiff
    //! \brief rational type for TIFF IFD entries
    //!
    //! IFD entries in TIFF files can consist of a rational number. This 
    //! class implements such a type as a template.
    //!
    template<typename T> class rational
    {
        protected:
            T _numerator;    //!< numerator of the rational number
            T _denominator;  //!< denominator of the rational number
        public:
            //=================constructors and destructor=================
            //! default constructor
            rational();
            //! copy constructor
            rational(const rational &o);
            //! standard constructor
            explicit rational(const T &,const T&);
            //! destructor
            ~rational(){}

            //====================conversion operator=======================
            //!
            //! \brief conversion operator
            //!
            //! This operator converts the rational number to a single 
            //! scalar value.  It will be typically used to convert from a 
            //! rational number to a floating point type. 
            //!
            template<typename ScalarT> operator ScalarT()
            {
                return (ScalarT)((ScalarT)(_numerator))/((ScalarT)(_denominator));
            }

            //================assignment operator===========================
            //! copy assignment operator
            virtual rational<T> &operator=(const rational<T> &r);

            //! set the numerator
            void numerator(const T &v) { _numerator = v; }
            //! get the numerator
            T numerator() const { return _numerator; } 

            //! set the denominator
            void denominator(T &v) { _denominator = v; }
            //! get the denominator
            T denominator() const { return _denominator; }

    };

    //=============implementation of template methods======================
    //implementation of the default constructor
    template<typename T> rational<T>::rational():
        _numerator(0),
        _denominator(0)
    { }

    //------------------------------------------------------------------------
    //implementation of the copy constructor
    template<typename T> rational<T>::rational(const rational<T> &r):
        _numerator(r._numerator),
        _denominator(r._denominator)
    { }

    //------------------------------------------------------------------------
    //implementation of the standard constructor
    template<typename T> rational<T>::rational(const T &n,const T &d):
        _numerator(n),
        _denominator(d)
    { }

    //------------------------------------------------------------------------
    //implementation of the copy assignment operator
    template<typename T> 
        rational<T> &rational<T>::operator=(const rational<T> &r)
    {
        if(this != &r){
            _numerator = r._numerator;
            _denominator = r._denominator;
        }
        return *this;
    }
    
    //------------------------------------------------------------------------
    //implementation of the output operator
    template<typename T> 
        std::ostream &operator<<(std::ostream &o,const rational<T> &r)
    {
        o<<r.numerator()<<"/"<<r.denominator();
        return o;
    }


    //some default types 
    typedef rational<pni::uint32> uirational;
    typedef rational<pni::int32> irational;

//end namespaces
}
}
