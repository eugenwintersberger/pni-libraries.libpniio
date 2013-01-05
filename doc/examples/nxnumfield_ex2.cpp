//nxnumfield_ex2.cpp
#include <pni/core/Types.hpp>
#include <pni/core/Array.hpp>
#include <pni/io/nx/NX.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

int main(int argc,char **argv)
{
    NXFile file = NXFile::create_file("nxnumfield_ex2.h5",true,0);
    
    //create field
    UInt32 counter;
    NXField field = file.create_field<UInt32>("counter",shape_t{0},shape_t{1});
    field.attr<String>("units").write("cps");
    field.attr<String>("long_name").write("a scalar counter");

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
    DArray<Int32> counters(shape);
    std::cout<<"size: "<<field.size()<<std::endl;
    for(auto s: field.shape<shape_t>()) std::cout<<s<<" ";
    std::cout<<std::endl;
    field.read(counters);

    //read a part of the values
    counters = DArray<Int32>(shape_t({3}));
    field(Slice(2,5)).read(counters);

    return 0;
}
