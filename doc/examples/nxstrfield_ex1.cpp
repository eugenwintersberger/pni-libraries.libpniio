//nxstrfield_ex1.cpp

#include <pni/io/nx/NX.hpp>
#include <pni/core/Types.hpp>

using namespace pni::io::nx::h5;
using namespace pni::core;

#include <iostream>

int main(int argc,char **argv){
    NXFile file = NXFile::create_file("nxstrfield_ex1.h5",true,0);

    NXField field = file.create_field<String>("text");

    field.close();
    file.close();
}
