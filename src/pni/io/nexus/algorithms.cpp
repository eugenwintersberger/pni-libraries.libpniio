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
// Created on: Dec 8, 2017
//

#include <pni/io/nexus/algorithms.hpp>
#include <algorithm>
#include <functional>

namespace {



}



namespace pni {
namespace io {
namespace nexus {

template<typename ITERT>
NodeList search_(ITERT begin,ITERT end,
                                 const NodePredicate &predicate)
{
  pni::io::nexus::NodeList result;
  std::copy_if(begin,end,std::back_inserter(result),std::cref(predicate));
  return result;
}

NodeList search(const hdf5::node::Group &base,
                const NodePredicate &predicate,
                bool recursive)
{
  using hdf5::node::RecursiveNodeIterator;
  using hdf5::node::NodeIterator;

  if(recursive)
  {
    return search_(RecursiveNodeIterator::begin(base),
                   RecursiveNodeIterator::end(base),
                   predicate);
  }
  else
  {
    return search_(NodeIterator::begin(base),
                   NodeIterator::end(base),
                   predicate);
  }
}


} // namespace nexus
} // namespace io
} // namespace pni
