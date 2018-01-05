=============================
A basic introduction to Nexus
=============================

Motivation
==========

Today, data recorded during synchrotron experiments is typically stored in
individual binary image files and/or as flat ASCII files. A typical directory 
structure for an individual run could look like this 

.. code-block:: bash

   ~/run_001/ user@localhost:$> ls
   
   run_001.dat
   detector/image_0001.tif
   detector/image_0002.tif
   ...
   ...
   ...
   detector/image_0100.tif 

The ASCII file :file:`run_001.dat` stores scalar data while the detector data is
stored in a separate directory as image files (here TIFF).
Such an approach leads to technical and organizational problems

* when the number of image files grows large the performance of most file 
  systems degenerate 
* to access data in an individual image file a new file handler has to be 
  created 
* image and scalar data is stored in different files which increases the
  managements efforts to keep related information together.

NeXus is a binary file format which attempts to solve all of these problems.
NeXus can keep scalar and multidimensional data within a single file and allows
to organize the data within the file in a tree like manager. Additional
attributes can be attached to each object in a file, storing metadata which 
might be required for later analysis. It must be noted that NeXus is not a
physical file format itself. It is rather a set of rules how data must be
organized within a particular format in order to become a valid Nexus file.
Currently the following physical file formats are supported by the original
Nexus API

* *XML* -- only used for file structure validation
* *HDF4* -- for historical reasons, should not be used for new data
* *HDF5* -- the current standard storage backend for Nexus files. 

One of the aims of *libpniio* is to provide an abstraction layer between the
user and the storage backend. As *libpniio* currently supports only HDF5 this is
rather artificial. However, *libpniio* provides the architecture to include
other file formats to be used with NeXus too. 
There has been a lot of confusion what physical file format NeXus files are.
Many users think that NeXus has its own physical file format. This is in fact
not true. Just to avoid any further confusion for the reader let me make this
clear once and for all

.. attention::

   **Every NeXus file written by libpniio is also a valid HDF5 file!**

To access NeXus files *libpniio* uses the *h5cpp* C++ wrapper to HDF5. 
Actually most of the work with NeXus files can be done directly with 
*h5cpp*, *libpniio* only adds additional functionality specific to the 
NeXus file standard.

.. attention::

   Before you continue reading this documentation you should have a firm 
   idea about *h5cpp*'s concepts and API. So if you never used *h5cpp* before
   you better go away for a while here and read the `h5cpp documentation`_. 


.. _h5cpp documentation: https://ess-dmsc.github.io/h5cpp/index.html

The Nexus layer model
=====================

As already mentioned in the previous section, NeXus can be considered as a set
of rules describing the logical organization of data within a file. 
NeXus, for this purpose, utilizes types defined in three different layers.

.. figure:: ../_static/layers.svg
   :align: center

Each group of types defined in a layer is used for a particular purpose. Layer 1
provides the basic brick-stones from which the NeXus standard is build of. 
Layer 2 provides collections of Layer 1 instances representing concrete beamline
components as well as abstract concepts. Layer 3 finally can be used to define 
file formats for particular experimental techniques. 

Layer 1 objects
---------------

The first layer in the NeXus layer model provides the fundamental types used 
to define the organizational structure of data in a file.

+---------------+---------------------------------------------------------+-+
| object        | description                                             | |
+===============+=========================================================+=+
| *NXgroup*     | is a container which can hold instances of fields and   | |
|               | other groups.                                           | |
+---------------+---------------------------------------------------------+-+
| *NXfield*     | stores numerical and other data.                        | |
+---------------+---------------------------------------------------------+-+
| *NXattribute* | instances of NXgroup and NXfield can be enhanced with   | |
|               | attributes which can store additional metadata about an | |
|               | object.                                                 | |
+---------------+---------------------------------------------------------+-+

Attributes behave a little like fields as will be shown later. These three types
form the basement for all other objects in the above layers. 
It should be mentioned that attributes are heavily used by the NIAC to add
metadata to a group or field. It is thus not wise to make too extensive use of
attributes as a Nexus user as it my cause name clashes with future attributes
defined by the NIAC.

The focus of *libpniio* is this first layer of the NeXus hierarchy. *libpniio*
uses HDF5 to store NeXus files. In particular the C++ wrapper *h5cpp* is 
used. There is a simple mapping between these basic Layer 1 types and native 
HDF5 types 

+---------------+-----------------------------------------+
| NeXus type    | HDF5 type                               |
+===============+=========================================+
| *NXgroup*     | :cpp:class:`hdf5::node::Group`          |
+---------------+-----------------------------------------+
| *NXfield*     | :cpp:class:`hdf5::node::Dataset`        |
+---------------+-----------------------------------------+
| *NXattribute* | :cpp:class:`hdf5::attribute::Attribute` |
+---------------+-----------------------------------------+

Layer 2 objects
---------------

Objects from the second layer are composites of the types provided by the first
layer. They describe logical or physical entities at a beamline. 
These range from the very concrete objects like undulators or detectors to
abstract concepts like *entries* and *subentries*. 
The available objects from Layer 2 are defined in the Nexus Base class
catalog.


Layer 3 objects
---------------

The third layer finally provides concepts to standardize the structure of a
Nexus data tree for particular scientific applications and methods. 
These so called *Application Definitions* are defined by the NIAC in
collaboration with the scientific community.

