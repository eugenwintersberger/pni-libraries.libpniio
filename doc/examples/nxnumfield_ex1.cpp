//Filename: nxnumfield_ex1.cpp
#include<iostream>
#include<pni/io/nx/NX.hpp>
#include<pni/core/Types.hpp>
#include<pni/core/Array.hpp>

using namespace pni::io::nx::h5;
using namespace pni::core;

int main(int argc,char **argv){
    //create the file
    NXFile file = NXFile::create_file("nxnumfield_ex1.h5",true,0);

    //create a array data 
    DArray<UInt16> data(shape_t{1024,512});
    std::fill(data.begin(),data.end(),1);

	//automatic from memory object
    NXField field = file.create_field<UInt16>("detector",data.shape<shape_t>());
    field.attr<String>("units").write("cps");
    field.attr<String>("long_name").write("detector data");

    //creating fields from scalars
    Float32 motor = 1.2;
    field = file.create_field<Float32>("omega");
    field.attr<String>("units").write("degree");
    field.attr<String>("long_name").write("motor moega of goniometer");

    file.close();

    return 0;
}



