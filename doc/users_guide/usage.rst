=================
Using the library
=================

.. _nexus_quickstart:

This chapter describes how you can use *libpniio* from within your own 
C++ project. As already mentioned in the installation chapter, *libpniio* uses
:program:`cmake` as its build tool. In addition it also exports a *cmake-package* 
providing access to all the installation details. 

For all the following examples we use the following minimal C++ program as 
an example 

.. code-block:: cpp

   #include <h5cpp/hdf5.hpp>
   #include <pni/nexus.hpp>
   
   using namespace pni::io;
   
   int main()
   {
      hdf5::file::File file = nexus::create("hello.nxs",hdf5::file::AccessFlags::TRUNCATE);
      
      return 0;
   }
   
which we assume is the content of a file named :file:`hello.cpp`. 

Building with :program:`CMake`
==============================

This is most probably the easierst case. As *libpniio* also installs a 
*cmake-package* which provides an imported target using the library is 
fairly easy. For the code example above a sufficient :file:`CMakeLists.txt` 
file would look like this

.. code-block:: cmake

   cmake_minimum_required(VERSION 3.5.0)
   project(hello LANGUAGES C CXX VERSION 0.0.1)
   
   find_package(pniio REQUIRED)
   
   add_executable(hello hello.cpp)
   target_link_libraries(hello pniio)
   
`pniio` in the `target_link_library` command is an imported target which 
contains all the information required to build and link with *libpniio*. 
This includes

* the location of the library as well as all its dependencies 
* the location of the header files. 


Build from the command line
===========================

.. todo:: 

   Need to finish this section

.. code-block:: bash

    $> g++ -std=c++11 -otest test.cpp $(pkg-config --cflags --libs pniio)

There are two important remarks we have to make here. The first is the 
`-std=c++11` option. This tells the compiler to use the new C++11
standard which is absolutely mandatory if you want to use *libpniio*. 
the `pkg-config` command at the end of the command line includes all the
necessary compiler and linker flags to build and link the code.

Build with a Makefile
=====================

.. todo::

   Need to finish this section

`pkg-config` can be used in a Makefile by putting the following at the top
of your Makefile

.. code-block:: make

   CPPFLAGS=-O2 -g -std=c++11 $(shell pkg-config --cflags pniio)
   LDFLAGS=$(shell pkg-config --libs pniio)




