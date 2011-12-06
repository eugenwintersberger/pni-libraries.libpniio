//nxstrfield_ex2.cpp

#include <pni/nx/NX.hpp>
#include <pni/utils/PNITypes.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

#include <iostream>
#include <fstream>
#include <string>

//-----------------------------------------------------------
void write_log(const String &logfile,NXStringField &field){
    std::ifstream istream;
    String line;

    istream.open(logfile,std::ifstream::in);

    while(!istream.eof()){
        getline(istream,line); 
        field<<line; //save data to field using streams
    }

    istream.close();
}

//-----------------------------------------------------------
int main(int argc,char **argv){
    NXFile file;
    file.setFileName("nxstrfield_ex2.h5");
    file.setOverwrite(true);
    file.create();

    NXStringField field = file.createStringField("logfile");
    write_log("nxstrfield_ex2.log",field);
   
    //read everything at once
    std::cout<<field.get('\n')<<std::endl;

    //read individual lines
    for(UInt64 i=0;i<field.size();i++){
        std::cout<<"line "<<i<<" : "<<field.get(i)<<std::endl;
    }

    //set individual lines
    field.set(field.size()-1,"End of log");
    for(UInt64 i=field.size()-20;i<field.size();i++){
        std::cout<<"line "<<i<<" : "<<field.get(i)<<std::endl;
    }

    //set creates lines if they are not available
    field.set(field.size()+2,"Newly created field entry");
    for(UInt64 i=field.size()-20;i<field.size();i++){
        std::cout<<"line "<<i<<" : "<<field.get(i)<<std::endl;
    }

    //close all objects
    field.close();
    file.close();

    return 0;
}
