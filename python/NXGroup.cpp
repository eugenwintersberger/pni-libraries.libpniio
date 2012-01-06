/*
 * NXGroup.cpp
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

#include "../src/NX.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;
using namespace boost::python;


void wrap_nxgroup(){
    NXGroup (NXGroup::*create_group)(const String &) const = &NXGroup::create_group;
    NXGroup (NXGroup::*create_typed_group)(const String &,const String &) const =
        &NXGroup::create_group;

    NXNumericField (NXGroup::*create_numfield1)
        (const String &,TypeID,const Shape &,const String &,const String &) const =
        &NXGroup::create_numericfield;

    NXNumericField (NXGroup::*create_numfield_deflate1)
        (const String &,TypeID,const Shape &,const String &,const String
         &,NXDeflateFilter &) const = 
        &NXGroup::create_numericfield;
    NXNumericField (NXGroup::*create_numfield_lzf1)
        (const String &,TypeID,const Shape &,const String &,const String
         &,NXLZFFilter &) const = &NXGroup::create_numericfield;

    NXNumericField (NXGroup::*create_numfield2)(const ArrayObject &) const =
        &NXGroup::create_numericfield;
    NXNumericField (NXGroup::*create_numfield_deflate2)(const ArrayObject
            &,NXDeflateFilter &) const = &NXGroup::create_numericfield;
    NXNumericField (NXGroup::*create_numfield_lzf2)(const ArrayObject
            &,NXLZFFilter &) const = &NXGroup::create_numericfield;

    NXNumericField (NXGroup::*create_numfield3)
        (const String &,TypeID,const String &,const String &) const
        = &NXGroup::create_numericfield;
    NXNumericField (NXGroup::*create_numfield4)(const ScalarObject &) const =
        &NXGroup::create_numericfield;

    class_<NXGroup,bases<NXObject> >("NXGroup")
        .def(init<>())
        .def("create_group",create_group)
        .def("create_group",create_typed_group)
        .def("create_numericfield",create_numfield1)
        .def("create_numericfield",create_numfield_deflate1)
        .def("create_numericfield",create_numfield_lzf1)
        .def("create_numericfield",create_numfield2)
        .def("create_numericfield",create_numfield_deflate2)
        .def("create_numericfield",create_numfield_lzf2)
        .def("create_numericfield",create_numfield3)
        .def("create_numericfield",create_numfield4)
        .def("create_stringfield",&NXGroup::create_stringfield)
        .def("create_binaryfield",&NXGroup::create_binaryfield)
        .def("open",&NXGroup::open)
        .def("close",&NXGroup::close)
        .def("exists",&NXGroup::exists)
        .def("remove",&NXGroup::remove)
        ;

}

