#pragma once

#include <pni/utils/Types.hpp>
#include <pni/utils/DArray.hpp>
#include "file_io_benchmark.hpp"

#include <pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

template<typename T> class pninx_io_benchmark : public file_io_benchmark
{
    private:
        //! array holding the buffer for the frame data
        DArray<T> _frame_buffer; 
        NXField   _field;
        NXFile    _file;
    public:
        //===================constructors and destructor=======================
        //! default constructor
        pninx_io_benchmark():
            file_io_benchmark(),
            _frame_buffer()
        {}

        //---------------------------------------------------------------------
        //! constructor
        pninx_io_benchmark(const String &fname,size_t nx,size_t ny,size_t nframes):
            file_io_benchmark(fname,nx,ny,nframes)
        {
            //create the frame buffer
            shape_t fshape{nx,ny};
            _frame_buffer = DArray<T>(fshape);
        }

        //---------------------------------------------------------------------


        //======================public member functions========================
        //! create data structures
        virtual void create();
        virtual void close();

        //---------------------------------------------------------------------
        //! run the benchmark
        virtual void run() ;

};

//-----------------------------------------------------------------------------
template<typename T> void pninx_io_benchmark<T>::create()
{
    //create the file
    _file = NXFile::create_file(filename(),true,0);
    shape_t s{0,nx(),ny()};
    shape_t cs{1,nx(),ny()};
    _field = _file.template create_field<T>("data",s,cs);
}

//-----------------------------------------------------------------------------
template<typename T> void pninx_io_benchmark<T>::close()
{
    _field.close();
    _file.close();
}


//-----------------------------------------------------------------------------
template<typename T> void pninx_io_benchmark<T>::run() 
{
    for(size_t n = 0; n<nframes();n++)
    {
        _field.grow(0);
        _field(n,Slice(0,nx()),Slice(0,ny())).write(_frame_buffer);
        _file.flush();
    }
}
