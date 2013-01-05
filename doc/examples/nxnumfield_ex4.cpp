//nxnumfield_ex2.cpp
#include <pni/core/Types.hpp>
#include <pni/core/Array.hpp>
#include <pni/io/nx/NX.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

typedef DArray<Float32> DataArray;

void create_data(String fname)
{
    shape_t shape{2,3};

    DBuffer<UInt16> datab{1,2,3,4,5,6};
    DBuffer<UInt16> bgb{1,2,0,0,1,0};

    DArray<UInt16> data(shape,datab);
    DArray<UInt16> bg(shape,bgb);

    NXFile file = NXFile::create_file(fname,true,0);
    file.create_field<UInt16>("detector",shape).write(data);
    file.create_field<UInt16>("background",shape).write(bg);
    file.create_field<Float32>("ctime").write(1.23);
    file.close();
}

template<typename MTYPE> void print_matrix(const MTYPE &m)
{
    shape_t s(m.template shape<shape_t>());

    for(size_t i=0;i<s[0];i++)
    {
        for(size_t j=0;j<s[1];j++)
            std::cout<<m(i,j)<<"\t";

        std::cout<<std::endl;
    }
}


int main(int argc,char **argv)
{
    shape_t shape{2,3};

    NumArray<DataArray> frame(shape);
    NumArray<DataArray> background(shape);
    NumArray<DataArray> cdata(shape);
    Float32 ctime;

    create_data("nxnumfield_ex4.h5");

    //reading data
    NXFile file = NXFile::open_file("nxnumfield_ex4.h5",true);

    NXField field = file["detector"];
    field.read(frame);

    field = file["background"];
    field.read(background);

    field = file["ctime"];
    field.read(ctime);
    
    std::cout<<"detector data:"<<std::endl;
    print_matrix(frame);

    std::cout<<"background data:"<<std::endl;
    print_matrix(background);


    cdata = (frame - background)/ctime;
    std::cout<<"Corrected data:"<<std::endl;
    print_matrix(cdata);
    

}
