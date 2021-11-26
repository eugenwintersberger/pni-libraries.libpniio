================
Creating objects
================

*libpninexus* provides some convenience approaches for creating objects. 
This incudes

* group (base class) creation
* field (dataset) creation. 

*libpninexus* provides no special means to handle attributes, instead use 
the facilities provided by *h5cpp*.

Creating base classes
=====================

The basic elements of a NeXus tree are base classes. Technically, a base
class is an HDF5 groups with a ``NX_class`` attribute attached to it 
determining the particular base class the group represents. So creating 
a base class group with *h5cpp* a three step process would have to be 
taken
 
1. check if the new name for the group complies to the NeXus naming rules
2. create the new group
3. create a string attribute attached to this group storing the name of the 
   particular base class the group should represent. 
   
To make this easier *libpninexus* provides the :cpp:class:`BaseClassFactory` 
factory class with a static :cpp:func:`create` member function which 
carries out all these tasks 

.. code-block:: cpp

   using hdf5::node::Group;
   Group entry      = nexus::BaseClassFactory::create(root_group,"run_001","NXentry"); 
   Group instrument = nexus::BaseClassFactory::create(entry,"instrument","NXinstrument");
   Group detector   = nexus::BaseClassFactory::create(instrument,"detector","NXdetector");
   Group sample     = nexus::BaseClassFactory::create(entry,"sample","NXsample");
   
The second argument of the :cpp:func:`create` function is an HDF5 path 
(:cpp:class:`hdf5::Path`). You could use, in special cases a NeXus path 
as it will be shown later, but there are limitations (as will be shown later). 
                                                             
Creating fields
===============

Similar as for base classes *libpninexus* provides a factory class to create 
fields: :cpp:class:`nexus::FieldFactory` in order to create HDF5 datasets. 
:cpp:class:`nexus::FieldFactory` provides two static member functions capable 
of creating chunked and contiguous HDF5 datasets. 

To create a simple dataset use 

.. code-block:: cpp

   hdf5::dataspace::Scalar space; 
   auto type = hdf5::datatype::create<int>();
   
   hdf5::node::Dataset number_of_frames = nexus::FieldFactory::create(root_group,"number_of_frames",type,space);

As you may know, such fields cannot be extended and are thus only useful 
for static data. If you want an extensible dataset a chunked layout should 
be chosen. 

.. code-block:: cpp

   auto type = hdf5::datatype::create<uint16>();
   hdf5::dataspace::Simple space{{0,1024,2048},{hdf5::dataspace::Simple::UNLIMITED,1024,2048}};
   hdf5::Dimensions chunk_shape{1,1024,2048};
   
   hdf5::node::Dataset frames = nexus::FieldFactory::create(root_group,"frames",type,space,chunk_shape);
   
The major additional task the :cpp:func:`create` function of 
:cpp:class:`nexus::FieldFactory` does is to check whether the new name of the 
field complies to the NeXus naming rules. 








