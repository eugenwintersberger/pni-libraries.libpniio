//Filename: nxbinfield_ex1.cpp
#include <iostream>
#include <fstream>
#include <pni/io/nx/nx.hpp>
#include <pni/core/types.hpp>
#include <pni/core/dbuffer.hpp>

using namespace pni::io::nx::h5;
using namespace pni::core;

typedef dbuffer<binary> bin_buffer;

void read_image(const string &n,nxfield &field);
void write_image(nxfield &f,const string &n);

//----------------------------------------------------------
int main(int argc,char **argv)
{
    nxfile file = nxfile::create_file("nxbinfield_ex1.h5",true,0); 

    nxfield field = file.create_field<binary>("image",{0});
    read_image("nexus.png",field); 
    write_image(field,"test.png");
    
    return 0;
}

//------------------------------------------------------------
void read_image(const string &n,nxfield &field)
{
    std::ifstream istream;

    istream.open(n,std::ifstream::binary);
    //determine the size of the stream
    //and allocate buffer
    istream.seekg(0,std::ifstream::end);
    bin_buffer buffer((size_t)istream.tellg());
    //reset stream position
    istream.seekg(0,std::ifstream::beg);
    istream.read((char *)buffer.ptr(),buffer.size());

    istream.close();

    field.grow(0,buffer.size());
    field.write(buffer);
}

//-----------------------------------------------------------
void write_image(nxfield &field,const string &n)
{
    std::ofstream ostream;

    ostream.open(n,std::ostream::binary);
    bin_buffer buffer(field.size());
    field.read(buffer);
    ostream.write((char *)buffer.ptr(),buffer.size());
    ostream.close();
}
