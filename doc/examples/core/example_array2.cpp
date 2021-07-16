/*! \example example_array2.cpp

Data access with DArray
*/

#include <vector>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>

using namespace pni::core;

//some usefull type definitions
typedef std::vector<size_t> index_t;      //index type
typedef dynamic_array<float32> f32array;  //an array type for Float32 values


int main(int ,char **)
{
    shape_t shape({10,3});
    //simpel construction from shape - memory allocation is done bye 
    //the array constructor
    auto a = f32array::create(shape); 

    //---------------linear access to data-------------------------------------
    //filling the array - works thanks to STL compliance
    std::fill(a.begin(),a.end(),0);

    //simple C++11 iterator access - output
    for(auto v: a) std::cout<<v<<" ";

    std::cout<<std::endl;
    
    //simple C++11 iterator access - input
    for(f32array::value_type &v: a) v=100.; 

    //data individual data can be accessed with
    a.at(10) = 101.;
    a[11] = 10.2;
    a.insert(12,13.3);

    //----------------multidimensional access----------------------------------
    //this works as easy as in Fortran for input and ouptut
    std::cout<<"Multidimensional index access (i,j):"<<std::endl;
    for(size_t i=0;i<shape[0];i++)
    {
        std::cout<<"| ";
        for(size_t j=0;j<shape[1];j++)
            std::cout<<a(i,j)<<" ";

        std::cout<<"|"<<std::endl;
    }

    //the same thing can be done using a container for accessing the data by
    //indices
    std::cout<<std::endl<<"Multidimensional index access with container index_t{i,j}:";
    std::cout<<std::endl;
    for(size_t i=0;i<shape[0];i++)
    {
        std::cout<<"| ";
        for(size_t j=0;j<shape[1];j++)
            std::cout<<a(index_t{i,j})<<" ";

        std::cout<<"|"<<std::endl;
    }

    return 0;
}

