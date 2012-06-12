//nxnumfield_ex2.cpp
#include <pni/utils/Types.hpp>
#include <pni/utils/ArrayFactory.hpp>
#include <pni/utils/Array.hpp>
#include <pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

int main(int argc,char **argv){
    NXFile file = NXFile::create_file("nxnumfield_ex2.h5",true,0);
    
    //create field
    UInt32Scalar counter("counter","cps","a scalar counter");
    NXField field = file.create_field<UInt32>(counter.name(),{0});

    //write stream
    for(size_t i=0;i<10;i++){
        field.grow(0);
        counter = i;
        field(i).write(counter);
    }

    //read all values
    Shape shape = {field.size()};
    Int32Array counters = ArrayFactory<Int32>::create(shape);
    field.read(counters);

    //read a part of the values
    counters = ArrayFactory<Int32>::create(Shape({3}));
    field(Slice(2,5)).read(counters);

    //set individual entries
    counter = 100;
    field(2).write(100);

    return 0;
}
