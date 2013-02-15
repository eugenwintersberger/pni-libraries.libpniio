/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: Dec 17, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

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
benchmark_factory::create_pninx_benchmark(const string &tc,bool random_fill) const
{
    typedef std::unique_ptr<file_io_benchmark> ptr_t;
    if(tc == "uint8")
        return ptr_t(new pniio_io_benchmark<uint8>(_fname,_nx,_ny,_nframes,random_fill));
    if(tc == "int8")
        return ptr_t(new pniio_io_benchmark<int8>(_fname,_nx,_ny,_nframes,random_fill));
    if(tc == "uint16")
        return ptr_t(new pniio_io_benchmark<uint16>(_fname,_nx,_ny,_nframes,random_fill));
    if(tc == "int16")
        return ptr_t(new pniio_io_benchmark<int16>(_fname,_nx,_ny,_nframes,random_fill));
    if(tc == "uint32")
        return ptr_t(new pniio_io_benchmark<uint32>(_fname,_nx,_ny,_nframes,random_fill));
    if(tc == "int32")
        return ptr_t(new pniio_io_benchmark<int32>(_fname,_nx,_ny,_nframes,random_fill));

    //if we arrived here something went wrong and we need to 
    //throw an exception

    return std::unique_ptr<file_io_benchmark>();
}

//-----------------------------------------------------------------------------
std::unique_ptr<file_io_benchmark>
benchmark_factory::create_hdf5_benchmark(const string &tc,bool random_fill) const
{
    typedef std::unique_ptr<file_io_benchmark> ptr_t;

    if(tc == "uint8")
        return ptr_t(new hdf5_io_benchmark<uint8>(_fname,_nx,_ny,_nframes,random_fill));
    if(tc == "int8")
        return ptr_t(new hdf5_io_benchmark<int8>(_fname,_nx,_ny,_nframes,random_fill));
    if(tc == "uint16")
        return ptr_t(new hdf5_io_benchmark<uint16>(_fname,_nx,_ny,_nframes,random_fill));
    if(tc == "int16")
        return ptr_t(new hdf5_io_benchmark<int16>(_fname,_nx,_ny,_nframes,random_fill));
    if(tc == "uint32")
        return ptr_t(new hdf5_io_benchmark<uint32>(_fname,_nx,_ny,_nframes,random_fill));
    if(tc == "int32")
        return ptr_t(new hdf5_io_benchmark<int32>(_fname,_nx,_ny,_nframes,random_fill));

    return std::unique_ptr<file_io_benchmark>();
}


//-----------------------------------------------------------------------------
std::unique_ptr<file_io_benchmark> 
benchmark_factory::create(const string &type,
                          const string &backend,bool random_fill) const
{
    if(backend == "pninx")
        return create_pninx_benchmark(type,random_fill);
    else if(backend == "hdf5")
        return create_hdf5_benchmark(type,random_fill);
    
    //if we came until here throw an exception
    return std::unique_ptr<file_io_benchmark>();
}
