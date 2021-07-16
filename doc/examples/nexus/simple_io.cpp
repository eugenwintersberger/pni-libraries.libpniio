#include <pni/types.hpp>
#include <pni/arrays.hpp>
#include <pni/nexus.hpp>
#include <h5cpp/hdf5.hpp>
#include <algorithm>
#include <boost/filesystem.hpp>


using namespace pni;


void write_data(const boost::filesystem::path &file_path,size_t np,size_t nx,size_t ny)
{
    auto frame = dynamic_array<uint32>::create(shape_t{nx,ny});

    hdf5::file::File file = nexus::create_file(file_path,hdf5::file::AccessFlags::TRUNCATE);

    hdf5::node::Group group = nexus::BaseClassFactory::create(file.root(),"scan","NXentry");
    group = nexus::BaseClassFactory::create(group,"instrument","NXinstrument");
    group = nexus::BaseClassFactory::create(group,"detector","NXdetector");

    hdf5::filter::Deflate deflate(8);
    hdf5::filter::Shuffle shuffle;
    hdf5::dataspace::Simple space{{0,nx,ny},{hdf5::dataspace::Simple::UNLIMITED,nx,ny}};
    hdf5::Dimensions chunk_dims{1,nx,ny};
    auto type = hdf5::datatype::create<int>();
    hdf5::property::LinkCreationList lcpl;
    hdf5::property::DatasetCreationList dcpl;
    shuffle(dcpl);
    deflate(dcpl);

    hdf5::node::Dataset field = nexus::FieldFactory::create(group,"data",type,space,chunk_dims,lcpl,dcpl);

    hdf5::dataspace::Hyperslab selection{{0,0,0},{1,nx,ny}};
    for(size_t i=0;i<np;i++)
    {
        //read data
        std::fill(frame.begin(),frame.end(),i);
        //extend field
        field.extent(0,1);
        selection.offset(0,i);
        field.write(frame,selection);
    }
}

//----------------------------------------------------------------------------
void read_data(const nexus::Path &path)
{
    typedef dynamic_array<float64> array_type;

    hdf5::file::File file = nexus::open_file(path.filename());
    nexus::DatasetList fields = nexus::get_objects(file.root(),path);
    
    auto data = array_type::create(hdf5::dataspace::Simple(fields[0].dataspace()).current_dimensions());
    
    fields[0].read(data);
}

//----------------------------------------------------------------------------
int main(int,char **)
{
    string fname="simple_io.nxs";

    std::cout<<"writing data ..."<<std::endl;
    write_data(fname,100,10,20);

    std::cout<<"reading data ..."<<std::endl;
    string target_path = "simple_io.nxs://:NXentry/:NXinstrument/"
                         ":NXdetector/data";
    read_data(nexus::Path::from_string(target_path));
    std::cout<<"program finished ..."<<std::endl;

    return 0;
}
