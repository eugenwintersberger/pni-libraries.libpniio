//nxstrfield_ex1.cpp

#include <pni/nx/NX.hpp>
#include <pni/utils/Types.hpp>

using namespace pni::nx::h5;
using namespace pni::utils;

#include <iostream>

int main(int argc,char **argv){
    NXFile file = NXFile::create_file("nxstrfield_ex1.h5",true,0);

    NXField field = file.create_field<String>("text");

    field.close();
    file.close();
}
