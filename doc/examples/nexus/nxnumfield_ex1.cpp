//Filename: nxnumfield_ex1.cpp
#include<iostream>
#include<pni/io/nx/nx.hpp>
#include<pni/core/types.hpp>
#include<pni/core/arrays.hpp>

using namespace pni::io::nx::h5;
using namespace pni::core;

int main(int argc,char **argv)
{
    //create the file
    nxfile file = nxfile::create_file("nxnumfield_ex1.h5",true,0);
    nxgroup root = file.root();

    //create a array data 
    auto  data = dynamic_array<uint16>::create(shape_t{1024,512});
    std::fill(data.begin(),data.end(),1);

	//automatic from memory object
    nxfield field = root.create_field<uint16>("detector",data.shape<shape_t>());
    field.attributes.create<string>("units").write("cps");
    field.attributes.create<string>("long_name").write("detector data");
    field.write(data);

    //creating fields from scalars
    float32 motor = 1.2;
    field = root.create_field<float32>("omega");
    field.write(motor);
    field.attributes.create<string>("units").write("degree");
    field.attributes.create<string>("long_name").write("motor moega of goniometer");

    file.close();

    return 0;
}



