//
// (c) Copyright 2017 DESY
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Dec 7, 2017
//

#include <pni/nexus/date_time.hpp>
#include <boost/date_time/local_time_adjustor.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>

namespace pni {
namespace io {
namespace nexus {

//---------------------------------------------------------------------
std::string DateTime::__get_utc_delta()
{
  using namespace boost::posix_time;
  using namespace boost::gregorian;

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

  return std::string(buffer);
}

//---------------------------------------------------------------------
std::string DateTime::__get_date_time_str(const boost::posix_time::ptime &t)
{

  std::string dtime = to_iso_extended_string(t);
  std::string utc_delta = __get_utc_delta();
  return dtime+utc_delta;
}

//---------------------------------------------------------------------
std::string DateTime::get_date_time_str()
{
  using namespace boost::posix_time;
  using namespace boost::gregorian;

  ptime t = microsec_clock::local_time();
  return __get_date_time_str(t);

}

//---------------------------------------------------------------------
std::string DateTime::get_date_time_str(const time_t &t)
{
  using namespace boost::posix_time;
  using namespace boost::gregorian;
  return __get_date_time_str(from_time_t(t));
}


} // namespace nexus
} // namespace io
} // namespace pni
