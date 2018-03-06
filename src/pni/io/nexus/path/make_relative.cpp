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

namespace {

  void verify_input_paths(const pni::io::nexus::Path &parent_path,
                          const pni::io::nexus::Path &orig_path)
  {
    std::stringstream error_message;

    if(!is_absolute(parent_path))
    {
      error_message<<"Error in pni::io::nexus::make_relative: ";
      error_message<<"parent_path ["<<parent_path<<"] is not absolute";
      throw std::runtime_error(error_message.str());
    }

    if(!is_absolute(orig_path))
    {
      error_message<<"Error in pni::io::nexus::make_relative: ";
      error_message<<"orig_path ["<<orig_path<<"] must be absolute";
      throw std::runtime_error(error_message.str());
    }

    if(parent_path.size()>orig_path.size())
    {
      error_message<<"Error in pni::io::nexus::make_relative: ";
      error_message<<"parent_path ["<<parent_path
                   <<"] is longer than orig_path ["<<orig_path<<"]!";
      throw std::runtime_error(error_message.str());
    }
  }

}

namespace pni{
namespace io{
namespace nexus{



Path make_relative(const Path &parent_path,const Path &orig_path)
{
  using namespace pni::core;

  //
  // check if the paths satisfy the requirements
  //
  verify_input_paths(parent_path,orig_path);

  Path new_path;
  if(parent_path.size()==orig_path.size())
  {
    // if boths paths have the same length we denote a dot here
    new_path = Path();
  }
  else
  {
    new_path = Path(orig_path);
    new_path.filename(""); //reset the file name part
    for(size_t element_index = 0;
        element_index < parent_path.size();
        element_index++)
      new_path.pop_front();
  }

  //
  // copy attribute section
  //
  new_path.attribute(orig_path.attribute());

  return new_path;
}


} // namespace nexus
} // namespace io
} // namespace pni
