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
    NXSelection sel = field.selection();
    sel.shape({1});
    sel.offset({0});
    sel.stride({1});
    
    //write stream
    for(size_t i=0;i<10;i++){
        field.grow(0);
        sel.offset(0,i);
        counter = i;
        sel.write(counter); 
    }

    //read individual values
    sel.offset(0,3);
    sel.read(counter);

    //read all values
    Shape shape = {field.size()};
    Int32Array counters = ArrayFactory<Int32>::create(shape);
    field.read(counters);

    //read a part of the values
    counters = ArrayFactory<Int32>::create(Shape({3}));

    sel.offset({2});
    sel.shape({3});
    sel.read(counters);

    //set individual entries
    counter = 100;
    sel.offset({2});
    sel.shape({1});
    sel.write(counter);

    return 0;
}
