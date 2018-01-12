/*
 * cbf_reader_test.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: Eugen Wintersberger
 */

//Testing program for the CBF reader

#include<iostream>
#include<typeinfo>
#include<cmath>


#include <pni/io/fio/fio_reader.hpp>
#include <pni/core/arrays.hpp>

using namespace pni;

using Float32Array = core::dynamic_array<core::float32>;


int main(int argc,char **argv){

    if(argc<2){
        std::cerr<<"Usage: cbf_reader_test <filename>"<<std::endl;
        return -1;
    }

    //get the name of the file to copen
    std::string file_name(argv[1]);


    io::fio_reader reader(file_name);
    std::cout<<"File has "<<reader.nparameters()<<" parameters: "<<std::endl;
    std::cout<<"Parameters are:"<<std::endl;

    auto parameter_names = reader.parameter_names();
    std::for_each(parameter_names.begin(),parameter_names.end(),
                  [](const std::string &name) { std::cout<<name<<"; ";});
    std::cout<<std::endl;

    //print parameters
    std::cout<<"ALPHA_OFF = "<<reader.parameter<core::int32>("ALPHA_OFF")<<std::endl;
    std::cout<<"ENT_SL_B  = "<<reader.parameter<core::float32>("ENT_SL_B")<<std::endl;
    std::cout<<"ENT_SL_L  = "<<reader.parameter<core::float32>("ENT_SL_L")<<std::endl;
    std::cout<<"ENT_SL_R  = "<<reader.parameter<core::float32>("ENT_SL_R")<<std::endl;
    std::cout<<"ENT_SL_T  = "<<reader.parameter<core::float32>("ENT_SL_T")<<std::endl;
    std::cout<<"EXIT_SL_B = "<<reader.parameter<core::float32>("EXIT_SL_B")<<std::endl;
    std::cout<<"EXIT_SL_L = "<<reader.parameter<core::float32>("EXIT_SL_L")<<std::endl;
    std::cout<<"EXIT_SL_R = "<<reader.parameter<core::float32>("EXIT_SL_R")<<std::endl;
    std::cout<<"EXIT_SL_T = "<<reader.parameter<core::float32>("EXIT_SL_T")<<std::endl;
    std::cout<<"HHE       = "<<reader.parameter<std::string>("HHE")<<std::endl;
    std::cout<<"HHE1_FAC  = "<<reader.parameter<core::float32>("HHE1_FAC")<<std::endl;
    std::cout<<"HHE2_FAC  = "<<reader.parameter<core::float32>("HHE2_FAC")<<std::endl;
    std::cout<<"HHE2_OFF  = "<<reader.parameter<core::float32>("HHE2_OFF")<<std::endl;
    std::cout<<"HHE1_OFF  = "<<reader.parameter<core::float32>("HHE1_OFF")<<std::endl;
    std::cout<<"IDORIS    = "<<reader.parameter<core::float32>("IDORIS")<<std::endl;
    std::cout<<"MONO      = "<<reader.parameter<core::float32>("MONO")<<std::endl;
    std::cout<<"REF_POS   = "<<reader.parameter<core::float32>("REF_POS")<<std::endl;
    std::cout<<"SAMPLE    = "<<reader.parameter<std::string>("SAMPLE")<<std::endl;
    std::cout<<"SAMPLE_POS= "<<reader.parameter<core::float32>("SAMPLE_POS")<<std::endl;

#ifdef NOFOREACH
    for(auto iter = reader.begin();iter!=reader.end();++iter)
    {
        auto c = *iter;
#else
    for(auto c: reader) 
    {
#endif 
        std::cout<<c<<std::endl;
    }
    std::cout<<"File contains: "<<reader.nrecords()<<std::endl;

    auto array = Float32Array::create(core::shape_t{reader.nrecords()},
                                      reader.column<Float32Array::storage_type>("TIO2_KRONOS_0001_ENERGIE_HHE1"));

    reader.close();

    return 0;
}
