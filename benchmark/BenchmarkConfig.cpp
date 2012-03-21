#include "BenchmarkConfig.hpp"
#include<boost/program_options/option.hpp>
#include<boost/program_options/options_description.hpp>
#include<boost/program_options/positional_options.hpp>
#include<boost/program_options/variables_map.hpp>
#include<boost/program_options/parsers.hpp>

namespace popts = boost::program_options;

//-----------------------------------------------------------------------------
BenchmarkConfig::BenchmarkConfig(int argc,char **argv)
{

    //create command line options
    popts::options_description odesc("CLI options");
    popts::options_description hidden("hidden options");
    popts::positional_options_description adesc;
    odesc.add_options()
        ("help,h","show help message")
        ("lib,l",popts::value<String>()->default_value("pninx"),
         "library to use for the benchmark")
        ("type,t",popts::value<String>()->default_value("uint8"),
         "data type of the frames")
        ("nx,x",popts::value<size_t>(&_nx)->default_value(512),
         "number of channels in x-direction")
        ("ny,y",popts::value<size_t>(&_ny)->default_value(512),
         "number of channels in y-direction")
        ("frames,f",popts::value<size_t>(&_nframes)->default_value(100),
         "number of rames to write during each run")
        ("runs,r",popts::value<size_t>(&_nruns)->default_value(1),
         "number of runs")
        ("noise,n",popts::value<UInt32>(&_nlevel)->default_value(0),
         "noise level for the data")
        ;
    hidden.add_options()
        ("output,o",popts::value<String>(&_fname)->default_value("out.h5"),
         "output file")
        ;

    adesc.add("output",-1);

    popts::options_description cliopts("Command line options");
    cliopts.add(odesc).add(hidden);

    popts::variables_map omap;
    popts::store(popts::command_line_parser(argc,argv).options(cliopts).positional(adesc).run(),omap);
    popts::notify(omap);

    //check for help options
    if(omap.count("help")){
        std::cout<<"show help message!"<<std::endl;
        std::cout<<odesc<<std::endl;
        exit(0);
    }

    //determine which library to use for the benchmark
    if(omap["lib"].as<String>() == "pninx"){
        std::cout<<"Using PNINX for writing data ..."<<std::endl;
        _libid = LibID::PNINX;
    }else if(omap["lib"].as<String>() == "hdf5"){
        std::cout<<"using plain HDF5 for writing data ..."<<std::endl;
        _libid = LibID::HDF5;
    }else{
        std::cerr<<"Unknown library code - aborting!"<<std::endl;
        exit(1);
    }

    //determine the datatype to use for the payload data
    if(omap["type"].as<String>() == "uint8")         
        _typecode = TypeID::UINT8;
    else if(omap["type"].as<String>() == "int8")     
        _typecode = TypeID::INT8;
    else if(omap["type"].as<String>() == "uint16")   
        _typecode = TypeID::UINT16;
    else if(omap["type"].as<String>() == "int16")    
        _typecode = TypeID::INT16;
    else if(omap["type"].as<String>() == "uint32")   
        _typecode = TypeID::UINT32;
    else if(omap["type"].as<String>() == "int32")    
        _typecode = TypeID::INT32;
    else if(omap["type"].as<String>() == "uint64")   
        _typecode = TypeID::UINT64;
    else if(omap["type"].as<String>() == "int64")    
        _typecode = TypeID::INT64;
    else if(omap["type"].as<String>() == "float32")  
        _typecode = TypeID::FLOAT32;
    else if(omap["type"].as<String>() == "float64")  
        _typecode = TypeID::FLOAT64;
    else if(omap["type"].as<String>() == "float128") 
        _typecode = TypeID::FLOAT128;
    else{
        std::cerr<<"Unkown type code - aborting!"<<std::endl;
        exit(1);
    }


}

//----------------------------------------------------------------------------
TypeID BenchmarkConfig::typecode() const
{
    return _typecode;
}

//----------------------------------------------------------------------------
size_t BenchmarkConfig::nx() const
{
    return _nx;
}

//----------------------------------------------------------------------------
size_t BenchmarkConfig::ny() const
{
    return _ny;
}

//----------------------------------------------------------------------------
size_t BenchmarkConfig::nframes() const
{
    return _nframes;
}

//----------------------------------------------------------------------------
size_t BenchmarkConfig::nruns() const
{
    return _nruns;
}

//----------------------------------------------------------------------------
Int32 BenchmarkConfig::noise() const
{
    return _nlevel;
}

//----------------------------------------------------------------------------
String BenchmarkConfig::filename() const
{
    return _fname;
}

//----------------------------------------------------------------------------
size_t BenchmarkConfig::typesize() const
{
   if(_typecode == TypeID::UINT8) return sizeof(UInt8);
   else if(_typecode == TypeID::INT8) return sizeof(Int8);
   else if(_typecode == TypeID::UINT16) return sizeof(UInt16);
   else if(_typecode == TypeID::INT16) return sizeof(Int16);
   else if(_typecode == TypeID::UINT32) return sizeof(UInt32);
   else if(_typecode == TypeID::INT32) return sizeof(Int32);
   else if(_typecode == TypeID::UINT64) return sizeof(UInt64);
   else if(_typecode == TypeID::INT64) return sizeof(Int64);
   else if(_typecode == TypeID::FLOAT32) return sizeof(Float32);
   else if(_typecode == TypeID::FLOAT64) return sizeof(Float64);
   else if(_typecode == TypeID::FLOAT128) return sizeof(Float128);
}

//----------------------------------------------------------------------------
size_t BenchmarkConfig::frame_size() const
{
    return typesize()*nx()*ny();
}

//----------------------------------------------------------------------------
size_t BenchmarkConfig::data_size() const
{
    return frame_size()*nframes();
}

//---------------------------------------------------------------------------
LibID BenchmarkConfig::libid() const
{
    return _libid;
}
//---------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const BenchmarkConfig &c)
{
    o<<"Storing data to: "<<c.filename()<<std::endl;
    o<<"number of runs:  "<<c.nruns()<<std::endl;
    o<<"number of rames: "<<c.nframes()<<std::endl;
    o<<"total data size: "<<c.data_size()/1024./1024.<<std::endl;

    return o;
}

