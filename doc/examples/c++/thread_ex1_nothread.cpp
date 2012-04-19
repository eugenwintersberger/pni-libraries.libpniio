/*example for the library using a thread*/

#include<thread>
#include<iostream>
#include<pni/hdf5/hdf5.h>

#include<pni/utils/Types.hpp>
#include<pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;


class Writer{
    private:
        String _filename;
    public:
        Writer(const String &fname)
        {
            _filename = fname;
        }

        void operator()(){
            std::cout<<"create file"<<std::endl;
            //works with HDF5
            /*
            hid_t h5f =
                H5Fcreate(_filename.c_str(),H5F_ACC_TRUNC,H5P_DEFAULT,H5P_DEFAULT);

            H5Fclose(h5f);
            */
            NXFile f = NXFile::create_file(_filename,true);
            auto g = f.create_group("log");
            auto d = g.create_field<String>("data");
            d.write("Staring new log");

            std::cout<<"close file"<<std::endl;
            f.close();
        }
};


int main(int argc,char **argv)
{
    Writer writer("userlog.nx");
    //std::thread wthread(writer);


    writer();

    //in the very end we need to join the thread
 //   wthread.join();

    return 0;
}    
