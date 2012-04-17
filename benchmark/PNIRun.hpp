#ifndef __PNIRUN_HPP__
#define __PNIRUN_HPP__

#include <pni/nx/NX.hpp>

using namespace pni::nx::h5;

#include "BenchmarkRun.hpp"
#include "Timer.hpp"


template<typename T> class PNIRun:public BenchmarkRun<T>
{
    private:
        NXFile _file;   //!< nexus file holding the data
        NXField _field; //!< nexus field storing data
        NXSelection _selection; //!< selection to store data
    public:
        PNIRun();
        PNIRun(const BenchmarkConfig &conf);
        ~PNIRun();

        virtual double run();

};

template<typename T> PNIRun<T>::PNIRun():BenchmarkRun<T>()
{
}

template<typename T> PNIRun<T>::PNIRun(const BenchmarkConfig &c):
    BenchmarkRun<T>(c)
{
    //create the file where to store data
    _file = NXFile::create_file(c.filename(),true,0);

    //create data field
    _field = _file.create_field<T>("data",{0,c.nx(),c.ny()});
    _selection = _field.selection();
    _selection.offset({0,0,0});
    _selection.count({1,c.nx(),c.ny()});

}

template<typename T> PNIRun<T>::~PNIRun()
{
    _field.close();
    _file.close();
}

template<typename T> double PNIRun<T>::run()
{
    double start = Timer::time();
    for(size_t i=0;i<this->nframes();i++){
        _field.grow(0);
        _selection.offset(0,i);
        _selection.write(this->data());
        _file.flush();
    }
    double stop = Timer::time();
    return stop-start;
}





#endif
