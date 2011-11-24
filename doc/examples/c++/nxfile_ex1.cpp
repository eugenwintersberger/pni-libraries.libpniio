//File: nxfile_ex1.cpp
#include <iostream>

//include NX.hpp header and switch to HDF5 Nexus namespace
#include <pni/nx/NX.hpp>
using namespace pni::nx::h5;

int main(int argc,char **argv){
	NXFile file;

	file.setFileName("file_ex1.h5");  //set the filename
	file.setOverwrite(true);          //file should be overwritten
	file.create();    //create the file
	file.close();     //close the file

	file.setReadOnly(true);  //reopen the file in read only mode
	file.open();
	file.close();

	file.setReadOnly(false); //open the file for writing
	file.open();
	file.close();

	return 0;
}
