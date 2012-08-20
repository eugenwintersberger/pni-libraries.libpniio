#include<pni/utils/Types.hpp>
#include<pni/utils/Array.hpp>
#include<pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;


void write_data(String fname,size_t np,size_t nx,size_t ny)
{
    DArray<UInt32> frame(shape_t{nx,ny});

    NXFile file = NXFile::create_file(fname,true,0);

    NXGroup g = file.create_group("/scan_1/instrument/detector","NXdetector");
    NXField data = g.create_field<UInt32>("data",shape_t{0,nx,ny});

    for(size_t i=0;i<np;i++)
    {
        //read data
        std::fill(frame.begin(),frame.end(),i);
        //extend field
        data.grow(0);
        data(i,Slice(0,nx),Slice(0,ny)).write(frame);
    }

    //close everything
    g.close();
    data.close();
    file.close();
}

void read_data(String fname,size_t np,size_t nx,size_t ny)
{
    DArray<Float64> data(shape_t{np,ny});

    NXFile file = NXFile::open_file(fname,false);
    NXField field = file["/scan_1/instrument/detector/data"];

    for(size_t i=0;i<nx;i++)
    {
        field(Slice(0,np),i,Slice(0,ny)).read(data);
    }

    //close everything
    field.close();
    file.close();
}

int main(int argc,char **argv)
{
    String fname="simple_io.h5";
    size_t nx = 10;
    size_t ny = 20;
    size_t np = 100;

    std::cout<<"writing data ..."<<std::endl;
    write_data(fname,np,nx,ny);
    std::cout<<"reading data ..."<<std::endl;
    read_data(fname,np,nx,ny);
    std::cout<<"program finished ..."<<std::endl;

    return 0;
}
