//File: nxfile_ex2.cpp
#include <iostream>

//include NX.hpp header and switch to HDF5 Nexus namespace
#include <pni/nx/NX.hpp>
using namespace pni::nx::h5;

int main(int argc,char **argv){
	NXFile file;

	file.setFileName("file_ex2.h5");  //set the filename
	file.setOverwrite(true);          //file should be overwritten
	file.create();    //create the file

	String fname = file.getFileName();
	if(file.isOverwrite()) std::cout<<"File "+fname+" is in overwrite mode!"<<std::endl;
	if(file.isReadOnly()) std::cout<<"File "+fname+" is read-only!"<<std::endl;
	if(file.isOpen()) std::cout<<"File "+fname+"is open!"<<std::endl;

	file.close();
	return 0;
}



