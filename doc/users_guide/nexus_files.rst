==================
Working with files
==================

Creating single files
=====================

In order to create a file *libpniio* provides some simple wrappers around 
the :cpp:func:`hdf5::file::create` functions provided by *h5cpp*. These wrappers
basically add all the attributes to the root group of an HDF5 file required 
by the NeXus standard. 

The simplest approach towards handling NeXus-files is to create a single file 
to store data. This can be achieved with the \cpp{create\_file} static member 
function of \cpp{nxfile}.

.. code-block:: cpp

   #include <pni/io/nexus.hpp>
   #include <h5cpp/hdf5.hpp>
   
   using namespace pni::io;
   
   int main(int argc,char **argv)
   {
       hdf5::file::File file = nexus::create_file("test.nxs");
       //... code omitted ...
       file.close();
   
       return 0;
   }

The code should be rather self explaining.  If the file already exists a
:cpp:class:`std::runtime_error` exception is thrown. 
In order to overwrite an existing file one can use

.. code-block:: cpp

   h5::file::File file = nexus::create_file("test.nxs",hdf5::file::AccessFlags::TRUNCATE);

where the second argument to \cpp{create\_file} enables overwriting an existing
file of same name. This option should be used with case as all data stored in 
the original file will be lost forever. 

Create distributed files
========================

In cases where a single data file would grow rather large (more than $40$ GByte
for instance) creating a single large file is not a good solution. One problem
is the transfer of the file via the network. It would require a quite
sophisticated down- or upload software which must be able to recover a transfer
from a broken network connection, for instance. 
The other problem comes from archives. Data which should be archived goes
typically to a tape library. However, such libraries typically want to have
files in a particular size in order to operate with optimal performance. 

\libpniio\ allows the content of a single file to be distributed over several
files each having the same size. Such a set of files can be created using the 
\cpp{create\_files} static member function as shown below
\begin{cppcode}
h5::nxfile file = h5::nxfile::create_files("test.%04i.nxs",1024);
\end{cppcode}
Aside from its name the arguments of the \cpp{create\_files} function have 
a slightly different meaning. If a set of files should be produced the file name
is not a simple string but a \cpp{printf} like format string. This allows the
storage backend of \libpniio\ to number each new file as it is created.
The second argument to this function is the size in MByte an individual file can 
attain before a new one will be created. The above call to \cpp{create\_files}
would yield the following files
\begin{minted}{bash}
test.0001.nxs
test.0002.nxs
test.0003.nxs
.............
\end{minted}
As for the simple \cpp{create\_file}, \cpp{create\_files} will throw an
\cpp{object\_error} exception if a file already exists. In order to overwrite an
existing file append \cpp{true} to the above call 
\begin{cppcode}
h5::nxfile file = h5::nxfile::create_files("test.%04i.nxs",1024,true);
\end{cppcode}
However, in this case already existing members of the family will not be removed
but just truncated (their size becomes $0$). So do not wonder that you still
find all the member files of a set even after overwriting it. Their size will be
set to zero.


Opening and closing files
=========================

If a file already exist the {\tt open\_file} static member function of the
\nxfile\ should be used.  Its signature is rather simple 
\begin{cppcode}
open_file(const string &n,bool ro=true)
\end{cppcode}
where the first argument is the name of the file and the second determines
whether or not the file will be opened in read-only mode. By default files are
opened read-only in order to avoid accidental changes in the file. 

\texttt{open\_file} can be used with a single file as well as with a file
family. For a single file use 
\begin{cppcode}
h5::nxfile f = h5::nxfile::open_file("test.nxs");
\end{cppcode}
In order to open a file split into several parts only a different file name 
must be used
\begin{cppcode}
h5::nxfile f = h5::nxfile::open_file("test.%05i.nxs");
\end{cppcode}
Like for file creation, the printf-like format string has to be used for the 
filename. 

Like all objects in \libpniio\ a file object is destroyed automatically if it
looses scope.  However, in some cases one may wants to explicitly close the
file. This can be done with the \texttt{close} member function
\begin{cppcode}
h5::nxfile f = ...;
.... code omitted ...
f.close();
\end{cppcode}


Other file related functions
============================

Like virtually all level $1$ objects in \libpniio\ \nxfile\ posses an
\cpp{is\_valid} inquiry method. It can be used to check whether or not an
objects is a valid instance or not. This is necessary as a default constructed
file is not a valid instance. 
\begin{cppcode}
h5::nxfile f = ...;
...code omitted ...
if(!f.is_valid())
    std::cerr<<"Something went wrong!"<<std::endl;
\end{cppcode}
You can also check whether a file is read-only or not by means of the 
\cpp{is\_readonly} member function 
\begin{cppcode}
h5::nxfile f = ...;
...code omitted ...
if(f.is_readonly())
    std::cerr<<"File is in read-only mode!"<<std::endl;
\end{cppcode}
As one can see from the API documentation, the interface of \nxfile\ is rather
simple. In order to do anything useful (like creating groups and fields) one 
has to obtain the root group of the file. This can be done with the 
\cpp{root} member function
\begin{cppcode}
h5::nxfile f = ...;
h5::nxgroup root = f.root();
\end{cppcode}
Finally there is an important member function named \cpp{flush}. Whenever
possible use this function to explicitly hand over data from the underlying
storage library to the operating system for writing.
\begin{cppcode}
h5::nxfile f =....;

while(measurement_running())
{
    //record data

    //flush the file
    f.flush();
}
\end{cppcode}

