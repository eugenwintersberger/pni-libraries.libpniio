/*
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

