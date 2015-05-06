//File: nxgroup_ex1.cpp
#include<iostream>
#include<pni/io/nx/nx.hpp>
#include<pni/io/nx/algorithms.hpp>

using namespace pni::core;
using namespace pni::io::nx;

int main(int argc,char **argv)
{
    h5::nxfile file  = h5::nxfile::create_file("nxgroup_ex1.h5",true);
    h5::nxgroup root = file.root();

    //create groups
    h5::nxgroup group = root.create_group("data1");
    group = group.create_group("dir");
    group = root.create_group("data2","NXentry");
    group = root.create_group("data3","NXentry").
                 create_group("detector","NXdetector").
                 create_group("data","NXdata");

    //open existing groups
    group = root.at("data1");
    group = group.at("dir");

    //open an existing group using [] operator
    group = get_object(root,"/data3/detector/data");

    file.close(); //close the file
    return 0;
}



