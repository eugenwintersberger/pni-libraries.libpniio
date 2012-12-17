#pragma once

#include "file_io_benchmark.hpp"

extern "C" {
    #include <hdf5.h>
}

template<typename T> struct type2hdftype;

#define TC2HDFTYPEMAP(stype,hdftype)\
    template<> struct type2hdftype<stype>\
    {\
        static hid_t type()\
        {\
            return hdftype;\
        }\
    }

TC2HDFTYPEMAP(UInt8,H5T_NATIVE_UCHAR);
TC2HDFTYPEMAP(Int8,H5T_NATIVE_SCHAR);
TC2HDFTYPEMAP(UInt16,H5T_NATIVE_USHORT);
TC2HDFTYPEMAP(Int16,H5T_NATIVE_SHORT);
TC2HDFTYPEMAP(UInt32,H5T_NATIVE_UINT);
TC2HDFTYPEMAP(Int32,H5T_NATIVE_INT);
TC2HDFTYPEMAP(UInt64,H5T_NATIVE_ULONG);
TC2HDFTYPEMAP(Int64,H5T_NATIVE_LONG);

template<typename T> class hdf5_io_benchmark : public file_io_benchmark
{
    private:
        hid_t _file;
        hid_t _file_space;
        hid_t _memory_space;
        hid_t _dataset;
        hid_t _datatype;
        T *_frame_data;

    public:
        //=====================constructor and destructors=====================
        //! default constructor
        hdf5_io_benchmark():file_io_benchmark()
        {}

        //---------------------------------------------------------------------
        //! constructor
        hdf5_io_benchmark(const String &fname,size_t nx,size_t ny,size_t
                nframes):
            file_io_benchmark(fname,nx,ny,nframes)
        {
            _frame_data = new T[nx*ny]; 
        }

        //---------------------------------------------------------------------
        //! destructor
        ~hdf5_io_benchmark()
        {
            if(_frame_data) delete [] _frame_data;
        }

        //=======================public member functions=======================
        //! create file and dataspace
        virtual void create();

        //! close file and datasets
        virtual void close();

        //! run the benchmark
        virtual void run();
};

//-----------------------------------------------------------------------------
template<typename T> void hdf5_io_benchmark<T>::create()
{
    //create data file
    _file = H5Fcreate(filename().c_str(),H5F_ACC_TRUNC,H5P_DEFAULT,H5P_DEFAULT);

    //create dtype
    _datatype = H5Tcopy(type2hdftype<T>::type());

    //create data-space on disk
    hsize_t fdims[] = {0,nx(),ny()};
    hsize_t fmaxdims[] = {H5S_UNLIMITED,nx(),ny()};

    _file_space = H5Screate_simple(3,fdims,fmaxdims);

    //create data-space in memory
    hsize_t mdims[] = {nx(),ny()};
    _memory_space = H5Screate_simple(2,mdims,mdims);

    //create the property list for the dataset
    hid_t plist = H5Pcreate(H5P_DATASET_CREATE);
    H5Pset_layout(plist,H5D_CHUNKED);
    fdims[0] = 1;
    H5Pset_chunk(plist,3,fdims);
    fdims[0] = 0;
    //create the dataset
    _dataset = H5Dcreate2(_file,"data",_datatype,_file_space,
                           H5P_DEFAULT,plist,H5P_DEFAULT);

    H5Pclose(plist);
}

//-----------------------------------------------------------------------------
template<typename T> void hdf5_io_benchmark<T>::close()
{
    H5Tclose(_datatype);
    H5Sclose(_file_space);
    H5Sclose(_memory_space);
    H5Dclose(_dataset);
    H5Fclose(_file);

}

//-----------------------------------------------------------------------------
template<typename T> void hdf5_io_benchmark<T>::run()
{
    hsize_t fdims[] = {0,nx(),ny()};
    hsize_t offset[] = {0,0,0};
    hsize_t count[] = {1,nx(),ny()};
    
    for(size_t n=0;n<nframes();n++)
    {
        fdims[0]++;
        H5Dset_extent(_dataset,fdims);
        _file_space = H5Dget_space(_dataset);

        H5Sselect_hyperslab(_file_space,H5S_SELECT_SET,offset,NULL,count,NULL);
        H5Dwrite(_dataset,_datatype,_memory_space,_file_space,
                 H5P_DEFAULT,_frame_data);

        H5Fflush(_file,H5F_SCOPE_LOCAL);
        offset[0]++;
    }

}
