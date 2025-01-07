from conan import ConanFile, tools
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps
from conan.tools.env import VirtualBuildEnv, VirtualRunEnv


class PNINeXusConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "with_mpi": [True, False],
        "with_boost": [True, False],
        "install_prefix": [None, "ANY"]
    }
    default_options = {
        "shared": False,
        "fPIC": True,
        "with_mpi": False,
        "with_boost": True,
        "hdf5/*:hl": True,
        "hdf5/*:enable_cxx": False,
        "hdf5/*:shared": False,
        "install_prefix": None
    }

    def build_requirements(self):
        self.build_requires("ninja/1.12.1")
        self.build_requires("zlib/1.3.1")
        if self.settings.os == "Windows":
           self.tool_requires("b2/5.2.1")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.with_mpi

    def configure(self):
        if self.options.get_safe("with_mpi", False):
            self.options["hdf5"].parallel = True

    def requirements(self):
        self.requires("hdf5/1.14.5")
        self.requires("zlib/1.3.1")
        self.requires("szip/2.1.1")
        self.requires("bzip2/1.0.8")
        # self.requires("doxygen/1.9.4")


        if self.options.get_safe("with_boost", False):
            if self.settings.os == "Windows":
                self.requires("boost/1.86.0")
            elif self.settings.os == "Macos":
                self.requires("boost/1.81.0")
            else:
                self.requires("boost/1.81.0")
        if self.options.get_safe("with_mpi", False):
            self.requires("openmpi/4.1.0")

    def build(self):
        cmake = CMake(self)
        build_env = VirtualBuildEnv(self).vars()
        run_env = VirtualRunEnv(self).vars()
        with build_env.apply():
            with run_env.apply():
                variables = {
                    "PNINEXUS_CONAN": "MANUAL",
                    "PNINEXUS_BUILD_DOC": False,
                    # "PNINEXUS_WITH_BOOST":
                    # self.options.get_safe("with_boost", False),
                    "PNINEXUS_WITH_MPI":
                    self.options.get_safe("with_mpi", False)
                }
                insprefix = self.options.get_safe("install_prefix", None)
                if insprefix:
                    variables["CMAKE_INSTALL_PREFIX"] = insprefix
                    variables["h5cpp_DIR"] = "%s/%s" % (
                        insprefix, "lib/cmake/h5cpp-0.6")
                cmake.configure(variables=variables)
                cmake.build()
