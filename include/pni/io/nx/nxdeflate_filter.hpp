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
// ===========================================================================
//
// Created on: Feb 16, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "nxfilter.hpp"

namespace pni{
namespace io {
namespace nx{
    //need this here to avoid name collisions with tango headers.
    using pni::core::array;
    using pni::core::string;
    using pni::core::exception;

    //!
    //! \ingroup nexus_lowlevel
    //! \brief Nexus deflate filter
    //!
    //! This class provides an implementation of the simple deflate filter as 
    //! it is implemented in zlib. 
    //!
    template<typename FIMP> 
    class nxdeflate_filter:public nxfilter<FIMP>
    {
        public:
            typedef FIMP imp_type;
            typedef nxdeflate_filter<FIMP> filter_type;
            //====================constructors and destructor==================
            //!
            //! \brief default constructor
            //!
            explicit nxdeflate_filter() noexcept:nxfilter<FIMP>() { }

            //-----------------------------------------------------------------
            //!
            //! \brief standard constructor
            //!
            explicit nxdeflate_filter(uint32 r,bool s) noexcept:
                nxfilter<FIMP>(imp_type(r,s))
            { }

            //-----------------------------------------------------------------
            //!
            //! \brief destructor
            //!
            ~nxdeflate_filter() { }

            //==============filter attribute access methods====================
            //!
            //! \brief set compression rate
            //!
            //! Sets the compression rate for the deflate filter. This 
            //! parameter can take values from 0 to 9. 
            //!
            //! \throws range_error if r is not between 0 and 9
            //!
            //! \param r compression ratio
            //! 
            void compression_rate(uint32 r)
            {
                this->imp().compression_rate(r);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get compression rate
            //!
            uint32 compression_rate() const noexcept
            {
                return this->imp().compression_rate();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief set shuffle 
            //!
            //! \param s boolean parameter switching shuffle on or of
            //!
            void shuffle(bool s) noexcept
            {
                this->imp().shuffle(s);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get shuffle flag
            //!
            bool shuffle() const noexcept
            {
                return this->imp().shuffle();
            }

    };

//end of namespace
}
}
}

