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


#include "../src/NXGroup.hpp"
#include "../src/h5/NXGroupH5Implementation.hpp"
#include "../src/h5/NXFileH5Implementation.hpp"
#include "../src/NXNumericField.hpp"
#include "../src/h5/H5DeflateFilter.hpp"
#include "../src/h5/H5LZFFilter.hpp"
#include "../src/NXFilter.hpp"
#include "../src/NXImpMap.hpp"


using namespace pni::utils;
using namespace pni::nx::h5;
using namespace boost::python;


#define GROUP_WRAPPER(wname,imp_type)\
    pni::nx::NXGroup<typename pni::nx::NXImpMap<imp_type::IMPCODE>::GroupImplementation>\
        (pni::nx::NXGroup<imp_type>::*(wname ## _create_group))\
        (const String &) const = &pni::nx::NXGroup<imp_type>::create_group;\
    pni::nx::NXGroup<typename pni::nx::NXImpMap<imp_type::IMPCODE>::GroupImplementation> \
        (pni::nx::NXGroup<imp_type>::*(wname ## _create_typed_group))\
        (const String &,const String &) const \
        =&pni::nx::NXGroup<imp_type>::create_group;\
    \
    pni::nx::NXNumericField<typename pni::nx::NXImpMap<imp_type::IMPCODE>::NumericFieldImplementation>\
        (pni::nx::NXGroup<imp_type>::*(wname ## _create_numfield1))\
        (const String &,TypeID,const Shape &,const String &,const String &)const \
          = &pni::nx::NXGroup<imp_type>::create_numericfield;\
    \
    pni::nx::NXNumericField<typename pni::nx::NXImpMap<imp_type::IMPCODE>::NumericFieldImplementation>\
        (pni::nx::NXGroup<imp_type>::*(wname ## _create_numfield_deflate1))\
        (const String &,TypeID,const Shape &,const String &,const String\
         &,pni::nx::NXFilter<H5DeflateFilter> &) const\
        =  &pni::nx::NXGroup<imp_type>::create_numericfield;\
    pni::nx::NXNumericField<typename pni::nx::NXImpMap<imp_type::IMPCODE>::NumericFieldImplementation>\
        (pni::nx::NXGroup<imp_type>::*(wname ## _create_numfield_lzf1))\
        (const String &,TypeID,const Shape &,const String &,const String\
         &,pni::nx::NXFilter<H5LZFFilter> &) const \
        = &pni::nx::NXGroup<imp_type>::create_numericfield;\
    \
    pni::nx::NXNumericField<typename pni::nx::NXImpMap<imp_type::IMPCODE>::NumericFieldImplementation>\
        (pni::nx::NXGroup<imp_type>::*(wname ## _create_numfield2))\
        (const ArrayObject &) const = &pni::nx::NXGroup<imp_type>::create_numericfield;\
    pni::nx::NXNumericField<typename pni::nx::NXImpMap<imp_type::IMPCODE>::NumericFieldImplementation>\
            (pni::nx::NXGroup<imp_type>::*(wname ## _create_numfield_deflate2))\
            (const ArrayObject &,pni::nx::NXFilter<H5DeflateFilter> &) const\
            = &pni::nx::NXGroup<imp_type>::create_numericfield;\
    pni::nx::NXNumericField<typename pni::nx::NXImpMap<imp_type::IMPCODE>::NumericFieldImplementation>\
            (pni::nx::NXGroup<imp_type>::*(wname ## _create_numfield_lzf2))\
            (const ArrayObject &,pni::nx::NXFilter<H5LZFFilter> &) const\
            = &pni::nx::NXGroup<imp_type>::create_numericfield;\
    \
    pni::nx::NXNumericField<typename pni::nx::NXImpMap<imp_type::IMPCODE>::NumericFieldImplementation>\
        (pni::nx::NXGroup<imp_type>::*(wname ## _create_numfield3))\
        (const String &,TypeID,const String &,const String &) const\
        = &pni::nx::NXGroup<imp_type>::create_numericfield;\
    pni::nx::NXNumericField<typename pni::nx::NXImpMap<imp_type::IMPCODE>::NumericFieldImplementation>\
        (pni::nx::NXGroup<imp_type>::*(wname ## _create_numfield4))\
        (const ScalarObject &) const =\
        &pni::nx::NXGroup<imp_type>::create_numericfield;\
    \
    class_<pni::nx::NXGroup<imp_type>,bases<pni::nx::NXObject<imp_type> > >(#wname)\
        .def(init<>())\
        .def("create_group",(wname ## _create_group))\
        .def("create_group",(wname ## _create_typed_group))\
        .def("create_numericfield",(wname ## _create_numfield1))\
        .def("create_numericfield",(wname ## _create_numfield_deflate1))\
        .def("create_numericfield",(wname ## _create_numfield_lzf1))\
        .def("create_numericfield",(wname ## _create_numfield2))\
        .def("create_numericfield",(wname ## _create_numfield_deflate2))\
        .def("create_numericfield",(wname ## _create_numfield_lzf2))\
        .def("create_numericfield",(wname ## _create_numfield3))\
        .def("create_numericfield",(wname ## _create_numfield4))\
        .def("create_stringfield",&pni::nx::NXGroup<imp_type>::create_stringfield)\
        .def("create_binaryfield",&pni::nx::NXGroup<imp_type>::create_binaryfield)\
        .def("open",&pni::nx::NXGroup<imp_type>::open)\
        .def("close",&pni::nx::NXGroup<imp_type>::close)\
        .def("exists",&pni::nx::NXGroup<imp_type>::exists)\
        .def("remove",&pni::nx::NXGroup<imp_type>::remove)\
        ;

#define GROUP_WRAPPERNOCOP(wname,imp_type)\
    pni::nx::NXGroup<typename pni::nx::NXImpMap<imp_type::IMPCODE>::GroupImplementation>\
        (pni::nx::NXGroup<imp_type>::*(wname ## _create_group))\
        (const String &) const = &pni::nx::NXGroup<imp_type>::create_group;\
    pni::nx::NXGroup<typename pni::nx::NXImpMap<imp_type::IMPCODE>::GroupImplementation> \
        (pni::nx::NXGroup<imp_type>::*(wname ## _create_typed_group))\
        (const String &,const String &) const \
        =&pni::nx::NXGroup<imp_type>::create_group;\
    \
    pni::nx::NXNumericField<typename pni::nx::NXImpMap<imp_type::IMPCODE>::NumericFieldImplementation>\
        (pni::nx::NXGroup<imp_type>::*(wname ## _create_numfield1))\
        (const String &,TypeID,const Shape &,const String &,const String &)const \
          = &pni::nx::NXGroup<imp_type>::create_numericfield;\
    \
    pni::nx::NXNumericField<typename pni::nx::NXImpMap<imp_type::IMPCODE>::NumericFieldImplementation>\
        (pni::nx::NXGroup<imp_type>::*(wname ## _create_numfield_deflate1))\
        (const String &,TypeID,const Shape &,const String &,const String\
         &,pni::nx::NXFilter<H5DeflateFilter> &) const\
        =  &pni::nx::NXGroup<imp_type>::create_numericfield;\
    pni::nx::NXNumericField<typename pni::nx::NXImpMap<imp_type::IMPCODE>::NumericFieldImplementation>\
        (pni::nx::NXGroup<imp_type>::*(wname ## _create_numfield_lzf1))\
        (const String &,TypeID,const Shape &,const String &,const String\
         &,pni::nx::NXFilter<H5LZFFilter> &) const \
        = &pni::nx::NXGroup<imp_type>::create_numericfield;\
    \
    pni::nx::NXNumericField<typename pni::nx::NXImpMap<imp_type::IMPCODE>::NumericFieldImplementation>\
        (pni::nx::NXGroup<imp_type>::*(wname ## _create_numfield2))\
        (const ArrayObject &) const = &pni::nx::NXGroup<imp_type>::create_numericfield;\
    pni::nx::NXNumericField<typename pni::nx::NXImpMap<imp_type::IMPCODE>::NumericFieldImplementation>\
            (pni::nx::NXGroup<imp_type>::*(wname ## _create_numfield_deflate2))\
            (const ArrayObject &,pni::nx::NXFilter<H5DeflateFilter> &) const\
            = &pni::nx::NXGroup<imp_type>::create_numericfield;\
    pni::nx::NXNumericField<typename pni::nx::NXImpMap<imp_type::IMPCODE>::NumericFieldImplementation>\
            (pni::nx::NXGroup<imp_type>::*(wname ## _create_numfield_lzf2))\
            (const ArrayObject &,pni::nx::NXFilter<H5LZFFilter> &) const\
            = &pni::nx::NXGroup<imp_type>::create_numericfield;\
    \
    pni::nx::NXNumericField<typename pni::nx::NXImpMap<imp_type::IMPCODE>::NumericFieldImplementation>\
        (pni::nx::NXGroup<imp_type>::*(wname ## _create_numfield3))\
        (const String &,TypeID,const String &,const String &) const\
        = &pni::nx::NXGroup<imp_type>::create_numericfield;\
    pni::nx::NXNumericField<typename pni::nx::NXImpMap<imp_type::IMPCODE>::NumericFieldImplementation>\
        (pni::nx::NXGroup<imp_type>::*(wname ## _create_numfield4))\
        (const ScalarObject &) const =\
        &pni::nx::NXGroup<imp_type>::create_numericfield;\
    \
    class_<pni::nx::NXGroup<imp_type>,bases<pni::nx::NXObject<imp_type> >,boost::noncopyable >(#wname)\
        .def(init<>())\
        .def("create_group",(wname ## _create_group))\
        .def("create_group",(wname ## _create_typed_group))\
        .def("create_numericfield",(wname ## _create_numfield1))\
        .def("create_numericfield",(wname ## _create_numfield_deflate1))\
        .def("create_numericfield",(wname ## _create_numfield_lzf1))\
        .def("create_numericfield",(wname ## _create_numfield2))\
        .def("create_numericfield",(wname ## _create_numfield_deflate2))\
        .def("create_numericfield",(wname ## _create_numfield_lzf2))\
        .def("create_numericfield",(wname ## _create_numfield3))\
        .def("create_numericfield",(wname ## _create_numfield4))\
        .def("create_stringfield",&pni::nx::NXGroup<imp_type>::create_stringfield)\
        .def("create_binaryfield",&pni::nx::NXGroup<imp_type>::create_binaryfield)\
        .def("open",&pni::nx::NXGroup<imp_type>::open)\
        .def("close",&pni::nx::NXGroup<imp_type>::close)\
        .def("exists",&pni::nx::NXGroup<imp_type>::exists)\
        .def("remove",&pni::nx::NXGroup<imp_type>::remove)\
        ;
void wrap_nxgroup(){
    GROUP_WRAPPER(NXGroup_NXGroup,NXGroupH5Implementation);
    GROUP_WRAPPERNOCOP(NXGroup_NXFile,NXFileH5Implementation);
}
