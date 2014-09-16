//nxnumfield_ex2.cpp
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

typedef dynamic_array<float32> data_array;
typedef std::vector<uint16>   buffer_type;

void create_data(string fname)
{
    shape_t shape{2,3};

    buffer_type datab{1,2,3,4,5,6};
    buffer_type bgb{1,2,0,0,1,0};

    auto data = dynamic_array<uint16>::create(shape,datab);
    auto bg   = dynamic_array<uint16>::create(shape,bgb);

    nxfile file = nxfile::create_file(fname,true,0);
    nxgroup root = file.root();
    root.create_field<uint16>("detector",shape).write(data);
    root.create_field<uint16>("background",shape).write(bg);
    root.create_field<float32>("ctime").write(1.23);
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

    auto frame = data_array::create(shape);
    auto background = data_array::create(shape);
    auto cdata = data_array::create(shape);
    float32 ctime;

    create_data("nxnumfield_ex4.h5");

    //reading data
    nxfile file = nxfile::open_file("nxnumfield_ex4.h5",true);
    nxgroup root = file.root();

    nxfield field = root["detector"];
    field.read(frame);

    field = root["background"];
    field.read(background);

    field = root["ctime"];
    field.read(ctime);
    
    std::cout<<"detector data:"<<std::endl;
    print_matrix(frame);

    std::cout<<"background data:"<<std::endl;
    print_matrix(background);


    cdata = (frame - background)/ctime;
    std::cout<<"Corrected data:"<<std::endl;
    print_matrix(cdata);
    

}
