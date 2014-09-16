//nxnumfield_ex2.cpp
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

int main(int argc,char **argv)
{
    nxfile file = nxfile::create_file("nxnumfield_ex2.h5",true,0);
    nxgroup root = file.root();
    
    //create field
    uint32 counter;
    nxfield field = root.create_field<uint32>("counter",shape_t{0},shape_t{1});
    field.attributes.create<string>("units").write("cps");
    field.attributes.create<string>("long_name").write("a scalar counter");

    //write stream
    for(size_t i=0;i<10;i++)
    {
        field.grow(0);
        counter = i;
        field(i).write(counter);
        std::cout<<field.size()<<std::endl;
    }

    //read all values
    shape_t shape{{field.size()}};
    auto counters = dynamic_array<int32>::create(shape);
    std::cout<<"size: "<<field.size()<<std::endl;
    for(auto s: field.shape<shape_t>()) std::cout<<s<<" ";
    std::cout<<std::endl;
    field.read(counters);

    //read a part of the values
    counters = dynamic_array<int32>::create(shape_t({3}));
    field(slice(2,5)).read(counters);

    return 0;
}
