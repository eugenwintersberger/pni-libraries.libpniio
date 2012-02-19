#ifndef __HDF5RUN_HPP__
#define __HDF5RUN_HPP__

extern "C"{
#include <hdf5.h>
}

#include "BenchmarkRun.hpp"
#include "BenchmarkConfig.hpp"
#include "Timer.hpp"

template<typename T> class H5TypeTrait;

template<> class H5TypeTrait<UInt8>{
    public:
        static hid_t H5Type(){
            return H5Tcopy(H5T_NATIVE_UCHAR);
        }
};

template<> class H5TypeTrait<Int8>{
    public:
        static hid_t H5Type(){
            return H5Tcopy(H5T_NATIVE_CHAR);
        }
};

template<> class H5TypeTrait<UInt16>{
    public:
        static hid_t H5Type(){
            return H5Tcopy(H5T_NATIVE_USHORT);
        }
};

template<> class H5TypeTrait<Int16>{
    public:
        static hid_t H5Type(){
            return H5Tcopy(H5T_NATIVE_SHORT);
        }
};

template<> class H5TypeTrait<UInt32>{
    public:
        static hid_t H5Type(){
            return H5Tcopy(H5T_NATIVE_UINT);
        }
};

template<> class H5TypeTrait<Int32>{
    public:
        static hid_t H5Type(){
            return H5Tcopy(H5T_NATIVE_INT);
        }
};

template<> class H5TypeTrait<UInt64>{
    public:
        static hid_t H5Type(){
            return H5Tcopy(H5T_NATIVE_LONG);
        }
};

template<> class H5TypeTrait<Int64>{
    public:
        static hid_t H5Type(){
            return H5Tcopy(H5T_NATIVE_ULONG);
        }
};

template<> class H5TypeTrait<Float32>{
    public:
        static hid_t H5Type(){
            return H5Tcopy(H5T_NATIVE_FLOAT);
        }
};

template<> class H5TypeTrait<Float64>{
    public:
        static hid_t H5Type(){
            return H5Tcopy(H5T_NATIVE_DOUBLE);
        }
};

template<> class H5TypeTrait<Float128>{
    public:
        static hid_t H5Type(){
            return H5Tcopy(H5T_NATIVE_LDOUBLE);
        }
};

//! \brief

//! Implementation of a benchmark for plain HDF5.
template<typename T> class HDF5Run:public BenchmarkRun<T>
{
    private:
        hid_t _file;          //!< file id 
        hid_t _type;          //!< datatype id
        hid_t _file_space;    //!< dataspace in the file
        hid_t _dataset;       //!< dataset to write data to
        hid_t _mem_space;     //!< memory dataspace
        hsize_t _fdims[3];    //!< buffer for frame size
        hsize_t _fmaxdims[3]; //!< maximum number of elements
        hsize_t _mdims[2];    //!< size in memory
        hsize_t _offset[3];   //!< selection offset
        hsize_t _counts[3];   //!< selection counts
    public:
        HDF5Run();
        HDF5Run(const BenchmarkConfig &c);
        ~HDF5Run();

        virtual double run();
        
};

//-----------------------------------------------------------------------------
template<typename T> HDF5Run<T>::HDF5Run():BenchmarkRun<T>()
{
}

//-----------------------------------------------------------------------------
template<typename T> HDF5Run<T>::HDF5Run(const BenchmarkConfig &c):
    BenchmarkRun<T>(c)
{
    hid_t plist;

    //create data file
    _file = H5Fcreate(c.filename().c_str(), H5F_ACC_TRUNC,H5P_DEFAULT,H5P_DEFAULT);

    //create dtype
    _type = H5TypeTrait<T>::H5Type();

    //create data-space on disk
    _fdims[0] = 0; 
    _fdims[1] = c.nx(); 
    _fdims[2] = c.ny();

    _fmaxdims[0] = H5S_UNLIMITED; 
    _fmaxdims[1] = c.nx(); 
    _fmaxdims[2] = c.ny();
    
    _file_space = H5Screate_simple(3,_fdims,_fmaxdims);

    //create data-space in memory
    _mdims[0] = c.nx(); _mdims[1] = c.ny();
    _mem_space = H5Screate_simple(2,_mdims,_mdims);

    //create the property list for the dataset
    plist = H5Pcreate(H5P_DATASET_CREATE);
    H5Pset_layout(plist,H5D_CHUNKED);
    _fdims[0] = 1;
    H5Pset_chunk(plist,3,_fdims);
    _fdims[0] = 0;
    //create the dataset
    _dataset = H5Dcreate2(_file,"detector",_type,_file_space,
                           H5P_DEFAULT,plist,H5P_DEFAULT);

    //write data
    _offset[0] = 0; _offset[1] = 0; _offset[2] = 0;
    _counts[0] = 1; _counts[1] = c.nx(); _counts[2] = c.ny();

    H5Pclose(plist);
}

//-----------------------------------------------------------------------------
template<typename T> HDF5Run<T>::~HDF5Run()
{

    H5Tclose(_type);
    H5Sclose(_file_space);
    H5Sclose(_mem_space);
    H5Dclose(_dataset);
    H5Fclose(_file);
}

//-----------------------------------------------------------------------------
template<typename T> double HDF5Run<T>::run()
{
    double start = Timer::time();

    //start with writting data
    for(size_t i=0;i<this->nframes();i++){
        //resize the dataset
        _fdims[0]++;
        
        H5Dset_extent(_dataset,_fdims);
        _file_space = H5Dget_space(_dataset); 

        //set the selection
        _offset[0] = i;
        H5Sselect_hyperslab(_file_space,H5S_SELECT_SET,_offset,NULL,_counts,NULL);

        //write data
        H5Dwrite(_dataset,_type,_mem_space,_file_space,H5P_DEFAULT,this->data().ptr());

        //flush data to disk
        H5Fflush(_file,H5F_SCOPE_LOCAL);
    }
    
    double stop = Timer::time();

    return (stop-start);
}

#endif
