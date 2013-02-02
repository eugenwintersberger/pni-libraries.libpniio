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

#include <pni/core/types.hpp>
#include <iostream>

using namespace pni::core;

class file_io_benchmark
{
    private:
        //! number of pixels along first dimension
        size_t _nx; 
        //! number of pixels along second dimension
        size_t _ny;
        //! number of frames to write
        size_t _nframes; 
        //! name of the output file
        string _filename;
    public:
        //---------------------------------------------------------------------
        //! default constructor
        file_io_benchmark();

        //---------------------------------------------------------------------
        //! constructor
        file_io_benchmark(const string &fname,size_t nx,size_t ny,size_t nframes);

        //=====================public member functions=========================
        //! get nx
        size_t nx() const { return _nx; }

        //---------------------------------------------------------------------
        //! set nx
        void   nx(size_t nx) { _nx = nx; }

        //---------------------------------------------------------------------
        //! get ny
        size_t ny() const { return _ny; }

        //---------------------------------------------------------------------
        //! set ny
        void   ny(size_t ny) { _ny = ny; }

        //---------------------------------------------------------------------
        //! get number of frames
        size_t nframes() const { return _nframes; }

        //---------------------------------------------------------------------
        //! set number of frames
        void   nframes(size_t n) { _nframes = n; }

        //---------------------------------------------------------------------
        //! get output file name
        string filename() const { return _filename; }

        //---------------------------------------------------------------------
        //! set output file
        void filename(const string &f) { _filename = f; }

        //---------------------------------------------------------------------
        //the run function of the benchmark
        virtual void run() {};

        virtual void create() {}

        virtual void close() {}

};
