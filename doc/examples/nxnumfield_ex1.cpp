//Filename: nxnumfield_ex1.cpp
#include<iostream>
#include<pni/nx/NX.hpp>
#include<pni/utils/Types.hpp>
#include<pni/utils/ArrayFactory.hpp>
#include<pni/utils/Array.hpp>

using namespace pni::nx::h5;
using namespace pni::utils;

int main(int argc,char **argv){
    //create the file
    NXFile file = NXFile::create_file("nxnumfield_ex1.h5",true,0);

    //create a array data 
    UInt16Array data = ArrayFactory<UInt16>::create(Shape({1024,512}));
    data.name("detector1"); data.unit("cps"); data.description("first detector");
    data = 1;

	//automatic from memory object
    NXField field = file.create_field<UInt16>(data.name(),data.shape());
    field.attr<String>("units").write(data.unit());
    field.attr<String>("long_name").write(data.description());

    //creating fields from scalars
    Float32Scalar motor("omega","degree","motor omega of goniometer");
    motor = 1.2;
    field = file.create_field<Float32>(motor.name());
    field.attr<String>("units").write(motor.unit());
    field.attr<String>("long_name").write(motor.description());

    file.close();

    return 0;
}



