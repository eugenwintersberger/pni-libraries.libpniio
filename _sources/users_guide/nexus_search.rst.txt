=====================
Searching for objects
=====================

One of the most important tasks for an application when dealing with NeXus files
is to look for specific objects below a particular group. Such searches would 
include 

* search for all detectors used during a particular experiment 
* search for all entries (top level elements) in a given file
* look for all datasets (fields) with particular properties 
  
and many more. Of course it would be possible to simply use the iterator 
interface provided by *h5cpp* along with STL algorithms to do the job and 
there is nothing wrong in doing so. However, *libpninexus* provides some 
convenience functions and classes to make the task easier.  
  
Search with path
================

When the search criteria can be expressed in terms of a NeXus path the 
simplest approach would be to use the :cpp:func:`get_objects` function. 
As a NeXus path can also reference attributes its return value is an instance 
of :cpp:class:`PathObjectList` which is a list of :cpp:class:`PathObject`. 
The latter one is a wrapper class which can store all three types of 
HDF5 objects a NeXus path can reference: groups, datasets and attributes. 
Luckily there is an implicit conversion operator which allows the conversion 
of :cpp:class:`PathObjectList` to any other list type provided by *libpninexus* 
relevant to NeXus files 

.. code-block:: cpp

   nexus::Group entry = root_group.nodes["run_001"];
   nexus::GroupList detectors = nexus::get_objects(entry,":NXinstrument/:NXdetector");
   
An other application would be to look for all entries in a file 

.. code-block:: cpp

   nexus::GroupList entries = nexus::get_objects(root_group,":NXentry");
   
.. attention::

   Though using path search is quite comfortable there is one word of 
   caution when you are concerned about performance. Under the hood 
   :cpp:func:`get_objects` performs a recursive search. So if the object trees
   in the file grow large this may can cause some severe performance penalty.
   
   However, in most cases this is not critical and thus the simplicity of 
   implementation outweighs this performance penalty.  

Search with predicates
======================

To search for all detectors in a run using predicates we could use the 
following approach 

.. code-block:: cpp

   nexus::Group entry = root_group.nodes["run_001"];
   nexus::GroupList detectors = nexus::search(entry,nexus::IsDetector(),true);
   
The last argument of the :cpp:func:`search` function determines whether or not 
a recursive search below the ``entry`` element will be made. 

In principle everything that can be done with :cpp:func:`get_objects` and 
a NeXus path can also be done with predicates. However, the :cpp:class:`NodePredicate`
allows also some more fine grained search. Consider the case where we 
want to find all 1D data elements below a particular entry which stores
more than one entry (this would be a reasonable thing to do if we 
are searching for plotable data outside of the *NXdata* group).  

We would first implement a custom predicate 

.. code-block:: cpp

   class Is1dDataset : public NodePredicate
   {
      public:
      
      virtual bool operator()(const hdf5::node::Node &node) const
      {
         if(node.type() == hdf5::node::Type::DATASET)
         {
            hdf5::node::Dataset dataset(node);
            hdf5::Dimensions dimensions = get_dimensions(dataset);
            
            return dimensions.size()==1 && dimensions[0]>1;
         } 
         return false;
      }
   };
   
with this predicate the search would simply be 

.. code-block:: cpp

   nexus::Group entry = root_group.nodes["run_001"];
   nexus::DatasetList datasets_1d = nexus::search(entry,Is1dDataset(),true);
   
   
Because looking for base classes is such a common taks *libpninexus* provides 
a set of predefined predicates dedicated to this purpose.  
The fundamental predicate type to look for base classes is 
:cpp:class:`nexus::IsBaseClass`. 
If you want to know just want to identify those groups which are a base class 
you could use 

.. code-block:: cpp

   nexus::Group entry = root_group.nodes["run_001"];
   nexus::GroupList base_classes = nexus::search(entry,IsBaseClass(),true);
   
To look for a specific base class you could use 

.. code-block:: cpp

   nexus::Group entry = root_group.nodes["run_001"];
   nexus::GroupList base_classes = nexus::search(entry,IsBaseClass("NXattenuator"),true);

For some of the most common base classes there are specialized versions of 
:cpp:class:`nexus::IsBaseClass`. 

+-------------------------------+---------------------------------------+
| predicate                     | description                           |
+===============================+=======================================+
| :cpp:class:`IsTransformation` | returns *true* for *NXtransformation* |
+-------------------------------+---------------------------------------+
| :cpp:class:`IsEntry`          | returns *true* for *NXentry*          |
+-------------------------------+---------------------------------------+
| :cpp:class:`IsSubentry`       | returns *true* for *NXsubentry*       |
+-------------------------------+---------------------------------------+
| :cpp:class:`IsDetector`       | returns *true* for *NXdetector*       |
+-------------------------------+---------------------------------------+
| :cpp:class:`IsInstrument`     | returns *true* for *NXinstrument*     |
+-------------------------------+---------------------------------------+
| :cpp:class:`IsSample`         | returns *true* for *NXsample*         |
+-------------------------------+---------------------------------------+
| :cpp:class:`IsData`           | returns *true* for *NXdata*           |
+-------------------------------+---------------------------------------+
