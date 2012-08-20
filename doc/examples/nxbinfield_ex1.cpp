//Filename: nxbinfield_ex1.cpp
#include <iostream>
#include <fstream>
#include <pni/nx/NX.hpp>
#include <pni/utils/Types.hpp>
#include <pni/utils/DBuffer.hpp>

using namespace pni::nx::h5;
using namespace pni::utils;

typedef DBuffer<Binary> BinBuffer;

void read_image(const String &n,NXField &field);
void write_image(NXField &f,const String &n);

//----------------------------------------------------------
int main(int argc,char **argv)
{
    NXFile file = NXFile::create_file("nxbinfield_ex1.h5",true,0); 

    NXField field = file.create_field<Binary>("image",{0});
    read_image("nexus.png",field); 
    write_image(field,"test.png");
    
    return 0;
}

//------------------------------------------------------------
void read_image(const String &n,NXField &field)
{
    std::ifstream istream;

    istream.open(n,std::ifstream::binary);
    //determine the size of the stream
    //and allocate buffer
    istream.seekg(0,std::ifstream::end);
    DBuffer<Binary> buffer((size_t)istream.tellg());
    //reset stream position
    istream.seekg(0,std::ifstream::beg);
    istream.read((char *)buffer.ptr(),buffer.size());

    istream.close();

    field.grow(0,buffer.size());
    field.write(buffer);
}

//-----------------------------------------------------------
void write_image(NXField &field,const String &n)
{
    std::ofstream ostream;

    ostream.open(n,std::ostream::binary);
    DBuffer<Binary> buffer(field.size());
    field.read(buffer);
    ostream.write((char *)buffer.ptr(),buffer.size());
    ostream.close();
}
