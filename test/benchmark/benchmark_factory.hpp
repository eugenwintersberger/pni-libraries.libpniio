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
#pragma once

#include <memory>
#include <pni/core/types.hpp>

#include "file_io_benchmark.hpp"

using namespace pni::core;

class benchmark_factory
{
    private:
        //! number of frames along the first dimension
        size_t _nx;
        //! number of frames along the second dimension
        size_t _ny;
        //! total number of frames to write for each benchmark
        size_t _nframes;
        //! name of the output file
        string _fname;

        std::unique_ptr<file_io_benchmark> 
            create_pninx_benchmark(const string &tc,bool random_fill) const;

        std::unique_ptr<file_io_benchmark>
            create_hdf5_benchmark(const string &tc,bool random_fill) const;
    public:
        //===============constructors and destructor===========================
        //! default constructor
        benchmark_factory();

        //---------------------------------------------------------------------
        /*! 
        \brief constructor

        \param fname fname of the output file
        \param nx number of pixels in the first direction
        \param ny number of pixels in the second direction
        \param nframes number of frames to write
        */
        benchmark_factory(const string &fname,size_t nx,size_t ny,size_t nframes);

        //---------------------------------------------------------------------
        /*! 
        \brief create a benchmark

        Create a benchmark for a particular data type and backend. If the
        random_fill argument is true, random data will be written to disk.
        \param type data type
        \param backend the backend to use
        \param random_fill write random data 
        \return unique pointer to the benchmark instance
        */
        std::unique_ptr<file_io_benchmark> create(const string &type,
                                                  const string &backend,
                                                  bool random_fill) const;


};

