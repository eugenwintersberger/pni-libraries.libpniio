//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//
// ===========================================================================
//
// Created on: Mar 13, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

//-----------------------------------------------------------------------------
// This example shows how to implement a simple file copy. 
//-----------------------------------------------------------------------------

#include <vector>
#include <fstream>
#include <pni/types.hpp>

using namespace pni;

typedef std::vector<binary> binary_vector;

int main(int ,char **)
{
    //open the input file
    std::ifstream i_stream("Makefile",std::fstream::binary);

    //determine the length of the file
    size_t length = i_stream.seekg(0,std::ifstream::end).tellg();
    i_stream.seekg(0,std::ifstream::beg);

    //allocate memory
    binary_vector data(length); 

    //read data
    i_stream.read(reinterpret_cast<char*>(data.data()),length);
    //close input file
    i_stream.close();

    //open output file
    std::ofstream o_stream("Makefile.copy",std::fstream::binary);
    o_stream.write(reinterpret_cast<char*>(data.data()),length);
    //close the output stream
    o_stream.close();
    
    return 0;
}

