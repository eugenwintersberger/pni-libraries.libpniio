//
// (c) Copyright 2018 DESY
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
// Created on: Jan 5, 2018
//

#include "thread_writer.hpp"
#include <pni/nexus.hpp>

using namespace pni::io;

void Writer::_write_entry(const std::string &s)
{
  //grow the data fields by one element
  _time.extent(0,1);
  _data.extent(0,1);
  _selection.offset(0,_index);


  //write the data
  _time.write(nexus::DateTime::get_date_time_str(),_selection);
  _data.write(s,_selection);
  _index++;

  //flush the new log entry
  _file.flush(hdf5::file::Scope::LOCAL);
}

void Writer::_init_log()
{
  //create log group
  auto g = _file.root().create_group("log");

  //create a field with holding the timestamp when the
  //log was created
  hdf5::dataspace::Simple space{{0},{hdf5::dataspace::Simple::UNLIMITED}};
  auto type = hdf5::datatype::create<std::string>();

  hdf5::node::Dataset(g,"create",type,hdf5::dataspace::Scalar()).write(nexus::DateTime::get_date_time_str());

  //create log data and timestamp field
  _data = nexus::FieldFactory::create(g,"data",type,space,{1024});
  _time = nexus::FieldFactory::create(g,"timestamp",type,space,{1024});
  _selection = hdf5::dataspace::Hyperslab({0},{1});

  //flush the file after initialization
  _file.flush(hdf5::file::Scope::LOCAL);
}

void Writer::operator()()
{
  std::cout<<"create file"<<std::endl;
  //works with HDF5
  _file = nexus::create_file(_filename,hdf5::file::AccessFlags::TRUNCATE);

  //initialize the log
  _init_log();

  //write an initial log entry
  _write_entry("Starting new log");

  while(true)
  {
    std::string log_entry;
    _queue.blocking_pop(log_entry);
    if(log_entry == "quit") break;
    try
    {
      _write_entry(log_entry);
    }
    catch(pni::core::shape_mismatch_error &e)
    {
      std::cout<<e<<std::endl;
      break;
    }
    _file.flush(hdf5::file::Scope::LOCAL);
  }


  //close the log file when finished
  _file.close();
}
