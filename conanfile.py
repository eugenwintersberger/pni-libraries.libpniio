from conans import ConanFile, CMake, tools


class H5CppConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake", "cmake_find_package"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "with_mpi": [True, False],
        "with_boost": [True]
    }
    default_options = {
        "shared": False,
        "fPIC": True,
        "with_mpi": False,
        "with_boost": True,
        "hdf5:hl": True,
        "hdf5:enable_cxx": False
    }

    def build_requirements(self):
        self.build_requires("catch2/2.13.7")
        self.build_requires("ninja/1.10.2")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.with_mpi

    def configure(self):
        if self.options.get_safe("with_mpi", False):
            self.options["hdf5"].parallel = True

    def requirements(self):
        self.requires("hdf5/1.12.0")
        # self.requires("boost/1.77.0")
        self.requires("boost/1.71.0")
        # self.requires("hdf5/1.10.6")
        # self.requires("boost/1.69.0")
        self.requires("doxygen/1.9.2")
        # self.requires("zlib/1.2.11")
        # self.requires("bzip2/1.0.8")
        if self.options.get_safe("with_mpi", False):
            self.requires("openmpi/4.1.0")

    def build(self):
        cmake = CMake(self)
        cmake.definitions.update({
            "PNINEXUS_CONAN": "MANUAL",
            "PNINEXUS_WITH_MPI": self.options.get_safe("with_mpi", False)
        })
        with tools.run_environment(self):
            cmake.configure()
            cmake.build()
