//nxbinfield_ex1.cpp

#include <pni/nx/NX.hpp>
#include <pni/utils/PNITypes.hpp>
#include <pni/utils/Buffer.hpp>

using namespace pni::nx::h5;
using namespace pni::utils;

typedef Buffer<Binary> BinBuffer;

#include <iostream>
#include <fstream>

//------------------------------------------------------------
void read_image(const String &n,NXBinaryField &field){
    std::ifstream istream;

    istream.open(n,std::ifstream::binary);
    //determine the size of the stream
    //and allocate buffer
    istream.seekg(0,std::ifstream::end);
    BinBuffer buffer(istream.tellg());
    //reset stream position
    istream.seekg(0,std::ifstream::beg);
    istream.read((char *)buffer.getPtr(),buffer.getSize());

    istream.close();

    field<<buffer;
}

//-----------------------------------------------------------
void write_image(NXBinaryField &field,const String &n){
    std::ofstream ostream;

    ostream.open(n,std::ostream::binary);
    BinBuffer buffer(field.size());
    field>>buffer;
    ostream.write((char *)buffer.getPtr(),buffer.getSize());
    ostream.close();
}

//----------------------------------------------------------
int main(int argc,char **argv){
    NXFile file;
    file.setFileName("nxbinfield_ex1.h5");
    file.setOverwrite(true);
    file.create();

    NXBinaryField field = file.createBinaryField("image");
    read_image("nexus.png",field); 
    write_image(field,"test.png");
    
    return 0;
}
