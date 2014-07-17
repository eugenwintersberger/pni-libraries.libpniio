//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// ==========================================================================
//
//  Created on: Jul 17, 2011
//      Author: Eugen Wintersberger
//
#pragma once

#include <pni/core/types.hpp>
#include "h5filter.hpp"


namespace pni {
namespace io {
namespace nx {
namespace h5 {

    using namespace pni::core;
    using pni::core::string;

    //! 
    //! \ingroup nxh5_classes
    //! \brief HDF5 deflate filter
    //!
    //! Implementation of the deflate (ZLIB) filter for HDF5.  This is most 
    //! probably the simplest filter available for HDF5. The only parameter 
    //! that can be configured for this filter is the compression ration which 
    //! can take a value from 0 to 9. In addition a shuffle filter can be used 
    //! in advance in order to achieve better compression ratios.
    //!
    class h5deflate_filter:public h5filter 
    {
        private:
            uint32 _comp_rate;   //!< compression rate
            bool   _shuffle;     //!< shuffle flag
        public:
            //====================constructor and destructor===================
            //! 
            //! \brief default constructor
            //! 
            explicit h5deflatefilter();

            //-----------------------------------------------------------------
            //! 
            //! \brief copy constructor
            //! 
            h5deflate(const H5DeflateFilter &);

            //-----------------------------------------------------------------
            //! 
            //! \brief move constructor
            //! 
            H5DeflateFilter(H5DeflateFilter &&o);

            //-----------------------------------------------------------------
            //! 
            //! \brief constructor
            //! 
            H5DeflateFilter(uint32 rate,bool shuffle);

            //-----------------------------------------------------------------
            //! 
            //! \brief destructor
            //! 
            virtual ~H5DeflateFilter();
           
            //=================assigment operators=============================
            //! 
            //! \brief copy assignment operator
            //! 
            H5DeflateFilter &operator=(const H5DeflateFilter &o);

            //-----------------------------------------------------------------
            //! 
            //! \brief move assignment operator
            //! 
            H5DeflateFilter &operator=(H5DeflateFilter &&o);
           
            //===================public member functions=======================
            //! 
            //! \brief setup the filter
            //! 
            virtual void setup(hid_t id) const;
           
            //-----------------------------------------------------------------
            //! 
            //! \brief get compression rate
            //!
            //! Returns the value of the compression rate.
            //!
            //! \return compression rate
            //!
            uint32 compression_rate() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief set compression rate
            //!
            //! Sets the compression rate. The value must be between 0 and 9. 
            //! If the a higher value is passed an H5FilterError will be 
            //! thrown.
            //!
            //! \param r compression rate (between 0 and 9).
            //!
            void compression_rate(uint32 r);

            //-----------------------------------------------------------------
            //!
            //! \brief active shuffle filter
            //!
            //! If this option is set the shuffle filter will be activated in
            //! advance of the defalte filter. This can lead to higher 
            //! compression ratios.
            //!
            //! \param value true/false use/not use shuffle filter
            //!
            void shuffle(bool value);

            //-----------------------------------------------------------------
            //! 
            //! \brief get shuffle status
            //!
            //! Returns the value of the shuffle flag. If true shuffle filter 
            //! is used before deflate. Flase otherwise.
            //!
            //! \return shuffle flag status
            //!
            bool shuffle() const;
    };


//end of namespace
}
}
}
}
