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
// Created on: Jan 9, 2018
//

#include <pni/types.hpp>
#include <pni/type_erasures.hpp>
#include <pni/parsers.hpp>
#include <pni/formatters.hpp>
#include <pni/container_io_config.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>

using namespace pni;

using Record = std::vector<core::value>;
using RecordParser = io::parser<Record>;
using Table = std::vector<Record>;

Table read_table(const boost::filesystem::path &file_path)
{
  std::ifstream stream(file_path.string());
  RecordParser parser;
  std::string line_buffer;
  Table table;

  while(!stream.eof())
  {
    std::getline(stream,line_buffer);
    table.push_back(parser(line_buffer));
  }

  return table;
}

int main(int argc,char **argv)
{
  boost::filesystem::path input_file;

  if(argc<=1)
  {
    std::cerr<<"You have to provide a path to an input file!"<<std::endl;
    return -1;
  }
  else
  {
    input_file = argv[1];
    std::cout<<"Reading data from "<<input_file<<std::endl;
  }

  Table input_records = read_table(input_file);

  std::cout<<"Got "<<input_records.size()<<" records"<<std::endl;

  io::container_io_config output_config('\t');
  std::for_each(input_records.begin(),input_records.end(),
                [&output_config](const Record &record)
                {
                  std::cout<<io::format(record,output_config)<<std::endl;
                });

  return 0;
}
