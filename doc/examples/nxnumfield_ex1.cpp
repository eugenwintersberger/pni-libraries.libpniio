//Filename: nxnumfield_ex1.cpp
#include<iostream>
#include<pni/io/nx/nx.hpp>
#include<pni/core/types.hpp>
#include<pni/core/arrays.hpp>

using namespace pni::io::nx::h5;
using namespace pni::core;

int main(int argc,char **argv){
    //create the file
    nxfile file = nxfile::create_file("nxnumfield_ex1.h5",true,0);

    //create a array data 
    darray<uint16> data(shape_t{1024,512});
    std::fill(data.begin(),data.end(),1);

	//automatic from memory object
    nxfield field = file.create_field<uint16>("detector",data.shape<shape_t>());
    field.attr<string>("units").write("cps");
    field.attr<string>("long_name").write("detector data");

    //creating fields from scalars
    float32 motor = 1.2;
    field = file.create_field<float32>("omega");
    field.attr<string>("units").write("degree");
    field.attr<string>("long_name").write("motor moega of goniometer");

    file.close();

    return 0;
}



