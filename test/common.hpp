#ifndef __COMMON_HPP__
#define __COMMON_HPP__

//header file for the BOOST_CURRENT_FUNCTION macro
#include<boost/current_function.hpp>

//header files for CPPUNIT tests
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

//headers from pniutils
#include<pni/utils/Types.hpp>

//headers from pninx
#include<pni/nx/NX.hpp>

//local template for equality checks
#include "EqualityCheck.hpp"

//set the common namespace
using namespace pni::nx::h5;
using namespace pni::utils;


//common macros
#define PRINT_TEST_FUNCTION_SIG std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

#endif
