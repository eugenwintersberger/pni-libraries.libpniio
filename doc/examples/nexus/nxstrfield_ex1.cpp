//nxstrfield_ex1.cpp

#include <pni/io/nx/nx.hpp>
#include <pni/core/types.hpp>

using namespace pni::io::nx::h5;
using namespace pni::core;

#include <iostream>

int main(int argc,char **argv){
    nxfile file = nxfile::create_file("nxstrfield_ex1.h5",true,0);

    nxfield field = file.create_field<string>("text");

    field.close();
    file.close();
}
