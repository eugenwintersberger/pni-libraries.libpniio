//File: nxgroup_ex1.cpp
#include<iostream>
#include<pni/io/nx/nx.hpp>
using namespace pni::io::nx::h5;

int main(int argc,char **argv)
{
    nxfile file  = nxfile::create_file("nxgroup_ex1.h5",true,0);
    nxgroup root = file.root();

    //create groups
    nxgroup group = root.create_group("data1");
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



