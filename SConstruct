#load python modules
import os.path as path
import os
import platform

###================================================================================
#Function to assemble library filenames depending on the operating system for
#which the library is built.
class LibFileNames(object):
    def __init__(self,libname,version,soversion):
        self.libname = libname
        self.version = version
        self.soversion = soversion
    
    def full_name(self,env):
        rstr = env["LIBPREFIX"]+self.libname
        if os.name == "posix":
            rstr += env["SHLIBSUFFIX"]+"."+self.soversion+"."+self.version
        if os.name == "nt":
            rstr += "."+self.soversion+"."+self.version+env["SHLIBSUFFIX"]
            
        return rstr
    
    def so_name(self,env):
        rstr = env["LIBPREFIX"]+self.libname
        if os.name == "posix":
            rstr += env["SHLIBSUFFIX"]+"."+self.soversion
        if os.name == "nt":
            rstr += "."+self.soversion+env["SHLIBSUFFIX"]
            
        return rstr
    
    def link_name(self,env):
        rstr = env["LIBPREFIX"]+self.libname+env["SHLIBSUFFIX"]
        return rstr
#==================================================================================

#made here a small comment - should be only in the branch

debug = ARGUMENTS.get("DEBUG",0)

var = Variables('BuildConfig.py')
var.Add(PathVariable("PREFIX","set installation prefix","/usr"))
var.Add(PathVariable("BOOSTINCDIR","installation directory of boost headers","/usr/include"))
var.Add(PathVariable("BOOSTLIBDIR","installation directory of boost libraries","/usr/include"))
var.Add(PathVariable("H5INCDIR","Directory where HDF5 headers are installed","",PathVariable.PathAccept))
var.Add(PathVariable("H5LIBDIR","Directory where HDF5 libraries are installed","",PathVariable.PathAccept))

var.Add("H5LIBNAME","HDF5 library name","hdf5")
var.Add("VERSION","library version","0.0.0")
var.Add("LIBNAME","library name","pniutils")
var.Add("SOVERSION","SOVersion of the library (binary interface version)","0")
var.Add("CXX","set the compiler to use","g++")
var.Add("MAINTAINER","package maintainer for the project","Eugen Wintersberger")
var.Add("MAINTAINER_MAIL","e-mail of the package maintainer","eugen.wintersberger@desy.de")
var.Add("DOCDIR","installation directory for the documentation","")
var.Add("MANDIR","installation directory for man pages","share/man")
var.Add("LIBSONAME","name of the library including the SO-version","")
var.Add("LIBLINKNAME","name of the library used for linking","")
var.Add("LIBFULLNAME","full name of the library binary","")
var.Add("INCDIR","installation path for header files","")
var.Add("LIBDIR","library installation path","")


#need now to create the proper library suffix

#create the build environment
env = Environment(variables=var,tools=['default','packaging','textfile'])
env["ENV"]["PKG_CONFIG_PATH"] = os.environ["PKG_CONFIG_PATH"]
env.ParseConfig('pkg-config --libs --cflags pniutils')
env.ParseConfig('pkg-config --libs --cflags cppunit')
env.Replace(CXX = env["CXX"])

            
libname = LibFileNames(env["LIBNAME"],env["VERSION"],env["SOVERSION"])
env.Append(LIBFULLNAME = libname.full_name(env))
env.Append(LIBSONAME   = libname.so_name(env))
env.Append(LIBLINKNAME = libname.link_name(env))

#create installation paths
if not env["INCDIR"]: env.Append(INCDIR = path.join(env["PREFIX"],"include"))

if not env["LIBDIR"]: env.Append(LIBDIR = path.join(env["PREFIX"],"lib"))

if not env["DOCDIR"]:
    #set default documentation directory for installation
    env.Append(DOCDIR = path.join(env["PREFIX"],"share/doc/"+
                                  env["LIBPREFIX"]+env["LIBNAME"]
                                  +env["SOVERSION"]+"-doc"))

#set the proper compiler - this should be changed to something 
#more general - independent of the underlying operating system
env.Replace(CXX = env["CXX"])

#set default compiler flags
env.Append(CXXFLAGS = ["-Wall","-std=c++0x"])
#need to link explicit against libdl because some compilers 
#are not doing this by default
env.Append(LIBS=["dl"])
#set paths for Boost and HDF5
if env["H5LIBDIR"]: env.AppendUnique(LIBPATH = env['H5LIBDIR'])
if env["H5INCDIR"]: env.AppendUnique(CPPPATH = env['H5INCDIR'])
if env['BOOSTINCDIR']: env.AppendUnique(CPPPATH = env['BOOSTINCDIR'])
if env['BOOSTLIBDIR']: env.AppendUnique(LIBPATH = env['BOOSTLIBDIR'])


