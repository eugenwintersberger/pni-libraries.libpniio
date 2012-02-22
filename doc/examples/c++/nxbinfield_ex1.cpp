//nxbinfield_ex1.cpp

#include <pni/nx/NX.hpp>
#include <pni/utils/Types.hpp>
#include <pni/utils/Buffer.hpp>

using namespace pni::nx::h5;
using namespace pni::utils;

typedef Buffer<Binary> BinBuffer;

#include <iostream>
#include <fstream>

//------------------------------------------------------------
void read_image(const String &n,NXField &field)
{
    std::ifstream istream;

    istream.open(n,std::ifstream::binary);
    //determine the size of the stream
    //and allocate buffer
    istream.seekg(0,std::ifstream::end);
    Buffer<Binary> buffer(istream.tellg());
    //reset stream position
    istream.seekg(0,std::ifstream::beg);
    istream.read((char *)buffer.ptr(),buffer.size());

    istream.close();

    field.grow(0,buffer.size()-1);
    field.write(buffer);
}

//-----------------------------------------------------------
void write_image(NXField &field,const String &n)
{
    std::ofstream ostream;

    ostream.open(n,std::ostream::binary);
    Buffer<Binary> buffer(field.size());
    field.read(buffer);
    ostream.write((char *)buffer.ptr(),buffer.size());
    ostream.close();
}

//----------------------------------------------------------
int main(int argc,char **argv){
    NXFile file = NXFile::create_file("nxbinfield_ex1.h5",true,0); 

    NXField field = file.create_field<Binary>("image");
    read_image("nexus.png",field); 
    write_image(field,"test.png");
    
    return 0;
}
