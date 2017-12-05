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
//  Created on: Nov 17, 2011
//      Author: Eugen Wintersberger
//

#pragma once

#include <ctime>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <pni/core/types.hpp>
#include <pni/io/windows.hpp>

namespace pni {
namespace io {
namespace nx {    
  
    
    //! 
    //! \ingroup nexus_lowlevel
    //! \brief date time factory
    //!
    //! nxdate_time provides static methods to create date-time strings which 
    //! are compliant to the Nexus standard. It is highly important for this 
    //! class to work properly that the time zone setup is correct.  
    //! Time-zone information can come either directly from the host machine 
    //! the program is running on or can be configured manually if this setup 
    //! is not correct. 
    //!
    class PNIIO_EXPORT nxdate_time 
    {
        private:
            //! get date time from ptime 
            static pni::core::string __get_date_time_str(const boost::posix_time::ptime &t);
            //! get delta to UTC as a string
            static pni::core::string __get_utc_delta();
        public:
            //-----------------------------------------------------------------
            //! 
            //! \brief date-time now
            //!
            //! Returns a string with a Nexus compliant date-time string for 
            //! now.
            //!
            //! \return Nexus date-time string
            //!
            static pni::core::string get_date_time_str();

            //-----------------------------------------------------------------
            //! 
            //! \brief date-time at t
            //!
            //! Converts a given time in time_t format to a Nexus date-time 
            //! string.
            //!
            //! \param t time as time_t
            //! \return Nexus date-time string
            //!
            static pni::core::string get_date_time_str(const time_t &t);
    };

//end of namepsace
} 
}
}
