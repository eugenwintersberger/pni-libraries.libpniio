/*
 * NXObject.hpp
 *
 *  Created on: Jan 8, 2012
 *      Author: Eugen Wintersberger
 */


#ifndef __NXOBJECT_HPP__
#define __NXOBJECT_HPP__

#define NXOBJECT_WRAPPER(wname,imp_type)\
    void (pni::nx::NXObject<imp_type>::*(wname ## _get_string_attribute))\
        (const String &,String &) const\
        = &pni::nx::NXObject<imp_type>::get_attr;\
    \
    void (pni::nx::NXObject<imp_type>::*(wname ## _set_string_attribute))\
        (const String &,const String &) const\
        = &pni::nx::NXObject<imp_type>::set_attr;\
    \
    void (pni::nx::NXObject<imp_type>::*(wname ## _get_scalar_attribute))\
        (const String &,ScalarObject &) const\
        = &pni::nx::NXObject<imp_type>::get_attr;\
    \
    void (pni::nx::NXObject<imp_type>::*(wname ## _set_scalar_attribute))\
        (const String &,const ScalarObject &)\
        const = &pni::nx::NXObject<imp_type>::set_attr;\
    \
    void (pni::nx::NXObject<imp_type>::*(wname ## _get_array_attribute))\
        (const String &,ArrayObject &) const =\
        &pni::nx::NXObject<imp_type>::get_attr;\
    \
    void (pni::nx::NXObject<imp_type>::*(wname ## _set_array_attribute))\
        (const String &,const ArrayObject &)\
        const = &pni::nx::NXObject<imp_type>::set_attr;\
    \
    void (pni::nx::NXObject<imp_type>::*(wname ## _link_this))\
        (const String &) const = &pni::nx::NXObject<imp_type>::link;\
    \
    void (pni::nx::NXObject<imp_type>::*(wname ## _link_this_name))\
        (const String &,const String &) const = &pni::nx::NXObject<imp_type>::link;\
    \
	class_<pni::nx::NXObject<imp_type> >(#wname)\
            .def(init<>())\
            .def("is_open",&pni::nx::NXObject<imp_type>::is_open)\
            .add_property("path",&pni::nx::NXObject<imp_type>::path)\
            .add_property("name",&pni::nx::NXObject<imp_type>::name)\
            .add_property("base",&pni::nx::NXObject<imp_type>::base)\
            .def("set_attr",(wname ## _set_string_attribute))\
            .def("get_attr",(wname ## _get_string_attribute))\
            .def("set_attr",(wname ## _set_scalar_attribute))\
            .def("get_attr",(wname ## _get_scalar_attribute))\
            .def("set_attr",(wname ## _set_array_attribute))\
            .def("get_attr",(wname ## _get_array_attribute))\
            .def("link",(wname ## _link_this))\
            .def("link",(wname ## _link_this_name))\
			;

#define NXOBJECT_WRAPPERNOCOP(wname,imp_type)\
    void (pni::nx::NXObject<imp_type>::*(wname ## _get_string_attribute))\
        (const String &,String &) const\
        = &pni::nx::NXObject<imp_type>::get_attr;\
    \
    void (pni::nx::NXObject<imp_type>::*(wname ## _set_string_attribute))\
        (const String &,const String &) const\
        = &pni::nx::NXObject<imp_type>::set_attr;\
    \
    void (pni::nx::NXObject<imp_type>::*(wname ## _get_scalar_attribute))\
        (const String &,ScalarObject &) const\
        = &pni::nx::NXObject<imp_type>::get_attr;\
    \
    void (pni::nx::NXObject<imp_type>::*(wname ## _set_scalar_attribute))\
        (const String &,const ScalarObject &)\
        const = &pni::nx::NXObject<imp_type>::set_attr;\
    \
    void (pni::nx::NXObject<imp_type>::*(wname ## _get_array_attribute))\
        (const String &,ArrayObject &) const =\
        &pni::nx::NXObject<imp_type>::get_attr;\
    \
    void (pni::nx::NXObject<imp_type>::*(wname ## _set_array_attribute))\
        (const String &,const ArrayObject &)\
        const = &pni::nx::NXObject<imp_type>::set_attr;\
    \
    void (pni::nx::NXObject<imp_type>::*(wname ## _link_this))\
        (const String &) const = &pni::nx::NXObject<imp_type>::link;\
    \
    void (pni::nx::NXObject<imp_type>::*(wname ## _link_this_name))\
        (const String &,const String &) const = &pni::nx::NXObject<imp_type>::link;\
    \
	class_<pni::nx::NXObject<imp_type>,boost::noncopyable >(#wname)\
            .def(init<>())\
            .def("is_open",&pni::nx::NXObject<imp_type>::is_open)\
            .add_property("path",&pni::nx::NXObject<imp_type>::path)\
            .add_property("name",&pni::nx::NXObject<imp_type>::name)\
            .add_property("base",&pni::nx::NXObject<imp_type>::base)\
            .def("set_attr",(wname ## _set_string_attribute))\
            .def("get_attr",(wname ## _get_string_attribute))\
            .def("set_attr",(wname ## _set_scalar_attribute))\
            .def("get_attr",(wname ## _get_scalar_attribute))\
            .def("set_attr",(wname ## _set_array_attribute))\
            .def("get_attr",(wname ## _get_array_attribute))\
            .def("link",(wname ## _link_this))\
            .def("link",(wname ## _link_this_name))\
			;

#endif
