//
// (c) Copyright 2018 DESY
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
// Created on: Jan 3, 2018
//

#include <pni/nexus/field_factory.hpp>
#include <pni/nexus/predicates.hpp>

namespace pni {
namespace nexus {

hdf5::node::Dataset FieldFactory::create(const hdf5::node::Group &parent,
                                         const hdf5::Path &path,
                                         const hdf5::datatype::Datatype &type,
                                         const hdf5::dataspace::Dataspace &space,
                                         const hdf5::property::LinkCreationList &lcpl,
                                         const hdf5::property::DatasetCreationList &dcpl,
                                         const hdf5::property::DatasetAccessList &acpl)
{
  IsValidNeXusName name_check;
  if(!name_check(path.name()))
  {
    std::stringstream ss;
    ss<<"Cannot create dataset ["<<path<<"] below ["<<parent.link().path()<<"]"
        <<" as its name does not comply to the NeXus naming convention!";
    throw std::runtime_error(ss.str());
  }
  return hdf5::node::Dataset(parent,path,type,space,lcpl,dcpl,acpl);
}

hdf5::node::Dataset FieldFactory::create(const hdf5::node::Group &parent,
                                         const hdf5::Path &path,
                                         const hdf5::datatype::Datatype &type,
                                         const hdf5::dataspace::Simple &space,
                                         const hdf5::Dimensions &chunk_shape,
                                         const hdf5::property::LinkCreationList &lcpl,
                                         const hdf5::property::DatasetCreationList &dcpl,
                                         const hdf5::property::DatasetAccessList &acpl)
{
  hdf5::property::DatasetCreationList chunk_dcpl(dcpl);
  chunk_dcpl.layout(hdf5::property::DatasetLayout::CHUNKED);
  chunk_dcpl.chunk(chunk_shape);

  IsValidNeXusName name_check;
  if(!name_check(path.name()))
  {
    std::stringstream ss;
    ss<<"Cannot create chunked dataset ["<<path<<"] below ["<<parent.link().path()<<"]"
        <<" as its name does not comply to the NeXus naming convention!";
    throw std::runtime_error(ss.str());
  }

  return hdf5::node::Dataset(parent,path,type,space,lcpl,chunk_dcpl,acpl);

}


} // namespace nexus
} // namespace pni
