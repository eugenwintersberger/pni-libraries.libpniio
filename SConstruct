import os.path as path

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

#need now to create the proper library suffix

#create the build environment
env = Environment(variables=var,tools=['default','packaging','textfile'])

#set some linker flags

env.Append(LIBS=["hdf5"])

#set the proper compiler - this should be changed to something 
#more general - independent of the underlying operating system
env.Replace(CXX = env["CXX"])

#set default compiler flags
env.Append(CXXFLAGS = ["-Wall"])
#set paths for Boost and HDF5
env.Append(LIBPATH=path.join(env["BOOSTPREFIX"],"lib"))
env.Append(CPPPATH=path.join(env["BOOSTPREFIX"],"include"))
env.Append(LIBPATH=path.join(env["HDF5PREFIX"],"lib"))
env.Append(CPPPATH=path.join(env["HDF5PREFIX"],"include"))


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

