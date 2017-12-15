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
// Created on: Sep 12, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <sstream>
#include <pni/io/nexus/path/utils.hpp>
#include <pni/io/nexus/path/path.hpp>
#include <pni/io/nexus/path/make_relative.hpp>
#include <pni/core/error.hpp>


namespace pni{
namespace io{
namespace nexus{

Path make_relative(const Path &parent_path,const Path &orig_path)
{
  using namespace pni::core;

  if(!is_absolute(parent_path) || !(is_absolute(orig_path)))
    throw value_error(EXCEPTION_RECORD,
                      "Paths must be absolute!");

  if(parent_path.size()>orig_path.size())
    throw value_error(EXCEPTION_RECORD,
                      "The original path must be longer than the parent path!");


  if(parent_path.size()==orig_path.size())
    return Path::from_string(".");

  Path new_path(orig_path);
  new_path.filename(""); //reset the file name part
  for(size_t element_index = 0;
      element_index < parent_path.size();
      element_index++)
    new_path.pop_front();

  return new_path;
}

//--------------------------------------------------------------------------
Path make_relative(const std::string &parent_path,
                   const std::string &orig_string)
{
  return make_relative(Path::from_string(parent_path),
                       Path::from_string(orig_string));
}

//--------------------------------------------------------------------------
Path make_relative(const Path &parent_path,
                   const std::string &orig_path)
{
  return make_relative(parent_path,Path::from_string(orig_path));
}

//--------------------------------------------------------------------------
Path make_relative(const std::string &parent_path,
                     const Path &orig_path)
{
  return make_relative(Path::from_string(parent_path),orig_path);
}


} // namespace nexus
} // namespace io
} // namespace pni
