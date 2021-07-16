/*! \example example_array4.cpp

Using selections and numerics
*/

#include <iostream>
#include <vector>
#include <pni/core/arrays.hpp>

using namespace pni::core;

typedef dynamic_array<float32>  frame_type;
typedef static_array<float32,3> vector_type;


std::ostream &operator<<(std::ostream &o,const frame_type &a)
{
    auto shape = a.shape<shape_t>();
    for(size_t i=0;i<shape[0];i++)
    {
        o<<"| ";
        for(size_t j=0;j<shape[1];j++) o<<a(i,j)<<" ";

        std::cout<<"|"<<std::endl;
    }
    return o;
}

std::ostream &operator<<(std::ostream &o,const vector_type &v)
{
    o<<"( ";
    for(auto c: v) o<<c<<" ";
    o<<")";
    return o;
}



int main(int ,char **)
{
    shape_t shape({10,3});
    //simpel construction from shape - memory allocation is done bye 
    //the array constructor
    auto a =  frame_type::create(shape); 

    //initialize the array with 0
    std::fill(a.begin(),a.end(),1);

    //using a selection to set the values of each vector
    for(size_t i=0;i<shape[0];i++) a(i,slice(0,3)) += i+0.1*i;

    //plotting some output
    std::cout<<a<<std::endl;
    for(size_t i=0;i<shape[0];i++)
    {
        vector_type v(a(i,slice(0,3)));
        std::cout<<"vector = "<<v<<std::endl;
    }

    auto  v1 = vector_type::create(std::vector<float32>({1.,2.,3.}));
    std::cout<<"v1 = "<<v1<<std::endl;

    //Vector v{std::vector<Float32>{4,5,6}};
    return 0;
}

