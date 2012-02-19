#include "BenchmarkConfig.hpp"


//-----------------------------------------------------------------------------
BenchmarkConfig::BenchmarkConfig(int argc,char **argv)
{
    if(argc<9){
        std::cerr<<"Usage: <prog> <lib> <type> <nx> <ny> <nframes> <nruns> "
            "<noiselevel> <filename>lx"<<std::endl;
        exit(1);
    }

    //read command line arguments
    String libcode(argv[1]);
    if(libcode == "pninx"){
        std::cout<<"Using PNINX for writing data ..."<<std::endl;
        _libid = LibID::PNINX;
    }else if(libcode == "hdf5"){
        std::cout<<"using plain HDF5 for writing data ..."<<std::endl;
        _libid = LibID::HDF5;
    }else{
        std::cerr<<"Unknown library code - aborting!"<<std::endl;
        exit(1);
    }

    String typestr(argv[2]);
    if(typestr == "uint8")         _typecode = TypeID::UINT8;
    else if(typestr == "int8")     _typecode = TypeID::INT8;
    else if(typestr == "uint16")   _typecode = TypeID::UINT16;
    else if(typestr == "int16")    _typecode = TypeID::INT16;
    else if(typestr == "uint32")   _typecode = TypeID::UINT32;
    else if(typestr == "int32")    _typecode = TypeID::INT32;
    else if(typestr == "uint64")   _typecode = TypeID::UINT64;
    else if(typestr == "int64")    _typecode = TypeID::INT64;
    else if(typestr == "float32")  _typecode = TypeID::FLOAT32;
    else if(typestr == "float64")  _typecode = TypeID::FLOAT64;
    else if(typestr == "float128") _typecode = TypeID::FLOAT128;
    else{
        std::cerr<<"Unkown type code - aborting!"<<std::endl;
        exit(1);
    }


    _nx      = (size_t)atoi(argv[3]);
    _ny      = (size_t)atoi(argv[4]);
    _nframes = (size_t)(atoi(argv[5])); //read the number of points
    _nruns   = (size_t)(atoi(argv[6]));
    _nlevel  = (Int32)atoi(argv[7]);
    _fname   = String(argv[8]);
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

