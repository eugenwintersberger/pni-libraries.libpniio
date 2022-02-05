/*! \mainpage @CMAKE_PROJECT_NAME@ @LIBRARY_VERSION@ documentation

\section Introduction
\c libpninexus is a C++ implementation of the Nexus file format. Althoug the NIAC
provides a C++ interface to their C-API too, \c libpninexus is a pure C++
implementation providing all the ideoms a C++ programmer would expect from an
API. In contrary to the NIAC implementation \c libpninexus supports only the HDF5
file format as a backend to store data (this is virtually its only restriction
in comparison to the existing C++ interface). Aside from this \c libpninexus
provides the following advantages over the existing API

    - Support for reading and writing \c std::string objects of variable length
    - keeping multiple object open for reading and writing concurrently (in the
      original NIAC API an object must be explicitly opened before data can be
      written or read from it)
    - support for complex numbers (32, 64, and 128 Bit) and for 128 Bit floating
      point numbers


\section outlook Outlook - concurrent applications

As demands on computing power increase in PNI experiments applications dealing
with data will run concurrently. Their are two methods to let an application run
in parallel
    - threads - if an application runs on a single host
    - MPI for distributed cluster systems

While the later approach is well known in scientific computing, multithreaded
applications are still rare. In order to write data from such applications
efficiently \c libpninexus will support both approaches.

\subsection ths Thread safety
With the new standard C++11 C++ provides multithreading support over different
platforms out of the box. However, HDF5 actually does not support multithreaded
reading or writing. Indeed library calls are serialized using a global lock in
the library. However, this is only true as long as the library  is compiled with
thread-safety switched on. If this is not the case an application has to take
care about locking. \c libpninexus will do this job for you in future.
Unfortunately it is not enough to simply introduced locks to make the code
thread safe. Along with this also the interface has to be changed in order to
reflect the problems that come with concurrency.

\subsection mpi Support for MPI IO

The Message Passing Interface is a well known interface for writing
applications running on distributed clusters. HDF5 supports parallel IO from
such clusters under some restrictions. \c libpninexus will support the MPI
interface of HDF5 to make it possible to read and write data in parallel.


*/
