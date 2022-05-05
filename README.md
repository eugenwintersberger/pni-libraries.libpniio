 # libpninexus

![github workflow](https://github.com/pni-libraries/libpninexus/actions/workflows/tests.yml/badge.svg) [![docs](https://img.shields.io/badge/Documentation-webpages-ADD8E6.svg)](https://pni-libraries.github.io/libpninexus/index.html)

`libpninexus` provides the IO functionality among the PNI libraries. Currently this
is restricted to file IO. The library supports

* simple ASCII io with formatters and parsers
* read support for TIFF and CBF files
* read support for DESY FIO files
* read/write support for Nexus files


## Installation

In order to install `libpninexus` on a Linux system the following software packages
are requiered sdfdsf

* a C++11 compatiable compiler (gcc >= 4.9, msvc >= 2014)
* cmake (>= 3.10)
* doxygen in order to build the documentation
* sphinx to build the users guide

`libpninexus` requires certain library dependencies to be installed on the
build system

* Boost (>=1.60)
* [h5cpp](https://github.com/ess-dmsc/h5cpp) (>=0.5.0) -- from https://ess-dmsc.github.io/h5cpp/

and their transitive dependencies. If all dependencies are available on your
system you can clone this repository and configure the build

```bash
$ git clone https://github.com/pni-libraries/libpninexus.git
$ cd libpninexus
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/opt/pninexus -DPNINEXUS_CONAN=DISABLE ../
```

with `CMAKE_INSTALL_PREFIX` we tell the system where to install the library
and its header files.
To start the build use

```bash
$ make
```

By the default the `all` target is built which excludes the tests. To build
and run the tests use

```bash
$ make check
```

Finally, you can install the code with

```bash
$ make install
```

to the directory determined by `CMAKE_INSTALL_PREFIX`.

## Using the library

The package not only installs the libraries runtime binaries and header files
but also cmake package files which make using the library quite simple if
you use `cmake` for your own build. Consider the following simple example
program in a file `hello.cpp`

```cpp
#include <pni/nexus.hpp>

using namespace pni;

int main()
{
    hdf5::file::File file = nexus::create_file("hello.nxs",hdf5::file::AccessFlags::Truncate);

    return 0;
}

```

When using `cmake` for the build the `CMakeLists.txt` file look like this

```cmake
cmake_minimum_required(VERSION 3.5.0)
project(hello LANGUAGES C CXX VERSION 0.0.1 )

find_package(pninexus REQUIRED)

add_executable(hello hello.cpp)
target_link_libraries(hello pninexus)
```

More information can be found at [online documentation](https://pni-libraries.github.io/libpninexus/index.html).

Changes for a specific version of libpninexus can be found
at [CHANGELOG](https://github.com/pni-libraries/libpninexus/blob/develop/CHANGELOG.md).
