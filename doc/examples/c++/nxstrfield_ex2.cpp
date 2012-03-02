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
    NXSelection sel = field.selection();
    sel.shape(0,1);
    sel.stride(0,1);
    sel.offset(0,0);
   
    
    size_t lcnt = 0;
    while(!istream.eof()){
        getline(istream,line); //read a line
        field.grow(0);         //grow dataset by one
        sel.offset(0,lcnt);    //set offset for selection
        sel.write(line);       //write data
        lcnt++;                //increment the line counter
    }

    istream.close();
}

//-----------------------------------------------------------
int main(int argc,char **argv){
    NXFile file = NXFile::create_file("nxstrfield_ex2.h5",true,0);

    NXField field = file.create_field<String>("logfile",{0});
    write_log("nxstrfield_ex2.log",field);
   
    //read everything at once
    NXSelection sel = field.selection();
    sel.offset(0,0);
    sel.stride(0,1);
    sel.shape(0,1);
    for(size_t i=0;i<field.size();i++)
    {
        String line;
        sel.read(line);
        std::cout<<line<<std::endl;
        sel.offset({i});
    }

    //set individual lines
    field.grow(0);
    sel.offset(0,field.size()-1);
    sel.write(String("End of log"));
    for(size_t i=field.size()-20;i<field.size();i++){
        String line;
        sel.offset(0,i);
        sel.read(line);
        std::cout<<"line "<<i<<" : "<<line<<std::endl;
    }

    //close all objects
    field.close();
    file.close();

    return 0;
}
