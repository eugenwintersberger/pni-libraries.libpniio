//File: nxgroup_ex2.cpp
#include<iostream>
#include<pni/io/nx/nx.hpp>
#include<pni/core/types.hpp>
#include<pni/core/arrays.hpp>

using namespace pni::io::nx::h5;
using namespace pni::core;

int main(int argc,char **argv){
    nxfile file = nxfile::create_file("nxgroup_ex2.h5",true,0);
    nxgroup g = file.create_group("data");

    //string attributes
    nxattribute attr = g.attr<string>("description");
    attr.write("a stupid data gruop");
    
    string desc; 
    attr.read(desc);
    std::cout<<desc<<std::endl;

    //a float attribute
    attr = g.attr<float32>("temperature");
    attr.write(389.2343);
    float64 temp;
    attr.read<float64>(temp);
    std::cout<<temp<<std::endl;

    //a array attribute
    darray<uint32> wa(shape_t{10,3});
    for(size_t i=0;i<wa.size();i++) wa[i] = i;

    attr = g.attr<uint32>("vectors",wa.shape());
    attr.write(wa);
   
    darray<float32> ra(attr.shape<shape_t>());
    for(size_t i=0;i<ra.size();i++) std::cout<<wa[i]<<" "<<ra[i]<<std::endl;

    file.close();
    return 0;
}
