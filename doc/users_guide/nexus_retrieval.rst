==================
Retrieving objects
==================

Objects (instances of :cpp:class:`hdf5::node::Node`) within an HDF5 file are
addressed by a path (instance of :cpp:class:`hdf5::Path`) which is a list 
of link names one has to follow to ultimately end up at the requested object.

In the NeXus world, additionally to the name of a link, we also can search 
for objects  by their type or base class. This introduces a new kind of 
path: the *NeXus path* represented by the :cpp:class:`pni::io::nexus::Path`. 
A NeXus path allows to augument every link name with a particular base class 
type. So for instance, the HDF5 path to the ``data`` field in a detector group 
would read 

   ``/entry/instrument/detector/data``
   
the NeXus path would look like this 

   ``/entry:NXentry/instrument:NXinstrument/detector:NXdetector/data``
   
where the string after the ``:`` denotes the base class type of the particular 
group. Clearly we cannot add a type to a dataset name (like ``data`` here). 
In particular, the NeXus standard demands that there is only on instance 
of ``NXinstrument`` in an entry group. Thus, we could reduce the above path to

   ``/entry:NXentry/:NXinstrument/detector:NXdetector/data``
   
and still would be able to uniquely address the requested data field. 
Furthermore, if there is only one detector available we could further reduce
the path to 

   ``/entry:NXentry/:NXinstrument/:NXdetector/data``
   
The advantage of this path scheme is that the path becomes independent on 
the particular name of, for instance, the detector group. In some sense 
a NeXus path will ask for objects of a particular properties rather than 
for a particular name. 
However, this ability also has some disadvantage: a NeXus path does not 
necessarily address an object uniquely. Take the above example: if there is more 
than one detector in the instrument group from the above path we could not 
tell which detector group should be selected. However, as will be shown later, 
this property of a NeXus path can be exploited to our advantage. 

.. toctree::
   :maxdepth: 1
   
   nexus_path
   nexus_search