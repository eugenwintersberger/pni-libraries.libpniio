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
// Created on: Jan 5, 2018
//
#pragma once

#include <h5cpp/hdf5.hpp>
#include <h5cpp/core/filesystem.hpp>
#include "thread_ex1.hpp"

class Writer
{
  private:
    fs::path _filename;
    StringIOQueue          &_queue;
    hdf5::file::File        _file;
    hdf5::node::Dataset     _data;
    hdf5::node::Dataset     _time;
    hdf5::dataspace::Hyperslab _selection;
    size_t _index;

    //private method writing a single log entry
    void _write_entry(const std::string &s);

    //method creating the initial structure of the log
    void _init_log();
  public:
    Writer(const fs::path &fname,StringIOQueue &q):
      _filename(fname),
      _queue(q),
      _file(),
      _data(),
      _selection(),
      _index(0)
    { }

    void operator()();
};
