#include "benchmark_factory.hpp"

#include "pniio_io_benchmark.hpp"
#include "hdf5_io_benchmark.hpp"

//-----------------------------------------------------------------------------
benchmark_factory::benchmark_factory():
    _nx(0),
    _ny(0),
    _nframes(0),
    _fname("pninxbm.h5")
{}

//-----------------------------------------------------------------------------
benchmark_factory::benchmark_factory(const string &fname,size_t nx,size_t ny,size_t nframes):
    _nx(nx),
    _ny(ny),
    _nframes(nframes),
    _fname(fname)
{}

//-----------------------------------------------------------------------------
std::unique_ptr<file_io_benchmark> 
benchmark_factory::create_pninx_benchmark(const string &tc) const
{
    typedef std::unique_ptr<file_io_benchmark> ptr_t;
    if(tc == "uint8")
        return ptr_t(new pniio_io_benchmark<uint8>(_fname,_nx,_ny,_nframes));
    if(tc == "int8")
        return ptr_t(new pniio_io_benchmark<int8>(_fname,_nx,_ny,_nframes));
    if(tc == "uint16")
        return ptr_t(new pniio_io_benchmark<uint16>(_fname,_nx,_ny,_nframes));
    if(tc == "int16")
        return ptr_t(new pniio_io_benchmark<int16>(_fname,_nx,_ny,_nframes));
    if(tc == "uint32")
        return ptr_t(new pniio_io_benchmark<uint32>(_fname,_nx,_ny,_nframes));
    if(tc == "int32")
        return ptr_t(new pniio_io_benchmark<int32>(_fname,_nx,_ny,_nframes));

    //if we arrived here something went wrong and we need to 
    //throw an exception

    return nullptr;
}

//-----------------------------------------------------------------------------
std::unique_ptr<file_io_benchmark>
benchmark_factory::create_hdf5_benchmark(const string &tc) const
{
    typedef std::unique_ptr<file_io_benchmark> ptr_t;

    if(tc == "uint8")
        return ptr_t(new hdf5_io_benchmark<uint8>(_fname,_nx,_ny,_nframes));
    if(tc == "int8")
        return ptr_t(new hdf5_io_benchmark<int8>(_fname,_nx,_ny,_nframes));
    if(tc == "uint16")
        return ptr_t(new hdf5_io_benchmark<uint16>(_fname,_nx,_ny,_nframes));
    if(tc == "int16")
        return ptr_t(new hdf5_io_benchmark<int16>(_fname,_nx,_ny,_nframes));
    if(tc == "uint32")
        return ptr_t(new hdf5_io_benchmark<uint32>(_fname,_nx,_ny,_nframes));
    if(tc == "int32")
        return ptr_t(new hdf5_io_benchmark<int32>(_fname,_nx,_ny,_nframes));

    return nullptr;
}


//-----------------------------------------------------------------------------
std::unique_ptr<file_io_benchmark> 
benchmark_factory::create(const string &type,const string &backend) const
{
    if(backend == "pninx")
        return create_pninx_benchmark(type);
    else if(backend == "hdf5")
        return create_hdf5_benchmark(type);
    
    //if we came until here throw an exception
    return nullptr;
}
