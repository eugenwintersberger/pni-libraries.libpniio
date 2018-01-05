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

#include "thread_clireader.hpp"

CliReader::CliReader(const std::string &prompt,StringIOQueue &q):
_prompt(prompt),
_queue(q)
{ }

void CliReader::operator()()
{
  std::string input;
  while(true)
  {
    std::cout<<_prompt;
    std::getline(std::cin,input);
    _queue.push(input);
    if(input=="quit") break;
  }
}
