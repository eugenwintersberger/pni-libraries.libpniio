#ifndef __NXHELPER_HPP__
#define __NXHELPER_HPP__

#include <pni/nx/NX.hpp>
#include <pni/utils/PNITypes.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/Scalar.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

class NXHelper{
    public:
        static NXGroup createNXpositioner(NXGroup &parent,const String &n,const
                String &unit,const String &name,const String &desc);
        static NXGroup createNXslit(NXGroup &parent,const String &n,const String
                &unit,const String &desc);

        static NXGroup createNXmirror(NXGroup &parent,const String &n);
        
};


#endif
