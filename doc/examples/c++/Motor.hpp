#ifndef __MOTOR_HPP__
#define __MOTOR_HPP__

#include <pni/nx/NX.hpp>
#include <pni/utils/PNITypes.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/Scalar.hpp>

class Motor{
    private:
        NXGroup _group;
    public:
        Motor();
        Motor(const NXGroup &parent,const String &n,const String &u);
        virtual ~Motor();

        String name();
        void name(const String &n);

        String description();
        void description(const String &n);

        
        

};

#endif
