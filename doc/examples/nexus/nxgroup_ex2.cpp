//File: nxgroup_ex2.cpp
#include<iostream>
#include<pni/io/nx/nx.hpp>
#include<pni/core/types.hpp>
#include<pni/core/arrays.hpp>

using namespace pni::io::nx::h5;
using namespace pni::core;

int main(int argc,char **argv)
{
    nxfile file = nxfile::create_file("nxgroup_ex2.h5",true,0);
    nxgroup root = file.root();
    nxgroup g = root.create_group("data");

    //string attributes
    auto attr = g.attributes.create<string>("description");
    attr.write("a stupid data gruop");
    
    string desc; 
    attr.read(desc);
    std::cout<<desc<<std::endl;

    //a float attribute
    attr = g.attributes.create<float32>("temperature");
    attr.write(389.2343);
    float64 temp;
    attr.read<float64>(temp);
    std::cout<<temp<<std::endl;

    //a array attribute
    auto wa = dynamic_array<uint32>::create(shape_t{10,3});
    std::iota(wa.begin(),wa.end(),0);

    attr = g.attributes.create<uint32>("vectors",wa.shape<shape_t>());
    attr.write(wa);
   
    auto ra = dynamic_array<float32>::create(attr.shape<shape_t>());
    for(size_t i=0;i<ra.size();i++) std::cout<<wa[i]<<" "<<ra[i]<<std::endl;

    file.close();
    return 0;
}
