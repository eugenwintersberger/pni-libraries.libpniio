//nxstrfield_ex1.cpp

#include <pni/nx/NX.hpp>
#include <pni/utils/PNITypes.hpp>

using namespace pni::nx::h5;
using namespace pni::utils;

#include <iostream>

int main(int argc,char **argv){
    NXFile file;
    NXStringField field;

    file.setFileName("nxstrfield_ex1.h5");
    file.setOverwrite(true);
    file.create();

    field = file.createStringField("text");

    field.close();
    file.close();
}
