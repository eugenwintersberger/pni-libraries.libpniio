//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// ===========================================================================
//
// Created on: Sep 08, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/type_erasures.hpp>
#include <pni/windows.hpp>


namespace pni{
namespace io{

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



    pni::core::string PNIIO_EXPORT format(const pni::core::uint8 &v);
    pni::core::string PNIIO_EXPORT format(const pni::core::int8 &v);
    pni::core::string PNIIO_EXPORT format(const pni::core::uint16 &v);
    pni::core::string PNIIO_EXPORT format(const pni::core::int16 &v);
    pni::core::string PNIIO_EXPORT format(const pni::core::uint32 &v);
    pni::core::string PNIIO_EXPORT format(const pni::core::int32 &v);
    pni::core::string PNIIO_EXPORT format(const pni::core::uint64 &v);
    pni::core::string PNIIO_EXPORT format(const pni::core::int64 &v);

    pni::core::string PNIIO_EXPORT format(const pni::core::float32 &v);
    pni::core::string PNIIO_EXPORT format(const pni::core::float64 &v);
    pni::core::string PNIIO_EXPORT format(const pni::core::float128 &v);

    pni::core::string PNIIO_EXPORT format(const pni::core::complex32 &v);
    pni::core::string PNIIO_EXPORT format(const pni::core::complex64 &v);
    pni::core::string PNIIO_EXPORT format(const pni::core::complex128 &v);

    pni::core::string PNIIO_EXPORT format(const pni::core::bool_t &v);
    pni::core::string PNIIO_EXPORT format(const pni::core::string &s);

    pni::core::string PNIIO_EXPORT format(const pni::core::value &v);
    pni::core::string PNIIO_EXPORT format(const pni::core::value_ref &v);

}
}
