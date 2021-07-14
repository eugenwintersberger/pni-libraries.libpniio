//
// (c) Copyright 2017 DESY
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Dec 6, 2017
//

#include <pni/nexus/version.hpp>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <stdexcept>

static const boost::regex version_regexp("(?<MAJOR>\\d+)((\\.(?<MINOR>\\d+))(\\.(?<PATCH>\\d+))?)?");

namespace pni {
namespace io {
namespace nexus {

Version::Version() noexcept:
    major_(0),
    minor_(0),
    patch_(0)
{}

Version::Version(NumberType major,NumberType minor,NumberType patch) noexcept:
    major_(major),
    minor_(minor),
    patch_(patch)
{}

Version::NumberType Version::major() const noexcept
{
  return major_;
}

Version::NumberType Version::minor() const noexcept
{
  return minor_;
}

Version::NumberType Version::patch() const noexcept
{
  return patch_;
}

Version::NumberType Version::get_number_from_part(const boost::smatch &match,
                                                  const std::string &part_name)
{
  std::string part = match.str(part_name);
  NumberType value = 0;
  if(!part.empty())
  {
    try
    {
      value =  boost::lexical_cast<NumberType>(part);
    }
    catch(...)
    {
      std::stringstream ss;
      ss<<"Failure to read version part ["<<part_name<<"]!";
      throw std::runtime_error(ss.str());
    }
  }

  return value;

}

Version Version::from_string(const std::string &str)
{
  boost::regex re(version_regexp);
  boost::smatch result;
  if(boost::regex_match(str,result,re))
  {
    try
    {
      NumberType major_number = get_number_from_part(result,"MAJOR");
      NumberType minor_number = get_number_from_part(result,"MINOR");
      NumberType patch_number = get_number_from_part(result,"PATCH");

      return Version(major_number,minor_number,patch_number);
    }
    catch(const std::runtime_error &error)
    {
      //for whatever reason, parsing of the individual numbers faild
      //we thus rethrow the original exception.
      std::stringstream ss;
      ss<<"Failure to read version from ["<<str<<"]!"<<std::endl
        <<error.what();
      throw std::runtime_error(ss.str());
    }
  }
  else
  {
    //the entire parsing failed - we can throw an exception here.
    std::stringstream ss;
    ss<<"Error reading version number for string ["<<str<<"]!"<<std::endl
      <<"Pleas check format specification!";
    throw std::runtime_error(ss.str());
  }

  return Version();
}

std::string Version::to_string(const Version &version)
{
  std::stringstream ss;
  ss<<version.major()<<"."<<version.minor()<<"."<<version.patch();
  return ss.str();
}

bool operator==(const Version &lhs,const Version &rhs)
{
  return (lhs.major() == rhs.major()) &&
         (lhs.minor() == rhs.minor()) &&
         (lhs.patch() == rhs.patch());
}

bool operator!=(const Version &lhs,const Version &rhs)
{
  return !(lhs==rhs);
}

bool operator<=(const Version &lhs,const Version &rhs)
{
  return (rhs==lhs)||(lhs<rhs);
}

bool operator<(const Version &lhs,const Version &rhs)
{
  if(lhs.major()<rhs.major())
    return true;

  if(lhs.minor() < rhs.minor())
    return true;

  if(lhs.patch() < rhs.patch())
    return true;

  return false;
}

bool operator>=(const Version &lhs,const Version &rhs)
{
  return (lhs==rhs) || (lhs>rhs);
}

bool operator>(const Version &lhs,const Version &rhs)
{
  if(lhs.major() > rhs.major())
    return true;

  if(lhs.minor() > rhs.minor())
    return true;

  if(lhs.patch() > rhs.patch())
    return true;

  return false;
}

std::ostream &operator<<(std::ostream &stream,const Version &v)
{
  return stream<<Version::to_string(v);
}

std::istream &operator>>(std::istream &stream,Version &v)
{
  std::string buffer;
  stream>>buffer;
  v = Version::from_string(buffer);
  return stream;
}

} // namespace nexus
} // namespace io
} // namespace pni
