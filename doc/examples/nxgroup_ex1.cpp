//File: nxgroup_ex1.cpp
#include<iostream>
#include<pni/io/nx/NX.hpp>
using namespace pni::io::nx::h5;

int main(int argc,char **argv){
    NXFile file = NXFile::create_file("nxgroup_ex1.h5",true,0);

    //create groups
    NXGroup group = file.create_group("data1");
    group = group.create_group("dir");
    group = file.create_group("data2","NXentry");
    group = file.create_group("data3/detector/data","NXdata");

    //open existing groups
    group = file.open("data1");
    group = group.open("dir");

    //open an existing group using [] operator
    group = file["/data3/detector/data"];

    file.close(); //close the file
    return 0;
}



