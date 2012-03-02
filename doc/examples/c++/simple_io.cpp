#include<pni/utils/Types.hpp>
#include<pni/utils/Array.hpp>
#include<pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;


void write_data(String fname,size_t np,size_t nx,size_t ny)
{
    UInt32Array frame({nx,ny},"detector","a.u.","detector data");

    NXFile file = NXFile::create_file(fname,true,0);

    NXGroup g = file.create_group("/scan_1/instrument/detector","NXdetector");
    NXField data = g.create_field<UInt32>("data",{0,nx,ny});
    NXSelection fsel = data.selection();
    fsel.offset({0,0,0});
    fsel.stride({1,1,1});
    fsel.shape({1,nx,ny});

    for(size_t i=0;i<np;i++){
        //read data
        frame = i;
        //extend field
        data.grow(0);
        //set selection offset
        fsel.offset({i,0,0});
        //write data
        fsel.write(frame);
    }

    //close everything
    g.close();
    data.close();
    file.close();
}

void read_data(String fname,size_t np,size_t nx,size_t ny)
{
    Float64Array data({np,ny},"slice","a.u.","detector slice");

    NXFile file = NXFile::open_file(fname);
    NXField field = file["/scan_1/instrument/detector/data"];
    NXSelection dsel = field.selection();
    dsel.offset({0,0,0});
    dsel.shape({np,1,ny});
    dsel.stride({1,1,1});

    for(size_t i=0;i<nx;i++){
        dsel.offset({0,i,0});
        dsel.read(data);
        //here we could do some processing
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
