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
#include <pni/io/nexus/containers.hpp>
#include <algorithm>

namespace pni {
namespace io {
namespace nexus {

bool is_resolvable(const hdf5::node::Link &link)
{
  try
  {
    *link;
    return true;
  }
  catch(...)
  {
    return false;
  }
}

class AbsolutePathMatcher
{
  public:
    AbsolutePathMatcher(const Path &path):
      path_(path)
    {}

    bool operator()(const hdf5::node::Link &link) const
    {
      Path path;
      if(!is_resolvable(link))
        path = get_path(link);
      else
        path = get_path(*link);

      bool result = match(path,path_);
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

    bool operator()(const hdf5::node::Link &link) const
    {
      Path path;
      if(!is_resolvable(link))
        path = get_path(link);
      else
        path = get_path(*link);

      path = make_relative(base_path_,path);
      return match(path,path_);
    }

  private:
    Path path_;
    Path base_path_;
};

PathObjectList get_objects(const hdf5::node::Group &base,const Path &path)
{
  PathObjectList list;

  if(path.has_attribute())
  {
    //if we are looking for attributes we first have to identify the parent
    //objects.
    Path parent_path(path);
    parent_path.attribute(std::string());
    NodeList parent_list = get_objects(base,parent_path);

    //once we have identified the parents we can select those who have
    //an attribute of appropriate name
    for(auto node: parent_list)
    {
      if(node.attributes.exists(path.attribute()))
        list.push_back(node.attributes[path.attribute()]);
    }

  }
  else
  {
    auto iter_begin = hdf5::node::RecursiveLinkIterator::begin(base);
    auto iter_end = hdf5::node::RecursiveLinkIterator::end(base);

    if(is_absolute(path))
      std::copy_if(iter_begin,iter_end,std::back_inserter(list),AbsolutePathMatcher(path));
    else
      std::copy_if(iter_begin,iter_end,std::back_inserter(list),RelativePathMatcher(path,get_path(base)));
  }

  return list;
}

} // namespace nexus
} // namespace io
} // namespace pni
