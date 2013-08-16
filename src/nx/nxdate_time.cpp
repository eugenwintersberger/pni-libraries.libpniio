/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * NXDateTime.cpp
 *
 *  Created on: Nov 17, 2011
 *      Author: eugen
 */

#include <pni/io/nx/nxdate_time.hpp>

namespace pni {
namespace io {
namespace nx {

    //---------------------------------------------------------------------
    string nxdate_time::__get_utc_delta()
    {
        typedef boost::date_time::c_local_adjustor<ptime> local_adj;
        //get utc time
        ptime utc_time    = microsec_clock::universal_time();
        //convert universal time to local time
        ptime system_time = local_adj::utc_to_local(utc_time);
        //compute difference between universal time and local
        //time
        time_duration delta = system_time - utc_time;
       
        //assemble ouput string
        char buffer[1024];
        std::sprintf(buffer,"%+03li00",(long)delta.hours());

        return string(buffer);
    }

    //---------------------------------------------------------------------
    string nxdate_time::__get_date_time_str(const ptime &t)
    {

        string dtime = to_iso_extended_string(t);
        string utc_delta = __get_utc_delta();
        return dtime+utc_delta;
    }

    //---------------------------------------------------------------------
    string nxdate_time::get_date_time_str(){
        ptime t = microsec_clock::local_time();
        return __get_date_time_str(t);

    }

    //---------------------------------------------------------------------
    string nxdate_time::get_date_time_str(const time_t &t)
    {
        return __get_date_time_str(from_time_t(t));
    }

//end of namespace
}
}
}
