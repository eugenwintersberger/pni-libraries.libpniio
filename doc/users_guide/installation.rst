============
Installation
============

Before you building `libpninexus` from sources one should first check if
pre-built binary packages are available. Building the library from the sources
requires a certain level of expertise which not all users posess.
As
`libpninexus` is mostly a template library only a few non performance critical
components have to be compiled. Therefore, custom builds of the libraries
binaries are not necessary in order to get optimum performance.

.. ============================================================================

Installing pre-built binary packages
====================================

Binary packages are currently available for the following platforms

* Debian/GNU Linux
* Ubuntu Linux

Debian and Ubuntu users
-----------------------

As Debian and Ubuntu are closely related the installation is quite similar.
The packages are provided by a special Debian repository. To work on the
package sources you need to login as `root` user. Use :command:`su` or
:command:`sudo su` on Debian and Ubuntu respectively.
The first task is to add the GPG key of the HDRI repository to your local
keyring

.. code-block:: bash

   $ curl -s http://repos.pni-hdri.de/debian_repo.pub.gpg  | gpg --no-default-keyring --keyring gnupg-ring:/etc/apt/trusted.gpg.d/debian-hdri-repo.gpg --import
   $ chmod 644 /etc/apt/trusted.gpg.d/debian-hdri-repo.gpg


The return value of this command line should be `OK`.
In a next step you have to add new package sources to your system. For this
purpose go to :file:`/etc/apt/sources.list.d` and download the sources file.
For Debian (Bookworm) use

.. code-block:: bash

   $ wget http://repos.pni-hdri.de/bookworm-pni-hdri.list

and for Ubuntu (Jammy)

.. code-block:: bash

   $ wget http://repos.pni-hdri.de/jammy-pni-hdri.list

The packages are also available for Debian Bookworm, Bullseye, Buster and Ubuntu Lunar, Jammy, Focal.

Once you have downloaded the file use

.. code-block:: bash

   $ apt-get update


to update your package list and

.. code-block:: bash

   $ apt-get install libpninexus3.2.0 libpninexus3.2.0-dev libpninexus3.2.0-doc

to install the library. Dependencies will be resolved automatically so you can
start with working right after the installation has finished.


Install from sources
====================

If your OS platform or a particular Linux distribution is currently not
supported you have to build `libpninexus` from its sources. As this process
usually requires some expert knowledge keep be prepared to get your hands dirty.

Requirements
------------

For a successful build some requirements must be satisfied

* `h5cpp` >= 0.5.0
* `gcc` >= 4.7 -- since version 1.0.0 `libpninexus` requires a mostly C++11
   compliant compiler. For the gcc familiy this is 4.7 and upwards
* `BOOST` >= 1.60
* `doxygen` \cite{web:doxygen} -- used to build the API documentation
* `cmake` \cite{web:cmake} $>=$ 3.10 -- the build software used by the `libpninexus`
* `pkg-config` \cite{web:pkgconfig} -- program to manage libraries

Building the code
-----------------

The sources can be obtained directly from the Git repository.

.. code-block:: bash

   $ git clone https://github.com/pni-libraries/libpninexus.git
   $ cd libpninexus
   $ cd ..

which will result in a new directory named :file:`libpninexus`. As we use
:command:`cmake` for
building the library, out of place builds are recommended. For this purpose
create a new directory where the code will be built and change to this directory

.. code-block:: bash

   $ mkdir libpninexus-build
   $ cd libpninexus-build

Now call :command:`cmake` with a path to the original source directory

.. code-block:: bash

   $ cmake -DCMAKE_BUILD_TYPE=Release -DPNINEXUS_CONAN=DISABLE ../libpninexus

or

.. code-block:: bash

   $ export H5CPP=/opt/pni/lib/cmake/h5cpp-0.5.0
   $ cmake -Dh5cpp_DIR=$H5CPP -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/opt/pni -DPNINEXUS_CONAN=DISABLE ../libpninexus

if `h5cpp` is installed in the non-standard directory.

A subsequent :command:`make` finally build the library

.. code-block:: bash

   $ make

This may take a while. Actually building the library is quite fast as
`libpninexus` is mostly a template, and thus header-only, library.
However, building the test suite is rather time consuming.

Testing the build
-----------------

Once the build has finished you should definitely run the tests.
`libpninexus` uses the :command:`ctest` facility of :command:`cmake`. To build
and run the tests just type

.. code-block:: bash

    $ make check


Installation
------------

If the build has passed the test suite `libpninexus` can be installed from within
the build directory with

.. code-block:: bash

   $ make install

By default the installation prefix is :file:`/usr/local`. If another prefix should
be used the :envvar:`CMAKE_INSTALL_PREFIX` variable must be set when running
:command:`cmake` with

.. code-block:: bash

   $ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/opt/pni -DPNINEXUS_CONAN=DISABLE ../libpninexus

which causes the installation prefix to be :file:`/opt/pni`.
