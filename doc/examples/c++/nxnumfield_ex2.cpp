//nxnumfield_ex2.cpp

#include <pni/utils/PNITypes.hpp>
#include <pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

int main(int argc,char **argv){
    NXFile file;
    file.setFileName("nxnumfield_ex2.h5");
    file.setOverwrite(true);
    file.create();
    
    //create field
    UInt32Scalar counter("counter","cps","a scalar counter");
    NXNumericField field = file.createNumericField(counter);
    
    //write stream
    for(UInt32 i=0;i<10;i++){
        counter = i;
        field<<counter;
    }

    //read individual values
    field.get(3,counter);

    //read all values
    ArrayShape shape(1);
    shape.setDimension(0,field.size());
    Int32Array counters(shape);
    counters.setUnit(counter.getUnit());
    field.get(counters);

    //read a part of the values
    shape.setDimension(0,3);
    counters.reset(); counters.setShape(shape);
    counters.allocate();

    field.get(2,counters);

    //set individual entries
    counter = 100;
    field.set(2,counter);
    field.set(12,counter);


    return 0;
}
