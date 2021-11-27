==================
Working with files
==================

.. note::

   The functions presented in this chapter mainly deal with objects of 
   type :cpp:class:`hdf5::file::File`. For a full list of operations provided
   by this type consult the *h5cpp* manual.

Creating single files
=====================

In order to create a file *libpniio* provides some simple wrappers around 
the :cpp:func:`hdf5::file::create` functions provided by *h5cpp*. These wrappers
basically add all the attributes to the root group of an HDF5 file required 
by the NeXus standard. 
In order to create a single file use the :cpp:func:`nexus::create_file` 
wrapper function which in turn will return an instance of 
:cpp:class:`hdf5::file::File`

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

This option should be used with case as all data stored in the original file 
will be lost forever. For more options to :cpp:func:`create_file` 
check the API documentation and the *h5cpp* documentation.  


Create distributed files
========================

.. todo::

   Do we really need this feature. Need to discuss this during the next 
   group meeting

..
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

Like for creating files there is a wrapper function :cpp:func:`nexus::open_file`
to open a NeXus file. 
 
.. code-block:: cpp

   hdf5::file::File f = nexus::open_file("test.nxs");

By default files are opened in read-only mode in order to avoid accidental 
data manipulations. To open a file for reading and writing use 

.. code-block:: cpp

   hdf5::file::File f = nexus::open_file("test.nxs",hdf5::file::AccessFlags::READWRITE);

The object returned by :cpp:func:`nexus::open_file` is again an instance 
of :cpp:func:`hdf5::file::File`. The :cpp:func:`nexus::open_file` does 
not check whether or not is a valid NeXus file. In order to perform that 
check use the :cpp:func:`is_nexus_file`

.. code-block:: cpp

   boost::filesystem::path file_path = ...;
   
   if(!nexus::is_nexus_file(file_path))
   {
      std::cerr<<"File "<<file_path<<" is not a valid NeXus file!"<<std::endl;
      return 1;
   }
   
   hdf5::file::File file = nexus::open_file(file_path);


