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
// Created on: Apr 23, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

namespace pni{
namespace cbf{

    //!
    //! \ingroup image_io_cbf
    //! \brief CBF compression id
    //!
    enum class compression_id { CBFByteOffset };

    //!
    //! \ingroup image_io_cbf
    //! \brief CBF vendor id
    //!
    enum class vendor_id { Dectris };

//end of namespace
}
}
