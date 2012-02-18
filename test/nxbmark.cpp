/*
 * Declaration of Nexus object template.
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * nxbmark.cpp
 *
 *  Created on: Jul 6, 2011
 *      Author: Eugen Wintersberger
 *
 *  A benchmark program for the Nexus API. This program shall show how
 *  much overhead is introduced by the API code in comparison to plain HDF5.
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>

#include "NX.hpp"

using namespace pni::nx::h5;
using namespace pni::utils;


int main(int argc,char **argv){
	size_t i,runs;
    //set shape for the array to write
	Shape s = {2048,2048};

	//create the array which should be stored
    Int32Array a(s,"data","a.u.","testing data");
    a = 1;

    //create data file where to store data
    NXFile file = NXFile::create_file("bmark.h5",true,0);

    //create the field where to store the data
    //and a selection to access individual frames
    NXField field = file.create_field<Int32>("data",{0,2048,2048});
    NXSelection sel = field.selection();
    
    //setup selection object
    sel.offset({0,0,0});
    sel.count({1,2048,2048});
    
	runs =100 ;
	for(i=0,field.grow(0);i<runs;i++,field.grow(0)){
        std::cout<<"Writing frame number "<<i<<std::endl;
        sel.write(a);
        sel.offset(0,i);
		file.flush();
	}

	//close the datafile
	file.close();


	return 0;
}

