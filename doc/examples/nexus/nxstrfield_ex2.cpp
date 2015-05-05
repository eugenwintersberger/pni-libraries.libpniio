//nxstrfield_ex2.cpp

#include <pni/io/nx/nx.hpp>
#include <pni/core/types.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

#include <iostream>
#include <fstream>
#include <string>

typedef dynamic_array<string> lines_type;

//-----------------------------------------------------------
void write_log(const string &logfile,nxfield &field)
{
    std::ifstream istream;
    string line;

    istream.open(logfile,std::ifstream::in);
    
    size_t line_counter = 0;
    while(!istream.eof())
    {
        getline(istream,line); //read a line
        field.grow(0);         //grow dataset by one
        field(line_counter++).write(line);
    }

    istream.close();
}

//------------------------------------------------------------
void write_end_log_message(nxfield &field)
{
    field.grow(0);
    field(field.size()-1).write("End of log");
}

//------------------------------------------------------------
lines_type get_lines(const nxfield &field)
{
    auto lines = lines_type::create(shape_t{{field.size()}});
    field.read(lines);
    return lines;
}

//-----------------------------------------------------------
int main(int argc,char **argv)
{
    nxfile file = nxfile::create_file("nxstrfield_ex2.h5",true);
    nxgroup root = file.root();

    nxfield field = root.create_field<string>("logfile",{0});
    std::cout<<"Write log file ..."<<std::endl;
    write_log("nxstrfield_ex2.log",field);
    write_end_log_message(field);
   
    //read everything at once
    std::cout<<"Read log file ..."<<std::endl;
    lines_type lines = get_lines(field);

    for(auto line: lines)
        std::cout<<line<<std::endl;

    //close all objects
    field.close();
    file.close();

    return 0;
}
