#pragma once

#include <pni/utils/Types.hpp>
#include <iostream>

using namespace pni::utils;

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
        String _filename;
    public:
        //---------------------------------------------------------------------
        //! default constructor
        file_io_benchmark();

        //---------------------------------------------------------------------
        //! constructor
        file_io_benchmark(const String &fname,size_t nx,size_t ny,size_t nframes);

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
        String filename() const { return _filename; }

        //---------------------------------------------------------------------
        //! set output file
        void filename(const String &f) { _filename = f; }

        //---------------------------------------------------------------------
        //the run function of the benchmark
        virtual void run() {};

        virtual void create() {}

        virtual void close() {}

};
