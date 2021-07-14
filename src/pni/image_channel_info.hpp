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
// Created on: Apr 23, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//

#pragma once

#include <pni/types.hpp>
#include <pni/windows.hpp>

namespace pni{

    //!
    //! \ingroup io_classes
    //! \brief image channel information class
    //! 
    //! image_channle_info holds information specific to a particular image 
    //! channel. 
    //!
    class PNINEXUS_EXPORT image_channel_info
    {
        private:
            pni::type_id_t _tid;  //!< ID of the datatype used for this channel
            size_t _bits; //!< number of bits per channel
        public:
            //-----------------------------------------------------------------
            //! default constructor
            image_channel_info():
                _tid(pni::type_id_t::NONE),
                _bits(0)
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief standard constructor
            //!
            //! \param id Typd id for the channel
            //! \param bits number of bits used to store channel data
            //!
            image_channel_info(const pni::type_id_t &id,size_t bits):
                _tid(id),
                _bits(bits)
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief get type ID
            //!
            //! Returns the TypeID for the channel described by this object.
            //! \return type ID 
            //!
            pni::type_id_t type_id() const { return _tid; }

            //-----------------------------------------------------------------
            //!
            //! \brief get bits 
            //!
            //! Return the number of bits used to store this channels data
            //! \return number of bits
            //!
            size_t bits() const { return _bits; }

    };

//end of namespace
}
