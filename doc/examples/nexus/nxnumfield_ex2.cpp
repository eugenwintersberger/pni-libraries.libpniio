//nxnumfield_ex2.cpp
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/algorithms.hpp>

using namespace pni::core;
using namespace pni::io::nx;

//-----------------------------------------------------------------------------
h5::nxfield create_field(const h5::nxgroup &parent)
{
    h5::nxfield field = parent.create_field<uint32>("counter",
                                              shape_t{0},
                                              shape_t{1});

    field.attributes.create<string>("long_name").write("a scalar counter");
    set_unit(field,"cps");

    return field;
}

//----------------------------------------------------------------------------
void write_data(uint32 n,h5::nxfield &field)
{
    uint32 counter = 0;

    for(;counter<n;counter++)
    {
        field.grow(0);
        field(counter).write(counter);
    }
}

//----------------------------------------------------------------------------
void read_all(const h5::nxfield &field)
{
    auto data = dynamic_array<int32>::create(shape_t{{field.size()}});

    field.read(data);

    std::cout<<"Data: ";
    for(auto d: data) std::cout<<d<<" ";
    std::cout<<std::endl;
}

//----------------------------------------------------------------------------
void read_single_value(size_t i,const h5::nxfield &field)
{
    float32 value;
    
    field(i).read(value);

    std::cout<<value<<std::endl;
}

//----------------------------------------------------------------------------
int main(int argc,char **argv)
{
    h5::nxfile file = h5::nxfile::create_file("nxnumfield_ex2.h5",true);
    
    //create field
    h5::nxfield field = create_field(file.root());

    //write stream
    write_data(20,field);

    //read all values
    read_all(field);

    //read a part of the values
    read_single_value(15,field);

    return 0;
}
