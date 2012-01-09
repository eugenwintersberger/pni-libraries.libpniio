/*
 * NXFile.cpp
 *
 *  Created on: Jan 6, 2012
 *      Author: Eugen Wintersberger
 */




#include <boost/python.hpp>

#include <pni/utils/Types.hpp>
#include <pni/utils/Shape.hpp>
#include <pni/utils/ArrayObject.hpp>
#include <pni/utils/ScalarObject.hpp>
#include <pni/utils/NumericObject.hpp>


#include "../src/NXObject.hpp"
#include "../src/NXGroup.hpp"
#include "../src/NXFile.hpp"

#include "../src/NX.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;
using namespace boost::python;

void wrap_nxfile(){
    String (NXFile::*get_filename)() const = &NXFile::filename;
    void (NXFile::*set_filename)(const String &) = &NXFile::filename;

    bool (NXFile::*get_readonly)() const = &NXFile::read_only;
    void (NXFile::*set_readonly)(bool) = &NXFile::read_only;

    bool (NXFile::*get_overwrite)() const = &NXFile::overwrite;
    void (NXFile::*set_overwrite)(bool) = &NXFile::overwrite;

    size_t (NXFile::*get_splitsize)()const = &NXFile::split_size;
    void (NXFile::*set_splitsize)(size_t) = &NXFile::split_size;

    void (NXFile::*file_open)() = &NXFile::open;
    NXObject (NXFile::*object_open)(const String &) = &NXFile::open;

    class_<NXFile,bases<NXGroup>,boost::noncopyable >("NXFile")
        .def(init<>())
        .add_property("filename",get_filename,set_filename)
        .add_property("read_only",get_readonly,set_readonly)
        .add_property("overwrite",get_overwrite,set_overwrite)
        .add_property("splitsize",get_splitsize,set_splitsize)
        .def("create",&NXFile::create)
        .def("open",file_open)
        .def("open",object_open)
        .def("close",&NXFile::close)
        .def("flush",&NXFile::flush)
        ;
}

