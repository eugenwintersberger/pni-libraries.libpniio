import os.path as path
import os

#made here a small comment - should be only in the branch

debug = ARGUMENTS.get("DEBUG",0)

var = Variables('BuildConfig.py')
var.Add(PathVariable("PREFIX","set installation prefix","/usr/local"))
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
var.Add("PKGNAMEROOT","root package name (actually only used for Debian packages)","")

#need now to create the proper library suffix

#create the build environment
env = Environment(variables=var,tools=['default','packaging','textfile'])

#create library names
if os.name == "posix":
    env.Append(LIBFULLNAME = env["LIBPREFIX"]+env["LIBNAME"]+env["SHLIBSUFFIX"]+"."
                             +env["SOVERSION"]+"."+env["VERSION"])
    env.Append(LIBSONAME = env["LIBPREFIX"]+env["LIBNAME"]+env["SHLIBSUFFIX"]+"."+
                             env["SOVERSION"])
    env.Append(LIBLINKNAME = env["LIBPREFIX"]+env["LIBNAME"]+env["SHLIBSUFFIX"])
elif os.name == "nt":
    env.Append(LIBFULLNAME = env["LIBPREFIX"]+env["LIBNAME"]+"."+env["SOVERSION"]+
                             "."+env["VERSION"]+env["SHLIBSUFFIX"])
    env.Append(LIBSONAME = env["LIBPREFIX"]+env["LIBNAME"]+"."+env["SOVERSION"]+env["SHLIBSUFFIX"])
    env.Append(LIBLINKNAME = env["LIBPREFIX"]+env["LIBNAME"]+env["SHLIBSUFFIX"])

#create installation paths
env.Append(INCINSTPATH = path.join(env["PREFIX"],"include/pni/nx"))
env.Append(LIBINSTPATH = path.join(env["PREFIX"],"lib"))

if env["DOCDIR"] == "":
    #set default documentation directory for installation
    env.Append(DOCDIR = path.join(env["PREFIX"],"share/doc/"+
                                  env["LIBPREFIX"]+env["LIBNAME"]
                                  +env["SOVERSION"]+"-doc"))

if env["PKGNAMEROOT"] == "":
    env.Append(PKGNAMEROOT = env["LIBPREFIX"]+env["LIBNAME"]+env["SOVERSION"])

#set some linker flags

env.Append(LIBS=["hdf5","pniutils"])

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



build_env = env.Clone()

if debug:
    build_env.Append(CXXFLAGS=["-O0","-g"])
else:
    build_env.Append(CXXFLAGS=["-O2"])
    
test_build_env = build_env.Clone()
build_env.Append(LINKFLAGS=["-Wl,-h"+env["LIBPREFIX"]+env["LIBNAME"]+env["SHLIBSUFFIX"]+"."+env["SOVERSION"]]) 
    
Export("build_env")
Export("test_build_env")


SConscript(["src/SConscript"])
SConscript(["test/SConscript"])
SConscript(["debian/SConscript"])
SConscript(["doc/SConscript"])

