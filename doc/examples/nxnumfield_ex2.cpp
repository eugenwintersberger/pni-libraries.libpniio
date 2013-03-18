//nxnumfield_ex2.cpp
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

int main(int argc,char **argv)
{
    nxfile file = nxfile::create_file("nxnumfield_ex2.h5",true,0);
    
    //create field
    uint32 counter;
    nxfield field = file.create_field<uint32>("counter",shape_t{0},shape_t{1});
    field.attr<string>("units").write("cps");
    field.attr<string>("long_name").write("a scalar counter");

    //write stream
    for(size_t i=0;i<10;i++)
    {
        field.grow(0);
        counter = i;
        field(i).write(counter);
        std::cout<<field.size()<<std::endl;
    }

    //read all values
    shape_t shape{field.size()};
    darray<int32> counters(shape);
    std::cout<<"size: "<<field.size()<<std::endl;
    for(auto s: field.shape<shape_t>()) std::cout<<s<<" ";
    std::cout<<std::endl;
    field.read(counters);

    //read a part of the values
    counters = darray<int32>(shape_t({3}));
    field(slice(2,5)).read(counters);

    return 0;
}
