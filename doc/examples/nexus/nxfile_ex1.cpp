//File: nxfile_ex1.cpp
#include <iostream>
#include <pni/io/nx/nx.hpp>  //include NXexus header file

using namespace pni::io::nx::h5; //switch to proper namespace

int main(int argc,char **argv){
    //create a file and overwrite an existing file with same name
    nxfile file = nxfile::create_file("file_ex1.h5",true,0);

    file.close(); //close the file
    return 0;
}
