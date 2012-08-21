//nxnumfield_ex2.cpp
#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>
#include <pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

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
    field.read(counters);

    //read a part of the values
    counters = DArray<Int32>(shape_t({3}));
    field(Slice(2,5)).read(counters);

    return 0;
}
