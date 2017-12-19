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
// Created on: Dec 18, 2017
//
#include <pni/io/nexus/path/utils.hpp>
#include <pni/io/nexus/path/make_relative.hpp>
#include <algorithm>

namespace pni {
namespace io {
namespace nexus {

class AbsolutePathMatcher
{
  public:
    AbsolutePathMatcher(const Path &path):
      path_(path)
    {}

    bool operator()(const hdf5::node::Node &node) const
    {
      Path node_path = get_path(node);
      bool result = match(node_path,path_);
      return result;
    }

  private:
    Path path_;
};

class RelativePathMatcher
{
  public:
    RelativePathMatcher(const Path &path,const Path &base_path):
      path_(path),
      base_path_(base_path)
    {}

    bool operator()(const hdf5::node::Node &node) const
    {
      Path node_path = make_relative(base_path_,get_path(node));
      return match(node_path,path_);
    }

  private:
    Path path_;
    Path base_path_;
};

PathObjectList get_objects(const hdf5::node::Group &base,const Path &path)
{
  PathObjectList list;

  auto iter_begin = hdf5::node::RecursiveNodeIterator::begin(base);
  auto iter_end = hdf5::node::RecursiveNodeIterator::end(base);

  if(is_absolute(path))
    std::copy_if(iter_begin,iter_end,
                 std::back_inserter(list),
                 AbsolutePathMatcher(path));
  else
    std::copy_if(iter_begin,iter_end,
                 std::back_inserter(list),
                 RelativePathMatcher(path,get_path(base)));

  return list;
}

} // namespace nexus
} // namespace io
} // namespace pni
