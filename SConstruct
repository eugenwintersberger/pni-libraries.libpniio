#load python modules
import os.path as path
import os
import platform
from smod import ProgramVersion
from smod import GCCVersionParser
from smod import CheckProgram
from smod import LibFileNames

#made here a small comment - should be only in the branch

debug = ARGUMENTS.get("DEBUG",0)

var = Variables('BuildConfig.py')
var.Add(PathVariable("PREFIX","set installation prefix","/usr"))
var.Add(PathVariable("BOOSTPREFIX","set the installation prefix for boost","/usr"))
var.Add(PathVariable("HDF5PREFIX","set the installation prefix for HDF5","/usr"))
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
var.Add("INCINSTPATH","installation path for header files","")
var.Add("LIBINSTPATH","library installation path","")
var.Add("PKGNAME","package name (actually only used for Debian packages)","")

#need now to create the proper library suffix

#create the build environment
env = Environment(variables=var,tools=['default','packaging','textfile'])
env.Replace(CXX = env["CXX"])

#check if the compiler version is ok and set definies if necessary
gcc_version = GCCVersionParser().parse(prog=env["CXX"])
#for GCC versions 4.4 and 4.5 some extra defines are required in order
#to work correctly with C++11 language extensions.
if gcc_version < ProgramVersion(4,4,0):
    print "compiler version not supported!"
    sys.exit()
elif gcc_version <= ProgramVersion(4,6,0):
    env.Append(CXXFLAGS=["-Dnullptr=NULL","-DOLD_CXX"])
else:
    pass
            
libname = LibFileNames(env["LIBNAME"],env["VERSION"],env["SOVERSION"])
env.Append(LIBFULLNAME = libname.full_name(env))
env.Append(LIBSONAME   = libname.so_name(env))
env.Append(LIBLINKNAME = libname.link_name(env))

#create installation paths
env.Append(INCINSTPATH = path.join(env["PREFIX"],"include/pni/nx"))
if platform.machine()=="x86_64":
    env.Append(LIBINSTPATH = path.join(env["PREFIX"],"lib64"))
else:
    env.Append(LIBINSTPATH = path.join(env["PREFIX"],"lib"))

if env["DOCDIR"] == "":
    #set default documentation directory for installation
    env.Append(DOCDIR = path.join(env["PREFIX"],"share/doc/"+
                                  env["LIBPREFIX"]+env["LIBNAME"]
                                  +env["SOVERSION"]+"-doc"))

if env["PKGNAME"] == "":
    env.Append(PKGNAME = env["LIBPREFIX"]+env["LIBNAME"]+env["SOVERSION"])

#set some linker flags

env.Append(LIBS=["hdf5"])

#set the proper compiler - this should be changed to something 
#more general - independent of the underlying operating system
env.Replace(CXX = env["CXX"])

#set default compiler flags
env.Append(CXXFLAGS = ["-Wall","-std=c++0x"])
#set paths for Boost and HDF5

env.Append(LIBPATH=[path.join(env["HDF5PREFIX"],"lib")])
env.Append(CPPPATH=[path.join(env["HDF5PREFIX"],"include")])
env.Append(LIBPATH=[path.join(env["BOOSTPREFIX"],"lib")])
env.Append(CPPPATH=[path.join(env["BOOSTPREFIX"],"include")])

#Once all parameters are set we can start with system configuration
#-------------------------------------------------------------------------------
#start with configuration
conf = Configure(env,custom_tests = {"CheckProgram":CheckProgram})

#check available programs
if not conf.CheckProgram("pdflatex -v"):
    print "pdflatex not installed!"
    Exit(1)
    
if not conf.CheckProgram("dot -V"):
    print "graphviz not installed!"
    Exit(1)
    
if not conf.CheckProgram("perl -v"):
    print "perl not installed!"
    Exit(1)

#check for header files
if not conf.CheckCXXHeader("boost/numeric/conversion/cast.hpp"):
    print "BOOST header file cast.hpp does not exist!"
    Exit(1)
    
if not conf.CheckCXXHeader("boost/shared_ptr.hpp"):
    print "BOOST header shared_ptr.hpp does not exist!"
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
    
if not conf.CheckCXXHeader("cppunit/TestResult.h"):
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
if not conf.CheckLib("hdf5"):
    print "HDF5 libraries not installed!"
    Exit(1)

    
if not conf.CheckLib("cppunit"):
    print "CPPUNIT unit test libraray is not installed!"
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
SConscript(["debian/SConscript"])
SConscript(["doc/SConscript"])

#set default target this is important otherwise we get a problem with the 
#debian build (which will be executed too)
Default("all")

