//nxstrfield_ex2.cpp

#include <pni/nx/NX.hpp>
#include <pni/utils/Types.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

#include <iostream>
#include <fstream>
#include <string>

//-----------------------------------------------------------
void write_log(const String &logfile,NXField &field){
    std::ifstream istream;
    String line;

    istream.open(logfile,std::ifstream::in);
    
    size_t lcnt = 0;
    while(!istream.eof())
    {
        getline(istream,line); //read a line
        field.grow(0);         //grow dataset by one
        field(lcnt++).write(line);
    }

    istream.close();
}

//-----------------------------------------------------------
int main(int argc,char **argv)
{
    NXFile file = NXFile::create_file("nxstrfield_ex2.h5",true,0);

    NXField field = file.create_field<String>("logfile",{0});
    std::cout<<"Write log file ..."<<std::endl;
    write_log("nxstrfield_ex2.log",field);
   
    //read everything at once
    std::cout<<"Read log file ..."<<std::endl;
    for(size_t i=0;i<field.size();i++)
    {
        String line;
        field(i).read(line);
        std::cout<<line<<std::endl;
    }

    //set individual lines
    field.grow(0);
    field(field.size()-1).write("End of log");
    std::cout<<"Read read partly ..."<<std::endl;
    for(size_t i=field.size()-20;i<field.size();i++)
    {
        String line;
        field(i).read(line);
        std::cout<<"line "<<i<<" : "<<line<<std::endl;
    }

    //close all objects
    field.close();
    file.close();

    return 0;
}
