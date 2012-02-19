

#ifndef __BENCHMARKCONFIG_HPP__
#define __BENCHMARKCONFIG_HPP__

#include<iostream>
#include<cstdlib>
#include<cstdio>

#include<pni/utils/Types.hpp>

using namespace pni::utils;

enum class LibID { HDF5,PNINX};

//! class for benchmark configuration

//! This class holds the entire configuration for a a single
//! benchmark.
class BenchmarkConfig{
    private:
        LibID  _libid;    //!< id which library to use
        TypeID _typecode; //!< typecode of the datatype to use
        size_t _nx;       //!< number of channels in x-direction
        size_t _ny;       //!< number of channels in y-direction
        size_t _nframes;  //!< number of frames to store per run
        size_t _nruns;    //!< number of runs to perform
        UInt32 _nlevel;   //!< noise level used for test data
        String _fname;    //!< file name to use
    public:
        //! constructor
        BenchmarkConfig(int argc,char **argv);

        //! return typecode
        
        //! Returns the typecode for the datatype which should 
        //! be used.
        //! \return typecode
        TypeID typecode() const;
       
        //! return nx

        //! Returns the number of channels in x-direction of the
        //! detector frame.
        //! \return number of channels along x
        size_t nx() const;

        //! return ny

        //! Returns the number of channels in y-direction of the 
        //! detector frame.
        //! \return number of channels along y
        size_t ny() const;

        //! return number of frames

        //! Returns the total number of frames that will be stored during
        //! a single run.
        //! \return number of frames
        size_t nframes() const;

        //! return number of runs

        //! Returns the number of runs for over which benchmark data 
        //! will be averaged.
        //! \return number of runs
        size_t nruns() const;

        //! return filename

        //! Return the name of the file used to store data.
        //! \return filename
        String filename() const;

        //! return noise level

        //! In some cases one want to use a particular noise level
        //! in the stored data. This might be useful to test the 
        //! performance of compression algorithms. This method 
        //! returns the noise level entered by the use.
        //! \return noise level
        Int32 noise() const;

        //! return frame size

        //! Return the total size of a single frame in MByte.
        //! \return frame size in MByte
        size_t frame_size() const;

        //! return data size
        
        //! Return the total size of data written to the file in MByte.
        //! \return data size in MByte
        size_t data_size() const;

        //! return type size

        //! Return the size of the datatype used for the payload data
        //! in bytes.
        //! \return datatype size in bytes
        size_t typesize() const;

        //! return library id

        //! Returns the library ID to use for the benchmark.
        //! \return library id
        LibID libid() const;

};

#endif
