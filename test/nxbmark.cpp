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

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/Array.hpp>

#include "NX.hpp"

using namespace pni::nx::h5;
using namespace pni::utils;


int main(int argc,char **argv){
	NXFile f;
	NXField d;
	UInt64 i,runs;
	String fname;
	ArrayShape s;
	Int32Array a;

	//create the array which should be stored
	s.setRank(2);
	s.setDimension(0,2048);
	s.setDimension(1,2048);
	a.setShape(s);
	a.allocate();
	a = 1;
	a.setName("data");
	a.setUnit("a.u.");
	a.setDescription("testing data");

	f.setFileName("bmark.h5");
	f.setOverwrite(true);	;
	f.create();

	d = f.createNumericField(a);

	runs = 500;
	for(i=0;i<runs;i++){
		d<<a;
		f.flush();
	}

	//close the datafile
	f.close();


	return 0;
}

