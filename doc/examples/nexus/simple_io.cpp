#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/algorithms.hpp>
#include <pni/io/nx/nxpath.hpp>

using namespace pni::core;
using namespace pni::io::nx;


void write_data(string fname,size_t np,size_t nx,size_t ny)
{
    auto frame = dynamic_array<uint32>::create(shape_t{nx,ny});

    h5::nxfile file = h5::nxfile::create_file(fname,true);

    h5::nxgroup g = file.root().create_group("scan","NXentry");
    g = g.create_group("instrument","NXinstrument");
    g = g.create_group("detector","NXdetector");

    h5::nxdeflate_filter filter(8,true);
    h5::nxfield data = g.create_field<uint32>("data",shape_t{0,nx,ny},
                                          shape_t{1,nx,ny},filter);

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

//----------------------------------------------------------------------------
void read_data(const nxpath &path)
{
    typedef dynamic_array<float64> array_type;

    h5::nxfile file = h5::nxfile::open_file(path.filename(),false);
    h5::nxfield field = get_object(file.root(),path);
    
    auto data = array_type::create(field.shape<shape_t>());
    
    field.read(data);

    //close everything
    field.close();
    file.close();
}

//----------------------------------------------------------------------------
int main(int argc,char **argv)
{
    string fname="simple_io.nxs";

    std::cout<<"writing data ..."<<std::endl;
    write_data(fname,100,10,20);

    std::cout<<"reading data ..."<<std::endl;
    string target_path = "simple_io.nxs://:NXentry/:NXinstrument/"
                         ":NXdetector/data";
    read_data(nxpath::from_string(target_path));
    std::cout<<"program finished ..."<<std::endl;

    return 0;
}
