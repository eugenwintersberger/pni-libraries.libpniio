//File: nxgroup_ex2.cpp
#include<iostream>
#include<pni/nx/NX.hpp>
#include<pni/utils/Types.hpp>
#include<pni/utils/Array.hpp>

using namespace pni::nx::h5;
using namespace pni::utils;

int main(int argc,char **argv){
    NXFile file = NXFile::create_file("nxgroup_ex2.h5",true,0);
    NXGroup g = file.create_group("data");

    //string attributes
    NXAttribute attr = g.attr<String>("description");
    attr.write("a stupid data gruop");
    
    String desc; 
    attr.read(desc);
    std::cout<<desc<<std::endl;

    //a float attribute
    attr = g.attr<Float32>("temperature");
    attr.write(389.2343);
    Float64 temp;
    attr.read<Float64>(temp);
    std::cout<<temp<<std::endl;

    //a array attribute
    DArray<UInt32> wa(shape_t{10,3});
    for(size_t i=0;i<wa.size();i++) wa[i] = i;

    attr = g.attr<UInt32>("vectors",wa.shape());
    attr.write(wa);
   
    DArray<Float32> ra(attr.shape<shape_t>());
    for(size_t i=0;i<ra.size();i++) std::cout<<wa[i]<<" "<<ra[i]<<std::endl;

    file.close();
    return 0;
}
