#ifndef __H5TYPES_HPP__
#define __H5TYPES_HPP__

extern "C"{
#include <hdf5.h>
}

#include <boost/shared_ptr.hpp>

namespace nx{
namespace h5{

typedef boost::shared_ptr<hid_t> hidsptr;  //!< define a shared pointer for HDF5 IDs



//end of namespace
}
}



#endif
