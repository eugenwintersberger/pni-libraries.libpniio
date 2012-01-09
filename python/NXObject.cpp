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

#include "../src/NXObject.hpp"
#include "../src/h5/NXObjectH5Implementation.hpp"
#include "../src/h5/NXGroupH5Implementation.hpp"
#include "../src/h5/NXFileH5Implementation.hpp"
#include "../src/h5/NXFieldH5Implementation.hpp"
#include "../src/h5/NXNumericFieldH5Implementation.hpp"
#include "../src/h5/NXStringFieldH5Implementation.hpp"
#include "../src/h5/NXBinaryFieldH5Implementation.hpp"

#include "NXObject.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;
using namespace boost::python;

void wrap_nxobject(){
    NXOBJECT_WRAPPER(NXObject_NXObject,NXObjectH5Implementation);
	//===================Wrapping NumericObject=================================
    NXOBJECT_WRAPPER(NXObject_NXGroup,NXGroupH5Implementation);
    NXOBJECT_WRAPPER(NXObject_NXField,NXFieldH5Implementation);
    NXOBJECT_WRAPPER(NXObject_NXNumericField,NXNumericFieldH5Implementation);
    NXOBJECT_WRAPPER(NXObject_NXStringField,NXStringFieldH5Implementation);
    NXOBJECT_WRAPPER(NXObject_NXBinaryField,NXBinaryFieldH5Implementation);
    NXOBJECT_WRAPPERNOCOP(NXObject_NXFile,NXFileH5Implementation);
}


