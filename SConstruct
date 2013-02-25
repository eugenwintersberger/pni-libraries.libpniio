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

AddOption("--enable-mpi",dest="with_mpi",action="store_true",default=False)

var = Variables()
var.Add(PathVariable("PREFIX","set installation prefix","/usr"))
var.Add(PathVariable("BOOSTINCDIR","installation directory of boost headers","/usr/include"))
var.Add(PathVariable("BOOSTLIBDIR","installation directory of boost libraries","/usr/include"))
var.Add(PathVariable("H5INCDIR","Directory where HDF5 headers are installed","",PathVariable.PathAccept))
var.Add(PathVariable("H5LIBDIR","Directory where HDF5 libraries are installed","",PathVariable.PathAccept))
var.Add(PathVariable("MPILIBDIR","Directory where MPI libraries are installed","/usr/lib"))
var.Add(PathVariable("MPIINCDIR","Directory where MPI headers are installed","/usr/include"))

var.Add("H5LIBNAME","HDF5 library name","hdf5")
var.Add("VERSION","library version","1.0.0")
var.Add("LIBNAME","library name","pniio")
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
env["ENV"]["PATH"] = os.environ["PATH"]
env.ParseConfig('pkg-config --libs --cflags pnicore')
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
env.Append(CXXFLAGS = ["-Wall","-std=c++0x","-fno-deduce-init-list","-pedantic"])
if debug:
    env.Append(CXXFLAGS=["-DDEBUG"])

#need to link explicit against libdl because some compilers 
#are not doing this by default
#set paths for Boost and HDF5
if env["H5LIBDIR"]: env.AppendUnique(LIBPATH = env['H5LIBDIR'])
if env["H5INCDIR"]: env.AppendUnique(CPPPATH = env['H5INCDIR'])
if env['BOOSTINCDIR']: env.AppendUnique(CPPPATH = env['BOOSTINCDIR'])
if env['BOOSTLIBDIR']: env.AppendUnique(LIBPATH = env['BOOSTLIBDIR'])

if GetOption("with_mpi"):
    env.AppendUnique(LIBPATH=env["MPILIBDIR"])
    env.AppendUnique(CPPPATH=env["MPIINCDIR"])

#========================custom tests for compiler capabilties=================

#Once all parameters are set we can start with system configuration
#-------------------------------------------------------------------------------
#start with configuration
Export("env")
(build_env,test_env) = SConscript("configure/SConscript")

#-------------------------------------------------------------------------------


if debug:
    build_env.Append(CXXFLAGS=["-O0","-g"])
    test_env.Append(CXXFLAGS=["-O0","-g"])
else:
    build_env.Append(CXXFLAGS=["-O2"])
    test_env.Append(CXXFLAGS=["-O2"])
    
build_env.Append(LINKFLAGS=["-Wl,-h"+libname.so_name(env)]) 
    
Export("build_env")
Export("test_env")


SConscript(["src/SConscript"])
SConscript(["test/SConscript"])
SConscript(["doc/SConscript"])

#set default target this is important otherwise we get a problem with the 
#debian build (which will be executed too)
Default("all")

