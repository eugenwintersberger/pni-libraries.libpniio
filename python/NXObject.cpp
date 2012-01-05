/*
 * NXObject.cpp
 *
 *  Created on: Jan 5, 2012
 *      Author: Eugen Wintersberger
 */




#include <boost/python.hpp>

#include <pni/utils/Types.hpp>
#include <pni/utils/ArrayObject.hpp>
#include <pni/utils/ScalarObject.hpp>

#include "../src/NX.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;
using namespace boost::python;

void wrap_nxobject(){
	//===================Wrapping NumericObject=================================
    void (NXObject::*get_string_attribute)(const String &,String &) const
        = &NXObject::get_attr;
    void (NXObject::*set_string_attribute)(const String &,const String &) const
        = &NXObject::set_attr;
    void (NXObject::*get_scalar_attribute)(const String &,ScalarObject &) const
        = &NXObject::get_attr;
    void (NXObject::*set_scalar_attribute)(const String &,const ScalarObject &)
        const = &NXObject::set_attr;
    void (NXObject::*get_array_attribute)(const String &,ArrayObject &) const =
        &NXObject::get_attr;
    void (NXObject::*set_array_attribute)(const String &,const ArrayObject &)
        const = &NXObject::set_attr;

    void (NXObject::*link_this)(const String &) const = &NXObject::link;
    void (NXObject::*link_this_name)(const String &,const String &) const =
        &NXObject::link;
	class_<NXObject>("NXObject")
			.def(init<>())
            .def("is_open",&NXObject::is_open)
            .add_property("path",&NXObject::path)
            .add_property("name",&NXObject::name)
            .add_property("base",&NXObject::base)
            .def("set_attr",set_string_attribute)
            .def("get_attr",get_string_attribute)
            .def("set_attr",set_scalar_attribute)
            .def("get_attr",get_scalar_attribute)
            .def("set_attr",set_array_attribute)
            .def("get_attr",get_array_attribute)
            .def("link",link_this)
            .def("link",link_this_name)
			;
}


