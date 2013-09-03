#include<pni/core/types.hpp>
#include<pni/core/arrays.hpp>
#include<pni/io/nx/nx.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;


void write_data(string fname,size_t np,size_t nx,size_t ny)
{
    darray<uint32> frame(shape_t{nx,ny});

    nxfile file = nxfile::create_file(fname,true,0);

    nxgroup g = file.create_group("/scan_1/instrument/detector","NXdetector");
    nxfield data = g.create_field<uint32>("data",shape_t{0,nx,ny});

    for(size_t i=0;i<np;i++)
    {
        //read data
        std::fill(frame.begin(),frame.end(),i);
        //extend field
        data.grow(0);
        data(i,slice(0,nx),slice(0,ny)).write(frame);
    }

    //close everything
    g.close();
    data.close();
    file.close();
}

void read_data(string fname,size_t np,size_t nx,size_t ny)
{
    darray<float64> data(shape_t{np,ny});

    nxfile file = nxfile::open_file(fname,false);
    nxfield field = file["/scan_1/instrument/detector/data"];

    for(size_t i=0;i<nx;i++)
    {
        field(slice(0,np),i,slice(0,ny)).read(data);
    }

    //close everything
    field.close();
    file.close();
}

int main(int argc,char **argv)
{
    string fname="simple_io.h5";
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
