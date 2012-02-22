//File: nxfile_ex1.cpp
#include <iostream>

//include NX.hpp header and switch to HDF5 Nexus namespace
#include <pni/nx/NX.hpp>
using namespace pni::nx::h5;

int main(int argc,char **argv){
    //create a file and overwrite an existing file 
    //with same name
	NXFile file = NXFile::create_file("file_ex1.h5",true,0);

    file.close();

	return 0;
}
