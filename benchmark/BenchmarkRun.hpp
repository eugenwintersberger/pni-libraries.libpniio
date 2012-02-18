#ifndef __BENCHMARKRUN_HPP__
#define __BENCHMARKRUN_HPP__

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>


using namespace pni::utils;


//! \brief benchmark run base class

//! Base class for all benchmark runs. 
template<typename T> class BenchmarkRun
{
    private:
        Array<T,Buffer> _data;  //!< array holding the data to write
        size_t _nframes;        //!< number of frames to write
        
    public:
        //! default constructor
        BenchmarkRun();
        //! constructor from configuration
        BenchmarkRun(const BenchmarkConfig &conf);
        //! destructor
        virtual ~BenchmarkRun();

        //! data 

        //! Get a constant reference to the data array
        const Array<T,Buffer> &data() const;

        //! run the benchmark
        virtual double run() = 0;

        size_t nframes() const;


};

//-----------------------------------------------------------------------------
template<typename T> BenchmarkRun<T>::BenchmarkRun():
    _data(),
    _nframes(0)
{
}

//-----------------------------------------------------------------------------
template<typename T> BenchmarkRun<T>::BenchmarkRun(const BenchmarkConfig &c):
    _data(Shape({c.nx(),c.ny()})),
    _nframes(c.nframes())
{
    //set initial data values
}

//-----------------------------------------------------------------------------
template<typename T> BenchmarkRun<T>::~BenchmarkRun()
{

}

//-----------------------------------------------------------------------------
template<typename T> const Array<T,Buffer> &BenchmarkRun<T>::data() const
{
    return _data;
}

//-----------------------------------------------------------------------------
template<typename T> size_t BenchmarkRun<T>::nframes() const
{
    return _nframes;
}



#endif
