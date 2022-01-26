//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Sep 08, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <pni/types.hpp>
#include <pni/type_erasures.hpp>
#include <pni/windows.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>


namespace pni{

    //!
    //! \ingroup formatter_classes
    //! \brief describe numeric output format
    //!
    //! This class contains a set of parameters independent of the underlying
    //! output mechanism. It an be used to configure whatever method for
    //! writing numbers is used to so that the desired result can be achieved.
    //! qppq

    class format_config
    {
    private:
        bool   _always_sign;    //!< always show the sign
        size_t _minimum_width;  //!< the minimum widht (length) of the field
        size_t _precission;     //!< the numeric precision

    public:
    };

    template<typename T> struct format_str {};



    pni::string PNINEXUS_EXPORT format(const pni::uint8 &v);
    pni::string PNINEXUS_EXPORT format(const pni::int8 &v);
    pni::string PNINEXUS_EXPORT format(const pni::uint16 &v);
    pni::string PNINEXUS_EXPORT format(const pni::int16 &v);
    pni::string PNINEXUS_EXPORT format(const pni::uint32 &v);
    pni::string PNINEXUS_EXPORT format(const pni::int32 &v);
    pni::string PNINEXUS_EXPORT format(const pni::uint64 &v);
    pni::string PNINEXUS_EXPORT format(const pni::int64 &v);

    pni::string PNINEXUS_EXPORT format(const pni::float32 &v);
    pni::string PNINEXUS_EXPORT format(const pni::float64 &v);
    pni::string PNINEXUS_EXPORT format(const pni::float128 &v);

    pni::string PNINEXUS_EXPORT format(const pni::complex32 &v);
    pni::string PNINEXUS_EXPORT format(const pni::complex64 &v);
    pni::string PNINEXUS_EXPORT format(const pni::complex128 &v);

    pni::string PNINEXUS_EXPORT format(const pni::bool_t &v);
    pni::string PNINEXUS_EXPORT format(const pni::string &s);

    pni::string PNINEXUS_EXPORT format(const pni::value &v);
    pni::string PNINEXUS_EXPORT format(const pni::value_ref &v);

    pni::string PNINEXUS_EXPORT format(const hdf5::datatype::EBool &v);
}