#========================custom tests for compiler capabilties=================
nullptr_test_code="""
int main(int argc,char **argv){
    char *ptr=nullptr;
    return 0;
}
"""

def CheckNullPtr(context):
    context.Message("Checking if compiler supports nullptr idiom ...")
    result = context.TryCompile(nullptr_test_code,".cpp")
    context.Result(result)
    return result

foreach_test_code="""
#include<iostream>
#include<vector>
int main(int argc,char **arv){
std::vector<int> vec = {1,2,3,4};
for(int &v: vec){
   std::cout<<v<<std::endl; 
}
return 0;
}
"""

def CheckForEach(context):
    context.Message("Check if compiler supports foreach loops ...")
    result = context.TryCompile(foreach_test_code,".cpp")
    context.Result(result)
    return result

initlist_test_code = """
#include <initializer_list>
class test{
public:
void testfunction(const std::initializer_list<int> &l){

}
};

template<typename T> void testtmp(){
    test t;
    t.testfunction({1,2,3});
}

int main(int argc,char **argv){
    testtmp<float>();
return 0;
}
"""

def CheckInitList(context):
    context.Message("Check for comprehensive init-list support ...")
    result = context.TryCompile(initlist_test_code,".cpp")
    context.Result(result)
    return result

#Once all parameters are set we can start with system configuration
#-------------------------------------------------------------------------------
#start with configuration
conf = Configure(env,
custom_tests = {"CheckNullPtr":CheckNullPtr,
                "CheckForEach":CheckForEach,"CheckInitList":CheckInitList})


#checking compiler capabilities
if not conf.CheckNullPtr():
    print "nullptr not supported - use NULL"
    env.Append(CXXFLAGS=["-Dnullptr=NULL"])

if not conf.CheckForEach():
    print "foreach construction not supported - use workaround"
    env.Append(CXXFLAGS=["-DNOFOREACH"])

if not conf.CheckInitList():
    print "comprehensive init list do not work ..."
    env.Append(CXXFLAGS=["-DINITLISTBUG"])

#check for header files
if not conf.CheckCXXHeader("boost/numeric/conversion/cast.hpp"):
    print "BOOST header file cast.hpp does not exist!"
    Exit(1)
    
    
if not conf.CheckCXXHeader("boost/static_assert.hpp"):
    print "BOOST header static_assert.hpp does not exist!"
    Exit(1)
    
if not conf.CheckCXXHeader("cppunit/TestFixture.h"):
    print "CPPUNIT header TestFixture.h does not exist!"
    Exit(1)
    
if not conf.CheckCXXHeader("cppunit/TestRunner.h"):
    print "CPPUNIT header TestRunner.h does not exist!"
    Exit(1)
    
if not conf.CheckCXXHeader("cppunit/extensions/HelperMacros.h"):
    print "CPPUNIT header HelperMacros.h does not exist!"
    Exit(1)
    
if not conf.CheckCXXHeader("cppunit/TestCaller.h"):
    print "CPPUNIT header TestCaller.h does not exist!"
    Exit(1)
    
if not conf.CheckCXXHeader(["string","cppunit/TestResult.h"]):
    print "CPPUNIT header TestResult.h does not exist!"
    Exit(1)
    
if not conf.CheckCXXHeader("cppunit/TextTestProgressListener.h"):
    print "CPPUNIT header TextTestProgressListener.h does not exist!"
    Exit(1)
    
if not conf.CheckCXXHeader("cppunit/ui/text/TextTestRunner.h"):
    print "CPPUNIT header TextTestRunner.h does not exist!"
    Exit(1)
    
if not conf.CheckCHeader("hdf5.h"):
    print "HDF5 header files are not installed!"
    Exit(1)

    
#check for libraries
if not conf.CheckLib(env["H5LIBNAME"]):
    print "HDF5 libraries not installed!"
    Exit(1)
    
if not conf.CheckLib("cppunit",language="C++"):
    print "CPPUNIT unit test libraray is not installed!"
    Exit(1)

if not conf.CheckLib("pniutils",language="C++"):
    print "libpniutils not installed!"
    Exit(1)

if not conf.CheckLib("boost_date_time",language="C++"):
    print "boost_date_time library not installed!"
    Exit(1)

env = conf.Finish()


#-------------------------------------------------------------------------------

#setup the different build environments
build_env = env.Clone()

if debug:
    build_env.Append(CXXFLAGS=["-O0","-g"])
else:
    build_env.Append(CXXFLAGS=["-O2"])
    
test_build_env = build_env.Clone()
build_env.Append(LINKFLAGS=["-Wl,-h"+libname.so_name(env)]) 
    
Export("build_env")
Export("test_build_env")


SConscript(["src/SConscript"])
SConscript(["test/SConscript"])
SConscript(["doc/SConscript"])

#set default target this is important otherwise we get a problem with the 
#debian build (which will be executed too)
Default("all")

