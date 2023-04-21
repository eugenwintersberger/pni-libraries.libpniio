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

#include <pni/nexus/file.hpp>
#include <pni/nexus/version.hpp>
#include <pni/nexus/date_time.hpp>
#include <h5cpp/core/filesystem.hpp>

#include <sstream>
#include <stdexcept>


using namespace hdf5;
using namespace boost;

//
// Utility functions - kept in a anonymous namespace to avoid exporting them
// to the ABI of the library
//
namespace {

void write_nexus_file_attribute(const node::Group &root_group,
                                const std::string &attribute_name,
                                const std::string &attribute_value)
{
  auto type = datatype::create<std::string>();
  dataspace::Scalar space;

  root_group.attributes.create(attribute_name,type,space).write(attribute_value);
}

}

//
// Official functions exported to the ABI of the library
//
namespace pni {
namespace nexus {


file::File create_file(const fs::path &path,file::AccessFlags flags,
                        const property::FileCreationList &fcpl,
                        const property::FileAccessList &fapl)
{
  return create_file(path,static_cast<file::AccessFlagsBase>(flags),fcpl,fapl);
}

file::File create_file(const fs::path &path,
                        file::AccessFlagsBase flags,
                        const property::FileCreationList &fcpl,
                        const property::FileAccessList &fapl)
{
  //
  // Creating a new HDF5 file and obtain the new root group
  //
  file::File nexus_file;
  try
  {
    nexus_file = file::create(path,flags,fcpl,fapl);
  }
  catch(const std::runtime_error &error)
  {
    std::stringstream ss;
    ss<<"Failure to create NeXus file"<<std::endl;
    ss<<error.what();
    throw std::runtime_error(ss.str());
  }

  node::Group root_group = nexus_file.root();

  //
  // get the version of the underlying HDF5 library
  //
  unsigned major = 0,minor = 0,rel = 0;
  H5get_libversion(&major,&minor,&rel);
  std::string hdf5_version =  Version::to_string(Version(major,minor,rel));


  //
  // set the root group attributes required by the NeXus standard
  //
  try
  {
    write_nexus_file_attribute(root_group,"HDF5_Version",hdf5_version);
    write_nexus_file_attribute(root_group,"NX_class","NXroot");
    write_nexus_file_attribute(root_group,"file_time",DateTime::get_date_time_str());
    write_nexus_file_attribute(root_group,"file_update_time",DateTime::get_date_time_str());
    write_nexus_file_attribute(root_group,"file_name",path.string());
  }
  catch(const std::runtime_error &error)
  {
    std::stringstream ss;
    ss<<"Failure to set NeXus file attributes during creation of file: "
      <<path<<"!";
    ss<<error.what();
    throw std::runtime_error(ss.str());
  }

  return nexus_file;
}

bool is_nexus_file(const fs::path &path)
{
  if(!file::is_hdf5_file(path))
  {
    return false;
  }

  //
  // open the file
  //
  file::File hdf5_file = file::open(path);
  node::Group root_group = hdf5_file.root();

  //
  // check if all required attributes exist
  //
  if (!(root_group.attributes.exists("NX_class") &&
        root_group.attributes.exists("file_time") &&
        root_group.attributes.exists("file_update_time") &&
        root_group.attributes.exists("file_name")))
  {
    return false;
  }

  //
  // check if certain attributes have appropriate values
  // - currently this is only the NX_class attribute
  std::string base_class;
  root_group.attributes["NX_class"].read(base_class);
  return base_class == "NXroot";
}

file::File open_file(const fs::path &path,
                      file::AccessFlags flags,
                      const property::FileAccessList &fapl)
{
  return open_file(path,static_cast<file::AccessFlagsBase>(flags),fapl);
}


file::File open_file(const fs::path &path,
                file::AccessFlagsBase flags,
                const property::FileAccessList &fapl)
{
  if(!is_nexus_file(path))
  {
    std::stringstream ss;
    ss<<"File "<<path<<" is not a NeXus file!";
    throw std::runtime_error(ss.str());
  }

  return file::open(path,flags,fapl);
}


}
}
