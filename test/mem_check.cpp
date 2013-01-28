#include<pni/io/nx/nx.hpp>
#include<pni/utils/types.hpp>
#include<pni/utils/arrays.hpp>
#include<sstream>
#include<iostream>
#include<fstream>

extern "C"{
#include<sys/types.h>
#include<unistd.h>
}



using namespace pni::nx::h5;
using namespace pni::utils;

String get_mem_file()
{
    std::stringstream ss;
    ss<<"/proc/"<<getpid()<<"/statm";
    return String(ss.str());
}

void get_mem(const String fname,size_t &s,size_t &rss)
{
    std::ifstream ifs(fname,std::ifstream::in);
    ifs>>s>>rss;
    ifs.close();
}

void testfunction()
{
    //create string array
    DArray<String,DBuffer<String> > array(shape_t{10});
    
    //fill string array
    std::stringstream ss;
    size_t index = 0;
    for(String &s: array)
    {
        ss<<index++;
        s = ss.str();
    }

    NXFile file = NXFile::create_file("mem_check.h5",true,0);
    try{
        NXField f = file.create_field<String>("text",array.shape<shape_t>());
        f.write(array);

        NXGroup g = file.create_group("detector");
        g.attr<String>("vendor_name").write("DECTRIS");
    }
    catch(pni::nx::NXGroupError &error)
    {
        std::cerr<<error<<std::endl;
    }
    file.close();
}


int main(int argc,char **argv)
{
    size_t nruns = std::atoi(argv[1]);   
    size_t size = 0;
    size_t rss  = 0;
    std::ofstream mem_log("memory.log",std::ofstream::out);
   
    for(size_t i=0;i<nruns;i++)
    {
        //run the test function
        testfunction();
        get_mem(get_mem_file(),size,rss);
        mem_log<<size<<"\t"<<rss<<std::endl;
    }



    return 0;

}
