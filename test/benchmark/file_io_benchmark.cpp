#include "file_io_benchmark.hpp"

//-----------------------------------------------------------------------------
file_io_benchmark::file_io_benchmark():
    _nx(0),
    _ny(0),
    _nframes(0),
    _filename("pninxbm.h5")
{}

//-----------------------------------------------------------------------------
file_io_benchmark::file_io_benchmark(const String &fname,size_t nx,size_t ny,size_t nframes):
    _nx(nx),
    _ny(ny),
    _nframes(nframes),
    _filename(fname)
{}

//-----------------------------------------------------------------------------
