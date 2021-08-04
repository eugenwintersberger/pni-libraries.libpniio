/*! \example example_array3.cpp

Using selections
*/

#include <iostream>
#include <vector>
#include <pni/types.hpp>
#include <pni/arrays.hpp>

using namespace pni;

//some usefull type definitions
typedef std::vector<size_t> index_t;        //index type
typedef dynamic_array<float32>  f32array;    //an array type for Float32 values
typedef static_array<float32,3> f32vector;  //a static 3-vector type



std::ostream &operator<<(std::ostream &o,const f32array &a)
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

std::ostream &operator<<(std::ostream &o,const f32vector &v)
{
    o<<"( ";
    for(auto c: v) o<<c<<" ";
    o<<")";
    return o;
}



int main(int ,char **)
{
    shape_t shape{10,3};
    //simpel construction from shape - memory allocation is done bye 
    //the array constructor
    auto a = f32array::create(shape); 

    //initialize the array with 0
    std::fill(a.begin(),a.end(),0);

    //using a selection to set the values of each vector
    for(size_t i=0;i<shape[0];i++)
    {
        auto view = a(slice(i),slice(0,3));
        view(0) = float32(i)+0.1;
        view(1) = float32(i)+0.2;
        view(2) = float32(i)+0.3;
    }

    //plotting some output
    std::cout<<a<<std::endl;

    //do some conversion
    for(size_t i=0;i<shape[0];i++)
    {
        f32vector v(a(slice(i),slice(0,3)));
        std::cout<<"vector = "<<v<<std::endl;
    }        


    return 0;
}

