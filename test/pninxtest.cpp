//libddf unit test system

#include<iostream>
#include<string>
#include<vector>

#include<cppunit/extensions/HelperMacros.h>
#include<cppunit/TestCaller.h>
#include<cppunit/TestResult.h>
#include<cppunit/TestRunner.h>
#include<cppunit/TextTestProgressListener.h>
#include<cppunit/ui/text/TextTestRunner.h>
#include<cppunit/extensions/TestFactoryRegistry.h>

#include "NX.hpp"


int main(int argc,char **argv){

	pni::nx::h5::H5Setup.verbose(false);
    //setup the test runner
    CppUnit::TextTestRunner runner;
    CppUnit::TextTestProgressListener progress;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    
    runner.addTest(registry.makeTest());
    runner.eventManager().addListener(&progress);
    
    
    runner.run();

    std::cout<<"done!"<<std::endl;


    return 0;
}

